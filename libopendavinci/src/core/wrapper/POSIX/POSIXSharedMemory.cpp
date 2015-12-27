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

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstring>
#include <ostream>

#include "core/macros.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/wrapper/POSIX/POSIXSharedMemory.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXSharedMemory::POSIXSharedMemory(const string &name, const uint32_t &size) :
                m_name(name),
                m_internalName(name),
                m_releaseSharedMemory(true),
                m_shmID(0),
                m_mutexSharedMemory(NULL),
                m_sharedMemory(NULL),
                m_size(size) {

                if (m_name.size() > 0) {
                    // FreeBSD requires that the semaphore must start with / and does not contain any furhter /'s.
                    replace(m_internalName.begin(), m_internalName.end(), '/', '_'); // Replace all / by _
                    m_internalName.insert(0, "/");

                    #ifdef _POSIX_NAME_MAX
                        const uint32_t MAX_NAME_LENGTH = _POSIX_NAME_MAX;
                    #else
                        const uint32_t MAX_NAME_LENGTH = 12;
                    #endif
                    if (m_internalName.length() > MAX_NAME_LENGTH) {
                        m_internalName.resize(MAX_NAME_LENGTH);
                    }

                    m_mutexSharedMemory = sem_open(m_internalName.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 1);
                    if (m_mutexSharedMemory == SEM_FAILED) {
                        CLOG3 << "[POSIXSharedMemory] Semaphore could not be created, errno: " << errno << "; " << ::strerror(errno) << endl;
                        sem_unlink(m_internalName.c_str());
                        m_mutexSharedMemory = NULL;
                    } else {
                        // Create the shared memory segment with this name.
                        const uint32_t hash = getCRC32(m_internalName);
                        m_shmID = shmget(hash, size + sizeof(uint32_t), IPC_CREAT | S_IRUSR | S_IWUSR);
                        if (m_shmID < 0) {
                            CLOG3 << "[POSIXSharedMemory] Shared memory could not be requested, errno: " << errno << "; " << ::strerror(errno) << endl;
                            sem_unlink(m_internalName.c_str());
                            m_mutexSharedMemory = NULL;
                        } else {
                            // Attach to virtual memory and store its size to the beginning of the shared memory.
                            m_sharedMemory = shmat(m_shmID, NULL, 0);
                            *static_cast<uint32_t *>(m_sharedMemory) = m_size;
                        }
                    }
                }
            }

            POSIXSharedMemory::POSIXSharedMemory(const string &name) :
                m_name(name),
                m_internalName(name),
                m_releaseSharedMemory(false),
                m_shmID(0),
                m_mutexSharedMemory(NULL),
                m_sharedMemory(NULL),
                m_size(0) {

                if (m_name.size() > 0) {
                    // FreeBSD requires that the semaphore must start with / and does not contain any furhter /'s.
                    replace(m_internalName.begin(), m_internalName.end(), '/', '_'); // Replace all / by _
                    m_internalName.insert(0, "/");

                    #ifdef _POSIX_NAME_MAX
                        const uint32_t MAX_NAME_LENGTH = _POSIX_NAME_MAX;
                    #else
                        const uint32_t MAX_NAME_LENGTH = 12;
                    #endif
                    if (m_internalName.length() > MAX_NAME_LENGTH) {
                        m_internalName.resize(MAX_NAME_LENGTH);
                    }

                    m_mutexSharedMemory = sem_open(m_internalName.c_str(), 0, S_IRUSR | S_IWUSR, 0);
                    if (m_mutexSharedMemory == SEM_FAILED) {
                        CLOG3 << "[POSIXSharedMemory] Semaphore could not be created, errno: " << errno << "; " << ::strerror(errno) << endl;
                        sem_close(m_mutexSharedMemory);
                        m_mutexSharedMemory = NULL;
                    }
                    else {
                        // Create the shared memory segment with this key.
                        const uint32_t hash = getCRC32(m_internalName);
                        m_shmID = shmget(hash, sizeof(uint32_t), S_IRUSR | S_IWUSR);
                        if (m_shmID < 0) {
                            CLOG3 << "[POSIXSharedMemory] Intermediate shared memory could not be requested." << "; " << ::strerror(errno) << endl;
                            sem_close(m_mutexSharedMemory);
                            m_mutexSharedMemory = NULL;
                        }
                        else {
                            // Attach to virtual memory and try to read its entire size.
                            m_sharedMemory = shmat(m_shmID, NULL, 0);
                            m_size = *static_cast<uint32_t *>(m_sharedMemory);

                            // Detach and try to attach to entire size.
                            shmdt(m_sharedMemory);

                            m_shmID = shmget(hash, m_size + sizeof(uint32_t), S_IRUSR | S_IWUSR);
                            if (m_shmID < 0) {
                                CLOG3 << "[POSIXSharedMemory] Final shared memory could not be requested, errno: " << errno << "; " << ::strerror(errno) << endl;
                                sem_close(m_mutexSharedMemory);
                                m_mutexSharedMemory = NULL;
                            }
                            else {
                                // Attach this segment to virtual memory.
                                m_sharedMemory = shmat(m_shmID, NULL, 0);
                            }
                        }
                    }
                }
            }

            POSIXSharedMemory::~POSIXSharedMemory() {
                if (m_releaseSharedMemory) {
                    if (m_mutexSharedMemory != NULL) {
                        sem_close(m_mutexSharedMemory);
                    }

                    // Remove semaphore.
                    sem_unlink(m_internalName.c_str());

                    // Detach shared memory.
                    shmdt(m_sharedMemory);

                    // Remove shared memory if released by other processes.
                    shmctl(m_shmID, IPC_RMID, 0);
                }
                else {
                    shmdt(m_sharedMemory);
                }
            }

            bool POSIXSharedMemory::isValid() const {
                return ((m_mutexSharedMemory != NULL) && (m_sharedMemory != NULL));
            }

            const string POSIXSharedMemory::getName() const {
                return m_name;
            }

            void POSIXSharedMemory::lock() {
                sem_wait(m_mutexSharedMemory);
            }

            void POSIXSharedMemory::unlock() {
                sem_post(m_mutexSharedMemory);
            }

            void* POSIXSharedMemory::getSharedMemory() const {
                // Adjust the address of the shared memory's beginning.
                return static_cast<void*>(static_cast<char*>(m_sharedMemory) + sizeof(uint32_t));
            }

            uint32_t POSIXSharedMemory::getSize() const {
                return m_size;
            }

            uint32_t POSIXSharedMemory::getCRC32(const string &s) const {
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
} // core::wrapper::POSIX
