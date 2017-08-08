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


#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/reflection/Field.h"
#include "opendavinci/odcore/reflection/Message.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/generated/odcockpit/SimplePlot.h"
#include "opendavinci/generated/odcore/data/reflection/AbstractField.h"
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
            using namespace odcore::reflection;

            ChartWidget::ChartWidget(const PlugIn &/*plugIn*/, const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                QWidget(prnt),
                m_messageResolver(),
                m_dataType(dataType),
                m_senderStamp(senderStamp),
                m_fieldName(fieldName),
                m_plot(),
                m_plotCurve(),
                m_chartData(),
                m_dataMutex(),
                m_data(),
                m_bufferMax(10000),
                m_bufferFilling(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                const string SEARCH_PATH = kvc.getValue<string>("odcockpit.directoriesForSharedLibaries");
                cout << "[odcockpit/chartviewer] Trying to find libodvd*.so files in: " << SEARCH_PATH << endl;

                const vector<string> paths = odcore::strings::StringToolbox::split(SEARCH_PATH, ',');
                m_messageResolver = unique_ptr<MessageResolver>(new MessageResolver(paths, "libodvd", ".so"));

                // Setup plot.
                {
                    m_plot = new QwtPlot(this);
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
                connect(this, SIGNAL(updateLabel(QString)), m_bufferFilling, SLOT(setText(QString)));

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
                {
                    Lock l(m_dataMutex);

                    if (!fn.empty()) {
                        fstream fout(fn, ios::out|ios::trunc);

                        // Write header.
                        fout << "time stamp sample time [microseconds]" << ";" << "value" << endl;

                        for(auto it = m_data.begin(); it != m_data.end(); it++) {
                            fout << setprecision(10) << it->first << ";" << setprecision(10) << it->second << endl;
                        }

                        fout.flush();
                    }
                }
            }

            void ChartWidget::nextContainer(Container &container) {
                Lock l(m_dataMutex);

                if ( (container.getDataType() == m_dataType) && (container.getSenderStamp() == m_senderStamp) ) {
                    double value = 0;
                    if ( container.getDataType() == odcockpit::SimplePlot::ID() ) {
                        odcockpit::SimplePlot sp = container.getData<odcockpit::SimplePlot>();
                        if (sp.containsKey_MapOfValues(m_fieldName)) {
                            value = sp.getValueForKey_MapOfValues(m_fieldName);
                        }
                    }
                    else {
                        bool successfullyMapped = false;
                        odcore::reflection::Message msg = m_messageResolver->resolve(container, successfullyMapped);
                        if (successfullyMapped) {
                            for(uint32_t i = 0; i < msg.getNumberOfFields(); i++) {
                                bool found = false;
                                std::shared_ptr<odcore::data::reflection::AbstractField> f = msg.getFieldByIdentifier(i, found);
                                if (f.get() && found && (0 == f->getShortFieldName().find(m_fieldName)) ) {
                                    if (f->getFieldDataType() <= odcore::data::reflection::AbstractField::DOUBLE_T) {
                                        found = false; bool extracted = false;
                                        value = msg.getValueFromScalarField<double>(i, found, extracted);
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    m_data.push_back(make_pair(container.getSampleTimeStamp().toMicroseconds(), value));
                    if (m_data.size() > m_bufferMax) {
                        m_data.pop_front();
                    }

                    {
                        stringstream sstr;
                        sstr << "Ringbuffer: " << m_data.size() << "/" << m_bufferMax << " entries received.";
                        const string str = sstr.str();
                        QString qs(str.c_str());
                        emit updateLabel(qs);
                    }
                }
            }

        }
    }
}
