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

#ifndef PLUGINS_ENVIRONMENTVIEWER_SELECTABLENODESCRIPTOR_H_
#define PLUGINS_ENVIRONMENTVIEWER_SELECTABLENODESCRIPTOR_H_

#include "hesperia/threeD/NodeDescriptor.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace std;

            /**
             * This class represents NodeDescriptor combined with a state
             * indicating whether this element was selected by the user.
             */
            class SelectableNodeDescriptor {
                public:
                    SelectableNodeDescriptor();

                    /**
                     * Constructor.
                     *
                     * @param nd NodeDescriptor.
                     * @param selected True iff selected.
                     */
                    SelectableNodeDescriptor(const hesperia::threeD::NodeDescriptor &nd, const bool &selected);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    SelectableNodeDescriptor(const SelectableNodeDescriptor &obj);

                    virtual ~SelectableNodeDescriptor();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    SelectableNodeDescriptor& operator=(const SelectableNodeDescriptor &obj);

                    /**
                     * This method returns the NodeDescriptor.
                     *
                     * @return Name.
                     */
                    const hesperia::threeD::NodeDescriptor getNodeDescriptor() const;

                    /**
                     * This method sets the NodeDescriptor.
                     *
                     * @param nd NodeDescriptor.
                     */
                    void setNodeDescriptor(const hesperia::threeD::NodeDescriptor &nd);

                    /**
                     * This method returns true if this NodeDescriptor is selected.
                     *
                     * @return True iff this NodeDescriptor element is selected.
                     */
                    bool isSelected() const;

                    /**
                     * This method sets the selection.
                     *
                     * @param selected True if this NodeDescriptor is selected.
                     */
                    void setSelected(const bool &selected);

                private:
                    hesperia::threeD::NodeDescriptor m_nodeDescriptor;
                    bool m_selected;
            };
        }
    }
} // plugins::environmentviewer

#endif /*PLUGINS_ENVIRONMENTVIEWER_SELECTABLENODESCRIPTOR_H_*/
