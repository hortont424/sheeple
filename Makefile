SHEEPLE_CFLAGS = `pkg-config --cflags gobject-2.0 gtk+-2.0 pango \
    couchdb-glib-1.0 avahi-client avahi-core avahi-gobject avahi-glib webkit-1.0`

SHEEPLE_LDFLAGS = `pkg-config --libs gobject-2.0 gtk+-2.0 pango \
    couchdb-glib-1.0 avahi-client avahi-core avahi-gobject avahi-glib webkit-1.0`

VALA_FLAGS = --pkg gobject-2.0 --pkg gobject-2.0 --pkg gtk+-2.0

all: libsheeple sheeple

libsheeple: src/libsheeple/*.vala
	valac $(VALA_FLAGS) -C -H src/libsheeple/sheeple.h --library sheeple \
	    src/libsheeple/*.vala --basedir src/libsheeple -d src/libsheeple
	gcc $(SHEEPLE_CFLAGS) --shared -fPIC src/libsheeple/*.c \
	    -o src/libsheeple/libsheeple.o

sheeple: src/sheeple/*.c
	gcc $(SHEEPLE_CFLAGS) $(SHEEPLE_LDFLAGS) -I. -Isrc -Lsrc/libsheeple \
	    -lsheeple src/sheeple/*.c -o sheeple

todo:
	cd src ; grep -n "TODO" libsheeple/*.vala sheeple/*.vala

gitclean:
	git clean -x -f -d

clean:
	rm src/libsheeple/*.[cho]
	rm src/sheeple/*.o
	rm sheeple
