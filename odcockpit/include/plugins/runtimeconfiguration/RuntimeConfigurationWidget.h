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

#ifndef RUNTIMECONFIGURATIONWIDGET_H_
#define RUNTIMECONFIGURATIONWIDGET_H_

#include <QtCore>
#include <QtGui>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "automotivedata/generated/automotive/VehicleControl.h"
#include "automotivedata/generated/automotive/miniature/UserButtonData.h"

#include <opendavinci/generated/odcockpit/RuntimeConfiguration.h>

class QTableWidget;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

      namespace runtimeconfiguration {

          using namespace std;

            /**
             * This class is the container for the runtimeconfiguration widget.
             */
            class RuntimeConfigurationWidget : public QWidget {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    RuntimeConfigurationWidget(const RuntimeConfigurationWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    RuntimeConfigurationWidget& operator=(const RuntimeConfigurationWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param conf Client conference to send data to.
                     * @param prnt Pointer to the parental widget.
                     */
                    RuntimeConfigurationWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt);

                    virtual ~RuntimeConfigurationWidget();

                public slots:
                    void TimerEvent();
                    void tableItemChanged(QTableWidgetItem * item);
                    void changeSenderStamp(int v);

                private:
                    odcore::io::conference::ContainerConference &m_conference;

                    QSpinBox *m_senderStampSelector;
                    QTableWidget *m_keyValueTable;

                    odcore::base::Mutex m_runtimeConfigurationMutex;
                    odcockpit::RuntimeConfiguration m_runtimeConfiguration;
                    uint32_t m_senderStamp;
            };
        }
    }
}

#endif /*RUNTIMECONFIGURATIONWIDGET_H_*/

