/**
 * OpenDLV - Simulation environment
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

#ifndef HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_
#define HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_

#include <vector>

#include "opendlv/data/situation/Behavior.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/situation/StartType.h"
#include "opendlv/data/situation/StopType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a point ID driver.
             */
            class OPENDAVINCI_API PointIDDriver : public Behavior {
                public:
                    PointIDDriver();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointIDDriver(const PointIDDriver &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointIDDriver& operator=(const PointIDDriver &obj);

                    virtual ~PointIDDriver();

                    virtual void accept(SituationVisitor &visitor);

                    /**
                     * This method returns the starttype of this point-ID-driver.
                     *
                     * @return Starttype of this point-ID-driver.
                     */
                    StartType* getStartType() const;

                    /**
                     * This method sets the point-ID-driver's starttype.
                     *
                     * @param st Starttype of this point-ID-driver.
                     */
                    void setStartType(StartType *st);

                    /**
                     * This method returns the stoptype of this point-ID-driver.
                     *
                     * @return Stoptype of this point-ID-driver.
                     */
                    StopType* getStopType() const;

                    /**
                     * This method sets the point-ID-driver's stoptype.
                     *
                     * @param st Stoptype of this point-ID-driver.
                     */
                    void setStopType(StopType *st);

                    /**
                     * This method returns the constant acceleration.
                     *
                     * @return Constant acceleration.
                     */
                    double getConstantAcceleration() const;

                    /**
                     * This method sets the constant acceleration.
                     *
                     * @param a Constant acceleration.
                     */
                    void setConstantAcceleration(const double &a);

                    /**
                     * This method returns the constant velocity.
                     *
                     * @return Constant velocity.
                     */
                    double getConstantVelocity() const;

                    /**
                     * This method sets the constant velocity.
                     *
                     * @param v Constant velocity.
                     */
                    void setConstantVelocity(const double &v);

                    /**
                     * This method adds a PointID.
                     *
                     * @param p PointID to add.
                     */
                    void addPointID(const PointID &p);

                    /**
                     * This method returns the list of PointIDs.
                     *
                     * @return List of PointIDs.
                     */
                    vector<PointID> getListOfPointIDs() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    StartType *m_startType;
                    StopType *m_stopType;
                    double m_constantAcceleration;
                    double m_constantVelocity;
                    vector<PointID> m_listOfPointIDs;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const PointIDDriver &obj);

                    /**
                     * This method clean's up the data.
                     */
                    void cleanUp();
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_*/
