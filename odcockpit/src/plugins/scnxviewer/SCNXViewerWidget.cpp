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

#include "core/platform.h"
#include "core/macros.h"
#include "plugins/GLControlFrame.h"
#include "plugins/scnxviewer/SCNXGLWidget.h"
#include "plugins/scnxviewer/SCNXViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace scnxviewer {

            using namespace std;

            SCNXViewerWidget::SCNXViewerWidget(const PlugIn &plugIn, QWidget *prnt) :
                    QWidget(prnt),
                    m_viewerWidget(NULL),
                    m_scnxViewerWidget(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                QMenuBar* menubar = new QMenuBar(this);
                QAction* open = new QAction(tr("op&en .scnx.."), this);
                open->setShortcut(tr("Ctrl+O"));
                open->setToolTip("Close the application.");
                connect(open, SIGNAL(triggered()), SLOT(openSCNX()));
                menubar->addAction(open);
                mainBox->addWidget(menubar, 0, 0);

                // OpenGL scene viewer.
                m_scnxViewerWidget = new SCNXGLWidget(plugIn, this);
                m_scnxViewerWidget->setMinimumWidth(540);
                m_scnxViewerWidget->setMinimumHeight(300);

                // Controllable frame.
                m_viewerWidget = new GLControlFrame(m_scnxViewerWidget);
                mainBox->addWidget(m_viewerWidget, 1, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            SCNXViewerWidget::~SCNXViewerWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_scnxViewerWidget);
                OPENDAVINCI_CORE_DELETE_POINTER(m_viewerWidget);
            }

            void SCNXViewerWidget::openSCNX() {
                QString fileName = QFileDialog::getOpenFileName(this, tr("Open .scnx..."), NULL );
                if (!fileName.isEmpty()) {
                    m_scnxViewerWidget->setSCNXModel(fileName.toStdString());
                }
            }

        }
    }
} // cockpit::plugins::scnxviewer
