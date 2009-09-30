#include "SheepleSourceViewCellRenderer.h"

/* This is based mainly on GtkCellRendererProgress
 *  in GAIM, written and (c) 2002 by Sean Egan
 *  (Licensed under the GPL), which in turn is
 *  based on Gtk's GtkCellRenderer[Text|Toggle|Pixbuf]
 *  implementation by Jonathan Blandford */

/* Some boring function declarations: GObject type system stuff */

static void sheeple_source_view_cell_renderer_init(SheepleSourceViewCellRenderer *
											   cellprogress);

static void sheeple_source_view_cell_renderer_class_init(SheepleSourceViewCellRendererClass *
										 klass);

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
												   gint * width, gint * height);

static void sheeple_source_view_cell_renderer_render(GtkCellRenderer * cell,
												 GdkWindow * window,
												 GtkWidget * widget,
												 GdkRectangle * background_area,
												 GdkRectangle * cell_area,
												 GdkRectangle * expose_area,
												 guint flags);

enum {
	PROP_PERCENTAGE = 1,
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
	static GType cell_progress_type = 0;

	if (cell_progress_type == 0)
	{
		static const GTypeInfo cell_progress_info = {
			sizeof(SheepleSourceViewCellRendererClass),
			NULL,				/* base_init */
			NULL,				/* base_finalize */
			(GClassInitFunc) sheeple_source_view_cell_renderer_class_init,
			NULL,				/* class_finalize */
			NULL,				/* class_data */
			sizeof(SheepleSourceViewCellRenderer),
			0,					/* n_preallocs */
			(GInstanceInitFunc) sheeple_source_view_cell_renderer_init,
		};

		/* Derive from GtkCellRenderer */
		cell_progress_type = g_type_register_static(GTK_TYPE_CELL_RENDERER,
													"SheepleSourceViewCellRenderer",
													&cell_progress_info, 0);
	}

	return cell_progress_type;
}

/***************************************************************************
 *
 *  sheeple_source_view_cell_renderer_init: set some default properties of the
 *                                      parent (GtkCellRenderer).
 *
 ***************************************************************************/

static void
sheeple_source_view_cell_renderer_init(SheepleSourceViewCellRenderer *
								   cellrendererprogress)
{
	GTK_CELL_RENDERER(cellrendererprogress)->mode =
		GTK_CELL_RENDERER_MODE_INERT;
	GTK_CELL_RENDERER(cellrendererprogress)->xpad = 2;
	GTK_CELL_RENDERER(cellrendererprogress)->ypad = 2;
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
sheeple_source_view_cell_renderer_class_init(SheepleSourceViewCellRendererClass *
										 klass)
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
									PROP_PERCENTAGE,
									g_param_spec_double("percentage",
														"Percentage",
														"The fractional progress to display",
														0, 1, 0,
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
	   SheepleSourceViewCellRenderer *cellrendererprogress = sheeple_source_view_cell_renderer(object);
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
										   GValue * value, GParamSpec * psec)
{
	SheepleSourceViewCellRenderer *cellprogress =
		SHEEPLE_SOURCE_VIEW_CELL_RENDERER(object);

	switch (param_id)
	{
	case PROP_PERCENTAGE:
		g_value_set_double(value, cellprogress->progress);
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
	SheepleSourceViewCellRenderer *cellprogress =
		SHEEPLE_SOURCE_VIEW_CELL_RENDERER(object);

	switch (param_id)
	{
	case PROP_PERCENTAGE:
		cellprogress->progress = g_value_get_double(value);
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

#define FIXED_WIDTH   100
#define FIXED_HEIGHT  10

static void
sheeple_source_view_cell_renderer_get_size(GtkCellRenderer * cell,
									   GtkWidget * widget,
									   GdkRectangle * cell_area,
									   gint * x_offset,
									   gint * y_offset,
									   gint * width, gint * height)
{
	gint calc_width;
	gint calc_height;

	calc_width = (gint) cell->xpad * 2 + FIXED_WIDTH;
	calc_height = (gint) cell->ypad * 2 + FIXED_HEIGHT;

	if (width)
		*width = calc_width;

	if (height)
		*height = calc_height;

	if (cell_area)
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
	}
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
									 GdkRectangle * expose_area, guint flags)
{
	SheepleSourceViewCellRenderer *cellprogress =
		SHEEPLE_SOURCE_VIEW_CELL_RENDERER(cell);
	GtkStateType state;
	gint width, height;
	gint x_offset, y_offset;

	sheeple_source_view_cell_renderer_get_size(cell, widget, cell_area,
										   &x_offset, &y_offset,
										   &width, &height);

	if (GTK_WIDGET_HAS_FOCUS(widget))
		state = GTK_STATE_ACTIVE;
	else
		state = GTK_STATE_NORMAL;

	width -= cell->xpad * 2;
	height -= cell->ypad * 2;

	gtk_paint_box(widget->style,
				  window,
				  GTK_STATE_NORMAL, GTK_SHADOW_IN,
				  NULL, widget, "trough",
				  cell_area->x + x_offset + cell->xpad,
				  cell_area->y + y_offset + cell->ypad, width - 1, height - 1);

	gtk_paint_box(widget->style,
				  window,
				  state, GTK_SHADOW_OUT,
				  NULL, widget, "bar",
				  cell_area->x + x_offset + cell->xpad,
				  cell_area->y + y_offset + cell->ypad,
				  width * cellprogress->progress, height - 1);
}
