#ifndef __SHEEPLE_CONTACT_EDS_BACKEND_H__
#define __SHEEPLE_CONTACT_EDS_BACKEND_H__

#include <glib-object.h>

#define TYPE_SHEEPLE_CONTACT_EDS_BACKEND             (sheeple_contact_eds_backend_get_type ())
#define SHEEPLE_CONTACT_EDS_BACKEND(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_CONTACT_EDS_BACKEND, SheepleContactEDSBackend))
#define IS_SHEEPLE_CONTACT_EDS_BACKEND(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_CONTACT_EDS_BACKEND))
#define SHEEPLE_CONTACT_EDS_BACKEND_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_CONTACT_EDS_BACKEND, SheepleContactEDSBackendClass))
#define IS_SHEEPLE_CONTACT_EDS_BACKEND_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_CONTACT_EDS_BACKEND))
#define SHEEPLE_CONTACT_EDS_BACKEND_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_CONTACT_EDS_BACKEND, SheepleContactEDSBackendClass))


typedef struct _SheepleContactEDSBackend        SheepleContactEDSBackend;
typedef struct _SheepleContactEDSBackendClass   SheepleContactEDSBackendClass;

struct _SheepleContactEDSBackend
{
  GObject parent_instance;

  int instance_member;
};

struct _SheepleContactEDSBackendClass
{
  GObjectClass parent_class;
};

SheepleContactEDSBackend * sheeple_contact_eds_backend_new ();
GType sheeple_contact_eds_backend_get_type (void);

#endif
