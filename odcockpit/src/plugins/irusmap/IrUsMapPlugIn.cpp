/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include "core/platform.h"
#include "ContainerObserver.h"
#include "plugins/irusmap/IrUsMapPlugIn.h"
#include "plugins/irusmap/IrUsMapWidgetControl.h"

class QWidget;
namespace core { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace irusmap {

            IrUsMapPlugIn::IrUsMapPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                    PlugIn(name, kvc, prnt),
                    m_kvc(kvc),
                    m_irusmapWidgetControl(NULL) {
                setDescription("This plugin displays the current irus readings.");
            }

            IrUsMapPlugIn::~IrUsMapPlugIn() {
                // The widget m_irusmapWidget will be destroyed by Qt.
            }

            void IrUsMapPlugIn::setupPlugin() {
                m_irusmapWidgetControl = new IrUsMapWidgetControl(*this, m_kvc, getParentQWidget());

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_irusmapWidgetControl);
                }
            }

            void IrUsMapPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_irusmapWidgetControl);
                }
            }

            QWidget* IrUsMapPlugIn::getQWidget() const {
                return m_irusmapWidgetControl;
            }

        }
    }
}

