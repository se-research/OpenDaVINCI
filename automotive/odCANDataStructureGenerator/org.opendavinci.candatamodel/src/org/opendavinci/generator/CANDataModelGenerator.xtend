/**
 * CANDataStructureGenerator - IDL tool to describe the mapping from
 *                             CAN data to high-level messages.
 * Copyright (C) 2015 - 2016 Christian Berger
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

import java.util.ArrayList
import java.util.HashMap
import java.util.Iterator
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess
import org.eclipse.xtext.generator.IGenerator
import org.opendavinci.canDataModel.CANSignal
import org.opendavinci.canDataModel.CANMessage
import org.opendavinci.canDataModel.CANMessageMapping
import java.util.Random
import org.opendavinci.canDataModel.CANSignalMapping
import org.opendavinci.canDataModel.CANMessageTesting
import org.opendavinci.canDataModel.ODVDFile

class CANDataModelGenerator implements IGenerator {

	/* This class describes all data to a defined CAN signal in a .can file. */
	static class CANSignalDescription {
		String m_FQDN
        String m_name
		String m_CANID
		String m_startBit
		String m_length
		String m_lengthBytes
		String m_signed
		String m_endian
		String m_multiplyBy
		String m_add
		String m_rangeStart
		String m_rangeEnd
	}
	
    /* This class describes all data to a defined CAN message in a .can file. */
    static class CANMessageDescription {
        String m_MessageName
        String m_CANID
        String m_length
        HashMap<String,CANSignalDescription> m_signals
    }
    
    /* This method is our interface to an outside caller. */
	override void doGenerate(Resource resource, IFileSystemAccess fsa) {
		val generatedHeadersFile = resource.URI.toString().substring(resource.URI.toString().lastIndexOf("/") + 1).replaceAll(".can", "")

        // First, extract all CAN messages from .can file.
        val mapOfDefinedCANMessages = collectDefinedCANMessages(resource.allContents.toIterable.filter(typeof(CANMessage)))
        
		// Next, extract all .odvd header names from the 'using' statement.
		val odvdIncludedFiles = extractOdvdHeaders(resource.allContents.toIterable.filter(typeof(ODVDFile)))
		
		// needed for the "super" header and source files
		var ArrayList<String> includedClasses=new ArrayList<String>
		for (e : resource.allContents.toIterable.filter(typeof(CANMessageMapping))) {
			includedClasses.add(e.mappingName.toString().replaceAll("\\.", "/"))
		}
		
		fsa.generateFile("include/GeneratedHeaders_" + generatedHeadersFile + ".h", generateSuperHeaderFileContent(generatedHeadersFile, includedClasses, odvdIncludedFiles))
		fsa.generateFile("src/GeneratedHeaders_" + generatedHeadersFile + ".cpp", generateSuperImplementationFileContent(generatedHeadersFile, includedClasses))
		
		var ArrayList<CANMessageTesting> tests=new ArrayList<CANMessageTesting>(resource.allContents.toIterable.filter(typeof(CANMessageTesting)).toList);
		
		// Next, generate the code for the actual mapping.
		for (e : resource.allContents.toIterable.filter(typeof(CANMessageMapping))) {
			fsa.generateFile("include/generated/" + e.mappingName.toString().replaceAll("\\.", "/") + ".h", 
			    generateHeaderFileContent(generatedHeadersFile, odvdIncludedFiles, e))
			fsa.generateFile("src/generated/" + e.mappingName.toString().replaceAll("\\.", "/") + ".cpp", 
				generateImplementationFileContent(e, "generated", mapOfDefinedCANMessages))
			fsa.generateFile("testsuites/" + e.mappingName.toString().replaceAll("\\.", "_") + "TestSuite.h", 
			    generateTestSuiteContent(generatedHeadersFile, odvdIncludedFiles, e, tests, mapOfDefinedCANMessages))
		}
	}

    /* This method collects all CAN message definitions. */
    def collectDefinedCANMessages(Iterable<CANMessage> iter) {
        val canMessagesByName =  new HashMap<String, CANMessageDescription>
        val localIterator = iter.iterator
        while (localIterator.hasNext) {
            val cs = localIterator.next
            val cmd = new CANMessageDescription
            cmd.m_MessageName = cs.canMessageName
            cmd.m_CANID = cs.canIdentifier
            cmd.m_length = cs.canMessageLength
            cmd.m_signals = collectDefinedCANSignals(cs.cansignals, cmd)
            canMessagesByName.put(cmd.m_CANID, cmd)
        }
        return canMessagesByName
    }

	/* This method collects CAN signal definitions. */
	def collectDefinedCANSignals(Iterable<CANSignal> iter, CANMessageDescription canMessage) {
		val cansignalsByFQDN =  new HashMap<String, CANSignalDescription>
		val localIterator = iter.iterator
		while (localIterator.hasNext) {
			val cs = localIterator.next
			val csd = new CANSignalDescription
			csd.m_FQDN = canMessage.m_MessageName+'.'+cs.cansignalname
			csd.m_CANID = canMessage.m_CANID
			csd.m_name = cs.cansignalname
			csd.m_startBit = cs.startBit
			csd.m_length = cs.length
			if((cs.length==null || cs.length=="") && (cs.lengthBytes!=null || cs.lengthBytes!=""))
				csd.m_length = (Integer.parseInt(cs.lengthBytes)*8)+""
			csd.m_lengthBytes = cs.lengthBytes
			if((cs.lengthBytes==null || cs.lengthBytes=="") && (cs.length!=null || cs.length!="") && Integer.parseInt(cs.length)%8==0)
				csd.m_lengthBytes = (Integer.parseInt(cs.length)/8)+""
			csd.m_signed = cs.signed
			csd.m_endian = cs.endian
			csd.m_multiplyBy = cs.multiplyBy
			csd.m_add = cs.add
			csd.m_rangeStart = cs.rangeStart
			csd.m_rangeEnd = cs.rangeEnd
			cansignalsByFQDN.put(csd.m_FQDN, csd)
		}
        return cansignalsByFQDN
	}
	
	def findSignal(HashMap<String, CANMessageDescription> canMessages, String signalFQDN) {
	    for(canMessage : canMessages.values) {
            val csd = canMessage.m_signals.get(signalFQDN)
            if(csd != null) {
                return csd
            }
	    }
	    return null
	}

	/* This method collects the name of the needed odvd headers. */
	def extractOdvdHeaders(Iterable<ODVDFile> iter) {
		val odvdHeaders =  new ArrayList<String>
		val localIterator = iter.iterator
		while (localIterator.hasNext) {
			val odvd = localIterator.next
			val include="#include <"+odvd.odvdFileName.toLowerCase+"/GeneratedHeaders_"+odvd.odvdFileName+".h>"
			odvdHeaders.add(include)
		}
        return odvdHeaders
	}
	
    /* This method generates the header file content. */
	def generateSuperHeaderFileContent(String generatedHeadersFile, ArrayList<String> includedClasses, ArrayList<String> odvdIncludedFiles) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_
