#include <glib.h>

#include "SheepleEDSContact.h"
#include "sheeple.h"

struct _SheepleEDSContactPrivate {
    EContact * econtact;
};

enum
{
  PROP_0,

  PROP_ECONTACT,
  PROP_FULL_NAME
};

static void sheeple_eds_contact_interface_init (SheepleContactIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleEDSContact, sheeple_eds_contact, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_CONTACT,
                                                sheeple_eds_contact_interface_init));

static void
eds_contact_set_property (GObject *object,
                          guint property_id,
                          const GValue *value,
                          GParamSpec *pspec)
{
    SheepleEDSContact *self = SHEEPLE_EDS_CONTACT (object);

    switch (property_id)
    {
        case PROP_ECONTACT:
            if(self->priv->econtact)
                g_object_unref (self->priv->econtact);
            sheeple_eds_contact_set_econtact(self, g_value_get_object (value));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
eds_contact_get_property (GObject *object,
                          guint property_id,
                          GValue *value,
                          GParamSpec *pspec)
{
    SheepleEDSContact *self = SHEEPLE_EDS_CONTACT (object);

    switch (property_id)
    {
        case PROP_ECONTACT:
            g_value_set_object (value, sheeple_eds_contact_get_econtact(self));
            break;
        case PROP_FULL_NAME:
            g_value_set_string (value, sheeple_eds_contact_get_full_name(self));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
sheeple_eds_contact_init (SheepleEDSContact *self)
{
    self->priv = SHEEPLE_EDS_CONTACT_GET_PRIVATE (self);
    self->priv->econtact = NULL;
}

static void
sheeple_eds_contact_class_init (SheepleEDSContactClass *self)
{
    g_type_class_add_private (self, sizeof (SheepleEDSContactPrivate));

    GObjectClass *gobject_class = G_OBJECT_CLASS (self);
    GParamSpec *econtact_param_spec;

    gobject_class->set_property = eds_contact_set_property;
    gobject_class->get_property = eds_contact_get_property;

    econtact_param_spec = g_param_spec_object ("econtact",
        "Represented contact",
        "The EDS EContact represented by this SheepleContact",
        E_TYPE_CONTACT,
        G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
    g_object_class_install_property (gobject_class, PROP_ECONTACT,
                                     econtact_param_spec);
    
    g_object_class_override_property (gobject_class, PROP_FULL_NAME, "full-name");
}

EContact * sheeple_eds_contact_get_econtact(SheepleEDSContact *self)
{
    return self->priv->econtact;
}

void sheeple_eds_contact_set_econtact(SheepleEDSContact *self, EContact *ec)
{
    self->priv->econtact = ec;
}

char * sheeple_eds_contact_get_full_name(SheepleEDSContact *self)
{
    return e_contact_get(self->priv->econtact, E_CONTACT_FULL_NAME);
}

SheepleEDSContact *
sheeple_eds_contact_new (EContact * contact)
{
    return g_object_new(TYPE_SHEEPLE_EDS_CONTACT, "econtact", contact, NULL);
}

static void
sheeple_eds_contact_interface_init (SheepleContactIface *iface)
{
    iface->get_full_name = &sheeple_eds_contact_get_full_name;
}
