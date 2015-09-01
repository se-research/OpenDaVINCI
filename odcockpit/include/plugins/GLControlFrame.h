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

#ifndef COCKPIT_GLCONTROLFRAME_H_
#define COCKPIT_GLCONTROLFRAME_H_

#include "QtIncludes.h"

#include "plugins/AbstractGLWidget.h"

namespace cockpit {
    namespace plugins {

        class GLControlFrame: public QWidget {

                Q_OBJECT

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                GLControlFrame(const GLControlFrame &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                GLControlFrame& operator=(const GLControlFrame &/*obj*/);

            public:
                GLControlFrame(AbstractGLWidget* controllableGLWidget);

                virtual ~GLControlFrame();

            signals:
                void horizontalValueChanged(double newValue);
                void verticalValueChanged(double newValue);

            private:
                QwtWheel* m_hWheel;
                QwtWheel* m_vWheel;

            private slots:
                void newVValue(double newValue);
                void newHValue(double newValue);
                void resetHValue();
                void resetVValue();
        };
    }
}

#endif /* COCKPIT_GLCONTROLFRAME_H_ */
