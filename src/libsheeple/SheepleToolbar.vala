using Gtk;

public class SheepleToolbar : Gtk.Toolbar
{
    public signal void update_filter(string filter);
    Entry searchEntry;

    public SheepleToolbar()
    {
        ToolButton addButton = new ToolButton.from_stock("gtk-add");
        SeparatorToolItem sepItem = new SeparatorToolItem();
        ToolItem searchField = new ToolItem();

        searchEntry = new Entry();
        searchEntry.set_size_request(175, -1);
        searchField.add(searchEntry);
        searchEntry.changed.connect(() => { this.update_filter(searchEntry.text); });

        sepItem.set_expand(true);
        sepItem.draw = false;
        
        this.insert(addButton, 0);
        this.insert(sepItem, -1);
        this.insert(searchField, -1);
    }
}

