using GLib;
using CouchDB;
using DBus;
using GnomeKeyring;

// TODO: needed to annotate 'unowned out' on find_items_sync

public class SheepleContact : GLib.Object
{
    public void test()
    {
        DBus.Connection conn;
        dynamic DBus.Object couchBus;
        
        conn = DBus.Bus.get(DBus.BusType.SESSION);
        
        couchBus = conn.get_object("org.desktopcouch.CouchDB", "/",
                                "org.desktopcouch.CouchDB");
        
        GnomeKeyring.lock_all_sync();
        
        GnomeKeyring.get_default_keyring((r, val) => {
        stdout.printf("Unlock %s %s %d\n\n", val, GnomeKeyring.result_to_message(r), r);
        GnomeKeyring.unlock_sync(val, "arst");
        
        
        
            // oauth tokens
            var attrs = new GnomeKeyring.AttributeList();
            unowned GLib.List<GnomeKeyring.Found> items;
            attrs.append_string("desktopcouch", "oauth");
            var res = GnomeKeyring.find_items_sync(GnomeKeyring.ItemType.GENERIC_SECRET,
                                    attrs, out items);
            
            stdout.printf("%s\n\n", GnomeKeyring.result_to_message(res));
            
            unowned GnomeKeyring.Found item = items.data;
            
            stdout.printf("%s\n", item.secret); 
            
            string [] token_items = item.secret.split(":", 4);
            
            if(res == GnomeKeyring.Result.OK && token_items != null)
            {
                string connString = "http://127.0.0.1:%d".printf(couchBus.getPort());
                stdout.printf("%s %s d\n", connString, token_items[0]);
                var couch = new CouchDB.Connection(connString);
                couch.enable_oauth(token_items[0],token_items[1],token_items[2],token_items[3]);
                
                unowned SList<string> dbs = couch.list_databases();
                
                foreach(string db in dbs)
                {
                    stdout.printf("%s\n", db);
                }
            }   
        
        
        
        });
        

    
    }
}
