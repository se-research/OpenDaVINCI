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

#include <iostream>
#include <string>

#include "opendavinci/odcore/base/Visitor.h"
#include "opendavinci/odcore/reflection/Field.h"
#include "opendavinci/odcore/reflection/Message.h"

namespace odcore {
    namespace reflection {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::data::reflection;

        Message::Message() :
            m_fields() {}

        Message::Message(const Message &obj) : 
            Visitable(obj),
            m_fields(obj.m_fields) {}

        Message::~Message() {}

        Message& Message::operator=(const Message &obj) {
            m_fields = obj.m_fields;
            return *this;
        }

        void Message::addField(const odcore::SharedPointer<odcore::data::reflection::AbstractField> &f) {
            m_fields.push_back(f);
        }

        void Message::accept(Visitor &v) {
            vector<SharedPointer<AbstractField> >::iterator it = m_fields.begin();
            while (it != m_fields.end()) {
                switch((*it)->getFieldDataType()) {
                    case odcore::data::reflection::AbstractField::SERIALIZABLE_T:
                    {
                        // If we have a nested message, we need to delegate this Visitor to the nested type.
                        Field<Message> *f = dynamic_cast<Field<Message>*>((*it).operator->()); // Access the value of the SharedPointer from the iterator.
                        if (f != NULL) {
                            f->getValue().accept(v);
                        }
                    }
                    break;

                    case odcore::data::reflection::AbstractField::BOOL_T :
                        visitPrimitiveDataType<bool>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::UINT8_T:
                        visitPrimitiveDataType<uint8_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::INT8_T:
                        visitPrimitiveDataType<int8_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::UINT16_T:
                        visitPrimitiveDataType<uint16_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::INT16_T:
                        visitPrimitiveDataType<int16_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::UINT32_T:
                        visitPrimitiveDataType<uint32_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::INT32_T:
                        visitPrimitiveDataType<int32_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::UINT64_T:
                        visitPrimitiveDataType<uint64_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::INT64_T:
                        visitPrimitiveDataType<int64_t>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::CHAR_T:
                        visitPrimitiveDataType<char>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::UCHAR_T:
                        visitPrimitiveDataType<unsigned char>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::FLOAT_T:
                        visitPrimitiveDataType<float>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::DOUBLE_T:
                        visitPrimitiveDataType<double>(v, *it);
                    break;

                    case odcore::data::reflection::AbstractField::STRING_T:
                    {
                        // Read value.
                        string value = dynamic_cast<Field<string>*>((*it).operator->())->getValue();
                        // Visit value.
                        v.visit((*it)->getLongIdentifier(), (*it)->getShortIdentifier(),
                                (*it)->getLongName(), (*it)->getShortName(), value);
                        // Update value.
                        dynamic_cast<Field<string>*>((*it).operator->())->setValue(value);
                        (*it)->setSize(value.size());
                    }
                    break;

                    case odcore::data::reflection::AbstractField::DATA_T :
                    {
                        // Read value.
                        SharedPointer<char> value = dynamic_cast<Field<SharedPointer<char> >*>((*it).operator->())->getValue();
                        char *valuePtr = value.operator->();
                        uint32_t size = (*it)->getSize();

                        // Visit value.
                        v.visit((*it)->getLongIdentifier(), (*it)->getShortIdentifier(),
                                (*it)->getLongName(), (*it)->getShortName(), valuePtr, size);
                        // Update value is not required as we deal with a pointer to a memory.
                    }
                    break;

                    default:
                        cerr << "[core::reflection::Message] Unknown type " << (*it)->getFieldDataType() << endl;
                    break;
                }

                ++it;
            }
        }

        SharedPointer<odcore::data::reflection::AbstractField> Message::getFieldByLongIdentifierOrShortIdentifier(const uint32_t &longIdentifier, const uint8_t &shortIdentifier, bool &found) {
            bool retVal = false;

            // Try the long identifier first.
            SharedPointer<odcore::data::reflection::AbstractField> field = getFieldByLongIdentifier(longIdentifier, retVal);

            // Try the short identifier next.
            if (!retVal) field = getFieldByShortIdentifier(shortIdentifier, retVal);

            found = retVal;
            return field;
        }

        SharedPointer<odcore::data::reflection::AbstractField> Message::getFieldByLongIdentifier(const uint32_t &longIdentifier, bool &found) {
            bool retVal = false;
            SharedPointer<odcore::data::reflection::AbstractField> field;

            vector<SharedPointer<AbstractField> >::iterator it = m_fields.begin();
            while (it != m_fields.end()) {
                if ( (*it)->getLongIdentifier() == longIdentifier ) {
                    retVal = true;
                    field = (*it);
                    break;
                }
                ++it;
            }

            found = retVal;
            return field;
        }

        SharedPointer<odcore::data::reflection::AbstractField> Message::getFieldByShortIdentifier(const uint8_t &shortIdentifier, bool &found) {
            bool retVal = false;
            SharedPointer<odcore::data::reflection::AbstractField> field;

            vector<SharedPointer<AbstractField> >::iterator it = m_fields.begin();
            while (it != m_fields.end()) {
                if ( (*it)->getShortIdentifier() == shortIdentifier ) {
                    retVal = true;
                    field = (*it);
                    break;
                }
                ++it;
            }

            found = retVal;
            return field;
        }

    }
} // odcore::reflection

