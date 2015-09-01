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

#ifndef COCKPIT_PLUGINS_SCNXVIEWER_SCNXGLWIDGET_H_
#define COCKPIT_PLUGINS_SCNXVIEWER_SCNXGLWIDGET_H_

#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Mutex.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/TransformGroup.h"

#include "plugins/AbstractGLWidget.h"

namespace cockpit {
    namespace plugins {
        namespace scnxviewer {

            using namespace std;

            /**
             * This class visualizes scnx models.
             */
            class SCNXGLWidget: public AbstractGLWidget {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    SCNXGLWidget(const SCNXGLWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    SCNXGLWidget& operator=(const SCNXGLWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    SCNXGLWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~SCNXGLWidget();

                    /**
                     * This method sets a new scnx-model to be loaded.
                     *
                     * @param scnxModel Model.
                     */
                    void setSCNXModel(const string &scnxModel);

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
} // cockpit::plugins::scnxviewer

#endif /*COCKPIT_PLUGINS_SCNXVIEWER_SCNXGLWIDGET_H_*/
