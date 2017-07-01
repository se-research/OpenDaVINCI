/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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
#include "plugins/chartviewer/ChartPlugIn.h"
#include "plugins/chartviewer/ChartWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace chartviewer {

            using namespace odcore::io;

            ChartPlugIn::ChartPlugIn(const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(title, kvc, prnt),
                m_dataType(dataType),
                m_senderStamp(senderStamp),
                m_fieldName(fieldName),
                m_chartWidget(NULL) {
                setDescription("This plugin displays the values over time.");
            }

            ChartPlugIn::~ChartPlugIn() {}

            void ChartPlugIn::setupPlugin() {
                m_chartWidget = new ChartWidget(*this, getName(), m_dataType, m_senderStamp, m_fieldName, getKeyValueConfiguration(), getParentQWidget());

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_chartWidget);
                }

            }

            void ChartPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_chartWidget);
                }
            }

            QWidget* ChartPlugIn::getQWidget() const {
                return m_chartWidget;
            }
        }
    }
}

