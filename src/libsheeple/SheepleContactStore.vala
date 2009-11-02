using GLib;

public class SheepleContactStoreBackendContact
{
    public string id;
    public string db_id;
}

public class SheepleContactStoreMetaContact
{
    public int refcount;
    public SheepleMetaContact metacontact;
    public GLib.List<SheepleContactStoreBackendContact> subcontacts;
    
    public SheepleContactStoreMetaContact()
    {
        this.refcount = 0;
        this.metacontact = null;
        this.subcontacts = new GLib.List<SheepleContactStoreBackendContact>();
    }
    
    public void invalidate()
    {
        this.metacontact = null;
    }
}

public class SheepleContactStore : GLib.Object
{
    // This should eventually be persistent
    private GLib.HashTable<string,SheepleContactStoreMetaContact> contact_store;
    
    private GLib.HashTable<string,SheepleContactBackend> contact_backends;
    
    public SheepleContactStore()
    {
        this.contact_store = new GLib.HashTable<string,SheepleContactStoreMetaContact>(GLib.str_hash,GLib.direct_equal);
        this.contact_backends = new GLib.HashTable<string,SheepleContactBackend>(GLib.str_hash,GLib.direct_equal);
    }
    
    public void add_backend(SheepleContactBackend backend)
    {
        string backend_id = backend.get_db_id();
        this.contact_backends.insert(backend_id, backend);
        backend.contact_added.connect((backend, contact_id) => {
            // Theoretically, eventually, we find contacts that might be merge candidates,
            // then ask the user if they're actually the same person or not
            
            SheepleContactStoreMetaContact meta = new SheepleContactStoreMetaContact();
            SheepleContactStoreBackendContact backend_contact = new SheepleContactStoreBackendContact();
            
            backend_contact.id = contact_id;
            backend_contact.db_id = backend_id;
            
            meta.subcontacts.prepend(backend_contact);
            meta.refcount++;
            
            this.contact_store.insert(contact_id, meta); // NEED A BETTER WAY TO COME UP WITH OUR
                                                         // OWN UUID (right now, use the one from EDS)
        });
        
        backend.contact_removed.connect((backend, contact_id) => {
            SheepleContactStoreMetaContact meta = this.contact_store.lookup(contact_id);
            
            if(meta != null)
            {
                meta.refcount--;
                meta.invalidate();
            }
        });
        
        backend.contact_changed.connect((backend, contact_id) => {
            SheepleContactStoreMetaContact meta = this.contact_store.lookup(contact_id);
            
            if(meta != null)
            {
                meta.invalidate();
            }
        });
    }
    
    SheepleContact? get_contact(string id)
    {
        SheepleContactStoreMetaContact meta = this.contact_store.lookup(id);
        SheepleMetaContact contact = meta.metacontact;
        
        if(meta.refcount == 0)
        {
            return null;
        }
        
        if(contact == null)
        {
            meta.metacontact = contact = new SheepleMetaContact();
            
            foreach(SheepleContactStoreBackendContact subcontact in meta.subcontacts)
            {
                SheepleContactBackend backend = this.contact_backends.lookup(subcontact.db_id);
                SheepleContact merge_contact = backend.get_contact(subcontact.id);
                
                if(merge_contact != null)
                    contact.merge_with_contact(merge_contact);
            }
        }
        
        return contact;
    }
    
    GLib.List<unowned string> get_contacts()
    {
        return this.contact_store.get_keys();
    }
}

