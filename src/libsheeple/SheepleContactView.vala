using GLib;
using Gtk;
using WebKit;

class SheepleContactView : Gtk.ScrolledWindow
{
    private WebKit.WebView webview;

    public SheepleContactView()
    {
        this.webview = new WebKit.WebView();
        webview.load_html_string("<script>document.onmousedown = function(e) { return false; }; document.onclick = function() { return true; };</script> Some Contact", "/");
        this.add(webview);
        this.show_all();
    }
}
