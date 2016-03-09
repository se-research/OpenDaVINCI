/**
 * DataStructureGenerator- IDL tool to describe exchangeable data.
 * Copyright (C) 2014 - 2016 Christian Berger
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

package org.opendavinci.generator

import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IGenerator
import org.eclipse.xtext.generator.IFileSystemAccess
import org.opendavinci.dataModel.Message
import org.opendavinci.dataModel.PackageDeclaration
import org.opendavinci.dataModel.Attribute
import java.util.HashMap

class DataModelGenerator implements IGenerator {
	
	/* This class describes an EnumDeclaration in an ODVD file. */
	static class EnumDescription {
		String m_enumName
		String m_enumNameIncludingMessageName
		String m_FQDN
		HashMap<String, String> enumerators
	}

    /* This hashmap maps the ODVD language's types to C++ types. */
 	val typeMap = newHashMap("double"-> "double",
  							 "float"-> "float",
  							 "int8"-> "int8_t",
  							 "uint8"-> "uint8_t",
  							 "int16"-> "int16_t",
  							 "uint16"-> "uint16_t",
  							 "int32"-> "int32_t",
  							 "uint32"-> "uint32_t",
  							 "int64"-> "int64_t",
  							 "uint64"-> "uint64_t",
  							 "bool"-> "bool",
  							 "char" -> "char",
  							 "string"-> "std::string"
  	)

    /* This hashmap assigns initializing values to attributes of the respective type. */
 	val initializationMap = newHashMap("double"-> "0.0",
  							 "float"-> "0",
  							 "int8"-> "0",
  							 "uint8"-> "0",
  							 "int16"-> "0",
  							 "uint16"-> "0",
  							 "int32"-> "0",
  							 "uint32"-> "0",
  							 "int64"-> "0",
  							 "uint64"-> "0",
  							 "bool"-> "false",
  							 "char"-> "'\\0'",
  							 "string"-> "\"\""
  	)

    /* This hashmap defines test values for attribues of the respective type. */
 	val testValuesMap = newHashMap("double"-> "1.0",
  							 "float"-> "2.5",
  							 "int8"-> "-3",
  							 "uint8"-> "4",
  							 "int16"-> "-300",
  							 "uint16"-> "400",
  							 "int32"-> "-3000",
  							 "uint32"-> "4000",
  							 "int64"-> "-30000",
  							 "uint64"-> "40000",
  							 "bool"-> "true",
  							 "char"-> "'c'",
  							 "string"-> "\"Hello World!\""
  	)
 
    /* This hashmap defines test values for attribues of the respective type used as a list. */
 	val testListValuesMap = newHashMap("double"-> #[1.0, 2.0, 3.0],
  							 "float"-> #[4.5, 5.5, 6.5],
  							 "int8"-> #[-3, -4, -5],
  							 "uint8"-> #[6, 7, 8],
  							 "int16"-> #[-30, -40, -50],
  							 "uint16"-> #[60, 70, 80],
  							 "int32"-> #[-300, -400, -500],
  							 "uint32"-> #[600, 700, 800],
  							 "int64"-> #[-3000, -4000, -5000],
  							 "uint64"-> #[6000, 7000, 8000],
  							 "bool"-> #[true, false],
  							 "char"-> #["'d'", "'e'", "'f'"],
  							 "string"-> #["\"Hello World!\"", "\"Hello Solar System!\"", "\"Hello Milky Way!\""]
  	)
 
    /* This method is our interface to an outside caller. */
	override void doGenerate(Resource resource, IFileSystemAccess fsa) {
		val generatedHeadersFile = resource.URI.toString().substring(resource.URI.toString().lastIndexOf("/") + 1).replaceAll(".odvd", "")
		val toplevelIncludeFolder = resource.URI.toString().substring(resource.URI.toString().lastIndexOf("/") + 1).replaceAll(".odvd", "").toLowerCase
		val pdl = resource.allContents.toIterable.filter(typeof(PackageDeclaration)).head
		for (e : resource.allContents.toIterable.filter(typeof(Message))) {
			if (pdl != null && pdl.package != null && pdl.package.length > 0) {
				val pdlToDirectory = pdl.package.replace('.','/')
				val enumDescriptions = collectEnumsFromMessage(pdl, e)
				fsa.generateFile("include/" + toplevelIncludeFolder + "/generated/" + pdlToDirectory + "/" + e.message.toString() + ".h", generateHeaderFileContent(toplevelIncludeFolder, generatedHeadersFile, pdl, e, enumDescriptions))
				fsa.generateFile("src/generated/" + pdlToDirectory + "/" + e.message.toString() + ".cpp", generateImplementationFileContent(pdl, e, toplevelIncludeFolder, "generated/" + pdlToDirectory, enumDescriptions))
				fsa.generateFile("testsuites/" + pdl.package.toString().replaceAll("\\.", "_") + "_" + e.message.toString().replaceAll("\\.", "_") + "TestSuite.h", generateTestSuiteContent(pdl, e, toplevelIncludeFolder, "generated/" + pdlToDirectory, generatedHeadersFile, enumDescriptions))
			}
			else {
				val enumDescriptions = collectEnumsFromMessage(pdl, e)
				fsa.generateFile("include/" + toplevelIncludeFolder + "/generated/" + e.message.toString() + ".h", generateHeaderFileContent(toplevelIncludeFolder, generatedHeadersFile, pdl, e, enumDescriptions))
				fsa.generateFile("src/generated/" + e.message.toString() + ".cpp", generateImplementationFileContent(pdl, e, toplevelIncludeFolder, "generated", enumDescriptions))
				fsa.generateFile("testsuites/" + e.message.toString().replaceAll("\\.", "_") + "TestSuite.h", generateTestSuiteContent(pdl, e, toplevelIncludeFolder, "generated", generatedHeadersFile, enumDescriptions))
			}
		}
	}

    /* This iterates over all defined enums in a message and stores the single enum values in EnumDescription. */
	def collectEnumsFromMessage(PackageDeclaration pdl, Message msg) {
		val enums =  new HashMap<String, EnumDescription>
		for (att : msg.attributes) {
			if (att.enumdec != null) {
				val ed = new EnumDescription
				ed.m_enumName = att.enumdec.name
				ed.m_enumNameIncludingMessageName = msg.message.substring(msg.message.lastIndexOf(".") + 1) + "." + ed.m_enumName
				ed.m_FQDN = msg.message + "." + ed.m_enumName
				if ( (pdl.package != null) && (pdl.package.length > 0) )
					ed.m_FQDN = pdl.package.toString + "." + ed.m_FQDN
				ed.enumerators = new HashMap<String, String>
				for (enumerator : att.enumdec.enumerators) {
					ed.enumerators.put(enumerator.enum_name, enumerator.enum_value)
				}
				enums.put(ed.m_enumName, ed)
			}
		}
        return enums
	}

    /* This method generates the header file content. */
	def generateHeaderFileContent(String toplevelIncludeFolder, String generatedHeadersFile, PackageDeclaration pdl, Message msg, HashMap<String, EnumDescription> enums) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

«IF pdl != null && pdl.package != null && pdl.package.length > 0 /*These lines generate the header guard using a message's name and a potential package name.*/»
#ifndef «pdl.package.replaceAll("\\.", "_").toUpperCase + "_" + msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»
#define «pdl.package.replaceAll("\\.", "_").toUpperCase + "_" + msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»
«ELSE»
#ifndef «msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»
#define «msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»
«ENDIF»

#include "opendavinci/odcore/opendavinci.h"

«var hasGeneratedVector = false /*These lines check if we have a list attribute and thus, need to include <vector>.*/»
«FOR a : msg.attributes»
	«IF !hasGeneratedVector && a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		#include <vector>
		«{hasGeneratedVector = true; ""}»
	«ENDIF»
«ENDFOR»
«var hasGeneratedMap = false /*These lines check if we have a hashmap attribute and thus, need to include <map>.*/»
«FOR a : msg.attributes»
	«IF !hasGeneratedMap && a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
		#include <map>
		«{hasGeneratedMap = true; ""}»
	«ENDIF»
«ENDFOR»

#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"

«FOR a : msg.attributes /*These lines include header files for user generated types used in other messages.*/»
	«IF a.scalar != null»
		«IF !typeMap.containsKey(a.scalar.type) && !enums.containsKey(a.scalar.type)»
			«IF a.scalar.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.scalar.type.contains("odcore::")»opendavinci/«ENDIF»«a.scalar.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.scalar.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		«IF !typeMap.containsKey(a.list.type) && !enums.containsKey(a.list.type)»
			«IF a.list.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.list.type.contains("odcore::")»opendavinci/«ENDIF»«a.list.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.list.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
		«IF !typeMap.containsKey(a.map.primaryType) && !enums.containsKey(a.map.primaryType)»
			«IF a.map.primaryType.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.map.primaryType.contains("odcore::")»opendavinci/«ENDIF»«a.map.primaryType.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.map.primaryType.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
		«IF !typeMap.containsKey(a.map.secondaryType) && !enums.containsKey(a.map.secondaryType)»
			«IF a.map.secondaryType.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.map.secondaryType.contains("odcore::")»opendavinci/«ENDIF»«a.map.secondaryType.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.map.secondaryType.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.fixedarray != null»
		«IF !typeMap.containsKey(a.fixedarray.type) && !enums.containsKey(a.fixedarray.type)»
			«IF a.fixedarray.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.fixedarray.type.contains("odcore::")»opendavinci/«ENDIF»«a.fixedarray.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.fixedarray.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
«ENDFOR»

«IF msg != null && msg.superMessage != null && msg.superMessage.length > 0 /*In the case of a message extending another message, we include GeneratedHeaders_<Filename>.h that points to all headers generated from <Filename>.*/»
	#include "«toplevelIncludeFolder»/GeneratedHeaders_«generatedHeadersFile + ".h"»"
«ENDIF»
«IF pdl != null && pdl.package != null && pdl.package.length > 0»
	«IF msg.message.split("\\.").length > 1»
	«generateNamespacesForHeader(msg, (pdl.package + "." + msg.message.substring(0, msg.message.lastIndexOf('.'))).toLowerCase().split("\\."), 0, enums)»
	«ELSE»
	«generateNamespacesForHeader(msg, pdl.package.toLowerCase().split("\\."), 0, enums)»
	«ENDIF»
«ELSE»
	«IF msg.message.split("\\.").length > 1»
	«generateNamespacesForHeader(msg, (msg.message.substring(0, msg.message.lastIndexOf('.'))).toLowerCase().split("\\."), 0, enums)»
	«ELSE»
	«generateHeaderFileContentBody(msg, enums)»
	«ENDIF»
«ENDIF»

