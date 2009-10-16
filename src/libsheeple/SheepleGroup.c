#include "SheepleGroup.h"

struct _SheepleGroupPrivate
{
    const gchar *name;
    GdkPixbuf *pixbuf;
};

static void sheeple_group_dispose(GObject * gobject);
static void sheeple_group_finalize(GObject * gobject);

static void
sheeple_group_set_property(GObject * object,
                           guint property_id,
                           const GValue * value, GParamSpec * pspec);

static void
sheeple_group_get_property(GObject * object,
                           guint property_id,
                           GValue * value, GParamSpec * pspec);

G_DEFINE_TYPE(SheepleGroup, sheeple_group, G_TYPE_OBJECT)
enum
{
    PROP_0,

    PROP_NAME,
    PROP_PIXBUF
};

static void sheeple_group_init(SheepleGroup * self)
{
    self->priv = SHEEPLE_GROUP_GET_PRIVATE(self);
}

static void sheeple_group_class_init(SheepleGroupClass * klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    GParamSpec *pspec;

    gobject_class->set_property = sheeple_group_set_property;
    gobject_class->get_property = sheeple_group_get_property;

    gobject_class->dispose = sheeple_group_dispose;
    gobject_class->finalize = sheeple_group_finalize;

    pspec = g_param_spec_string("name", "Group Name",
                                "The displayable name of the SheepleGroup",
                                "Unnamed",
                                G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_NAME, pspec);

    pspec = g_param_spec_object("pixbuf", "Group Icon",
                                "The icon used to represent the SheepleGroup",
                                GDK_TYPE_PIXBUF,
                                G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_PIXBUF, pspec);

    g_type_class_add_private(klass, sizeof(SheepleGroupPrivate));
}

static void
sheeple_group_set_property(GObject * object,
                           guint property_id,
                           const GValue * value, GParamSpec * pspec)
{
    SheepleGroup *self = SHEEPLE_GROUP(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_free((gpointer) self->priv->name);
        sheeple_group_set_name(self, g_value_dup_string(value));
        break;
    case PROP_PIXBUF:
        if (self->priv->pixbuf)
            g_object_unref(self->priv->pixbuf);
        sheeple_group_set_pixbuf(self, g_value_get_object(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

static void
sheeple_group_get_property(GObject * object,
                           guint property_id,
                           GValue * value, GParamSpec * pspec)
{
    SheepleGroup *self = SHEEPLE_GROUP(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_value_set_string(value, sheeple_group_get_name(self));
        break;
    case PROP_PIXBUF:
        g_value_set_object(value, sheeple_group_get_pixbuf(self));
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

SheepleGroup *sheeple_group_new()
{
    return g_object_new(SHEEPLE_TYPE_GROUP, NULL);
}

SheepleGroup *sheeple_group_new_with_name(const gchar * name)
{
    return g_object_new(SHEEPLE_TYPE_GROUP, "name", name, NULL);
}

SheepleGroup *sheeple_group_new_with_name_and_pixbuf(const gchar * name,
                                                     GdkPixbuf * pixbuf)
{
    return g_object_new(SHEEPLE_TYPE_GROUP, "name", name, "pixbuf", pixbuf,
                        NULL);
}

const char *sheeple_group_get_name(SheepleGroup * self)
{
    return self->priv->name;
}

void sheeple_group_set_name(SheepleGroup * self, const char *name)
{
    self->priv->name = name;
}

GdkPixbuf *sheeple_group_get_pixbuf(SheepleGroup * self)
{
    return self->priv->pixbuf;
}

void sheeple_group_set_pixbuf(SheepleGroup * self, GdkPixbuf * pixbuf)
{
    self->priv->pixbuf = pixbuf;
}

static void sheeple_group_dispose(GObject * gobject)
{
    //SheepleGroup *self = SHEEPLE_GROUP(gobject);

    // Lose our reference to objects...

    /* Chain up to the parent class */
    G_OBJECT_CLASS(sheeple_group_parent_class)->dispose(gobject);
}

static void sheeple_group_finalize(GObject * gobject)
{
    SheepleGroup *self = SHEEPLE_GROUP(gobject);

    // We're really going away, free things

    g_free((gpointer) self->priv->name);

    /* Chain up to the parent class */
    G_OBJECT_CLASS(sheeple_group_parent_class)->finalize(gobject);
}
