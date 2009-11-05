#ifndef __SHEEPLE_EDS_BACKEND_GROUP_H__
#define __SHEEPLE_EDS_BACKEND_GROUP_H__

#include <glib-object.h>
#include <libebook/e-book.h>

#define TYPE_SHEEPLE_EDS_BACKEND_GROUP             (sheeple_eds_backend_group_get_type ())
#define SHEEPLE_EDS_BACKEND_GROUP(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_EDS_BACKEND_GROUP, SheepleEDSBackendGroup))
#define IS_SHEEPLE_EDS_BACKEND_GROUP(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_EDS_BACKEND_GROUP))
#define SHEEPLE_EDS_BACKEND_GROUP_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_EDS_BACKEND_GROUP, SheepleEDSBackendGroupClass))
#define IS_SHEEPLE_EDS_BACKEND_GROUP_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_EDS_BACKEND_GROUP))
#define SHEEPLE_EDS_BACKEND_GROUP_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_EDS_BACKEND_GROUP, SheepleEDSBackendGroupClass))


typedef struct _SheepleEDSBackendGroup        SheepleEDSBackendGroup;
typedef struct _SheepleEDSBackendGroupClass   SheepleEDSBackendGroupClass;

struct _SheepleEDSBackendGroup
{
    GObject parent_instance;
    
    ESource *source;
    EBook *ebook;
    EBookView *ebookview;
};

struct _SheepleEDSBackendGroupClass
{
    GObjectClass parent_class;
};

SheepleEDSBackendGroup * sheeple_eds_backend_group_new ();
GType sheeple_eds_backend_group_get_type (void);

void sheeple_eds_backend_group_set_esource(SheepleEDSBackendGroup *self, ESource *src);

#endif
