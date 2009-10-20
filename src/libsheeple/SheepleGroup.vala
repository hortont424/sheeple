using GLib;
using Gdk;

public class SheepleGroup : GLib.Object
{

    // Fields
    public string name {get; set;}
    public Gdk.Pixbuf icon {get; set;}
    
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
