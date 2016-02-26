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

#ifndef HESPERIA_DATA_ENVIRONMENT_NAMEDLINE_H_
#define HESPERIA_DATA_ENVIRONMENT_NAMEDLINE_H_

#include "opendlv/data/environment/Line.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;

            /**
             * This class can be used for line operations.
             */
            class OPENDAVINCI_API NamedLine : public Line {
                public:
                    NamedLine();

                    /**
                     * Constructor.
                     *
                     * @param A
                     * @param B
                     */
                    NamedLine(const string &name, const Point3 &A, const Point3 &B);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    NamedLine(const NamedLine &obj);

                    virtual ~NamedLine();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    NamedLine& operator=(const NamedLine &obj);

                    /**
                     * This method sets the name.
                     *
                     * @param n Name.
                     */
                    void setName(const string &n);

                    /**
                     * This method returns the name.
                     *
                     * @return name.
                     */
                    const string getName() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    string m_name;
            };

        }
    }
} // opendlv::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_NAMEDLINE_H_*/
