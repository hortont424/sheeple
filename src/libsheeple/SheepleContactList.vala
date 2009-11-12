using GLib;
using Gtk;

public class SheepleContactList : Gtk.ScrolledWindow
{
    private Gtk.TreeView treeview;
    private Gtk.ListStore listmodel;
    
    public unowned GLib.List<unowned SheepleContact> selection {get; set;}
    public signal void selection_changed();
    
    public unowned SheepleGroup _group;
    public unowned SheepleGroup group
    {
        get
        {
            return _group;
        }
        
        set
        {
            if(_group != null)
            {
                _group.contact_added.disconnect(update_contact_list);
                _group.contact_changed.disconnect(update_contact_list);
                _group.contact_removed.disconnect(update_contact_list);
            }
                
            _group = value;
            
            _group.contact_added.connect(update_contact_list);
            _group.contact_changed.connect(update_contact_list);
            _group.contact_removed.connect(update_contact_list);
        }
    }
    
    public SheepleContactList()
    {
        this._group = null;
    
        this.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
        
        this.treeview = new Gtk.TreeView();
        this.treeview.set_headers_visible(false);
        this.treeview.cursor_changed.connect(update_selection);
        
        this.listmodel = new Gtk.ListStore(3, typeof(string), typeof(string), typeof(SheepleContact));
        this.treeview.set_model(this.listmodel);

        this.treeview.insert_column_with_attributes(-1, "Icon", new CellRendererPixbuf(), "icon-name", 0, null);
        this.treeview.insert_column_with_attributes(-1, "Contacts", new CellRendererText(), "text", 1, null);
        
        var cs = SheepleStore.get_store();
        cs.ready.connect(update_contact_list);
        
        this.add(this.treeview);
        this.show_all();
        
        this.notify["group"].connect(update_contact_list);
    }
    
    private void update_selection()
    {
        Gtk.TreeSelection sel = this.treeview.get_selection();
        Gtk.TreeIter iter;
        Gtk.TreeModel treemodel;
        GLib.Value val;
        SheepleContact contact;
         
        if(!sel.get_selected(out treemodel, out iter))
        {
            GLib.List<unowned SheepleContact> new_selection = new GLib.List<unowned SheepleContact>();
            this.selection = new_selection;
            
            this.selection_changed();
            return;
        }
        
        treemodel.get_value(iter, 2, out val);
        
        contact = (SheepleContact)val;
        
        GLib.List<unowned SheepleContact> new_selection = new GLib.List<unowned SheepleContact>();
        new_selection.prepend(contact);
        this.selection = new_selection;
        
        this.selection_changed();
    }
    
    private void update_contact_list()
    {
        this.listmodel.clear();
        
        GLib.List<unowned SheepleContact> contact_list;
        
        if(this.group == null)
            contact_list = SheepleStore.get_store().get_contacts();
        else
            contact_list = this.group.get_contacts();
        
        foreach(SheepleContact contact in contact_list)
        {
            Gtk.TreeIter iter;
            this.listmodel.append(out iter);
            this.listmodel.set(iter, 0, "gtk-orientation-portrait", 1, contact.full_name, 2, contact, -1);
        }
        
        this.listmodel.set_sort_column_id(1, Gtk.SortType.ASCENDING);
    }
}
