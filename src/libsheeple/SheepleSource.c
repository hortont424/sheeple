#include "SheepleSource.h"

G_DEFINE_TYPE(SheepleSource, sheeple_source, G_TYPE_OBJECT)

static void sheeple_source_init(SheepleSource * self)
{

}

static void sheeple_source_class_init(SheepleSourceClass * klass)
{

}

SheepleSource *sheeple_source_new()
{
    return g_object_new(SHEEPLE_TYPE_SOURCE, NULL);
}

SheepleSource *sheeple_source_new_with_name(const gchar * name)
{
    SheepleSource *src = g_object_new(SHEEPLE_TYPE_SOURCE, NULL);
    src->name = name;
    return src;
}
