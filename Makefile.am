#SUBDIRS = po

### automake options ###

AUTOMAKE_OPTIONS = gnu dist-bzip2 subdir-objects
ACLOCAL_AMFLAGS = -I m4

### initial values ###

CLEANFILES = 
bin_PROGRAMS = 
lib_LTLIBRARIES = 
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"

### intltool ###

INTLTOOL_FILES = \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

DISTCLEANFILES = \
	intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

### sheeple documentation ###

docdir = ${prefix}/doc/sheeple
doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS

### libsheeple ###

lib_LTLIBRARIES += libsheeple.la

libsheeple_la_SOURCES = \
    src/libsheeple/SheepleSourceView.c \
    src/libsheeple/SheepleSourceView.h \
    src/libsheeple/SheepleSource.c \
    src/libsheeple/SheepleSource.h \
    src/libsheeple/SheepleGroup.c \
    src/libsheeple/SheepleGroup.h \
    src/libsheeple/sheeple.c \
    src/libsheeple/sheeple.h

libsheeple_la_CFLAGS = $(SHEEPLE_CFLAGS) -Isrc
libsheeple_la_LDFLAGS = $(SHEEPLE_LIBS)

libsheepleheaders_HEADERS = \
    src/libsheeple/sheeple.h \
    src/libsheeple/SheepleSourceView.h \
    src/libsheeple/SheepleSource.h \
    src/libsheeple/SheepleGroup.h

libsheepleheadersdir = $(pkgincludedir)

pkgconfig_DATA = src/libsheeple/libsheeple-1.0.pc
pkgconfigdir = $(libdir)/pkgconfig

### sheeple application ###

#uidir = $(datadir)/sheeple/ui
#ui_DATA = src/sheeple/sheeple.ui

bin_PROGRAMS += sheeple

sheeple_SOURCES = \
	src/sheeple/main.c

sheeple_CFLAGS = $(SHEEPLE_CFLAGS) -Isrc
sheeple_LDFLAGS = -Wl,--export-dynamic
sheeple_LDADD = $(SHEEPLE_LIBS) libsheeple.la

### extra-dist ###

EXTRA_DIST = $(ui_DATA) $(doc_DATA) $(INTLTOOL_FILES)

### uninstallation ###

uninstall-local:
	-rm -r $(docdir)
	-rm -r $(uidir)
	-rm -r $(datadir)/sheeple

### gobject-introspection ###

if HAVE_INTROSPECTION
BUILT_GIRSOURCES =

Sheeple-1.0.gir: $(INTROSPECTION_SCANNER) libsheeple.la
	$(QUIET_GEN)$(INTROSPECTION_SCANNER) -v \
	    -I src \
		--namespace Sheeple --nsversion=1.0 \
		--include=GObject-2.0 \
		--include=Gtk-2.0 \
		--include=Pango-1.0 \
		--include=Avahi-0.6 \
		--include=AvahiCore-0.6 \
		--include=WebKit-1.0 \
		--library=libsheeple.la \
		--libtool="$(top_builddir)/libtool" \
        --pkg gobject-2.0 \
        --pkg gtk+-2.0 \
        --pkg pango \
        --pkg libedataserver-1.2 \
        --pkg libebook-1.2 \ 
        --pkg avahi-client \
        --pkg avahi-core \
        --pkg avahi-gobject \
        --pkg avahi-glib \
        --pkg webkit-1.0 \
        --output $@ \
		$(libsheeple_la_SOURCES)

BUILT_GIRSOURCES += Sheeple-1.0.gir

# INTROSPECTION_GIRDIR/INTROSPECTION_TYPELIBDIR aren't the right place to
# install anything - we need to install inside our prefix.
girdir = $(datadir)/gir-1.0
gir_DATA = $(BUILT_GIRSOURCES)

typelibsdir = $(libdir)/girepository-1.0/

typelibs_DATA = $(BUILT_GIRSOURCES:.gir=.typelib)

%.typelib: %.gir $(INTROSPECTION_COMPILER)
	$(QUIET_GEN) \
	LD_LIBRARY_PATH=.libs$${LD_LIBRARY_PATH:+:$$LD_LIBRARY_PATH} \
	$(INTROSPECTION_COMPILER) \
		--includedir=$(srcdir) \
		--includedir=. \
		$(INTROSPECTION_COMPILER_OPTS) $< -o $(@F)

CLEANFILES += $(BUILT_GIRSOURCES) $(typelibs_DATA)
endif

### special build rules ###
lint:
	splint $(SHEEPLE_CFLAGS) -I. -Isrc -nullpass -nullassign -badflag src/sheeple/*.[ch] src/libsheeple/*.[ch]

indent:
	cd src/libsheeple ; bash ../../indent.sh
	cd src/sheeple ; bash ../../indent.sh

