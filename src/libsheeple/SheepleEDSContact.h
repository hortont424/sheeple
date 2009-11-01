#ifndef __SHEEPLE_EDS_CONTACT_H__
#define __SHEEPLE_EDS_CONTACT_H__

#include <glib-object.h>
#include <libebook/e-book.h>

#define TYPE_SHEEPLE_EDS_CONTACT             (sheeple_eds_contact_get_type ())
#define SHEEPLE_EDS_CONTACT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SHEEPLE_EDS_CONTACT, SheepleEDSContact))
#define IS_SHEEPLE_EDS_CONTACT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SHEEPLE_EDS_CONTACT))
#define SHEEPLE_EDS_CONTACT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SHEEPLE_EDS_CONTACT, SheepleEDSContactClass))
#define IS_SHEEPLE_EDS_CONTACT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SHEEPLE_EDS_CONTACT))
#define SHEEPLE_EDS_CONTACT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SHEEPLE_EDS_CONTACT, SheepleEDSContactClass))
#define SHEEPLE_EDS_CONTACT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), TYPE_SHEEPLE_EDS_CONTACT, SheepleEDSContactPrivate))


typedef struct _SheepleEDSContact        SheepleEDSContact;
typedef struct _SheepleEDSContactClass   SheepleEDSContactClass;
typedef struct _SheepleEDSContactPrivate SheepleEDSContactPrivate;

struct _SheepleEDSContact
{
    GObject parent_instance;
    SheepleEDSContactPrivate * priv;
};

struct _SheepleEDSContactClass
{
    GObjectClass parent_class;
};

SheepleEDSContact * sheeple_eds_contact_new ();
GType sheeple_eds_contact_get_type (void);

EContact * sheeple_eds_contact_get_econtact(SheepleEDSContact *self);
void sheeple_eds_contact_set_econtact(SheepleEDSContact *self, EContact *ec);

char * sheeple_eds_contact_get_full_name(SheepleEDSContact *self);

#endif
