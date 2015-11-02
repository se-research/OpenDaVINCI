/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE2_TEST20C_H
#define SUB_STRUCTURE2_TEST20C_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"

#include "generated/sub/structure/Test20b.h"

namespace sub {
	namespace structure2 {
		using namespace std;
		
		class Test20c : public core::data::SerializableData, public core::base::Visitable {
			public:
				Test20c();
		
				Test20c(
				const uint32_t &val0, 
				const sub::structure::Test20b &val1
				);
		
				virtual ~Test20c();
		
				/**
				 * Copy constructor.
				 *
				 * @param obj Reference to an object of this class.
				 */
				Test20c(const Test20c &obj);
		
				/**
				 * Assignment operator.
				 *
				 * @param obj Reference to an object of this class.
				 * @return Reference to this instance.
				 */
				Test20c& operator=(const Test20c &obj);
		
			public:
				/**
				 * @return val3.
				 */
				uint32_t getVal3() const;
				
				/**
				 * This method sets val3.
				 *
				 * @param val Value for val3.
				 */
				void setVal3(const uint32_t &val);
			public:
				/**
				 * @return val4.
				 */
				sub::structure::Test20b getVal4() const;
				
				/**
				 * This method sets val4.
				 *
				 * @param val Value for val4.
				 */
				void setVal4(const sub::structure::Test20b &val);
		
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
		
				/**
				 * This method returns the message id.
				 *
				 * @return Message id.
				 */
				virtual int32_t getID() const;
		
				/**
				 * This method returns the short message name.
				 *
				 * @return Short message name.
				 */
				virtual const string getShortName() const;
		
				/**
				 * This method returns the long message name include package/sub structure.
				 *
				 * @return Long message name.
				 */
				virtual const string getLongName() const;
		
			public:
				virtual void accept(core::base::Visitor &v);
		
				virtual ostream& operator<<(ostream &out) const;
				virtual istream& operator>>(istream &in);
		
				virtual const string toString() const;
		
			private:
				uint32_t m_val3;
			private:
				sub::structure::Test20b m_val4;
		
		};
	} // structure2
} // sub

#endif /*SUB_STRUCTURE2_TEST20C_H*/
