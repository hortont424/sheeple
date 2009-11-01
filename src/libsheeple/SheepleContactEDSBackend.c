#include <glib.h>

#include "SheepleContactEDSBackend.h"
#include "sheeple.h"

static void sheeple_contact_eds_backend_interface_init (SheepleContactBackendIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleContactEDSBackend, sheeple_contact_eds_backend, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_CONTACT_BACKEND,
                                                sheeple_contact_eds_backend_interface_init));

static char *
sheeple_contact_eds_backend_get_db_id (SheepleContactBackend *self)
{
    g_print ("do something");
    return "EDS";
}

static void
sheeple_contact_eds_backend_interface_init (SheepleContactBackendIface *iface)
{
    iface->get_db_id = sheeple_contact_eds_backend_get_db_id;
}

static void
sheeple_contact_eds_backend_init (SheepleContactEDSBackend *self)
{
}

static void
sheeple_contact_eds_backend_class_init (SheepleContactEDSBackendClass *self)
{
}

SheepleContactEDSBackend *
sheeple_contact_eds_backend_new ()
{
    return g_object_new(TYPE_SHEEPLE_CONTACT_EDS_BACKEND, NULL);
}
