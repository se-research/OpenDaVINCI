/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PLUGINS_STREETMAP_STREETMAPPLUGIN_H_
#define PLUGINS_STREETMAP_STREETMAPPLUGIN_H_

#include <string>

#include "opendlv/data/environment/WGS84Coordinate.h"

#include "plugins/PlugIn.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

class StreetMapWidget;

            /**
             * This class is visualizes map tiles.
             */
            class StreetMapPlugIn : public PlugIn {

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    StreetMapPlugIn(const StreetMapPlugIn &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    StreetMapPlugIn& operator=(const StreetMapPlugIn &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param name Name of this plugin.
                     * @param kvc KeyValueConfiguration for this GL-based widget.
                     * @param prnt Pointer to the container super window.
                     */
                    StreetMapPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget* prnt);

                    virtual ~StreetMapPlugIn();

                    virtual QWidget* getQWidget() const;

                    virtual void setupPlugin();

                    virtual void stopPlugin();

                private:
                    StreetMapWidget *m_widget;
                    opendlv::data::environment::WGS84Coordinate m_referenceLocation;
            };
        }
    }
} // plugins::streetmap

#endif /*PLUGINS_STREETMAP_STREETMAPPLUGIN_H_*/
