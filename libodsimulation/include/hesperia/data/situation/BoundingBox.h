/**
 * hesperia - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef HESPERIA_CORE_DATA_SITUATION_BOUNDINGBOX_H_
#define HESPERIA_CORE_DATA_SITUATION_BOUNDINGBOX_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/data/SerializableData.h"
#include "hesperia/data/situation/SituationNode.h"
#include "hesperia/data/situation/SituationVisitor.h"
#include "hesperia/data/situation/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a bounding box.
             */
            class OPENDAVINCI_API BoundingBox : public core::data::SerializableData, public SituationNode {
                public:
                    BoundingBox();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    BoundingBox(const BoundingBox &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    BoundingBox& operator=(const BoundingBox &obj);

                    virtual ~BoundingBox();

                    virtual void accept(SituationVisitor &visitor);

                    /**
                     * This method returns the upper/left corner.
                     *
                     * @return Upper/left position.
                     */
                    const Vertex3& getUpperLeft() const;

                    /**
                     * This method sets the upper/left corner.
                     *
                     * @param ul Upper/left position.
                     */
                    void setUpperLeft(const Vertex3 &ul);

                    /**
                     * This method returns the upper/right corner.
                     *
                     * @return Upper/right position.
                     */
                    const Vertex3& getUpperRight() const;

                    /**
                     * This method sets the upper/right corner.
                     *
                     * @param ur Upper/right position.
                     */
                    void setUpperRight(const Vertex3 &ur);

                    /**
                     * This method returns the lower/right corner.
                     *
                     * @return Lower/right position.
                     */
                    const Vertex3& getLowerRight() const;

                    /**
                     * This method sets the lower/right corner.
                     *
                     * @param lr Lower/right position.
                     */
                    void setLowerRight(const Vertex3 &lr);

                    /**
                     * This method returns the lower/left corner.
                     *
                     * @return Lower/left position.
                     */
                    const Vertex3& getLowerLeft() const;

                    /**
                     * This method sets the lower/left corner.
                     *
                     * @param ll Lower/left position.
                     */
                    void setLowerLeft(const Vertex3 &ll);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    Vertex3 m_upperLeft;
                    Vertex3 m_upperRight;
                    Vertex3 m_lowerRight;
                    Vertex3 m_lowerLeft;
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_BOUNDINGBOX_H_*/
