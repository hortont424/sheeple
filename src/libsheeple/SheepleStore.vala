using GLib;

public class SheepleStoreBackendContact
{
    public string id;
    public string db_id;
    public string group_id;
}

public class SheepleStoreMetaContact
{
    public int refcount;
    public SheepleMetaContact metacontact;
    public GLib.List<SheepleStoreBackendContact> subcontacts;
    
    public SheepleStoreMetaContact()
    {
        this.refcount = 0;
        this.metacontact = null;
        this.subcontacts = new GLib.List<SheepleStoreBackendContact>();
    }
    
    public void invalidate()
    {
        this.metacontact = null;
    }
}

public class SheepleStore : GLib.Object
{
    private static SheepleStore instance = null;

    // This (well at least the subcontacts field) should eventually be persistent
    private GLib.HashTable<string,SheepleStoreMetaContact> contact_store;
    
    private GLib.HashTable<string,SheepleSource> contact_sources;
    
    private int subready_count = 0;
    
    public signal void source_added(SheepleSource db);
    public signal void source_removed(SheepleSource db);
    
    public signal void contact_added(SheepleContact contact);
    public signal void contact_changed(SheepleContact contact);
    public signal void contact_removed(SheepleContact contact);
    public signal void ready();
    
    public SheepleStore()
    {
        this.contact_store = new GLib.HashTable<string,SheepleStoreMetaContact>(GLib.str_hash,GLib.str_equal);
        this.contact_sources = new GLib.HashTable<string,SheepleSource>(GLib.str_hash,GLib.str_equal);
    }
    
    public static SheepleStore get_store()
    {
        if(instance == null)
            instance = new SheepleStore();
        
        return instance;
    }
    
    public void add_backend(SheepleBackend backend)
    {
        string backend_id = backend.get_db_id();
        SheepleSource contact_source = new SheepleSource(backend_id, backend);
        this.contact_sources.insert(backend_id, contact_source);
        
        contact_source.group_added.connect((src, grp) => {
            grp.contact_added.connect((backend, contact_id) => {
                // Theoretically, eventually, we find contacts that might be merge candidates,
                // then ask the user if they're actually the same person or not
                SheepleStoreMetaContact meta = new SheepleStoreMetaContact();
                SheepleStoreBackendContact backend_contact = new SheepleStoreBackendContact();
                
                backend_contact.id = contact_id;
                backend_contact.group_id = grp.get_group_id();
                backend_contact.db_id = backend_id;
                
                meta.subcontacts.prepend(backend_contact);
                meta.refcount++;
                
                this.contact_store.insert(contact_id, meta); // NEED A BETTER WAY TO COME UP WITH OUR
                                                             // OWN UUID (right now, use the one from EDS)
                
                this.contact_added(this.resolve_contact(meta));
            });
            
            grp.contact_removed.connect((backend, contact_id) => {
                SheepleStoreMetaContact meta = this.contact_store.lookup(contact_id);
                this.contact_removed(this.resolve_contact(meta));
                
                if(meta != null)
                {
                    meta.refcount--;
                    meta.invalidate();
                }
            });
            
            grp.contact_changed.connect((backend, contact_id) => {
                SheepleStoreMetaContact meta = this.contact_store.lookup(contact_id);
                
                if(meta != null)
                {
                    meta.invalidate();
                }
                
                this.contact_changed(this.resolve_contact(meta));
            });
            
            grp.ready.connect(() => {
                // TODO: FIXME: this needs to only fire when all registered backends, groups, etc. are ready!
                this.subready();
            });
            
            this.subready_count++;
            
            grp.start();
            
            //this.group_added(group_id);
        });
        
        //contact_source.group_removed((src, group_id) => {
            //this.group_removed(group_id);
        //});
        
        contact_source.ready.connect((cs) => {
        });
        
        contact_source.start();
        
        this.source_added(contact_source);
    }
    
    private void subready()
    {
        this.subready_count--;
        
        if(this.subready_count == 0)
            this.ready();
    }
    
    public SheepleContact? resolve_contact(SheepleStoreMetaContact meta)
    {
        if(meta == null)
            return null;
        
        SheepleMetaContact contact = meta.metacontact;
        
        if(meta.refcount == 0)
            return null;
        
        if(contact == null)
        {
            meta.metacontact = contact = new SheepleMetaContact();
            
            foreach(SheepleStoreBackendContact subcontact in meta.subcontacts)
            {
                SheepleSource src = this.contact_sources.lookup(subcontact.db_id);
                SheepleGroup grp = src.get_group(subcontact.group_id);
                SheepleContact merge_contact = grp.get_contact(subcontact.id);
                
                if(merge_contact != null)
                    contact.merge_with_contact(merge_contact);
            }
        }
        
        return contact;
    }
    
    public GLib.List<SheepleSource> get_sources()
    {
        return this.contact_sources.get_values();
    }
    
    public GLib.List<SheepleContact> get_contacts()
    {
        GLib.List<SheepleContact> contacts = new GLib.List<SheepleContact>();
        
        foreach(SheepleStoreMetaContact mc in this.contact_store.get_values())
        {
            contacts.prepend(this.resolve_contact(mc));
            stdout.printf("%s\n", this.resolve_contact(mc).full_name);
        }
        return contacts;
    }
}

