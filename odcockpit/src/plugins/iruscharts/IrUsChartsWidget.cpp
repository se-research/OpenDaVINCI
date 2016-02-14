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

#include <Qt/qfiledialog.h>
#include <Qt/qlabel.h>
#include <Qt/qpushbutton.h>
#include <Qt/qscrollarea.h>
#include <Qt/qtimer.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qnamespace.h>

#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Weffc++"
#endif
    #include <qwt_plot.h>
    #include <qwt_plot_curve.h>
    #include <qwt_plot_item.h>
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic pop
# endif
#endif


#include <iostream>
#include <sstream>

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "core/base/Serializable.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"
#include "plugins/iruscharts/IrUsChartData.h"
#include "plugins/iruscharts/IrUsChartsWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace iruscharts {

            using namespace std;
            using namespace core;
            using namespace core::base;
            using namespace core::data;

            IrUsChartsWidget::IrUsChartsWidget(const PlugIn &/*plugIn*/, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                QWidget(prnt),
                m_listOfPlots(),
                m_listOfPlotCurves(),
                m_listOfData(),
                m_mapOfSensors(),
                m_data(),
                m_bufferMax(10000),
                m_receivedSensorBoardDataContainersMutex(),
                m_receivedSensorBoardDataContainers(),
                m_bufferFilling(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Setup point distance sensors.
                for (uint32_t i = 0; i < kvc.getValue<uint32_t>("odsimirus.numberOfSensors"); i++) {
                    stringstream sensorID;
                    sensorID << "odsimirus.sensor" << i << ".id";
                    uint16_t id(kvc.getValue<uint16_t>(sensorID.str()));

                    stringstream sensorName;
                    sensorName << "odsimirus.sensor" << i << ".name";
                    string name(kvc.getValue<string>(sensorName.str()));

                    m_mapOfSensors[id] = name;

                    stringstream sensorDistanceFOV;
                    sensorDistanceFOV << "odsimirus.sensor" << i << ".distanceFOV";
                    const double distanceFOV = kvc.getValue<double>(sensorDistanceFOV.str());

                    stringstream desc;
                    desc << name << " (ID: " << id << ") [m]";

                    // Setup plot.
                    QwtPlot *plot = new QwtPlot(this);
                    plot->setAxisScale(QwtPlot::yLeft, -2, distanceFOV);
                    plot->setMinimumSize(350, 300);
                    plot->setCanvasBackground(Qt::white);
                    plot->setFrameStyle(QFrame::NoFrame);
                    plot->setLineWidth(0);
                    plot->setAxisTitle(QwtPlot::xBottom, "t");
                    plot->setAxisTitle(QwtPlot::yLeft, desc.str().c_str());
                    m_listOfPlots.push_back(plot);

                    // Setup data interface.
                    IrUsChartData *dataInterface = new IrUsChartData(m_data, id);
                    m_listOfData.push_back(dataInterface);

                    // Setup data curve.
                    QwtPlotCurve *curve = new QwtPlotCurve();
                    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
                    curve->setData(*dataInterface);
                    curve->attach(plot);
                }

                QScrollArea *scrollArea = new QScrollArea(this);
                QWidget *widgetForScrolling = new QWidget(scrollArea);

                // Combine all plots.
                QHBoxLayout *plotsLayout = new QHBoxLayout(widgetForScrolling);

                vector<QwtPlot*>::iterator it = m_listOfPlots.begin();
                for(;it < m_listOfPlots.end(); it++) {
                    plotsLayout->addWidget((*it));
                }

                widgetForScrolling->setLayout(plotsLayout);
                scrollArea->setWidget(widgetForScrolling);

                // Buffer control.
                m_bufferFilling = new QLabel("Ringbuffer: 0 SensorBoardData received.");

                QPushButton *saveRecordingsFileBtn = new QPushButton("Save as .rec", this);
                QObject::connect(saveRecordingsFileBtn, SIGNAL(clicked()), this, SLOT(saveRecordingsFile()));

                QPushButton *saveCSVFileBtn = new QPushButton("Save as .csv", this);
                QObject::connect(saveCSVFileBtn, SIGNAL(clicked()), this, SLOT(saveCSVFile()));

                QHBoxLayout *controlLayout = new QHBoxLayout();
                controlLayout->addWidget(m_bufferFilling);
                controlLayout->addWidget(saveRecordingsFileBtn);
                controlLayout->addWidget(saveCSVFileBtn);

                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(controlLayout);
                mainLayout->addWidget(scrollArea);

                setLayout(mainLayout);

                // Timer for sending data regularly.
                QTimer* timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                timer->start(50);
            }

            IrUsChartsWidget::~IrUsChartsWidget() {}

            void IrUsChartsWidget::TimerEvent() {
                vector<QwtPlot*>::iterator it = m_listOfPlots.begin();
                for(;it < m_listOfPlots.end(); it++) {
                    (*it)->replot();
                }
                {
                    Lock l(m_receivedSensorBoardDataContainersMutex);

                    stringstream s;
                    s << "Ringbuffer: " << m_receivedSensorBoardDataContainers.size() << "/" << m_bufferMax << " SensorBoardData received.";

                    m_bufferFilling->setText(s.str().c_str());
                }
            }

            void IrUsChartsWidget::saveRecordingsFile() {
                string fn = QFileDialog::getSaveFileName(this, tr("Save received containers as .rec file"), "", tr("Recording files (*.rec)")).toStdString();
                {
                    Lock l(m_receivedSensorBoardDataContainersMutex);

                    if (!fn.empty()) {
                        stringstream s;
                        s << "file://" << fn;
                        core::io::URL url(s.str());

                        try {
                            SharedPointer<ostream> out = core::io::StreamFactory::getInstance().getOutputStream(url);

                            deque<Container>::iterator it = m_receivedSensorBoardDataContainers.begin();
                            for(;it < m_receivedSensorBoardDataContainers.end(); it++) {
                                (*out) << (*it);
                            }

                            out->flush();
                        }
                        catch(core::exceptions::InvalidArgumentException &iae) {
                            cerr << "Error: " << iae.toString() << endl;
                        }
                    }

                }
            }

            void IrUsChartsWidget::saveCSVFile() {
                string fn = QFileDialog::getSaveFileName(this, tr("Save received containers as .csv file"), "", tr("CSV files (*.csv)")).toStdString();
                {
                    Lock l(m_receivedSensorBoardDataContainersMutex);

                    if (!fn.empty()) {
                        stringstream s;
                        s << "file://" << fn;
                        core::io::URL url(s.str());

                        try {
                            SharedPointer<ostream> out = core::io::StreamFactory::getInstance().getOutputStream(url);

                            // Write header.
                            (*out) << "Time stamp sent long" << ";" << "Time stamp sent short [microseconds]" << ";" << "Time stamp received long" << ";" << "Time stamp received short [microseconds]";

                            map<uint32_t, string>::iterator jt = m_mapOfSensors.begin();
                            for(;jt != m_mapOfSensors.end(); jt++) {
                                (*out) << ";" << jt->second;
                            }
                            (*out) << endl;

                            deque<Container>::iterator it = m_receivedSensorBoardDataContainers.begin();
                            for(;it != m_receivedSensorBoardDataContainers.end(); it++) {
                                Container c = (*it);
                                automotive::miniature::SensorBoardData sbd = c.getData<automotive::miniature::SensorBoardData>();

                                // Write time stamps.
                                (*out) << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ";";
                                (*out) << c.getSentTimeStamp().toMicroseconds() << ";";
                                (*out) << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << ";";
                                (*out) << c.getReceivedTimeStamp().toMicroseconds();

                                // Write data.
                                map<uint32_t, string>::iterator jt2 = m_mapOfSensors.begin();
                                for(;jt2 != m_mapOfSensors.end(); jt2++) {
                                    (*out) << ";" << sbd.getValueForKey_MapOfDistances(jt2->first);
                                }
                                (*out) << endl;
                            }

                            out->flush();
                        }
                        catch(core::exceptions::InvalidArgumentException &iae) {
                            cerr << "Error: " << iae.toString() << endl;
                        }
                    }

                }
            }

            void IrUsChartsWidget::nextContainer(Container &container) {
                if (container.getDataType() == automotive::miniature::SensorBoardData::ID()) {
                    automotive::miniature::SensorBoardData sbd = container.getData<automotive::miniature::SensorBoardData>();

                    m_data.push_back(sbd);

                    if (m_data.size() > 10*15) {
                        m_data.pop_front();
                    }

                    {
                        Lock l(m_receivedSensorBoardDataContainersMutex);
                        if (m_receivedSensorBoardDataContainers.size() < m_bufferMax) {
                            m_receivedSensorBoardDataContainers.push_back(container);
                        }
                    }
                }
            }

        }
    }
}
