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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/Image.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

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

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('f', 'i', 'l', 'e', 'n', 'a', 'm', 'e') >::RESULT,
                        m_fileName);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('x') >::RESULT,
                        m_originX);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('y') >::RESULT,
                        m_originY);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', 'p', 'p', 'x') >::RESULT,
                        m_meterPerPixelX);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', 'p', 'p', 'y') >::RESULT,
                        m_meterPerPixelY);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                        m_rotationZ);

                return out;
            }

            istream& Image::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('f', 'i', 'l', 'e', 'n', 'a', 'm', 'e') >::RESULT,
                       m_fileName);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('x') >::RESULT,
                       m_originX);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('y') >::RESULT,
                       m_originY);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', 'p', 'p', 'x') >::RESULT,
                       m_meterPerPixelX);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', 'p', 'p', 'y') >::RESULT,
                       m_meterPerPixelY);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                       m_rotationZ);

                return in;
            }

        }
    }
} // hesperia::data::scenario
