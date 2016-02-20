/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_SUBPACKAGE_TEST8C_H
#define TESTPACKAGE_SUBPACKAGE_TEST8C_H

#include "opendavinci/odcore/opendavinci.h"


#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"


namespace testpackage {
	namespace subpackage {
		using namespace std;
		
		class Test8C : public odcore::data::SerializableData, public odcore::base::Visitable {
			public:
				Test8C();
		
				Test8C(
				const std::string &val0
				);
		
				virtual ~Test8C();
		
				/**
				 * Copy constructor.
				 *
				 * @param obj Reference to an object of this class.
				 */
				Test8C(const Test8C &obj);
		
				/**
				 * Assignment operator.
				 *
				 * @param obj Reference to an object of this class.
				 * @return Reference to this instance.
				 */
				Test8C& operator=(const Test8C &obj);
		
			public:
				/**
				 * @return attribute1.
				 */
				std::string getAttribute1() const;
				
				/**
				 * This method sets attribute1.
				 *
				 * @param val Value for attribute1.
				 */
				void setAttribute1(const std::string &val);
		
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
				virtual void accept(odcore::base::Visitor &v);
		
				virtual ostream& operator<<(ostream &out) const;
				virtual istream& operator>>(istream &in);
		
				virtual const string toString() const;
		
			private:
				std::string m_attribute1;
		
		};
	} // subpackage
} // testpackage

#endif /*TESTPACKAGE_SUBPACKAGE_TEST8C_H*/
