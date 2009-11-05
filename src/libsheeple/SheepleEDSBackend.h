#ifndef __SHEEPLE_EDS_BACKEND_H__
#define __SHEEPLE_EDS_BACKEND_H__

#include <glib-object.h>
#include <libebook/e-book.h>

#define TYPE_SHEEPLE_EDS_BACKEND             (sheeple_eds_backend_get_type ())
#define SHEEPLE_EDS_BACKEND(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_EDS_BACKEND, SheepleEDSBackend))
#define IS_SHEEPLE_EDS_BACKEND(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_EDS_BACKEND))
#define SHEEPLE_EDS_BACKEND_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_EDS_BACKEND, SheepleEDSBackendClass))
#define IS_SHEEPLE_EDS_BACKEND_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_EDS_BACKEND))
#define SHEEPLE_EDS_BACKEND_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_EDS_BACKEND, SheepleEDSBackendClass))


typedef struct _SheepleEDSBackend        SheepleEDSBackend;
typedef struct _SheepleEDSBackendClass   SheepleEDSBackendClass;

struct _SheepleEDSBackend
{
    GObject parent_instance;
    
    EBook * ebook;
    EBookView * ebookview;
};

struct _SheepleEDSBackendClass
{
    GObjectClass parent_class;
};

SheepleEDSBackend * sheeple_eds_backend_new ();
GType sheeple_eds_backend_get_type (void);

#endif
