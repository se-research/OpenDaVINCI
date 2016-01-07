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

#ifndef HESPERIA_DATA_CAMERA_IMAGEGRABBERID_H_
#define HESPERIA_DATA_CAMERA_IMAGEGRABBERID_H_

#include <string>

#include "core/opendavinci.h"

#include "core/data/SerializableData.h"

namespace hesperia {
    namespace data {
        namespace camera {

            using namespace std;

            /**
             * This class implements a CAN message.
             */
            class OPENDAVINCI_API ImageGrabberID : public core::data::SerializableData {
                public:
                    /**
                     * Constructor.
                     *
                     * @param name Name.
                     */
                    ImageGrabberID(const string &name);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ImageGrabberID(const ImageGrabberID &obj);

                    virtual ~ImageGrabberID();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ImageGrabberID& operator=(const ImageGrabberID &obj);

                    /**
                     * This method returns the name.
                     *
                     * @return Name.
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
} // hesperia::data::camera

#endif /*HESPERIA_DATA_CAMERA_IMAGEGRABBERID_H_*/
