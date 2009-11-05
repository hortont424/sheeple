using GLib;
using Gdk;

public class SheepleGroup : GLib.Object
{
    public string name {get; set;}
    public Gdk.Pixbuf icon {get; set;}
    private SheepleBackendGroup backend_group;
    
    private GLib.HashTable<string,SheepleContact> contacts;
    
    public signal void contact_added(string contact);
    public signal void contact_changed(string contact);
    public signal void contact_removed(string contact);
    public signal void ready();
    
    public SheepleGroup(string name, SheepleBackendGroup backend_group)
    {
        this.name = name;
        this.backend_group = backend_group;
        this.contacts = new GLib.HashTable<string,SheepleContact>(GLib.str_hash, GLib.str_equal);
        
        this.backend_group.contact_added.connect((grp, contact_id) => {
            // TODO: make sure it's not already there
            this.contacts.insert(contact_id, this.backend_group.get_contact(contact_id));
            this.contact_added(contact_id);
        });
        
        this.backend_group.contact_changed.connect((grp, contact_id) => {
            this.contact_changed(contact_id);
        });
        
        this.backend_group.contact_changed.connect((grp, contact_id) => {
            // TODO: make sure it exists
            this.contacts.remove(contact_id);
            this.contact_removed(contact_id);
        });
        
        this.backend_group.start();
    }
    
    public SheepleContact get_contact(string id)
    {
        return this.contacts.lookup(id);
    }
    
    public GLib.List<string> get_contacts()
    {
        return this.contacts.get_keys();
    }
}
