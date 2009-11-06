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
            email_str += "<h2>" + email + "</h2>";
        }
    
        string phone_str = "";
        foreach(string phone in this.contact.phone)
        {
            phone_str += "<h2>" + phone + "</h2>";
        }
    
        SheepleContactViewUI ui = new SheepleContactViewUI();
        this.webview.load_html_string("<script>document.onmousedown = function(e) { return false; }; document.onclick = function() { return true; };</script><h1>" + this.contact.full_name + "</h1>" + email_str + phone_str, "/");
        //this.webview.load_html_string(ui.contact_view_source, "/");
    }
}
