#include "SheepleSourceView.h"
#include <stdlib.h>

G_DEFINE_TYPE(SheepleSourceView, sheeple_source_view, GTK_TYPE_SCROLLED_WINDOW)

struct _SheepleSourceViewPrivate
{
    GList *sources;
    GList *selected_groups;

    GtkWidget *source_vbox;
};

typedef struct _SheepleSourceViewSelectPrivateData
{
    SheepleSourceView *source_view;
    SheepleGroup *group;
} SheepleSourceViewSelectPrivateData;

static void sheeple_source_view_init(SheepleSourceView * self)
{
    GtkWidget *master_padding, *viewport;

    self->priv = SHEEPLE_SOURCE_VIEW_GET_PRIVATE(self);

    // Create GtkAdjustments
    gtk_scrolled_window_set_hadjustment(GTK_SCROLLED_WINDOW(self), NULL);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(self), NULL);

    // Set ScrolledWindow to automatically show scrollbars when needed
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    self->priv->source_vbox = gtk_vbox_new(FALSE, 10);

    // Pad the whole sourceview
    master_padding = gtk_alignment_new(0, 0, 1, 1);
    gtk_alignment_set_padding(GTK_ALIGNMENT(master_padding), 0, 0, 4, 4);
    gtk_container_add(GTK_CONTAINER(master_padding), self->priv->source_vbox);

    // Set up scrolled window
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(self),
                                        GTK_SHADOW_NONE);

    // Create viewport containing sourceview
    viewport =
        gtk_viewport_new(gtk_scrolled_window_get_hadjustment
                         (GTK_SCROLLED_WINDOW(self)),
                         gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW
                                                             (self)));
    gtk_container_add(GTK_CONTAINER(viewport), master_padding);
    gtk_container_add(GTK_CONTAINER(self), viewport);

    gtk_viewport_set_shadow_type(GTK_VIEWPORT(viewport), GTK_SHADOW_NONE);
}

static void sheeple_source_view_class_init(SheepleSourceViewClass * klass)
{
    g_type_class_add_private(klass, sizeof(SheepleSourceViewPrivate));
}

GtkWidget *sheeple_source_view_new()
{
    return g_object_new(SHEEPLE_TYPE_SOURCE_VIEW, NULL);
}

void _sheeple_source_view_update_selection(SheepleSourceView * self)
{
    GList *sources = self->priv->sources;

    if (!sources)
        return;

    do
    {
        SheepleSource *source = ((SheepleSource *) sources->data);
        GList *group_list = sheeple_source_get_groups(source);

        do
        {
            SheepleGroup *group = ((SheepleGroup *) group_list->data);
            const gchar *button_markup, *markup_str;
            GtkReliefStyle new_style = GTK_RELIEF_NONE;

            if (g_list_find(self->priv->selected_groups, group))
            {
                new_style = GTK_RELIEF_NORMAL;
                markup_str = "<small><b>%s</b></small>";
            }
            else
            {
                markup_str = "<small>%s</small>";
            }

            gtk_button_set_relief(GTK_BUTTON(group->_button), new_style);

            button_markup = g_markup_printf_escaped(markup_str,
                                                    sheeple_group_get_name
                                                    (group));

            gtk_label_set_markup(GTK_LABEL(group->_label), button_markup);
        }
        while ((group_list = g_list_next(group_list)));
    }
    while ((sources = g_list_next(sources)));
}

static void _sheeple_source_view_remove_source_vbox_subview(GtkWidget * self,
                                                            gpointer child)
{
    /* this seems entirely wrong */
    gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(self)), self);
}

static void _sheeple_source_view_select(GtkButton * button, gpointer user_data)
{
    SheepleSourceViewSelectPrivateData *private =
        (SheepleSourceViewSelectPrivateData *) user_data;
    private->source_view->priv->selected_groups =
        g_list_prepend(NULL, private->group);
    _sheeple_source_view_update_selection(private->source_view);
}

void sheeple_source_view_set_sources(SheepleSourceView * self,
                                     GList * new_sources)
{
    self->priv->sources = new_sources;

    gtk_container_foreach(GTK_CONTAINER(self->priv->source_vbox),
                          &_sheeple_source_view_remove_source_vbox_subview,
                          NULL);

    // Iterate over all sources, creating a section (and buttons) for each
    do
    {
        SheepleSource *source = ((SheepleSource *) new_sources->data);

        GtkWidget *sourcebox, *title_label;
        gchar *title_markup;
        GList *group_list = sheeple_source_get_groups(source);

        sourcebox = gtk_vbox_new(FALSE, 0);

        // Create the source's title label
        title_markup = g_markup_printf_escaped("<small><b>%s</b></small>",
                                               sheeple_source_get_name(source));
        title_label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
        gtk_misc_set_alignment(GTK_MISC(title_label), 0, 0);
        gtk_box_pack_start(GTK_BOX(sourcebox), title_label, TRUE, TRUE, 4);

        // Iterate over all groups within this source, creating
        // selection buttons for each group and packing them
        do
        {
            SheepleSourceViewSelectPrivateData *cb_data = NULL;
            SheepleGroup *group = ((SheepleGroup *) group_list->data);

            GtkWidget *button, *alignment, *button_label;
            gchar *button_markup;

            alignment = gtk_alignment_new(0, 0, 0, 0);
            gtk_alignment_set_padding(GTK_ALIGNMENT(alignment), 0, 0, 20, 4);

            button_markup = g_markup_printf_escaped("<small>%s</small>",
                                                    sheeple_group_get_name
                                                    (group));

            button_label = gtk_label_new(NULL);
            gtk_label_set_markup(GTK_LABEL(button_label), button_markup);

            button = gtk_button_new();
            gtk_container_add(GTK_CONTAINER(button), button_label);
            gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
            gtk_button_set_focus_on_click(GTK_BUTTON(button), FALSE);

            cb_data =
                (SheepleSourceViewSelectPrivateData *) calloc(1,
                                                              sizeof
                                                              (SheepleSourceViewSelectPrivateData));
            cb_data->group = group;
            cb_data->source_view = self;

            g_signal_connect(button, "clicked",
                             G_CALLBACK(_sheeple_source_view_select), cb_data);

            gtk_container_add(GTK_CONTAINER(alignment), button);
            gtk_box_pack_start(GTK_BOX(sourcebox), alignment, TRUE, TRUE, 0);

            group->_button = button;
            group->_label = button_label;
        }
        while ((group_list = g_list_next(group_list)));

        gtk_box_pack_start(GTK_BOX(self->priv->source_vbox), sourcebox, FALSE, TRUE,
                           0);

        source->_box = sourcebox;
    }
    while ((new_sources = g_list_next(new_sources)));

    // select first group. this will eventually have to change
    // (what if the first source has no groups!?)
    self->priv->selected_groups = g_list_prepend(NULL,
                                           (sheeple_source_get_groups
                                            ((SheepleSource *) self->priv->sources->
                                             data)->data));

    _sheeple_source_view_update_selection(self);
}
