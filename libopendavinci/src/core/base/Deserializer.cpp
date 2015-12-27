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

#include "core/base/Deserializer.h"
#include "core/wrapper/Libraries.h"

namespace core {
    namespace base {

        Deserializer::Deserializer() {}

        Deserializer::~Deserializer() {}

        float Deserializer::ntohf(float f) {
            if (core::wrapper::USESYSTEMENDINANESS == core::wrapper::IS_BIG_ENDIAN) {
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

        double Deserializer::ntohd(double d) {
            if (core::wrapper::USESYSTEMENDINANESS == core::wrapper::IS_BIG_ENDIAN) {
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

        uint64_t Deserializer::__ntohll(uint64_t ui) {
            if (core::wrapper::USESYSTEMENDINANESS == core::wrapper::IS_BIG_ENDIAN) {
                return ui;
            }
            else {
                return ((static_cast<uint64_t>(htonl(ui))) << 32) + htonl(ui >> 32);
            }
        }

        int64_t Deserializer::__ntohll(int64_t i) {
            if (core::wrapper::USESYSTEMENDINANESS == core::wrapper::IS_BIG_ENDIAN) {
                return i;
            }
            else {
                return ((static_cast<int64_t>(ntohl(i))) << 32) + ntohl(i >> 32);
            }
        }
    }
} // core::base
