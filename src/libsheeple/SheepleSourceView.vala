using GLib;
using Gdk;
using Gtk;

struct _SourceWidgets
{
    public Gtk.VBox box;
}

struct _GroupWidgets
{
    public Gtk.Button button;
    public Gtk.Label label;
    public Gtk.HBox hbox;
    public Gtk.Image icon;
}

public class SheepleSourceView : Gtk.ScrolledWindow
{
    public unowned GLib.List<SheepleSource> sources {get; set;}
    public unowned GLib.List<SheepleGroup> selection {get; set;}
    private GLib.HashTable<SheepleSource,_SourceWidgets?> source_widgets;
    private GLib.HashTable<SheepleGroup,_GroupWidgets?> group_widgets;
    private Gtk.VBox source_vbox;
    
    public signal void selection_changed();
    
    public SheepleSourceView()
    {
        Gtk.Alignment master_padding;
        Gtk.Viewport viewport;
        
        this.source_widgets = new GLib.HashTable<SheepleSource,_SourceWidgets?>(GLib.direct_hash,GLib.direct_equal);
        this.group_widgets = new GLib.HashTable<SheepleGroup,_GroupWidgets?>(GLib.direct_hash,GLib.direct_equal);
        
        this.set_hadjustment(null);
        this.set_vadjustment(null);
        this.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
        this.set_shadow_type(Gtk.ShadowType.NONE);
        
        this.source_vbox = new Gtk.VBox(false, 10);
        
        master_padding = new Gtk.Alignment(0, 0, 1, 1);
        master_padding.set_padding(0, 0, 4, 4);
        master_padding.add(this.source_vbox);
        
        viewport = new Gtk.Viewport(this.hadjustment, this.vadjustment);
        viewport.set_shadow_type(Gtk.ShadowType.NONE);
        viewport.add(master_padding);
        this.add(viewport);
    }
}
