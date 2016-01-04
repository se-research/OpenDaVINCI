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

#include "core/opendavinci.h"
#include "ContainerObserver.h"

#include "plugins/streetmapviewer/StreetMapPlugIn.h"
#include "plugins/streetmapviewer/StreetMapWidget.h"

class QWidget;
namespace core { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace core::base;

            StreetMapPlugIn::StreetMapPlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                    PlugIn(name, kvc, prnt),
                    m_widget(NULL) {
                setDescription("This plugin visualizes the environment data using a map tile provider.");
            }

            StreetMapPlugIn::~StreetMapPlugIn() {
            }

            void StreetMapPlugIn::setupPlugin() {
                m_widget = new StreetMapWidget(*this, getParentQWidget());

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

