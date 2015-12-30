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

#ifndef CONTAINEROBSERVER_H_
#define CONTAINEROBSERVER_H_

namespace core { namespace io { namespace conference { class ContainerListener; } } }

namespace cockpit {

    using namespace std;

    /**
     * This interface manages multiple ContainerListeners.
     */
    class ContainerObserver {
        public:
            virtual ~ContainerObserver();

            /**
             * This method adds a container listener.
             *
             * @param containerListener ContainerListener to be added.
             */
            virtual void addContainerListener(core::io::conference::ContainerListener *containerListener) = 0;

            /**
             * This method removes a container listener.
             *
             * @param containerListener ContainerListener to be removed.
             */
            virtual void removeContainerListener(core::io::conference::ContainerListener *containerListener) = 0;
    };

} // cockpit

#endif /*CONTAINEROBSERVER_H_*/
