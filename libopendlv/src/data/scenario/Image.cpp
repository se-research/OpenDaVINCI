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
#include <ostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Image.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            Image::Image() :
                    m_fileName(""),
                    m_originX(0),
                    m_originY(0),
                    m_meterPerPixelX(0),
                    m_meterPerPixelY(0),
                    m_rotationZ(0) {}

            Image::Image(const Image &obj) :
                    SerializableData(),
                    m_fileName(obj.m_fileName),
                    m_originX(obj.m_originX),
                    m_originY(obj.m_originY),
                    m_meterPerPixelX(obj.m_meterPerPixelX),
                    m_meterPerPixelY(obj.m_meterPerPixelY),
                    m_rotationZ(obj.m_rotationZ) {}

            Image::~Image() {}

            Image& Image::operator=(const Image &obj) {
                setFileName(obj.getFileName());
                setOriginX(obj.getOriginX());
                setOriginY(obj.getOriginY());
                setMeterPerPixelX(obj.getMeterPerPixelX());
                setMeterPerPixelY(obj.getMeterPerPixelY());
                setRotationZ(obj.getRotationZ());
                return (*this);
            }

            void Image::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);
            }

            const string Image::getFileName() const {
                return m_fileName;
            }

            void Image::setFileName(const string &fileName) {
                m_fileName = fileName;
            }

            uint32_t Image::getOriginX() const {
                return m_originX;
            }

            void Image::setOriginX(const uint32_t &x) {
                m_originX = x;
            }

            uint32_t Image::getOriginY() const {
                return m_originY;
            }

            void Image::setOriginY(const uint32_t &y) {
                m_originY = y;
            }

            double Image::getMeterPerPixelX() const {
                return m_meterPerPixelX;
            }

            void Image::setMeterPerPixelX(const double &mppX) {
                m_meterPerPixelX = mppX;
            }

            double Image::getMeterPerPixelY() const {
                return m_meterPerPixelY;
            }

            void Image::setMeterPerPixelY(const double &mppY) {
                m_meterPerPixelY = mppY;
            }

            double Image::getRotationZ() const {
                return m_rotationZ;
            }

            void Image::setRotationZ(const double &rotZ) {
                m_rotationZ = rotZ;
            }

            int32_t Image::getID() const {
                return 842;
            }

            const string Image::getShortName() const {
                return "Image";
            }

            const string Image::getLongName() const {
                return "hesperia.data.scenario.Image";
            }

            const string Image::toString() const {
                stringstream s;
                s << "Filename: '" << m_fileName << "', (0; 0) @ (" << m_originX << "; " << m_originY << "), Resolution: (" << m_meterPerPixelX << "; " << m_meterPerPixelY << "), Rotation: " << m_rotationZ;
                return s.str();
            }

            ostream& Image::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_fileName);

                s->write(2, m_originX);

                s->write(3, m_originY);

                s->write(4, m_meterPerPixelX);

                s->write(5, m_meterPerPixelY);

                s->write(6, m_rotationZ);

                return out;
            }

            istream& Image::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_fileName);

                d->read(2, m_originX);

                d->read(3, m_originY);

                d->read(4, m_meterPerPixelX);

                d->read(5, m_meterPerPixelY);

                d->read(6, m_rotationZ);

                return in;
            }

        }
    }
} // opendlv::data::scenario
