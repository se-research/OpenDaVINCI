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

#include <Qt/qgridlayout.h>
#include <Qt/qtimer.h>
#include <qcolor.h>

#include "core/platform.h"
#include "core/data/Container.h"
#include "core/opendavinci.h"
#include "generated/coredata/dmcp/ModuleDescriptor.h"
#include "generated/coredata/dmcp/ModuleStatistic.h"
#include "plugins/modulestatisticsviewer/LoadPerModule.h"
#include "plugins/modulestatisticsviewer/LoadPlot.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            using namespace std;
            using namespace core::base;
            using namespace coredata;
            using namespace core::data;
            using namespace coredata::dmcp;

            ModuleStatisticsViewerWidget::ModuleStatisticsViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                    QWidget(prnt),
                    m_plot(NULL),
                    m_moduleStatistics(),
                    m_loadPerModule(),
                    m_color(0) {

                // Set size.
                setMinimumSize(640, 480);

                m_plot = new LoadPlot(this);

                // Show the axes
                m_plot->setCanvasLineWidth(2);

                QGridLayout* mainGrid = new QGridLayout(this);
                mainGrid->addWidget(m_plot, 0, 0, 1, 3);

                QTimer *timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), m_plot, SLOT(replot()));
                const uint32_t fps = 5;
                timer->start(1000 / fps);
            }

            ModuleStatisticsViewerWidget::~ModuleStatisticsViewerWidget() {
                m_loadPerModule.clear();
                OPENDAVINCI_CORE_DELETE_POINTER(m_plot);
            }

            void ModuleStatisticsViewerWidget::nextContainer(Container &c) {
                if (c.getDataType() == Container::MODULESTATISTICS) {
                    ModuleStatistics ms = c.getData<ModuleStatistics>();
                    m_moduleStatistics.push_back(ms);

                    // Get the iterator to the entries.
    				std::pair<std::map<std::string, coredata::dmcp::ModuleStatistic>::iterator, std::map<std::string, coredata::dmcp::ModuleStatistic>::iterator> iterators = ms.iteratorPair_MapOfModuleStatistics();

                    std::map<std::string, coredata::dmcp::ModuleStatistic>::iterator it = iterators.first;
                    while (it != iterators.second) {
                        ModuleStatistic entry = it->second;

                        // Lookup module in map.
                        core::SharedPointer<LoadPerModule> lpm = m_loadPerModule[entry.getModule().getName()];
                        if (!lpm.isValid()) {
                            const uint32_t R = (m_color > 255) ? 255 : m_color;
                            const uint32_t G = (m_color > 510) ? 255 : ( (m_color > 255) ? (m_color-255) : 0 );
                            const uint32_t B = (m_color > 510) ? (m_color-510) : 0;
                            QColor color(R, G, B);
                            lpm = core::SharedPointer<LoadPerModule>(new LoadPerModule(entry.getModule(), color));
                            m_loadPerModule[entry.getModule().getName()] = lpm;
                            m_plot->addLoadPerModule(lpm);

                            m_color += 30;

                            if (m_color > 750) {
                                m_color = 0;
                            }
                        }

                        // Add statistic.
                        lpm->addRuntimeStatistics(entry.getRuntimeStatistic());

                        it++;
                    }
                }
            }
        }
    }
} // plugins::modulestatisticsviewer
