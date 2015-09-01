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

#ifndef COCKPIT_PLUGINS_CUTTERWIDGET_H_
#define COCKPIT_PLUGINS_CUTTERWIDGET_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <iostream>
#include <map>
#include <string>

#include "core/SharedPointer.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"

#include "plugins/PlugIn.h"
#include "QtIncludes.h"

namespace cockpit {

    namespace plugins {

        namespace cutter {

            using namespace std;
            using namespace core::data;

            /**
             * This class is the container for the cutter widget.
             */
            class CutterWidget : public QWidget {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    CutterWidget(const CutterWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    CutterWidget& operator=(const CutterWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    CutterWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~CutterWidget();

                public slots:
                    void loadFile();
                    void saveFile();

                private:
                    QListWidget *m_containerWidget;
                    QLabel *m_desc;
                    map<uint32_t, string> m_mapOfContainers;
                    map<uint32_t, string> m_mapOfSelectedContainers;
                    core::SharedPointer<istream> m_in;
                    uint32_t m_numberOfCounters;

            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_CUTTERWIDGET_H_ */
