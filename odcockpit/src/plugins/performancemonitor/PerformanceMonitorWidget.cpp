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

#include <QtCore>
#include <QtGui>

#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
//#include "opendavinci/generated/odcore/data/PerformanceMonitor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "plugins/performancemonitor/PerformanceMonitorWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace performancemonitor {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            PerformanceMonitorWidget::PerformanceMonitorWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataView(),
                m_components(),
                m_CPUStatisticsPerComponent(),
                m_MEMStatisticsPerComponent(),
                m_MAX_CPU_HISTORY(3),
                m_MAX_MEM_HISTORY(3) {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                //Federico: Here you can change the column names, number of columns, and size of columns
                headerLabel << tr("Component") << tr("Statistics");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);
                
                //The following 3 lines can print something in the window:
//                QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
//                newHeader->setText(0,"123"); //Left column
//                newHeader->setText(1,"456"); //Right column

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            PerformanceMonitorWidget::~PerformanceMonitorWidget() {}

            void PerformanceMonitorWidget::nextContainer(Container &container) {
                if (container.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
                    addContainerToTree(container);
                }
            }

            void PerformanceMonitorWidget::addContainerToTree(Container &container){
                odcore::data::dmcp::ModuleStatistics pm = container.getData<odcore::data::dmcp::ModuleStatistics>();

                string componentName="componentName";
                string componentIdentifier="componentIdentifier";
std::cout<<"modulestatistics size: "<<pm.getListOfModuleStatistics().size()<<std::endl;
                if(pm.getListOfModuleStatistics().size() > 0)
                {
                    odcore::data::dmcp::ModuleDescriptor md=pm.getListOfModuleStatistics().at(0).getModule();
                    componentName=md.getName();
                    componentIdentifier=md.getIdentifier();
                }
                std::cout << "DEBUG: process " << ::getpid() << " (parent: " << ::getppid() << ")" << std::endl;

                // Create new entry if needed
                if (m_components.find(componentName) == m_components.end()) {
                    QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                    newHeader->setText(0, componentName.c_str());
                    m_components[componentName] = newHeader;
                }
                QTreeWidgetItem *componentEntry = m_components[componentName];

                // Search for CPU statistics entry.
                stringstream sstr;
                sstr << componentName << "-"<< componentIdentifier << "-CPU";
                const string subentryCPU = sstr.str();
                
                if (m_CPUStatisticsPerComponent.find(subentryCPU) == m_CPUStatisticsPerComponent.end()) {
                    QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                    stringstream ss;
                    ss<<"CPU Usage Level (history="<<+m_MAX_CPU_HISTORY<<")";
                    newComponentStatisticsHeader->setText(0, ss.str().c_str());
                    m_CPUStatisticsPerComponent[subentryCPU] = newComponentStatisticsHeader;

                    componentEntry->insertChild(0, newComponentStatisticsHeader);
                }

                QTreeWidgetItem *componentSubEntryCPU = m_CPUStatisticsPerComponent[subentryCPU];
                {
                    QTreeWidgetItem *entry = new QTreeWidgetItem();
                    stringstream sstr2;
                    sstr2 << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();

                    entry->setText(0, sstr2.str().c_str());
                    entry->setText(1, "CPU X%");
                    componentSubEntryCPU->insertChild(0, entry);

                    componentSubEntryCPU->takeChild(m_MAX_CPU_HISTORY);
                }
               
               
                // Search for MEM statistics entry.
                sstr.str("");
                sstr << componentName << "-"<< componentIdentifier << "-MEM";
                const string subentryMEM = sstr.str();
                
                if (m_MEMStatisticsPerComponent.find(subentryMEM) == m_MEMStatisticsPerComponent.end()) {
                    QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                    stringstream ss;
                    ss<<"MEM Usage Level (history="<<+m_MAX_MEM_HISTORY<<")";
                    newComponentStatisticsHeader->setText(0, ss.str().c_str());
                    m_MEMStatisticsPerComponent[subentryMEM] = newComponentStatisticsHeader;

                    componentEntry->insertChild(1, newComponentStatisticsHeader);
                }

                QTreeWidgetItem *componentSubEntryMEM = m_MEMStatisticsPerComponent[subentryMEM];
                {
                    QTreeWidgetItem *entry = new QTreeWidgetItem();
                    stringstream sstr2;
                    sstr2 << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                    entry->setText(0, sstr2.str().c_str());
                    entry->setText(1, "MEM X%");
                    componentSubEntryMEM->insertChild(0, entry);

                    componentSubEntryMEM->takeChild(m_MAX_MEM_HISTORY);
                }
            }
       }
    }
}