#define GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_

#include <string>
#include <vector>

#include "odcantools/CANMessage.h"

«FOR include : includedClasses»
#include "generated/«include».h"
«ENDFOR»

#include <opendavinci/odcore/data/Container.h>

«FOR odvd : odvdIncludedFiles»
«odvd»
«ENDFOR»

namespace canmapping {

    using namespace std;

    class CanMapping {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            CanMapping(const CanMapping &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            CanMapping& operator=(const CanMapping &/*obj*/);

        public:
            CanMapping();

            virtual ~CanMapping();

            /**
             * This method adds the given GenericCANMessage to the internal
             * CAN message decoder. If this message could be decoded (or
             * including the previous sequence, this method returns a valid
             * Container (i.e. !Container::UNDEFINEDDATA).
             *
             * @param gcm Next GenericCANMessage.
             * @return Container, where the type needs to be checked to determine invalidity (i.e. !Container::UNDEFINEDDATA).
             */
            vector<odcore::data::Container> mapNext(const ::automotive::GenericCANMessage &gcm);

        private:
        
			«FOR include : includedClasses»
			«var String className=include.split('\\/').get(include.split('\\/').size-1)»
				«include.replaceAll('\\/','::')» m_«className.toFirstLower»;
			«ENDFOR»
		
    };

} // canmapping

#endif /*GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_*/
'''

    /* This method generates the super implementation file content. */
	def generateSuperImplementationFileContent(String generatedHeadersFile, ArrayList<String> includedClasses) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

«FOR include : includedClasses»
#include "generated/«include».h"
«ENDFOR»

#include "GeneratedHeaders_«generatedHeadersFile».h"

namespace canmapping {


«var ArrayList<String> members=new ArrayList<String>»
«{ // extracting the contructor parameters
	var Iterator<String> iter = includedClasses.iterator;
	var String member;
	while (iter.hasNext()){
	member=iter.next();
	var String className=member.split('\\/').get(member.split('\\/').size-1)
	var String temp="m_"+className.toFirstLower+" ()";
	if(iter.hasNext())temp+=",";
	members.add(temp);
}}»
    CanMapping::CanMapping() :
    «FOR member:members»
    «member»
    «ENDFOR»
{}

    CanMapping::~CanMapping() {}

    vector<odcore::data::Container> CanMapping::mapNext(const ::automotive::GenericCANMessage &gcm) {
        vector<odcore::data::Container> listOfContainers;

        // Traverse all defined mappings and check whether a new high-level message could be fully decoded.
	    «FOR member:members»
	    {
	    	odcore::data::Container container = «member.substring(0,member.indexOf(" ()"))».decode(gcm);
	    	if (container.getDataType() != odcore::data::Container::UNDEFINEDDATA)
	    	{
	    		listOfContainers.push_back(container);
	    	}
	    }
	    «ENDFOR»

        return listOfContainers;
    }

} // canmapping
'''

// this method generates the header file body
	def generateHeaderFileBody(String className, CANMessageMapping mapping) '''
    using namespace std;

    class «className» : public odcore::data::SerializableData, public odcore::base::Visitable {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            «className»(const «className» &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            «className»& operator=(const «className» &/*obj*/);

        public:
            «className»();

		«IF mapping.mappings.size>0»
		«var ArrayList<String> parameters=new ArrayList<String>»
		«var Iterator<CANSignalMapping> iter = mapping.mappings.iterator»
		«{ // contructor parameter
			while (iter.hasNext()){
				iter.next();
				var String temp="double";
				if(iter.hasNext())temp+=", ";
				parameters.add(temp);
			}
		}»
		«className»(«FOR parameter:parameters»«parameter»«ENDFOR»);
		«ENDIF»

            virtual ~«className»();

            odcore::data::Container decode(const ::automotive::GenericCANMessage &gcm);
            
            ::automotive::GenericCANMessage encode(odcore::data::Container &c);
            
«var ArrayList<String> capitalizedNames=new ArrayList<String>»
«{ // fields names
			var String[] chunks
			var String capitalizedName
			for(currentMapping : mapping.mappings){
				chunks=currentMapping.cansignalname.split('\\.');
				capitalizedName=""
				for(chunk:chunks){ // add type information
					capitalizedName+=chunk.toFirstUpper
				}
				capitalizedNames+=capitalizedName
			}
	}»
        	«FOR capitalizedName : capitalizedNames»
        	double get«capitalizedName»() const;
        	void set«capitalizedName»(const double&);
        	
        	«ENDFOR»

            virtual const string toString() const;
    
    		virtual ostream& operator<<(ostream &out) const;
    
    		virtual istream& operator>>(istream &in);

    		virtual void accept(odcore::base::Visitor &v);
    		

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
        private:
        	«FOR capitalizedName : capitalizedNames»
        	double m_«capitalizedName.toFirstLower»;
        	«ENDFOR»
        	
        	std::map<uint64_t,uint64_t> m_payloads;
            std::map<uint64_t,uint8_t> m_lengths;
        	std::vector<uint64_t> m_neededCanMessages;
        	uint64_t m_index;
        	
        	::«mapping.mappingName.replaceAll("\\.", "::")» «"m_"+mapping.mappingName.toFirstLower.replaceAll("\\.", "_")»;
        	
    }; // end of class "«className»"
    
	'''

