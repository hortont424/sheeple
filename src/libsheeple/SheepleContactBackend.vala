using GLib;

public interface SheepleContactBackendGroup : GLib.Object
{
    public abstract string get_group_id();
    
    private GLib.HashTable<string,SheepleContact> contacts;
    
    public abstract SheepleContact get_contact(string id);
    
    public signal void contact_added(string contact);
    public signal void contact_changed(string contact);
    public signal void contact_removed(string contact);
    public signal void ready();
}

public interface SheepleContactBackend : GLib.Object
{
    public abstract string get_db_id();
    
    public signal void group_added(string group);
    public signal void group_changed(string group);
    public signal void group_removed(string group);
    public signal void ready();
}
