/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cstring>
#include <sstream>
#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/image/CompressedImage.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace data {
        namespace image {

            using namespace std;
            using namespace odcore::base;

            CompressedImage::CompressedImage() :
                    SerializableData(),
                    m_name(""),
                    m_width(0),
                    m_height(0),
                    m_bytesPerPixel(0),
                    m_compressedSize(0),
                    m_imageData(NULL) {}

            CompressedImage::CompressedImage(const string &name, const uint32_t &width, const uint32_t &height, const uint32_t &bpp, const uint32_t &compressedSize) :
                    SerializableData(),
                    m_name(name),
                    m_width(width),
                    m_height(height),
                    m_bytesPerPixel(bpp),
                    m_compressedSize(compressedSize),
                    m_imageData(NULL) {
                m_imageData = new uint8_t[compressedSize];
            }

            CompressedImage::~CompressedImage() {
                OPENDAVINCI_CORE_DELETE_ARRAY(m_imageData);
            }

            CompressedImage::CompressedImage(const CompressedImage &obj) :
                    SerializableData(obj),
                    m_name(obj.getName()),
                    m_width(obj.getWidth()),
                    m_height(obj.getHeight()),
                    m_bytesPerPixel(obj.getBytesPerPixel()), 
                    m_compressedSize(obj.getCompressedSize()),
                    m_imageData(NULL) {
                OPENDAVINCI_CORE_DELETE_ARRAY(m_imageData);
                m_imageData = new uint8_t[m_compressedSize];
                ::memcpy(m_imageData, obj.getRawData(), obj.getCompressedSize());
            }

            CompressedImage& CompressedImage::operator=(const CompressedImage &obj) {
                SerializableData::operator=(obj);
                setName(obj.getName());
                setWidth(obj.getWidth());
                setHeight(obj.getHeight());
                setBytesPerPixel(obj.getBytesPerPixel());
                m_compressedSize = obj.getCompressedSize();

                OPENDAVINCI_CORE_DELETE_ARRAY(m_imageData);
                m_imageData = new uint8_t[m_compressedSize];
                ::memcpy(m_imageData, obj.getRawData(), obj.getCompressedSize());

                return (*this);
            }

            const string CompressedImage::getName() const {
                return m_name;
            }

            void CompressedImage::setName(const string &name) {
                m_name = name;
            }

            uint32_t CompressedImage::getWidth() const {
                return m_width;
            }

            void CompressedImage::setWidth(const uint32_t &width) {
                m_width = width;
            }

            uint32_t CompressedImage::getHeight() const {
                return m_height;
            }

            void CompressedImage::setHeight(const uint32_t &height) {
                m_height = height;
            }

            uint32_t CompressedImage::getBytesPerPixel() const {
                return m_bytesPerPixel;
            }

            void CompressedImage::setBytesPerPixel(const uint32_t &bytesPerPixel) {
                m_bytesPerPixel = bytesPerPixel;
            }

            uint32_t CompressedImage::getSize() const {
                return getWidth() * getHeight() * getBytesPerPixel();
            }

            uint32_t CompressedImage::getCompressedSize() const {
                return m_compressedSize;
            }

            uint8_t* CompressedImage::getRawData() const {
                return m_imageData;
            }

            void CompressedImage::accept(Visitor &v) {
                v.beginVisit();
                v.visit(1,
                        "CompressedImage.name",
                        "name",
                        m_name);

                v.visit(2,
                        "CompressedImage.width",
                        "width",
                        m_width);

                v.visit(3,
                        "CompressedImage.height",
                        "height",
                        m_height);

                v.visit(4,
                        "CompressedImage.bytesPerPixel",
                        "bytesPerPixel",
                        m_bytesPerPixel);

                v.visit(5,
                        "CompressedImage.compressedSize",
                        "compressedSize",
                        m_compressedSize);

                v.visit(6,
                        "CompressedImage.imageData",
                        "imageData",
                        m_imageData, m_compressedSize);

                v.endVisit();
            }

            ostream& CompressedImage::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                std::shared_ptr<Serializer> s = sf.getSerializer(out);

                s->write(1, getName());

                s->write(2, getWidth());

                s->write(3, getHeight());

                s->write(4, getBytesPerPixel());

                s->write(5, getCompressedSize());

                s->write(6, m_imageData, m_compressedSize);

                return out;
            }

            istream& CompressedImage::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

                d->read(1, m_name);

                d->read(2, m_width);

                d->read(3, m_height);

                d->read(4, m_bytesPerPixel);

                d->read(5, m_compressedSize);

                OPENDAVINCI_CORE_DELETE_ARRAY(m_imageData);
                m_imageData = new uint8_t[m_compressedSize];

                d->read(6, m_imageData, m_compressedSize);

                return in;
            }

            int32_t CompressedImage::getID() const {
                return 16;
            }

            const string CompressedImage::getShortName() const {
                return "CompressedImage";
            }

            const string CompressedImage::getLongName() const {
                return "core.data.image.CompressedImage";
            }

            int32_t CompressedImage::ID() {
                return 16;
            }

            const string CompressedImage::ShortName() {
                return "CompressedImage";
            }

            const string CompressedImage::LongName() {
                return "core.data.image.CompressedImage";
            }

            const string CompressedImage::toString() const {
                stringstream sstr;
                sstr << "name = " << getName() << ", width = " << getWidth() << ", height = " << getHeight() << ", bytes per pixel = " << getBytesPerPixel() << ", compressed size = " << getCompressedSize();
                return sstr.str();
            }
        }
    }
} // odcore::data::image
