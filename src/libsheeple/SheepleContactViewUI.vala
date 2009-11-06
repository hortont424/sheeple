using GLib;

public class SheepleContactViewUI : GLib.Object
{
    public string contact_view_css = """
<style>
h1
{
    font-size: 1em;
    margin: 0px;
    padding: 0px;
}

h2
{
    font-size: 0.75em;
    font-weight: normal;
    margin: 0px;
    padding: 0px;
}

h2.label
{
    font-size: 0.75em;
    font-weight: normal;
    color: #aaa;
    text-align: right;
    padding-right: 0.3em;
}

table
{
    width: 100%;
}

#icon
{
    width: 3em;
    height: 3em;
    border: 1px solid #aaa;
}
</style>
""";

    public string contact_view_source = """
<script>
function load_contact(ctc)
{
    document.write(ctc.full_name);
}
</script>

Test: 
""";
}
