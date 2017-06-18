/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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

#include <QtCore>
#include <QtGui>

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
#include <memory>
#include <sstream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/io/StreamFactory.h"
#include "opendavinci/odcore/io/URL.h"
#include "plugins/chartviewer/ChartData.h"
#include "plugins/chartviewer/ChartWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace chartviewer {

            using namespace std;
            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::data;

            ChartWidget::ChartWidget(const PlugIn &/*plugIn*/, const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName, const odcore::base::KeyValueConfiguration &/*kvc*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataType(dataType),
                m_senderStamp(senderStamp),
                m_fieldName(fieldName),
                m_plot(),
                m_plotCurve(),
                m_chartData(),
                m_data(),
                m_bufferMax(10000),
                m_bufferFilling(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Setup plot.
                {
                    m_plot = new QwtPlot(this);
                    m_plot->setAxisScale(QwtPlot::yLeft, -2, 10);
//                    m_plot->axisScaleEngine(QwtPlot::yBottom)->setAttribute(QwtScaleEngine::Floating, true);
                    m_plot->setMinimumSize(350, 300);
                    m_plot->setCanvasBackground(Qt::white);
                    m_plot->setFrameStyle(QFrame::NoFrame);
                    m_plot->setLineWidth(0);
                    m_plot->setAxisTitle(QwtPlot::xBottom, "t");
                    m_plot->setAxisTitle(QwtPlot::yLeft, title.c_str());

                    // Setup data interface.
                    m_chartData = new ChartData(m_data);

                    // Setup data curve.
                    m_plotCurve = new QwtPlotCurve();
                    m_plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
                    m_plotCurve->setData(*m_chartData);
                    m_plotCurve->attach(m_plot);
                }

                // Buffer control.
                m_bufferFilling = new QLabel("Ringbuffer: 0 entries received.");

                QPushButton *saveCSVFileBtn = new QPushButton("Save as .csv", this);
                QObject::connect(saveCSVFileBtn, SIGNAL(clicked()), this, SLOT(saveCSVFile()));

                QHBoxLayout *controlLayout = new QHBoxLayout();
                controlLayout->addWidget(m_bufferFilling);
                controlLayout->addWidget(saveCSVFileBtn);

                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(controlLayout);
                mainLayout->addWidget(m_plot);

                setLayout(mainLayout);

                // Timer for sending data regularly.
                QTimer* timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                timer->start(50);
            }

            ChartWidget::~ChartWidget() {}

            void ChartWidget::TimerEvent() {
                m_plot->replot();
            }

            void ChartWidget::saveCSVFile() {
                string fn = QFileDialog::getSaveFileName(this, tr("Save received data as .csv file"), "", tr("CSV files (*.csv)")).toStdString();
                cout << "Filename = " << fn << endl;
//                {
//                    Lock l(m_receivedSensorBoardDataContainersMutex);

//                    if (!fn.empty()) {
//                        stringstream s;
//                        s << "file://" << fn;
//                        odcore::io::URL url(s.str());

//                        try {
//                            std::shared_ptr<ostream> out = odcore::io::StreamFactory::getInstance().getOutputStream(url);

//                            // Write header.
//                            (*out) << "Time stamp sent long" << ";" << "Time stamp sent short [microseconds]" << ";" << "Time stamp received long" << ";" << "Time stamp received short [microseconds]";

//                            map<uint32_t, string>::iterator jt = m_mapOfSensors.begin();
//                            for(;jt != m_mapOfSensors.end(); jt++) {
//                                (*out) << ";" << jt->second;
//                            }
//                            (*out) << endl;

//                            deque<Container>::iterator it = m_receivedSensorBoardDataContainers.begin();
//                            for(;it != m_receivedSensorBoardDataContainers.end(); it++) {
//                                Container c = (*it);
//                                automotive::miniature::SensorBoardData sbd = c.getData<automotive::miniature::SensorBoardData>();

//                                // Write time stamps.
//                                (*out) << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ";";
//                                (*out) << c.getSentTimeStamp().toMicroseconds() << ";";
//                                (*out) << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << ";";
//                                (*out) << c.getReceivedTimeStamp().toMicroseconds();

//                                // Write data.
//                                map<uint32_t, string>::iterator jt2 = m_mapOfSensors.begin();
//                                for(;jt2 != m_mapOfSensors.end(); jt2++) {
//                                    (*out) << ";" << sbd.getValueForKey_MapOfDistances(jt2->first);
//                                }
//                                (*out) << endl;
//                            }

//                            out->flush();
//                        }
//                        catch(odcore::exceptions::InvalidArgumentException &iae) {
//                            cerr << "Error: " << iae.toString() << endl;
//                        }
//                    }

//                }
            }

            void ChartWidget::nextContainer(Container &container) {
                if ( (container.getDataType() == m_dataType) && (container.getSenderStamp() == m_senderStamp) ) {
                    cout << "ChartWidget = " << container.getDataType() << endl;
                }

//                if (container.getDataType() == automotive::miniature::SensorBoardData::ID()) {
//                    automotive::miniature::SensorBoardData sbd = container.getData<automotive::miniature::SensorBoardData>();

//                    m_data.push_back(sbd);

//                    if (m_data.size() > 10*15) {
//                        m_data.pop_front();
//                    }

//                    {
//                        Lock l(m_receivedSensorBoardDataContainersMutex);
//                        if (m_receivedSensorBoardDataContainers.size() < m_bufferMax) {
//                            m_receivedSensorBoardDataContainers.push_back(container);
//                        }
//                    }
//                }
            }

        }
    }
}
