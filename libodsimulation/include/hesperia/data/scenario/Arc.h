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

#ifndef HESPERIA_CORE_DATA_SCENARIO_ARC_H_
#define HESPERIA_CORE_DATA_SCENARIO_ARC_H_

#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/SerializableData.h"

#include "hesperia/data/scenario/StraightLine.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents an arc.
             */
            class OPENDAVINCI_API Arc : public StraightLine {
                public:
                    Arc();

                    virtual ~Arc();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Arc(const Arc &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Arc& operator=(const Arc &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the radius.
                     *
                     * @return Radius.
                     */
                    double getRadius() const;

                    /**
                     * This method sets the radius.
                     *
                     * @param r New radius.
                     */
                    void setRadius(const double &r);

                    /**
                     * This method returns the beginning of the interval
                     * for computing the arc.
                     *
                     * @return Beginning of interval.
                     */
                    double getBeginInterval() const;

                    /**
                     * This method sets the beginning of the interval
                     * for computing the arc.
                     *
                     * @param bi Beginning of interval.
                     */
                    void setBeginInterval(const double &bi);

                    /**
                     * This method returns the end of the interval
                     * for computing the arc.
                     *
                     * @return End of interval.
                     */
                    double getEndInterval() const;

                    /**
                     * This method sets the end of the interval
                     * for computing the arc.
                     *
                     * @param ei End of interval.
                     */
                    void setEndInterval(const double &ei);

                    /**
                     * This method returns the rotation around the z-axis.
                     *
                     * @return Rotation around the z-axis.
                     */
                    double getRotationZ() const;

                    /**
                     * This method sets the rotation around the z-axis.
                     *
                     * @param rotationZ Rotation around z-axis.
                     */
                    void setRotationZ(const double &rotationZ);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    double m_radius;
                    double m_beginInterval;
                    double m_endInterval;
                    double m_rotationZ;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_ARC_H_*/
