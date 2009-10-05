#include "SheepleSourceView.h"

G_DEFINE_TYPE(SheepleSourceView, sheeple_source_view, G_TYPE_OBJECT)

static void sheeple_source_view_init(SheepleSourceView * self)
{

}

static void sheeple_source_view_class_init(SheepleSourceViewClass * klass)
{

}

SheepleSourceView *sheeple_source_view_new()
{
    return g_object_new(SHEEPLE_TYPE_SOURCE_VIEW, NULL);
}

