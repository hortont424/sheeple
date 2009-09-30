#ifndef _SHEEPLE_SOURCE_VIEW_CELL_RENDERER_H_
#define _SHEEPLE_SOURCE_VIEW_CELL_RENDERER_H_

#include <gtk/gtk.h>

#define SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER (sheeple_source_view_cell_renderer_get_type())
#define SHEEPLE_SOURCE_VIEW_CELL_RENDERER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),  SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER, SheepleSourceViewCellRenderer))
#define SHEEPLE_SOURCE_VIEW_CELL_RENDERER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass),  SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER, SheepleSourceViewCellRendererClass))
#define SHEEPLE_SOURCE_VIEW_IS_CELL_RENDERER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER))
#define SHEEPLE_SOURCE_VIEW_IS_CELL_RENDERER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER))
#define CUSTOM_CELL_RENDERER_PROGRESS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj),  SHEEPLE_SOURCE_VIEW_TYPE_CELL_RENDERER, SheepleSourceViewCellRendererClass))

typedef struct _SheepleSourceViewCellRenderer SheepleSourceViewCellRenderer;
typedef struct _SheepleSourceViewCellRendererClass
	SheepleSourceViewCellRendererClass;

/* CustomCellRendererProgress: Our custom cell renderer
*   structure. Extend according to need */

struct _SheepleSourceViewCellRenderer {
	GtkCellRenderer parent;
	gdouble progress;
};

struct _SheepleSourceViewCellRendererClass {
	GtkCellRendererClass parent_class;
};

GType sheeple_source_view_cell_renderer_get_type(void);

GtkCellRenderer *sheeple_source_view_cell_renderer_new(void);

#endif							// _SHEEPLE_SOURCE_VIEW_CELL_RENDERER_H_
