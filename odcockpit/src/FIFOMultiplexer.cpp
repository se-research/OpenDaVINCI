/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "core/base/DataStoreManager.h"
#include "core/base/Lock.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"

#include "FIFOMultiplexer.h"

namespace cockpit {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io::conference;

    FIFOMultiplexer::FIFOMultiplexer(DataStoreManager &dsm) :
        m_dataStoreManager(dsm),
        m_fifoMutex(),
        m_listOfContainerListeners(),
        m_fifo() {}

    FIFOMultiplexer::~FIFOMultiplexer() {
        Lock l(m_fifoMutex);
        m_listOfContainerListeners.clear();
    }

    void FIFOMultiplexer::addContainerListener(core::io::conference::ContainerListener *containerListener) {
        if (containerListener != NULL) {
            Lock l(m_fifoMutex);
            m_listOfContainerListeners.push_back(containerListener);
        }
    }

    void FIFOMultiplexer::removeContainerListener(core::io::conference::ContainerListener *containerListener) {
        if (containerListener != NULL) {
            Lock l(m_fifoMutex);
            vector<ContainerListener*>::iterator it = m_listOfContainerListeners.begin();
            while (it != m_listOfContainerListeners.end()) {
                if (*it == containerListener) {
                    break;
                }
                it++;
            }

            // Actually remove the container listener.
            if (it != m_listOfContainerListeners.end()) {
                m_listOfContainerListeners.erase(it);
            }
        }
    }

    void FIFOMultiplexer::beforeStop() {
        // Awake our thread.
        m_fifo.wakeAll();
    }

    void FIFOMultiplexer::waitForData(){
        m_fifo.waitForData();
    }

    void FIFOMultiplexer::distributeContainer(Container &c){
    	{
    	  Lock l(m_fifoMutex);
    	  vector<ContainerListener*>::iterator it = m_listOfContainerListeners.begin();
    	  while (it != m_listOfContainerListeners.end()) {
    		  ContainerListener *cl = (*it++);
    		  if (cl != NULL) {
    			 cl->nextContainer(c);
    		  }
    	  }
    	}
    }

    Container FIFOMultiplexer::leaveContainer(){
    	Container c;
    	{
    	   Lock l(m_fifoMutex);
    	   c = m_fifo.leave();
    	}
    	return c;
    }

    uint32_t FIFOMultiplexer::getFIFOSize(){
    	uint32_t size = 0;
    	{
    	   Lock l(m_fifoMutex);
    	   size = m_fifo.getSize();
    	}
    	return size;
    }

    void FIFOMultiplexer::run() {
        // Register FIFO for receiving new data.
        m_dataStoreManager.addDataStoreFor(m_fifo);

        serviceReady();
        while (isRunning()) {
        	waitForData();

            if (isRunning()) {
                // Distribute new containers.
                for (uint32_t i = 0; i < getFIFOSize(); i++) {
                	Container c = leaveContainer();
                    distributeContainer(c);
                }
            }
        }
    }

} // cockpit

