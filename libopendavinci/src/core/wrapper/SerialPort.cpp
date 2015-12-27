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

// The following compiler switches are added to ignore -Weffc++ warnings in serial/serial.h.
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Weffc++"
#endif
#include <stddef.h>

#include "core/io/ConnectionListener.h"
#include "core/io/StringListener.h"
#include "core/wrapper/Mutex.h"
#include "core/wrapper/Thread.h"
    #include "serial/serial.h"
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic pop
# endif
#endif

#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/SerialPort.h"

namespace core {
    namespace wrapper {

        using namespace core::io;

        SerialPort::SerialPort(const string &port, const uint32_t &baudRate) :
            m_thread(),
            m_connectionListenerMutex(),
            m_connectionListener(NULL),
            m_stringListenerMutex(),
            m_stringListener(NULL),
            m_serial(NULL) {
            m_connectionListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_connectionListenerMutex.get() == NULL) {
                throw std::string("[core::wrapper::SerialPort] Error creating mutex for connection listener.");
            }

            m_stringListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_stringListenerMutex.get() == NULL) {
                throw std::string("[core::wrapper::SerialPort] Error creating mutex for string listener.");
            }

            m_thread = auto_ptr<Thread>(ConcurrencyFactory::createThread(*this));
            if (m_thread.get() == NULL) {
                throw std::string("[core::wrapper::SerialPort] Error creating thread.");
            }

            try {
                const uint32_t TIMEOUT_MS = 50;
                m_serial = new serial::Serial(port, baudRate, serial::Timeout::simpleTimeout(TIMEOUT_MS));
                if (m_serial == NULL) {
                    throw std::string("[core::wrapper::SerialPort] Error creating serial port.");
                }
            }
            catch(...) {
                throw std::string("[core::wrapper::SerialPort] Error creating serial port.");
            }
        }

        SerialPort::~SerialPort() {
            setConnectionListener(NULL);
            setStringListener(NULL);

            delete reinterpret_cast<serial::Serial*>(m_serial);
        }

        void SerialPort::setConnectionListener(ConnectionListener* listener) {
            m_connectionListenerMutex->lock();
                m_connectionListener = listener;
            m_connectionListenerMutex->unlock();
        }

        void SerialPort::setStringListener(StringListener* sl) {
            m_stringListenerMutex->lock();
                m_stringListener = sl;
            m_stringListenerMutex->unlock();
        }

        void SerialPort::start() {
            m_thread.get()->start();
        }

        void SerialPort::stop() {
            m_thread.get()->stop();
        }

        bool SerialPort::isRunning() {
            return m_thread.get()->isRunning();
        }

        void SerialPort::run() {
            while (m_thread.get()->isRunning()) {
                if (reinterpret_cast<serial::Serial*>(m_serial)->waitReadable()) {
                    try {
                        const uint32_t AVAILABLE = reinterpret_cast<serial::Serial*>(m_serial)->available();
                        string data;
                        reinterpret_cast<serial::Serial*>(m_serial)->read(data, AVAILABLE);

                        // Invoke the string listener for the recently received bytes.
                        receivedString(data);
                    }
                    catch(...) {
                        // In the case of an exception, invoke the connection listener.
                        invokeConnectionListener();
                    }
                }
            }
        }

        void SerialPort::send(const string& data) {
            if (data.size() > 0) {
                if (reinterpret_cast<serial::Serial*>(m_serial)->isOpen()) {
                    try {
                        reinterpret_cast<serial::Serial*>(m_serial)->write(data);
                    }
                    catch(...) {
                        // In the case of an exception, invoke the connection listener.
                        invokeConnectionListener();
                    }
                }
                else {
                    invokeConnectionListener();
                }
            }
        }

        void SerialPort::receivedString(const string &s) {
            m_stringListenerMutex->lock();
                if (m_stringListener != NULL) {
                    m_stringListener->nextString(s);
                }
            m_stringListenerMutex->unlock();
        }

         void SerialPort::invokeConnectionListener() {
            m_connectionListenerMutex->lock();
                if (m_connectionListener != NULL) {
                    m_connectionListener->handleConnectionError();
                }
            m_connectionListenerMutex->unlock();
        }

   }
}
