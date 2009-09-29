SUBDIRS = po

### sheeple documentation ###

sheepledocdir = ${prefix}/doc/sheeple
sheepledoc_DATA = \
    README \
    COPYING \
    AUTHORS \
    ChangeLog \
    INSTALL \
    NEWS

INTLTOOL_FILES = \
    intltool-extract.in \
    intltool-merge.in \
    intltool-update.in

EXTRA_DIST = \
    $(sheepledoc_DATA) \
    $(INTLTOOL_FILES)

DISTCLEANFILES = \
    intltool-extract \
    intltool-merge \
    intltool-update \
    po/.intltool-merge-cache

# Remove doc/ui directory on uninstall
uninstall-local:
    -rm -r $(sheepledocdir)
    -rm -r $(uidir)
    -rm -r $(datadir)/sheeple

### sheeple application ###

uidir = $(datadir)/sheeple/ui
ui_DATA = src/sheeple.ui

AM_CPPFLAGS = \
    -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
    -DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
    $(SHEEPLE_CFLAGS)

AM_CFLAGS = -Wall -g

bin_PROGRAMS = sheeple

sheeple_SOURCES = \
    src/callbacks.c \
    src/callbacks.h \
    src/main.c

sheeple_LDFLAGS = -Wl,--export-dynamic

sheeple_LDADD = $(SHEEPLE_LIBS)

EXTRA_DIST = $(ui_DATA)
