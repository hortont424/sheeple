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
  
  PROP_FULL_NAME,
  PROP_GIVEN_NAME,
  PROP_FAMILY_NAME,
  PROP_NICKNAME,
  
  PROP_EMAIL,
  PROP_PHONE
};

void sheeple_eds_contact_set_econtact(SheepleEDSContact *self, EContact *ec)
{
    self->priv->econtact = ec;
}

EContact * sheeple_eds_contact_get_econtact(SheepleEDSContact *self)
{
    return self->priv->econtact;
}

#define INSTALL_EDS_GETSETTERS(smallpropname) \
    iface->set_ ## smallpropname = &sheeple_eds_contact_set_ ## smallpropname; \
    iface->get_ ## smallpropname = &sheeple_eds_contact_get_ ## smallpropname;

#define INSTALL_EDS_PROP(propname, propstring) \
    g_object_class_override_property (gobject_class, PROP_ ## propname, propstring);

#define DEFINE_EDS_GETSETTERS(typename, propname, smallpropname) \
    void sheeple_eds_contact_set_ ## smallpropname (SheepleContact *self, typename prop) \
        { e_contact_set(SHEEPLE_EDS_CONTACT(self)->priv->econtact, E_CONTACT_ ## propname, prop); } \
    typename sheeple_eds_contact_get_ ## smallpropname (SheepleContact *self) \
        { e_contact_get(SHEEPLE_EDS_CONTACT(self)->priv->econtact, E_CONTACT_ ## propname); }

#define DEFINE_EDS_SETPROP(type, propname, smallpropname) \
    case PROP_ ## propname :\
        sheeple_eds_contact_set_ ## smallpropname (SHEEPLE_CONTACT(self), g_value_get_ ## type (value)); \
        break;

#define DEFINE_EDS_GETPROP(type, propname, smallpropname) \
    case PROP_ ## propname: \
        g_value_set_ ## type (value, sheeple_eds_contact_get_ ## smallpropname (SHEEPLE_CONTACT(self))); \
        break;

DEFINE_EDS_GETSETTERS(const gchar *, FULL_NAME, full_name);
DEFINE_EDS_GETSETTERS(const gchar *, GIVEN_NAME, given_name);
DEFINE_EDS_GETSETTERS(const gchar *, FAMILY_NAME, family_name);
DEFINE_EDS_GETSETTERS(const gchar *, NICKNAME, nickname);
DEFINE_EDS_GETSETTERS(GList *, EMAIL, email);
//DEFINE_EDS_GETSETTERS(GList *, PHONE, phone);

// TODO: DEFINE_EDS_GETSETTERS_PROP macros

void sheeple_eds_contact_set_phone(SheepleContact *self, GList * prop)
{
    //e_contact_set(SHEEPLE_EDS_CONTACT(self)->priv->econtact, E_CONTACT_PHONE, prop);
}

GList * sheeple_eds_contact_get_phone(SheepleContact * self)
{
    GList * phones = NULL;
    EVCard * vcard = E_VCARD(SHEEPLE_EDS_CONTACT(self)->priv->econtact);
    GList * attrs = e_vcard_get_attributes(vcard);
    
    for(; attrs; attrs = attrs->next)
    {
        EVCardAttribute * attr = (EVCardAttribute*)attrs->data;
        
        if(g_strcmp0(e_vcard_attribute_get_name(attr), EVC_TEL) == 0)
        {
            EVCardAttributeParam * param = e_vcard_attribute_get_param(attr, "type");
            const gchar * type = e_vcard_attribute_param_get_name(param);
            const gchar * value = e_vcard_attribute_get_value(attr);
            
            SheepleContactPhone * phone_num = sheeple_contact_phone_new();
            sheeple_contact_phone_set_label(phone_num, type);
            sheeple_contact_phone_set_number(phone_num, value);
            
            phones = g_list_prepend(phones, phone_num);
        }
    }

    return phones;
}


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
        
        DEFINE_EDS_SETPROP(string, FULL_NAME, full_name)
        DEFINE_EDS_SETPROP(string, GIVEN_NAME, given_name)
        DEFINE_EDS_SETPROP(string, FAMILY_NAME, family_name)
        DEFINE_EDS_SETPROP(string, NICKNAME, nickname)
        
        DEFINE_EDS_SETPROP(object, EMAIL, email)
        DEFINE_EDS_SETPROP(object, PHONE, phone)
        
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
        
        DEFINE_EDS_GETPROP(string, FULL_NAME, full_name)
        DEFINE_EDS_GETPROP(string, GIVEN_NAME, given_name)
        DEFINE_EDS_GETPROP(string, FAMILY_NAME, family_name)
        DEFINE_EDS_GETPROP(string, NICKNAME, nickname)
        
        DEFINE_EDS_GETPROP(object, EMAIL, email)
        DEFINE_EDS_GETPROP(object, PHONE, phone)
        
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
    
    INSTALL_EDS_PROP(FULL_NAME, "full-name");
    INSTALL_EDS_PROP(GIVEN_NAME, "given-name");
    INSTALL_EDS_PROP(FAMILY_NAME, "family-name");
    INSTALL_EDS_PROP(NICKNAME, "nickname");
    
    INSTALL_EDS_PROP(EMAIL, "email");
    INSTALL_EDS_PROP(PHONE, "phone");
}

SheepleEDSContact *
sheeple_eds_contact_new (EContact * contact)
{
    return g_object_new(TYPE_SHEEPLE_EDS_CONTACT, "econtact", contact, NULL);
}

static void
sheeple_eds_contact_interface_init (SheepleContactIface *iface)
{
    INSTALL_EDS_GETSETTERS(full_name);
    INSTALL_EDS_GETSETTERS(given_name);
    INSTALL_EDS_GETSETTERS(family_name);
    INSTALL_EDS_GETSETTERS(nickname);
    
    INSTALL_EDS_GETSETTERS(email);
    INSTALL_EDS_GETSETTERS(phone);
}
