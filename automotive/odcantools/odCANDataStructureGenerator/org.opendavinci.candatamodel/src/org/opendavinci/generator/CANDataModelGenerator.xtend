/**
 * CANDataStructureGenerator - IDL tool to describe the mapping from
 *                             CAN data to high-level messages.
 * Copyright (C) 2015 Christian Berger
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
import org.opendavinci.canDataModel.CANSignalMapping

class CANDataModelGenerator implements IGenerator {
	
    /* This method is our interface to an outside caller. */
	override void doGenerate(Resource resource, IFileSystemAccess fsa) {
		val generatedHeadersFile = resource.URI.toString().substring(resource.URI.toString().lastIndexOf("/") + 1).replaceAll(".odvd", "")
		for (e : resource.allContents.toIterable.filter(typeof(CANSignalMapping))) {
			fsa.generateFile("include/generated/" + e.message.toString().replaceAll("\\.", "/") + ".h", generateHeaderFileContent(generatedHeadersFile, e))
			fsa.generateFile("src/generated/" + e.message.toString().replaceAll("\\.", "/") + ".cpp", generateImplementationFileContent(e, "generated"))
			fsa.generateFile("testsuites/" + e.message.toString().replaceAll("\\.", "_") + "TestSuite.h", generateTestSuiteContent(e, generatedHeadersFile))
		}
	}

    /* This method generates the header file content. */
	def generateHeaderFileContent(String generatedHeadersFile, CANSignalMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: «mapping.message.toString»
'''

	/* This method generates the implementation (.cpp). */
	def generateImplementationFileContent(CANSignalMapping mapping, String includeDirectoryPrefix) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Source file for: «mapping.message.toString»
'''

	// Generate the test suite content (.h).	
	def generateTestSuiteContent(CANSignalMapping mapping, String generatedHeadersFile) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Test suite file for: «mapping.message.toString»
'''
}
