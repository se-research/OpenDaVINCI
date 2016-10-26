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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "ContainerObserver.h"

#include "plugins/streetmapviewer/StreetMapPlugIn.h"
#include "plugins/streetmapviewer/StreetMapWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::strings;
            using namespace opendlv::data::environment;

            StreetMapPlugIn::StreetMapPlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                    PlugIn(name, kvc, prnt),
                    m_widget(NULL),
                    m_referenceLocation() {
                setDescription("This plugin visualizes the environment data using a map tile provider.");

                try {
                    const double LAT = kvc.getValue<double>("global.reference.WGS84.latitude");
                    const double LON = kvc.getValue<double>("global.reference.WGS84.longitude");
                    m_referenceLocation = WGS84Coordinate(LAT, LON);
                }
                catch(...) {
                    cerr << "[StreetMapPlugIn] No WGS84 reference location specified like global.reference.WGS84.latitude = 57.687745843 and global.reference.WGS84.longitude = 11.98219965283333." << endl;
                    m_referenceLocation = WGS84Coordinate(57.70485804, 11.93831921);
                }
                clog << "[StreetMapPlugIn] Reference frame located at " << m_referenceLocation.toString() << endl;
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

