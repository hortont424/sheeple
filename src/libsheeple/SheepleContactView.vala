using GLib;
using Gtk;
using WebKit;

public class SheepleContactView : Gtk.ScrolledWindow
{
    private Gtk.VBox main_box;
    
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
        
        this.notify["contact"].connect(update_view);
        
        this.show_all();
    }
    
    private void update_view()
    {
        if(this.main_box != null)
            this.remove(this.child);
        
        this.main_box = new Gtk.VBox(false, 0);
        this.add_with_viewport(this.main_box);
        
        Gdk.Pixbuf contact_pixbuf = this.contact.photo;
        Gtk.Image img = new Gtk.Image.from_file("/home/hortont/src/sheeple/media/no-contact-photo.png");
        
        if(contact_pixbuf != null)
        {
            contact_pixbuf = contact_pixbuf.scale_simple(96, 96, Gdk.InterpType.BILINEAR);
            img = new Gtk.Image.from_pixbuf(contact_pixbuf);
        }
        
        this.main_box.pack_start(img, true, true, 0);
       
        main_box.show_all();
    }
}
