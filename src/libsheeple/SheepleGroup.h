#ifndef _SHEEPLE_GROUP_H_
#define _SHEEPLE_GROUP_H_

#include <gtk/gtk.h>

#define SHEEPLE_TYPE_GROUP             (sheeple_group_get_type())
#define SHEEPLE_GROUP(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), SHEEPLE_TYPE_GROUP, SheepleGroup))
#define SHEEPLE_IS_GROUP(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), SHEEPLE_TYPE_GROUP))
#define SHEEPLE_GROUP_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), SHEEPLE_TYPE_GROUP, SheepleGroupClass))
#define SHEEPLE_IS_GROUP_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), SHEEPLE_TYPE_GROUP))
#define SHEEPLE_GROUP_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), SHEEPLE_TYPE_GROUP, SheepleGroupClass))
#define SHEEPLE_GROUP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), SHEEPLE_TYPE_GROUP, SheepleGroupPrivate))

typedef struct _SheepleGroup SheepleGroup;
typedef struct _SheepleGroupClass SheepleGroupClass;
typedef struct _SheepleGroupPrivate SheepleGroupPrivate;

struct _SheepleGroup
{
    GObject parent_instance;

    // Instance members

    GtkWidget *_button, *_label;
    
    SheepleGroupPrivate * priv;
};

struct _SheepleGroupClass
{
    GObjectClass parent_class;

    // Class members
};

GType sheeple_group_get_type(void);

SheepleGroup *sheeple_group_new();
SheepleGroup *sheeple_group_new_with_name(const gchar * name);

const char *sheeple_group_get_name(SheepleGroup *self);
void sheeple_group_set_name(SheepleGroup *self, const char *name);

#endif
