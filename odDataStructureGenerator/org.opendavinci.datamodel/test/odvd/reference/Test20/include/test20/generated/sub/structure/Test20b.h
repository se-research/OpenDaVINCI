/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE_TEST20B_H
#define SUB_STRUCTURE_TEST20B_H

#include "opendavinci/core/opendavinci.h"


#include "opendavinci/core/base/Visitable.h"
#include "opendavinci/core/data/SerializableData.h"


namespace sub {
	namespace structure {
		using namespace std;
		
		class Test20b : public core::data::SerializableData, public core::base::Visitable {
			public:
				Test20b();
		
				Test20b(
				const uint32_t &val0
				);
		
				virtual ~Test20b();
		
				/**
				 * Copy constructor.
				 *
				 * @param obj Reference to an object of this class.
				 */
				Test20b(const Test20b &obj);
		
				/**
				 * Assignment operator.
				 *
				 * @param obj Reference to an object of this class.
				 * @return Reference to this instance.
				 */
				Test20b& operator=(const Test20b &obj);
		
			public:
				/**
				 * @return val2.
				 */
				uint32_t getVal2() const;
				
				/**
				 * This method sets val2.
				 *
				 * @param val Value for val2.
				 */
				void setVal2(const uint32_t &val);
		
			public:
				/**
				 * This method returns the message id.
				 *
				 * @return Message id.
				 */
				static int32_t ID();
		
				/**
				 * This method returns the short message name.
				 *
				 * @return Short message name.
				 */
				static const string ShortName();
		
				/**
				 * This method returns the long message name include package/sub structure.
				 *
				 * @return Long message name.
				 */
				static const string LongName();
		
			public:
				virtual void accept(core::base::Visitor &v);
		
				virtual ostream& operator<<(ostream &out) const;
				virtual istream& operator>>(istream &in);
		
				virtual const string toString() const;
		
			private:
				uint32_t m_val2;
		
		};
	} // structure
} // sub

#endif /*SUB_STRUCTURE_TEST20B_H*/
