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
        
        this.listmodel = new Gtk.ListStore(1, typeof (string));
        this.treeview.set_model(this.listmodel);

        this.treeview.insert_column_with_attributes(-1, "Contacts", new CellRendererText(), "text", 0, null);
        
        var cs = SheepleContactStore.get_contact_store();
        cs.ready.connect(contact_store_ready);
        
        this.add(this.treeview);
        this.show_all();
    }
    
    private void contact_store_ready()
    {
        var cs = SheepleContactStore.get_contact_store();
        foreach(string c_id in cs.get_contacts())
        {
            TreeIter iter;
            this.listmodel.append(out iter);
            this.listmodel.set(iter, 0, cs.get_contact(c_id).full_name, -1);
        }
        
        this.listmodel.set_sort_column_id(0, Gtk.SortType.ASCENDING);
    }
}
