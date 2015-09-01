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

#ifndef COCKPIT_PLUGINS_FORCECONTROLVIEWERWIDGET_H_
#define COCKPIT_PLUGINS_FORCECONTROLVIEWERWIDGET_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <deque>

#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
//#include "core/data/control/ForceControl.h" included by GeneratedHeaders_AutomotiveData.h
#include "core/io/conference/ContainerListener.h"
#include "GeneratedHeaders_CoreData.h"
#include "QtIncludes.h"

#include "plugins/PlugIn.h"
#include "plugins/forcecontrolviewer/ForceControlData.h"

namespace cockpit {

    namespace plugins {

      namespace forcecontrolviewer {

          using namespace std;

            /**
             * This class is the container for the controller widget.
             */
            class ForceControlViewerWidget : public QWidget, public core::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ForceControlViewerWidget(const ForceControlViewerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ForceControlViewerWidget& operator=(const ForceControlViewerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    ForceControlViewerWidget(const PlugIn &plugIn, const core::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~ForceControlViewerWidget();

                    virtual void nextContainer(core::data::Container &c);

                public slots:
                    void TimerEvent();

                private:
#ifndef PANDABOARD
                    QwtPlot *m_plotAcceleration;
                    QwtPlotCurve *m_curveAcceleration;

                    QwtPlot *m_plotBrake;
                    QwtPlotCurve *m_curveBrake;

                    QwtPlot *m_plotSteering;
                    QwtPlotCurve *m_curveSteering;
#endif
                    deque<automotive::ForceControl> m_data;

#ifndef PANDABOARD
                    ForceControlData m_accelerationData;
                    ForceControlData m_brakeData;
                    ForceControlData m_steeringData;
#endif
            };
        }
    }
}

#endif /*COCKPIT_PLUGINS_FORCECONTROLVIEWERWIDGET_H_*/

