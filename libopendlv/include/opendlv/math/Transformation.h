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

#ifndef HESPERIA_MATH_TRANSFORMATION_H_
#define HESPERIA_MATH_TRANSFORMATION_H_

#include "opendavinci/core/opendavinci.h"
#include "opendlv/data/environment/Point3.h"

namespace hesperia { namespace data { namespace environment { class Position; } } }

namespace hesperia {
    namespace math {

        /**
         * This class implements different transformation operations.
         */
        class OPENDAVINCI_API Transformation {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Transformation(const Transformation &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                Transformation& operator=(const Transformation &);

            public:
                Transformation();

                virtual ~Transformation();

                /**
                 * This method transforms the given cartesian coordinate from
                 * the position coordinate system to the world coordinate system.
                 *
                 * @param coordinate Coordinate to transform.
                 * @param position Position to be used.
                 * @return Transformed cartesian coordinate.
                 */
                hesperia::data::environment::Point3 transform(const hesperia::data::environment::Point3 &coordinate, const hesperia::data::environment::Position &position) const;

                /**
                 * This method transforms the given cartesian coordinate from
                 * the world coordinate system to the position coordinate system.
                 *
                 * @param coordinate Coordinate to transform.
                 * @param position Position to be used.
                 * @return Transformed cartesian coordinate.
                 */
                hesperia::data::environment::Point3 transformInversely(const hesperia::data::environment::Point3 &coordinate, const hesperia::data::environment::Position &position) const;
        };

    }
} // hesperia::math

#endif /*HESPERIA_MATH_TRANSFORMATION_H_*/
