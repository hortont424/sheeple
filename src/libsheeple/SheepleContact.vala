using GLib;

public class SheepleContactPhone : GLib.Object
{
    public string label {get; set;}
    public string number {get; set;}
    public bool primary {get; set;}
}

public class SheepleContactEmail : GLib.Object
{
    public string label {get; set;}
    public string address {get; set;}
    public bool primary {get; set;}
}

public interface SheepleContact : GLib.Object
{
    public abstract string full_name {get; set;}
    public abstract string given_name {get; set;}
    public abstract string family_name {get; set;}
    public abstract string nickname {get; set;}
    
    public abstract GLib.List<SheepleContactEmail> email {get; set;}
    public abstract GLib.List<SheepleContactPhone> phone {get; set;}
}
