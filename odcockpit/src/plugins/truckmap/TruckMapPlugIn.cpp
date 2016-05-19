/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#include "opendavinci/odcore/opendavinci.h"
#include "ContainerObserver.h"
#include "plugins/truckmap/TruckMapPlugIn.h"
#include "plugins/truckmap/TruckMapWidgetControl.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace truckmap {

            TruckMapPlugIn::TruckMapPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                    PlugIn(name, kvc, prnt),
                    m_kvc(kvc),
                    m_truckmapWidgetControl(NULL) {
                setDescription("This plugin displays the current object readings from the truck.");
            }

            TruckMapPlugIn::~TruckMapPlugIn() {
                // The widget m_truckmapWidget will be destroyed by Qt.
            }

            void TruckMapPlugIn::setupPlugin() {
                m_truckmapWidgetControl = new TruckMapWidgetControl(*this, m_kvc, getParentQWidget());

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_truckmapWidgetControl);
                }
            }

            void TruckMapPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_truckmapWidgetControl);
                }
            }

            QWidget* TruckMapPlugIn::getQWidget() const {
                return m_truckmapWidgetControl;
            }

        }
    }
}

