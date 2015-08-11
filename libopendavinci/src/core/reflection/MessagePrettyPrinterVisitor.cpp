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

#include "core/base/Visitable.h"
#include "core/reflection/MessagePrettyPrinterVisitor.h"

namespace core {
    namespace reflection {

        using namespace std;
        using namespace core::base;

        MessagePrettyPrinterVisitor::MessagePrettyPrinterVisitor() :
            m_indent(0),
            m_buffer() {}

        MessagePrettyPrinterVisitor::MessagePrettyPrinterVisitor(const uint16_t &indent) :
            m_indent(indent),
            m_buffer() {}

        MessagePrettyPrinterVisitor::~MessagePrettyPrinterVisitor() {}

        void MessagePrettyPrinterVisitor::getOutput(ostream &o) {
            o << m_buffer.str();
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, Serializable &v) {
            try {
                Visitable& visitable = dynamic_cast<Visitable&>(v);
                stringstream buffer;

                // Visit Serializable using a more indented PrettyPrinter.
                MessagePrettyPrinterVisitor prettyPrinter(m_indent+1);
                visitable.accept(prettyPrinter);
                prettyPrinter.getOutput(buffer);

                for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
                m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << buffer.str() << endl;
            }
            catch(...) {}
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", v = " << v << endl;
        }

        void MessagePrettyPrinterVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            for (uint16_t i = 0; i < m_indent; i++) m_buffer << "\t";
            m_buffer << "longIdentifier = " << longId << ", shortIdentifier = " << shortId << ", longName = " << longName << ", shortName = " << shortName << ", size " << size << ", data = " << static_cast<char*>(data) << endl;
        }

    }
} // core::reflection

