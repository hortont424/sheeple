using GLib;
using Gtk;
using WebKit;

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
        //this.webview.load_html_string("<script>document.onmousedown = function(e) { return false; }; document.onclick = function() { return true; };</script> ", "/");
        this.webview.load_html_string(this.contact.full_name, "/");
    }
}
