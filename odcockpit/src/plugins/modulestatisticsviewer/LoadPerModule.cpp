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

#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Weffc++"
#endif
    #include <qwt_plot_curve.h>
    #include <qwt_plot_item.h>
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic pop
# endif
#endif

#include <cstring>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "plugins/modulestatisticsviewer/LoadPerModule.h"

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::data::dmcp;

            LoadPerModule::LoadPerModule( const odcore::data::dmcp::ModuleDescriptor &md, const QColor &color) :
                    m_moduleDescriptor(md),
                    m_curve(NULL),
                    m_loadMutex(),
                    m_load(),
                    m_data(),
                    m_reference(),
                    m_referenceOffset(0) {

                    m_curve = new QwtPlotCurve(m_moduleDescriptor.toString().c_str());
                    m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
                    m_curve->setPen(QPen(color));
            }

            LoadPerModule::~LoadPerModule() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_curve);
            }

            void LoadPerModule::addRuntimeStatistics(const RuntimeStatistic &rts) {
                Lock l(m_loadMutex);
                m_load.push_back(rts);

                // Shift entries. TODO: Optimize.
                const uint32_t size = m_load.size();
                if (size > LoadPerModule::MAX_ENTRIES_TO_QUEUE) {
                    for (uint32_t i = 0; i < (size - LoadPerModule::MAX_ENTRIES_TO_QUEUE); i++) {
                        m_load.pop_front();
                    }
                    m_referenceOffset += (size - LoadPerModule::MAX_ENTRIES_TO_QUEUE);
                }

                // Copy data.
                m_data.clear();
                m_reference.clear();
                deque<RuntimeStatistic>::iterator it = m_load.begin();
                while (it != m_load.end()) {
                    const float f = (*it).getSliceConsumption();
                    m_data.push_back(f);
                    m_reference.push_back(m_referenceOffset + m_data.size());
                    it++;
                }

                // Set curve's data.
                    m_curve->setRawData(&m_reference[0], &m_data[0], m_data.size());
            }

            QwtPlotCurve* LoadPerModule::getCurve(){
                return m_curve;
            }

            const string LoadPerModule::getModuleName() const{
                return m_moduleDescriptor.toString();
            }

        }
    }
} // cockpit::plugins::modulestatisticsviewer
