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
#include <Qt/qpushbutton.h>
#include <qnamespace.h>

#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Weffc++"
#endif
    #include "qwt_wheel.h"
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic pop
# endif
#endif

#include "core/platform.h"
#include "generated/cartesian/Constants.h"
#include "plugins/AbstractGLWidget.h"
#include "plugins/GLControlFrame.h"

namespace cockpit {
    namespace plugins {

        GLControlFrame::GLControlFrame(AbstractGLWidget* controllableGLWidget) :
                m_hWheel(NULL),
                m_vWheel(NULL) {

            QGridLayout* grid = new QGridLayout(this);
            m_vWheel = new QwtWheel(this);
            m_vWheel->setOrientation(Qt::Vertical);
            m_vWheel->setRange(0, -cartesian::Constants::PI, 0.01);
            m_vWheel->setMinimumHeight(300);
            m_vWheel->setMaximumWidth(20);
            connect(m_vWheel, SIGNAL(valueChanged(double)), controllableGLWidget, SLOT(setTheta(double)));
            grid->addWidget(m_vWheel, 1, 0);

            m_hWheel = new QwtWheel(this);
            m_hWheel->setRange(-1, 1, 0.01);
            m_hWheel->setMinimumWidth(300);
            m_hWheel->setMaximumHeight(20);
            m_hWheel->setOrientation(Qt::Horizontal);
            connect(m_hWheel, SIGNAL(valueChanged(double)),  SLOT(newHValue(double)));
            connect(this , SIGNAL(horizontalValueChanged(double)), controllableGLWidget, SLOT(setPhi(double)));
            grid->addWidget(m_hWheel, 3, 2);

            QPushButton* rstVBtn = new QPushButton("", this);
            rstVBtn->setMaximumSize(20, 20);
            connect(rstVBtn, SIGNAL(clicked()), SLOT(resetVValue()));
            grid->addWidget(rstVBtn, 0, 0);

            QPushButton* rstHBtn = new QPushButton("", this);
            rstHBtn->setMaximumSize(20, 20);
            connect(rstHBtn, SIGNAL(clicked()), SLOT(resetHValue()));
            grid->addWidget(rstHBtn, 3, 3);

            grid->addWidget(controllableGLWidget, 0, 1, 3, 3);
            grid->setColumnStretch(1, 1);
            grid->setColumnStretch(3, 1);
            grid->setRowStretch(0, 1);
            grid->setRowStretch(2, 1);
            setLayout(grid);

            connect(controllableGLWidget, SIGNAL(thetaChanged(double)), m_vWheel, SLOT(setValue(double)));
            connect(controllableGLWidget, SIGNAL(phiChanged(double)), m_hWheel, SLOT(setValue(double)));
        }

        GLControlFrame::~GLControlFrame() {}

        void GLControlFrame::newVValue(double newValue) {
            m_vWheel->setRange(newValue - 10, newValue + 10, 1);
            emit verticalValueChanged(newValue);
        }

        void GLControlFrame::newHValue(double newValue) {
            m_hWheel->setRange(newValue - 1, newValue + 1, 0.01);
            emit horizontalValueChanged(newValue);
        }

        void GLControlFrame::resetHValue() {
            m_hWheel->setValue(0);
        }

        void GLControlFrame::resetVValue() {
            m_vWheel->setValue(0);
        }
    }
} // cockpit::plugins

