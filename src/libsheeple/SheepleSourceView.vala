using GLib;
using Gdk;
using Gtk;

internal class _SourceWidgets
{
    public Gtk.VBox box;
}

internal class _GroupWidgets
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
        
        this.notify["sources"].connect(update_sources);
        this.notify["selection"].connect(update_selection);
    }
    
    public void select_first_group()
    {
        foreach(SheepleSource src in this.sources)
        {
            foreach(SheepleGroup grp in src.groups)
            {
                GLib.List<SheepleGroup> newselection = new GLib.List<SheepleGroup>();
                newselection.prepend(grp);
                this.selection = newselection;
                return;
            }
        }
    }
    
    private void update_sources()
    {
        this.source_vbox.foreach((ud) => {
            this.source_vbox.remove(ud);
        });
        
        this.source_widgets = new GLib.HashTable<SheepleSource,_SourceWidgets?>(GLib.direct_hash,GLib.direct_equal);
        this.group_widgets = new GLib.HashTable<SheepleGroup,_GroupWidgets?>(GLib.direct_hash,GLib.direct_equal);
        
        foreach(SheepleSource src in this.sources)
        {
            Gtk.VBox source_box;
            Gtk.Label source_label;
            string title_markup;
            _SourceWidgets source_widgets;
            
            title_markup = GLib.Markup.printf_escaped("<b>%s</b>", src.name);
            
            source_label = new Gtk.Label(null);
            source_label.set_markup(title_markup);
            source_label.set_alignment(0, 0);
            
            source_box = new Gtk.VBox(false, 0);
            source_box.pack_start(source_label, true, true, 4);
            
            foreach(SheepleGroup gr in src.groups)
            {
                Gtk.Button button_widget;
                Gtk.Alignment alignment;
                Gtk.Label button_label;
                Gtk.Image button_image;
                Gtk.HBox button_hbox;
                Gtk.Alignment button_align;
                string button_markup;
                SheepleGroup grp = gr; // Vala bug #599133
                _GroupWidgets group_widgets;
                
                button_hbox = new Gtk.HBox(false, 2);
                
                if(grp.icon != null)
                {
                    button_image = new Gtk.Image.from_pixbuf(grp.icon);
                    button_hbox.pack_start(button_image, true, true, 0);
                }
                
                button_markup = GLib.Markup.printf_escaped("%s", grp.name);
                
                button_label = new Gtk.Label(null);
                button_label.set_markup(button_markup);
                
                button_align = new Gtk.Alignment(0, 0.7f, 0, 0); // TODO: wtf!?
                button_align.add(button_label);
                
                button_hbox.pack_start(button_align, true, true, 2);
                
                button_widget = new Gtk.Button();
                button_widget.add(button_hbox);
                button_widget.relief = Gtk.ReliefStyle.NONE;
                button_widget.focus_on_click = false;
                button_widget.clicked.connect(() => {
                    GLib.List<SheepleGroup> newselection = new GLib.List<SheepleGroup>();
                    newselection.prepend(grp);
                    selection = newselection;
                });
                
                alignment = new Gtk.Alignment(0, 0, 0, 0);
                alignment.set_padding(0, 0, 8, 4);
                alignment.add(button_widget);
                
                source_box.pack_start(alignment, true, true, 0);
                
                group_widgets = new _GroupWidgets() { 
                    button = button_widget,
                    label = button_label,
                    hbox = button_hbox,
                    icon = button_image
                };
                
                this.group_widgets.insert(grp, group_widgets);
            }
            
            this.source_vbox.pack_start(source_box, false, true, 0);
            
            source_widgets = new _SourceWidgets() {
                box = source_box
            };
            
            this.source_widgets.insert(src, source_widgets);
        }
        
        this.show_all();
        this.select_first_group();
    }
    
    private void update_selection()
    {
        foreach(SheepleSource src in this.sources)
        {
            foreach(SheepleGroup grp in src.groups)
            {
                _GroupWidgets group_widgets = this.group_widgets.lookup(grp);
                string button_markup;
                Gtk.ReliefStyle new_style = Gtk.ReliefStyle.NONE;
                
                if(this.selection.find(grp) != null)
                    new_style = Gtk.ReliefStyle.NORMAL;
                
                button_markup = GLib.Markup.printf_escaped(
                    ((new_style == Gtk.ReliefStyle.NONE) ? "%s" : "<b>%s</b>"),
                    grp.name);
                
                group_widgets.button.relief = new_style;
                group_widgets.label.set_markup(button_markup);
            }
        }
        
        this.selection_changed();
    }
}

