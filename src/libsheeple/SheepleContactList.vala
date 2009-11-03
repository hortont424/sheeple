using GLib;
using Gtk;

public class SheepleContactList : Gtk.VBox
{
    private Gtk.ScrolledWindow scroll_window;
    private Gtk.VBox contacts_box;
    private Gtk.Label onebox;
    
    public SheepleContactList()
    {
        Gtk.Viewport viewport;
        this.contacts_box = new Gtk.VBox(true, 10);
        
        this.scroll_window = new Gtk.ScrolledWindow(null, null);
        this.scroll_window.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
        this.scroll_window.set_shadow_type(Gtk.ShadowType.NONE);
        
        viewport = new Gtk.Viewport(this.scroll_window.hadjustment, this.scroll_window.vadjustment);
        viewport.set_shadow_type(Gtk.ShadowType.NONE);
        viewport.add(this.contacts_box);
        
        this.scroll_window.add(viewport);
        
        
        var cs = SheepleContactStore.get_contact_store();
        cs.ready.connect(contact_store_ready);
                
        this.pack_start(scroll_window, true, true, 0);
        this.show_all();
    }
    
    private void contact_store_ready()
    {
        var cs = SheepleContactStore.get_contact_store();
        foreach(string c_id in cs.get_contacts())
        {
            onebox = new Gtk.Label(cs.get_contact(c_id).full_name);
            this.contacts_box.pack_start(onebox, false, true, 0);
            onebox.show();
        }
    }
}
