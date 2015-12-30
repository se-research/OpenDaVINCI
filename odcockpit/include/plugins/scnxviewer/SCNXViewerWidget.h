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

#ifndef COCKPIT_PLUGINS_SCNXVIEWER_SCNXVIEWERWIDGET_H_
#define COCKPIT_PLUGINS_SCNXVIEWER_SCNXVIEWERWIDGET_H_

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <qobjectdefs.h>
#include <qwidget.h>

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

namespace cockpit { namespace plugins { class GLControlFrame; } }
namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace scnxviewer {

class SCNXGLWidget;

            using namespace std;

            /**
             * This class is the container for the SCNX viewer widget.
             */
            class SCNXViewerWidget : public QWidget {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    SCNXViewerWidget(const SCNXViewerWidget &/*scn*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    SCNXViewerWidget& operator=(const SCNXViewerWidget &/*scn*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    SCNXViewerWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~SCNXViewerWidget();

                private slots:
                    /**
                     * This method is called when the user clicks on the button.
                     */
                    void openSCNX();

                private:
                    GLControlFrame *m_viewerWidget;
                    SCNXGLWidget *m_scnxViewerWidget;
            };

        }
    }
} // plugins::scnxviewer

#endif /*COCKPIT_PLUGINS_SCNXVIEWER_SCNXVIEWERWIDGET_H_*/
