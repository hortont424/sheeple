using GLib;
using Gtk;
using WebKit;

class SheepleContactView : Gtk.ScrolledWindow
{
    private WebKit.WebView webview;

    public SheepleContactView()
    {
        this.webview = new WebKit.WebView();
        webview.load_uri("http://www.google.com");
        this.add(webview);
        this.show_all();
    }
}
