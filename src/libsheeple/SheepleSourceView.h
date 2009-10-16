#ifndef _SHEEPLE_SOURCE_VIEW_H_
#define _SHEEPLE_SOURCE_VIEW_H_

#include <gtk/gtk.h>
#include <libsheeple/sheeple.h>

#define SHEEPLE_TYPE_SOURCE_VIEW             (sheeple_source_view_get_type())
#define SHEEPLE_SOURCE_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceView))
#define SHEEPLE_IS_SOURCE_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), SHEEPLE_TYPE_SOURCE_VIEW))
#define SHEEPLE_SOURCE_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceViewClass))
#define SHEEPLE_IS_SOURCE_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), SHEEPLE_TYPE_SOURCE_VIEW))
#define SHEEPLE_SOURCE_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceViewClass))
#define SHEEPLE_SOURCE_VIEW_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceViewPrivate))

typedef struct _SheepleSourceView SheepleSourceView;
typedef struct _SheepleSourceViewClass SheepleSourceViewClass;
typedef struct _SheepleSourceViewPrivate SheepleSourceViewPrivate;

struct _SheepleSourceView
{
    GtkScrolledWindow parent_instance;

    SheepleSourceViewPrivate *priv;
};

struct _SheepleSourceViewClass
{
    GtkScrolledWindowClass parent_class;

    // Class members
};

GType sheeple_source_view_get_type(void);

GtkWidget *sheeple_source_view_new();

void sheeple_source_view_set_sources(SheepleSourceView * self,
                                     GList * new_sources);

#endif
