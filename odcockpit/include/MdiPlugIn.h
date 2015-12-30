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

#ifndef MDIPLUGIN_H_
#define MDIPLUGIN_H_

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <Qt/qmdisubwindow.h>
#include <qnamespace.h>
#include <qobjectdefs.h>

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

class QCloseEvent;
class QWidget;

namespace cockpit {

namespace plugins { class PlugIn; }

    using namespace std;

    /**
     * This class is a special QMdiSubWindow that invokes the stopPlugIn()
     * method before closing. Therefore, it is STRONGLY RECOMMENDED to
     * use this specialization.
     */
    class MdiPlugIn : public QMdiSubWindow {

            Q_OBJECT

        public:
            /**
             * Constructor.
             *
             * @param plugIn The plugin to which this plugin belongs to.
             * @param prnt Any parental window.
             * @param flags Any flags.
             */
            MdiPlugIn(plugins::PlugIn &plugIn, QWidget *prnt = 0, Qt::WindowFlags flags = 0);

            virtual ~MdiPlugIn();

        protected:
            virtual void closeEvent(QCloseEvent *evnt);

        private:
            plugins::PlugIn &m_plugIn;
    };

} // cockpit

#endif /*MDIPLUGIN_H_*/
