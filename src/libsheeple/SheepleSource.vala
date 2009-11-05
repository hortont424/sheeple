using GLib;
using Gdk;

public class SheepleSource : GLib.Object
{
    public string name {get; set;}
    
    private GLib.HashTable<string,SheepleGroup> groups;
    
    public SheepleBackend backend {get; set;}
    
    public signal void group_added(string group);
    public signal void group_removed(string group);
    public signal void ready();
    
    public SheepleSource(string name, SheepleBackend backend)
    {
        this.name = name;
        this.backend = backend;
        this.groups = new GLib.HashTable<string,SheepleGroup>(GLib.str_hash, GLib.str_equal);
        
        this.backend.group_added.connect((grp, id) => {
            this.groups.insert(id, this.backend.get_group(id));
            this.group_added(id);
        });
        
        this.backend.group_removed.connect((grp, id) => {
            this.groups.remove(id);
            this.group_removed(id);
        });
        
        this.backend.ready.connect((grp) => {
            this.ready();
        });
        
        this.backend.start();
    }
    
    public SheepleGroup get_group(string id)
    {
        return this.groups.lookup(id);
    }
    
    public GLib.List<string> get_groups()
    {
        return this.groups.get_keys();
    }
}
