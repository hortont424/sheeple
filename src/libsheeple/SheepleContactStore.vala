using GLib;

public class SheepleContactStoreBackendContact
{
    public string id;
    public string db_id;
}

public class SheepleContactStoreMetaContact
{
    public GLib.List<SheepleContactStoreBackendContact> subcontacts;
}

public class SheepleContactStore : GLib.Object
{
    // This should eventually be persistent
    private GLib.HashTable<string,SheepleContactStoreMetaContact> contact_store;
    
    public SheepleContactStore()
    {
        this.contact_store = new GLib.HashTable<string,SheepleContactStoreMetaContact>(GLib.str_hash,GLib.direct_equal);
    }
    
    SheepleContact get_contact(string id)
    {
        return new SheepleMetaContact();
    }
    
    GLib.List<unowned string> get_contacts()
    {
        return this.contact_store.get_keys();
    }
}

