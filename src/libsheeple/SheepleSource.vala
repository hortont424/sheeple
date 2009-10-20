using GLib;
using Gdk;

public class SheepleSource : GLib.Object
{

    // Fields
    public string name {get; set;}
    public unowned List groups {get; set;}
    
    public SheepleSource()
    {
    }
    
    public SheepleSource.with_name(string name)
    {
        this.name = name;
    }

}
