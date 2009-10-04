#include "SheepleGroup.h"

G_DEFINE_TYPE(SheepleGroup, sheeple_group, G_TYPE_OBJECT)

static void sheeple_group_init(SheepleGroup * self)
{

}

static void sheeple_group_class_init(SheepleGroupClass * klass)
{

}

SheepleGroup *sheeple_group_new()
{
    return g_object_new(SHEEPLE_TYPE_GROUP, NULL);
}

SheepleGroup *sheeple_group_new_with_name(const gchar * name)
{
    SheepleGroup *grp = g_object_new(SHEEPLE_TYPE_GROUP, NULL);
    grp->name = name;
    return grp;
}
