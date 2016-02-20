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

#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/wrapper/Libraries.h"

namespace odcore {
    namespace base {

        Serializer::Serializer() {}

        Serializer::~Serializer() {}

        float Serializer::htonf(float f) {
            if (odcore::wrapper::USESYSTEMENDINANESS == odcore::wrapper::IS_BIG_ENDIAN) {
                return f;
            }
            else {
                uint8_t *buf = reinterpret_cast<uint8_t*>(&f);
                uint8_t tmp = 0;
                for(uint32_t i = 0, j = sizeof(float) - 1; i < sizeof(float) / 2; i++, j--) {
                    tmp = buf[i];
                    buf[i] = buf[j];
                    buf[j] = tmp;
                }
                return f;
            }
        }

        double Serializer::htond(double d) {
            if (odcore::wrapper::USESYSTEMENDINANESS == odcore::wrapper::IS_BIG_ENDIAN) {
                return d;
            }
            else {
                uint8_t *buf = reinterpret_cast<uint8_t*>(&d);
                uint8_t tmp = 0;
                for(uint32_t i = 0, j = sizeof(double) - 1; i < sizeof(double) / 2; i++, j--) {
                    tmp = buf[i];
                    buf[i] = buf[j];
                    buf[j] = tmp;
                }
                return d;
            }
        }

        uint64_t Serializer::__htonll(uint64_t ui) {
            if (odcore::wrapper::USESYSTEMENDINANESS == odcore::wrapper::IS_BIG_ENDIAN) {
                return ui;
            }
            else {
                return ((static_cast<uint64_t>(htonl(ui))) << 32) + htonl(ui >> 32);
            }
        }

        int64_t Serializer::__htonll(int64_t i) {
            if (odcore::wrapper::USESYSTEMENDINANESS == odcore::wrapper::IS_BIG_ENDIAN) {
                return i;
            }
            else {
                return ((static_cast<int64_t>(htonl(i))) << 32) + htonl(i >> 32);
            }
        }
    }
} // odcore::base
