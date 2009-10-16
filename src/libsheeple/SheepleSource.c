#include "SheepleSource.h"

struct _SheepleSourcePrivate
{
    const gchar *name;
    GList *groups;
};

static void sheeple_source_dispose(GObject * gobject);
static void sheeple_source_finalize(GObject * gobject);

static void
sheeple_source_set_property(GObject * object,
                            guint property_id,
                            const GValue * value, GParamSpec * pspec);

static void
sheeple_source_get_property(GObject * object,
                            guint property_id,
                            GValue * value, GParamSpec * pspec);

G_DEFINE_TYPE(SheepleSource, sheeple_source, G_TYPE_OBJECT)
enum
{
    PROP_0,

    PROP_NAME
};

static void sheeple_source_init(SheepleSource * self)
{
    self->priv = SHEEPLE_SOURCE_GET_PRIVATE(self);
}

static void sheeple_source_class_init(SheepleSourceClass * klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    GParamSpec *pspec;

    gobject_class->set_property = sheeple_source_set_property;
    gobject_class->get_property = sheeple_source_get_property;

    gobject_class->dispose = sheeple_source_dispose;
    gobject_class->finalize = sheeple_source_finalize;

    pspec = g_param_spec_string("name", "Source Name",
                                "The displayable name of the SheepleSource",
                                "Unnamed",
                                G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_NAME, pspec);

    g_type_class_add_private(klass, sizeof(SheepleSourcePrivate));
}

static void
sheeple_source_set_property(GObject * object,
                            guint property_id,
                            const GValue * value, GParamSpec * pspec)
{
    SheepleSource *self = SHEEPLE_SOURCE(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_free((gpointer) self->priv->name);
        sheeple_source_set_name(self, g_value_dup_string(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

static void
sheeple_source_get_property(GObject * object,
                            guint property_id,
                            GValue * value, GParamSpec * pspec)
{
    SheepleSource *self = SHEEPLE_SOURCE(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_value_set_string(value, sheeple_source_get_name(self));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

SheepleSource *sheeple_source_new()
{
    return g_object_new(SHEEPLE_TYPE_SOURCE, NULL);
}

SheepleSource *sheeple_source_new_with_name(const gchar * name)
{
    return g_object_new(SHEEPLE_TYPE_SOURCE, "name", name, NULL);
}

const char *sheeple_source_get_name(SheepleSource * self)
{
    return self->priv->name;
}

void sheeple_source_set_name(SheepleSource * self, const char *name)
{
    self->priv->name = name;
}

GList *sheeple_source_get_groups(SheepleSource * self)
{
    return self->priv->groups;
}

void sheeple_source_set_groups(SheepleSource * self, GList * groups)
{
    self->priv->groups = groups;
}

static void sheeple_source_dispose(GObject * gobject)
{
    //SheepleSource *self = SHEEPLE_SOURCE(gobject);

    // Lose our reference to objects...

    /* Chain up to the parent class */
    G_OBJECT_CLASS(sheeple_source_parent_class)->dispose(gobject);
}

static void sheeple_source_finalize(GObject * gobject)
{
    SheepleSource *self = SHEEPLE_SOURCE(gobject);

    // We're really going away, free things

    g_free((gpointer) self->priv->name);
    g_list_free(self->priv->groups);

    /* Chain up to the parent class */
    G_OBJECT_CLASS(sheeple_source_parent_class)->finalize(gobject);
}
