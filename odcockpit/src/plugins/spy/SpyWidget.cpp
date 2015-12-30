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

#include <sstream>
#include <cstring>

#include "hesperia/data/environment/Position.h"
#include "core/data/TimeStamp.h"

#include "GeneratedHeaders_CoreData.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "plugins/spy/SpyWidget.h"

namespace cockpit {

    namespace plugins {

        namespace spy {

            using namespace std;
            using namespace core::data;

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
                //create new Header if needed
                if (m_dataToType.find(container.getDataType()) == m_dataToType.end()) {
                    QTreeWidgetItem * newHeader = new QTreeWidgetItem(m_dataView);
                    newHeader->setText(0, container.toString().c_str());
                    m_dataToType[container.getDataType()] = newHeader;
                }

                //append Data to respective Header
                QTreeWidgetItem * dataItem = new QTreeWidgetItem();
                dataItem->setText(0, DataToString(container).c_str());
                dataItem->setText(1, container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms().c_str());
                dataItem->setText(2, container.getSentTimeStamp().getYYYYMMDD_HHMMSSms().c_str());
                m_dataToType[container.getDataType()]->insertChild(0, dataItem);

                if (m_dataToType[container.getDataType()]->childCount() > 100000) {
                    m_dataToType[container.getDataType()]->removeChild(m_dataToType[container.getDataType()]->takeChild(100000));
                }
            }

            string SpyWidget::DataToString(Container &container) {
                switch (container.getDataType()) {
                    case Container::CONFIGURATION:
                       return container.getData<coredata::Configuration> ().toString();
                    case Container::FORCECONTROL:
                       return container.getData<automotive::ForceControl> ().toString();
                    case Container::DMCP_DISCOVER:
                       return container.getData<coredata::dmcp::DiscoverMessage> ().toString();
                    case Container::DMCP_CONFIGURATION_REQUEST:
                       return container.getData<coredata::dmcp::ModuleDescriptor> ().toString();
                    case Container::DMCP_MODULESTATEMESSAGE:
                       return container.getData<coredata::dmcp::ModuleStateMessage> ().toString();
                    case Container::DMCP_MODULEEXITCODEMESSAGE:
                       return container.getData<coredata::dmcp::ModuleExitCodeMessage> ().toString();
                    case Container::MODULESTATISTICS:
                       return container.getData<coredata::dmcp::ModuleStatistics> ().toString();
                    case Container::VEHICLEDATA:
                       return container.getData<automotive::VehicleData> ().toString();
                    case Container::PLAYER_COMMAND:
                       return container.getData<coredata::player::PlayerCommand> ().toString();
                    case Container::POSITION:
                       return container.getData<hesperia::data::environment::Position> ().toString();
                    case Container::RECORDER_COMMAND:
                       return container.getData<coredata::recorder::RecorderCommand> ().toString();
                    case Container::RUNTIMESTATISTIC:
                       return container.getData<coredata::dmcp::RuntimeStatistic> ().toString();
                    case Container::SHARED_DATA:
                       return container.getData<coredata::SharedData> ().toString();
                    case Container::SHARED_IMAGE:
                       return container.getData<coredata::image::SharedImage> ().toString();
                    case Container::TIMESTAMP:
                       return container.getData<core::data::TimeStamp> ().toString();
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
            }
        }
    }
}
