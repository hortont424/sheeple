using GLib;

public class SheepleContactStoreItem
{
    string id;
    string db_id;
}

public class SheepleContactStore : GLib.Object
{
    private GLib.List<GLib.List<SheepleContactStoreItem>> contact_store;
}
