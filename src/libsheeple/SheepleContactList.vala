using GLib;
using Gtk;

public class SheepleContactList : Gtk.ScrolledWindow
{
    private Gtk.TreeView treeview;
    private Gtk.ListStore listmodel;
    
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
        
        this.listmodel = new Gtk.ListStore(2, typeof(string), typeof(string));
        this.treeview.set_model(this.listmodel);

        this.treeview.insert_column_with_attributes(-1, "Icon", new CellRendererPixbuf(), "icon-name", 0, null);
        this.treeview.insert_column_with_attributes(-1, "Contacts", new CellRendererText(), "text", 1, null);
        
        var cs = SheepleStore.get_store();
        cs.ready.connect(update_contact_list);
        
        this.add(this.treeview);
        this.show_all();
        
        this.notify["group"].connect(update_contact_list);
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
            TreeIter iter;
            this.listmodel.append(out iter);
            this.listmodel.set(iter, 0, "gtk-orientation-portrait", 1, contact.full_name, -1);
        }
        
        this.listmodel.set_sort_column_id(1, Gtk.SortType.ASCENDING);
    }
}
