.PHONY: clean run gitclean todo

SHEEPLE_CFLAGS = `pkg-config --cflags gobject-2.0 gtk+-2.0 pango \
    couchdb-glib-1.0 avahi-client avahi-core avahi-gobject avahi-glib webkit-1.0`

SHEEPLE_LDFLAGS = `pkg-config --libs gobject-2.0 gtk+-2.0 pango \
    couchdb-glib-1.0 avahi-client avahi-core avahi-gobject avahi-glib webkit-1.0`

VALA_FLAGS = --pkg gobject-2.0 --pkg gobject-2.0 --pkg gtk+-2.0

all: libsheeple.so sheeple

libsheeple.so: src/libsheeple/*.vala
	valac $(VALA_FLAGS) -C -H src/libsheeple/sheeple.h --library sheeple \
	    src/libsheeple/*.vala --basedir src/libsheeple -d src/libsheeple
	gcc -g -O0 $(SHEEPLE_CFLAGS) --shared -fPIC src/libsheeple/*.c \
	    -o libsheeple.so

sheeple: src/sheeple/*.c
	gcc -g -O0 $(SHEEPLE_CFLAGS) $(SHEEPLE_LDFLAGS) -I. -Isrc -L. \
	    -lsheeple src/sheeple/*.c -o sheeple

todo:
	cd src ; grep -n "TODO" libsheeple/*.vala sheeple/*.vala

gitclean:
	git clean -x -f -d

clean:
	rm -f src/libsheeple/*.[ch] src/libsheeple/*.so
	rm -f src/sheeple/*.o
	rm -f sheeple
	rm -f libsheeple.so

run: all
	LD_LIBRARY_PATH=. ./sheeple
