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

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include <libsheeple/sheeple.h>
#include <libsheeple/SheepleEDSContact.h> // yuck
#include <libsheeple/SheepleEDSBackend.h> // yuck
#include <libsheeple/SheepleEDSBackendGroup.h> // yuck

SheepleBackend * eds;
SheepleContactList * contactlistview;
SheepleContactView * contactview;

void sv_select_changed(SheepleSourceView * sourceview, gpointer user_data)
{
    SheepleGroup *gr = sheeple_source_view_get_selection(sourceview)->data;
    GValue gr_val = { 0, };
    g_value_init(&gr_val, TYPE_SHEEPLE_GROUP);
    g_value_set_object(&gr_val, gr);
    g_object_set_property(G_OBJECT(contactlistview), "group", &gr_val);
}

void clv_select_changed(SheepleContactList * clv, gpointer user_data)
{
    SheepleContact *ctc = sheeple_contact_list_get_selection(clv)->data;

    GValue gr_val = { 0, };
    g_value_init(&gr_val, TYPE_SHEEPLE_CONTACT);
    g_value_set_object(&gr_val, ctc);
    g_object_set_property(G_OBJECT(contactview), "contact", &gr_val);
}

int main(int argc, char **argv)
{
    GList *sources;
    GtkWidget *window, *hbox, *sourceview, *pane;

    g_thread_init(NULL);
    gtk_init(&argc, &argv);
    
    SheepleStore * contact_store = sheeple_store_get_store();
    eds = SHEEPLE_BACKEND(sheeple_eds_backend_new());

    sourceview = GTK_WIDGET(sheeple_source_view_new());
    sheeple_source_view_set_store(SHEEPLE_SOURCE_VIEW(sourceview), contact_store);
    g_signal_connect(sourceview, "selection-changed",
                     G_CALLBACK(sv_select_changed), NULL);
    
    contactview = sheeple_contact_view_new();
    
    contactlistview = sheeple_contact_list_new();
    g_signal_connect(contactlistview, "selection-changed",
                     G_CALLBACK(clv_select_changed), NULL);
    
    sheeple_store_add_backend(contact_store, eds);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);
    
    pane = gtk_hpaned_new();
    gtk_paned_add1(GTK_PANED(pane), GTK_WIDGET(contactlistview));
    gtk_paned_add2(GTK_PANED(pane), GTK_WIDGET(contactview));

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), sourceview, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), gtk_vseparator_new(), FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), pane, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), hbox);

    gtk_widget_grab_focus(GTK_WIDGET(contactview));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
