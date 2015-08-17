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

#ifndef HESPERIA_SCENARIO_SCNXARCHIVE_H_
#define HESPERIA_SCENARIO_SCNXARCHIVE_H_

#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/SharedPointer.h"
#include "core/wrapper/DecompressedData.h"
#include "core/wrapper/Image.h"

#include "hesperia/data/scenario/ComplexModel.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/data/situation/Situation.h"


namespace hesperia {
    namespace scenario {

        using namespace std;

        // Forward declaration to prevent circular dependencies.
        class SCNXArchiveFactory;

        /**
         * This class represents the contents of an SCNX archive.
         */
        class OPENDAVINCI_API SCNXArchive {
            private:
                friend class SCNXArchiveFactory;

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                SCNXArchive(const SCNXArchive&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                SCNXArchive& operator=(const SCNXArchive&);

            private:
                /**
                 * Constructor.
                 *
                 * @param scenario Scenario data structure.
                 * @param dd Decompressed contents of an SCNX archive.
                 */
                SCNXArchive(const data::scenario::Scenario &scenario, core::SharedPointer<core::wrapper::DecompressedData> dd);

            public:
                virtual ~SCNXArchive();

                /**
                 * This method returns the contained scenario data.
                 *
                 * @return Scenario data.
                 */
                data::scenario::Scenario& getScenario();

                /**
                 * This method returns the aerial image.
                 *
                 * @return Aerial image or NULL if the SCNXArchive does not contain an aerial image.
                 */
                core::wrapper::Image* getAerialImage();

                /**
                 * This method returns the height image.
                 *
                 * @return Height image or NULL if the SCNXArchive does not contain a height image.
                 */
                core::wrapper::Image* getHeightImage();

                /**
                 * This method return the list of ground based complex models.
                 *
                 * @return List of ground based models.
                 */
                vector<data::scenario::ComplexModel*> getListOfGroundBasedComplexModels() const;

                /**
                 * This method return the list of defined situations
                 *
                 * @return List of situations.
                 */
                vector<data::situation::Situation> getListOfSituations() const;

                /**
                 * This method returns the input stream
                 * for reading the model data.
                 *
                 * @param modelFile Name of the model file.
                 * @return Input stream to read the model data or NULL if the name could not be found.
                 */
                core::SharedPointer<istream> getModelData(const string &modelFile) const;

            private:
                data::scenario::Scenario m_scenario;
                core::SharedPointer<core::wrapper::DecompressedData> m_decompressedData;
                core::wrapper::Image *m_aerialImage;
                core::wrapper::Image *m_heightImage;
        };

    }
} // hesperia::scenario

#endif /*HESPERIA_SCENARIO_SCNXARCHIVE_H_*/
