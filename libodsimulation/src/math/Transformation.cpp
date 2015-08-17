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

#include "hesperia/math/Transformation.h"

namespace hesperia {
    namespace math {

        using namespace std;
        using namespace core::data;
        using namespace hesperia::data::environment;

        Transformation::Transformation() {}

        Transformation::~Transformation() {}

        Point3 Transformation::transform(const Point3 &coordinate, const Position &position) const {
            Point3 cc = coordinate;

            // Rotate the coordinate.
            cc.rotateX(position.getRotation().getX());
            cc.rotateY(position.getRotation().getY());
            cc.rotateZ(position.getRotation().getZ());

            // Translate the coordinate.
            cc += position.getPosition();

            return cc;
        }

        Point3 Transformation::transformInversely(const Point3 &coordinate, const Position &position) const {
            Point3 cc = coordinate;

            // Rotate the coordinate.
            cc.rotateX(-1 * position.getRotation().getX());
            cc.rotateY(-1 * position.getRotation().getY());
            cc.rotateZ(-1 * position.getRotation().getZ());

            // Translate the coordinate.
            cc -= position.getPosition();

            return cc;
        }

    }
} // hesperia::math
