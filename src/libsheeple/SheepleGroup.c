
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gdk-pixbuf/gdk-pixdata.h>


#define TYPE_SHEEPLE_GROUP (sheeple_group_get_type ())
#define SHEEPLE_GROUP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_GROUP, SheepleGroup))
#define SHEEPLE_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_GROUP, SheepleGroupClass))
#define IS_SHEEPLE_GROUP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_GROUP))
#define IS_SHEEPLE_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_GROUP))
#define SHEEPLE_GROUP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_GROUP, SheepleGroupClass))

typedef struct _SheepleGroup SheepleGroup;
typedef struct _SheepleGroupClass SheepleGroupClass;
typedef struct _SheepleGroupPrivate SheepleGroupPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _SheepleGroup {
	GObject parent_instance;
	SheepleGroupPrivate * priv;
	char* name;
	GdkPixbuf* icon;
};

struct _SheepleGroupClass {
	GObjectClass parent_class;
};


static gpointer sheeple_group_parent_class = NULL;

GType sheeple_group_get_type (void);
enum  {
	SHEEPLE_GROUP_DUMMY_PROPERTY
};
SheepleGroup* sheeple_group_new (void);
SheepleGroup* sheeple_group_construct (GType object_type);
SheepleGroup* sheeple_group_new_with_name (const char* name);
SheepleGroup* sheeple_group_construct_with_name (GType object_type, const char* name);
SheepleGroup* sheeple_group_new_with_name_and_icon (const char* name, GdkPixbuf* icon);
SheepleGroup* sheeple_group_construct_with_name_and_icon (GType object_type, const char* name, GdkPixbuf* icon);
static void sheeple_group_finalize (GObject* obj);



SheepleGroup* sheeple_group_construct (GType object_type) {
	SheepleGroup * self;
	self = (SheepleGroup*) g_object_new (object_type, NULL);
	return self;
}


SheepleGroup* sheeple_group_new (void) {
	return sheeple_group_construct (TYPE_SHEEPLE_GROUP);
}


SheepleGroup* sheeple_group_construct_with_name (GType object_type, const char* name) {
	SheepleGroup * self;
	char* _tmp0_;
	g_return_val_if_fail (name != NULL, NULL);
	self = (SheepleGroup*) g_object_new (object_type, NULL);
	self->name = (_tmp0_ = g_strdup (name), _g_free0 (self->name), _tmp0_);
	return self;
}


SheepleGroup* sheeple_group_new_with_name (const char* name) {
	return sheeple_group_construct_with_name (TYPE_SHEEPLE_GROUP, name);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


SheepleGroup* sheeple_group_construct_with_name_and_icon (GType object_type, const char* name, GdkPixbuf* icon) {
	SheepleGroup * self;
	char* _tmp0_;
	GdkPixbuf* _tmp1_;
	g_return_val_if_fail (name != NULL, NULL);
	g_return_val_if_fail (icon != NULL, NULL);
	self = (SheepleGroup*) g_object_new (object_type, NULL);
	self->name = (_tmp0_ = g_strdup (name), _g_free0 (self->name), _tmp0_);
	self->icon = (_tmp1_ = _g_object_ref0 (icon), _g_object_unref0 (self->icon), _tmp1_);
	return self;
}


SheepleGroup* sheeple_group_new_with_name_and_icon (const char* name, GdkPixbuf* icon) {
	return sheeple_group_construct_with_name_and_icon (TYPE_SHEEPLE_GROUP, name, icon);
}


static void sheeple_group_class_init (SheepleGroupClass * klass) {
	sheeple_group_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = sheeple_group_finalize;
}


static void sheeple_group_instance_init (SheepleGroup * self) {
}


static void sheeple_group_finalize (GObject* obj) {
	SheepleGroup * self;
	self = SHEEPLE_GROUP (obj);
	_g_free0 (self->name);
	_g_object_unref0 (self->icon);
	G_OBJECT_CLASS (sheeple_group_parent_class)->finalize (obj);
}


GType sheeple_group_get_type (void) {
	static GType sheeple_group_type_id = 0;
	if (sheeple_group_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (SheepleGroupClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) sheeple_group_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SheepleGroup), 0, (GInstanceInitFunc) sheeple_group_instance_init, NULL };
		sheeple_group_type_id = g_type_register_static (G_TYPE_OBJECT, "SheepleGroup", &g_define_type_info, 0);
	}
	return sheeple_group_type_id;
}




