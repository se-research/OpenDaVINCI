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

#include <Qt/qaction.h>
#include <Qt/qfiledialog.h>
#include <Qt/qgridlayout.h>
#include <Qt/qmenubar.h>
#include <qstring.h>

#include "core/opendavinci.h"
#include "plugins/GLControlFrame.h"
#include "plugins/objxviewer/OBJXGLWidget.h"
#include "plugins/objxviewer/OBJXViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace objxviewer {

            using namespace std;

            OBJXViewerWidget::OBJXViewerWidget(const PlugIn &plugIn, QWidget *prnt) :
                    QWidget(prnt),
                    m_viewerWidget(NULL),
                    m_objxViewerWidget(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                QMenuBar* menubar = new QMenuBar(this);
                QAction* open = new QAction(tr("op&en .objx.."), this);
                open->setShortcut(tr("Ctrl+O"));
                open->setToolTip("Close the application.");
                connect(open, SIGNAL(triggered()), SLOT(openOBJX()));
                menubar->addAction(open);
                mainBox->addWidget(menubar, 0, 0);

                // OpenGL scene viewer.
                m_objxViewerWidget = new OBJXGLWidget(plugIn, this);
                m_objxViewerWidget->setMinimumWidth(540);
                m_objxViewerWidget->setMinimumHeight(300);

                // Controllable frame.
                m_viewerWidget = new GLControlFrame(m_objxViewerWidget);
                mainBox->addWidget(m_viewerWidget, 1, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            OBJXViewerWidget::~OBJXViewerWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_objxViewerWidget);
                OPENDAVINCI_CORE_DELETE_POINTER(m_viewerWidget);
            }

            void OBJXViewerWidget::openOBJX() {
                QString fileName = QFileDialog::getOpenFileName(this, tr("Open .objx..."), NULL );
                if (!fileName.isEmpty()) {
                    m_objxViewerWidget->setOBJXModel(fileName.toStdString());
                }
            }
        }
    }
} // cockpit::plugins::objxviewer
