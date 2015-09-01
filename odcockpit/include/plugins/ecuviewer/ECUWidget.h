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

#ifndef COCKPIT_PLUGINS_ECUWIDGET_H_
#define COCKPIT_PLUGINS_ECUWIDGET_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <map>
#include <cstring>

#include "core/io/conference/ContainerConference.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"

#include "plugins/PlugIn.h"

#include "QtIncludes.h"

namespace cockpit {

    namespace plugins {

        namespace ecuviewer {

            using namespace std;
            using namespace core::data;

            /**
             * This class is the container for the ECUViewer widget.
             */
            class ECUWidget : public QWidget, public core::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ECUWidget(const ECUWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ECUWidget&
                    operator=(const ECUWidget &/*obj*/);

                public slots:
                    void setDesiredData(int v);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    ECUWidget(const PlugIn &plugIn, core::io::conference::ContainerConference &conf, QWidget *prnt);

                    virtual ~ECUWidget();

                    virtual void nextContainer(Container &c);

                private:
                    core::io::conference::ContainerConference &m_conference;

                    QTextEdit *m_rawDataFromECU;

                    QLabel *m_accelX;
                    QLabel *m_accelY;
                    QLabel *m_accelZ;

                    bool m_firstCycle;
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_ECUWIDGET_H_ */
