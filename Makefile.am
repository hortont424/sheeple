SUBDIRS = po

### automake options ###

AUTOMAKE_OPTIONS = gnu dist-bzip2 subdir-objects

### initial values ###

bin_PROGRAMS = 
AM_CFLAGS = -Wall -g
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

### sheeple application ###

uidir = $(datadir)/sheeple/ui
ui_DATA = src/sheeple/sheeple.ui

bin_PROGRAMS += sheeple

sheeple_SOURCES = \
	src/sheeple/callbacks.c \
	src/sheeple/callbacks.h \
	src/sheeple/main.c

sheeple_CFLAGS = $(SHEEPLE_CFLAGS)
sheeple_LDFLAGS = -Wl,--export-dynamic
sheeple_LDADD = $(SHEEPLE_LIBS)

### extra-dist ###

EXTRA_DIST = $(ui_DATA) $(doc_DATA) $(INTLTOOL_FILES)

### uninstallation ###
uninstall-local:
	-rm -r $(docdir)
	-rm -r $(uidir)
	-rm -r $(datadir)/sheeple

