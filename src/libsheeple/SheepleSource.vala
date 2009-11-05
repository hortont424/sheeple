using GLib;
using Gdk;

public class SheepleSource : GLib.Object
{
    public string name {get; set;}
    
    private GLib.List<SheepleGroup> _groups;
    public GLib.List<SheepleGroup> groups {get { return _groups; } set { _groups = value.copy(); }}
    
    public SheepleBackend backend {get; set;}
    
    public SheepleSource()
    {
    }
    
    public SheepleSource.with_backend(SheepleBackend backend)
    {
        this.backend = backend;
    }
    
    public SheepleSource.with_name(string name) // TODO: get rid of this
    {
        this.name = name;
    }

}