	def generateHeaderFileNSs(String[] namespaces, int i, CANMessageMapping mapping) '''
	«IF namespaces.size>i+1»
	namespace «namespaces.get(i)» {
		«generateHeaderFileNSs(namespaces, i+1, mapping)»
	} // end of namespace "«namespaces.get(i)»"
	«ELSE»
	«generateHeaderFileBody(namespaces.get(i), mapping)»
	«ENDIF»
	'''

    /* This method generates the header file content. */
	def generateHeaderFileContent(String generatedHeadersFile, ArrayList<String> odvdIncludedFiles, CANMessageMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: «mapping.mappingName.toString»
#ifndef «mapping.mappingName.toString.toUpperCase.replaceAll("\\.", "_")»_H_
#define «mapping.mappingName.toString.toUpperCase.replaceAll("\\.", "_")»_H_

#include <memory>
#include <cmath>
#include <vector>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/data/SerializableData.h>

#include "odcantools/CANMessage.h"

«FOR odvd : odvdIncludedFiles»
«odvd»
«ENDFOR»

namespace canmapping {
	«var String[] classNames = mapping.mappingName.toString.split('\\.')»
	«IF classNames.size>1»
		«generateHeaderFileNSs(classNames, 0, mapping)»
	«ELSE»
		«generateHeaderFileBody(classNames.get(0), mapping)»
	«ENDIF»
} // end of namespace canmapping

#endif /*«mapping.mappingName.toString.toUpperCase.replaceAll("\\.", "_")»_H_*/
'''

// THIS WILL GENERATE THE IMPLEMENTATION (.CPP) FILE NAMESPACES
	def generateImplementationFileNSs(String[] namespaces, int i, CANMessageMapping mapping, String includeDirectoryPrefix, HashMap<String, CANMessageDescription> canMessages, ArrayList<String> canIDs) '''
	«IF namespaces.size>i+1»
	namespace «namespaces.get(i)» {
		«generateImplementationFileNSs(namespaces, i+1, mapping, includeDirectoryPrefix, canMessages, canIDs)»
	} // end of namespace "«namespaces.get(i)»"
	«ELSE»
	«generateImplementationFileBody(namespaces.get(i), mapping, includeDirectoryPrefix, canMessages, canIDs)»
	«ENDIF»
	'''

// THIS WILL GENERATE THE IMPLEMENTATION (.CPP) FILE BODY
	def generateImplementationFileBody(String className, CANMessageMapping mapping, String includeDirectoryPrefix, HashMap<String, CANMessageDescription> canMessages, ArrayList<String> canIDs) '''
	
	using namespace std;

«var ArrayList<String> capitalizedNames=new ArrayList<String>»
«{
		var String[] chunks
		var String capitalizedName
		for(currentMapping : mapping.mappings){
			chunks=currentMapping.cansignalname.split('\\.');
			capitalizedName=""
			for(chunk:chunks){
				capitalizedName+=chunk.toFirstUpper
			}
			capitalizedNames+=capitalizedName
		}
	}»

	«className»::«className»() :
		odcore::data::SerializableData(),
		odcore::base::Visitable(),
		«FOR capitalizedName : capitalizedNames»
		m_«capitalizedName.toFirstLower»(0.0),
		«ENDFOR»
		m_payloads(),
        m_lengths(),
		m_neededCanMessages(),
		m_index(0),
		«"m_"+mapping.mappingName.toFirstLower.replaceAll("\\.", "_")»()
	{
		«FOR id : canIDs»
		m_neededCanMessages.push_back(«id»);
        «ENDFOR»
	}
	
	«IF mapping.mappings.size>0»
	«var ArrayList<String> parameters=new ArrayList<String>»
	«var ArrayList<String> initializations=new ArrayList<String>»
	«var Iterator<CANSignalMapping> iter = mapping.mappings.iterator»
	«{ // constructor parameters
		var int i=0;
		while (iter.hasNext()){
		iter.next();
		var String temp="double parameter"+(i++);
		if(iter.hasNext())temp+=", ";
		parameters.add(temp);
		}
		i=0;
		for(currentMapping : mapping.mappings){
			var String[] chunks=currentMapping.cansignalname.split('\\.');
			var String capitalizedName=""
			for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			initializations.add("m_"+capitalizedName.toFirstLower+"(parameter"+(i++)+")");
		}
		}»
	«className»::«className»(«FOR parameter:parameters»«parameter»«ENDFOR») :
		odcore::data::SerializableData(),
		odcore::base::Visitable(),
		«FOR initialization:initializations»«initialization+","+'\n'»«ENDFOR»
		m_payloads(),
	    m_lengths(),
		m_neededCanMessages(),
		m_index(0),
		«"m_"+mapping.mappingName.toFirstLower.replaceAll("\\.", "_")»()
	{
		«FOR id : canIDs»
		m_neededCanMessages.push_back(«id»);
        «ENDFOR»
	}
	«ENDIF»
	
	«className»::~«className»() {}
	
    	«var String result="\"Class : "+className+"\"<<endl"+'\n'»
    	«var int fieldsNum=mapping.mappings.size»
    	«IF fieldsNum>0»
		«var Iterator<CANSignalMapping> iter = mapping.mappings.iterator»
		«{var int i=0;
			while (iter.hasNext()){
			iter.next();
			var String[] chunks=mapping.mappings.get(i).cansignalname.split('\\.');
			var String capitalizedName=""
			for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			result+='\t'+'\t'+"<<\" "+mapping.mappings.get(i).cansignalname.toString+" : \"<< +m_"+capitalizedName.toFirstLower+" << endl";
			i++;
			if(iter.hasNext())result+='\n';
    	}}»
    	«ENDIF»
	const string «className»::toString() const {
		stringstream result;
		result << «result»;
		return result.str();
	}
	
	«FOR capitalizedName : capitalizedNames»
	double «className»::get«capitalizedName»() const{
		return m_«capitalizedName.toFirstLower»;
	}
	
	void «className»::set«capitalizedName»(const double &«capitalizedName.toFirstLower») {
		m_«capitalizedName.toFirstLower»=«capitalizedName.toFirstLower»;
	}
	«ENDFOR»
	
	ostream& «className»::operator<<(ostream &out) const {
		odcore::serialization::SerializationFactory& sf = odcore::serialization::SerializationFactory::getInstance();
		std::shared_ptr<odcore::serialization::Serializer> s = sf.getSerializer(out);

		«IF mapping.mappings.size>0»
		«var ArrayList<String> opOutBody=new ArrayList<String>»
		«for(var int i=0;i<mapping.mappings.size;i++){
			var String capitalizedName
			var String[] chunks=mapping.mappings.get(i).cansignalname.split('\\.');
			capitalizedName=""
			for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			
			opOutBody+="s->write(static_cast<uint32_t>("+mapping.mappings.get(i).signalIdentifier+"), m_"+capitalizedName.toFirstLower+");"
		}»
		«FOR line:opOutBody»
		«line»
		«ENDFOR»
		«ENDIF»
		return out;
	}
	
	istream& «className»::operator>>(istream &in) {
		odcore::serialization::SerializationFactory& sf = odcore::serialization::SerializationFactory::getInstance();
		std::shared_ptr<odcore::serialization::Deserializer> s = sf.getDeserializer(in);
		
		«IF mapping.mappings.size>0»
		uint32_t id;
		«var ArrayList<String> opInBody=new ArrayList<String>»
		«for(var int i=0;i<mapping.mappings.size;i++){
			var String capitalizedName
			var String[] chunks=mapping.mappings.get(i).cansignalname.split('\\.');
			capitalizedName=""
			for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			
			opInBody+="id="+mapping.mappings.get(i).signalIdentifier+";"
			opInBody+="s->read(static_cast<uint32_t>(id), m_"+capitalizedName.toFirstLower+");"
		}»
		«FOR line:opInBody»
		«line»
		«ENDFOR»
		«ENDIF»
		return in;
	}
	
	int32_t «/* Here, we generate the method to return the message ID. */className»::ID() {
		return 0; // There is no valid message identifier specified as the CAN message will be mapped to a high-level data structure.
	}

	const string «/* Here, we generate the method to return the short message name. */className»::ShortName() {
		return "«className»";
	}

	const string «/* Here, we generate the method to return the long message name. */className»::LongName() {
		return "«className»";
	}

	int32_t «/* Here, we generate the method to return the message ID. */className»::getID() const {
		return 0; // There is no valid message identifier specified as the CAN message will be mapped to a high-level data structure.
	}

	const string «/* Here, we generate the method to return the short message name. */className»::getShortName() const {
		return «className»::ShortName();
	}

	const string «/* Here, we generate the method to return the long message name. */className»::getLongName() const {
		return «className»::LongName();
	}

	void «className»::accept(odcore::base::Visitor &v) {
	v.beginVisit(ID(), ShortName(), LongName());
	«IF mapping.mappings.size==0»
	(void)v;
	«ELSE»
	«var ArrayList<String> acceptBody=new ArrayList<String>»
	«for(var int i=0;i<mapping.mappings.size;i++){
			var String capitalizedName
			var String[] chunks=mapping.mappings.get(i).cansignalname.split('\\.');
			capitalizedName=""
			for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			
			acceptBody+="v.visit(static_cast<uint32_t>("+mapping.mappings.get(i).signalIdentifier+"), \""
						+mapping.mappings.get(i).cansignalname+"\", \""
						+chunks.get(chunks.size-1)+"\", m_"
						+capitalizedName.toFirstLower+");"
		}»
		«FOR line:acceptBody»
		«line»
		«ENDFOR»
	«ENDIF»
	v.endVisit();
	}

/*
	**********************************************************
	**                                                      **
	**                        ENCODE                        **
	**                                                      **
	**********************************************************
*/
	::automotive::GenericCANMessage «className»::encode(odcore::data::Container &c) 
	{
	«IF canIDs.size==0»
	(void)c;
	// Return an empty GenericCANMessage
	cerr<<"Fatal Error: Mapping '«className»' is empty."<<endl;
	::automotive::odcantools::CANMessage error(0x00,0,0x00);
	return error.getGenericCANMessage();
    «ELSEIF canIDs.size<0»
	(void)c;
	cerr<<"Fatal Error: Mapping '«className»' experienced an error. "<<endl;
	::automotive::odcantools::CANMessage error(0x00,0,0x00);
	return error.getGenericCANMessage();
    «ELSE»
    «{//make sure all the CAN messages exist*/
        
    }»

		«var String cmNamePrefix="CM_" /* multiple canIDs partially supported */»
		«FOR id : canIDs»
		::automotive::odcantools::CANMessage «cmNamePrefix+id»(«id»,«canMessages.get(id).m_length»,0x00);
		«ENDFOR»

		if(c.getDataType() != ::«mapping.mappingName.replaceAll("\\.","::")»::ID())
		{
			// something went wrong
			::automotive::odcantools::CANMessage error(0x00,0,0x00);
		    return error.getGenericCANMessage();
		}

		bool found, extracted, abort=false;
		::«mapping.mappingName.replaceAll("\\.","::")» temp«className»=c.getData<::«mapping.mappingName.replaceAll("\\.","::")»>();
		odcore::reflection::MessageFromVisitableVisitor mfvv;
		temp«className».accept(mfvv);
		odcore::reflection::Message msg=mfvv.getMessage();

    	«var String varName»
		«FOR currentSignalInMapping : mapping.mappings»
			«var CANSignalDescription CurrentCANSignal=findSignal(canMessages,currentSignalInMapping.cansignalname)»
			«{varName=currentSignalInMapping.cansignalname.replace('.','_').toFirstUpper;""}»
			
			///////// manipulating signal «currentSignalInMapping.cansignalname» : «currentSignalInMapping.signalIdentifier»
			«IF CurrentCANSignal!=null»
			found=extracted=false;
			double «varName» = msg.getValueFromScalarField<double>(«currentSignalInMapping.signalIdentifier», found, extracted);
			
			if(found && extracted) {
			    ::automotive::odcantools::CANSignal signal_«currentSignalInMapping.cansignalname.replaceAll("\\.","_")»(«CurrentCANSignal.m_startBit»,«CurrentCANSignal.m_length»,"«CurrentCANSignal.m_signed»","«CurrentCANSignal.m_endian»",«CurrentCANSignal.m_multiplyBy»,«CurrentCANSignal.m_add»,«CurrentCANSignal.m_rangeStart»,«CurrentCANSignal.m_rangeEnd»);
                «cmNamePrefix+CurrentCANSignal.m_CANID».addSignal(«currentSignalInMapping.signalIdentifier»,signal_«currentSignalInMapping.cansignalname.replaceAll("\\.","_")»);
                «cmNamePrefix+CurrentCANSignal.m_CANID».encodeSignal(«currentSignalInMapping.signalIdentifier»,«varName»);
			}
			else {
				abort=true; // set to true and never reset to false to keep track of failures
			}
			«ELSE /* This else branch should be unreachable since the generator is supposed to fail when a signal is misspelled or not found*/»
				«System.err.println("\n\nWarning: Signal "+className+"."+currentSignalInMapping.cansignalname+" could not be found. Check your .can file. \n\n")»
				cerr<<endl<<endl<<"Warning: Signal '«className».«currentSignalInMapping.cansignalname»' could not be found. Check your .can file."<<endl<<endl<<endl;
				«throwSignalNotFoundException(className+'.'+currentSignalInMapping.cansignalname)»
				«System.exit(-1)»
			«ENDIF»
		«ENDFOR»
		
		if(abort) { // if there was at least one failure
		    // discard and return
		    ::automotive::odcantools::CANMessage error(0x00,0,0x00);
		    return error.getGenericCANMessage();
		}
		
		// return the CAN message, or the first CAN message if the mapping is defined over multiple CAN messages
		return «cmNamePrefix+canIDs.get(0)».getGenericCANMessage();
	«ENDIF»
	}

/*
	**********************************************************
	**                                                      **
	**                        DECODE                        **
	**                                                      **
	**********************************************************
*/
	odcore::data::Container «className»::decode(const ::automotive::GenericCANMessage &gcm) 
	{
		odcore::data::Container c;
    «IF canIDs.size==0»
        // Return an empty GenericCANMessage
        cerr<<"Fatal Error: Mapping '«className»' is empty."<<endl;
        return c;
    «ELSEIF canIDs.size<0»
        cerr<<"Fatal Error: Mapping '«className»' experienced an error. "<<endl;
        return c;
    «ELSE»
		«IF mapping.unordered==null || mapping.unordered.compareTo("unordered")!=0»

		bool reset=false;
		«ENDIF»
		switch(gcm.getIdentifier())
		{
    	«FOR id : canIDs /* multiple canIDs supported */»

    		case «id» : 
    		«IF mapping.unordered!=null && mapping.unordered.compareTo("unordered")==0»

	    	// since the order doesn't matter, store the payload in a map for future use replacing the current content held there
	    	m_payloads[«id»] = gcm.getData();
	    	m_lengths[«id»] = gcm.getLength();
    		«ELSE»

	    	// since the order matters:
	    	if(m_neededCanMessages.at(m_index) == «id») // if we got the expected message
	    	{
	    		// Store the payload in a map for future use replacing the current content
	    	m_payloads[«id»] = gcm.getData();
	    	m_lengths[«id»] = gcm.getLength();
	    		// modularly increase the internal index
	    		(m_index==m_neededCanMessages.size()-1) ? m_index=0 : ++m_index;
	    	}
	    	else // otherwise reset
	    		reset=true;
    		«ENDIF»
    		break;

        «ENDFOR»
		default : return c; // valid id not found
	}

	    «IF mapping.unordered==null || mapping.unordered.compareTo("unordered")!=0»

		if(reset)
		{		
			// reset the payloads and lengths map
			while(! m_payloads.empty())
				m_payloads.erase(m_payloads.begin());
		while(! m_lengths.empty())
		    m_lengths.erase(m_lengths.begin());
			// reset the internal index
			m_index=0;
		}
		«ENDIF»
		// if we don't have all the needed CAN messages, return 
		if(m_payloads.size()!=m_neededCanMessages.size())
			return c;

		// Create a generic message.
		odcore::reflection::Message message;

        «var String cmNamePrefix="CM_"»
        «FOR id : canIDs /* multiple canIDs supported */»
        ::automotive::odcantools::CANMessage «cmNamePrefix+id»(«id»,m_lengths[«id»],m_payloads[«id»]);
        «ENDFOR»

		«FOR currentSignalInMapping : mapping.mappings»
			«var CANSignalDescription CurrentCANSignal=findSignal(canMessages,currentSignalInMapping.cansignalname)»
			«IF CurrentCANSignal!=null /*if the signal exists*/»

            «var String capitalizedName»
			«{
				var String[] chunks=currentSignalInMapping.cansignalname.split('\\.');
				capitalizedName=""
				for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
			}»
			«var String memberVarName="m_"+capitalizedName.toFirstLower»

			// addressing signal «currentSignalInMapping.cansignalname» : «currentSignalInMapping.signalIdentifier»
			{
				// Add the CAN signal to the CAN message
				::automotive::odcantools::CANSignal «currentSignalInMapping.cansignalname.replaceAll("\\.","_")»(«CurrentCANSignal.m_startBit»,«CurrentCANSignal.m_length»,"«CurrentCANSignal.m_signed»","«CurrentCANSignal.m_endian»",«CurrentCANSignal.m_multiplyBy»,«CurrentCANSignal.m_add»,«CurrentCANSignal.m_rangeStart»,«CurrentCANSignal.m_rangeEnd»);
                «cmNamePrefix+CurrentCANSignal.m_CANID».addSignal(«currentSignalInMapping.signalIdentifier»,«currentSignalInMapping.cansignalname.replaceAll("\\.","_")»);
                «memberVarName»=«cmNamePrefix+CurrentCANSignal.m_CANID».decodeSignal(«currentSignalInMapping.signalIdentifier»);

				// Create a field for a generic message.
				odcore::reflection::Field<double> *f = new odcore::reflection::Field<double>(«memberVarName»);
				f->setFieldIdentifier(«currentSignalInMapping.signalIdentifier»); // The identifiers specified here must match with the ones defined in the .odvd file!
				f->setLongFieldName("«CurrentCANSignal.m_FQDN»");
				f->setShortFieldName("«{var String[] res; res=CurrentCANSignal.m_FQDN.split("\\."); res.get(res.size-1)}»");
				f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
				f->setSize(sizeof(«memberVarName»));

				// Add created field to generic message.
				message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f));
			}
			«ELSE /* This else branch should be unreachable since the generator is supposed to fail when a signal is misspelled or not found*/»
				// Signal "«currentSignalInMapping.cansignalname»" could not be found. 
				«System.err.println("\n\nWarning: Signal "+className+"."+currentSignalInMapping.cansignalname+" could not be found. Check your .can file. \n\n")»
				cerr<<endl<<endl<<"Warning: Signal '«className».«currentSignalInMapping.cansignalname»' could not be found. Check your .can file."<<endl<<endl<<endl;
				«throwSignalNotFoundException(className+'.'+currentSignalInMapping.cansignalname)»
				«System.exit(-1)»
			«ENDIF»
		«ENDFOR»
		// Depending on the CAN message specification, we are either ready here
		// (i.e. mapping one CAN message to one high-level C++ message), or we have
		// to wait for more low-level CAN messages to complete this high-level C++ message.
		// Thus, our state machine would have to store this (incomplete) "message"
		// variable internally to continue decoding later.
		{
			// As we are ready here, we create a visitor to traverse the 
			// unnamed message and create a named message (i.e. an instance
			// of a high-level C++ message) to be distributed as a Container.
			odcore::reflection::MessageToVisitableVisitor mtvv(message);
        	«var String memberHLName="m_"+mapping.mappingName.toFirstLower.replaceAll("\\.", "_")»
			// Letting the high-level message accept the visitor to set the values.
        	«memberHLName».accept(mtvv);
			// Create the resulting container carrying a valid payload.
			c = odcore::data::Container(«memberHLName»);
		}

