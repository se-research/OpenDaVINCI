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

#ifndef HESPERIA_CORE_DATA_SCENARIO_GROUND_H_
#define HESPERIA_CORE_DATA_SCENARIO_GROUND_H_

#include <string>

#include "core/opendavinci.h"
#include "core/data/SerializableData.h"

#include "hesperia/data/scenario/HeightImage.h"
#include "hesperia/data/scenario/Image.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Surroundings.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents the ground of the scenario.
             */
            class OPENDAVINCI_API Ground : public core::data::SerializableData, public ScenarioNode {
                public:
                    Ground();

                    virtual ~Ground();

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Ground(const Ground &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Ground& operator=(const Ground &obj);

                    /**
                     * This method returns the ground's name.
                     *
                     * @return Ground's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the ground's name.
                     *
                     * @param name Ground's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the aerial image.
                     *
                     * @return Aerial image.
                     */
                    const Image& getAerialImage() const;

                    /**
                     * This method sets the aerial image.
                     *
                     * @param ai Aerial image.
                     */
                    void setAerialImage(const Image &ai);

                    /**
                     * This method returns the height image.
                     *
                     * @return Height image.
                     */
                    const HeightImage& getHeightImage() const;

                    /**
                     * This method sets the height image.
                     *
                     * @param hi Height image.
                     */
                    void setHeightImage(const HeightImage &hi);

                    /**
                     * This method returns the surroundings.
                     *
                     * @return Surroundings.
                     */
                    const Surroundings& getSurroundings() const;

                    /**
                     * This method sets the surroundings.
                     *
                     * @param s Surroundings.
                     */
                    void setSurroundings(const Surroundings &s);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_name;
                    Image m_aerialImage;
                    HeightImage m_heightImage;
                    Surroundings m_surroundings;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_GROUND_H_*/
