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

GList *create_default_sources()
{
    GList *sources = NULL;

    GdkPixbuf *pbuf =
        gdk_pixbuf_new_from_file_at_size
        ("/usr/share/icons/gnome/scalable/apps/im-msn.svg", 16, 16, NULL);
    GdkPixbuf *pbuf2 =
        gdk_pixbuf_new_from_file_at_size
        ("/usr/share/icons/gnome/scalable/apps/system-users.svg", 16, 16, NULL);

    SheepleSource *sheeple_contacts, *sheeple_contacts_matt;
    SheepleGroup *group;

    GList *contacts_list = NULL, *matt_list = NULL;

    group = sheeple_group_new_with_name("Matt's Girls");
    sheeple_group_set_icon(group, pbuf);
    matt_list = g_list_prepend(matt_list, group);
    group = sheeple_group_new_with_name("Bus People");
    sheeple_group_set_icon(group, pbuf);
    matt_list = g_list_prepend(matt_list, group);

    group = sheeple_group_new_with_name("Family");
    sheeple_group_set_icon(group, pbuf2);
    contacts_list = g_list_prepend(contacts_list, group);
    group = sheeple_group_new_with_name("RCOS");
    sheeple_group_set_icon(group, pbuf2);
    contacts_list = g_list_prepend(contacts_list, group);
    group = sheeple_group_new_with_name("RPI Friends");
    sheeple_group_set_icon(group, pbuf2);
    contacts_list = g_list_prepend(contacts_list, group);

    sheeple_contacts = sheeple_source_new_with_name("Contacts");
    sheeple_source_set_groups(sheeple_contacts, contacts_list);

    sheeple_contacts_matt = sheeple_source_new_with_name("Matt's Contacts");
    sheeple_source_set_groups(sheeple_contacts_matt, matt_list);

    sources = g_list_prepend(sources, sheeple_contacts_matt);
    sources = g_list_prepend(sources, sheeple_contacts);

    return sources;
}

void sv_select_changed(SheepleSourceView * sourceview, gpointer user_data)
{
    SheepleGroup *gr = sheeple_source_view_get_selection(sourceview)->data;
    g_print("%s\n", sheeple_group_get_name(gr));
}

int main(int argc, char **argv)
{
    GList *sources;
    GtkWidget *window, *hbox, *textview, *sourceview;

    gtk_init(&argc, &argv);

    sources = create_default_sources();

    textview = gtk_text_view_new();

    sourceview = GTK_WIDGET(sheeple_source_view_new());
    sheeple_source_view_set_sources(SHEEPLE_SOURCE_VIEW(sourceview), sources);
    g_signal_connect(sourceview, "selection-changed",
                     G_CALLBACK(sv_select_changed), textview);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), sourceview, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), textview, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), hbox);

    gtk_widget_grab_focus(textview);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
