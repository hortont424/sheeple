using GLib;
using Gtk;
using WebKit;
using Seed;

public class SheepleContactView : Gtk.ScrolledWindow
{
    private WebKit.WebView webview;
    
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
        this.webview = new WebKit.WebView();
        this.add(webview);
        
        this.notify["contact"].connect(update_view);
        
        this.show_all();
    }
    
    public void test()
    {
        stdout.printf("hello\n");
    }
    
    private void update_view()
    {
        string email_str = "";
        foreach(string email in this.contact.email)
        {
            email_str += "<tr><td><h2 class='label'>email</h2></td><td><h2>" + email + "</h2></td></tr>";
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
        //this.webview.load_html_string(ui.contact_view_source, "/");
    }
}
