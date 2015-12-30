/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include "core/platform.h"
#include "ContainerObserver.h"
#include "plugins/birdseyemap/BirdsEyeMapPlugIn.h"
#include "plugins/birdseyemap/BirdsEyeMapWidget.h"

class QWidget;
namespace core { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace core::base;

            BirdsEyeMapPlugIn::BirdsEyeMapPlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                    PlugIn(name, kvc, prnt),
                    m_widget(NULL) {
                setDescription("This plugin shows the entire environment in 2D.");
            }

            BirdsEyeMapPlugIn::~BirdsEyeMapPlugIn() {
            }

            void BirdsEyeMapPlugIn::setupPlugin() {
                m_widget = new BirdsEyeMapWidget(*this, getParentQWidget());

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_widget);
                }
            }

            void BirdsEyeMapPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_widget);
                }
            }

            QWidget* BirdsEyeMapPlugIn::getQWidget() const {
                return m_widget;
            }
        }
    }
} // plugins::birdseyemap

