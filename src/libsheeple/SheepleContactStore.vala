using GLib;

public class SheepleContactStoreItem
{
    string id;
    int db_id;
}

public class SheepleContactStore : GLib.Object
{
    private GLib.List<GLib.List<SheepleContactStoreItem>> contact_store;
}
