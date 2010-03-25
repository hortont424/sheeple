.PHONY: clean run gitclean todo vapi

SHEEPLE_CFLAGS = `pkg-config --cflags gobject-2.0 gtk+-2.0 pango \
    avahi-client avahi-core avahi-gobject avahi-glib \
    dbus-glib-1 gnome-keyring-1 libebook-1.2`

SHEEPLE_LDFLAGS = `pkg-config --libs gobject-2.0 gtk+-2.0 pango \
    avahi-client avahi-core avahi-gobject avahi-glib \
    dbus-glib-1 gnome-keyring-1 libebook-1.2`

VALA_FLAGS = --pkg gobject-2.0 --pkg gobject-2.0 --pkg gtk+-2.0 --vapidir=vapi \
             --pkg json-glib-1.0 --pkg dbus-glib-1 \
             --pkg gnome-keyring-1 --pkg pango

all: libsheeple.so sheeple

libsheeple.so: src/libsheeple/*.vala src/libsheeple/*.c src/libsheeple/*.h
	valac $(VALA_FLAGS) -C -H src/libsheeple/sheeple.h --library sheeple \
	    src/libsheeple/*.vala --basedir src/libsheeple -d src/libsheeple
	gcc -g -O0 $(SHEEPLE_CFLAGS) --shared -fPIC src/libsheeple/*.c \
	    -o libsheeple.so

sheeple: libsheeple.so src/sheeple/*.c
	gcc -g -O0 $(SHEEPLE_CFLAGS) $(SHEEPLE_LDFLAGS) -I. -Isrc -L. \
	    -lsheeple src/sheeple/*.c -o sheeple

vapi:
	cd vapi ; vala-gen-introspect seed seed
	cd vapi ; vapigen --pkg webkit-1.0 --pkg glib-2.0 --library seed seed/seed.gi
#	cd vapi ; vala-gen-introspect couchdb-glib-1.0 couchdb-glib-1.0
#	cd vapi ; vapigen --pkg json-glib-1.0 --library couchdb-glib-1.0 couchdb-glib-1.0/couchdb-glib-1.0.gi

todo:
	cd src ; grep -n "TODO" libsheeple/*.vala sheeple/*.vala

gitclean:
	git clean -x -f -d

clean:
	rm -f src/libsheeple/*.o src/libsheeple/*.so src/libsheeple/*.vapi
	rm -f src/sheeple/*.o
	rm -f sheeple
	rm -f libsheeple.so

run: all
	LD_LIBRARY_PATH=. ./sheeple
