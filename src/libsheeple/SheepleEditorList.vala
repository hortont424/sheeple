using GLib;
using Gtk;
using Pango;

public class SheepleEditorList : Gtk.Alignment
{
    private Gtk.Table main_table;
    private Gtk.Label title_label;
    private GLib.List<SheepleEditorField> fields; 
    
    private string _title;
    private unowned GLib.List<SheepleContactField> _data;
    
    public string title
    {
        get
        {
            return _title;
        }
        
        set
        {
            _title = value;
            this.title_label.label = _title;
        }
    }
    
    public unowned GLib.List<SheepleContactField> data
    {
        get
        {
            return _data;
        }
        
        set
        {
            if(this.fields != null)
            {
                foreach(SheepleEditorField w in this.fields)
                {
                    this.main_table.remove(w);
                    this.fields.remove(w);
                }
            }
            
            _data = value;
            
            this.main_table.resize(2 + this.data.length(), 2);
            
            int i = 3;
            
            foreach(SheepleContactField f in this.data)
            {
                SheepleEditorField w = new SheepleEditorField();
                w.field = f;
                this.fields.append(w);
                this.main_table.attach_defaults(w, 0, 1, i, i + 1);
                i++;
                
                this.main_table.show_all();
            }
        }
    }
    
    public SheepleEditorList()
    {
        this.fields = null;
        
        this.xalign = this.yalign = 0;
        this.set_padding(0, 0, 15, 15);
    
        this.title_label = new Gtk.Label("");
        Gtk.Alignment title_align = new Gtk.Alignment(0,0,0,0);
        title_align.add(title_label);
        
        this.main_table = new Gtk.Table(2, 2, false);
        this.main_table.attach_defaults(title_align, 0, 1, 0, 1);
        Gtk.Alignment main_table_align = new Gtk.Alignment(0,0,1,0);
        main_table_align.add(main_table);
        
        this.add(main_table_align);
        
        this.show_all();
    }
}
