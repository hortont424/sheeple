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
        /*string email_str = "";
        foreach(SheepleContactEmail email in this.contact.email)
        {
            email_str += "<tr><td><h2 class='label'>" + email.label.down() + "</h2></td><td><h2>" + email.address + "</h2></td></tr>";
        }
    
        string phone_str = "";
        foreach(SheepleContactPhone phone in this.contact.phone)
        {
            phone_str += "<tr><td><h2 class='label'>" + phone.label.down() + "</h2></td><td><h2>" + phone.number + "</h2></td></tr>";
        }
        
        string if_email_str = "<tr><td>&nbsp</td><td></td></tr>";
        if(email_str == "")
            if_email_str = "";
    
        SheepleContactViewUI ui = new SheepleContactViewUI();
        this.webview.load_html_string(ui.contact_view_css + "<script>document.onmousedown = function(e) { return false; }; document.onclick = function() { return true; };</script><table><tr><td width='25%'><div id='icon'>&nbsp;</div></td><td><h1>" + this.contact.full_name + "</h1></td></tr>" + if_email_str + email_str + "<tr><td>&nbsp</td><td></td></tr>" + phone_str + "</table>", "/");
        //this.webview.load_html_string(ui.contact_view_source, "/");*/
        
        if(this.main_box != null)
            this.remove(this.child);
        
        this.main_box = new Gtk.VBox(false, 0);
        this.add_with_viewport(this.main_box);
        
        Gdk.Pixbuf contact_pixbuf = this.contact.photo;
        
        if(contact_pixbuf != null)
            contact_pixbuf = contact_pixbuf.scale_simple(96, 96, Gdk.InterpType.BILINEAR);
        
        Gtk.Image img = new Gtk.Image.from_pixbuf(contact_pixbuf);
        this.main_box.pack_start(img, true, true, 0);
       
        main_box.show_all();
    }
}