	«ENDIF»
		return c;
	}
	'''
	
	def throwSignalNotFoundException(String signalLongName) {
		//either IllegalStateException or UnsupportedOperationException
		throw new IllegalStateException("\n\nWarning: Signal "+signalLongName+" could not be found. Check your .can file. \n\n");
		//System.exit(-1); // doesn't work here
	}
	
	/* This method generates the implementation (.cpp). */
	def generateImplementationFileContent(CANMessageMapping mapping, String includeDirectoryPrefix, HashMap<String, CANMessageDescription> canMessages) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Source file for: «mapping.mappingName.toString»

«var ArrayList<String> canIDs=new ArrayList<String>»
«FOR currentMapping : mapping.mappings»
«var String signalName=currentMapping.cansignalname»
«var CANSignalDescription canSignal=findSignal(canMessages,signalName) /*canSignals.get(signalName)maybe preserve the global signal collection with reference to parent can message?*/»
«{ // make sure we don't add 2 times the same CAN id
	if(canSignal!=null)
	{
		var boolean test=true;
		for(id:canIDs)
			if(id.compareToIgnoreCase(canSignal.m_CANID)==0)
				test=false;
		if(test)
			canIDs.add(canSignal.m_CANID);		
	}
	""
}»
«IF canSignal==null»
«System.err.println("\n\nWarning: Signal "+signalName+" could not be found. Check your .can file. \n\n") /*first one to show up in console*/»
«throwSignalNotFoundException(signalName)»
«System.exit(-1)»
«ENDIF»
«ENDFOR»

#include <memory>
#include <iostream>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/reflection/MessageToVisitableVisitor.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>
#include <opendavinci/odcore/serialization/Deserializer.h>

#include "generated/«mapping.mappingName.toString.replaceAll('\\.','/')».h"

namespace canmapping {

	«var String[] classNames = mapping.mappingName.toString.split('\\.')»
	«IF classNames.size>1»
		«generateImplementationFileNSs(classNames, 0, mapping, includeDirectoryPrefix, canMessages, canIDs)»
	«ELSE»
		«generateImplementationFileBody(classNames.get(0), mapping, includeDirectoryPrefix, canMessages, canIDs)»
	«ENDIF»

} // canmapping
'''

	// Generate the test suite content (.h).	
	def generateTestSuiteContent(String generatedHeadersFile, ArrayList<String> odvdIncludedFiles, CANMessageMapping mapping, 
				ArrayList<CANMessageTesting> canSignalTesting, HashMap<String, CANMessageDescription> canMessages) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Test suite file for: «mapping.mappingName.toString»
