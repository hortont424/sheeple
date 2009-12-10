using GLib;
using Gtk;
using WebKit;

public class SheepleContactView : Gtk.ScrolledWindow
{
    private Gtk.VBox main_box;
    private Gtk.EventBox event_box;
    
    public unowned SheepleContact _contact;
    public unowned SheepleContact contact
    {
        get
        {
            return _contact;
        }
        
        set
        {
            //if(_contact != null)
            //{
                //_contact.contact_added.disconnect(update_contact_list);
                //_contact.contact_changed.disconnect(update_contact_list);
                //_contact.contact_removed.disconnect(update_contact_list);
            //}
                
            _contact = value;
            
            //_contact.contact_added.connect(update_contact_list);
            //_contact.contact_changed.connect(update_contact_list);
            //_contact.contact_removed.connect(update_contact_list);
        }
    }

    public SheepleContactView()
    {
        this.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.AUTOMATIC);
        
        this.main_box = null;
        this.event_box = new Gtk.EventBox();
        
        this.notify["contact"].connect(update_view);
        
        Gdk.Color color;
        Gdk.Color.parse("#fff", out color);
        this.event_box.modify_bg(Gtk.StateType.NORMAL, color);
        
        this.add_with_viewport(event_box);
        
        this.show_all();
    }
    
    private void update_view()
    {
        if(this.main_box != null)
            this.event_box.remove(this.event_box.child);
        
        this.main_box = new Gtk.VBox(false, 0);
        this.event_box.add(this.main_box);
        
        // Load, scale, and resize the contact photo
        Gdk.Pixbuf contact_pixbuf = this.contact.photo;
        Gtk.Image img = new Gtk.Image.from_file("media/no-contact-photo.png");
        
        if(contact_pixbuf != null)
        {
            contact_pixbuf = contact_pixbuf.scale_simple(96, 96, Gdk.InterpType.BILINEAR);
            img = new Gtk.Image.from_pixbuf(contact_pixbuf);
        }
        
        // Construct the editor
        Gtk.HBox top_bar = new Gtk.HBox(false, 0);
        
        top_bar.pack_start(img, false, true, 5);
        
        this.main_box.pack_start(top_bar, false, true, 5);
       
        main_box.show_all();
    }
}
