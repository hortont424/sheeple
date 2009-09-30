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

#include "SheepleSourceViewCellRenderer.h"

static GtkTreeStore *treestore;

enum {
    COL_SOURCES = 0,
    NUM_COLS
};

GtkWidget *create_view_and_model(void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkTreeIter iter, toplevel;
    GtkWidget *view;
    GdkColor bg_color;
    GtkTreeSelection *selection;

    treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
    gtk_tree_store_append(treestore, &iter, NULL);
    toplevel = iter;
    gtk_tree_store_set(treestore, &iter, COL_SOURCES, "Something here...", -1);
    gtk_tree_store_append(treestore, &iter, &toplevel);
    gtk_tree_store_set(treestore, &iter, COL_SOURCES, "Something here...", -1);

    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treestore));

    g_object_unref(treestore);  /* destroy store automatically with view */

    renderer = sheeple_source_view_cell_renderer_new();
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "name", COL_SOURCES);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), FALSE);
    
    // Set background; eventually, get this from the theme!!
    gdk_colormap_alloc_color(gdk_colormap_get_system(), &bg_color, TRUE, TRUE);
    gdk_color_parse("#d7dbd4", &bg_color);
    gtk_widget_modify_base(view, GTK_STATE_NORMAL, &bg_color);
    
    // Hide expanders (expand everything by default), but keep 12px indent
    // Eventually I'll have to solve expanders, probably, but not today.
    gtk_tree_view_set_show_expanders(GTK_TREE_VIEW(view), FALSE);
    gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(view), 12);
    gtk_tree_view_expand_all(GTK_TREE_VIEW(view));
    
    // Disable selection of anything in the treeview
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_NONE);
    gtk_widget_grab_focus(view);

    return view;
}

int main(int argc, char **argv)
{
    GtkWidget *window, *view;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 500);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    view = create_view_and_model();

    gtk_container_add(GTK_CONTAINER(window), view);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
