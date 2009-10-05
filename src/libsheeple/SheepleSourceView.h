#ifndef _SHEEPLE_SOURCE_VIEW_H_
#define _SHEEPLE_SOURCE_VIEW_H_

#include <gtk/gtk.h>

#define SHEEPLE_TYPE_SOURCE_VIEW             (sheeple_source_view_get_type())
#define SHEEPLE_SOURCE_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceView))
#define SHEEPLE_IS_SOURCE_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), SHEEPLE_TYPE_SOURCE_VIEW))
#define SHEEPLE_SOURCE_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceViewClass))
#define SHEEPLE_IS_SOURCE_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), SHEEPLE_TYPE_SOURCE_VIEW))
#define SHEEPLE_SOURCE_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), SHEEPLE_TYPE_SOURCE_VIEW, SheepleSourceViewClass))

typedef struct _SheepleSourceView SheepleSourceView;
typedef struct _SheepleSourceViewClass SheepleSourceViewClass;

struct _SheepleSourceView {
    GObject parent_instance;

    // Instance members
};

struct _SheepleSourceViewClass {
    GObjectClass parent_class;

    // Class members
};

GType sheeple_source_view_get_type(void);

SheepleSourceView *sheeple_source_view_new();

#endif
