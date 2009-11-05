#include <glib.h>

#include "SheepleEDSBackendGroup.h"
#include "SheepleEDSContact.h"
#include "sheeple.h"

static void sheeple_eds_backend_group_interface_init (SheepleBackendGroupIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleEDSBackendGroup, sheeple_eds_backend_group, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_BACKEND,
                                                sheeple_eds_backend_group_interface_init));

enum
{
    PROP_0,
    
    PROP_SOURCE
};

static char *
sheeple_eds_backend_group_get_group_id (SheepleBackendGroup *self)
{
    return strdup("some-group"); // TODO: implement!
}

static SheepleContact *
sheeple_eds_backend_group_get_contact (SheepleBackendGroup *self, const char *id)
{
    SheepleEDSBackendGroup * backend = SHEEPLE_EDS_BACKEND_GROUP(self);
    EContact * econtact;
    e_book_get_contact(backend->ebook, id, &econtact, NULL);
    return SHEEPLE_CONTACT(sheeple_eds_contact_new(econtact));
}

static void sheeple_eds_backend_start (SheepleEDSBackendGroup *self)
{
    e_book_view_start(self->ebookview);
}

static void
sheeple_eds_backend_group_interface_init (SheepleBackendGroupIface *iface)
{
    iface->get_group_id = sheeple_eds_backend_group_get_group_id;
    iface->get_contact = sheeple_eds_backend_group_get_contact;
    iface->start = sheeple_eds_backend_start;
}

static void contacts_added_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    GList *list = (GList*)added, *elem;
    EContact * contact;

    for(elem = list; elem; elem = elem->next)
    {
        contact = elem->data;
        g_signal_emit_by_name(self, "contact-added",
                              e_contact_get(contact, E_CONTACT_UID), NULL);
    }
}

static void contacts_changed_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    GList *list = (GList*)added, *elem;
    EContact * contact;

    for(elem = list; elem; elem = elem->next)
    {
        contact = elem->data;
        g_signal_emit_by_name(self, "contact-changed",
                              e_contact_get(contact, E_CONTACT_UID), NULL);
    }
}

static void contacts_removed_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    GList *list = (GList*)added, *elem;
    EContact * contact;

    for(elem = list; elem; elem = elem->next)
    {
        contact = elem->data;
        g_signal_emit_by_name(self, "contact-removed",
                              e_contact_get(contact, E_CONTACT_UID), NULL);
    }
}

static void sequence_complete_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    g_signal_emit_by_name(self, "ready", NULL);
}

static void
sheeple_eds_backend_group_set_property (GObject *object, guint property_id,
                                        const GValue *value, GParamSpec *pspec)
{
    SheepleEDSBackendGroup *self = SHEEPLE_EDS_BACKEND_GROUP(object);

    switch (property_id)
    {
    case PROP_SOURCE:
        //TODO: g_free (self->priv->name);
        self->source = g_value_get_object(value);
        break;

    default:
        /* We don't have any other property... */
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
sheeple_eds_backend_group_get_property (GObject *object, guint property_id,
                                        GValue *value, GParamSpec *pspec)
{
    SheepleEDSBackendGroup *self = SHEEPLE_EDS_BACKEND_GROUP(object);

    switch (property_id)
    {
    case PROP_SOURCE:
        g_value_set_object (value, self->source);
        break;
    default:
        /* We don't have any other property... */
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
sheeple_eds_backend_group_init (SheepleEDSBackendGroup *self)
{
    self->ebook = e_book_new(self->source, NULL); // TODO: error
    e_book_open(self->ebook, FALSE, NULL);
    
    EBookQuery * q = e_book_query_any_field_contains("");
    
    e_book_get_book_view(self->ebook, q, NULL, 0, &(self->ebookview), NULL);
    g_signal_connect(self->ebookview, "contacts-added", G_CALLBACK(contacts_added_handler), self);
    g_signal_connect(self->ebookview, "contacts-changed", G_CALLBACK(contacts_changed_handler), self);
    g_signal_connect(self->ebookview, "contacts-removed", G_CALLBACK(contacts_removed_handler), self);
    g_signal_connect(self->ebookview, "sequence-complete", G_CALLBACK(sequence_complete_handler), self);
}

static void
sheeple_eds_backend_group_class_init (SheepleEDSBackendGroupClass *self)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (self);
    GParamSpec *pspec;
    gobject_class->set_property = sheeple_eds_backend_group_set_property;
    gobject_class->get_property = sheeple_eds_backend_group_get_property;

    pspec = g_param_spec_object ("source",
                                 "ESource of BackendGroup",
                                 "Represented ESource",
                                 E_TYPE_SOURCE,
                                 G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
    g_object_class_install_property (gobject_class, PROP_SOURCE, pspec);
}

SheepleEDSBackendGroup *
sheeple_eds_backend_group_new (ESource * src)
{
    return g_object_new(TYPE_SHEEPLE_EDS_BACKEND_GROUP, "source", src, NULL);
}

