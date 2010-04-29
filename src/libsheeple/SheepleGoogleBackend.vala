using GLib;
using GData;

public class SheepleGoogleContact : GLib.Object, SheepleContact
{
    private GData.ContactsContact contact;
    private GData.ContactsService server;
    
    public string full_name
    {
        get
        {
            return contact.get_name().get_full_name();
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            
            contact.get_name().set_full_name(value);
            contact = server.update_contact(contact, canc);
        }
    }
    public string given_name
    {
        get
        {
            return contact.get_name().get_given_name();
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            
            contact.get_name().set_given_name(value);
            contact = server.update_contact(contact, canc);
        }
    }
    public string family_name
    {
        get
        {
            return contact.get_name().get_family_name();
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            
            contact.get_name().set_family_name(value);
            contact = server.update_contact(contact, canc);
        }
    }
    public string nickname
    {
        get
        {
            return contact.get_name().get_additional_name();
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            
            contact.get_name().set_additional_name(value);
            contact = server.update_contact(contact, canc);
        }
    }

    public GLib.List<SheepleContactField> _email;
    public unowned GLib.List<SheepleContactField> email
    {
        get
        {
            if(_email == null)
            {
                unowned GLib.List<GData.GDEmailAddress> addrs;
                
                addrs = contact.get_email_addresses();
                _email = new GLib.List<SheepleContactField>();

                foreach(GData.GDEmailAddress addr in addrs)
                {
                    SheepleContactField cfield = new SheepleContactEmail();
                    if(addr.get_relation_type() != null)
                        cfield.label = addr.get_relation_type();
                    else
                        cfield.label = addr.get_label();

                    cfield.data = addr.get_address();
                    cfield.primary = addr.is_primary;
                    
                    _email.prepend(cfield);
                }
            }
            
            return _email;
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            _email = value.copy();
            
            contact.remove_all_email_addresses();

            foreach(SheepleContactField cf in _email)
            {
                GData.GDEmailAddress addr;

                if(cf.data == "")
                    continue;

                if("schemas.google.com" in cf.label)
                    addr = new GData.GDEmailAddress(cf.data, cf.label, null, cf.primary);
                else
                    addr = new GData.GDEmailAddress(cf.data, null, cf.label, cf.primary);
                contact.add_email_address(addr);
            }

            contact = server.update_contact(contact, canc);
        }
    }
    public GLib.List<SheepleContactField> _phone;
    public unowned GLib.List<SheepleContactField> phone
    {
        get
        {
            if(_phone == null)
            {
                unowned GLib.List<GData.GDPhoneNumber> nums;
                
                nums = contact.get_phone_numbers();
                _phone = new GLib.List<SheepleContactField>();

                foreach(GData.GDPhoneNumber num in nums)
                {
                    SheepleContactField cfield = new SheepleContactPhone();
                    cfield.label = num.get_label();
                    cfield.data = num.get_number();
                    cfield.primary = num.is_primary;
                    _phone.prepend(cfield);
                }
            }
            
            return _phone;
        }
        
        set
        {
            GLib.Cancellable canc = new GLib.Cancellable();
            _phone = value.copy();
            
            contact.remove_all_phone_numbers();

            foreach(SheepleContactField cf in _phone)
            {
                GData.GDPhoneNumber num;

                if(cf.data == "")
                    continue;

                if("schemas.google.com" in cf.label)
                    num = new GData.GDPhoneNumber(cf.data, cf.label, null, null, cf.primary);
                else
                    num = new GData.GDPhoneNumber(cf.data, null, cf.label, null, cf.primary);
                contact.add_phone_number(num);
            }

            contact = server.update_contact(contact, canc);
        }
    }

    public Gdk.Pixbuf _photo;
    public Gdk.Pixbuf photo
    {
        get
        {
            /*string photo_data = contact.get_photo(...);
            
            if(photo_data != null)
            {
                photo_loader = new Gdk.PixbufLoader.with_type();
                photo_loader.write(contact_photo->data.inlined.data,
                                   contact_photo->data.inlined.length, NULL);
                photo_loader.close(NULL);
                
                _photo = photo_loader.get_pixbuf();
            }

            return _photo;*/

            return _photo;
        }
        
        set
        {
        }
    }

    public SheepleGoogleContact(GData.ContactsContact ctc, GData.ContactsService inServer)
    {
        contact = ctc;
        server = inServer;
    }
}

public class SheepleGoogleBackendGroup : GLib.Object, SheepleBackendGroup
{
    private unowned GData.ContactsService server;
    private string id;
    private GLib.HashTable<string,GData.ContactsContact?> contactTable;
    
    public SheepleGoogleBackendGroup(GData.ContactsService inServer, string inId)
    {
        server = inServer;
        id = inId;

        contactTable = new GLib.HashTable<string,GData.ContactsContact?>(GLib.str_hash,GLib.str_equal);
    }
    
    public string get_group_id()
    {
        return id;
    }
    
    public SheepleContact get_contact(string id)
    {
        GData.ContactsContact contact = contactTable.lookup(id);
        SheepleContact ct = new SheepleGoogleContact(contact, server);
        return ct;
    }
    
    public void start()
    {
        GData.Feed feed;
        GData.Query query;
        GLib.Cancellable canc = new GLib.Cancellable();

        query = new GData.ContactsQuery(null);

        try
        {
            feed = server.query_contacts(query, canc, (entry, key, ct) => {
                GData.ContactsContact ctc = (GData.ContactsContact)entry;
                contactTable.insert(ctc.get_id(), ctc);
                this.contact_added(ctc.get_id());
            });
        }
        catch(Error e)
        {
            stdout.printf("Error while listing contacts...\n");
            stdout.printf("%s\n", e.message);
        }
    }
}

public class SheepleGoogleBackend : GLib.Object, SheepleBackend
{
    private GData.ContactsService server;
    private string username;
    private string password;

    public SheepleGoogleBackend(string inUsername, string inPassword)
    {
        username = inUsername;
        password = inPassword;
    }
    
    public string get_db_id()
    {
        return "Google";
    }
    
    public SheepleGroup get_group(string id)
    {
        SheepleGoogleBackendGroup bgp = new SheepleGoogleBackendGroup(server, id);
        SheepleGroup gp = new SheepleGroup(id, bgp);
        return gp;
    }
    
    public void start()
    {
        server = new GData.ContactsService("sheeple-0.1");
        try
        {
            server.authenticate_async(username, password, null, (obj, result) => {
                stdout.printf("Authenticated: %d\n", (int)server.is_authenticated());
                this.group_added("Contacts");
            });
        }
        catch(Error e)
        {
            stdout.printf("Problem authenticating to Google as %s!\n", username);
        }
    }
}