«var ArrayList<String> canIDs=new ArrayList<String>»
«FOR currentMapping : mapping.mappings»
«var String signalName=currentMapping.cansignalname»
«var CANSignalDescription canSignal=findSignal(canMessages,signalName)»
«{ // make sure we don't add 2 times the same CAN id
	if(canSignal!=null)
	{
		var boolean test=true;
		for(id:canIDs)
			if(id.compareToIgnoreCase(canSignal.m_CANID)==0)
				test=false;
		if(test)
			canIDs.add(canSignal.m_CANID);		
	}
	""
}»
«IF canSignal==null»
«System.err.println("\n\nWarning: Signal "+signalName+" could not be found. Check your .can file. \n\n")»
«throwSignalNotFoundException(signalName)»
«System.exit(-1)»
«ENDIF»
«ENDFOR»

#ifndef CANMAPPINGTESTSUITE_«mapping.mappingName.split('\\.').get(mapping.mappingName.split('\\.').size-1).toUpperCase»_H_
#define CANMAPPINGTESTSUITE_«mapping.mappingName.split('\\.').get(mapping.mappingName.split('\\.').size-1).toUpperCase»_H_

#include "GeneratedHeaders_«generatedHeadersFile».h"
#include "generated/«mapping.mappingName.toString.replaceAll('\\.','/')».h"

