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
#include "plugins/iruscharts/IrUsChartsPlugIn.h"
#include "plugins/iruscharts/IrUsChartsWidget.h"

class QWidget;
namespace core { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace iruscharts {

            using namespace core::io;

            IrUsChartsPlugIn::IrUsChartsPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(name, kvc, prnt),
                m_irusChartsWidget(NULL) {
                setDescription("This plugin displays the values of SensorBoardData over time.");
            }

            IrUsChartsPlugIn::~IrUsChartsPlugIn() {}

            void IrUsChartsPlugIn::setupPlugin() {
                m_irusChartsWidget = new IrUsChartsWidget(*this, getKeyValueConfiguration(), getParentQWidget());

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_irusChartsWidget);
                }

            }

            void IrUsChartsPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_irusChartsWidget);
                }
            }

            QWidget* IrUsChartsPlugIn::getQWidget() const {
                return m_irusChartsWidget;
            }
        }
    }
}

