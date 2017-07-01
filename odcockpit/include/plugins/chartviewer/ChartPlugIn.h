/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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

#ifndef COCKPIT_PLUGINS_CHARTVIEWER_CHARTPLUGIN_H_
#define COCKPIT_PLUGINS_CHARTVIEWER_CHARTPLUGIN_H_

#include <string>

#include "plugins/PlugIn.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace chartviewer {

class ChartWidget;

          class ChartPlugIn : public PlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ChartPlugIn(const ChartPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ChartPlugIn& operator=(const ChartPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param title Title of this plugin.
                 * @param dataType Container data type identifier to monitor.
                 * @param senderStamp Container sender stamp.
                 * @param fieldName Field from message to watch.
                 * @param kvc KeyValueConfiguration for this based widget.
                 * @param prnt Pointer to the containing super window.
                 */
                ChartPlugIn(const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                virtual ~ChartPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                int32_t m_dataType;
                uint32_t m_senderStamp;
                string m_fieldName;

                ChartWidget *m_chartWidget;
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_CHARTVIEWER_CHARTPLUGIN_H_*/

