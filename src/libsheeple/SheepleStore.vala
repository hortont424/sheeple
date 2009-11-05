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
    
    public signal void source_added(string db_id);
    public signal void source_removed(string db_id);
    
    public signal void contact_added(string contact_id);
    public signal void contact_changed(string contact_id);
    public signal void contact_removed(string contact_id);
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
        
        contact_source.group_added.connect((src, group_id) => {
            SheepleGroup grp = contact_source.get_group(group_id);
            
            grp.contact_added.connect((backend, contact_id) => {
                // Theoretically, eventually, we find contacts that might be merge candidates,
                // then ask the user if they're actually the same person or not
                SheepleStoreMetaContact meta = new SheepleStoreMetaContact();
                SheepleStoreBackendContact backend_contact = new SheepleStoreBackendContact();
                
                backend_contact.id = contact_id;
                backend_contact.group_id = group_id;
                backend_contact.db_id = backend_id;
                
                meta.subcontacts.prepend(backend_contact);
                meta.refcount++;
                
                this.contact_store.insert(contact_id, meta); // NEED A BETTER WAY TO COME UP WITH OUR
                                                             // OWN UUID (right now, use the one from EDS)
                
                this.contact_added(contact_id);
            });
            
            grp.contact_removed.connect((backend, contact_id) => {
                SheepleStoreMetaContact meta = this.contact_store.lookup(contact_id);
                
                if(meta != null)
                {
                    meta.refcount--;
                    meta.invalidate();
                }
                
                this.contact_removed(contact_id);
            });
            
            grp.contact_changed.connect((backend, contact_id) => {
                SheepleStoreMetaContact meta = this.contact_store.lookup(contact_id);
                
                if(meta != null)
                {
                    meta.invalidate();
                }
                
                this.contact_changed(contact_id);
            });
            
            grp.ready.connect(() => {
                // TODO: FIXME: this needs to only fire when all registered backends, groups, etc. are ready!
                this.ready();
            });
            
            grp.start();
            
            //this.group_added(group_id);
        });
        
        //contact_source.group_removed((src, group_id) => {
            //this.group_removed(group_id);
        //});
        
        contact_source.ready.connect((cs) => {
        });
        
        contact_source.start();
        
        this.source_added(backend_id);
    }
    
    public SheepleContact? get_contact(string id)
    {
        SheepleStoreMetaContact meta = this.contact_store.lookup(id);
        
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
    
    public SheepleSource get_source(string source_id)
    {
        return this.contact_sources.lookup(source_id);
    }
    
    public SheepleGroup get_group(string group_id, string source_id)
    {
        return this.contact_sources.lookup(source_id).get_group(group_id);
    }
    
    public GLib.List<unowned string> get_contacts()
    {
        return this.contact_store.get_keys();
    }
}

