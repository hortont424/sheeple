using GLib;

public interface SheepleContactBackend : GLib.Object
{
    public abstract int get_db_id();
    
    public abstract GLib.List<SheepleContact> get_contacts();
    public abstract SheepleContact get_contact_by_id(string id);
}
