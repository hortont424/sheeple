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

#include <config.h>

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include <libsheeple/sheeple.h>

GtkWidget *create_source_view_test(GHashTable *sources)
{
    GtkWidget *scrollbox, *layout, *master_vbox, *master_padding;
    GList *current_source_buttons = NULL;
    GHashTableIter iter;
    gpointer source_title, source_details;
    
    scrollbox = gtk_scrolled_window_new(NULL, NULL);
    layout = gtk_layout_new(NULL, NULL);
    master_vbox = gtk_vbox_new(FALSE, 10);
    
    // Iterate over all sources
    g_hash_table_iter_init(&iter, sources);
    while(g_hash_table_iter_next(&iter, &source_title, &source_details))
    {
        GtkWidget *sourcebox, *title_label;
        gchar *title_markup;
        GList *group_list = (GList *)source_details;
        
        sourcebox = gtk_vbox_new(FALSE, 0);
        
        // Create the source's title label
        title_markup = g_markup_printf_escaped("<span weight=\"bold\" size=\"small\">%s</span>",
                                               (const gchar *)source_title);
        title_label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
        gtk_misc_set_alignment(GTK_MISC(title_label), 0, 0);
        gtk_box_pack_start(GTK_BOX(sourcebox), title_label, TRUE, TRUE, 4);
        
        // Iterate over all groups within this source, creating
        // selection buttons for each group and packing them
        do
        {
            GtkWidget *button, *alignment, *button_label;
            gchar *button_markup;
            
            alignment = gtk_alignment_new(0, 0, 0, 0);
            gtk_alignment_set_padding(GTK_ALIGNMENT(alignment), 0, 0, 20, 4);
            
            button_markup = g_markup_printf_escaped("<span size=\"small\">%s</span>",
                                                    (const gchar *)group_list->data);
            
            button_label = gtk_label_new(NULL);
            gtk_label_set_markup(GTK_LABEL(button_label), button_markup);
            
            button = gtk_button_new();
            gtk_container_add(GTK_CONTAINER(button), button_label);
            gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
            gtk_button_set_focus_on_click(GTK_BUTTON(button), FALSE);
            
            gtk_container_add(GTK_CONTAINER(alignment), button);
            gtk_box_pack_start(GTK_BOX(sourcebox), alignment, TRUE, TRUE, 0);
        }
        while(group_list = g_list_next(group_list));
        
        gtk_box_pack_start(GTK_BOX(master_vbox), sourcebox, FALSE, TRUE, 0);
    }
    
    //gtk_layout_put(GTK_LAYOUT(layout), master_vbox, 0, 0);
    //gtk_container_add(GTK_CONTAINER(scrollbox), layout);
    
    // Pad the whole sourceview
    master_padding = gtk_alignment_new(0, 0, 1, 1);
    gtk_alignment_set_padding(GTK_ALIGNMENT(master_padding), 0, 0, 4, 4);
    gtk_container_add(GTK_CONTAINER(master_padding), master_vbox);

    return master_padding;
}

int main(int argc, char **argv)
{
    GtkWidget *window;
    GHashTable *sources = NULL;
    GList *contacts_list = NULL, *matt_list = NULL;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 300);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);
    
    matt_list = g_list_prepend(matt_list, "Matt's Girls");
    
    contacts_list = g_list_prepend(contacts_list, "Family");
    contacts_list = g_list_prepend(contacts_list, "RCOS");
    contacts_list = g_list_prepend(contacts_list, "RPI Friends");
    
    sources = g_hash_table_new(&g_str_hash, &g_str_equal);
    g_hash_table_insert(sources, "Contacts", contacts_list);
    g_hash_table_insert(sources, "Matt's Friends", matt_list);
    
    gtk_container_add(GTK_CONTAINER(window), create_source_view_test(sources));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

