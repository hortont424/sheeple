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

static GtkListStore *liststore;

static gboolean increasing = TRUE;  /* direction of progress bar change */

enum {
    COL_PERCENTAGE = 0,
    COL_TEXT,
    NUM_COLS
};

#define STEP  0.01

gboolean increase_progress_timeout(GtkCellRenderer * renderer)
{
    GtkTreeIter iter;
    gfloat perc = 0.0;
    gchar buf[20];

    gtk_tree_model_get_iter_first(GTK_TREE_MODEL(liststore), &iter);    /* first and only row */

    gtk_tree_model_get(GTK_TREE_MODEL(liststore), &iter, COL_PERCENTAGE, &perc,
                       -1);

    if (perc > (1.0 - STEP) || (perc < STEP && perc > 0.0))
    {
        increasing = (!increasing);
    }

    if (increasing)
        perc = perc + STEP;
    else
        perc = perc - STEP;

    g_snprintf(buf, sizeof(buf), "%u %%", (guint) (perc * 100));

    gtk_list_store_set(liststore, &iter, COL_PERCENTAGE, perc, COL_TEXT, buf,
                       -1);

    return TRUE;                /* Call again */
}

GtkWidget *create_view_and_model(void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;
    GtkWidget *view;

    liststore = gtk_list_store_new(NUM_COLS, G_TYPE_FLOAT, G_TYPE_STRING);
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, COL_PERCENTAGE, 0.5, -1);  /* start at 50% */

    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));

    g_object_unref(liststore);  /* destroy store automatically with view */

    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "text", COL_TEXT);
    gtk_tree_view_column_set_title(col, "Progress");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    renderer = sheeple_source_view_cell_renderer_new();
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "percentage",
                                       COL_PERCENTAGE);
    gtk_tree_view_column_set_title(col, "Progress");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    g_timeout_add(50, (GSourceFunc) increase_progress_timeout, NULL);

    return view;
}

int main(int argc, char **argv)
{
    GtkWidget *window, *view;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 100);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    view = create_view_and_model();

    gtk_container_add(GTK_CONTAINER(window), view);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
