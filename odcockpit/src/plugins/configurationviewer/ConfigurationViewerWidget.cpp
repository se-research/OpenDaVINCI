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

#include <Qt/qgridlayout.h>
#include <Qt/qtextedit.h>
#include <qfont.h>
#include <qstring.h>

#include <sstream>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "plugins/configurationviewer/ConfigurationViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace configurationviewer {

            using namespace std;

            ConfigurationViewerWidget::ConfigurationViewerWidget(const PlugIn &/*plugIn*/, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                QWidget(prnt),
                m_configurationDataText(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout *mainBox = new QGridLayout(this);

                // QLabel to show configuration data.
                m_configurationDataText = new QTextEdit(this);

                QFont courierFont("Courier", 12, QFont::Normal, false);
                m_configurationDataText->setFont(courierFont);

                // Get textual representation.
                stringstream configurationText;
                kvc.writeTo(configurationText);

                m_configurationDataText->append(QString(configurationText.str().c_str()));
                m_configurationDataText->setReadOnly(true);

                mainBox->addWidget(m_configurationDataText, 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            ConfigurationViewerWidget::~ConfigurationViewerWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_configurationDataText);
            }

        }
    }
}

