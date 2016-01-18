/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "opendavinci/core/io/Packet.h"

namespace core {
    namespace io {

        using namespace std;

        Packet::Packet() :
            m_sender(),
            m_data() {}

        Packet::Packet(const string &s, const string &d) :
            m_sender(s),
            m_data(d) {}

        Packet::~Packet() {}

        Packet::Packet(const Packet &obj) :
            m_sender(obj.m_sender),
            m_data(obj.m_data) {}

        Packet& Packet::operator=(const Packet &obj) {
            setSender(obj.getSender());
            setData(obj.getData());

            return (*this);
        }

        const string Packet::getSender() const {
            return m_sender;
        }

        void Packet::setSender(const string &s) {
            m_sender = s;
        }

        const string Packet::getData() const {
            return m_data;
        }

        void Packet::setData(const string &d) {
            m_data = d;
        }

    }
} // core::io
