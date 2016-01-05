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

#include <iostream>
#include <sstream>
#include <string>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"
#include "ContainerObserver.h"

#include "plugins/streetmapviewer/StreetMapPlugIn.h"
#include "plugins/streetmapviewer/StreetMapWidget.h"

class QWidget;
namespace core { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;
            using namespace core::base;
            using namespace core::strings;
            using namespace hesperia::data::environment;

            StreetMapPlugIn::StreetMapPlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                    PlugIn(name, kvc, prnt),
                    m_widget(NULL),
                    m_referenceLocation() {
                setDescription("This plugin visualizes the environment data using a map tile provider.");

                try {
                    const string LAT = kvc.getValue<string>("global.reference.WGS84.latitude");
                    const string LON = kvc.getValue<string>("global.reference.WGS84.longitude");

                    stringstream sstrLAT(LAT);
                    double vLAT = 0; sstrLAT >> vLAT;
                    string sLAT; sstrLAT >> sLAT >> sLAT;

                    stringstream sstrLON(LON);
                    double vLON = 0; sstrLON >> vLON;
                    string sLON; sstrLON >> sLON >> sLON;

                    WGS84Coordinate ref;
                    if (StringToolbox::equalsIgnoreCase(sLAT, "_north") && StringToolbox::equalsIgnoreCase(sLON, "_west")) {
                        ref = WGS84Coordinate(vLAT, WGS84Coordinate::NORTH, vLON, WGS84Coordinate::WEST);
                    }
                    else if (StringToolbox::equalsIgnoreCase(sLAT, "_north") && StringToolbox::equalsIgnoreCase(sLON, "_east")) {
                        ref = WGS84Coordinate(vLAT, WGS84Coordinate::NORTH, vLON, WGS84Coordinate::EAST);
                    }
                    else if (StringToolbox::equalsIgnoreCase(sLAT, "_south") && StringToolbox::equalsIgnoreCase(sLON, "_west")) {
                        ref = WGS84Coordinate(vLAT, WGS84Coordinate::SOUTH, vLON, WGS84Coordinate::WEST);
                    }
                    else if (StringToolbox::equalsIgnoreCase(sLAT, "_south") && StringToolbox::equalsIgnoreCase(sLON, "_east")) {
                        ref = WGS84Coordinate(vLAT, WGS84Coordinate::SOUTH, vLON, WGS84Coordinate::EAST);
                    }
                    else {
                        cerr << "[StreetMapPlugIn] Invalid specification of global.reference.WGS84.latitude and global.reference.WGS84.longitude." << endl;
                        cerr << "[StreetMapPlugIn] Expected values like global.reference.WGS84.latitude = 57.687745843_NORTH and global.reference.WGS84.longitude = 11.98219965283333_EAST." << endl;
                    }
                    m_referenceLocation = ref;

                    clog << "[StreetMapPlugIn] Reference frame located at " << m_referenceLocation.toString() << endl;
                }
                catch(...) {
                    cerr << "[StreetMapPlugIn] No WGS84 reference location specified at global.reference.WGS84.latitude and global.reference.WGS84.longitude in configuration." << endl;
                }

            }

            StreetMapPlugIn::~StreetMapPlugIn() {
            }

            void StreetMapPlugIn::setupPlugin() {
                m_widget = new StreetMapWidget(*this, getParentQWidget(), m_referenceLocation);

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_widget);
                }
            }

            void StreetMapPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_widget);
                }
            }

            QWidget* StreetMapPlugIn::getQWidget() const {
                return m_widget;
            }
        }
    }
} // plugins::streetmap

