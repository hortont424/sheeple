using GLib;
using Gtk;
using Pango;

public class SheepleEditorField : Gtk.Alignment
{
    private Gtk.Entry entry;
    private Gtk.Button button;
    
    private bool _large_type;
    private SheepleContactField _field;
    
    public bool large_type
    {
        get
        {
            return _large_type;
        }
        
        set
        {
            _large_type = value;
            
            var font = new Pango.FontDescription();
            
            if(this.large_type)
                font.set_weight(Pango.Weight.BOLD);
            
            this.entry.modify_font(font);
            this.button.child.modify_font(font);
        }
    }
    
    public SheepleContactField field
    {
        get
        {
            return _field;
        }
        
        set
        {
            _field = value;
            this.entry.text = _field.data;
            this.button.label = _field.data;
        }
    }
    
    public SheepleEditorField()
    {
        var font = new Pango.FontDescription();
        
        if(this.large_type)
            font.set_weight(Pango.Weight.BOLD);
    
        this.entry = new Gtk.Entry();
        this.entry.modify_font(font);
        this.entry.activate.connect(() => { // TODO: bad to use activate?
            this.remove(entry);
            this.add(button);
            this.show_all(); // No matter what I do, the button won't lose relief
        });
        this.entry.changed.connect(() => {
            this.field.data = this.entry.text;
            this.button.label = this.entry.text;
        });
        
        this.button = new Gtk.Button();
        this.button.modify_font(font);
        this.button.relief = Gtk.ReliefStyle.NONE;
        this.button.focus_on_click = false;
        this.button.set_can_focus(false);
        this.button.clicked.connect(() => {
            this.remove(button);
            this.entry.set_width_chars((int)this.field.data.length);
            this.add(entry);
            this.show_all();
            this.entry.grab_focus();
        });
        
        this.xscale = this.yscale = 0;
        this.xalign = this.yalign = 0;
        
        this.add(button);
        
        this.show_all();
    }
}