«IF pdl != null && pdl.package != null && pdl.package.length > 0 /* These lines generate the closing header guard.*/»
#endif /*«pdl.package.replaceAll("\\.", "_").toUpperCase + "_" + msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»*/
«ELSE»
#endif /*«msg.message.replaceAll("\\.", "_").toUpperCase + "_H"»*/
«ENDIF»
'''

	/* This method generates the nested namespaces. */
	def generateNamespacesForHeader(Message msg, String[] s, int i, HashMap<String, EnumDescription> enums) '''
	«IF s.length > i /*These lines generate the namespaces recursively followed by generating the content of the header file (i.e. the class).*/»
namespace «s.get(i)» {
	«generateNamespacesForHeader(msg, s, i+1, enums)»
} // «s.get(i)»
	«ELSE»
	«generateHeaderFileContentBody(msg, enums)»
	«ENDIF»
'''	

	/* This  method generates the actual body of the header file. */
	def generateHeaderFileContentBody(Message msg, HashMap<String, EnumDescription> enums) '''
using namespace std;

class «msg.message.substring(msg.message.lastIndexOf('.') + 1) /* These lines generate the class structure and the superclass (i.e. the one from which this class is deriving or SerializableData as default. */» : «IF msg.superMessage != null && msg.superMessage.length > 0»public «msg.superMessage.replaceAll("\\.", "::")»«ELSE»public odcore::data::SerializableData, public odcore::base::Visitable«ENDIF» {
	«IF enums.size > 0 /*These lines generate the enum declarations.*/»
	«generateHeaderFileEnum(msg, enums)»
	«ENDIF»
	public:
		«msg.message.substring(msg.message.lastIndexOf('.') + 1) /* Here, we generate the constructor. */»();

		«var hasOtherThanEnumAndConstAttributes = false»
		«FOR a : msg.attributes»
			«IF (a.scalar != null) || (a.list != null) || (a.map != null) || (a.fixedarray != null) /* Check for enum or constant only classes. */»
				«{hasOtherThanEnumAndConstAttributes = true; ""}»
			«ENDIF»
		«ENDFOR»
		«IF hasOtherThanEnumAndConstAttributes»
			«msg.message.substring(msg.message.lastIndexOf('.') + 1) /* Here, we generate the copy constructor. */»(
«var counter = 0»
			«FOR a : msg.attributes»
				«IF a.scalar != null»
					const «IF typeMap.containsKey(a.scalar.type)»«typeMap.get(a.scalar.type)»«ELSE»«a.scalar.type.replaceAll("\\.", "::")»«ENDIF» &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
				«ENDIF»
				«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
					const vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
				«ENDIF»
				«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
					const map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
				«ENDIF»
				«IF a.fixedarray != null»
					const «IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF» *val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
				«ENDIF»
			«ENDFOR»
			);
		«ENDIF»

		virtual ~«msg.message.substring(msg.message.lastIndexOf('.') + 1) /* Here, we generate the destructor. */»();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		«msg.message.substring(msg.message.lastIndexOf('.') + 1)»(const «msg.message.substring(msg.message.lastIndexOf('.') + 1)» &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		«msg.message.substring(msg.message.lastIndexOf('.') + 1)»& operator=(const «msg.message.substring(msg.message.lastIndexOf('.') + 1)» &obj);

	«FOR a : msg.attributes /* Here, we iterate over the attributes to generate the getter and setter methods. */»
		«a.generateHeaderGetterSetter(enums)»
	«ENDFOR»

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
		virtual void accept(odcore::base::Visitor &v);

		virtual ostream& operator<<(ostream &out) const;
		virtual istream& operator>>(istream &in);

		virtual const string toString() const;

	«FOR a : msg.attributes /* Here, we generate the member attributes. */»
		«a.generateHeaderAttribute»
	«ENDFOR»

«var hasConstAttributes = false»
«FOR a : msg.attributes»
	«IF (a.const != null) /* Check for constant attributes. */»
		«{hasConstAttributes = true; ""}»
	«ENDIF»
«ENDFOR»
«IF hasConstAttributes»
«FOR a : msg.attributes»
	«a.generateHeaderConstants»
«ENDFOR»
«ENDIF»
};
	'''
	
	/* This method generates the enum declarations. */
	def generateHeaderFileEnum(Message msg, HashMap<String, EnumDescription> enums) '''
	«FOR e : enums.entrySet»
		public:
			enum «e.key» {
				«FOR enumerator : e.value.enumerators.entrySet»
					«enumerator.key» = «enumerator.value»,
				«ENDFOR»
			};
	«ENDFOR»
	'''

	/* This method generates the getter and setter interface. */
	def generateHeaderGetterSetter(Attribute a, HashMap<String, EnumDescription> enums) '''
		public:
			«IF a.scalar != null»
				/**
				 * @return «a.scalar.name».
				 */
				«IF typeMap.containsKey(a.scalar.type)»
				«typeMap.get(a.scalar.type)» get«a.scalar.name.toFirstUpper»() const;
				«ELSE»
					«IF enums.containsKey(a.scalar.type)»
					«enums.get(a.scalar.type).m_enumName» get«a.scalar.name.toFirstUpper»() const;
					«ELSE»
					«a.scalar.type.replaceAll("\\.", "::")» get«a.scalar.name.toFirstUpper»() const;
					«ENDIF»
				«ENDIF»
				
				/**
				 * This method sets «a.scalar.name».
				 *
				 * @param val Value for «a.scalar.name».
				 */
				«IF typeMap.containsKey(a.scalar.type)»
				void set«a.scalar.name.toFirstUpper»(const «typeMap.get(a.scalar.type)» &val);
				«ELSE»
				void set«a.scalar.name.toFirstUpper»(const «a.scalar.type.replaceAll("\\.", "::")» &val);
				«ENDIF»
			«ENDIF»
			«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
				/**
				 * @return «a.list.name».
				 */
				std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> getListOf«a.list.name.toFirstUpper»() const;

				/**
				 * This method sets «a.list.name».
				 *
				 * @param val Value for «a.list.name».
				 */
				void setListOf«a.list.name.toFirstUpper»(const std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> &val);

				/**
				 * This method clears the list of «a.list.name».
				 */
				void clear_ListOf«a.list.name.toFirstUpper»();

				/**
				 * @return the size of the list of «a.list.name».
				 */
				uint32_t getSize_ListOf«a.list.name.toFirstUpper»() const;

				/**
				 * @return true if the list of «a.list.name» is empty.
				 */
				bool isEmpty_ListOf«a.list.name.toFirstUpper»() const;

