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

#ifndef CONFIGURATIONVIEWERWIDGET_H_
#define CONFIGURATIONVIEWERWIDGET_H_

#include <qobjectdefs.h>
#include <qwidget.h>

class QTextEdit;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

      namespace configurationviewer {

          using namespace std;

            /**
             * This class is the container for the configuration viewer widget.
             */
            class ConfigurationViewerWidget : public QWidget {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ConfigurationViewerWidget(const ConfigurationViewerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ConfigurationViewerWidget& operator=(const ConfigurationViewerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    ConfigurationViewerWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~ConfigurationViewerWidget();

                private:
                    QTextEdit *m_configurationDataText;
            };
      }
    }
}

#endif /*CONFIGURATIONVIEWERWIDGET_H_*/

