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

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <sstream>
#include <string>

#include "core/data/TimeStamp.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"

#include "plugins/cutter/CutterWidget.h"

namespace cockpit {

    namespace plugins {

        namespace cutter {

            using namespace std;
            using namespace core;
            using namespace core::data;

            CutterWidget::CutterWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_containerWidget(NULL),
                m_desc(NULL),
                m_mapOfContainers(),
                m_mapOfSelectedContainers(),
                m_in(NULL),
                m_numberOfCounters(0) {
                // Set size.
                setMinimumSize(640, 480);

                // Button control.
                QPushButton *loadFileBtn = new QPushButton("Load recording", this);
                QPushButton *saveFileBtn = new QPushButton("Save recording", this);

                QObject::connect(loadFileBtn, SIGNAL(clicked()), this, SLOT(loadFile()));
                QObject::connect(saveFileBtn, SIGNAL(clicked()), this, SLOT(saveFile()));

                QHBoxLayout *fileOperations = new QHBoxLayout();
                fileOperations->addWidget(loadFileBtn);
                fileOperations->addWidget(saveFileBtn);

                // Create list widget.
                m_containerWidget = new QListWidget(this);
                m_containerWidget->setSortingEnabled(true);

                m_desc = new QLabel("No file loaded.");

                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(fileOperations);
                mainLayout->addWidget(m_desc);
                mainLayout->addWidget(m_containerWidget);

                setLayout(mainLayout);
            }

            CutterWidget::~CutterWidget() {}

            void CutterWidget::loadFile() {
                string fn = QFileDialog::getOpenFileName(this, tr("Open previous recording file"), "", tr("Recording files (*.rec)")).toStdString();

                if (!fn.empty()) {
                    stringstream s;
                    s << "file://" << fn;
                    core::io::URL url(s.str());

                    try {
                        m_in = core::io::StreamFactory::getInstance().getInputStream(url);

                        // Clear any error flags.
                        m_in->clear();

                        // Seek to the beginning of the input stream.
                        m_in->seekg(ios::beg);
                        if (m_in->good()) {
                            m_containerWidget->clear();                
                            m_mapOfContainers.clear();
                            m_numberOfCounters = 0;

                            Container c;
                            while (m_in->good()) {
                                // Read container.
                                (*m_in) >> c;

                                // Read container meta data.
                                uint32_t containerDataTypeID = (uint32_t)c.getDataType();
                                string containerName = c.toString();

                                // If a desc is missing, generate one.
                                if (containerName.size() == 0) {
                                    stringstream desc;
                                    desc << "Undefined (type ID = " << containerDataTypeID << ")";
                                    containerName = desc.str();
                                }

                                m_mapOfContainers[containerDataTypeID] = containerName;
                                m_numberOfCounters++;
                            }

                            stringstream desc;
                            desc << "Successfully opened '" << fn << "' containing " << m_numberOfCounters << " containers.";
                            m_desc->setText(desc.str().c_str());

                            map<uint32_t, string>::iterator it = m_mapOfContainers.begin();
                            for(;it != m_mapOfContainers.end(); it++) {
                                string v = it->second;
                                
                                QListWidgetItem *item = new QListWidgetItem();
                                item->setText(v.c_str());
                                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                                item->setCheckState(Qt::Checked);

                                m_containerWidget->addItem(item);
                            }
                        }
                    }
                    catch(core::exceptions::InvalidArgumentException &iae) {
                        cerr << "Error: " << iae.toString() << endl;
                    }
                }
            }

            void CutterWidget::saveFile() {
                string fn = QFileDialog::getSaveFileName(this, tr("Save selected types of containers to file"), "", tr("Recording files (*.rec)")).toStdString();

                if (!fn.empty()) {
                    m_mapOfSelectedContainers.clear();

                    for(int i = 0; i < m_containerWidget->count(); i++) {
                        if (m_containerWidget->item(i)->checkState() == Qt::Checked) {
                            string toFind = m_containerWidget->item(i)->text().toStdString();

                            map<uint32_t, string>::iterator it = m_mapOfContainers.begin();
                            uint32_t val = 0;
                            for(;it != m_mapOfContainers.end(); it++) {
                                string v = it->second;
                                val = it->first;

                                if (v.compare(toFind) == 0) {
                                    break;
                                }
                            }

                            m_mapOfSelectedContainers[val] = toFind;
                        }
                    }

                    stringstream s;
                    s << "file://" << fn;
                    core::io::URL url(s.str());

                    try {
                        SharedPointer<ostream> out = core::io::StreamFactory::getInstance().getOutputStream(url);

                        // Clear any error flags.
                        m_in->clear();

                        // Seek to the beginning of the input stream.
                        m_in->seekg(ios::beg);
                        if (m_in->good()) {
                            Container c;
                            while (m_in->good()) {
                                // Read container.
                                (*m_in) >> c;

                                // Read container meta data.
                                uint32_t containerDataTypeID = (uint32_t)c.getDataType();

                                // Check if this container needs to be written.
                                map<uint32_t, string>::iterator it = m_mapOfSelectedContainers.find(containerDataTypeID);
                                if (it != m_mapOfSelectedContainers.end()) {
                                    (*out) << c;
                                }
                            }
                        }

                        out->flush();
                    }
                    catch(core::exceptions::InvalidArgumentException &iae) {
                        cerr << "Error: " << iae.toString() << endl;
                    }
                }

            }

        }
    }
}
