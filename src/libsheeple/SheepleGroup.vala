using GLib;
using Gdk;

public class SheepleGroup : GLib.Object
{
    public string name {get; set;}
    public Gdk.Pixbuf icon {get; set;}
    public SheepleContactBackendGroup backend_group {get; set;}
    
    public GLib.List<SheepleContact> contacts {get; private set;} // todo wtf
    
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
