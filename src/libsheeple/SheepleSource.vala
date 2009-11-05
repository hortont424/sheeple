using GLib;
using Gdk;

public class SheepleSource : GLib.Object
{
    public string name {get; set;}
    public unowned List<SheepleGroup> groups {get; set;}
    public SheepleContactBackend backend {get; set;}
    
    public SheepleSource()
    {
    }
    
    public SheepleSource.with_name(string name)
    {
        this.name = name;
    }

}
