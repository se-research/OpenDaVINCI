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

#include "core/SharedPointer.h"

#include "QtIncludes.h"
#include "plugins/modulestatisticsviewer/LoadPlot.h"
#include "plugins/modulestatisticsviewer/LoadPerModule.h"

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            LoadPlot::LoadPlot(QWidget* prnt) :
	            QwtPlot(prnt),
	            m_legend(),
	            m_toAdd(),
	            m_toAttachVisitor(){
	            //set parameter
                setCanvasBackground(Qt::white);
                setTitle(QString("ModuleStatistics"));
                setFrameStyle(QFrame::NoFrame);
                setLineWidth(0);
                setAxisTitle(QwtPlot::xBottom, "count");
                setAxisTitle(QwtPlot::yLeft, "load");

                //add legend
                m_legend = new QwtLegend(this);
                m_legend->setFrameStyle(QFrame::Box | QFrame::Sunken);
                m_legend->setItemMode(QwtLegend::ReadOnlyItem);
                insertLegend(m_legend,QwtPlot::BottomLegend);

                m_toAttachVisitor = new QTimer(this);
                connect(m_toAttachVisitor, SIGNAL(timeout()), SLOT(attachQueuedLPM()));
            }

            LoadPlot::~LoadPlot(){}

            void
            LoadPlot::addLoadPerModule(core::SharedPointer<LoadPerModule> lpm) {
	            m_toAdd.push_back(lpm);
	            m_toAttachVisitor->start(100);
            }

            void LoadPlot::attachQueuedLPM(){
	            for (uint32_t i = 0; i < m_toAdd.size(); i++) {
		            m_toAdd[i]->getCurve()->attach(this);
	            }
	            m_toAttachVisitor->stop();
            }
        }
    }
}

