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

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <sstream>
#include <cstring>

#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Position.h"
#include "core/SharedPointer.h"
#include "core/data/TimeStamp.h"
#include "core/reflection/Message.h"
#include "core/reflection/MessageFromVisitableVisitor.h"
#include "core/reflection/MessagePrettyPrinterVisitor.h"

#include "GeneratedHeaders_CoreData.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "plugins/livefeed/LiveFeedWidget.h"
#include "plugins/livefeed/MessageToTupleVisitor.h"

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace core;
            using namespace core::base;
            using namespace core::data;
            using namespace core::reflection;
            using namespace coredata::reflection;

            LiveFeedWidget::LiveFeedWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataView(NULL),
                m_dataToType() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = auto_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("Message") << tr("Value");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            LiveFeedWidget::~LiveFeedWidget() {}

            void LiveFeedWidget::nextContainer(Container &container) {
                transformContainerToTree(container);
            }

            void LiveFeedWidget::addMessageToTree(const string &messageName, core::data::Container &container, core::base::Visitable &v) {
                //create new Header if needed
                if (m_dataToType.find(messageName) == m_dataToType.end()) {
                    QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                    newHeader->setText(0, container.toString().c_str());
                    m_dataToType[messageName] = newHeader;
                }

                vector<pair<string, string> > entries;
                entries.push_back(make_pair("Sent", container.getSentTimeStamp().getYYYYMMDD_HHMMSSms()));
                entries.push_back(make_pair("Received", container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()));

                // Map attributes from message to the entries.
                MessageToTupleVisitor mttv(entries);
                v.accept(mttv);

                QTreeWidgetItem *entry = m_dataToType[messageName];
                if (static_cast<uint32_t>(entry->childCount()) != entries.size()) {
                    entry->takeChildren();

                    for (uint32_t i = 0; i < entries.size(); i++) {
                        QTreeWidgetItem *sent = new QTreeWidgetItem();
                        entry->insertChild(i, sent);
                    }
                }

                // Map tuples of <string, string> to the tree.
                for (uint32_t i = 0; i < entries.size(); i++) {
                    QTreeWidgetItem *child = entry->child(i);
                    child->setText(0, entries.at(i).first.c_str());
                    child->setText(1, entries.at(i).second.c_str());
                }
            }

            void LiveFeedWidget::transformContainerToTree(Container &container) {
                switch (container.getDataType()) {
                    case Container::EGOSTATE:
                    {
                        hesperia::data::environment::EgoState es = container.getData<hesperia::data::environment::EgoState>();
                        Message msg;

                        {
                            Field<double> *f = new Field<double>(es.getPosition().getX());
                            f->setLongIdentifier(1);
                            f->setShortIdentifier(1);
                            f->setLongName("EgoState.Position.X");
                            f->setShortName("Position.X");
                            f->setFieldDataType(coredata::reflection::AbstractField::DOUBLE_T);
                            f->setSize(sizeof(double));
                            msg.addField(SharedPointer<AbstractField>(f));
                        }
                        {
                            Field<double> *f = new Field<double>(es.getPosition().getY());
                            f->setLongIdentifier(2);
                            f->setShortIdentifier(2);
                            f->setLongName("EgoState.Position.Y");
                            f->setShortName("Position.Y");
                            f->setFieldDataType(coredata::reflection::AbstractField::DOUBLE_T);
                            f->setSize(sizeof(double));
                            msg.addField(SharedPointer<AbstractField>(f));
                        }
                        {
                            Field<double> *f = new Field<double>(es.getRotation().getAngleXY());
                            f->setLongIdentifier(3);
                            f->setShortIdentifier(3);
                            f->setLongName("EgoState.Heading.RAD");
                            f->setShortName("Heading.RAD");
                            f->setFieldDataType(coredata::reflection::AbstractField::DOUBLE_T);
                            f->setSize(sizeof(double));
                            msg.addField(SharedPointer<AbstractField>(f));
                        }
                        {
                            Field<double> *f = new Field<double>(es.getRotation().getAngleXY() * cartesian::Constants::RAD2DEG);
                            f->setLongIdentifier(4);
                            f->setShortIdentifier(4);
                            f->setLongName("EgoState.Heading.DEG");
                            f->setShortName("Heading.DEG");
                            f->setFieldDataType(coredata::reflection::AbstractField::DOUBLE_T);
                            f->setSize(sizeof(double));
                            msg.addField(SharedPointer<AbstractField>(f));
                        }

                        addMessageToTree("EgoState", container, msg);
                        break;
                    }
                    case Container::CONFIGURATION:
                    {
                        coredata::Configuration tmp = container.getData<coredata::Configuration>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::FORCECONTROL:
                    {
                        automotive::ForceControl tmp = container.getData<automotive::ForceControl>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::DMCP_DISCOVER:
                    {
                        coredata::dmcp::DiscoverMessage tmp = container.getData<coredata::dmcp::DiscoverMessage>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::DMCP_CONFIGURATION_REQUEST:
                    {
                        coredata::dmcp::ModuleDescriptor tmp = container.getData<coredata::dmcp::ModuleDescriptor>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::DMCP_MODULESTATEMESSAGE:
                    {
                        coredata::dmcp::ModuleStateMessage tmp = container.getData<coredata::dmcp::ModuleStateMessage>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::DMCP_MODULEEXITCODEMESSAGE:
                    {
                        coredata::dmcp::ModuleExitCodeMessage tmp = container.getData<coredata::dmcp::ModuleExitCodeMessage>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::MODULESTATISTICS:
                    {
                        coredata::dmcp::ModuleStatistics tmp = container.getData<coredata::dmcp::ModuleStatistics>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::VEHICLEDATA:
                    {
                        automotive::VehicleData tmp = container.getData<automotive::VehicleData>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::PLAYER_COMMAND:
                    {
                        coredata::player::PlayerCommand tmp = container.getData<coredata::player::PlayerCommand>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::RECORDER_COMMAND:
                    {
                        coredata::recorder::RecorderCommand tmp = container.getData<coredata::recorder::RecorderCommand>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::RUNTIMESTATISTIC:
                    {
                        coredata::dmcp::RuntimeStatistic tmp = container.getData<coredata::dmcp::RuntimeStatistic>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::SHARED_DATA:
                    {
                        coredata::SharedData tmp = container.getData<coredata::SharedData>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::SHARED_IMAGE:
                    {
                        coredata::image::SharedImage tmp = container.getData<coredata::image::SharedImage>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::USER_BUTTON:
                    {
                        automotive::miniature::UserButtonData tmp = container.getData<automotive::miniature::UserButtonData>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::GENERIC_CAN_MESSAGE:
                    {
                        automotive::GenericCANMessage tmp = container.getData<automotive::GenericCANMessage>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    case Container::WHEELSPEED:
                    {
                        automotive::vehicle::WheelSpeed tmp = container.getData<automotive::vehicle::WheelSpeed>();
                        if (dynamic_cast<Visitable*>(&tmp) != NULL) {
                            addMessageToTree(tmp.LongName(), container, tmp);
                        }
                        break;
                    }
                    default:
                    break;
                }
            }
        }
    }
}
