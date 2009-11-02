using GLib;

public class SheepleMetaContact : GLib.Object, SheepleContact
{
    private GLib.List<SheepleContact> subcontacts;

    public string full_name {get; set;}
    public string given_name {get; set;}
    public string family_name {get; set;}
    public string nickname {get; set;}
    
    public GLib.List<string> _email;
    public GLib.List<string> email {get { return _email; } set { _email = value.copy(); }}
    
    public SheepleMetaContact()
    {
        subcontacts = new GLib.List<SheepleContact>();
    }
    
    public void merge_with_contact(SheepleContact to_merge)
    {
        
    }
}
