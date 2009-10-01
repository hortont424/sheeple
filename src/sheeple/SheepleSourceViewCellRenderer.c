#include "SheepleSourceViewCellRenderer.h"

/* This is based mainly on GtkCellRendererProgress
 *  in GAIM, written and (c) 2002 by Sean Egan
 *  (Licensed under the GPL), which in turn is
 *  based on Gtk's GtkCellRenderer[Text|Toggle|Pixbuf]
 *  implementation by Jonathan Blandford */

/* Some boring function declarations: GObject type system stuff */

static void sheeple_source_view_cell_renderer_init(SheepleSourceViewCellRenderer
                                                   * cell);

static void
sheeple_source_view_cell_renderer_class_init(SheepleSourceViewCellRendererClass
                                             * klass);

static void sheeple_source_view_cell_renderer_get_property(GObject * object,
                                                           guint param_id,
                                                           GValue * value,
                                                           GParamSpec * pspec);

static void sheeple_source_view_cell_renderer_set_property(GObject * object,
                                                           guint param_id,
                                                           const GValue * value,
                                                           GParamSpec * pspec);

static void sheeple_source_view_cell_renderer_finalize(GObject * gobject);

/* These functions are the heart of our custom cell renderer: */

static void sheeple_source_view_cell_renderer_get_size(GtkCellRenderer * cell,
                                                       GtkWidget * widget,
                                                       GdkRectangle * cell_area,
                                                       gint * x_offset,
                                                       gint * y_offset,
                                                       gint * width,
                                                       gint * height);

static void sheeple_source_view_cell_renderer_render(GtkCellRenderer * cell,
                                                     GdkWindow * window,
                                                     GtkWidget * widget,
                                                     GdkRectangle *
                                                     background_area,
                                                     GdkRectangle * cell_area,
                                                     GdkRectangle * expose_area,
                                                     guint flags);

enum {
    PROP_SOURCE = 1
};

static gpointer parent_class;

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_get_type: here we register our type with
 *                                          the GObject type system if we
 *                                          haven't done so yet. Everything
 *                                          else is done in the callbacks.
 *
 ***************************************************************************/

