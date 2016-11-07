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
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "opendavinci/generated/odcore/data/dmcp/CPUConsumption.h"
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
                m_dataView->setColumnWidth(0, 350);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);
                
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
                odcore::data::dmcp::ModuleStatistics ms = container.getData<odcore::data::dmcp::ModuleStatistics>();
                
                string componentName="noName";
                string componentIdentifier="noIdentifier";
                bool empty=true;
                double cpu_avg=0.0, cpu_od=0.0;
                uint64_t mem_vm=0, mem_rss=0;
                
                if(! ms.isEmpty_ListOfModuleStatistics())
                {
                    odcore::data::dmcp::ModuleDescriptor md=ms.getListOfModuleStatistics().at(0).getModule();
                    componentName=md.getName();
                    componentIdentifier=md.getIdentifier();
                    cpu_avg= ms.getListOfModuleStatistics().at(0).getRuntimeStatistic().getCpuConsumption().getAverage();
                    cpu_od = ms.getListOfModuleStatistics().at(0).getRuntimeStatistic().getCpuConsumption().getOnDemand();
                    mem_vm = ms.getListOfModuleStatistics().at(0).getRuntimeStatistic().getMemConsumption().getTotalVM();
                    mem_rss= ms.getListOfModuleStatistics().at(0).getRuntimeStatistic().getMemConsumption().getRSS();
                    empty=false;
                }
                
                if(empty)
                    return;
                
                // Create new entry if needed
                if (m_components.find(componentName) == m_components.end()) {
                    QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                    newHeader->setText(0, componentName.c_str());
                    m_components[componentName] = newHeader;
                }
                QTreeWidgetItem *componentEntry = m_components[componentName];

                {
                    // Search for avg CPU statistics entry.
                    stringstream sstr;
                    sstr << componentName << "-"<< componentIdentifier << "-CPU-AVG";
                    const string subentryCPU = sstr.str();
                    // search for the avg CPU stats container
                    if (m_CPUStatisticsPerComponent.find(subentryCPU) == m_CPUStatisticsPerComponent.end()) {
                        QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                        stringstream ss;
                        ss<<"CPU Average Usage Level [%] (history="<<+m_MAX_CPU_HISTORY<<")";
                        newComponentStatisticsHeader->setText(0, ss.str().c_str());
                        m_CPUStatisticsPerComponent[subentryCPU] = newComponentStatisticsHeader;

                        componentEntry->insertChild(0, newComponentStatisticsHeader);
                    }
                    // add the new value
                    QTreeWidgetItem *componentSubEntryCPU = m_CPUStatisticsPerComponent[subentryCPU];
                    {
                        QTreeWidgetItem *entry = new QTreeWidgetItem();
                        stringstream timestamp;
                        timestamp << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                        stringstream cpu;
                        cpu<<"CPU "<<cpu_avg<<" %";

                        entry->setText(0, timestamp.str().c_str());
                        entry->setText(1, cpu.str().c_str());
                        componentSubEntryCPU->insertChild(0, entry);

                        componentSubEntryCPU->takeChild(m_MAX_CPU_HISTORY);
                    }
                }
                {
                    // Search for od CPU statistics entry.
                    stringstream sstr;
                    sstr << componentName << "-"<< componentIdentifier << "-CPU-OD";
                    const string subentryCPU = sstr.str();
                    // search for the od CPU stats container
                    if (m_CPUStatisticsPerComponent.find(subentryCPU) == m_CPUStatisticsPerComponent.end()) {
                        QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                        stringstream ss;
                        ss<<"CPU On-demand Usage Level [ %] (history="<<+m_MAX_CPU_HISTORY<<")";
                        newComponentStatisticsHeader->setText(0, ss.str().c_str());
                        m_CPUStatisticsPerComponent[subentryCPU] = newComponentStatisticsHeader;

                        componentEntry->insertChild(0, newComponentStatisticsHeader);
                    }
                    // add the new value
                    QTreeWidgetItem *componentSubEntryCPU = m_CPUStatisticsPerComponent[subentryCPU];
                    {
                        QTreeWidgetItem *entry = new QTreeWidgetItem();
                        stringstream timestamp;
                        timestamp << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                        stringstream cpu;
                        cpu<<"CPU "<<cpu_od<<"%";

                        entry->setText(0, timestamp.str().c_str());
                        entry->setText(1, cpu.str().c_str());
                        componentSubEntryCPU->insertChild(0, entry);

                        componentSubEntryCPU->takeChild(m_MAX_CPU_HISTORY);
                    }
                }
                {
                    // Search for MEM statistics entry.
                    stringstream sstr;
                    sstr << componentName << "-"<< componentIdentifier << "-MEM-TVM";
                    const string subentryMEM = sstr.str();
                    
                    if (m_MEMStatisticsPerComponent.find(subentryMEM) == m_MEMStatisticsPerComponent.end()) {
                        QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                        stringstream ss;
                        ss<<"MEM Total VM Allocated [Bytes] (history="<<+m_MAX_MEM_HISTORY<<")";
                        newComponentStatisticsHeader->setText(0, ss.str().c_str());
                        m_MEMStatisticsPerComponent[subentryMEM] = newComponentStatisticsHeader;

                        componentEntry->insertChild(1, newComponentStatisticsHeader);
                    }
                    // add the new value
                    QTreeWidgetItem *componentSubEntryMEM = m_MEMStatisticsPerComponent[subentryMEM];
                    {
                        QTreeWidgetItem *entry = new QTreeWidgetItem();
                        stringstream timestamp;
                        timestamp << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                        stringstream mem;
                        mem<<"MEM "<<mem_vm<<"B";
                        entry->setText(0, timestamp.str().c_str());
                        entry->setText(1, mem.str().c_str());
                        componentSubEntryMEM->insertChild(0, entry);

                        componentSubEntryMEM->takeChild(m_MAX_MEM_HISTORY);
                    }
                }
                {
                    // Search for MEM statistics entry.
                    stringstream sstr;
                    sstr << componentName << "-"<< componentIdentifier << "-MEM-RSS";
                    const string subentryMEM = sstr.str();
                    
                    if (m_MEMStatisticsPerComponent.find(subentryMEM) == m_MEMStatisticsPerComponent.end()) {
                        QTreeWidgetItem *newComponentStatisticsHeader = new QTreeWidgetItem();
                        stringstream ss;
                        ss<<"MEM Resident Set Size [Bytes] (history="<<+m_MAX_MEM_HISTORY<<")";
                        newComponentStatisticsHeader->setText(0, ss.str().c_str());
                        m_MEMStatisticsPerComponent[subentryMEM] = newComponentStatisticsHeader;

                        componentEntry->insertChild(1, newComponentStatisticsHeader);
                    }
                    // add the new value
                    QTreeWidgetItem *componentSubEntryMEM = m_MEMStatisticsPerComponent[subentryMEM];
                    {
                        QTreeWidgetItem *entry = new QTreeWidgetItem();
                        stringstream timestamp;
                        timestamp << container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                        stringstream mem;
                        mem<<"MEM "<<mem_rss<<"B";
                        entry->setText(0, timestamp.str().c_str());
                        entry->setText(1, mem.str().c_str());
                        componentSubEntryMEM->insertChild(0, entry);

                        componentSubEntryMEM->takeChild(m_MAX_MEM_HISTORY);
                    }
                }
            }
       }
    }
}