«FOR odvd : odvdIncludedFiles»
«odvd»
«ENDFOR»
#include "cxxtest/TestSuite.h"
#include <sstream>
#include <iostream>
#include "opendavinci/odcore/data/Container.h"
#include <opendavinci/odcore/reflection/MessageToVisitableVisitor.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/reflection/Field.h>

#include "odcantools/CANMessage.h"

using namespace std;

/**
 * The actual testsuite starts here.
 */
class CANBridgeTest : public CxxTest::TestSuite {
    public:
        void testSer_Deser() {
            
            «var String init=""»
            «var int fieldsNum=mapping.mappings.size»
            «IF fieldsNum>0»
            «var Iterator<CANSignalMapping> iter = mapping.mappings.iterator»
            «{
            //(1,1234.56,3.1415,0.00000001)
                var Random r = new Random();
                var double rangeMin=-10000.0;
                var double rangeMax=10000.0;
                while (iter.hasNext()){
                iter.next();
                var double randomValue = rangeMin + (rangeMax - rangeMin) * r.nextDouble();
                init+=randomValue+"";
                if(iter.hasNext())init+=", ";
            }}»
            «ENDIF»
            
            «var String HLName= mapping.mappingName.toFirstLower.replaceAll("\\.", "_")»
            canmapping::«mapping.mappingName.toString.replaceAll("\\.", "::")» «HLName»_1«IF fieldsNum>0»«"("+init+")"»«ENDIF»;
            canmapping::«mapping.mappingName.toString.replaceAll("\\.", "::")» «HLName»_2;
            
            stringstream ss1,ss2;
            ss1 << «HLName»_1;
            
            TS_ASSERT(ss1.str().compare(ss2.str())!=0);
            
            ss1 >> «HLName»_2;
            ss2 << «HLName»_2;
            
            TS_ASSERT(ss1.str().compare(ss2.str())==0);
        }

