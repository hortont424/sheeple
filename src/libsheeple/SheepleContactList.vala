using GLib;
using Gtk;

public class SheepleContactList : Gtk.ScrolledWindow
{
    private Gtk.TreeView treeview;
    private Gtk.ListStore listmodel;
    
    public SheepleContactList()
    {
        this.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
        
        this.treeview = new Gtk.TreeView();
        this.treeview.set_headers_visible(false);
        
        this.listmodel = new Gtk.ListStore(2, typeof(string), typeof(string));
        this.treeview.set_model(this.listmodel);

        this.treeview.insert_column_with_attributes(-1, "Icon", new CellRendererPixbuf(), "icon-name", 0, null);
        this.treeview.insert_column_with_attributes(-1, "Contacts", new CellRendererText(), "text", 1, null);
        
        var cs = SheepleStore.get_store();
        cs.ready.connect(contact_store_ready);
        
        this.add(this.treeview);
        this.show_all();
    }
    
    private void contact_store_ready()
    {
        var cs = SheepleStore.get_store();
        foreach(string c_id in cs.get_contacts())
        {
            stdout.printf("c_id = %s\n", c_id);
            stdout.printf("contact = %p\n", cs.get_contact(c_id));
            TreeIter iter;
            this.listmodel.append(out iter);
            this.listmodel.set(iter, 0, "gtk-orientation-portrait", 1, cs.get_contact(c_id).full_name, -1);
        }
        
        this.listmodel.set_sort_column_id(1, Gtk.SortType.ASCENDING);
    }
}
