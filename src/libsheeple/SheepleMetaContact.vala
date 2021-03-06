using GLib;
using Gdk;

public class SheepleMetaContact : GLib.Object, SheepleContact
{
    private GLib.List<SheepleContact> subcontacts;

    public string full_name {get; set;}
    public string given_name {get; set;}
    public string family_name {get; set;}
    public string nickname {get; set;}
    
    private GLib.List<SheepleContactField> _email;
    public GLib.List<SheepleContactField> email {get { return _email; } set { _email = value.copy(); }}
    
    private GLib.List<SheepleContactField> _phone;
    public GLib.List<SheepleContactField> phone {get { return _phone; } set { _phone = value.copy(); }}
    
    public Gdk.Pixbuf photo {get; set;}
    
    public SheepleMetaContact()
    {
        subcontacts = new GLib.List<SheepleContact>();
    }
    
    public void merge_with_contact(SheepleContact to_merge)
    {
        subcontacts.prepend(to_merge);
        
        this.full_name = to_merge.full_name;
        this.given_name = to_merge.given_name;
        this.family_name = to_merge.family_name;
        this.nickname = to_merge.nickname;
        
        this.email = to_merge.email;
        this.phone = to_merge.phone;
        
        this.photo = to_merge.photo;
    }
}
