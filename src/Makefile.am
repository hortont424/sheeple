## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/sheeple/ui
ui_DATA = sheeple.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(SHEEPLE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = sheeple

sheeple_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c

sheeple_LDFLAGS = \
	-Wl,--export-dynamic

sheeple_LDADD = $(SHEEPLE_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/sheeple
