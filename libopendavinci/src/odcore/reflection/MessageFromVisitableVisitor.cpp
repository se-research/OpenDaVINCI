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

#include <cstdlib>
#include <cstring>

#include <memory>
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/reflection/Field.h"
#include "opendavinci/odcore/reflection/MessageFromVisitableVisitor.h"
#include "opendavinci/generated/odcore/data/reflection/AbstractField.h"

namespace odcore {
    namespace reflection {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::serialization;
        using namespace odcore::data::reflection;

        MessageFromVisitableVisitor::MessageFromVisitableVisitor() :
            m_message() {}

        MessageFromVisitableVisitor::~MessageFromVisitableVisitor() {}

        Message MessageFromVisitableVisitor::getMessage() {
            return m_message;
        }

        void MessageFromVisitableVisitor::beginVisit(const int32_t &id, const string &shortName, const string &longName) {
            m_message.setID(id);
            m_message.setShortName(shortName);
            m_message.setLongName(longName);
        }

        void MessageFromVisitableVisitor::endVisit() {}

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, Serializable &v) {
            try {
                // A Serializable is replaced by a generic message representation. Thus,
                // try to cast v into a Visitable and visit it using a fresh Message.
                Visitable &visitable = dynamic_cast<Visitable&>(v);
                MessageFromVisitableVisitor msgFromVisitableVisitor;
                visitable.accept(msgFromVisitableVisitor);

                // Store the generic message representation.
                Field<Message> *f = new Field<Message>(msgFromVisitableVisitor.getMessage());
                f->setFieldIdentifier(id);
                f->setLongFieldName(longName);
                f->setShortFieldName(shortName);
                f->setFieldDataType(odcore::data::reflection::AbstractField::SERIALIZABLE_T);
                m_message.addField(std::shared_ptr<AbstractField>(f));
            }
            catch (...) {
                // Cast was unsuccessful.
            }
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, bool &v) {
            Field<bool> *f = new Field<bool>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::BOOL_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, char &v) {
            Field<char> *f = new Field<char>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::CHAR_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v) {
            Field<unsigned char> *f = new Field<unsigned char>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::UCHAR_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v) {
            Field<int8_t> *f = new Field<int8_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::INT8_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v) {
            Field<int16_t> *f = new Field<int16_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::INT16_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v) {
            Field<uint16_t> *f = new Field<uint16_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::UINT16_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v) {
            Field<int32_t> *f = new Field<int32_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::INT32_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v) {
            Field<uint32_t> *f = new Field<uint32_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::UINT32_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v) {
            Field<int64_t> *f = new Field<int64_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::INT64_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v) {
            Field<uint64_t> *f = new Field<uint64_t>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::UINT64_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, float &v) {
            Field<float> *f = new Field<float>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::FLOAT_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, double &v) {
            Field<double> *f = new Field<double>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
            f->setSize(sizeof(v));
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, string &v) {
            Field<string> *f = new Field<string>(v);
            f->setFieldIdentifier(id);
            f->setLongFieldName(longName);
            f->setShortFieldName(shortName);
            f->setFieldDataType(odcore::data::reflection::AbstractField::STRING_T);
            f->setSize(v.size());
            m_message.addField(std::shared_ptr<AbstractField>(f));
        }

        void MessageFromVisitableVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            if (data != NULL) {
                // Copy the data.
                char* ptr = static_cast<char*>(malloc(size));
                memcpy(ptr, data, size);

                // Create a field.
                Field<std::shared_ptr<char> > *f = new Field<std::shared_ptr<char> >(std::shared_ptr<char>(ptr));
                f->setFieldIdentifier(id);
                f->setLongFieldName(longName);
                f->setShortFieldName(shortName);
                f->setFieldDataType(odcore::data::reflection::AbstractField::DATA_T);
                f->setSize(size);
                m_message.addField(std::shared_ptr<AbstractField>(f));
            }
        }

    }
} // odcore::reflection

