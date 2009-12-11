using GLib;
using Gdk;

public interface SheepleContactField : GLib.Object
{
    public abstract string label {get; set;}
    public abstract string data {get; set;}
    public abstract bool primary {get; set;}
}

public class SheepleContactPhone : GLib.Object, SheepleContactField
{
    public string label {get; set;}
    public string data {get; set;}
    public bool primary {get; set;}
}

public class SheepleContactEmail : GLib.Object, SheepleContactField
{
    public string label {get; set;}
    public string data {get; set;}
    public bool primary {get; set;}
}

public interface SheepleContact : GLib.Object
{
    public abstract string full_name {get; set;}
    public abstract string given_name {get; set;}
    public abstract string family_name {get; set;}
    public abstract string nickname {get; set;}
    
    public abstract GLib.List<SheepleContactField> email {get; set;}
    public abstract GLib.List<SheepleContactField> phone {get; set;}
    
    public abstract Gdk.Pixbuf photo {get; set;}
}
