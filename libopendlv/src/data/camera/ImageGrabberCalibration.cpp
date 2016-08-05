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

#include <memory>
#include <sstream>
#include <string>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/camera/ExtrinsicParameters.h"
#include "opendlv/data/camera/ImageGrabberCalibration.h"
#include "opendlv/data/camera/IntrinsicParameters.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace std;
            using namespace odcore::data;
            using namespace odcore::base;

            ImageGrabberCalibration::ImageGrabberCalibration() :
                    m_extrinsicParameters(),
                    m_intrinsicParameters() {}

            ImageGrabberCalibration::ImageGrabberCalibration(const ImageGrabberCalibration &obj) :
                    m_extrinsicParameters(obj.getExtrinsicParameters()),
                    m_intrinsicParameters(obj.getIntrinsicParameters()) {}

            ImageGrabberCalibration::~ImageGrabberCalibration() {}

            ImageGrabberCalibration& ImageGrabberCalibration::operator=(const ImageGrabberCalibration &obj) {
                setExtrinsicParameters(obj.getExtrinsicParameters());
                setIntrinsicParameters(obj.getIntrinsicParameters());

                return (*this);
            }

            const ExtrinsicParameters ImageGrabberCalibration::getExtrinsicParameters() const {
                return m_extrinsicParameters;
            }

            void ImageGrabberCalibration::setExtrinsicParameters(const ExtrinsicParameters &extrinsicParameters) {
                m_extrinsicParameters = extrinsicParameters;
            }

            const IntrinsicParameters ImageGrabberCalibration::getIntrinsicParameters() const {
                return m_intrinsicParameters;
            }

            void ImageGrabberCalibration::setIntrinsicParameters(const IntrinsicParameters &intrinsicParameters) {
                m_intrinsicParameters = intrinsicParameters;
            }

            ostream& ImageGrabberCalibration::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_extrinsicParameters);

                s->write(2, m_intrinsicParameters);

                return out;
            }

            istream& ImageGrabberCalibration::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_extrinsicParameters);

                d->read(2, m_intrinsicParameters);

                return in;
            }

            int32_t ImageGrabberCalibration::getID() const {
                return 23;
            }

            const string ImageGrabberCalibration::getShortName() const {
                return "ImageGrabberCalibration";
            }

            const string ImageGrabberCalibration::getLongName() const {
                return "hesperia.data.camera.ImageGrabberCalibration";
            }

            const string ImageGrabberCalibration::toString() const {
                stringstream sstr;
                sstr << "Extrinsic: " << m_extrinsicParameters.toString() << "/Intrinsic: " << m_intrinsicParameters.toString();
                return sstr.str();
            }
        }
    }
} // opendlv::data::camera
