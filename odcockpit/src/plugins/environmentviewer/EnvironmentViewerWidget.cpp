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

#include <Qt/qcombobox.h>
#include <Qt/qgridlayout.h>
#include <Qt/qlabel.h>
#include <Qt/qtreewidget.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qstringlist.h>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/TreeNode.h"
#include "plugins/GLControlFrame.h"
#include "plugins/environmentviewer/EnvironmentViewerGLWidget.h"
#include "plugins/environmentviewer/EnvironmentViewerWidget.h"
#include "plugins/environmentviewer/SelectableNodeDescriptor.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace odcore::base;
            using namespace odcore::data;
            using namespace opendlv::threeD;

            EnvironmentViewerWidget::EnvironmentViewerWidget(const PlugIn &plugIn, QWidget *prnt) :
                    QWidget(prnt),
                    m_viewerControlWidget(NULL),
                    m_environmentViewerGLWidget(NULL),
                    m_cameraSelector(NULL),
                    m_cameraAssignableNodesUpdateMutex(),
                    m_cameraAssignableNodesUpdate(false),
                    m_mapOfNodeDescriptors(),
                    m_backgroundSelector(NULL),
                    m_textualSceneGraph(NULL),
                    m_textualSceneGraphRootUpdateMutex(),
                    m_textualSceneGraphRootUpdate(false),
                    m_selectableNodeDescriptorTreeMutex(),
                    m_selectableNodeDescriptorTree(NULL) {

                QGridLayout *environmentGrid = new QGridLayout(this);

                // Setup 3D viewer.
                m_environmentViewerGLWidget = new EnvironmentViewerGLWidget(plugIn, this, *this, *this);
                m_viewerControlWidget = new GLControlFrame(m_environmentViewerGLWidget);

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

                // Background control.
                QLabel *lblBackgroundColor = new QLabel(tr("Background:"));
                m_backgroundSelector = new QComboBox(this);
                m_backgroundSelector->addItem(tr("black"));
                m_backgroundSelector->addItem(tr("white"));

                connect(m_backgroundSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(selectedItemChangedBackground(const QString &)));

                QWidget *sideBar = new QWidget(this);
                QGridLayout *sideBarLayout = new QGridLayout(this);
                sideBarLayout->addWidget(lblCamera, 0, 0);
                sideBarLayout->addWidget(m_cameraSelector, 1, 0);
                sideBarLayout->addWidget(lblBackgroundColor, 2, 0);
                sideBarLayout->addWidget(m_backgroundSelector, 3, 0);

                sideBarLayout->addWidget(m_textualSceneGraph, 4, 0);
                sideBar->setLayout(sideBarLayout);

                // Setup layout.
                environmentGrid->addWidget(m_viewerControlWidget, 0, 0);
                environmentGrid->addWidget(sideBar, 0, 1);
                environmentGrid->setColumnStretch(0, 1);
                environmentGrid->setColumnStretch(1, 0);

                setLayout(environmentGrid);
            }

            EnvironmentViewerWidget::~EnvironmentViewerWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_selectableNodeDescriptorTree);
            }

            void EnvironmentViewerWidget::updateListOfCameraAssignableNodes(const vector<NodeDescriptor> &list) {
                if (list.size() > 0) {
                    {
                        Lock l(m_cameraAssignableNodesUpdateMutex);
                        m_cameraAssignableNodesUpdate = true;
                    }

                    // Remove old selectable cameras.
                    m_cameraSelector->clear();
                    m_mapOfNodeDescriptors.clear();
                    m_cameraSelector->addItem(tr("Free Camera"));

                    vector<NodeDescriptor>::const_iterator it = list.begin();
                    while (it != list.end()) {
                        NodeDescriptor nd = (*it++);
                        string item = nd.getName();
                        m_mapOfNodeDescriptors[item] = nd;

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

            void EnvironmentViewerWidget::update(odcore::base::TreeNode<SelectableNodeDescriptor> *node) {
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
                        item->setText(0, group->getValue().getNodeDescriptor().getName().c_str());
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
                            childItem->setText(0, child->getValue().getNodeDescriptor().getName().c_str());
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

            void EnvironmentViewerWidget::selectedItemChangedBackground(const QString &item) {
                if (item.toStdString() == "black") {
                    m_environmentViewerGLWidget->setBackgroundColor(opendlv::data::environment::Point3(0, 0, 0));
                }
                if (item.toStdString() == "white") {
                    m_environmentViewerGLWidget->setBackgroundColor(opendlv::data::environment::Point3(1, 1, 1));
                }
            }

            void EnvironmentViewerWidget::selectedItemChanged(const QString &item) {
                bool updating = false;
                {
                    Lock l(m_textualSceneGraphRootUpdateMutex);
                    updating = m_textualSceneGraphRootUpdate;
                }

                if (!updating) {
                    NodeDescriptor nd;
                    if (item.toStdString() != "Free Camera") {
                        nd = m_mapOfNodeDescriptors[item.toStdString()];
                    }
                    m_environmentViewerGLWidget->assignCameraTo(nd);
                }
            }

            void EnvironmentViewerWidget::itemChanged(QTreeWidgetItem *item, int column) {
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
                        m_environmentViewerGLWidget->update(m_selectableNodeDescriptorTree);
                    }
                }
            }

            void EnvironmentViewerWidget::updateEntry(TreeNode<SelectableNodeDescriptor> *node, const string &name, const bool &enabled) {
                if (node != NULL) {
                    if (node->getValue().getNodeDescriptor().getName() == name) {
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

            void EnvironmentViewerWidget::nextContainer(Container &c) {
                m_environmentViewerGLWidget->nextContainer(c);
            }
        }
    }
} // plugins::environmentviewer
