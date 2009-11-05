using GLib;
using Gdk;

public class SheepleSource : GLib.Object
{
    public string name {get; set;}
    
    private GLib.HashTable<string,SheepleGroup> groups;
    
    public SheepleBackend backend {get; set;}
    
    public signal void group_added(SheepleGroup group);
    public signal void group_removed(SheepleGroup group);
    public signal void ready();
    
    public SheepleSource(string name, SheepleBackend backend)
    {
        this.name = name;
        this.backend = backend;
        this.groups = new GLib.HashTable<string,SheepleGroup>(GLib.str_hash, GLib.str_equal);
        
        this.backend.group_added.connect((be, id) => {
            SheepleGroup group = this.backend.get_group(id);
            this.groups.insert(id, group);
            this.group_added(group);
        });
        
        this.backend.group_removed.connect((be, id) => {
            this.group_removed(this.backend.get_group(id));
            this.groups.remove(id);
        });
        
        this.backend.ready.connect((grp) => {
            this.ready();
        });
    }
    
    public void start()
    {
        this.backend.start();
    }
    
    public SheepleGroup get_group(string id)
    {
        return this.groups.lookup(id);
    }
    
    public GLib.List<SheepleGroup> get_groups()
    {
        return this.groups.get_values();
    }
}
