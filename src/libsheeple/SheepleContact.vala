using GLib;

public interface SheepleContact : GLib.Object
{
    public abstract string full_name {get; set;}
    public abstract string given_name {get; set;}
    public abstract string family_name {get; set;}
    public abstract string nickname {get; set;}
    
    public abstract GLib.List<string> email {get; set;}
}
