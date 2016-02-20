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

#include "opendavinci/odcore/wrapper/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/odcore/wrapper/SimpleDB/SimpleDB.h"

namespace odcore {
    namespace wrapper {
        namespace SimpleDB {

            using namespace std;

            SimpleDB::SimpleDB() :
                m_mutex(NULL),
                m_entries() {
                m_mutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_mutex.get() == NULL) {
                    throw std::string("[core::wrapper::SimpleDB] Error creating mutex");
                }
            }

            SimpleDB::~SimpleDB() {
                m_entries.clear();
            }

            void SimpleDB::put(const int32_t &key, const string &value) {
                m_mutex->lock();
                    m_entries[key] = value;
                m_mutex->unlock();
            }

            const string SimpleDB::get(const int32_t &key) const {
                string retVal("");
                m_mutex->lock();
                    retVal = m_entries[key];
                m_mutex->unlock();

                return retVal;
            }

        }
    }
} // odcore::wrapper::SimpleDB
