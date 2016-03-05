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

#ifndef COCKPIT_PLUGINS_SHAREDIMAGEVIEWER_SHAREDIMAGEVIEWERWIDGET_H_
#define COCKPIT_PLUGINS_SHAREDIMAGEVIEWER_SHAREDIMAGEVIEWERWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <string>
#include <vector>

#include <memory>
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

class QImage;
class QListWidget;
class QListWidgetItem;
class QPaintEvent;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace sharedimageviewer {

            using namespace std;

            /**
             * This class is the container for the shared image viewer widget.
             */
            class SharedImageViewerWidget : public QWidget, public odcore::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    SharedImageViewerWidget(const SharedImageViewerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    SharedImageViewerWidget& operator=(const SharedImageViewerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    SharedImageViewerWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~SharedImageViewerWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                public slots:
				    void selectedSharedImage(QListWidgetItem *item);

                private:
                    mutable odcore::base::Mutex m_sharedImageMemoryMutex;
                    odcore::data::image::SharedImage m_sharedImage;
                    std::shared_ptr<odcore::wrapper::SharedMemory> m_sharedImageMemory;
                    QImage *m_drawableImage;
                    QVector<QRgb> m_grayscale;

                    QListWidget *m_list;
                    vector<string> m_listOfAvailableSharedImages;
                    map<string, odcore::data::image::SharedImage> m_mapOfAvailableSharedImages;

                    virtual void paintEvent(QPaintEvent *evnt);
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_SHAREDIMAGEVIEWER_SHAREDIMAGEVIEWERWIDGET_H_*/