    void testDecode() {
        «var int testIndex=0»
        «FOR test : canSignalTesting /* this loops over all the provided test suites*/»
            «IF test.mappingName.toString.compareToIgnoreCase(mapping.mappingName.toString)==0»
                «var String testName="test_"+(testIndex++)»
                «var HashMap<String,String> GCMs=new HashMap<String,String>»
            {
                // Mapping name «test.mappingName»
                «var int gcmIndex=0»
                «var String gcmName="gcm_"»
                «FOR description : test.CANMessageDescriptions»
                // id «description.canIdentifier»
                // payload «description.payload» : length «(description.payload.length-2)/2» bytes

                    ::automotive::GenericCANMessage «{gcmIndex+=1;gcmName=gcmName.substring(0,4)+gcmIndex}»;
                    «gcmName».setIdentifier(«description.canIdentifier»);
                    «gcmName».setLength(«(description.payload.length-2)/2»);
                    «gcmName».setData(«description.payload»);
                    «{GCMs.put(description.canIdentifier,gcmName);""}»
                «ENDFOR»

                canmapping::«mapping.mappingName.toString.replaceAll("\\.", "::")» «testName»;
                
                «IF canIDs.length==GCMs.size»
                    «FOR canid:canIDs»
                    «testName».decode(«GCMs.get(canid)»);
                    «ENDFOR»
                    
                    «var ArrayList<String> asserts=new ArrayList<String>»
                    «{
                        for(var int index=0;index<mapping.mappings.size;index++){
                            var String capitalizedName=""
                            var String[] chunks=mapping.mappings.get(index).cansignalname.split('\\.')
                            for(chunk:chunks) capitalizedName+=chunk.toFirstUpper
                            for(result:test.results)
                                if(result.signalIdentifier.compareToIgnoreCase(mapping.mappings.get(index).signalIdentifier)==0)
                                    asserts+="TS_ASSERT_DELTA("+testName+".get"+capitalizedName+"() , "+result.expectedResult+", 1e-4);"+'\n'
                        }
                    }»
                    «FOR assertions:asserts»
                    «assertions»
                    «ENDFOR»
                «ELSE»
                    // not enough CAN messages were provided «canIDs.length» «GCMs.size»
                «ENDIF»
            }
            «ENDIF»
        «ENDFOR»
    }

«{testIndex=0;""}»
    void testEncode() {
    «FOR test : canSignalTesting»
        «IF test.mappingName.toString.compareToIgnoreCase(mapping.mappingName.toString)==0»
            «var String testName="test_"+(testIndex++)»
            {
             // Mapping name «test.mappingName»

            «IF test.CANMessageDescriptions.size==1»

                // id «test.CANMessageDescriptions.get(0).canIdentifier»
                // payload «test.CANMessageDescriptions.get(0).payload» : length «(test.CANMessageDescriptions.get(0).payload.length-2)/2»

                odcore::reflection::Message message;
    
                «var ArrayList<String> assignments=new ArrayList<String>»
                «{
                    for(var int index=0;index<mapping.mappings.size;index++){
                        var int fIndex=0;
                        for(result:test.results){
                            fIndex++
                            if(result.signalIdentifier.compareToIgnoreCase(mapping.mappings.get(index).signalIdentifier)==0){
                                assignments+="odcore::reflection::Field<double> *f_"+fIndex+" = new odcore::reflection::Field<double>("+result.expectedResult+");"+'\n'+
                                                "f_"+fIndex+"->setFieldIdentifier("+result.signalIdentifier+");"+'\n'+
                                                "f_"+fIndex+"->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);"+'\n'+
                                                "message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f_"+fIndex+"));"+'\n'
                            }
                        }
                    }
                }»

                «FOR assignment:assignments»
                «assignment»
                «ENDFOR»

                odcore::reflection::MessageToVisitableVisitor mtvv(message);
                ::«mapping.mappingName.toString.replaceAll("\\.", "::")» HLClass;
                HLClass.accept(mtvv);
                odcore::data::Container c(HLClass);
                
                canmapping::«mapping.mappingName.toString.replaceAll("\\.", "::")» «testName»;
                ::automotive::GenericCANMessage GCM;
                GCM=«testName».encode(c);

    // Testing the ID of the resulting CAN message
    TS_ASSERT_EQUALS(GCM.getIdentifier(),«test.CANMessageDescriptions.get(0).canIdentifier»);
                // Testing the length of the resulting CAN message
                «{
                    // add a test for the length of the produced CAN message
                    var int payloadLength=test.CANMessageDescriptions.get(0).payload.length;
                    // subtracting the substring "0x"
                    if(test.CANMessageDescriptions.get(0).payload.substring(0,2).compareToIgnoreCase("0x")==0)
                        payloadLength-=2;
                    payloadLength/=2;
                    "TS_ASSERT_EQUALS(GCM.getLength(),"+payloadLength+");"
                }»
    // Testing the payload of the resulting CAN message
                TS_ASSERT_EQUALS(GCM.getData(),static_cast<uint64_t>(«test.CANMessageDescriptions.get(0).payload»));
    }
                «ELSE»
            std::cerr<<"Warning: Multiple CAN messages for one mapping are not supported."<<std::endl;
                «ENDIF»
            «ENDIF»
        «ENDFOR»
    }
};

#endif /*CANMAPPINGTESTSUITE_«mapping.mappingName.split('\\.').get(mapping.mappingName.split('\\.').size-1).toUpperCase»_H_*/
'''
}
