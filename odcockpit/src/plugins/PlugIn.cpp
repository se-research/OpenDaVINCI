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

#include "core/base/Lock.h"

#include "plugins/PlugIn.h"

namespace cockpit {

    namespace plugins {

        using namespace std;
        using namespace core::base;

        PlugIn::PlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                m_parent(prnt),
                m_name(name),
                m_description(),
                m_kvc(kvc),
                m_containerObserverMutex(),
                m_containerObserver() {}

        PlugIn::~PlugIn() {}

        ContainerObserver* PlugIn::getContainerObserver() const {
            Lock l(m_containerObserverMutex);
            return m_containerObserver;
        }

        void PlugIn::setContainerObserver(ContainerObserver *containerObserver) {
            Lock l(m_containerObserverMutex);
            m_containerObserver = containerObserver;
        }

        const string PlugIn::getName() const {
            return m_name;
        }

        void PlugIn::setDescription(const string &description) {
          m_description = description;
        }

        const string PlugIn::getDescription() const {
          return m_description;
        }

        QWidget* PlugIn::getParentQWidget() {
            return m_parent;
        }

        const KeyValueConfiguration PlugIn::getKeyValueConfiguration() const {
            return m_kvc;
        }

    } // plugins

} // cockpit

