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

#ifndef __ORIENTATION_LOCK_STATUS_PLUGIN_H__
#define __ORIENTATION_LOCK_STATUS_PLUGIN_H__

#include <libhildondesktop/libhildondesktop.h>

G_BEGIN_DECLS

#define TYPE_ORIENTATION_LOCK_STATUS_PLUGIN            (orientation_lock_status_plugin_get_type ())

#define ORIENTATION_LOCK_STATUS_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                                    TYPE_ORIENTATION_LOCK_STATUS_PLUGIN, OrientationLockStatusPlugin))

#define ORIENTATION_LOCK_STATUS_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), \
                                TYPE_ORIENTATION_LOCK_STATUS_PLUGIN, OrientationLockStatusPluginClass))

#define IS_ORIENTATION_LOCK_STATUS_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                                    TYPE_ORIENTATION_LOCK_STATUS_PLUGIN))

#define IS_ORIENTATION_LOCK_STATUS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                                                    TYPE_ORIENTATION_LOCK_STATUS_PLUGIN))

#define ORIENTATION_LOCK_STATUS_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                            TYPE_ORIENTATION_LOCK_STATUS_PLUGIN, OrientationLockStatusPluginClass))

#define STATUS_AREA_ORIENTATION_LOCK_ICON_SIZE 18

typedef struct _OrientationLockStatusPlugin        OrientationLockStatusPlugin;
typedef struct _OrientationLockStatusPluginClass   OrientationLockStatusPluginClass;
typedef struct _OrientationLockStatusPluginPrivate OrientationLockStatusPluginPrivate;

struct _OrientationLockStatusPlugin
{
    HDStatusMenuItem parent;

    OrientationLockStatusPluginPrivate *priv;
};

struct _OrientationLockStatusPluginClass
{
    HDStatusMenuItemClass parent;
};

GType orientation_lock_status_plugin_get_type (void);

G_END_DECLS

#endif
