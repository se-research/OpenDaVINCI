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

#include <Qt/qevent.h>
#include <qcoreevent.h>

#include "opendavinci/core/opendavinci.h"
#include "MdiPlugIn.h"
#include "plugins/PlugIn.h"

class QWidget;

namespace cockpit {

    using namespace std;

    MdiPlugIn::MdiPlugIn(plugins::PlugIn &plugIn, QWidget *prnt, Qt::WindowFlags flags) :
        QMdiSubWindow(prnt, flags),
        m_plugIn(plugIn) {}

    MdiPlugIn::~MdiPlugIn() {}

    void MdiPlugIn::closeEvent(QCloseEvent *evt) {
        // Stop plugin.
        if ( (evt != NULL) && (evt->type() == QEvent::Close) ) {
            m_plugIn.stopPlugin();
        }

        // Call closeEvent from upper class.
        QMdiSubWindow::closeEvent(evt);
    }

} // cockpit
