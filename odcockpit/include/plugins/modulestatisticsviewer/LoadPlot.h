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

#ifndef LOADPLOT_H_
#define LOADPLOT_H_

#include <qobjectdefs.h>

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif
    #include <qwt-qt4/qwt_plot.h>
#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#include <vector>

#include "core/SharedPointer.h"

class QTimer;
class QWidget;
class QwtLegend;

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

class LoadPerModule;

            using namespace std;

            class LoadPlot: public QwtPlot {

                Q_OBJECT

                private:
	                /**
	                 * "Forbidden" copy constructor. Goal: The compiler should warn
	                 * already at compile time for unwanted bugs caused by any misuse
	                 * of the copy constructor.
	                 */
	                LoadPlot(const LoadPlot &/*obj*/);

	                /**
	                 * "Forbidden" assignment operator. Goal: The compiler should warn
	                 * already at compile time for unwanted bugs caused by any misuse
	                 * of the assignment operator.
	                 */
	                LoadPlot& operator=(const LoadPlot &/*obj*/);

                public:
	                LoadPlot(QWidget* prnt = 0);

	                ~LoadPlot();

	                void addLoadPerModule(core::SharedPointer<LoadPerModule> lpm);

                private:
	                QwtLegend* m_legend;
	                vector<core::SharedPointer<LoadPerModule> > m_toAdd;
	                QTimer* m_toAttachVisitor;

                private slots:
	                void attachQueuedLPM();

            };
        }
    }
}

#endif /* LOADPLOT_H_ */
