/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include <algorithm>
#include <iostream>
#include <sstream>

#include "core/base/module/AbstractCIDModule.h"
#include "core/wrapper/WIN32/WIN32SharedMemory.h"

namespace core {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32SharedMemory::WIN32SharedMemory(const string &name, const uint32_t &size) :
                    m_name(name),
                    m_internalName(name),
                    m_shmID(0),
                    m_mutexSharedMemory(NULL),
                    m_sharedMemory(NULL),
                    m_size(size) {

                if (m_name.size() > 0) {
                    // FreeBSD requires that the semaphore must start with / and does not contain any furhter /'s.
                    replace(m_internalName.begin(), m_internalName.end(), '/', '_'); // Replace all / by _
                    m_internalName.insert(0, "/");

                    const LONG SEM_INITIAL_COUNT = 1;
                    const LONG SEM_MAX_COUNT = 1;
                    const DWORD FLAGS = 0; // Must be 0 as this flag is currently reserved.
                    m_mutexSharedMemory = CreateSemaphoreEx(NULL, SEM_INITIAL_COUNT, SEM_MAX_COUNT, m_internalName.c_str(), FLAGS, SEMAPHORE_ALL_ACCESS);
                    if (m_mutexSharedMemory == NULL) {
                        const int retcode = GetLastError();
                        CLOG3 << "Semaphore could not be created: " << retcode << endl;
                        CloseHandle(m_mutexSharedMemory);
                        m_mutexSharedMemory = NULL;
                    }
                    else {
                        // Create the shared memory segment with this name.
                        const uint32_t hash = getCRC32(m_internalName);
                        stringstream sstr;
                        sstr << "" << hash;
                        const string &s = sstr.str();
                        
                        m_shmID = CreateFileMapping(
                            INVALID_HANDLE_VALUE,    // use paging file
                            NULL,                    // default security
                            PAGE_READWRITE,          // read/write access
                            0,                       // maximum object size (high-order DWORD)
                            size + sizeof(uint32_t), // maximum object size (low-order DWORD)
                            s.c_str());              // name of mapping object
                        if (m_shmID == NULL) {
                            const int retcode = GetLastError();
                            CLOG3 << "Shared memory could not be requested: " << retcode << endl;
                            CloseHandle(m_mutexSharedMemory);
                            m_mutexSharedMemory = NULL;
                        }
                        else {
                            // Attach to virtual memory.
                            m_sharedMemory = MapViewOfFile(m_shmID, // handle to map object
                                                           FILE_MAP_ALL_ACCESS, // read/write permission
                                                           0,       // offset (high-order DWORD)
                                                           0,       // offset (low-order DWORD)
                                                           size + sizeof(uint32_t));
                            if (m_sharedMemory == NULL) {
                                const int retcode = GetLastError();
                                CLOG3 << "Could not map view of file: " << retcode << endl;

                                CloseHandle(m_shmID);
                                m_sharedMemory = NULL;

                                CloseHandle(m_mutexSharedMemory);
                                m_mutexSharedMemory = NULL;
                            }
                            else {
                                // Store its size to the beginning of the shared memory
                                *(uint32_t *)m_sharedMemory = m_size;
                            }
                        }
                    }
                }
            }

