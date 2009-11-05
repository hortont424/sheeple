#include <glib.h>

#include "SheepleEDSBackend.h"
#include "SheepleEDSContact.h"
#include "sheeple.h"

static void sheeple_eds_backend_interface_init (SheepleBackendIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleEDSBackend, sheeple_eds_backend, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_BACKEND,
                                                sheeple_eds_backend_interface_init));

static char *
sheeple_eds_backend_get_db_id (SheepleBackend *self)
{
    return "evolution-data-server";
}

static SheepleBackendGroup *
sheeple_eds_backend_get_group (SheepleBackend *self, const char *id)
{
    SheepleEDSBackend * backend = SHEEPLE_EDS_BACKEND(self);
    EContact * econtact;
    e_book_get_contact(backend->ebook, id, &econtact, NULL);
    return SHEEPLE_CONTACT(sheeple_eds_contact_new(econtact));
}

static void
sheeple_eds_backend_interface_init (SheepleBackendIface *iface)
{
    iface->get_db_id = sheeple_eds_backend_get_db_id;
    iface->get_group = sheeple_eds_backend_get_contact;
}

void contacts_added_handler (EBookView *ebookview, gpointer added, gpointer self)
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

void contacts_changed_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    /*GList *list = (GList*)added, *elem;
    EContact * contact;

    for(elem = list; elem; elem = elem->next)
    {
        contact = elem->data;
        g_signal_emit_by_name(self, "contact-changed",
                              e_contact_get(contact, E_CONTACT_UID), NULL);
    }*/
}

void contacts_removed_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    /*GList *list = (GList*)added, *elem;
    EContact * contact;

    for(elem = list; elem; elem = elem->next)
    {
        contact = elem->data;
        g_signal_emit_by_name(self, "contact-removed",
                              e_contact_get(contact, E_CONTACT_UID), NULL);
    }*/
}

void sequence_complete_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    g_signal_emit_by_name(self, "ready", NULL);
}

static void
sheeple_eds_backend_init (SheepleEDSBackend *self)
{
    self->ebook = e_book_new_default_addressbook(NULL);
    e_book_open(self->ebook, FALSE, NULL);
    
    EBookQuery * q = e_book_query_any_field_contains("");
    
    e_book_get_book_view(self->ebook, q, NULL, 0, &(self->ebookview), NULL);
    g_signal_connect(self->ebookview, "contacts-added", G_CALLBACK(contacts_added_handler), self);
    //g_signal_connect(self->ebookview, "contacts-changed", G_CALLBACK(contacts_changed_handler), self);
    //g_signal_connect(self->ebookview, "contacts-removed", G_CALLBACK(contacts_removed_handler), self);
    g_signal_connect(self->ebookview, "sequence-complete", G_CALLBACK(sequence_complete_handler), self);
    e_book_view_start(self->ebookview);
}

static void
sheeple_eds_backend_class_init (SheepleEDSBackendClass *self)
{
}

SheepleEDSBackend *
sheeple_eds_backend_new ()
{
    return g_object_new(TYPE_SHEEPLE_EDS_BACKEND, NULL);
}
