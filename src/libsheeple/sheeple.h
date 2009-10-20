
#ifndef __SRC_LIBSHEEPLE_SHEEPLE_H__
#define __SRC_LIBSHEEPLE_SHEEPLE_H__

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gdk-pixbuf/gdk-pixdata.h>

G_BEGIN_DECLS


#define TYPE_SHEEPLE_GROUP (sheeple_group_get_type ())
#define SHEEPLE_GROUP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_GROUP, SheepleGroup))
#define SHEEPLE_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_GROUP, SheepleGroupClass))
#define IS_SHEEPLE_GROUP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_GROUP))
#define IS_SHEEPLE_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_GROUP))
#define SHEEPLE_GROUP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_GROUP, SheepleGroupClass))

typedef struct _SheepleGroup SheepleGroup;
typedef struct _SheepleGroupClass SheepleGroupClass;
typedef struct _SheepleGroupPrivate SheepleGroupPrivate;

struct _SheepleGroup {
	GObject parent_instance;
	SheepleGroupPrivate * priv;
	char* name;
	GdkPixbuf* icon;
};

struct _SheepleGroupClass {
	GObjectClass parent_class;
};


GType sheeple_group_get_type (void);
SheepleGroup* sheeple_group_new (void);
SheepleGroup* sheeple_group_construct (GType object_type);
SheepleGroup* sheeple_group_new_with_name (const char* name);
SheepleGroup* sheeple_group_construct_with_name (GType object_type, const char* name);
SheepleGroup* sheeple_group_new_with_name_and_icon (const char* name, GdkPixbuf* icon);
SheepleGroup* sheeple_group_construct_with_name_and_icon (GType object_type, const char* name, GdkPixbuf* icon);


G_END_DECLS

#endif
