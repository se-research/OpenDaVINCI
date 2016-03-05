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

#include <QtCore>
#include <QtGui>

#include <cstring>
#include <sstream>

#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/opendavinci.h"
#include "automotivedata/generated/automotive/ForceControl.h"
#include "automotivedata/generated/automotive/GenericCANMessage.h"
#include "automotivedata/generated/automotive/VehicleData.h"
#include "automotivedata/generated/automotive/miniature/UserButtonData.h"
#include "automotivedata/generated/automotive/vehicle/WheelSpeed.h"
#include "opendavinci/generated/odcore/data/Configuration.h"
#include "opendavinci/generated/odcore/data/SharedData.h"
#include "opendavinci/generated/odcore/data/dmcp/DiscoverMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"
#include "opendavinci/generated/odcore/data/player/PlayerCommand.h"
#include "opendavinci/generated/odcore/data/recorder/RecorderCommand.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Position.h"
#include "plugins/spy/SpyWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace spy {

            using namespace std;
            using namespace odcore::data;

            SpyWidget::SpyWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataView(NULL),
                m_dataToType() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = new QTreeWidget(this);
                m_dataView->setColumnCount(3);
                QStringList headerLabel;
                headerLabel << tr("Datatype") << tr("Received@") << tr("Sent@");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView, 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            SpyWidget::~SpyWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_dataView);
            }

            void SpyWidget::nextContainer(Container &container) {
                const string s = DataToString(container);
                if (s.size() > 0) {
                    //create new Header if needed
                    if (m_dataToType.find(container.getDataType()) == m_dataToType.end()) {
                        QTreeWidgetItem * newHeader = new QTreeWidgetItem(m_dataView);
                        newHeader->setText(0, container.toString().c_str());
                        m_dataToType[container.getDataType()] = newHeader;
                    }

                    //append Data to respective Header
                    QTreeWidgetItem * dataItem = new QTreeWidgetItem();
                    dataItem->setText(0, s.c_str());
                    dataItem->setText(1, container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms().c_str());
                    dataItem->setText(2, container.getSentTimeStamp().getYYYYMMDD_HHMMSSms().c_str());
                    m_dataToType[container.getDataType()]->insertChild(0, dataItem);

                    if (m_dataToType[container.getDataType()]->childCount() > 1000) {
                        m_dataToType[container.getDataType()]->removeChild(m_dataToType[container.getDataType()]->takeChild(1000));
                    }
                }
            }

            string SpyWidget::DataToString(Container &container) {
/*
                if (container.getDataType() == coredata::dmcp::ModuleStatistics::ID()) {
                   return container.getData<coredata::dmcp::ModuleStatistics>().toString();
                }
*/

                if (container.getDataType() == opendlv::data::environment::EgoState::ID()) {
                   return container.getData<opendlv::data::environment::EgoState>().toString();
                }

                if (container.getDataType() == automotive::VehicleData::ID()) {
                   return container.getData<automotive::VehicleData>().toString();
                }
                return "";
/*
                switch (container.getDataType()) {
                    case Container::CONFIGURATION:
                       return container.getData<odcore::data::Configuration> ().toString();
                    case Container::FORCECONTROL:
                       return container.getData<automotive::ForceControl> ().toString();
                    case Container::DMCP_DISCOVER:
                       return container.getData<odcore::data::dmcp::DiscoverMessage> ().toString();
                    case Container::DMCP_CONFIGURATION_REQUEST:
                       return container.getData<odcore::data::dmcp::ModuleDescriptor> ().toString();
                    case Container::DMCP_MODULESTATEMESSAGE:
                       return container.getData<odcore::data::dmcp::ModuleStateMessage> ().toString();
                    case Container::DMCP_MODULEEXITCODEMESSAGE:
                       return container.getData<odcore::data::dmcp::ModuleExitCodeMessage> ().toString();
                    case Container::MODULESTATISTICS:
                       return container.getData<odcore::data::dmcp::ModuleStatistics> ().toString();
                    case Container::VEHICLEDATA:
                       return container.getData<automotive::VehicleData> ().toString();
                    case Container::PLAYER_COMMAND:
                       return container.getData<odcore::data::player::PlayerCommand> ().toString();
                    case Container::POSITION:
                       return container.getData<opendlv::data::environment::Position> ().toString();
                    case Container::RECORDER_COMMAND:
                       return container.getData<odcore::data::recorder::RecorderCommand> ().toString();
                    case Container::RUNTIMESTATISTIC:
                       return container.getData<odcore::data::dmcp::RuntimeStatistic> ().toString();
                    case Container::SHARED_DATA:
                       return container.getData<odcore::data::SharedData> ().toString();
                    case Container::SHARED_IMAGE:
                       return container.getData<odcore::data::image::SharedImage> ().toString();
                    case Container::TIMESTAMP:
                       return container.getData<odcore::data::TimeStamp> ().toString();
                    case Container::USER_BUTTON:
                       return container.getData<automotive::miniature::UserButtonData> ().toString();
                    case Container::GENERIC_CAN_MESSAGE:
                       return container.getData<automotive::GenericCANMessage> ().toString();
                    case Container::WHEELSPEED:
                       return container.getData<automotive::vehicle::WheelSpeed> ().toString();
                    default:{
                        stringstream sstrType;
                        sstrType << "Type: " << container.getDataType() << ": " << container;
                        return sstrType.str();
                    }
                }
*/
            }
        }
    }
}
