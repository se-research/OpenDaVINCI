/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPPLUGIN_H_
#define PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPPLUGIN_H_

#include <string>

#include "plugins/PlugIn.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            /**
             * This class is birdseye map plugin.
             */
class BirdsEyeMapWidget;

            class BirdsEyeMapPlugIn : public PlugIn {

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BirdsEyeMapPlugIn(const BirdsEyeMapPlugIn &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BirdsEyeMapPlugIn& operator=(const BirdsEyeMapPlugIn &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param name Name of this plugin.
                     * @param kvc KeyValueConfiguration for this GL-based widget.
                     * @param prnt Pointer to the container super window.
                     */
                    BirdsEyeMapPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget* prnt);

                    virtual ~BirdsEyeMapPlugIn();

                    virtual QWidget* getQWidget() const;

                    virtual void setupPlugin();

                    virtual void stopPlugin();

                private:
                    BirdsEyeMapWidget *m_widget;
            };
        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPPLUGIN_H_*/
