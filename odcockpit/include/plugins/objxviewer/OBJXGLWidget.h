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

#ifndef COCKPIT_PLUGINS_OBJXVIEWER_OBJXGLWIDGET_H_
#define COCKPIT_PLUGINS_OBJXVIEWER_OBJXGLWIDGET_H_

#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Mutex.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/TransformGroup.h"

#include "plugins/AbstractGLWidget.h"

namespace cockpit {
    namespace plugins {
        namespace objxviewer {

            using namespace std;

            /**
             * This class visualizes objx models.
             */
            class OBJXGLWidget: public AbstractGLWidget {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OBJXGLWidget(const OBJXGLWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OBJXGLWidget& operator=(const OBJXGLWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    OBJXGLWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~OBJXGLWidget();

                    /**
                     * This method sets a new objx-model to be loaded.
                     *
                     * @param objxModel Model.
                     */
                    void setOBJXModel(const string &objxModel);

                protected:
                    virtual void setupOpenGL();

                    virtual void initScene();

                    virtual void drawScene();

                private:
                    hesperia::threeD::Node *m_root;

                    mutable core::base::Mutex m_modelMutex;
                    hesperia::threeD::TransformGroup *m_model;
            };

        }
    }
} // cockpit::plugins::objxviewer

#endif /*COCKPIT_PLUGINS_OBJXVIEWER_OBJXGLWIDGET_H_*/
