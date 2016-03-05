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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistic.h"
#include "plugins/modulestatisticsviewer/LoadPerModule.h"
#include "plugins/modulestatisticsviewer/LoadPlot.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::data;
            using namespace odcore::data::dmcp;

            ModuleStatisticsViewerWidget::ModuleStatisticsViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                    QWidget(prnt),
#ifdef HAVE_QWT5QWT4
                    m_plot(NULL),
#endif
                    m_moduleStatistics(),
#ifdef HAVE_QWT5QWT4
                    m_loadPerModule(),
#endif
                    m_color(0) {

                // Set size.
                setMinimumSize(640, 480);

#ifdef HAVE_QWT5QWT4
                m_plot = new LoadPlot(this);

                // Show the axes
                m_plot->setCanvasLineWidth(2);

                QGridLayout* mainGrid = new QGridLayout(this);
                mainGrid->addWidget(m_plot, 0, 0, 1, 3);

                QTimer *timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), m_plot, SLOT(replot()));
                const uint32_t fps = 5;
                timer->start(1000 / fps);
#endif
            }

            ModuleStatisticsViewerWidget::~ModuleStatisticsViewerWidget() {
#ifdef HAVE_QWT5QWT4
                m_loadPerModule.clear();
                OPENDAVINCI_CORE_DELETE_POINTER(m_plot);
#endif
            }

            void ModuleStatisticsViewerWidget::nextContainer(Container &c) {
#ifdef HAVE_QWT5QWT4
                if (c.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
                    ModuleStatistics ms = c.getData<ModuleStatistics>();
                    m_moduleStatistics.push_back(ms);

                    // Get the iterator to the entries.
                    std::pair<std::map<std::string, odcore::data::dmcp::ModuleStatistic>::iterator, std::map<std::string, odcore::data::dmcp::ModuleStatistic>::iterator> iterators = ms.iteratorPair_MapOfModuleStatistics();

                    std::map<std::string, odcore::data::dmcp::ModuleStatistic>::iterator it = iterators.first;
                    while (it != iterators.second) {
                        ModuleStatistic entry = it->second;

                        // Lookup module in map.
                        std::shared_ptr<LoadPerModule> lpm = m_loadPerModule[entry.getModule().getName()];
                        if (!lpm.get()) {
                            const uint32_t R = (m_color > 255) ? 255 : m_color;
                            const uint32_t G = (m_color > 510) ? 255 : ( (m_color > 255) ? (m_color-255) : 0 );
                            const uint32_t B = (m_color > 510) ? (m_color-510) : 0;
                            QColor color(R, G, B);
                            lpm = std::shared_ptr<LoadPerModule>(new LoadPerModule(entry.getModule(), color));
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
#endif
                }
            }
        }
    }
} // plugins::modulestatisticsviewer
