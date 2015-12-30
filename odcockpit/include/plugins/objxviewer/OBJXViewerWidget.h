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

#ifndef COCKPIT_PLUGINS_OBJXVIEWER_OBJXVIEWERWIDGET_H_
#define COCKPIT_PLUGINS_OBJXVIEWER_OBJXVIEWERWIDGET_H_

#include <qobjectdefs.h>
#include <qwidget.h>

namespace cockpit { namespace plugins { class GLControlFrame; } }
namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace objxviewer {

class OBJXGLWidget;

            using namespace std;

            /**
             * This class is the container for the OBJX viewer widget.
             */
            class OBJXViewerWidget : public QWidget {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OBJXViewerWidget(const OBJXViewerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OBJXViewerWidget& operator=(const OBJXViewerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    OBJXViewerWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~OBJXViewerWidget();

                private slots:
                    /**
                     * This method is called when the user clicks on the button.
                     */
                    void openOBJX();

                private:
                    GLControlFrame *m_viewerWidget;
                    OBJXGLWidget *m_objxViewerWidget;
            };
        }
    }
} // cockpit::plugins::objxviewer

#endif /*COCKPIT_PLUGINS_OBJXVIEWER_OBJXVIEWERWIDGET_H_*/
