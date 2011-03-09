 /***********************************************************************************
 *  Orientation lock status area plugin
 *  Copyright (C) 2011 Mohammad Abu-Garbeyyeh
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <hildon/hildon.h>
#include <gconf/gconf-client.h>

#include "lib-orientation-lock-status-menu-widget.h"

#define ORIENTATION_LOCK_STATUS_PLUGIN_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE (obj, \
                            TYPE_ORIENTATION_LOCK_STATUS_PLUGIN, OrientationLockStatusPluginPrivate))

#define GCONF_KEY_ORIENTATION_LOCK       "/apps/osso/hildon-desktop/orientation_lock"
#define GCONF_KEY_MENU_ORIENTATION_LOCK  "/apps/osso/hildon-desktop/ui_can_rotate"

struct _OrientationLockStatusPluginPrivate
{
    GtkWidget *button;
    GConfClient *gconf_client;
    gpointer data;
};

HD_DEFINE_PLUGIN_MODULE (OrientationLockStatusPlugin, orientation_lock_status_plugin, HD_TYPE_STATUS_MENU_ITEM);

static void
orientation_lock_status_plugin_class_finalize (OrientationLockStatusPluginClass *klass) {}

static void
orientation_lock_status_plugin_class_init (OrientationLockStatusPluginClass *klass)
{
    g_type_class_add_private (klass, sizeof (OrientationLockStatusPluginPrivate));
}

static void
orientation_lock_status_plugin_on_button_clicked (GtkWidget *button, OrientationLockStatusPlugin *plugin)
{
    OrientationLockStatusPluginPrivate *priv = ORIENTATION_LOCK_STATUS_PLUGIN_GET_PRIVATE (plugin);

    // Toggle orientation lock
    gconf_client_set_bool (priv->gconf_client, GCONF_KEY_ORIENTATION_LOCK,
                           !gconf_client_get_bool (plugin->priv->gconf_client, GCONF_KEY_ORIENTATION_LOCK, NULL), NULL);

    // Update button text and status bar icon
    if (gconf_client_get_bool (priv->gconf_client, GCONF_KEY_ORIENTATION_LOCK, NULL)) {
        hildon_button_set_value (HILDON_BUTTON (priv->button), "Landscape orientation locked");
        GtkIconTheme *icon_theme = gtk_icon_theme_get_default ();
        GdkPixbuf *pixbuf = gtk_icon_theme_load_icon (icon_theme, "orientation-lock.landscape",
                            18, GTK_ICON_LOOKUP_NO_SVG, NULL);
        hd_status_plugin_item_set_status_area_icon (HD_STATUS_PLUGIN_ITEM (plugin), pixbuf);
        g_object_unref (pixbuf);
        hildon_button_set_image (HILDON_BUTTON (priv->button),
                                 gtk_image_new_from_icon_name ("orientation-lock-icon.landscape", GTK_ICON_SIZE_DIALOG));
    } else {
        hildon_button_set_value (HILDON_BUTTON (priv->button), "Auto-orientation enabled");
        hd_status_plugin_item_set_status_area_icon (HD_STATUS_PLUGIN_ITEM (plugin), NULL);
        hildon_button_set_image (HILDON_BUTTON (priv->button),
                                 gtk_image_new_from_icon_name ("orientation-lock-icon.auto", GTK_ICON_SIZE_DIALOG));
    }

    // We need to set auto-rotation to false in the menu, when orientation lock is true.
    gconf_client_set_bool (priv->gconf_client, GCONF_KEY_MENU_ORIENTATION_LOCK,
                           !gconf_client_get_bool (priv->gconf_client, GCONF_KEY_ORIENTATION_LOCK, NULL), NULL);
}

static void
orientation_lock_status_plugin_init (OrientationLockStatusPlugin *plugin)
{
    plugin->priv = ORIENTATION_LOCK_STATUS_PLUGIN_GET_PRIVATE (plugin);

    plugin->priv->gconf_client = gconf_client_get_default();
    g_assert(GCONF_IS_CLIENT(plugin->priv->gconf_client));

    plugin->priv->button = hildon_button_new (HILDON_SIZE_FINGER_HEIGHT | HILDON_SIZE_AUTO_WIDTH, HILDON_BUTTON_ARRANGEMENT_VERTICAL);
    hildon_button_set_style (HILDON_BUTTON (plugin->priv->button), HILDON_BUTTON_STYLE_PICKER);
    if (gconf_client_get_bool (plugin->priv->gconf_client, GCONF_KEY_ORIENTATION_LOCK, NULL)) {
        hildon_button_set_value (HILDON_BUTTON (plugin->priv->button), "Landscape orientation locked");

        GtkIconTheme *icon_theme = gtk_icon_theme_get_default ();
        GdkPixbuf *pixbuf = gtk_icon_theme_load_icon (icon_theme, "orientation-lock.landscape",
                            STATUS_AREA_ORIENTATION_LOCK_ICON_SIZE, GTK_ICON_LOOKUP_NO_SVG, NULL);
        hd_status_plugin_item_set_status_area_icon (HD_STATUS_PLUGIN_ITEM (plugin), pixbuf);
        g_object_unref (pixbuf);

        hildon_button_set_image (HILDON_BUTTON (plugin->priv->button),
                                 gtk_image_new_from_icon_name ("orientation-lock-icon.landscape", GTK_ICON_SIZE_DIALOG));
    } else {
        hildon_button_set_value (HILDON_BUTTON (plugin->priv->button), "Auto-orientation enabled");
        hildon_button_set_image (HILDON_BUTTON (plugin->priv->button),
                                 gtk_image_new_from_icon_name ("orientation-lock-icon.auto", GTK_ICON_SIZE_DIALOG));
    }
    hildon_button_set_title (HILDON_BUTTON (plugin->priv->button), "Orientation lock");
    gtk_button_set_alignment (GTK_BUTTON (plugin->priv->button), 0, 0);

    g_signal_connect (plugin->priv->button, "clicked", G_CALLBACK (orientation_lock_status_plugin_on_button_clicked), plugin);

    gtk_container_add (GTK_CONTAINER (plugin), plugin->priv->button);

    gtk_widget_show_all (plugin->priv->button);

    gtk_widget_show (GTK_WIDGET (plugin));
}
