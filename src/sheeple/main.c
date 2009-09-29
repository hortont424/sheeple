/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Tim Horton 2009 <hortont424@gmail.com>
 *
 * sheeple is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sheeple is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include <libsheeple/sheeple.h>

#include "callbacks.h"

#define UI_FILE PACKAGE_DATA_DIR"/sheeple/ui/sheeple.ui"

GtkWidget *create_window(void)
{
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error))
    {
        g_warning("Couldn't load builder file: %s", error->message);
        g_error_free(error);
    }

    /* This is important */
    gtk_builder_connect_signals(builder, NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_object_unref(builder);

    return window;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;

#ifdef ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif

    gtk_set_locale();
    gtk_init(&argc, &argv);

    window = create_window();
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