				/**
				 * This method adds an element to the end of the list of «a.list.name».
				 *
				 * @param val Value to be added to the end of the list of «a.list.name».
				 */
				void addTo_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val);

				/**
				 * This method adds an element to the beginning of the list of «a.list.name».
				 *
				 * @param val Value to be inserted to the beginning of the list of «a.list.name».
				 */
				void insertTo_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val);

				/**
				 * @return true if the list of «a.list.name» contains the element val.
				 *              If the list has a complex data type, the entries are compared using their .toString() method.
				 */
				bool contains_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val) const;

				/**
				 * @return Pair of iterators for the begin and end of the list of «a.list.name».
				 */
				std::pair<std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»>::iterator, std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»>::iterator> iteratorPair_ListOf«a.list.name.toFirstUpper»();
			«ENDIF»
			«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
				/**
				 * @return «a.map.name».
				 */
				std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> getMapOf«a.map.name.toFirstUpper»() const;

				/**
				 * This method sets «a.map.name».
				 *
				 * @param val Value for «a.map.name».
				 */
				void setMapOf«a.map.name.toFirstUpper»(const std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> &val);

				/**
				 * This method clears the map of «a.map.name».
				 */
				void clear_MapOf«a.map.name.toFirstUpper»();

				/**
				 * @return the size of the map of «a.map.name».
				 */
				uint32_t getSize_MapOf«a.map.name.toFirstUpper»() const;

				/**
				 * @return true if the map of «a.map.name» is empty.
				 */
				bool isEmpty_MapOf«a.map.name.toFirstUpper»() const;

				/**
				 * This method adds an element to the map of «a.map.name».
				 *
				 * @param key Key of the key/value pair to be added to the map of «a.map.name».
				 * @param val Value of the key/value pair to be added to the map of «a.map.name».
				 */
				void putTo_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key, const «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF» &val);

				/**
				 * @return true if the map of «a.map.name» is contains the given key.
				 */
				bool containsKey_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key) const;

				/**
				 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
				 *
				 * @param key Key for which the value should be returned from the map of «a.map.name».
				 * @return Value to given key from the map of «a.map.name» is contains the given key.
				 */
				«IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF» getValueForKey_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key);

				/**
				 * @return Pair of iterators for the begin and end of the map of «a.map.name».
				 */
				std::pair<std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»>::iterator, std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»>::iterator> iteratorPair_MapOf«a.map.name.toFirstUpper»();
			«ENDIF»
			«IF a.fixedarray != null»
				/**
				 * @return «a.fixedarray.name».
				 */
				«IF typeMap.containsKey(a.fixedarray.type)»
				«typeMap.get(a.fixedarray.type)»* get«a.fixedarray.name.toFirstUpper»();
				«ELSE»
					«IF enums.containsKey(a.fixedarray.type)»
					«enums.get(a.fixedarray.type).m_enumName»* get«a.fixedarray.name.toFirstUpper»();
					«ELSE»
					«a.fixedarray.type.replaceAll("\\.", "::")»* get«a.fixedarray.name.toFirstUpper»();
					«ENDIF»
				«ENDIF»
				
				/**
				 * This method gets the size of the fixed size array «a.fixedarray.name».
				 *
				 * @return Size of the fixed size array «a.fixedarray.name».
				 */
				uint32_t getSize_«a.fixedarray.name.toFirstUpper»() const;
			«ENDIF»
	'''

	def generateHeaderAttribute(Attribute a) '''
		private:
			«IF a.scalar != null»
				«IF typeMap.containsKey(a.scalar.type)»«typeMap.get(a.scalar.type)»«ELSE»«a.scalar.type.replaceAll("\\.", "::")»«ENDIF» m_«a.scalar.name»;
			«ENDIF»
			«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> m_listOf«a.list.name.toFirstUpper»;
			«ENDIF»
			«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> m_mapOf«a.map.name.toFirstUpper»;
			«ENDIF»
			«IF a.fixedarray != null»
				«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»* m_«a.fixedarray.name»;
			«ENDIF»
	'''

	def generateHeaderConstants(Attribute a) '''
		public:
			«IF a.const != null»
				static const «IF typeMap.containsKey(a.const.type)»«typeMap.get(a.const.type)»«ENDIF» «a.const.name.toUpperCase()»;
			«ENDIF»
	'''

	/* This method generates the implementation (.cpp). */
	def generateImplementationFileContent(PackageDeclaration pdl, Message msg, String toplevelIncludeFolder, String includeDirectoryPrefix, HashMap<String, EnumDescription> enums) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>
«var hasGeneratedAlgorithm = false»
«var hasGeneratedMacros = false»
«FOR a : msg.attributes /* If we have lists or maps we need to include the proper header files here. */»
	«IF !hasGeneratedAlgorithm && a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		#include <algorithm>
		#include <sstream>
		#include <utility>
		«{hasGeneratedAlgorithm = true; ""}»
	«ENDIF»
	«IF !hasGeneratedMacros && a.fixedarray != null && a.fixedarray.name != null && a.fixedarray.name.length > 0»
#include <cstring>
#include "opendavinci/odcore/opendavinci.h"
		«{hasGeneratedMacros = true; ""}»
	«ENDIF»
«ENDFOR»

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

«IF msg.superMessage != null && msg.superMessage.length > 0 /* If this message is a derived one, we need to include the supermessage here. */»
#include "«toplevelIncludeFolder»/«includeDirectoryPrefix + "/" + msg.superMessage.substring(0, msg.superMessage.lastIndexOf('.')).replaceAll("\\.", "/") + "/" + msg.superMessage.substring(msg.superMessage.lastIndexOf('.') + 1)».h"
«ENDIF»

«IF msg.message.split("\\.").length > 1 /* Here, we include our own header file. */»
#include "«toplevelIncludeFolder»/«includeDirectoryPrefix + "/" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "/") + "/" + msg.message.substring(msg.message.lastIndexOf('.') + 1)».h"
«ELSE»
#include "«toplevelIncludeFolder»/«includeDirectoryPrefix + "/" + msg.message.substring(msg.message.lastIndexOf('.') + 1)».h"
«ENDIF»

«IF pdl != null && pdl.package != null && pdl.package.length > 0 /* Next, we generate our namespaces. */»
	«IF msg.message.split("\\.").length > 1»
	«generateNamespacesForImplementation(pdl, msg, (pdl.package + "." + msg.message.substring(0, msg.message.lastIndexOf('.'))).toLowerCase().split("\\."), 0, enums)»
	«ELSE»
	«generateNamespacesForImplementation(pdl, msg, pdl.package.toLowerCase().split("\\."), 0, enums)»
	«ENDIF»
«ELSE»
	«IF msg.message.split("\\.").length > 1»
	«generateNamespacesForImplementation(pdl, msg, (msg.message.substring(0, msg.message.lastIndexOf('.'))).toLowerCase().split("\\."), 0, enums)»
	«ELSE»
	«generateImplementationFileContentBody(pdl, msg, enums)»
	«ENDIF»
«ENDIF»
'''

	/* This method recursively creates the namespaces. */
	def generateNamespacesForImplementation(PackageDeclaration pdl, Message msg, String[] s, int i, HashMap<String, EnumDescription> enums) '''
	«IF s.length > i»
namespace «s.get(i)» {
	«generateNamespacesForImplementation(pdl, msg, s, i+1, enums)»
} // «s.get(i)»
	«ELSE»
	«generateImplementationFileContentBody(pdl, msg, enums)»
	«ENDIF»
'''	

	/* This method finally generates the content of the CPP file. */
	def generateImplementationFileContentBody(PackageDeclaration pdl, Message msg, HashMap<String, EnumDescription> enums) '''
	using namespace std;
	using namespace odcore::base;

	«FOR a : msg.attributes /* Here, we generate the const definitions. */»
		«a.generateImplementationFileConstants(msg)»
	«ENDFOR»

	«msg.message.substring(msg.message.lastIndexOf('.') + 1)»::«msg.message.substring(msg.message.lastIndexOf('.') + 1) /* Here, we generate the default constructor. */»() :
	    «IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»()«ELSE»SerializableData(), Visitable()«ENDIF»
		«FOR a : msg.attributes»
			«a.generateAttributeInitialization»
		«ENDFOR»
	{
		«FOR a : msg.attributes»
			«IF a.fixedarray != null»
				m_«a.fixedarray.name» = new «IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»[getSize_«a.fixedarray.name.toFirstUpper»()];
				for(uint32_t i = 0; i < getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
					m_«a.fixedarray.name»[i] = «initializationMap.get(a.fixedarray.type)»;
				}
			«ENDIF»
		«ENDFOR»
	}

«var hasOtherThanEnumAndConstAttributes = false»
«FOR a : msg.attributes»
	«IF (a.scalar != null) || (a.list != null) || (a.map != null) || (a.fixedarray != null) /* Check for enum or constant only classes. */»
		«{hasOtherThanEnumAndConstAttributes = true; ""}»
	«ENDIF»
«ENDFOR»
	«IF hasOtherThanEnumAndConstAttributes /* Next, we generate a constructor that would accept parameters for all member variables. */»
	«msg.message.substring(msg.message.lastIndexOf('.') + 1)»::«msg.message.substring(msg.message.lastIndexOf('.') + 1)»(
«var counter = 0»
		«FOR a : msg.attributes»
			«IF a.scalar != null»
				const «IF typeMap.containsKey(a.scalar.type)»«typeMap.get(a.scalar.type)»«ELSE»«IF enums.containsKey(a.scalar.type)»«enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»«ELSE»«a.scalar.type.replaceAll("\\.", "::")»«ENDIF»«ENDIF» &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
			«ENDIF»
			«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
				const vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
			«ENDIF»
			«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
				const map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> &val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
			«ENDIF»
			«IF a.fixedarray != null»
				const «IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«IF enums.containsKey(a.fixedarray.type)»«enums.get(a.fixedarray.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»«ENDIF» *val«counter++»«IF counter < (msg.attributes.size - enums.size)», «ENDIF»
			«ENDIF»
		«ENDFOR»
	) :
	    «IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»()«ELSE»SerializableData(), Visitable()«ENDIF»
		«var counterParameter = 0»
		«FOR a : msg.attributes»
			«IF a.enumdec == null»«a.generateAttributeInitializationWithParameters(counterParameter++)»«ENDIF»
		«ENDFOR»
	{
		«var counterParameterBody = 0»
		«FOR a : msg.attributes»
			«IF a.scalar != null»«{counterParameterBody++; ""}»«ENDIF»
			«IF a.list != null»«{counterParameterBody++; ""}»«ENDIF»
			«IF a.map != null»«{counterParameterBody++; ""}»«ENDIF»
			«IF a.fixedarray != null»
				m_«a.fixedarray.name» = new «IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»[getSize_«a.fixedarray.name.toFirstUpper»()];
				::memcpy(m_«a.fixedarray.name», val«counterParameterBody++», getSize_«a.fixedarray.name.toFirstUpper»() * sizeof(*m_«a.fixedarray.name»));
			«ENDIF»
		«ENDFOR»
	}
	«ENDIF»

	«/* Next, we generate the copy constructor. */ msg.message.substring(msg.message.lastIndexOf('.') + 1)»::«msg.message.substring(msg.message.lastIndexOf('.') + 1)»(const «msg.message.substring(msg.message.lastIndexOf('.') + 1)» &obj) :
	    «IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»(obj)«ELSE»SerializableData(), Visitable()«ENDIF»
		«IF !msg.attributes.empty»
		«FOR a : msg.attributes»
			«a.generateAttributeCopyConstructor»
		«ENDFOR»
		«ENDIF»
	{
		«IF !hasOtherThanEnumAndConstAttributes»
		(void)obj; // Avoid unused parameter warning.
		«ENDIF»
		«FOR a : msg.attributes»
			«IF a.fixedarray != null && a.fixedarray.name != null && a.fixedarray.name.length > 0»
				m_«a.fixedarray.name» = new «IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»[getSize_«a.fixedarray.name.toFirstUpper»()];
				::memcpy(m_«a.fixedarray.name», obj.m_«a.fixedarray.name», obj.getSize_«a.fixedarray.name.toFirstUpper»() * sizeof(*m_«a.fixedarray.name»));
			«ENDIF»
		«ENDFOR»
	}
	
	«msg.message.substring(msg.message.lastIndexOf('.') + 1)»::~«msg.message.substring(msg.message.lastIndexOf('.') + 1) /* Here, we have the destructor. */»() {
		«FOR a : msg.attributes»
			«IF a.fixedarray != null»
				OPENDAVINCI_CORE_DELETE_ARRAY(m_«a.fixedarray.name»);
			«ENDIF»
		«ENDFOR»
	}

	«/* Here, we create the assignment operator. */ msg.message.substring(msg.message.lastIndexOf('.') + 1)»& «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::operator=(const «msg.message.substring(msg.message.lastIndexOf('.') + 1)» &obj) {
		«IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»::operator=(obj);«ENDIF»
		«FOR a : msg.attributes»
			«a.generateAttributeAssignmentOperator»
		«ENDFOR»
		«IF !hasOtherThanEnumAndConstAttributes»(void)obj; // Avoid unused parameter warning.«ENDIF»
		return (*this);
	}

	int32_t «/* Here, we generate the method to return the message ID. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::ID() {
		return «msg.id»;
	}

	const string «/* Here, we generate the method to return the short message name. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::ShortName() {
		return "«msg.message.substring(msg.message.lastIndexOf('.') + 1)»";
	}

	const string «/* Here, we generate the method to return the long message name. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::LongName() {
		«IF pdl != null && pdl.package != null && pdl.package.length > 0 /* Next, we generate our namespaces. */»
			return "«pdl.package + "." + msg.message»";
		«ELSE»
			return "«msg.message»";
		«ENDIF»
	}

	int32_t «/* Here, we generate the method to return the message ID. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getID() const {
		return «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::ID();
	}

	const string «/* Here, we generate the method to return the short message name. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getShortName() const {
		return «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::ShortName();
	}

	const string «/* Here, we generate the method to return the long message name. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getLongName() const {
		return «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::LongName();
	}

	«FOR a : msg.attributes /* Next, we generate all implementations for the getter and setters. */»
		«a.generateAttributeGetterSetter(msg, enums)»
	«ENDFOR»

«var hasScalarAttributes = false»
«FOR a : msg.attributes»
	«IF a.scalar != null /* Check for existence of scalar attributes. */»
		«{hasScalarAttributes = true; ""}»
	«ENDIF»
«ENDFOR»
	void «/* Here, we generate the accept() method. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		«IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»::accept(v);«ENDIF»
		«FOR a : msg.attributes»
			«a.generateVisitableAttribute(msg, enums)»
		«ENDFOR»
		v.endVisit();
	}

	const string «/* Here, we generate the toString() method. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::toString() const {
		stringstream s;

		«IF msg.superMessage != null && msg.superMessage.length > 0»s << «msg.superMessage.replaceAll("\\.", "::")»::toString() << " ";«ENDIF»

		«FOR a : msg.attributes»
			«a.generateAttributeToStringStream(enums)»
		«ENDFOR»

		return s.str();
	}

	ostream& «/* Here, we generate the serialization method. */ msg.message.substring(msg.message.lastIndexOf('.') + 1)»::operator<<(ostream &out) const {
		«IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»::operator<<(out);«ENDIF»

		«IF !msg.attributes.empty»
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);«IF !hasOtherThanEnumAndConstAttributes»(void)s; // Avoid unused variable warning.«ENDIF»

		«FOR a : msg.attributes»
			«a.generateAttributeSerialization(enums)»
		«ENDFOR»
		«ENDIF»
		return out;
	}

	istream& «/* Here, we generate the deserialization method. */msg.message.substring(msg.message.lastIndexOf('.') + 1)»::operator>>(istream &in) {
		«IF msg.superMessage != null && msg.superMessage.length > 0»«msg.superMessage.replaceAll("\\.", "::")»::operator>>(in);«ENDIF»

		«IF !msg.attributes.empty»
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);«IF !hasOtherThanEnumAndConstAttributes»(void)d; // Avoid unused variable warning.«ENDIF»

		«FOR a : msg.attributes»
			«a.generateAttributeDeserialization(enums)»
		«ENDFOR»
		«ENDIF»
		return in;
	}
	'''

	def generateImplementationFileConstants(Attribute a, Message msg) '''
		«IF a.const != null»
			const «IF typeMap.containsKey(a.const.type)»«typeMap.get(a.const.type)»«ENDIF» «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::«a.const.name.toUpperCase()» = «IF a.const.type.equalsIgnoreCase("string")»"«a.const.value»"«ELSE»«a.const.value»«ENDIF»;
		«ENDIF»
	'''

	def generateAttributeInitialization(Attribute a) '''
		«IF a.scalar != null»
			«IF a.scalar.value == null»
				«IF initializationMap.containsKey(a.scalar.type)»
					, m_«a.scalar.name»(«initializationMap.get(a.scalar.type)»)
		        «ELSE»
					, m_«a.scalar.name»()
				«ENDIF»
	        «ELSE»
				, m_«a.scalar.name»(«IF a.scalar.type.equalsIgnoreCase("string")»"«a.scalar.value»"«ELSE»«IF a.scalar.type.equalsIgnoreCase("char")»'«a.scalar.value.charAt(0)»'«ELSE»«a.scalar.value»«ENDIF»«ENDIF») // TODO: Validation if the default value is of the desired type.
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			, m_listOf«a.list.name.toFirstUpper»()
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			, m_mapOf«a.map.name.toFirstUpper»()
		«ENDIF»
		«IF a.fixedarray != null»
			, m_«a.fixedarray.name»()
		«ENDIF»
	'''

	def generateAttributeInitializationWithParameters(Attribute a, int counterParameter) '''
		«IF a.scalar != null»
			, m_«a.scalar.name»(val«counterParameter»)
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			, m_listOf«a.list.name.toFirstUpper»(val«counterParameter»)
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			, m_mapOf«a.map.name.toFirstUpper»(val«counterParameter»)
		«ENDIF»
		«IF a.fixedarray != null»
			, m_«a.fixedarray.name»() // The content from obj will be copied in the copy-constructor's body.
		«ENDIF»
	'''

	def generateAttributeCopyConstructor(Attribute a) '''
		«IF a.scalar != null»
			, m_«a.scalar.name»(obj.m_«a.scalar.name»)
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			, m_listOf«a.list.name.toFirstUpper»(obj.m_listOf«a.list.name.toFirstUpper»)
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			, m_mapOf«a.map.name.toFirstUpper»(obj.m_mapOf«a.map.name.toFirstUpper»)
		«ENDIF»
		«IF a.fixedarray != null»
			, m_«a.fixedarray.name»() // The content from obj will be copied in the copy-constructor's body.
		«ENDIF»
	'''

	def generateAttributeAssignmentOperator(Attribute a) '''
		«IF a.scalar != null»
			m_«a.scalar.name» = obj.m_«a.scalar.name»;
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			m_listOf«a.list.name.toFirstUpper» = obj.m_listOf«a.list.name.toFirstUpper»;
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			m_mapOf«a.map.name.toFirstUpper» = obj.m_mapOf«a.map.name.toFirstUpper»;
		«ENDIF»
		«IF a.fixedarray != null»
			::memcpy(m_«a.fixedarray.name», obj.m_«a.fixedarray.name», obj.getSize_«a.fixedarray.name.toFirstUpper»() * sizeof(*m_«a.fixedarray.name»));
		«ENDIF»
	'''

	def generateVisitableAttribute(Attribute a, Message msg, HashMap<String, EnumDescription> enums) '''
		«IF a.scalar != null»
			«IF typeMap.containsKey(a.scalar.type)»
				«var hasFourByteID = false»
				«IF a.scalar.fourbyteid != null»
					«{hasFourByteID = true; ""}»
				«ENDIF»
				«var hasId = false»
				«IF a.scalar.id != null»
					«{hasId = true; ""}»
				«ENDIF»
				«IF hasFourByteID && hasId»
					v.visit(«a.scalar.fourbyteid», «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
				«ENDIF»
				«IF hasFourByteID && !hasId»
					v.visit(«a.scalar.fourbyteid», 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
				«ENDIF»
				«IF !hasFourByteID && hasId»
					v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
				«ENDIF»
				«IF !hasFourByteID && !hasId»
					v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
				«ENDIF»
			«ELSE»
				«var hasFourByteID = false»
				«IF a.scalar.fourbyteid != null»
					«{hasFourByteID = true; ""}»
				«ENDIF»
				«var hasId = false»
				«IF a.scalar.id != null»
					«{hasId = true; ""}»
				«ENDIF»
				«IF hasFourByteID && hasId»
					«IF enums.containsKey(a.scalar.type)»
						int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
						v.visit(«a.scalar.fourbyteid», «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", int32t_«a.scalar.name»);
					«ELSE»
						v.visit(«a.scalar.fourbyteid», «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
				«IF hasFourByteID && !hasId»
					«IF enums.containsKey(a.scalar.type)»
						int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
						v.visit(«a.scalar.fourbyteid», 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", int32t_«a.scalar.name»);
					«ELSE»
						v.visit(«a.scalar.fourbyteid», 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
				«IF !hasFourByteID && hasId»
					«IF enums.containsKey(a.scalar.type)»
						int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
						v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", int32t_«a.scalar.name»);
					«ELSE»
						v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, «a.scalar.id», "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
				«IF !hasFourByteID && !hasId»
					«IF enums.containsKey(a.scalar.type)»
						int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
						v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", int32t_«a.scalar.name»);
					«ELSE»
						v.visit(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT, 0, "«msg.message.substring(msg.message.lastIndexOf('.') + 1)».«a.scalar.name»", "«a.scalar.name»", m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''	

	def generateAttributeGetterSetter(Attribute a, Message msg, HashMap<String, EnumDescription> enums) '''
		«IF a.scalar != null»
			«IF typeMap.containsKey(a.scalar.type)»
				«typeMap.get(a.scalar.type)» «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.scalar.name.toFirstUpper»() const {
					return m_«a.scalar.name»;
				}

				void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::set«a.scalar.name.toFirstUpper»(const «typeMap.get(a.scalar.type)» &val) {
					m_«a.scalar.name» = val;
				}
			«ELSE»
				«IF enums.containsKey(a.scalar.type)»
					«enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")» «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.scalar.name.toFirstUpper»() const {
						return m_«a.scalar.name»;
					}

					void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::set«a.scalar.name.toFirstUpper»(const «enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")» &val) {
						m_«a.scalar.name» = val;
					}
				«ELSE»
					«a.scalar.type.replaceAll("\\.", "::")» «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.scalar.name.toFirstUpper»() const {
						return m_«a.scalar.name»;
					}

					void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::set«a.scalar.name.toFirstUpper»(const «a.scalar.type.replaceAll("\\.", "::")» &val) {
						m_«a.scalar.name» = val;
					}
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getListOf«a.list.name.toFirstUpper»() const {
				return m_listOf«a.list.name.toFirstUpper»;
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::setListOf«a.list.name.toFirstUpper»(const std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»> &val) {
				m_listOf«a.list.name.toFirstUpper» = val;
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::clear_ListOf«a.list.name.toFirstUpper»() {
				m_listOf«a.list.name.toFirstUpper».clear();
			}

			uint32_t «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getSize_ListOf«a.list.name.toFirstUpper»() const {
				return m_listOf«a.list.name.toFirstUpper».size();
			}

			bool «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::isEmpty_ListOf«a.list.name.toFirstUpper»() const {
				return m_listOf«a.list.name.toFirstUpper».empty();
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::addTo_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val) {
				m_listOf«a.list.name.toFirstUpper».push_back(val);
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::insertTo_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val) {
				m_listOf«a.list.name.toFirstUpper».insert(m_listOf«a.list.name.toFirstUpper».begin(), val);
			}

			bool «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::contains_ListOf«a.list.name.toFirstUpper»(const «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» &val) const {
				«IF typeMap.containsKey(a.list.type)»
				return std::find(m_listOf«a.list.name.toFirstUpper».begin(), m_listOf«a.list.name.toFirstUpper».end(), val) != m_listOf«a.list.name.toFirstUpper».end();
				«ELSE»
				bool found = false;
				std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»>::const_iterator it = m_listOf«a.list.name.toFirstUpper».begin();
				while (it != m_listOf«a.list.name.toFirstUpper».end() && !found) {
				    found |= (*it).toString() == val.toString();
				    it++;
				}
				return found;
				«ENDIF»
			}

			std::pair<std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»>::iterator, std::vector<«IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF»>::iterator> «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::iteratorPair_ListOf«a.list.name.toFirstUpper»() {
				return std::make_pair(m_listOf«a.list.name.toFirstUpper».begin(), m_listOf«a.list.name.toFirstUpper».end());
			}
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getMapOf«a.map.name.toFirstUpper»() const {
				return m_mapOf«a.map.name.toFirstUpper»;
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::setMapOf«a.map.name.toFirstUpper»(const std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»> &val) {
				m_mapOf«a.map.name.toFirstUpper» = val;
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::clear_MapOf«a.map.name.toFirstUpper»() {
				m_mapOf«a.map.name.toFirstUpper».clear();
			}

			uint32_t «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getSize_MapOf«a.map.name.toFirstUpper»() const {
				return m_mapOf«a.map.name.toFirstUpper».size();
			}

			bool «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::isEmpty_MapOf«a.map.name.toFirstUpper»() const {
				return m_mapOf«a.map.name.toFirstUpper».empty();
			}

			void «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::putTo_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key, const «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF» &val) {
				m_mapOf«a.map.name.toFirstUpper»[key] = val;
			}

			bool «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::containsKey_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key) const {
				return (m_mapOf«a.map.name.toFirstUpper».count(key) > 0);
			}

			«IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF» «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getValueForKey_MapOf«a.map.name.toFirstUpper»(const «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» &key) {
				return m_mapOf«a.map.name.toFirstUpper»[key];
			}

			std::pair<std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»>::iterator, std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»>::iterator> «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::iteratorPair_MapOf«a.map.name.toFirstUpper»() {
				return std::make_pair(m_mapOf«a.map.name.toFirstUpper».begin(), m_mapOf«a.map.name.toFirstUpper».end());
			}
		«ENDIF»
		«IF a.fixedarray != null»
			«IF typeMap.containsKey(a.fixedarray.type)»
				«typeMap.get(a.fixedarray.type)»* «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.fixedarray.name.toFirstUpper»() {
					return m_«a.fixedarray.name»;
				}
			«ELSE»
				«IF enums.containsKey(a.fixedarray.type)»
					«enums.get(a.fixedarray.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»* «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.fixedarray.name.toFirstUpper»() {
						return m_«a.fixedarray.name»;
					}
				«ELSE»
					«a.fixedarray.type.replaceAll("\\.", "::")»* «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::get«a.fixedarray.name.toFirstUpper»() {
						return m_«a.fixedarray.name»;
					}
				«ENDIF»
			«ENDIF»

			uint32_t «msg.message.substring(msg.message.lastIndexOf('.') + 1)»::getSize_«a.fixedarray.name.toFirstUpper»() const {
				return «a.fixedarray.size»;
			}
		«ENDIF»
	'''
	
	def generateAttributeToStringStream(Attribute a, HashMap<String, EnumDescription> enums) '''
		«IF a.scalar != null»
			«IF typeMap.containsKey(a.scalar.type)»
				s << "«a.scalar.name.toFirstUpper»: " << get«a.scalar.name.toFirstUpper»() << " ";
	        «ELSE»
		        «IF enums.containsKey(a.scalar.type)»
		        	switch(get«a.scalar.name.toFirstUpper»()) {
		        		«FOR e : enums.get(a.scalar.type).enumerators.entrySet»
		        			case «e.key» :
		        			s << "«a.scalar.name.toFirstUpper»: «enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\." + enums.get(a.scalar.type).m_enumName, "")»::«e.key» («e.value») ";
		        			break;
		        		«ENDFOR»
		        	}
		        «ELSE»
					s << "«a.scalar.name.toFirstUpper»: " << get«a.scalar.name.toFirstUpper»().toString() << " ";
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			s << "Number of elements in list of «a.list.name.toFirstUpper»: " << getSize_ListOf«a.list.name.toFirstUpper»() << " ";
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			s << "Number of elements in map of «a.map.name.toFirstUpper»: " << getSize_MapOf«a.map.name.toFirstUpper»() << " ";
		«ENDIF»
		«IF a.fixedarray != null»
			s << "«a.fixedarray.name»: (";
			for(uint32_t i = 0; i < getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
				s << (m_«a.fixedarray.name»[i]) << (((i+1) < getSize_«a.fixedarray.name.toFirstUpper»()) ? ", " : "");
			}
			s << ")" << " ";
		«ENDIF»
	'''
	
	def generateCharList(String s, int i) '''
		«IF i < s.length»CharList<'«s.charAt(i)»', «generateCharList(s, i+1)»> «ELSE»NullType«ENDIF»'''
	
	def generateAttributeSerialization(Attribute a, HashMap<String, EnumDescription> enums) '''
		«IF a.scalar != null»
			«IF a.scalar.fourbyteid != null»
				«IF enums.containsKey(a.scalar.type)»
				int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
				s->write(«a.scalar.fourbyteid», int32t_«a.scalar.name»);
				«ELSE»
				s->write(«a.scalar.fourbyteid», m_«a.scalar.name»);
				«ENDIF»
			«ELSE»
				«IF a.scalar.id != null»
					«IF enums.containsKey(a.scalar.type)»
					int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
					s->write(«a.scalar.id»,
							int32t_«a.scalar.name»);
					«ELSE»
					s->write(«a.scalar.id»,
							m_«a.scalar.name»);
					«ENDIF»
				«ELSE»
					«IF enums.containsKey(a.scalar.type)»
					int32_t int32t_«a.scalar.name» = m_«a.scalar.name»;
					s->write(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT,
							int32t_«a.scalar.name»);
					«ELSE»
					s->write(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT,
							m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		// Write number of elements in m_listOf«a.list.name.toFirstUpper».
		const uint32_t numberOf«a.list.name.toFirstUpper» = static_cast<uint32_t>(m_listOf«a.list.name.toFirstUpper».size());
		«IF a.list.fourbyteid != null»
			s->write(«a.list.fourbyteid», numberOf«a.list.name.toFirstUpper»);
		«ELSE»
			«IF a.list.id != null»
				s->write(«a.list.id», numberOf«a.list.name.toFirstUpper»);
			«ELSE»
				s->write(CRC32 < «generateCharList(new String("numberOf" + a.list.name.toFirstUpper), 0)» >::RESULT,
				        numberOf«a.list.name.toFirstUpper»);
			«ENDIF»
		«ENDIF»
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOf«a.list.name.toFirstUpper»;
		for (uint32_t i = 0; i < numberOf«a.list.name.toFirstUpper»; i++) {
		    sstrOf«a.list.name.toFirstUpper» << m_listOf«a.list.name.toFirstUpper».at(i)«IF typeMap.containsKey(a.list.type) /* primitive types need to be separated by endl. */» << endl«ENDIF»;
		}
		
		// Write string of elements.
		if (numberOf«a.list.name.toFirstUpper» > 0) {
			«IF a.list.fourbyteid != null»
				s->write(«a.list.fourbyteid» + «((a.eContainer) as Message).attributes.size», sstrOf«a.list.name.toFirstUpper».str());
			«ELSE»
				«IF a.list.id != null»
					s->write(«a.list.id» + «((a.eContainer) as Message).attributes.size»,
					        sstrOf«a.list.name.toFirstUpper».str());
				«ELSE»
					s->write(CRC32 < «generateCharList(a.list.name.toFirstUpper, 0)» >::RESULT,
					        sstrOf«a.list.name.toFirstUpper».str());
				«ENDIF»
			«ENDIF»
		}
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
		{
			// Write number of elements in m_mapOf«a.map.name.toFirstUpper».
			const uint32_t numberOf«a.map.name.toFirstUpper» = static_cast<uint32_t>(m_mapOf«a.map.name.toFirstUpper».size());
			«IF a.map.fourbyteid != null»
				s->write(«a.map.fourbyteid», numberOf«a.map.name.toFirstUpper»);
			«ELSE»
				«IF a.map.id != null»
					s->write(«a.map.id», numberOf«a.map.name.toFirstUpper»);
				«ELSE»
					s->write(CRC32 < «generateCharList(new String("numberOf" + a.map.name.toFirstUpper), 0)» >::RESULT,
					        numberOf«a.map.name.toFirstUpper»);
				«ENDIF»
			«ENDIF»

			// Write actual elements into a stringstream.
			std::stringstream sstrOf«a.map.name.toFirstUpper»;
			std::map<«IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF», «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF»>::const_iterator it = m_mapOf«a.map.name.toFirstUpper».begin();
			while (it != m_mapOf«a.map.name.toFirstUpper».end()) {
			    sstrOf«a.map.name.toFirstUpper» << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOf«a.map.name.toFirstUpper» > 0) {
				«IF a.map.fourbyteid != null»
					s->write(«a.map.fourbyteid» + «((a.eContainer) as Message).attributes.size», sstrOf«a.map.name.toFirstUpper».str());
				«ELSE»
					«IF a.map.id != null»
						s->write(«a.map.id» + «((a.eContainer) as Message).attributes.size»,
								sstrOf«a.map.name.toFirstUpper».str());
					«ELSE»
						s->write(CRC32 < «generateCharList(a.map.name.toFirstUpper, 0)» >::RESULT,
								sstrOf«a.map.name.toFirstUpper».str());
					«ENDIF»
				«ENDIF»
			}
		}
		«ENDIF»
		«IF a.fixedarray != null»
			«IF a.fixedarray.fourbyteid != null»
				s->write(«a.fixedarray.fourbyteid», m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
			«ELSE»
				«IF a.fixedarray.id != null»
					s->write(«a.fixedarray.id»,
							m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
				«ELSE»
					s->write(CRC32 < «generateCharList(a.fixedarray.name, 0)» >::RESULT,
							m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''
	
	def generateAttributeDeserialization(Attribute a, HashMap<String, EnumDescription> enums) '''
		«IF a.scalar != null»
			«IF a.scalar.fourbyteid != null»
				«IF enums.containsKey(a.scalar.type)»
				int32_t int32t_«a.scalar.name» = 0;
				d->read(«a.scalar.fourbyteid», int32t_«a.scalar.name»);
				m_«a.scalar.name» = static_cast<«enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»>(int32t_«a.scalar.name»);
				«ELSE»
				d->read(«a.scalar.fourbyteid», m_«a.scalar.name»);
				«ENDIF»
			«ELSE»
				«IF a.scalar.id != null»
					«IF enums.containsKey(a.scalar.type)»
					int32_t int32t_«a.scalar.name» = 0;
					d->read(«a.scalar.id»,
							int32t_«a.scalar.name»);
					m_«a.scalar.name» = static_cast<«enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»>(int32t_«a.scalar.name»);
					«ELSE»
					d->read(«a.scalar.id»,
							m_«a.scalar.name»);
					«ENDIF»
				«ELSE»
					«IF enums.containsKey(a.scalar.type)»
					int32_t int32t_«a.scalar.name» = 0;
					d->read(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT,
							int32t_«a.scalar.name»);
					m_«a.scalar.name» = static_cast<«enums.get(a.scalar.type).m_enumNameIncludingMessageName.replaceAll("\\.", "::")»>(int32t_«a.scalar.name»);
					«ELSE»
					d->read(CRC32 < «generateCharList(a.scalar.name, 0)» >::RESULT,
							m_«a.scalar.name»);
					«ENDIF»
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		// Clean up the existing list of «a.list.name.toFirstUpper».
		m_listOf«a.list.name.toFirstUpper».clear();
		
		// Read number of elements in m_listOf«a.list.name.toFirstUpper».
		uint32_t numberOf«a.list.name.toFirstUpper» = 0;
		«IF a.list.fourbyteid != null»
			d->read(«a.list.fourbyteid», numberOf«a.list.name.toFirstUpper»);
		«ELSE»
			«IF a.list.id != null»
				d->read(«a.list.id»,
				       numberOf«a.list.name.toFirstUpper»);
			«ELSE»
				d->read(CRC32 < «generateCharList(new String("numberOf" + a.list.name.toFirstUpper), 0)» >::RESULT,
				       numberOf«a.list.name.toFirstUpper»);
			«ENDIF»
		«ENDIF»
		
		if (numberOf«a.list.name.toFirstUpper» > 0) {
		    // Read string of elements.
		    string elements;
			«IF a.list.fourbyteid != null»
				d->read(«a.list.fourbyteid» + «((a.eContainer) as Message).attributes.size», elements);
			«ELSE»
				«IF a.list.id != null»
					d->read(«a.list.id» + «((a.eContainer) as Message).attributes.size»,
					   elements);
				«ELSE»
					d->read(CRC32 < «generateCharList(a.list.name.toFirstUpper, 0)» >::RESULT,
					   elements);
				«ENDIF»
			«ENDIF»
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOf«a.list.name.toFirstUpper»; i++) {
		        «IF typeMap.containsKey(a.list.type)»«typeMap.get(a.list.type)»«ELSE»«a.list.type.replaceAll("\\.", "::")»«ENDIF» element;
		        «IF a.list.type.equalsIgnoreCase("string")»getline(sstr, element);«ELSE»sstr >> element;«ENDIF»
		        m_listOf«a.list.name.toFirstUpper».push_back(element);
		    }
		}
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
		// Clean up the existing map of «a.map.name.toFirstUpper».
		m_mapOf«a.map.name.toFirstUpper».clear();
		
		// Read number of elements in m_mapOf«a.map.name.toFirstUpper».
		uint32_t numberOf«a.map.name.toFirstUpper» = 0;
		«IF a.map.fourbyteid != null»
			d->read(«a.map.fourbyteid», numberOf«a.map.name.toFirstUpper»);
		«ELSE»
			«IF a.map.id != null»
				d->read(«a.map.id», numberOf«a.map.name.toFirstUpper»);
			«ELSE»
				d->read(CRC32 < «generateCharList(new String("numberOf" + a.map.name.toFirstUpper), 0)» >::RESULT,
					   numberOf«a.map.name.toFirstUpper»);
			«ENDIF»
		«ENDIF»
		
		if (numberOf«a.map.name.toFirstUpper» > 0) {
		    // Read string of elements.
		    string elements;
			«IF a.map.fourbyteid != null»
				d->read(«a.map.fourbyteid» + «((a.eContainer) as Message).attributes.size», elements);
			«ELSE»
				«IF a.map.id != null»
					d->read(«a.map.id» + «((a.eContainer) as Message).attributes.size»,
							elements);
				«ELSE»
					d->read(CRC32 < «generateCharList(a.map.name.toFirstUpper, 0)» >::RESULT,
					       elements);
				«ENDIF»
			«ENDIF»

			stringstream sstr(elements);

			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);

			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");

			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();

			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }

			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);

			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }

			    stringstream sstrKey(key);
			    «IF typeMap.containsKey(a.map.primaryType)»«typeMap.get(a.map.primaryType)»«ELSE»«a.map.primaryType.replaceAll("\\.", "::")»«ENDIF» _key;
		        «IF a.map.primaryType.equalsIgnoreCase("string")»getline(sstrKey, _key);«ELSE»sstrKey >> _key;«ENDIF»

			    stringstream sstrValue(value);
			    «IF typeMap.containsKey(a.map.secondaryType)»«typeMap.get(a.map.secondaryType)»«ELSE»«a.map.secondaryType.replaceAll("\\.", "::")»«ENDIF» _value;
		        «IF a.map.secondaryType.equalsIgnoreCase("string")»getline(sstrValue, _value);«ELSE»sstrValue >> _value;«ENDIF»

				// Store key/value pair.
				putTo_MapOf«a.map.name.toFirstUpper»(_key, _value);
			}
		}
		«ENDIF»
		«IF a.fixedarray != null»
			«IF a.fixedarray.fourbyteid != null»
				d->read(«a.fixedarray.fourbyteid», m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
			«ELSE»
				«IF a.fixedarray.id != null»
					d->read(«a.fixedarray.id»,
					       m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
				«ELSE»
					d->read(CRC32 < «generateCharList(a.fixedarray.name, 0)» >::RESULT,
					       m_«a.fixedarray.name», getSize_«a.fixedarray.name.toFirstUpper»() * (sizeof(«IF typeMap.containsKey(a.fixedarray.type)»«typeMap.get(a.fixedarray.type)»«ELSE»«a.fixedarray.type.replaceAll("\\.", "::")»«ENDIF»)/sizeof(char)));
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''

	// Generate the test suite content (.h).
	def generateTestSuiteContent(PackageDeclaration pdl, Message msg, String toplevelIncludeFolder, String includeDirectoryPrefix, String generatedHeadersFile, HashMap<String, EnumDescription> enums) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

«IF pdl != null && pdl.package != null && pdl.package.length > 0»
#ifndef «pdl.package.replace('.', '_').toUpperCase + "_" + msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»
#define «pdl.package.replace('.', '_').toUpperCase + "_" + msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»
«ELSE»
#ifndef «msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»
#define «msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»
«ENDIF»

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "«toplevelIncludeFolder»/GeneratedHeaders_«generatedHeadersFile + ".h"»"
«IF msg.message.split("\\.").length > 1 /* Here, we include our own header file. */»
#include "«toplevelIncludeFolder»/«includeDirectoryPrefix + "/" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "/") + "/" + msg.message.substring(msg.message.lastIndexOf('.') + 1)».h"
«ELSE»
#include "«toplevelIncludeFolder»/«includeDirectoryPrefix + "/" + msg.message.substring(msg.message.lastIndexOf('.') + 1)».h"
«ENDIF»

«FOR a : msg.attributes /*These lines include header files for user generated types used in other messages.*/»
	«IF a.scalar != null»
		«IF !typeMap.containsKey(a.scalar.type) && !enums.containsKey(a.scalar.type)»
			«IF a.scalar.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.scalar.type.contains("odcore::")»opendavinci/«ENDIF»«a.scalar.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.scalar.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
		«IF !typeMap.containsKey(a.list.type) && !enums.containsKey(a.list.type)»
			«IF a.list.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.list.type.contains("odcore::")»opendavinci/«ENDIF»«a.list.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.list.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
		«IF !typeMap.containsKey(a.map.primaryType) && !enums.containsKey(a.map.primaryType)»
			«IF a.map.primaryType.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.map.primaryType.contains("odcore::")»opendavinci/«ENDIF»«a.map.primaryType.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.map.primaryType.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
		«IF !typeMap.containsKey(a.map.secondaryType) && !enums.containsKey(a.map.secondaryType)»
			«IF a.map.secondaryType.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.map.secondaryType.contains("odcore::")»opendavinci/«ENDIF»«a.map.secondaryType.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.map.secondaryType.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
	«IF a.fixedarray != null»
		«IF !typeMap.containsKey(a.fixedarray.type) && !enums.containsKey(a.fixedarray.type)»
			«IF a.fixedarray.type.contains("::") /* The type of this attribute is of type ExternalClass and thus, we have to include an external header file. */»
				#include "«IF a.fixedarray.type.contains("odcore::")»opendavinci/«ENDIF»«a.fixedarray.type.replaceAll("::", "/")».h"
			«ELSE /* Use the types only as specified by the user. */»
				#include "«toplevelIncludeFolder»/generated/«IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replaceAll('.', '/')»/«ENDIF»«a.fixedarray.type.replaceAll("\\.", "/")».h"
			«ENDIF»
		«ENDIF»
	«ENDIF»
«ENDFOR»

class «IF pdl != null && pdl.package != null && pdl.package.length > 0»«pdl.package.replace('.', '_') + "_"»«ENDIF»«msg.message.replace('.', '_') + "_TestSuite"» : public CxxTest::TestSuite {

	«generateCasesContentBody(pdl, msg)»

};

«IF pdl != null && pdl.package != null && pdl.package.length > 0»
#endif /*«pdl.package.replace('.', '_').toUpperCase + "_" + msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»*/
«ELSE»
#endif /*«msg.message.replace('.', '_').toUpperCase + "_TESTSUITE_H"»*/
«ENDIF»
'''

	def generateCasesContentBody(PackageDeclaration pdl, Message msg) '''
	public:
		void testCreateObject() {
			«IF pdl != null && pdl.package != null && pdl.package.length > 0»
				«IF msg.message.split("\\.").length > 1»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase + "::" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ELSE»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase»;
				«ENDIF»
			«ELSE»
				«IF msg.message.split("\\.").length > 1»
				using namespace «msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ENDIF»
			«ENDIF»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj1;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj1")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateAssignAttributeValueWithTestValues("obj1")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj1")»
			«ENDFOR»
		}

		void testCreateAndCopyObject() {
			«IF pdl != null && pdl.package != null && pdl.package.length > 0»
				«IF msg.message.split("\\.").length > 1»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase + "::" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ELSE»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase»;
				«ENDIF»
			«ELSE»
				«IF msg.message.split("\\.").length > 1»
				using namespace «msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ENDIF»
			«ENDIF»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj1;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj1")»
			«ENDFOR»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj2(obj1);
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithAnotherObject("obj1", "obj2")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateAssignAttributeValueWithTestValues("obj1")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj1")»
			«ENDFOR»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj3(obj1);
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithAnotherObject("obj1", "obj3")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj3")»
			«ENDFOR»

			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}

		void testCreateAndAssignObject() {
			«IF pdl != null && pdl.package != null && pdl.package.length > 0»
				«IF msg.message.split("\\.").length > 1»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase + "::" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ELSE»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase»;
				«ENDIF»
			«ELSE»
				«IF msg.message.split("\\.").length > 1»
				using namespace «msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ENDIF»
			«ENDIF»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj1;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj1")»
			«ENDFOR»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj2;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj2")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateAssignAttributeValueWithTestValues("obj1")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj1")»
			«ENDFOR»

			obj2 = obj1;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithAnotherObject("obj1", "obj2")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj2")»
			«ENDFOR»

			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

		void testCreateAndSerializeObject() {
			«IF pdl != null && pdl.package != null && pdl.package.length > 0»
				«IF msg.message.split("\\.").length > 1»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase + "::" + msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ELSE»
				using namespace «pdl.package.replaceAll("\\.", "::").toLowerCase»;
				«ENDIF»
			«ELSE»
				«IF msg.message.split("\\.").length > 1»
				using namespace «msg.message.substring(0, msg.message.lastIndexOf('.')).replaceAll("\\.", "::")»;
				«ENDIF»
			«ENDIF»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj1;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj1")»
			«ENDFOR»

			«msg.message.substring(msg.message.lastIndexOf('.') + 1)» obj2;
			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithInitializationValuesTest("obj2")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateAssignAttributeValueWithTestValues("obj1")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj1")»
			«ENDFOR»

			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithAnotherObject("obj1", "obj2")»
			«ENDFOR»

			«FOR a : msg.attributes»
				«a.generateCompareAttributeValueWithTestValuesTest("obj2")»
			«ENDFOR»

			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
'''

	def generateCompareAttributeValueWithInitializationValuesTest(Attribute a, String obj) '''
		«IF a.scalar != null»
			«IF a.scalar.value == null»
				«IF initializationMap.containsKey(a.scalar.type)»
					«IF (a.scalar.type.equalsIgnoreCase("float") || a.scalar.type.equalsIgnoreCase("double"))»
						TS_ASSERT_DELTA(«obj».get«a.scalar.name.toFirstUpper»(), «initializationMap.get(a.scalar.type)», 1e-5);
					«ENDIF»
					«IF (a.scalar.type.equalsIgnoreCase("string"))»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«obj».get«a.scalar.name.toFirstUpper»(), «initializationMap.get(a.scalar.type)»));
					«ENDIF»
					«IF (a.scalar.type.equalsIgnoreCase("bool") || a.scalar.type.equalsIgnoreCase("char") || a.scalar.type.equalsIgnoreCase("int32") || a.scalar.type.equalsIgnoreCase("uint32"))»
						TS_ASSERT(«obj».get«a.scalar.name.toFirstUpper»() == «initializationMap.get(a.scalar.type)»);
					«ENDIF»
				«ENDIF»
	        «ELSE»
				«IF (a.scalar.type.equalsIgnoreCase("float") || a.scalar.type.equalsIgnoreCase("double"))»
					TS_ASSERT_DELTA(«obj».get«a.scalar.name.toFirstUpper»(), «a.scalar.value», 1e-5);
				«ENDIF»
				«IF (a.scalar.type.equalsIgnoreCase("string"))»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«obj».get«a.scalar.name.toFirstUpper»(), "«a.scalar.value»"));
				«ENDIF»
				«IF (a.scalar.type.equalsIgnoreCase("char"))»
					TS_ASSERT(«obj».get«a.scalar.name.toFirstUpper»() == '«a.scalar.value»');
				«ENDIF»
				«IF (a.scalar.type.equalsIgnoreCase("bool") || a.scalar.type.equalsIgnoreCase("int32") || a.scalar.type.equalsIgnoreCase("uint32"))»
					TS_ASSERT(«obj».get«a.scalar.name.toFirstUpper»() == «a.scalar.value»);
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			TS_ASSERT(«obj».getListOf«a.list.name.toFirstUpper»().size() == 0);
			TS_ASSERT(«obj».getSize_ListOf«a.list.name.toFirstUpper»() == 0);
			TS_ASSERT(«obj».isEmpty_ListOf«a.list.name.toFirstUpper»());
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			TS_ASSERT(«obj».getMapOf«a.map.name.toFirstUpper»().size() == 0);
			TS_ASSERT(«obj».getSize_MapOf«a.map.name.toFirstUpper»() == 0);
			TS_ASSERT(«obj».isEmpty_MapOf«a.map.name.toFirstUpper»());
		«ENDIF»
		«IF a.fixedarray != null»
			«IF initializationMap.containsKey(a.fixedarray.type)»
				«IF (a.fixedarray.type.equalsIgnoreCase("float") || a.fixedarray.type.equalsIgnoreCase("double"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT_DELTA(«obj».get«a.fixedarray.name.toFirstUpper»()[i], «initializationMap.get(a.fixedarray.type)», 1e-5);
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("string"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«obj».get«a.fixedarray.name.toFirstUpper»()[i], «initializationMap.get(a.fixedarray.type)»));
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("bool") || a.fixedarray.type.equalsIgnoreCase("char") || a.fixedarray.type.equalsIgnoreCase("int32") || a.fixedarray.type.equalsIgnoreCase("uint32"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(«obj».get«a.fixedarray.name.toFirstUpper»()[i] == «initializationMap.get(a.fixedarray.type)»);
					}
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''

	def generateCompareAttributeValueWithTestValuesTest(Attribute a, String obj) '''
		«IF a.scalar != null»
			«IF testValuesMap.containsKey(a.scalar.type)»
				«IF (a.scalar.type.equalsIgnoreCase("float") || a.scalar.type.equalsIgnoreCase("double"))»
					TS_ASSERT_DELTA(«obj».get«a.scalar.name.toFirstUpper»(), «testValuesMap.get(a.scalar.type)», 1e-5);
				«ENDIF»
				«IF (a.scalar.type.equalsIgnoreCase("string"))»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«obj».get«a.scalar.name.toFirstUpper»(), «testValuesMap.get(a.scalar.type)»));
				«ENDIF»
				«IF (a.scalar.type.equalsIgnoreCase("bool") || a.scalar.type.equalsIgnoreCase("char") || a.scalar.type.equalsIgnoreCase("int32") || a.scalar.type.equalsIgnoreCase("uint32"))»
					TS_ASSERT(«obj».get«a.scalar.name.toFirstUpper»() == «testValuesMap.get(a.scalar.type)»);
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			«IF testListValuesMap.containsKey(a.list.type)»
				TS_ASSERT(«obj».getListOf«a.list.name.toFirstUpper»().size() == «testListValuesMap.get(a.list.type).size()»);
				TS_ASSERT(«obj».getSize_ListOf«a.list.name.toFirstUpper»() == «testListValuesMap.get(a.list.type).size()»);
				TS_ASSERT(!«obj».isEmpty_ListOf«a.list.name.toFirstUpper»());
				TS_ASSERT(«obj».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
				TS_ASSERT(«obj».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
				«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(«obj».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			«IF testListValuesMap.containsKey(a.map.primaryType) && testListValuesMap.containsKey(a.map.secondaryType)»
				TS_ASSERT(«obj».getMapOf«a.map.name.toFirstUpper»().size() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
				TS_ASSERT(«obj».getSize_MapOf«a.map.name.toFirstUpper»() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
				TS_ASSERT(!«obj».isEmpty_MapOf«a.map.name.toFirstUpper»());
				«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
					TS_ASSERT_DELTA(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)», 1e-5);
				«ELSE»
					TS_ASSERT(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)») == «testListValuesMap.get(a.map.secondaryType).get(0)»);
				«ENDIF»
				TS_ASSERT(«obj».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
				«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
					TS_ASSERT_DELTA(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)», 1e-5);
				«ELSE»
					TS_ASSERT(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)») == «testListValuesMap.get(a.map.secondaryType).get(1)»);
				«ENDIF»
				«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»
					TS_ASSERT(«obj».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»), «testListValuesMap.get(a.map.secondaryType).get(2)», 1e-5);
					«ELSE»
						TS_ASSERT(«obj».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)») == «testListValuesMap.get(a.map.secondaryType).get(2)»);
					«ENDIF»
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.fixedarray != null»
			«IF initializationMap.containsKey(a.fixedarray.type)»
				«IF (a.fixedarray.type.equalsIgnoreCase("float") || a.fixedarray.type.equalsIgnoreCase("double"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT_DELTA(«obj».get«a.fixedarray.name.toFirstUpper»()[i], «testValuesMap.get(a.fixedarray.type)» + (1.0+i), 1e-5);
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("string"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						std::stringstream sstr;
						sstr << «testValuesMap.get(a.fixedarray.type)» << "-" << i;
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«obj».get«a.fixedarray.name.toFirstUpper»()[i], sstr.str()));
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("int32") || a.fixedarray.type.equalsIgnoreCase("uint32"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(«obj».get«a.fixedarray.name.toFirstUpper»()[i] == «testValuesMap.get(a.fixedarray.type)» + i);
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("char"))»
					for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(«obj».get«a.fixedarray.name.toFirstUpper»()[i] == static_cast<char>(«testValuesMap.get(a.fixedarray.type)» + i));
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("bool"))»
					{
						bool flip = false;
						for(uint32_t i = 0; i < «obj».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
							TS_ASSERT(«obj».get«a.fixedarray.name.toFirstUpper»()[i] == flip);
							flip = !flip;
						}
					}
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''

	def generateCompareAttributeValueWithAnotherObject(Attribute a, String objA, String objB) '''
		«IF a.scalar != null»
			«IF (a.scalar.type.equalsIgnoreCase("float") || a.scalar.type.equalsIgnoreCase("double"))»
				TS_ASSERT_DELTA(«objA».get«a.scalar.name.toFirstUpper»(), «objB».get«a.scalar.name.toFirstUpper»(), 1e-5);
			«ENDIF»
			«IF (a.scalar.type.equalsIgnoreCase("string"))»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».get«a.scalar.name.toFirstUpper»(), «objB».get«a.scalar.name.toFirstUpper»()));
			«ENDIF»
			«IF (a.scalar.type.equalsIgnoreCase("bool") || a.scalar.type.equalsIgnoreCase("char") || a.scalar.type.equalsIgnoreCase("int32") || a.scalar.type.equalsIgnoreCase("uint32"))»
				TS_ASSERT(«objA».get«a.scalar.name.toFirstUpper»() == «objB».get«a.scalar.name.toFirstUpper»());
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == «objB».getSize_ListOf«a.list.name.toFirstUpper»());
			TS_ASSERT(«objA».isEmpty_ListOf«a.list.name.toFirstUpper»() == «objB».isEmpty_ListOf«a.list.name.toFirstUpper»());
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == «objB».getSize_MapOf«a.map.name.toFirstUpper»());
			TS_ASSERT(«objA».isEmpty_MapOf«a.map.name.toFirstUpper»() == «objB».isEmpty_MapOf«a.map.name.toFirstUpper»());
		«ENDIF»
		«IF a.fixedarray != null»
			TS_ASSERT(«objA».getSize_«a.fixedarray.name.toFirstUpper»() == «objB».getSize_«a.fixedarray.name.toFirstUpper»());
			«IF (a.fixedarray.type.equalsIgnoreCase("float") || a.fixedarray.type.equalsIgnoreCase("double"))»
				for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
					TS_ASSERT_DELTA(«objA».get«a.fixedarray.name.toFirstUpper»()[i], «objB».get«a.fixedarray.name.toFirstUpper»()[i], 1e-5);
				}
			«ENDIF»
			«IF (a.fixedarray.type.equalsIgnoreCase("string"))»
				for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».get«a.fixedarray.name.toFirstUpper»()[i], «objB».get«a.fixedarray.name.toFirstUpper»()[i]));
				}
			«ENDIF»
			«IF (a.fixedarray.type.equalsIgnoreCase("bool") || a.fixedarray.type.equalsIgnoreCase("char") || a.fixedarray.type.equalsIgnoreCase("int32") || a.fixedarray.type.equalsIgnoreCase("uint32"))»
				for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
					TS_ASSERT(«objA».get«a.fixedarray.name.toFirstUpper»()[i] == «objB».get«a.fixedarray.name.toFirstUpper»()[i]);
				}
			«ENDIF»
		«ENDIF»
	'''

	def generateAssignAttributeValueWithTestValues(Attribute a, String objA) '''
		«IF a.scalar != null»
			«IF testValuesMap.containsKey(a.scalar.type)»
				«objA».set«a.scalar.name.toFirstUpper»(«testValuesMap.get(a.scalar.type)»);
			«ENDIF»
		«ENDIF»
		«IF a.list != null && a.list.modifier != null && a.list.modifier.length > 0 && a.list.modifier.equalsIgnoreCase("list")»
			«IF testListValuesMap.containsKey(a.list.type)»
				{
					std::vector<«typeMap.get(a.list.type)»> myExternalList;
					myExternalList.push_back(«testListValuesMap.get(a.list.type).get(0)»);
					myExternalList.push_back(«testListValuesMap.get(a.list.type).get(1)»);
					«IF testListValuesMap.get(a.list.type).size() == 3»myExternalList.push_back(«testListValuesMap.get(a.list.type).get(2)»);«ENDIF»

					«objA».clear_ListOf«a.list.name.toFirstUpper»();
					TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == 0);
					TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == 0);
					TS_ASSERT(«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
					TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
					TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
					«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»

					«objA».setListOf«a.list.name.toFirstUpper»(myExternalList);
					TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == «testListValuesMap.get(a.list.type).size()»);
					TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == «testListValuesMap.get(a.list.type).size()»);
					TS_ASSERT(!«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
					TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
					TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
					«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»

					«objA».clear_ListOf«a.list.name.toFirstUpper»();
					TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == 0);
					TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == 0);
					TS_ASSERT(«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
					TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
					TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
					«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»
				}
				«objA».addTo_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»);
				TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == 1);
				TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == 1);
				TS_ASSERT(!«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
				TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
				TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
				«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»

				«objA».addTo_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»);
				TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == 2);
				TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == 2);
				TS_ASSERT(!«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
				TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
				TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
				«IF testListValuesMap.get(a.list.type).size() == 3»TS_ASSERT(!«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));«ENDIF»

				«IF testListValuesMap.get(a.list.type).size() == 3»
					«objA».insertTo_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»);
					TS_ASSERT(«objA».getListOf«a.list.name.toFirstUpper»().size() == 3);
					TS_ASSERT(«objA».getSize_ListOf«a.list.name.toFirstUpper»() == 3);
					TS_ASSERT(!«objA».isEmpty_ListOf«a.list.name.toFirstUpper»());
					TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(0)»));
					TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(1)»));
					TS_ASSERT(«objA».contains_ListOf«a.list.name.toFirstUpper»(«testListValuesMap.get(a.list.type).get(2)»));
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.map != null && a.map.modifier != null && a.map.modifier.length > 0 && a.map.modifier.equalsIgnoreCase("map")»
			«IF testListValuesMap.containsKey(a.map.primaryType) && testListValuesMap.containsKey(a.map.secondaryType)»
				{
					std::map<«typeMap.get(a.map.primaryType)», «typeMap.get(a.map.secondaryType)»> myExternalMap;
					myExternalMap[«testListValuesMap.get(a.map.primaryType).get(0)»] = «testListValuesMap.get(a.map.secondaryType).get(0)»;
					myExternalMap[«testListValuesMap.get(a.map.primaryType).get(1)»] = «testListValuesMap.get(a.map.secondaryType).get(1)»;
					«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»myExternalMap[«testListValuesMap.get(a.map.primaryType).get(2)»] = «testListValuesMap.get(a.map.secondaryType).get(2)»;«ENDIF»

					«objA».clear_MapOf«a.map.name.toFirstUpper»();
					TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == 0);
					TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == 0);
					TS_ASSERT(«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
					TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
					TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
					«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));«ENDIF»

					«objA».setMapOf«a.map.name.toFirstUpper»(myExternalMap);
					TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
					TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
					TS_ASSERT(!«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
					TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)», 1e-5);
					«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)»));
					«ELSE»
						TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)») == «testListValuesMap.get(a.map.secondaryType).get(0)»);
					«ENDIF»
					TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)», 1e-5);
					«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)»));
					«ELSE»
						TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)») == «testListValuesMap.get(a.map.secondaryType).get(1)»);
					«ENDIF»
					«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»
						TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));
						«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
							TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»), «testListValuesMap.get(a.map.secondaryType).get(2)», 1e-5);
						«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
							TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»), «testListValuesMap.get(a.map.secondaryType).get(2)»));
						«ELSE»
							TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)») == «testListValuesMap.get(a.map.secondaryType).get(2)»);
						«ENDIF»
					«ENDIF»

					«objA».clear_MapOf«a.map.name.toFirstUpper»();
					TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == 0);
					TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == 0);
					TS_ASSERT(«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
					TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
					TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
					«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));«ENDIF»
				}
				«objA».putTo_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)», «testListValuesMap.get(a.map.secondaryType).get(0)»);
				TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == 1);
				TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == 1);
				TS_ASSERT(!«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
				TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
				«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
					TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)», 1e-5);
				«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)»));
				«ELSE»
					TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)») == «testListValuesMap.get(a.map.secondaryType).get(0)»);
				«ENDIF»
				TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
				«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));«ENDIF»

				«objA».putTo_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)», «testListValuesMap.get(a.map.secondaryType).get(1)»);
				TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == 2);
				TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == 2);
				TS_ASSERT(!«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
				TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
				«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
					TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)», 1e-5);
				«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)»));
				«ELSE»
					TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)») == «testListValuesMap.get(a.map.secondaryType).get(0)»);
				«ENDIF»
				TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
				«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
					TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)», 1e-5);
				«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
					TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)»));
				«ELSE»
					TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)») == «testListValuesMap.get(a.map.secondaryType).get(1)»);
				«ENDIF»
				«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»TS_ASSERT(!«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));«ENDIF»

				«IF ((testListValuesMap.get(a.map.primaryType).size() == 3) && (testListValuesMap.get(a.map.secondaryType).size() == 3))»
					«objA».putTo_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)», «testListValuesMap.get(a.map.secondaryType).get(2)»);
					TS_ASSERT(«objA».getMapOf«a.map.name.toFirstUpper»().size() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
					TS_ASSERT(«objA».getSize_MapOf«a.map.name.toFirstUpper»() == «Math.min(testListValuesMap.get(a.map.primaryType).size(), testListValuesMap.get(a.map.secondaryType).size())»);
					TS_ASSERT(!«objA».isEmpty_MapOf«a.map.name.toFirstUpper»());
					TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)», 1e-5);
					«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)»), «testListValuesMap.get(a.map.secondaryType).get(0)»));
					«ELSE»
						TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(0)») == «testListValuesMap.get(a.map.secondaryType).get(0)»);
					«ENDIF»
					TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)», 1e-5);
					«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)»), «testListValuesMap.get(a.map.secondaryType).get(1)»));
					«ELSE»
						TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(1)») == «testListValuesMap.get(a.map.secondaryType).get(1)»);
					«ENDIF»
					TS_ASSERT(«objA».containsKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»));
					«IF ((a.map.secondaryType.equalsIgnoreCase("float")) || (a.map.secondaryType.equalsIgnoreCase("double")))»
						TS_ASSERT_DELTA(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»), «testListValuesMap.get(a.map.secondaryType).get(2)», 1e-5);
					«ELSEIF a.map.secondaryType.equalsIgnoreCase("string")»
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)»), «testListValuesMap.get(a.map.secondaryType).get(2)»));
					«ELSE»
						TS_ASSERT(«objA».getValueForKey_MapOf«a.map.name.toFirstUpper»(«testListValuesMap.get(a.map.primaryType).get(2)») == «testListValuesMap.get(a.map.secondaryType).get(2)»);
					«ENDIF»
				«ENDIF»
			«ENDIF»
		«ENDIF»
		«IF a.fixedarray != null»
			«IF initializationMap.containsKey(a.fixedarray.type)»
				«IF (a.fixedarray.type.equalsIgnoreCase("float") || a.fixedarray.type.equalsIgnoreCase("double"))»
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						«objA».get«a.fixedarray.name.toFirstUpper»()[i] = «testValuesMap.get(a.fixedarray.type)» + (1.0+i);
					}
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT_DELTA(«objA».get«a.fixedarray.name.toFirstUpper»()[i], «testValuesMap.get(a.fixedarray.type)» + (1.0+i), 1e-5);
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("string"))»
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						std::stringstream sstr;
						sstr << «testValuesMap.get(a.fixedarray.type)» << "-" << i;
						«objA».get«a.fixedarray.name.toFirstUpper»()[i] = sstr.str();
					}
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						std::stringstream sstr;
						sstr << «testValuesMap.get(a.fixedarray.type)» << "-" << i;
						TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(«objA».get«a.fixedarray.name.toFirstUpper»()[i], sstr.str()));
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("int32") || a.fixedarray.type.equalsIgnoreCase("uint32"))»
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						«objA».get«a.fixedarray.name.toFirstUpper»()[i] = «testValuesMap.get(a.fixedarray.type)» + i;
					}
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(«objA».get«a.fixedarray.name.toFirstUpper»()[i] == «testValuesMap.get(a.fixedarray.type)» + i);
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("char"))»
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						«objA».get«a.fixedarray.name.toFirstUpper»()[i] = static_cast<char>(«testValuesMap.get(a.fixedarray.type)» + i);
					}
					for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
						TS_ASSERT(«objA».get«a.fixedarray.name.toFirstUpper»()[i] == static_cast<char>(«testValuesMap.get(a.fixedarray.type)» + i));
					}
				«ENDIF»
				«IF (a.fixedarray.type.equalsIgnoreCase("bool"))»
					{
						bool flip = false;
						for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
							«objA».get«a.fixedarray.name.toFirstUpper»()[i] = flip;
							flip = !flip;
						}
					}
					{
						bool flip = false;
						for(uint32_t i = 0; i < «objA».getSize_«a.fixedarray.name.toFirstUpper»(); i++) {
							TS_ASSERT(«objA».get«a.fixedarray.name.toFirstUpper»()[i] == flip);
							flip = !flip;
						}
					}
				«ENDIF»
			«ENDIF»
		«ENDIF»
	'''
}
