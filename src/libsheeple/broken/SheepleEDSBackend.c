#include <glib.h>

#include "SheepleEDSBackend.h"
#include "SheepleEDSBackendGroup.h"
#include "SheepleEDSContact.h"
#include "sheeple.h"

static void sheeple_eds_backend_interface_init (SheepleBackendIface *iface);

G_DEFINE_TYPE_WITH_CODE (SheepleEDSBackend, sheeple_eds_backend, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (TYPE_SHEEPLE_BACKEND,
                                                sheeple_eds_backend_interface_init));

static char *
sheeple_eds_backend_get_db_id (SheepleBackend *self)
{
    return strdup("Evolution");
}

static void
sheeple_eds_backend_start (SheepleBackend *self)
{
    SheepleEDSBackend * backend = SHEEPLE_EDS_BACKEND(self);
    GSList *groups = e_source_list_peek_groups(backend->source_list);
    GSList *elem;
    ESourceGroup *group;
    
    for(elem = groups; elem; elem = elem->next)
    {
        group = elem->data;
        
        GSList *sources = e_source_group_peek_sources(group);
        GSList *source_elem;
        ESource *source;
        
        for(source_elem = sources; source_elem; source_elem = source_elem->next)
        {
            source = source_elem->data;
            
            EBook * book = e_book_new(source, NULL);
            if(!book) // don't throw groups for non-addressbook sources
                continue;
            
            g_print("%s\n", e_source_peek_name(source));
            
            g_signal_emit_by_name(backend, "group-added",
                                  e_source_peek_uid(source), NULL);
        }
    }
    
    g_signal_emit_by_name(backend, "ready", NULL);
}

static SheepleGroup *
sheeple_eds_backend_get_group (SheepleBackend *self, const char *id)
{
    SheepleEDSBackend *backend = SHEEPLE_EDS_BACKEND(self);
    
    ESource *src = e_source_list_peek_source_by_uid(backend->source_list, id);
    
    SheepleEDSBackendGroup *backend_group = sheeple_eds_backend_group_new();
    sheeple_eds_backend_group_set_esource(backend_group, src);
    
    SheepleGroup *grp = sheeple_group_new(e_source_peek_name(src), SHEEPLE_BACKEND_GROUP(backend_group));
    
    return grp;
}

static void
sheeple_eds_backend_interface_init (SheepleBackendIface *iface)
{
    iface->get_db_id = sheeple_eds_backend_get_db_id;
    iface->get_group = sheeple_eds_backend_get_group;
    iface->start = sheeple_eds_backend_start;
}

void group_added_handler (EBookView *ebookview, gpointer added, gpointer self)
{
    g_signal_emit_by_name(self, "group-added", e_source_peek_uid(E_SOURCE(added)), NULL);
}

void group_removed_handler (EBookView *ebookview, gpointer removed, gpointer self)
{
    g_signal_emit_by_name(self, "group-removed", e_source_peek_uid(E_SOURCE(removed)), NULL);
}

static void
sheeple_eds_backend_init (SheepleEDSBackend *self)
{
    e_book_get_addressbooks(&(self->source_list), NULL); // TODO: error

    // TODO: these signals seem to not be fired!?
    g_signal_connect(self->source_list, "group-added", G_CALLBACK(group_added_handler), self);
    g_signal_connect(self->source_list, "group-removed", G_CALLBACK(group_removed_handler), self);
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
