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

#include <Qt/qcombobox.h>
#include <Qt/qgridlayout.h>
#include <Qt/qlabel.h>
#include <Qt/qpushbutton.h>
#include <Qt/qspinbox.h>
#include <Qt/qtreewidget.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qstringlist.h>

#include "core/platform.h"
#include "core/base/Lock.h"
#include "core/base/TreeNode.h"
#include "core/macros.h"
#include "plugins/birdseyemap/BirdsEyeMapMapWidget.h"
#include "plugins/birdseyemap/BirdsEyeMapWidget.h"
#include "plugins/birdseyemap/SelectableNodeDescriptor.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace core { namespace data { class Container; } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace core::base;
            using namespace core::data;
            using namespace hesperia::scenegraph;

            BirdsEyeMapWidget::BirdsEyeMapWidget(const PlugIn &plugIn, QWidget *prnt) :
                QWidget(prnt),
                m_birdsEyeMapMapWidget(NULL),
                m_cameraSelector(NULL),
                m_cameraAssignableNodesUpdateMutex(),
                m_cameraAssignableNodesUpdate(false),
                m_mapOfSceneNodeDescriptors(),
                m_zoomLevel(NULL),
                m_textualSceneGraph(NULL),
                m_textualSceneGraphRootUpdateMutex(),
                m_textualSceneGraphRootUpdate(false),
                m_selectableNodeDescriptorTreeMutex(),
                m_selectableNodeDescriptorTree(NULL) {

                QGridLayout *environmentGrid = new QGridLayout(this);

                // Setup selectable scene graph elements.
                m_textualSceneGraph = new QTreeWidget(this);
                m_textualSceneGraph->setMaximumWidth(160);
                m_textualSceneGraph->setColumnCount(1);

                QStringList headerLabel;
                headerLabel << tr("SceneGraph");
                m_textualSceneGraph->setColumnWidth(0, 180);
                m_textualSceneGraph->setHeaderLabels(headerLabel);

                connect(m_textualSceneGraph, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(itemChanged(QTreeWidgetItem *, int)));

                // Camera control.
                QLabel *lblCamera = new QLabel(tr("Camera:"));
                m_cameraSelector = new QComboBox(this);
                m_cameraSelector->addItem(tr("Free Camera"));

                connect(m_cameraSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(selectedItemChanged(const QString &)));

                // Zoom control.
                QLabel *lblZoomLevel = new QLabel(tr("Zoom level:"));
                m_zoomLevel = new QSpinBox(this);
                m_zoomLevel->setRange(1, 100);
                m_zoomLevel->setSingleStep(10);
                m_zoomLevel->setSuffix("%");
                m_zoomLevel->setValue(50);

                connect(m_zoomLevel, SIGNAL(valueChanged(int)), this, SLOT(changeZoom(int)));

                QPushButton *btn = new QPushButton(tr("Reset ego trace"));
                connect(btn, SIGNAL(released()), this, SLOT(resetTrace()));

                QWidget *sideBar = new QWidget(this);
                QGridLayout *sideBarLayout = new QGridLayout(this);
                sideBarLayout->addWidget(lblZoomLevel, 0, 0);
                sideBarLayout->addWidget(m_zoomLevel, 1, 0);
                sideBarLayout->addWidget(lblCamera, 2, 0);
                sideBarLayout->addWidget(m_cameraSelector, 3, 0);
                sideBarLayout->addWidget(btn, 4, 0);

                sideBarLayout->addWidget(m_textualSceneGraph, 5, 0);
                sideBar->setLayout(sideBarLayout);

                // Setup 2D viewer.
                m_birdsEyeMapMapWidget = new BirdsEyeMapMapWidget(plugIn, this, *this, *this);

                // Setup layout.
                environmentGrid->addWidget(m_birdsEyeMapMapWidget, 0, 0);
                environmentGrid->addWidget(sideBar, 0, 1);
                environmentGrid->setColumnStretch(0, 1);
                environmentGrid->setColumnStretch(1, 0);

                setLayout(environmentGrid);
            }

            BirdsEyeMapWidget::~BirdsEyeMapWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_selectableNodeDescriptorTree);
            }

            void BirdsEyeMapWidget::updateListOfCameraAssignableNodes(const vector<SceneNodeDescriptor> &list) {
                if (list.size() > 0) {
                    {
                        Lock l(m_cameraAssignableNodesUpdateMutex);
                        m_cameraAssignableNodesUpdate = true;
                    }

                    // Remove old selectable cameras.
                    m_cameraSelector->clear();
                    m_mapOfSceneNodeDescriptors.clear();
                    m_cameraSelector->addItem(tr("Free Camera"));

                    vector<SceneNodeDescriptor>::const_iterator it = list.begin();
                    while (it != list.end()) {
                        SceneNodeDescriptor snd = (*it++);
                        string item = snd.getName();
                        m_mapOfSceneNodeDescriptors[item] = snd;

                        if (item.size() > 0) {
                            m_cameraSelector->addItem(item.c_str());
                        }
                    }

                    {
                        Lock l2(m_cameraAssignableNodesUpdateMutex);
                        m_cameraAssignableNodesUpdate = false;
                    }
                }
            }

            void BirdsEyeMapWidget::update(core::base::TreeNode<SelectableNodeDescriptor> *node) {
                if (node != NULL) {
                    {
                        Lock l(m_textualSceneGraphRootUpdateMutex);
                        m_textualSceneGraphRootUpdate = true;
                    }
                    Lock l(m_selectableNodeDescriptorTreeMutex);

                    // Remove old textual scene graph.
                    m_textualSceneGraph->clear();
                    OPENDAVINCI_CORE_DELETE_POINTER(m_selectableNodeDescriptorTree);

                    // The textual scene graph represents grouped scene graph elements.
                    // The first layer describes a group where as all children from that layer are selectable.
                    m_selectableNodeDescriptorTree = new TreeNode<SelectableNodeDescriptor>();
                    vector<TreeNode<SelectableNodeDescriptor>* > groups = node->getChildren();
                    vector<TreeNode<SelectableNodeDescriptor>* >::iterator it = groups.begin();
                    while (it != groups.end()) {
                        TreeNode<SelectableNodeDescriptor> *group = (*it++);
                        TreeNode<SelectableNodeDescriptor> *entry = new TreeNode<SelectableNodeDescriptor>();
                        entry->setValue(group->getValue());
                        m_selectableNodeDescriptorTree->addChild(entry);

                        QTreeWidgetItem *item = new QTreeWidgetItem();
                        m_textualSceneGraph->addTopLevelItem(item);
                        item->setText(0, group->getValue().getSceneNodeDescriptor().getName().c_str());
                        item->setFlags(item->flags() | Qt::ItemIsSelectable);

                        // Iterate through all children.
                        vector<TreeNode<SelectableNodeDescriptor>* > childrenFromGroup = group->getChildren();
                        vector<TreeNode<SelectableNodeDescriptor>* >::iterator jt = childrenFromGroup.begin();
                        while (jt != childrenFromGroup.end()) {
                            TreeNode<SelectableNodeDescriptor> *child = (*jt++);
                            TreeNode<SelectableNodeDescriptor> *childEntry = new TreeNode<SelectableNodeDescriptor>();
                            childEntry->setValue(child->getValue());
                            entry->addChild(childEntry);

                            QTreeWidgetItem *childItem = new QTreeWidgetItem();
                            childItem->setText(0, child->getValue().getSceneNodeDescriptor().getName().c_str());
                            if (child->getValue().isSelected()) {
                                childItem->setCheckState(0, Qt::Checked);
                            }
                            else {
                                childItem->setCheckState(0, Qt::Unchecked);
                            }
                            childItem->setFlags(childItem->flags() | Qt::ItemIsUserCheckable);
                            item->addChild(childItem);
                        }
                    }

                    {
                        Lock l2(m_textualSceneGraphRootUpdateMutex);
                        m_textualSceneGraphRootUpdate = false;
                    }
                }
            }

            void BirdsEyeMapWidget::changeZoom(int val) {
                if (m_birdsEyeMapMapWidget != NULL) {
                    m_birdsEyeMapMapWidget->setZoomLevel(((float)val)/100.0f);
                }
            }

            void BirdsEyeMapWidget::resetTrace() {
                if (m_birdsEyeMapMapWidget != NULL) {
                    m_birdsEyeMapMapWidget->resetEgoTrace();
                }
            }

            void BirdsEyeMapWidget::selectedItemChanged(const QString &item) {
                bool updating = false;
                {
                    Lock l(m_textualSceneGraphRootUpdateMutex);
                    updating = m_textualSceneGraphRootUpdate;
                }

                if (!updating) {
                    SceneNodeDescriptor snd;
                    if (item.toStdString() != "Free Camera") {
                        snd = m_mapOfSceneNodeDescriptors[item.toStdString()];
                    }
                    if (m_birdsEyeMapMapWidget != NULL) {
                        m_birdsEyeMapMapWidget->assignCameraTo(snd);
                    }
                }
            }

            void BirdsEyeMapWidget::itemChanged(QTreeWidgetItem *item, int column) {
                bool updating = false;
                {
                    Lock l(m_textualSceneGraphRootUpdateMutex);
                    updating = m_textualSceneGraphRootUpdate;
                }

                if (!updating) {
                    if (item != NULL) {
                        Lock l(m_selectableNodeDescriptorTreeMutex);

                        // Searching for textual representation in m_textualSceneGraphRoot and update it appropriately.
                        updateEntry(m_selectableNodeDescriptorTree, item->text(column).toStdString(), item->checkState(column) == Qt::Checked);

                        // Update nodes in visualization.
                        m_birdsEyeMapMapWidget->update(m_selectableNodeDescriptorTree);
                    }
                }
            }

            void BirdsEyeMapWidget::updateEntry(TreeNode<SelectableNodeDescriptor> *node, const string &name, const bool &enabled) {
                if (node != NULL) {
                    if (node->getValue().getSceneNodeDescriptor().getName() == name) {
                        SelectableNodeDescriptor snd = node->getValue();
                        snd.setSelected(enabled);
                        node->setValue(snd);
                    }

                    vector<TreeNode<SelectableNodeDescriptor>* > childrenOfNode = node->getChildren();
                    vector<TreeNode<SelectableNodeDescriptor>* >::iterator it = childrenOfNode.begin();
                    while (it != childrenOfNode.end()) {
                        TreeNode<SelectableNodeDescriptor> *child = (*it++);
                        updateEntry(child, name, enabled);
                    }
                }
            }

            void BirdsEyeMapWidget::nextContainer(Container &c) {
                m_birdsEyeMapMapWidget->nextContainer(c);
            }
        }
    }
} // plugins::birdseyemap
