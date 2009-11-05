using GLib;

public interface SheepleBackendGroup : GLib.Object
{
    public abstract string get_group_id();
    
    public abstract SheepleContact get_contact(string id);
    
    public signal void contact_added(string contact);
    public signal void contact_changed(string contact);
    public signal void contact_removed(string contact);
    public signal void ready();
    
    public abstract void start();
}

public interface SheepleBackend : GLib.Object
{
    public abstract string get_db_id();
    
    public abstract SheepleGroup get_group(string id);
    
    public signal void group_added(string group);
    public signal void group_removed(string group);
    public signal void ready();
    
    public abstract void start();
}
