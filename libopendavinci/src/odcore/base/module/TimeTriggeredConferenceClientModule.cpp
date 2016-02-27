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

#include "opendavinci/odcore/base/AbstractDataStore.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/wrapper/KeyValueDatabase.h"
#include "opendavinci/odcore/wrapper/KeyValueDatabaseFactory.h"

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;

            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::io;
            using namespace odcore::exceptions;

            TimeTriggeredConferenceClientModule::TimeTriggeredConferenceClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException, NoDatabaseAvailableException) :
                AbstractConferenceClientModule(argc, argv, name),
                m_dataStoresMutex(),
                m_listOfDataStores(),
                m_mapOfListOfDataStores(),
                m_keyValueDataStore() {
                // Create an in-memory database.
                m_keyValueDataStore = std::shared_ptr<KeyValueDataStore>(new KeyValueDataStore(wrapper::KeyValueDatabaseFactory::createKeyValueDatabase()));
            }

            TimeTriggeredConferenceClientModule::~TimeTriggeredConferenceClientModule() {
                // Database will be cleaned up by std::shared_ptr.
                {
                    Lock l(m_dataStoresMutex);
                    m_listOfDataStores.clear();

                    map<int32_t, vector<AbstractDataStore*> >::iterator it = m_mapOfListOfDataStores.begin();
                    while (it != m_mapOfListOfDataStores.end()) {
                        vector<AbstractDataStore*> listOfDataStores = it->second;
                        listOfDataStores.clear();
                        ++it;
                    }
                    m_mapOfListOfDataStores.clear();
                }
            }

            void TimeTriggeredConferenceClientModule::nextContainer(Container &c) {
                // Distribute data to datastores.
                {
                    Lock l(m_dataStoresMutex);

                    vector<AbstractDataStore*>::iterator it = m_listOfDataStores.begin();
                    while (it != m_listOfDataStores.end()) {
                        AbstractDataStore *ads = (*it++);
                        if (ads != NULL) {
                            ads->add(c); // Currently waiting threads are awaken automagically.
                        }
                    }

                    vector<AbstractDataStore*> listOfDataStores = m_mapOfListOfDataStores[c.getDataType()];
                    vector<AbstractDataStore*>::iterator jt = listOfDataStores.begin();
                    while (jt != listOfDataStores.end()) {
                        AbstractDataStore *ads = (*jt++);
                        if (ads != NULL) {
                            ads->add(c); // Currently waiting threads are awaken automagically.
                        }
                    }
                }

                if (m_keyValueDataStore.get()) {
                    // Store data using a plain map.
                    m_keyValueDataStore->put(c.getDataType(), c);
                }
            }

            void TimeTriggeredConferenceClientModule::addDataStoreFor(AbstractDataStore &dataStore) {
                Lock l(m_dataStoresMutex);

                m_listOfDataStores.push_back(&dataStore);
            }

            void TimeTriggeredConferenceClientModule::addDataStoreFor(const int32_t &datatype, AbstractDataStore &dataStore) {
                Lock l(m_dataStoresMutex);

                vector<AbstractDataStore*> listOfDataStores = m_mapOfListOfDataStores[datatype];
                listOfDataStores.push_back(&dataStore);
                m_mapOfListOfDataStores[datatype] = listOfDataStores;
            }

            KeyValueDataStore& TimeTriggeredConferenceClientModule::getKeyValueDataStore() {
                return *m_keyValueDataStore;
            }

        }
    }
} // odcore::base::module
