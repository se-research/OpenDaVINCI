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

#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/reflection/Field.h"
#include "opendavinci/odcore/reflection/MessageToVisitableVisitor.h"

namespace odcore {
    namespace reflection {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::data::reflection;

        MessageToVisitableVisitor::MessageToVisitableVisitor(const Message &m) :
            m_message(m) {}

        MessageToVisitableVisitor::~MessageToVisitableVisitor() {}

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, Serializable &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                try {
                    Visitable &visitable = dynamic_cast<Visitable&>(v);

                    // A Serializable (i.e. a nested type) is restored from a Message that is nested within m_message.
                    // Thus, retrieve the nested message from m_message, create a new MessageToVisitableVisitor based
                    // on the nested message, and visit the Serializable v with the new MessageToVisitableVisitor.
                    odcore::reflection::Field<Message> *nestedField = dynamic_cast<odcore::reflection::Field<Message>*>(field.operator->());
                    MessageToVisitableVisitor msgToVisitableVisitor(nestedField->getValue());
                    visitable.accept(msgToVisitableVisitor);
                }
                catch (...) {
                    // Cast was unsuccessful.
                }
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<bool>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, char &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<char>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<unsigned char>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<int8_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<int16_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<uint16_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<int32_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<uint32_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<int64_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<uint64_t>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, float &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<float>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, double &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<double>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, string &v) {
            bool found = false;
            SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
            if (found) {
                visitPrimitiveDataType<string>(field, v);
            }
        }

        void MessageToVisitableVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            if ( (data != NULL) && (size > 0) ) {
                bool found = false;
                SharedPointer<odcore::data::reflection::AbstractField> field = m_message.getFieldByLongIdentifierOrShortIdentifier(longId, shortId, found);
                if (found) {
                    odcore::reflection::Field<SharedPointer<char> > *fValue = dynamic_cast<odcore::reflection::Field<SharedPointer<char> >*>(field.operator->());
                    const uint32_t fSize = fValue->getSize();
                    memcpy(data, fValue->getValue().operator->(), (size <= fSize ? size : fSize));
                }
            }
        }

    }
} // odcore::reflection

