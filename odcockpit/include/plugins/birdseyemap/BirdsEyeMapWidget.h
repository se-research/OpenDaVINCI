/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPWIDGET_H_
#define PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPWIDGET_H_

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <qobjectdefs.h>
#include <qstring.h>
#include <qwidget.h>

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#include <map>
#include <string>
#include <vector>

#include "core/base/Mutex.h"
#include "core/io/conference/ContainerListener.h"
#include "core/strings/StringComparator.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"
#include "plugins/birdseyemap/CameraAssignableNodesListener.h"
#include "plugins/birdseyemap/SelectableNodeDescriptorTreeListener.h"

class QComboBox;
class QSpinBox;
class QTreeWidget;
class QTreeWidgetItem;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace core { namespace base { template <typename T> class TreeNode; } }
namespace core { namespace data { class Container; } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace std;

            /**
             * This class is the outer container for the 2D scene graph viewer
             * implemented in BirdsEyeMapMapWidget and a tree like data
             * structure on its right hand side.
             */
class BirdsEyeMapMapWidget;
class SelectableNodeDescriptor;

            class BirdsEyeMapWidget : public QWidget, public core::io::conference::ContainerListener, public CameraAssignableNodesListener, public SelectableNodeDescriptorTreeListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BirdsEyeMapWidget(const BirdsEyeMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BirdsEyeMapWidget& operator=(const BirdsEyeMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    BirdsEyeMapWidget(const PlugIn &plugIn, QWidget *prnt);

                    virtual ~BirdsEyeMapWidget();

                    virtual void nextContainer(core::data::Container &c);

                    virtual void update(core::base::TreeNode<SelectableNodeDescriptor> *node);

                    virtual void updateListOfCameraAssignableNodes(const vector<hesperia::scenegraph::SceneNodeDescriptor> &list);

                private slots:
                    /**
                     * This method is called whenever an item in the list changes
                     * its state.
                     *
                     * @param item Item that changed.
                     * @param column Number of column.
                     */
                    void itemChanged(QTreeWidgetItem *item, int column);

                    /**
                     * This method is called whenever an item in the combobox
                     * for the assignable camera changes its state.
                     *
                     * @param item Item that changed.
                     */
                    void selectedItemChanged(const QString &item);

                    /**
                     * This method is called whenever zoom level has been changed.
                     *
                     * @param val New value.
                     */
                    void changeZoom(int val);

                    /**
                     * This method is called whenever reset trace button is released.
                     */
                    void resetTrace();

                private:
                    BirdsEyeMapMapWidget *m_birdsEyeMapMapWidget;

                    QComboBox *m_cameraSelector;
                    core::base::Mutex m_cameraAssignableNodesUpdateMutex;
                    bool m_cameraAssignableNodesUpdate;
                    map<string, hesperia::scenegraph::SceneNodeDescriptor, core::strings::StringComparator> m_mapOfSceneNodeDescriptors;

                    QSpinBox *m_zoomLevel;

                    QTreeWidget *m_textualSceneGraph;
                    core::base::Mutex m_textualSceneGraphRootUpdateMutex;
                    bool m_textualSceneGraphRootUpdate;
                    core::base::Mutex m_selectableNodeDescriptorTreeMutex;
                    core::base::TreeNode<SelectableNodeDescriptor> *m_selectableNodeDescriptorTree;

                    /**
                     * This method updates the tree of SelectableNodeDescriptors.
                     *
                     * @param name name of the NodeDescriptor to be updated.
                     * @param enabled True if the NodeDescriptor is enabled.
                     */
                    void updateEntry(core::base::TreeNode<SelectableNodeDescriptor> *node, const string &name, const bool &enabled);
            };
        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPWIDGET_H_*/
