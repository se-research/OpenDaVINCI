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

#include <Qt/qdesktopwidget.h>
#include <Qt/qtranslator.h>
#include <qlocale.h>
#include <qsize.h>
#include <qstring.h>

#include <iostream>
#include <string>

#include "Cockpit.h"
#include "CockpitWindow.h"

namespace cockpit {

    using namespace std;
    using namespace odcore::base;

    Cockpit::Cockpit(int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odcockpit"),
        m_cockpitApp(argc, argv)
	{}

    Cockpit::~Cockpit() {}

    void Cockpit::setUp() {
        // This method will be call automatically _before_ running body().
    }

    void Cockpit::tearDown() {
        // This method will be call automatically _after_ return from body().
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Cockpit::body() {
        // Get apropriate translator.
        QTranslator qtTranslator;
        std::cerr << QLocale::system().name().toStdString() << std::endl;
        qtTranslator.load("cockpit_" + QLocale::system().name());
        m_cockpitApp.installTranslator(&qtTranslator);

        // Create main cockpit.
        CockpitWindow  mainWindow(getKeyValueConfiguration(), (*this), getConference());
        mainWindow.resize(800, 600);

        // Center window.
        QSize size;
        size = mainWindow.size();

        QDesktopWidget *d = QApplication::desktop();
        int ws = d->width();   // returns screen width
        int h = d->height();  // returns screen height
        int mw = size.width();
        int mh = size.height();
        int cw = (ws/2) - (mw/2);
        int ch = (h/2) - (mh/2);
        mainWindow.move(cw,ch);

        mainWindow.setWindowTitle("OpenDaVINCI Cockpit");

        mainWindow.show();
        m_cockpitApp.exec();

    	return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // cockpit

