using GLib;
using Gdk;

public class SheepleGroup : GLib.Object
{
    public string name {get; set;}
    public Gdk.Pixbuf icon {get; set;}
    public SheepleContactBackendGroup backend_group {get; set;}
    
    private GLib.List<string> _contacts;
    public GLib.List<string> contacts {get { return _contacts; } set { _contacts = value.copy(); }}
    
    public abstract SheepleContact get_contact(string id);
    
    public signal void contact_added(string contact);
    public signal void contact_changed(string contact);
    public signal void contact_removed(string contact);
    public signal void ready();
    
    public SheepleGroup()
    {
    }
    
    public SheepleGroup.with_name(string name)
    {
        this.name = name;
    }
    
    public SheepleGroup.with_name_and_icon(string name, Gdk.Pixbuf icon)
    {
        this.name = name;
        this.icon = icon;
    }

}
