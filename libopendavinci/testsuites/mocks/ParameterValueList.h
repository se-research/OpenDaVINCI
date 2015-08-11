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

#ifndef MOCKS_PARAMETERVALUELIST_H
#define MOCKS_PARAMETERVALUELIST_H

#include <list>

namespace mocks {

    template <typename TYPE> class ParameterValueList
    {
        public:
            ParameterValueList() :
                m_items(),
                m_current(m_items.begin())
            {}

            void addItem(const TYPE& value) {
                m_items.push_back(value);
            }

            void prepare() {
                m_current = m_items.begin();
            }

            TYPE getCurrentItem() {
                TYPE value = *m_current;
                ++m_current;

                return value;
            }

            bool itemsAvaiable() {
                return (m_current != m_items.end());
            }

        private:
            std::list< TYPE > m_items;
            typename std::list< TYPE >::iterator m_current;
    };
}

#endif
