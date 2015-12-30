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

#include <algorithm>
#include <iostream>

#include "QtIncludes.h"

#include "core/base/Lock.h"
#include "core/data/Container.h"
#include "GeneratedHeaders_AutomotiveData.h"
#include "hesperia/data/environment/Point3.h"

#include "plugins/irusmap/IrUsMapWidget.h"

namespace cockpit {

    namespace plugins {

        namespace irusmap {

            using namespace std;
            using namespace core::base;
            using namespace core::data;
            using namespace hesperia::data::environment;

            IrUsMapWidget::IrUsMapWidget(const PlugIn &/*plugIn*/, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                QWidget(prnt),
                m_timer(NULL),
                m_scaleFactorMutex(),
                m_scaleFactor(0.05),
                m_rotation(90),
                m_mapOfPointSensors(),
                m_sensorBoardDataMutex(),
                m_sensorBoardData() {

                // Setup all point sensors.
                for (uint32_t i = 0; i < kvc.getValue<uint32_t>("odsimirus.numberOfSensors"); i++) {
                    stringstream sensorID;
                    sensorID << "odsimirus.sensor" << i << ".id";
                    uint16_t id(kvc.getValue<uint16_t>(sensorID.str()));

                    stringstream sensorName;
                    sensorName << "odsimirus.sensor" << i << ".name";
                    string name(kvc.getValue<string>(sensorName.str()));
                    
                    stringstream sensorTranslation;
                    sensorTranslation << "odsimirus.sensor" << i << ".translation";
                    Point3 translation(kvc.getValue<string>(sensorTranslation.str()));

                    stringstream sensorRotZ;
                    sensorRotZ << "odsimirus.sensor" << i << ".rotZ";
                    const double rotZ = kvc.getValue<double>(sensorRotZ.str());
                    
                    stringstream sensorAngleFOV;
                    sensorAngleFOV << "odsimirus.sensor" << i << ".angleFOV";
                    const double angleFOV = kvc.getValue<double>(sensorAngleFOV.str());
                    
                    stringstream sensorDistanceFOV;
                    sensorDistanceFOV << "odsimirus.sensor" << i << ".distanceFOV";
                    const double distanceFOV = kvc.getValue<double>(sensorDistanceFOV.str());
                    
                    stringstream sensorClampDistance;
                    sensorClampDistance << "odsimirus.sensor" << i << ".clampDistance";
                    const double clampDistance = kvc.getValue<double>(sensorClampDistance.str());

                    PointSensor *ps = new PointSensor(id, name, translation, rotZ, angleFOV, distanceFOV, clampDistance);

                    if (ps != NULL) {
                        // Save for later.
                        m_mapOfPointSensors[ps->getName()] = ps;

                        cout << "Registered point sensor " << ps->toString() << "." << endl;
                    }
                }

                // Timer for sending data regularly.
                m_timer = new QTimer(this);
                connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
                m_timer->start(200);
            }

            IrUsMapWidget::~IrUsMapWidget() {}

            void IrUsMapWidget::stopTimer() {
                m_timer->stop();
            }

            void IrUsMapWidget::nextContainer(Container &c) {
                if (c.getDataType() == Container::USER_DATA_0) {
                    Lock l(m_sensorBoardDataMutex);
        			m_sensorBoardData = c.getData<automotive::miniature::SensorBoardData>();
                }
            }

            void IrUsMapWidget::setScale(const int &val) {
                if (val > 0) {
                    Lock l(m_scaleFactorMutex);
                    m_scaleFactor = (val / 100.0);
                }
            }

            void IrUsMapWidget::paintEvent(QPaintEvent *evt) {
                Lock l(m_scaleFactorMutex);

                QPainter painter(this);
                painter.setRenderHint(QPainter::Antialiasing);

                const double scaleMax = 5;
                const double scaleMin = 1e-4;
                const double offsetViewMaxFactor = 8;

                if (m_scaleFactor < scaleMin) {
                    m_scaleFactor = scaleMin;
                } else if (m_scaleFactor > scaleMax) {
                    m_scaleFactor = scaleMax;
                }

                // White background.
                painter.fillRect(evt->rect(), QBrush(Qt::white));

                // Variables for displaying labels on the map.
                QString description;
                QPointF pt_description;
                QRectF rect_description;
                QFont fontSettings = this->font();

                QPen pen;

                // Map coordinate system transformation according to DIN 70000: x = 12am, y = 9am --> m_rotation = +90 (http://www.isupia.de/download/Fahrdynamische%20Größen.pdf)
                QTransform transformationDIN70000;
                transformationDIN70000.translate(evt->rect().width() / 2, evt->rect().height() / 2);
                transformationDIN70000.scale(m_scaleFactor, -m_scaleFactor);
                transformationDIN70000.rotate(m_rotation);

                // Transformation into the regular coordinate system.
                QTransform transformationCartesianCoordinateSystem;
                transformationCartesianCoordinateSystem.translate(evt->rect().width() / 2, evt->rect().height() / 2);
                transformationCartesianCoordinateSystem.scale(m_scaleFactor, -m_scaleFactor);
                transformationCartesianCoordinateSystem.rotate(m_rotation - 90);

                // Transformation for descriptions label in image coordinates.
                QTransform descriptionTrans;
                descriptionTrans.translate(0, 0);
                descriptionTrans.scale(1, 1);
                descriptionTrans.rotate(0);

                // Setup fonts.
                fontSettings.setPointSize(10);
                painter.setFont(fontSettings);

                // Setup axes parameters.
                const double scaleMultiplier = ceil((1 / ((m_scaleFactor * 100) / 50)));
                const double step = 100 * scaleMultiplier;
                const double zeroAxisWidth = 3;
                const QColor zeroAxisColor = Qt::black;
                const QColor gridAxisColor = Qt::gray;
                const QColor textColor = QPalette::Foreground;
                const double xStepFact = ceil(width() * offsetViewMaxFactor / step / m_scaleFactor);
                const double yStepFact = ceil(height() * offsetViewMaxFactor / step / m_scaleFactor);

                // Draw X-axes.
                for (double i = -yStepFact * step;i < yStepFact * step;i += step) {
                    if ((int)(i / step) % 2) {
                        painter.setPen(gridAxisColor);
                    }
                    else {
                        description.sprintf("%.0f", i);

                        pt_description.setY(i);
                        painter.setTransform(descriptionTrans);
                        pt_description = transformationCartesianCoordinateSystem.map(pt_description);
                        pt_description.setX(10);
                        pt_description.setY(pt_description.y() - 5);

                        painter.setPen(QPen(textColor));
                        painter.drawText(pt_description, description);

                        if (fabs(i) < 1e-5) {
                            pen.setWidthF(zeroAxisWidth / m_scaleFactor);
                            pen.setColor(zeroAxisColor);
                        }
                        else {
                            pen.setWidth(0);
                        }
                        painter.setPen(pen);
                    }
                    painter.setTransform(transformationDIN70000);
                    painter.drawLine(-xStepFact * step, i, xStepFact * step, i);
                }

                // Draw Y-axis segments
                for (double i = -xStepFact * step;i < xStepFact * step;i += step) {
                    if ((int)(i / step) % 2) {
                        painter.setPen(gridAxisColor);
                    }
                    else {
                        description.sprintf("%.0f", i*-1);

                        pt_description.setX(i);
                        pt_description.setY(0);
                        painter.setTransform(descriptionTrans);
                        pt_description = transformationCartesianCoordinateSystem.map(pt_description);
                        pt_description.setX(pt_description.x() + 5);
                        pt_description.setY(height() - 10);

                        painter.setPen(QPen(textColor));
                        painter.drawText(pt_description, description);

                        if (fabs(i) < 1e-5) {
                            pen.setWidthF(zeroAxisWidth / m_scaleFactor);
                            pen.setColor(zeroAxisColor);
                        }
                        else {
                            pen.setWidth(0);
                        }
                        painter.setPen(pen);
                    }

                    painter.setTransform(transformationDIN70000);
                    painter.drawLine(i, -yStepFact * step, i, yStepFact * step);
                }

                // Draw the field of views for the chosen sensor setup.
                const QColor FOVColor = Qt::green;

                // Loop through point sensors.
                map<string, PointSensor*, core::strings::StringComparator>::iterator sensorIterator = m_mapOfPointSensors.begin();
                for (; sensorIterator != m_mapOfPointSensors.end(); sensorIterator++) {
                    PointSensor *sensor = sensorIterator->second;

                    // Draw field of view.
                    {
                        painter.setTransform(transformationDIN70000);
                        pen.setColor(FOVColor);
                        painter.setPen(pen);
                        sensor->drawFOV(painter);

                        // Draw distances that belong to this sensor.
                        {
                            Lock l2(m_sensorBoardDataMutex);
                            sensor->drawMatchingDistances(painter, m_sensorBoardData);
                        }
                    }

                    // Add description to the sensor.
                    {
                        painter.setPen(QPen(textColor));
                        fontSettings.setPointSize(10);
                        painter.setFont(fontSettings);
                        stringstream desc;
                        desc << sensor->getName() << " (ID: " << sensor->getID() << ")";

                        pt_description.setX(sensor->getDescPoint().getX()*1000);
                        pt_description.setY(sensor->getDescPoint().getY()*1000);
                        painter.setTransform(descriptionTrans);
                        pt_description = transformationDIN70000.map(pt_description);

                        description = desc.str().c_str();
                        painter.drawText(pt_description, description);
                    }
                }

                // Draw axes labels.
                pen.setColor(zeroAxisColor);
                painter.setPen(pen);
                painter.setTransform(descriptionTrans);
                fontSettings.setPointSize(10);
                painter.setFont(fontSettings);
                description = "x [mm]";
                painter.drawText(evt->rect().width() / 2 + 15, 15, description);

                description = "y [mm]";
                painter.drawText(15, evt->rect().height() / 2 + 15, description);

                // Arrows for the axes.
                pen.setWidthF(zeroAxisWidth);
                pen.setColor(zeroAxisColor);
                painter.setPen(pen);
                // Arrow X axis.
                painter.drawLine(evt->rect().width() / 2, 0, evt->rect().width() / 2 - 15, 15);
                painter.drawLine(evt->rect().width() / 2, 0, evt->rect().width() / 2 + 15, 15);
                // Arrow Y axis.
                painter.drawLine(0, evt->rect().height() / 2, 15, evt->rect().height() / 2 - 15);
                painter.drawLine(0, evt->rect().height() / 2, 15, evt->rect().height() / 2 + 15);

                painter.end();
            }

        }
    }
}

