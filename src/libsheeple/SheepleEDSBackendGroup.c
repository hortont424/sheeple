#include <glib.h>

#include "SheepleEDSBackendGroup.h"
#include "SheepleEDSContact.h"
#include "sheeple.h"

static void sheeple_eds_backend_group_interface_init (SheepleBackendGroupIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleEDSBackendGroup, sheeple_eds_backend_group, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_BACKEND_GROUP,
                                                sheeple_eds_backend_group_interface_init));

static char *
sheeple_eds_backend_group_get_group_id (SheepleBackendGroup *self)
{
    SheepleEDSBackendGroup * backend = SHEEPLE_EDS_BACKEND_GROUP(self);
    return e_source_peek_uid(backend->source);
}

static SheepleContact *
sheeple_eds_backend_group_get_contact (SheepleBackendGroup *self, const char *id)
{
    SheepleEDSBackendGroup * backend = SHEEPLE_EDS_BACKEND_GROUP(self);
    EContact * econtact;
    e_book_get_contact(backend->ebook, id, &econtact, NULL);
    return SHEEPLE_CONTACT(sheeple_eds_contact_new(econtact));
}

static void sheeple_eds_backend_group_start (SheepleEDSBackendGroup *self)
{
    e_book_view_start(self->ebookview);
}

static void
sheeple_eds_backend_group_interface_init (SheepleBackendGroupIface *iface)
{
    iface->get_group_id = sheeple_eds_backend_group_get_group_id;
    iface->get_contact = sheeple_eds_backend_group_get_contact;
    iface->start = sheeple_eds_backend_group_start;
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
sheeple_eds_backend_group_init (SheepleEDSBackendGroup *self)
{
}

static void
sheeple_eds_backend_group_class_init (SheepleEDSBackendGroupClass *self)
{
}

SheepleEDSBackendGroup *
sheeple_eds_backend_group_new ()
{
    return g_object_new(TYPE_SHEEPLE_EDS_BACKEND_GROUP, NULL);
}

// TODO: this is disgusting, why can't it be a construct property
void sheeple_eds_backend_group_set_esource(SheepleEDSBackendGroup *self, ESource *src)
{
    self->source = src;
    self->ebook = e_book_new(self->source, NULL); // TODO: error
    e_book_open(self->ebook, FALSE, NULL);
    
    EBookQuery * q = e_book_query_any_field_contains("");
    
    e_book_get_book_view(self->ebook, q, NULL, 0, &(self->ebookview), NULL);
    g_signal_connect(self->ebookview, "contacts-added", G_CALLBACK(contacts_added_handler), self);
    g_signal_connect(self->ebookview, "contacts-changed", G_CALLBACK(contacts_changed_handler), self);
    g_signal_connect(self->ebookview, "contacts-removed", G_CALLBACK(contacts_removed_handler), self);
    g_signal_connect(self->ebookview, "sequence-complete", G_CALLBACK(sequence_complete_handler), self);
}

