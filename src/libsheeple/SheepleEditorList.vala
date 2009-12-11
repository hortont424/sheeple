using GLib;
using Gtk;
using Pango;

public class SheepleEditorList : Gtk.Alignment
{
    private Gtk.HBox main_hbox;
    private Gtk.Label title_label;
    private GLib.List<SheepleEditorField> fields; 
    private Gtk.VBox field_box;
    
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
                    this.field_box.remove(w);
                    this.fields.remove(w);
                }
            }
            
            _data = value;
            
            //this.main_hbox.resize(2 + this.data.length(), 2);
            
            int i = 3;
            
            foreach(SheepleContactField f in this.data)
            {
                SheepleEditorField w = new SheepleEditorField();
                w.field = f;
                this.fields.append(w);
                w.left_padding = 15;
                w.yalign = 0.5f;
                
                Gtk.Image img = new Gtk.Image.from_stock("gtk-remove", Gtk.IconSize.SMALL_TOOLBAR);
                Gtk.Button close_button = new Gtk.Button();
                close_button.set_image(img);
                close_button.relief = Gtk.ReliefStyle.NONE;
                Gtk.Alignment close_button_align = new Gtk.Alignment(1, 0.5f, 0, 0);
                close_button_align.add(close_button);
                
                Gtk.HBox f_box = new Gtk.HBox(false, 0);
                f_box.pack_start(w, false, true, 0);
                f_box.pack_start(close_button_align, true, true, 0);
                
                this.field_box.pack_start(f_box, true, true, 0);
                i++;
                
                this.field_box.show_all();
            }
        }
    }
    
    public SheepleEditorList()
    {
        this.fields = null;
        
        this.xalign = this.yalign = 0;
        this.yscale = 0;
        this.set_padding(0, 0, 15, 15);
    
        this.field_box = new Gtk.VBox(false, 0);
    
        this.title_label = new Gtk.Label("");
        this.title_label.set_size_request(40, -1); // TODO: CHEATING
        //Gtk.Alignment title_align = new Gtk.Alignment(0,0.5f,0,0);
        //title_align.add(title_label);
        
        this.main_hbox = new Gtk.HBox(false, 0);
        this.main_hbox.pack_start(title_label, false, true, 15);
        
        Gtk.Alignment main_hbox_align = new Gtk.Alignment(0,0,1,0);
        main_hbox_align.add(main_hbox);
        
        main_hbox.pack_start(new Gtk.VSeparator(), false, true, 0);
        main_hbox.pack_start(this.field_box, true, true, 0);
        
        this.add(main_hbox_align);
        
        this.show_all();
    }
}
