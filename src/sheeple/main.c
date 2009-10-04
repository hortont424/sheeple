/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Tim Horton 2009 <hortont424@gmail.com>
 *
 * sheeple is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sheeple is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include <libsheeple/sheeple.h>

GList *all_sources = NULL;
GList *selected_groups = NULL;

void update_selection();

void choose_group(GtkButton * button, gpointer user_data)
{
    selected_groups = g_list_prepend(NULL, user_data);
    update_selection();
}

GtkWidget *create_source_view_test(GList * sources)
{
    GtkWidget *scrollbox, *layout, *master_vbox, *master_padding;

    scrollbox = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbox),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    layout = gtk_layout_new(NULL, NULL);
    master_vbox = gtk_vbox_new(FALSE, 10);

    // Iterate over all sources
    do
    {
        SheepleSource *source = ((SheepleSource *) sources->data);

        GtkWidget *sourcebox, *title_label;
        gchar *title_markup;
        GList *group_list = (GList *) (source->groups);

        sourcebox = gtk_vbox_new(FALSE, 0);

        // Create the source's title label
        title_markup = g_markup_printf_escaped("<small><b>%s</b></small>",
                                               source->name);
        title_label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
        gtk_misc_set_alignment(GTK_MISC(title_label), 0, 0);
        gtk_box_pack_start(GTK_BOX(sourcebox), title_label, TRUE, TRUE, 4);

        // Iterate over all groups within this source, creating
        // selection buttons for each group and packing them
        do
        {
            SheepleGroup *group = ((SheepleGroup *) group_list->data);

            GtkWidget *button, *alignment, *button_label;
            gchar *button_markup;

            alignment = gtk_alignment_new(0, 0, 0, 0);
            gtk_alignment_set_padding(GTK_ALIGNMENT(alignment), 0, 0, 20, 4);

            button_markup = g_markup_printf_escaped("<small>%s</small>",
                                                    (const gchar *)group->name);

            button_label = gtk_label_new(NULL);
            gtk_label_set_markup(GTK_LABEL(button_label), button_markup);

            button = gtk_button_new();
            gtk_container_add(GTK_CONTAINER(button), button_label);
            gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
            gtk_button_set_focus_on_click(GTK_BUTTON(button), FALSE);

            g_signal_connect(button, "clicked", G_CALLBACK(choose_group),
                             group);

            gtk_container_add(GTK_CONTAINER(alignment), button);
            gtk_box_pack_start(GTK_BOX(sourcebox), alignment, TRUE, TRUE, 0);

            group->_button = button;
            group->_label = button_label;
        }
        while ((group_list = g_list_next(group_list)));

        gtk_box_pack_start(GTK_BOX(master_vbox), sourcebox, FALSE, TRUE, 0);

        source->_box = sourcebox;
    }
    while ((sources = g_list_next(sources)));

    //gtk_layout_put(GTK_LAYOUT(layout), master_vbox, 0, 0);
    //gtk_container_add(GTK_CONTAINER(scrollbox), layout);

    // Pad the whole sourceview
    master_padding = gtk_alignment_new(0, 0, 1, 1);
    gtk_alignment_set_padding(GTK_ALIGNMENT(master_padding), 0, 0, 4, 4);
    gtk_container_add(GTK_CONTAINER(master_padding), master_vbox);

    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollbox),
                                        GTK_SHADOW_NONE);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbox),
                                          master_padding);
    gtk_widget_set_size_request(scrollbox, 150, -1);

    return scrollbox;
}

void update_selection()
{
    GList *sources = all_sources;

    do
    {
        SheepleSource *source = ((SheepleSource *) sources->data);
        GList *group_list = (GList *) (source->groups);

        do
        {
            SheepleGroup *group = ((SheepleGroup *) group_list->data);
            const gchar *button_markup, *markup_str;
            GtkReliefStyle new_style = GTK_RELIEF_NONE;

            if (g_list_find(selected_groups, group))
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
                                                    (const gchar *)group->name);

            gtk_label_set_markup(GTK_LABEL(group->_label), button_markup);
        }
        while ((group_list = g_list_next(group_list)));
    }
    while ((sources = g_list_next(sources)));
}

GList *create_default_sources()
{
    GList *sources = NULL;

    SheepleSource *sheeple_contacts, *sheeple_contacts_matt;

    GList *contacts_list = NULL, *matt_list = NULL;

    matt_list =
        g_list_prepend(matt_list, sheeple_group_new_with_name("Matt's Girls"));
    matt_list =
        g_list_prepend(matt_list, sheeple_group_new_with_name("Bus People"));

    contacts_list =
        g_list_prepend(contacts_list, sheeple_group_new_with_name("Family"));
    contacts_list =
        g_list_prepend(contacts_list, sheeple_group_new_with_name("RCOS"));
    contacts_list =
        g_list_prepend(contacts_list,
                       sheeple_group_new_with_name("RPI Friends"));

    sheeple_contacts = sheeple_source_new_with_name("Contacts");
    sheeple_contacts->groups = contacts_list;

    sheeple_contacts_matt = sheeple_source_new_with_name("Matt's Contacts");
    sheeple_contacts_matt->groups = matt_list;

    sources = g_list_prepend(sources, sheeple_contacts_matt);
    sources = g_list_prepend(sources, sheeple_contacts);

    selected_groups = g_list_prepend(selected_groups, contacts_list->data);

    return sources;
}

int main(int argc, char **argv)
{
    GtkWidget *window, *hbox, *textview;

    gtk_init(&argc, &argv);

    all_sources = create_default_sources();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    textview = gtk_text_view_new();

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), create_source_view_test(all_sources),
                       FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), textview, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), hbox);
    update_selection();

    gtk_widget_grab_focus(textview);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
