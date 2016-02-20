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
#include <Qt/qlistwidget.h>
#include <Qt/qtimer.h>
#include <qatomic_x86_64.h>
#include <qglobal.h>
#include <qimage.h>
#include <qpainter.h>
#include <qstring.h>

#include <algorithm>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "plugins/sharedimageviewer/SharedImageViewerWidget.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

class QPaintEvent;
namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace sharedimageviewer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::data::image;

            SharedImageViewerWidget::SharedImageViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_sharedImageMemoryMutex(),
                m_sharedImage(),
                m_sharedImageMemory(),
                m_drawableImage(NULL),
                m_grayscale(),
                m_list(NULL),
                m_listOfAvailableSharedImages(),
                m_mapOfAvailableSharedImages() {

                // Set size.
                setMinimumSize(640, 480);

                // Create grayscale table.
                for(int i = 0; i < 256; i++) m_grayscale.push_back(qRgb(i,i,i));

                QGridLayout *gridLayout = new QGridLayout(this);

                m_list = new QListWidget(this);
                connect(m_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectedSharedImage(QListWidgetItem*)));

                gridLayout->addWidget(m_list);

                setLayout(gridLayout);

                QTimer *timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(update()));
                const uint32_t fps = 25;
                timer->start(1000 / fps);
            }

            SharedImageViewerWidget::~SharedImageViewerWidget() {
                Lock l(m_sharedImageMemoryMutex);

                OPENDAVINCI_CORE_DELETE_POINTER(m_drawableImage);
            }

            void SharedImageViewerWidget::selectedSharedImage(QListWidgetItem *item) {
                if (item != NULL) {
                    // Retrieve stored shared image.
                    SharedImage si = m_mapOfAvailableSharedImages[item->text().toStdString()];

                    if ( (si.getWidth() * si.getHeight()) > 0 ) {
                        Lock l(m_sharedImageMemoryMutex);

                        cerr << "Using shared image: " << si.toString() << endl;
                        setWindowTitle(QString::fromStdString(si.toString()));

                        m_sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                        m_sharedImage = si;

                        // Remove the selection box.
                        m_list->hide();
                    }
                }
            }

            void SharedImageViewerWidget::nextContainer(Container &c) {
                if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                    SharedImage si = c.getData<SharedImage>();

                    if ( ( (si.getWidth() * si.getHeight()) > 0) && (si.getName().size() > 0) ) {
                        // Check if this shared image is already in the list.
                        vector<string>::iterator result = std::find(m_listOfAvailableSharedImages.begin(), m_listOfAvailableSharedImages.end(), si.getName());
                        if (result == m_listOfAvailableSharedImages.end()) {
                            m_listOfAvailableSharedImages.push_back(si.getName());

                            QString item = QString::fromStdString(si.getName());
                            m_list->addItem(item);

                            // Store for further usage.
                            m_mapOfAvailableSharedImages[si.getName()] = si;
                        }
                    }
                }
            }

            void SharedImageViewerWidget::paintEvent(QPaintEvent * /*evnt*/) {
                Lock l(m_sharedImageMemoryMutex);

                if ( (m_sharedImageMemory.isValid()) && (m_sharedImageMemory->isValid()) ) {
                    m_sharedImageMemory->lock();

                    OPENDAVINCI_CORE_DELETE_POINTER(m_drawableImage);
                    if (m_sharedImage.getBytesPerPixel() == 3) {
                        m_drawableImage = new QImage((uchar*)(static_cast<char*>(m_sharedImageMemory->getSharedMemory())), m_sharedImage.getWidth(), m_sharedImage.getHeight(), m_sharedImage.getBytesPerPixel() * m_sharedImage.getWidth(), QImage::Format_RGB888);
                        *m_drawableImage = m_drawableImage->rgbSwapped();
                    }
                    else if (m_sharedImage.getBytesPerPixel() == 1) {
                        m_drawableImage = new QImage((uchar*)(static_cast<char*>(m_sharedImageMemory->getSharedMemory())), m_sharedImage.getWidth(), m_sharedImage.getHeight(), m_sharedImage.getBytesPerPixel() * m_sharedImage.getWidth(), QImage::Format_Indexed8);
                        m_drawableImage->setColorTable(m_grayscale);
                    }

                    if (m_drawableImage != NULL) {
                        QPainter widgetPainter(this);
                        widgetPainter.drawImage(0, 0, *m_drawableImage);
                    }
                    m_sharedImageMemory->unlock();
                }
            }

        }
    }
}