GType sheeple_source_view_cell_renderer_get_type(void)
{
    static GType cell_type = 0;

    if (cell_type == 0)
    {
        static const GTypeInfo cell_info = {
            sizeof(SheepleSourceViewCellRendererClass),
            NULL,               /* base_init */
            NULL,               /* base_finalize */
            (GClassInitFunc) sheeple_source_view_cell_renderer_class_init,
            NULL,               /* class_finalize */
            NULL,               /* class_data */
            sizeof(SheepleSourceViewCellRenderer),
            0,                  /* n_preallocs */
            (GInstanceInitFunc) sheeple_source_view_cell_renderer_init,
        };

        /* Derive from GtkCellRenderer */
        cell_type = g_type_register_static(GTK_TYPE_CELL_RENDERER,
                                                    "SheepleSourceViewCellRenderer",
                                                    &cell_info, 0);
    }

    return cell_type;
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_init: set some default properties of the
 *                                      parent (GtkCellRenderer).
 *
 ***************************************************************************/

static void
sheeple_source_view_cell_renderer_init(SheepleSourceViewCellRenderer *
                                       cellrenderer)
{
    GTK_CELL_RENDERER(cellrenderer)->mode = GTK_CELL_RENDERER_MODE_INERT;
    GTK_CELL_RENDERER(cellrenderer)->xpad = 2;
    GTK_CELL_RENDERER(cellrenderer)->ypad = 2;
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_class_init:
 *
 *  set up our own get_property and set_property functions, and
 *  override the parent's functions that we need to implement.
 *  And make our new "percentage" property known to the type system.
 *  If you want cells that can be activated on their own (ie. not
 *  just the whole row selected) or cells that are editable, you
 *  will need to override 'activate' and 'start_editing' as well.
 *
 ***************************************************************************/

static void
sheeple_source_view_cell_renderer_class_init(SheepleSourceViewCellRendererClass
                                             * klass)
{
    GtkCellRendererClass *cell_class = GTK_CELL_RENDERER_CLASS(klass);
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    parent_class = g_type_class_peek_parent(klass);
    object_class->finalize = sheeple_source_view_cell_renderer_finalize;

    /* Hook up functions to set and get our
     *   custom cell renderer properties */
    object_class->get_property = sheeple_source_view_cell_renderer_get_property;
    object_class->set_property = sheeple_source_view_cell_renderer_set_property;

    /* Override the two crucial functions that are the heart
     *   of a cell renderer in the parent class */
    cell_class->get_size = sheeple_source_view_cell_renderer_get_size;
    cell_class->render = sheeple_source_view_cell_renderer_render;

    /* Install our very own properties */
    g_object_class_install_property(object_class,
                                    PROP_SOURCE,
                                    g_param_spec_pointer("source",
                                                         "Source",
                                                         "The source",
                                                         G_PARAM_READWRITE));
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_finalize: free any resources here
 *
 ***************************************************************************/

static void sheeple_source_view_cell_renderer_finalize(GObject * object)
{
    /*
       SheepleSourceViewCellRenderer *cellrenderer = sheeple_source_view_cell_renderer(object);
     */

    /* Free any dynamically allocated resources here */

    (*G_OBJECT_CLASS(parent_class)->finalize) (object);
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_get_property: as it says
 *
 ***************************************************************************/

static void
sheeple_source_view_cell_renderer_get_property(GObject * object,
                                               guint param_id,
                                               GValue * value,
                                               GParamSpec * psec)
{
    SheepleSourceViewCellRenderer *cellrenderer =
        SHEEPLE_SOURCE_VIEW_CELL_RENDERER(object);

    switch (param_id)
    {
    case PROP_SOURCE:
        g_value_set_pointer(value, cellrenderer->source);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, psec);
        break;
    }
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_set_property: as it says
 *
 ***************************************************************************/

static void
sheeple_source_view_cell_renderer_set_property(GObject * object,
                                               guint param_id,
                                               const GValue * value,
                                               GParamSpec * pspec)
{
    SheepleSourceViewCellRenderer *cellrenderer =
        SHEEPLE_SOURCE_VIEW_CELL_RENDERER(object);

    switch (param_id)
    {
    case PROP_SOURCE:
        cellrenderer->source = g_value_get_pointer(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, pspec);
        break;
    }
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_new: return a new cell renderer instance
 *
 ***************************************************************************/

GtkCellRenderer *sheeple_source_view_cell_renderer_new(void)
{
    return g_object_new(SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER, NULL);
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_get_size: crucial - calculate the size
 *                                          of our cell, taking into account
 *                                          padding and alignment properties
 *                                          of parent.
 *
 ***************************************************************************/

#define TEXT_H_PAD      2
#define TEXT_V_PAD      2

static void
sheeple_source_view_cell_renderer_get_size(GtkCellRenderer * cell,
                                           GtkWidget * widget,
                                           GdkRectangle * cell_area,
                                           gint * x_offset,
                                           gint * y_offset,
                                           gint * width, gint * height)
{
    PangoLayout * layout;
    PangoFontDescription * font_description = NULL;
    SheepleSourceViewCellRenderer *cellrenderer =
        SHEEPLE_SOURCE_VIEW_CELL_RENDERER(cell);
    
    gint calc_width, calc_height, text_w, text_h;
    
    layout = gtk_widget_create_pango_layout(widget,
                                            ((SheepleSource*)(cellrenderer->source))->name);
    
    font_description = pango_font_description_copy(
        pango_layout_get_font_description(layout));
    
    if(!font_description)
        font_description = pango_font_description_new();
    
    if(((SheepleSource*)(cellrenderer->source))->toplevel ||
       ((SheepleSource*)(cellrenderer->source))->selected)
        pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);
    
    pango_font_description_set_size(font_description, 9 * PANGO_SCALE);
    
    pango_layout_set_font_description(layout, font_description);
    pango_layout_get_pixel_size(layout, &text_w, &text_h);

    calc_width = (gint) cell->xpad * 2 + text_w + TEXT_H_PAD * 2;
    calc_height = (gint) cell->ypad * 2 + text_h + TEXT_V_PAD * 2;

    if (width)
        *width = calc_width;

    if (height)
        *height = calc_height;

    /*if (cell_area)
    {
        if (x_offset)
        {
            *x_offset = cell->xalign * (cell_area->width - calc_width);
            *x_offset = MAX(*x_offset, 0);
        }

        if (y_offset)
        {
            *y_offset = cell->yalign * (cell_area->height - calc_height);
            *y_offset = MAX(*y_offset, 0);
        }
    }*/
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_render: crucial - do the rendering.
 *
 ***************************************************************************/
static void
sheeple_source_view_cell_renderer_render(GtkCellRenderer * cell,
                                         GdkWindow * window,
                                         GtkWidget * widget,
                                         GdkRectangle * background_area,
                                         GdkRectangle * cell_area,
                                         GdkRectangle * expose_area,
                                         guint flags)
{
    SheepleSourceViewCellRenderer *cellrenderer =
        SHEEPLE_SOURCE_VIEW_CELL_RENDERER(cell);
    
    GtkStateType state = GTK_STATE_NORMAL;
    gboolean draw_button = FALSE;
    gint width, height;
    gint x_offset, y_offset;
    PangoLayout * layout;
    PangoFontDescription * font_description = NULL;
    GdkGC * gc;
    GdkColor fg_color;

    sheeple_source_view_cell_renderer_get_size(cell, widget, cell_area,
                                               &x_offset, &y_offset,
                                               &width, &height);

    //width -= cell->xpad * 2;
    //height -= cell->ypad * 2;
    
    if(((SheepleSource*)(cellrenderer->source))->selected)
    {
        state = GTK_STATE_ACTIVE;
        draw_button = TRUE;
    }
    else
    {
        if (flags & GTK_CELL_RENDERER_PRELIT)
        {
            state = GTK_STATE_PRELIGHT;
            draw_button = TRUE;
        }
        else
            state = GTK_STATE_NORMAL;
    }
    
    if(!((SheepleSource*)(cellrenderer->source))->toplevel && draw_button)
    {
        gtk_paint_box(widget->style,
                      window,
                      state, GTK_SHADOW_IN,
                      NULL, widget, "buttondefault",
                      cell_area->x,
                      cell_area->y,
                      width, height);
        
        gtk_paint_box(widget->style,
                      window,
                      state, GTK_SHADOW_IN,
                      NULL, widget, "button",
                      cell_area->x,
                      cell_area->y,
                      width, height);
    }
    
    layout = gtk_widget_create_pango_layout(widget,
                                            ((SheepleSource*)(cellrenderer->source))->name);
    
    font_description = pango_font_description_copy(
        pango_layout_get_font_description(layout));
    
    if(!font_description)
        font_description = pango_font_description_new();
    
    if(((SheepleSource*)(cellrenderer->source))->toplevel ||
       ((SheepleSource*)(cellrenderer->source))->selected)
        pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);
    
    pango_font_description_set_size(font_description, 9 * PANGO_SCALE);
    
    
    gc = gdk_gc_new(window);
    pango_layout_set_font_description(layout, font_description);
    gdk_colormap_alloc_color(gdk_colormap_get_system(), &fg_color, TRUE, TRUE);
    gdk_color_parse("#404040", &fg_color);
    gdk_draw_layout_with_colors(window, gc, cell_area->x + cell->xpad + 2, cell_area->y + cell->ypad + 2, layout, &fg_color, NULL);
    pango_font_description_free(font_description);
    g_object_unref(layout);
    
    
    // http://git.gnome.org/cgit/gtk+/tree/gtk/gtkcellrenderertoggle.c
}

