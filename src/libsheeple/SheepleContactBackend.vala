using GLib;

public interface SheepleContactBackend : GLib.Object
{
    public abstract string get_db_id();
    
    //public abstract GLib.List<SheepleContact> get_contacts();
    //public abstract SheepleContact get_contact_by_id(string id);
    
    public signal void contact_added(string contact);
    public signal void contact_changed(string contact);
    public signal void contact_removed(string contact);
    
    public void test()
    {
        
    }
}