            WIN32SharedMemory::WIN32SharedMemory(const string &name) :
                    m_name(name),
                    m_internalName(name),
                    m_shmID(0),
                    m_mutexSharedMemory(NULL),
                    m_sharedMemory(NULL),
                    m_size(0) {

                if (m_name.size() > 0) {
                    // FreeBSD requires that the semaphore must start with / and does not contain any furhter /'s.
                    replace(m_internalName.begin(), m_internalName.end(), '/', '_'); // Replace all / by _
                    m_internalName.insert(0, "/");

                    const BOOL INHERIT_HANDLE = FALSE;
                    m_mutexSharedMemory = OpenSemaphore(SEMAPHORE_ALL_ACCESS, INHERIT_HANDLE, m_internalName.c_str());
                    if (m_mutexSharedMemory == NULL) {
                        const int retcode = GetLastError();
                        CLOG3 << "Semaphore could not be open: " << retcode << endl;
                        CloseHandle(m_mutexSharedMemory);
                        m_mutexSharedMemory = NULL;
                    }
                    else {
                        // Create the shared memory segment with this name.
                        const uint32_t hash = getCRC32(m_internalName);
                        stringstream sstr;
                        sstr << "" << hash;
                        const string &s = sstr.str();

                        m_shmID = OpenFileMapping(FILE_MAP_ALL_ACCESS, // read/write access
                                                  FALSE,               // do not inherit the name
                                                  s.c_str());             // name of mapping object
                        if (m_shmID == NULL) {
                            const int retcode = GetLastError();
                            CLOG3 << "Shared memory could not be opened: " << retcode << endl;
                            CloseHandle(m_mutexSharedMemory);
                            m_mutexSharedMemory = NULL;
                        }
                        else {
                            // Attach to shared memory temporarily to read the buffer size.
                            m_sharedMemory = MapViewOfFile(m_shmID,             // handle to map object
                                                           FILE_MAP_ALL_ACCESS, // read/write permission
                                                           0,
                                                           0,
                                                           sizeof(uint32_t));
                            if (m_sharedMemory == NULL) {
                                const int retcode = GetLastError();
                                CLOG3 << "Could not map view of file: " << retcode << endl;

                                CloseHandle(m_shmID);
                                m_sharedMemory = NULL;

                                CloseHandle(m_mutexSharedMemory);
                                m_mutexSharedMemory = NULL;
                            }
                            else {
                                //  Try to read its entire size
                                m_size = *(uint32_t *)m_sharedMemory;

                                // Unmap the file and re-open it with the entire size.
                                UnmapViewOfFile(m_sharedMemory);
                                m_sharedMemory = NULL;

                                // Attach to shared memory finally.
                                m_sharedMemory = MapViewOfFile(m_shmID,             // handle to map object
                                                               FILE_MAP_ALL_ACCESS, // read/write permission
                                                               0,
                                                               0,
                                                               m_size + sizeof(uint32_t));
                                if (m_sharedMemory == NULL) {
                                    const int retcode = GetLastError();
                                    CLOG3 << "Could not map view of file: " << retcode << endl;

                                    CloseHandle(m_shmID);
                                    m_sharedMemory = NULL;

                                    CloseHandle(m_mutexSharedMemory);
                                    m_mutexSharedMemory = NULL;
                                }
                            }
                        }
                    }
                }
            }

            WIN32SharedMemory::~WIN32SharedMemory() {
                // Firstly, release the interprocess semaphore.
                if (m_mutexSharedMemory != NULL) {
                    unlock();

                    // Close semaphore (applies to the process that creates the semaphore AND to the process that just opens it).
                    CloseHandle(m_mutexSharedMemory);
                }
                m_mutexSharedMemory = NULL;

                // Secondly, unmap the shared memory segment.
                if (m_sharedMemory != NULL) {
                    UnmapViewOfFile(m_sharedMemory);
                }
                m_sharedMemory = NULL;

                // Thirdly, release the shared memory handle.
                if (m_shmID != NULL) {
                    CloseHandle(m_shmID);
                }
                m_shmID = NULL;
            }

            bool WIN32SharedMemory::isValid() const {
                return ((m_mutexSharedMemory != NULL) && (m_sharedMemory != NULL));
            }

            const string WIN32SharedMemory::getName() const {
                return m_name;
            }

            void WIN32SharedMemory::lock() {
                WaitForSingleObject(m_mutexSharedMemory, INFINITE);
            }

            void WIN32SharedMemory::unlock() {
                const LONG RELEASE_COUNT = 1;
                ReleaseSemaphore(m_mutexSharedMemory, RELEASE_COUNT, 0);
            }

            void* WIN32SharedMemory::getSharedMemory() const {
                // Adjust the address of the shared memory's beginning.
                return static_cast<void*>(static_cast<char*>(m_sharedMemory) + sizeof(uint32_t));
            }

            uint32_t WIN32SharedMemory::getSize() const {
                return m_size;
            }

            uint32_t WIN32SharedMemory::getCRC32(const string &s) const {
                // The CRC32 polynomial.
                const uint32_t CRC32POLYNOMIAL = 0x04C11DB7;

                uint32_t retVal = 0;
                for (uint32_t i = 0; i < s.size(); i++) {
                    retVal = retVal ^ (s.at(i) ^ CRC32POLYNOMIAL);
                }

                return retVal;
            }

        }
    }
} // core::wrapper::WIN32Impl
