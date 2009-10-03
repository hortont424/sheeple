#ifndef _SHEEPLE_SOURCE_H_
#define _SHEEPLE_SOURCE_H_

#include <gtk/gtk.h>

#define SHEEPLE_TYPE_SOURCE             (sheeple_source_get_type())
#define SHEEPLE_SOURCE(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), SHEEPLE_TYPE_SOURCE, SheepleSource))
#define SHEEPLE_IS_SOURCE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), SHEEPLE_TYPE_SOURCE))
#define SHEEPLE_SOURCE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), SHEEPLE_TYPE_SOURCE, SheepleSourceClass))
#define SHEEPLE_IS_SOURCE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), SHEEPLE_TYPE_SOURCE))
#define SHEEPLE_SOURCE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), SHEEPLE_TYPE_SOURCE, SheepleSourceClass))

typedef struct _SheepleSource SheepleSource;
typedef struct _SheepleSourceClass SheepleSourceClass;

struct _SheepleSource
{
    GObject parent_instance;
    
    // Instance members
    
    const gchar * name;
    GList * groups;
    
    GtkWidget * _box;
};

struct _SheepleSourceClass
{
    GObjectClass parent_class;
    
    // Class members
};

GType sheeple_source_get_type(void);

SheepleSource * sheeple_source_new();
SheepleSource * sheeple_source_new_with_name(const gchar * name);

#endif
