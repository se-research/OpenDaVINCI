/**
 * DataStructureGenerator- IDL tool to describe exchangeable data.
 * Copyright (C) 2014 - 2015 Christian Berger
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

package org.opendavinci.generator;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.Resource.Diagnostic;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.xtext.generator.IFileSystemAccess;
import org.eclipse.xtext.generator.IGenerator;
import org.eclipse.xtext.util.CancelIndicator;
import org.eclipse.xtext.validation.NamesAreUniqueValidationHelper;
import org.eclipse.xtext.validation.NamesAreUniqueValidator;
import org.opendavinci.DataModelStandaloneSetup;
import org.opendavinci.dataModel.Attribute;
import org.opendavinci.dataModel.ListDeclaration;
import org.opendavinci.dataModel.MapDeclaration;
import org.opendavinci.dataModel.Message;
import org.opendavinci.dataModel.ScalarDeclaration;

import com.google.inject.Injector;

public class DataStructureGenerator {
    public static boolean appendGeneratedHeadersFile = false;
	public List<String> listOfGeneratedHeaderFiles = new ArrayList<String>();
	
	public class MyNamesAreUniqueValidator extends NamesAreUniqueValidator {
		private String fileName;
		private List<String> listOfClashingNames = new ArrayList<String>();
		
		public MyNamesAreUniqueValidator(String fileName) {
			this.fileName = fileName;
		}
		
		public boolean hasUniqueNamesOnly() {
			boolean uniqueNamesOnly = true;
			List<String> checkedListOfClashingNames = new ArrayList<String>();
			for(String s : listOfClashingNames) {
				if (checkedListOfClashingNames.contains(s)) {
					System.err.println("Error while parsing '" + fileName + "': Duplicate entry " + s + " found.");
					uniqueNamesOnly = false;
				}
				else {
					checkedListOfClashingNames.add(s);
				}
			}
			return uniqueNamesOnly;
		}
		
		public void acceptError(String message, EObject object, EStructuralFeature feature, int index, String code,
				String... issueData) {
			if (object instanceof ScalarDeclaration) {
				ScalarDeclaration att = (ScalarDeclaration)object;
				Message mes = (Message)att.eContainer().eContainer();
				listOfClashingNames.add(mes.getMessage().toString() + "." + att.getName());
			}
			if (object instanceof ListDeclaration) {
				ListDeclaration att = (ListDeclaration)object;
				Message mes = (Message)att.eContainer().eContainer();
				listOfClashingNames.add(mes.getMessage().toString() + "." + att.getName());
			}
			if (object instanceof MapDeclaration) {
				MapDeclaration att = (MapDeclaration)object;
				Message mes = (Message)att.eContainer().eContainer();
				listOfClashingNames.add(mes.getMessage().toString() + "." + att.getName());
			}
		}
	}
	
	public class FileSystemAccessWriter implements IFileSystemAccess {
		@Override
		public void generateFile(String fileName, CharSequence contents) {
			String filenameWithSubpackage = fileName.replaceAll("\\.", "/");
			filenameWithSubpackage = filenameWithSubpackage.replaceAll("/h$", ".h");
			filenameWithSubpackage = filenameWithSubpackage.replaceAll("/cpp$", ".cpp");
			System.out.print("Creating '" + folder + "/" + filenameWithSubpackage + "' ");
			if (filenameWithSubpackage.contains("/")) {
				File d = new File(folder + "/" + filenameWithSubpackage.substring(0, filenameWithSubpackage.lastIndexOf('/')));
				d.mkdirs();
			}
			File f = new File(folder + "/" + filenameWithSubpackage);
			FileWriter fw;
			try {
				fw = new FileWriter(f);
				fw.append(contents);
				fw.flush();
				fw.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
            if (filenameWithSubpackage.endsWith(".h")) {
                if (!filenameWithSubpackage.startsWith("testsuites/")) {
                	listOfGeneratedHeaderFiles.add(filenameWithSubpackage);
                }
            }
			System.out.println("done.");
		}

		@Override
		public void generateFile(String fileName,
				String outputConfigurationName, CharSequence contents) {
			System.out.println("generateFile(String fileName, String outputConfigurationName, CharSequence contents) is not implemented yet.");
		}

		@Override
		public void deleteFile(String fileName) {
			System.out.println("deleteFile(String fileName) is not implemented yet.");
		}
	}
	
	private String folder = null;
    private String odvdFilename = null;
	
	public DataStructureGenerator(String folder, String odvdFilename) {
		this.folder = folder;
        this.odvdFilename = odvdFilename;
		
		File d = new File(this.folder);
		d.mkdir();
	}
	
	public void generateSuperHeaderFile() {
		StringBuilder sb = new StringBuilder();
		sb.append("/*"); sb.append("\r\n");
		sb.append(" * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN."); sb.append("\r\n");
		sb.append(" */"); sb.append("\r\n");
        sb.append("\r\n");

        for(String file : listOfGeneratedHeaderFiles) {
    		sb.append("#include \"" + file.replaceFirst("include/", "") + "\""); sb.append("\r\n");
        }

		System.out.print((DataStructureGenerator.appendGeneratedHeadersFile ? "Appending" : "Creating") + " '" + folder + "/include/GeneratedHeaders_" + odvdFilename + ".h' ");
		File f = new File(folder + "/include/GeneratedHeaders_" + odvdFilename + ".h");
		FileWriter fw;
		try {
			fw = new FileWriter(f, DataStructureGenerator.appendGeneratedHeadersFile);
			fw.append(sb.toString());
			fw.flush();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("done.");
    }

	public void generateCMakeModules() {
		System.out.print("Creating '" + folder + "/cmake.Modules' ");
		File d = new File(folder + "/cmake.Modules");
		d.mkdir();
		System.out.println("done.");

        generateCMakeModulesCompileFlags();
        generateCMakeModulesCheckCxxTestEnvironment();
        generateCMakeModulesFindLibrary();
    }

	public void generateCMakeModulesCompileFlags() {
		StringBuilder sb = new StringBuilder();

		sb.append("# DataStructureGenerator- IDL tool to describe exchangeable data."); sb.append("\r\n");
		sb.append("# Copyright (C) 2008 - 2015  Christian Berger"); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is free software; you can redistribute it and/or"); sb.append("\r\n");
		sb.append("# modify it under the terms of the GNU General Public License"); sb.append("\r\n");
		sb.append("# as published by the Free Software Foundation; either version 2"); sb.append("\r\n");
		sb.append("# of the License, or (at your option) any later version."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is distributed in the hope that it will be useful,"); sb.append("\r\n");
		sb.append("# but WITHOUT ANY WARRANTY; without even the implied warranty of"); sb.append("\r\n");
		sb.append("# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"); sb.append("\r\n");
		sb.append("# GNU General Public License for more details."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# You should have received a copy of the GNU General Public License"); sb.append("\r\n");
		sb.append("# along with this program; if not, write to the Free Software"); sb.append("\r\n");
		sb.append("# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."); sb.append("\r\n");

                sb.append("IF(WIN32)"); sb.append("\r\n");
                sb.append("    ADD_DEFINITIONS(-DNOMINMAX)"); sb.append("\r\n");
                sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("IF(UNIX)"); sb.append("\r\n");
                sb.append("    IF(\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\")"); sb.append("\r\n");
                sb.append("        SET(CMAKE_MACOSX_RPATH 1)"); sb.append("\r\n");
                sb.append("    ENDIF()"); sb.append("\r\n");
		sb.append("    SET (CXX_OPTIONS       \"-Wno-deprecated -Wall -Wshadow -Wextra -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wpacked\")"); sb.append("\r\n");
		sb.append("    SET (CXX_OPTION_ANSI   \"-ansi\")"); sb.append("\r\n");
		sb.append("    SET (CXX_EFFECTIVE_CXX \"-Wmissing-format-attribute -Wredundant-decls -Weffc++\")"); sb.append("\r\n");
		sb.append("    SET (CXX_UNINITIALIZED \"-Wno-maybe-uninitialized -Wno-error=unused-result\")"); sb.append("\r\n");

		sb.append("    # Remove \"-ansi\" flag for clang on Darwin."); sb.append("\r\n");
		sb.append("    IF(    (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\")"); sb.append("\r\n");
		sb.append("       AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"FreeBSD\")"); sb.append("\r\n");
		sb.append("       AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"NetBSD\")"); sb.append("\r\n");
		sb.append("       AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"DragonFly\")"); sb.append("\r\n");
		sb.append("       AND (NOT \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\") )"); sb.append("\r\n");
		sb.append("        SET (CXX_OPTIONS \"${CXX_OPTIONS} ${CXX_OPTION_ANSI}\")"); sb.append("\r\n");
		sb.append("    ENDIF()"); sb.append("\r\n");

		sb.append("    # Additionally, test for Effective C++ warnings except on OpenBSD."); sb.append("\r\n");
		sb.append("    IF(NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"OpenBSD\")"); sb.append("\r\n");
		sb.append("        SET (CXX_OPTIONS \"${CXX_OPTIONS} ${CXX_EFFECTIVE_CXX}\")"); sb.append("\r\n");

		sb.append("        # Remove \"-Wno-maybe-uninitialized -Wno-error=unused-result\" flag on FreeBSD and MacOSX or where the GCC is not 4.7+"); sb.append("\r\n");
		sb.append("        IF(    (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\")"); sb.append("\r\n");
		sb.append("           AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"NetBSD\")"); sb.append("\r\n");
		sb.append("           AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"FreeBSD\")"); sb.append("\r\n");
		sb.append("           AND (NOT \"${ARMHF}\" STREQUAL \"YES\") )"); sb.append("\r\n");

		sb.append("            # Check for GCC version."); sb.append("\r\n");
		sb.append("            EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)"); sb.append("\r\n");

		sb.append("            IF (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)"); sb.append("\r\n");
		sb.append("                SET (CXX_OPTIONS \"${CXX_OPTIONS} ${CXX_UNINITIALIZED}\")"); sb.append("\r\n");
		sb.append("            ENDIF()"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");
		sb.append("    ENDIF()"); sb.append("\r\n");

		sb.append("    SET (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} \" -fPIC\")"); sb.append("\r\n");
		sb.append("    SET (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} \" -fPIC ${CXX_OPTIONS} -pipe\")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		System.out.print("Creating '" + folder + "/cmake.Modules/CompileFlags.cmake' ");
		File f = new File(folder + "/" + "cmake.Modules/CompileFlags.cmake");
		FileWriter fw;
		try {
			fw = new FileWriter(f);
			fw.append(sb.toString());
			fw.flush();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("done.");
	}

	public void generateCMakeModulesCheckCxxTestEnvironment() {
		StringBuilder sb = new StringBuilder();

		sb.append("# DataStructureGenerator- IDL tool to describe exchangeable data."); sb.append("\r\n");
		sb.append("# Copyright (C) 2008 - 2015  Christian Berger"); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is free software; you can redistribute it and/or"); sb.append("\r\n");
		sb.append("# modify it under the terms of the GNU General Public License"); sb.append("\r\n");
		sb.append("# as published by the Free Software Foundation; either version 2"); sb.append("\r\n");
		sb.append("# of the License, or (at your option) any later version."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is distributed in the hope that it will be useful,"); sb.append("\r\n");
		sb.append("# but WITHOUT ANY WARRANTY; without even the implied warranty of"); sb.append("\r\n");
		sb.append("# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"); sb.append("\r\n");
		sb.append("# GNU General Public License for more details."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# You should have received a copy of the GNU General Public License"); sb.append("\r\n");
		sb.append("# along with this program; if not, write to the Free Software"); sb.append("\r\n");
		sb.append("# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."); sb.append("\r\n");

		sb.append("FIND_PACKAGE (PythonInterp)"); sb.append("\r\n");

		sb.append("IF(PYTHONINTERP_FOUND)"); sb.append("\r\n");
		sb.append("    SET (CXXTEST_TESTGEN_ARGS --xunit-printer --have-eh)"); sb.append("\r\n");
		sb.append("    SET (CXXTEST_USE_PYTHON true)"); sb.append("\r\n");
		sb.append("    SET (CXXTEST_PYTHON_INTERPRETER \"${PYTHON_EXECUTABLE}\")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Next, find CxxTest (shipped with the distribution)."); sb.append("\r\n");
		sb.append("FIND_PACKAGE(CxxTest)"); sb.append("\r\n");
		sb.append("IF(CXXTEST_FOUND)"); sb.append("\r\n");
		sb.append("    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})"); sb.append("\r\n");
		sb.append("    ENABLE_TESTING()"); sb.append("\r\n");
		sb.append("    MESSAGE(STATUS \"Found CxxTest: Compiling and running test suites enabled.\")"); sb.append("\r\n");
		sb.append("ENDIF(CXXTEST_FOUND)"); sb.append("\r\n");

		System.out.print("Creating '" + folder + "/cmake.Modules/CheckCxxTestEnvironment.cmake' ");
		File f = new File(folder + "/" + "cmake.Modules/CheckCxxTestEnvironment.cmake");
		FileWriter fw;
		try {
			fw = new FileWriter(f);
			fw.append(sb.toString());
			fw.flush();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("done.");
	}

	public void generateCMakeFile() {
		StringBuilder sb = new StringBuilder();
		sb.append("# DataStructureGenerator- IDL tool to describe exchangeable data."); sb.append("\r\n");
		sb.append("# Copyright (C) 2008 - 2015  Christian Berger"); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is free software; you can redistribute it and/or"); sb.append("\r\n");
		sb.append("# modify it under the terms of the GNU General Public License"); sb.append("\r\n");
		sb.append("# as published by the Free Software Foundation; either version 2"); sb.append("\r\n");
		sb.append("# of the License, or (at your option) any later version."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# This program is distributed in the hope that it will be useful,"); sb.append("\r\n");
		sb.append("# but WITHOUT ANY WARRANTY; without even the implied warranty of"); sb.append("\r\n");
		sb.append("# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"); sb.append("\r\n");
		sb.append("# GNU General Public License for more details."); sb.append("\r\n");
		sb.append("#"); sb.append("\r\n");
		sb.append("# You should have received a copy of the GNU General Public License"); sb.append("\r\n");
		sb.append("# along with this program; if not, write to the Free Software"); sb.append("\r\n");
		sb.append("# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."); sb.append("\r\n");

		sb.append("CMAKE_MINIMUM_REQUIRED (VERSION 2.8)"); sb.append("\r\n");

		sb.append("PROJECT (" + folder + ")"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Set the search path for .cmake files."); sb.append("\r\n");
		sb.append("SET (CMAKE_MODULE_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules\" ${CMAKE_MODULE_PATH})"); sb.append("\r\n");

		sb.append("# Add a local CMake module search path dependent on the desired installation destination."); sb.append("\r\n");
		sb.append("# Thus, artifacts from the complete source build can be given precendence over any installed versions."); sb.append("\r\n");
		sb.append("IF(UNIX)"); sb.append("\r\n");
		sb.append("    SET (CMAKE_MODULE_PATH \"${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules\" ${CMAKE_MODULE_PATH})"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");
		sb.append("IF(WIN32)"); sb.append("\r\n");
		sb.append("    SET (CMAKE_MODULE_PATH \"${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules\" ${CMAKE_MODULE_PATH})"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Include flags for compiling."); sb.append("\r\n");
		sb.append("INCLUDE (CompileFlags)"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Find and configure CxxTest."); sb.append("\r\n");
		sb.append("IF(\"${CXXTEST_INCLUDE_DIR}\" STREQUAL \"\")"); sb.append("\r\n");
		sb.append("    SET (CXXTEST_INCLUDE_DIR \"${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest\")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");
		sb.append("INCLUDE (CheckCxxTestEnvironment)"); sb.append("\r\n");

		sb.append("IF(\"${OPENDAVINCI_DIR}\" STREQUAL \"\")"); sb.append("\r\n");
		sb.append("    SET(OPENDAVINCI_DIR \"${CMAKE_INSTALL_PREFIX}\")"); sb.append("\r\n");
		sb.append("ELSE()"); sb.append("\r\n");
		sb.append("    SET(CMAKE_MODULE_PATH \"${OPENDAVINCI_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules\" ${CMAKE_MODULE_PATH})"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");
		sb.append("FIND_PACKAGE (OpenDaVINCI REQUIRED)"); sb.append("\r\n");

		sb.append("# Include directories from core."); sb.append("\r\n");
		sb.append("INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci)"); sb.append("\r\n");
		sb.append("INCLUDE_DIRECTORIES (include)"); sb.append("\r\n");

		sb.append("# Recipe for building " + folder + "."); sb.append("\r\n");
		sb.append("FILE(GLOB_RECURSE " + folder + "-sources \"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp\")"); sb.append("\r\n");

		sb.append("ADD_LIBRARY (" + folder.replaceFirst("lib", "") + "-core OBJECT ${" + folder + "-sources})"); sb.append("\r\n");
		sb.append("ADD_LIBRARY (" + folder.replaceFirst("lib", "") + "-static STATIC $<TARGET_OBJECTS:" + folder.replaceFirst("lib", "") + "-core>)"); sb.append("\r\n");
		sb.append("IF(    (NOT WIN32)"); sb.append("\r\n");
		sb.append("   AND (NOT (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\")) )"); sb.append("\r\n");
		sb.append("    ADD_LIBRARY (" + folder.replaceFirst("lib", "") + " SHARED $<TARGET_OBJECTS:" + folder.replaceFirst("lib", "") + "-core>)"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("# Installing " + folder + "."); sb.append("\r\n");
		sb.append("INSTALL(TARGETS " + folder.replaceFirst("lib", "") + "-static DESTINATION lib" + " " + "COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("IF(    (NOT WIN32)"); sb.append("\r\n");
                sb.append("   AND (NOT (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\")) )"); sb.append("\r\n");
		sb.append("    INSTALL(TARGETS " + folder.replaceFirst("lib", "") + " DESTINATION lib" + " " + "COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("# Install header files."); sb.append("\r\n");
		sb.append("INSTALL(DIRECTORY \"${CMAKE_CURRENT_SOURCE_DIR}/include/\" DESTINATION include/" + folder.replaceFirst("lib", "") + " " + "COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");

		sb.append("IF(CXXTEST_FOUND)"); sb.append("\r\n");
		sb.append("FILE(GLOB " + folder + "-testsuites \"${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h\")"); sb.append("\r\n");

		sb.append("# Install CMake modules locally."); sb.append("\r\n");
		sb.append("IF(UNIX)"); sb.append("\r\n");
		sb.append("    INSTALL(FILES \"${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/Find" + odvdFilename + ".cmake\" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" + " COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("    INSTALL(FILES \"${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/Find" + odvdFilename + ".cmake\" DESTINATION share/cmake-2.8/Modules" + " COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("    INSTALL(FILES \"${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/Find" + odvdFilename + ".cmake\" DESTINATION share/cmake-3.0/Modules" + " COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");
		sb.append("IF(WIN32)"); sb.append("\r\n");
		sb.append("    INSTALL(FILES \"${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/Find" + odvdFilename + ".cmake\" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" + " COMPONENT od" + folder.replaceFirst("lib", "") + "lib" + ")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("FOREACH(testsuite ${" + folder + "-testsuites})"); sb.append("\r\n");
		sb.append("    STRING(REPLACE \"/\" \";\" testsuite-list ${testsuite})"); sb.append("\r\n");

		sb.append("    LIST(LENGTH testsuite-list len)"); sb.append("\r\n");
		sb.append("    MATH(EXPR lastItem \"${len}-1\")"); sb.append("\r\n");
		sb.append("    LIST(GET testsuite-list \"${lastItem}\" testsuite-short)"); sb.append("\r\n");

		sb.append("        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})"); sb.append("\r\n");
		sb.append("        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})"); sb.append("\r\n");
		sb.append("        IF(UNIX)"); sb.append("\r\n");
		sb.append("            IF( (   (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Linux\")"); sb.append("\r\n");
		sb.append("                 OR (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"FreeBSD\")"); sb.append("\r\n");
		sb.append("                 OR (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"DragonFly\") )"); sb.append("\r\n");
		sb.append("                 AND (NOT \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\") )"); sb.append("\r\n");
		sb.append("                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS \"-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn\")"); sb.append("\r\n");
		sb.append("            ELSE()"); sb.append("\r\n");
		sb.append("                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS \"-Wno-effc++ -Wno-float-equal\")"); sb.append("\r\n");
		sb.append("            ENDIF()"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");

		sb.append("        IF(WIN32)"); sb.append("\r\n");
		sb.append("            SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS \"\")"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");

		sb.append("        IF(   WIN32"); sb.append("\r\n");
                sb.append("           OR (\"${CMAKE_SYSTEM_NAME}\" STREQUAL \"Darwin\") )"); sb.append("\r\n");
		sb.append("            TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite " + folder.replaceFirst("lib", "") + "-static ${OPENDAVINCI_LIBRARIES})"); sb.append("\r\n");
		sb.append("        ELSE()"); sb.append("\r\n");
		sb.append("            TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite " + folder.replaceFirst("lib", "") + " ${OPENDAVINCI_LIBRARIES})"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");
		sb.append("    ENDFOREACH()"); sb.append("\r\n");
		sb.append("ENDIF(CXXTEST_FOUND)"); sb.append("\r\n");

		sb.append("IF(    (UNIX)"); sb.append("\r\n");
		sb.append("   AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"DragonFly\")"); sb.append("\r\n");
		sb.append("   AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"OpenBSD\")"); sb.append("\r\n");
		sb.append("   AND (NOT \"${CMAKE_SYSTEM_NAME}\" STREQUAL \"NetBSD\") )"); sb.append("\r\n");
		sb.append("    SET(CPACK_GENERATOR \"DEB;RPM\")"); sb.append("\r\n");

		sb.append("    SET(CPACK_PACKAGE_CONTACT \"First name Last name\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_VENDOR \"${CPACK_PACKAGE_CONTACT}\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY \"This is a " + folder + ", a library containing data structures for distributed software systems realized with OpenDaVINCI.\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_NAME " + folder + ")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_VERSION_MAJOR \"1\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_VERSION_MINOR \"0\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_VERSION_PATCH \"0\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_VERSION \"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_COMPONENTS_ALL od" + folder.replaceFirst("lib", "") + "lib)"); sb.append("\r\n");

		sb.append("    # Debian packages:"); sb.append("\r\n");
		sb.append("    SET(CPACK_DEBIAN_PACKAGE_SECTION \"devel\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_DEBIAN_PACKAGE_PRIORITY \"optional\")"); sb.append("\r\n");
		sb.append("    IF(\"${ARMHF}\" STREQUAL \"YES\")"); sb.append("\r\n");
		sb.append("        SET(ARCH \"armhf\")"); sb.append("\r\n");
		sb.append("    ELSE()"); sb.append("\r\n");
		sb.append("        IF(\"${CMAKE_SIZEOF_VOID_P}\" STREQUAL \"8\")"); sb.append("\r\n");
		sb.append("            SET(ARCH \"amd64\")"); sb.append("\r\n");
		sb.append("        ELSE()"); sb.append("\r\n");
		sb.append("            SET(ARCH \"i386\")"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");
		sb.append("    ENDIF()"); sb.append("\r\n");
		sb.append("    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE \"${ARCH}\")"); sb.append("\r\n");
		sb.append("#    SET(CPACK_DEB_COMPONENT_INSTALL ON)"); sb.append("\r\n");
		sb.append("    SET(CPACK_DEBIAN_PACKAGE_DEPENDS \"ant,default-jre,default-jdk\")"); sb.append("\r\n");

		sb.append("    # RPM packages:"); sb.append("\r\n");
		sb.append("    IF(\"${ARMHF}\" STREQUAL \"YES\")"); sb.append("\r\n");
		sb.append("        SET(ARCH \"armhf\")"); sb.append("\r\n");
		sb.append("        SET(CPACK_RPM_PACKAGE_PROVIDES \"" + folder + ".so()(armhf)\")"); sb.append("\r\n");
		sb.append("    ELSE()"); sb.append("\r\n");
		sb.append("        IF(\"${CMAKE_SIZEOF_VOID_P}\" STREQUAL \"8\")"); sb.append("\r\n");
		sb.append("            SET(ARCH \"x86_64\")"); sb.append("\r\n");
		sb.append("            SET(CPACK_RPM_PACKAGE_PROVIDES \"" + folder + ".so()(64bit)\")"); sb.append("\r\n");
		sb.append("        ELSE()"); sb.append("\r\n");
		sb.append("            SET(ARCH \"i686\")"); sb.append("\r\n");
		sb.append("            SET(CPACK_RPM_PACKAGE_PROVIDES \"" + folder + ".so\")"); sb.append("\r\n");
		sb.append("        ENDIF()"); sb.append("\r\n");
		sb.append("    ENDIF()"); sb.append("\r\n");
		sb.append("    SET(CPACK_RPM_PACKAGE_BUILDARCH \"Buildarch: ${CPACK_RPM_PACKAGE_ARCHITECTURE}\")"); sb.append("\r\n");
		sb.append("#    SET(CPACK_RPM_COMPONENT_INSTALL ON)"); sb.append("\r\n");
		sb.append("    SET(CPACK_RPM_PACKAGE_LICENSE \"LGPL\")"); sb.append("\r\n");
		sb.append("    SET(CPACK_RPM_PACKAGE_DEPENDS \"ant\")"); sb.append("\r\n");
		sb.append("    # Resulting package name:"); sb.append("\r\n");
		sb.append("    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("INCLUDE(CPack)"); sb.append("\r\n");

		System.out.print("Creating '" + folder + "/CMakeLists.txt' ");
		File f = new File(folder + "/" + "CMakeLists.txt");
		FileWriter fw;
		try {
			fw = new FileWriter(f);
			fw.append(sb.toString());
			fw.flush();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("done.");
	}

	public void generateCMakeModulesFindLibrary() {
		StringBuilder sb = new StringBuilder();

		sb.append("# " + odvdFilename + " - Data structure library generated by DataStructureGenerator."); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Try to find " + odvdFilename + " library."); sb.append("\r\n");

		sb.append("# The user can specify an additional search path using the CMake variable"); sb.append("\r\n");
		sb.append("# " + odvdFilename.toUpperCase() + "_DIR"); sb.append("\r\n");

		sb.append("# First, search at the specific user path setting."); sb.append("\r\n");
		sb.append("IF(NOT (\"${" + odvdFilename.toUpperCase() + "_DIR}\" STREQUAL \"\"))"); sb.append("\r\n");
		sb.append("    FIND_PATH(" + odvdFilename.toUpperCase() + "_INCLUDE_DIR " + odvdFilename.toLowerCase() + "/GeneratedHeaders_" + odvdFilename + ".h"); sb.append("\r\n");
		sb.append("                 NAMES " + odvdFilename.toLowerCase()); sb.append("\r\n");
		sb.append("                 PATHS ${" + odvdFilename.toUpperCase() + "_DIR}/include"); sb.append("\r\n");
		sb.append("                 NO_DEFAULT_PATH)"); sb.append("\r\n");

		sb.append("    FIND_LIBRARY(" + odvdFilename.toUpperCase() + "_LIBRARY"); sb.append("\r\n");
		sb.append("                 NAMES " + odvdFilename.toLowerCase() + " " + odvdFilename.toLowerCase() + "-static"); sb.append("\r\n");
		sb.append("                 PATHS ${" + odvdFilename.toUpperCase() + "_DIR}/lib"); sb.append("\r\n");
		sb.append("                 NO_DEFAULT_PATH)"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");
		sb.append("IF(   (\"${" + odvdFilename.toUpperCase() + "_INCLUDE_DIR}\" STREQUAL \"" + odvdFilename.toUpperCase() + "_INCLUDE_DIR-NOTFOUND\")"); sb.append("\r\n");
		sb.append("   OR (\"${" + odvdFilename.toUpperCase() + "_DIR}\" STREQUAL \"\") )"); sb.append("\r\n");
		sb.append("    MESSAGE(STATUS \"Trying to find " + odvdFilename + " in default paths.\")"); sb.append("\r\n");
		sb.append("    # If not found, use the system's search paths."); sb.append("\r\n");
		sb.append("    FIND_PATH(" + odvdFilename.toUpperCase() + "_INCLUDE_DIR " + odvdFilename.toLowerCase() + "/GeneratedHeaders_" + odvdFilename + ".h"); sb.append("\r\n");
		sb.append("                 NAMES " + odvdFilename.toLowerCase()); sb.append("\r\n");
		sb.append("                 PATHS /usr/include"); sb.append("\r\n");
		sb.append("                       /usr/local/include)"); sb.append("\r\n");

		sb.append("    FIND_LIBRARY(" + odvdFilename.toUpperCase() + "_LIBRARY"); sb.append("\r\n");
		sb.append("                 NAMES " + odvdFilename.toLowerCase() + " " + odvdFilename.toLowerCase() + "-static"); sb.append("\r\n");
		sb.append("                 PATHS /usr/lib"); sb.append("\r\n");
		sb.append("                       /usr/lib64"); sb.append("\r\n");
		sb.append("                       /usr/local/lib"); sb.append("\r\n");
		sb.append("                       /usr/local/lib64)"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("IF(\"${" + odvdFilename.toUpperCase() + "_INCLUDE_DIR}\" STREQUAL \"\")"); sb.append("\r\n");
		sb.append("    MESSAGE(FATAL_ERROR \"Could not find " + odvdFilename + " library.\")"); sb.append("\r\n");
		sb.append("ENDIF()"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("# Set linking libraries."); sb.append("\r\n");
		sb.append("SET(" + odvdFilename.toUpperCase() + "_LIBRARIES ${" + odvdFilename.toUpperCase() + "_LIBRARY})"); sb.append("\r\n");
		sb.append("SET(" + odvdFilename.toUpperCase() + "_INCLUDE_DIRS ${" + odvdFilename.toUpperCase() + "_INCLUDE_DIR})"); sb.append("\r\n");

		sb.append("###########################################################################"); sb.append("\r\n");
		sb.append("INCLUDE(FindPackageHandleStandardArgs)"); sb.append("\r\n");
		sb.append("FIND_PACKAGE_HANDLE_STANDARD_ARGS(Lib" + odvdFilename + " DEFAULT_MSG"); sb.append("\r\n");
		sb.append("                                  " + odvdFilename.toUpperCase() + "_LIBRARY " + odvdFilename.toUpperCase() + "_INCLUDE_DIR)"); sb.append("\r\n");
		sb.append("MARK_AS_ADVANCED(" + odvdFilename.toUpperCase() + "_INCLUDE_DIR " + odvdFilename.toUpperCase() + "_LIBRARY)"); sb.append("\r\n");

		System.out.print("Creating '" + folder + "/cmake.Modules/Find" + odvdFilename + ".cmake' ");
		File f = new File(folder + "/" + "cmake.Modules/Find" + odvdFilename + ".cmake");
		FileWriter fw;
		try {
			fw = new FileWriter(f);
			fw.append(sb.toString());
			fw.flush();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("done.");
	}
	
	public static int process(String[] args) throws FileNotFoundException, IOException {
		// Assume that no error will happen.
		int retVal = 0;

		if (args == null) {
			System.out.println("Run with java -jar odDataStructureGenerator-latest.jar [--withCMake] [--appendGeneratedHeadersFile] MyDataStructure.odvd");
			retVal = -1; // No file given.
			return retVal;
		}
		
	    // Register the EMF for our DSL.
        Injector injector = new DataModelStandaloneSetup().createInjectorAndDoEMFRegistration();
        ResourceSet rs = new ResourceSetImpl();

        // Loop through command line arguments.
        String odvdFile = "";
        boolean createCMakeFile = false;
        for(String s : args) {
        	if (s.equalsIgnoreCase("--withcmake")) {
        		createCMakeFile = true;
                continue;
        	}
        	if (s.equalsIgnoreCase("--appendgeneratedheadersfile")) {
        		DataStructureGenerator.appendGeneratedHeadersFile = true;
                continue;
        	}
        	if (s.toLowerCase().endsWith(".odvd")) {
        		odvdFile = s;
                continue;
        	}
        }
		if (odvdFile.length() == 0) {
			System.out.println("Run with java -jar odDataStructureGenerator-latest.jar [--withCMake] [--appendGeneratedHeadersFile] MyDataStructure.odvd");
			retVal = -1; // Not file given.
		}
		else {
			File file = new File(odvdFile);
			if (file.exists()) {
				if (file.canRead()) {
			        Resource resource = rs.getResource(URI.createURI(file.toURI().toString()), true);
			        
			        if (resource.getErrors().isEmpty()) {
			        	if (resource.getWarnings().isEmpty()) {
			        		// Library folder structure is only created when CMakeLists.txt is also generated; otherwise, it is assumed that the include/generated and src/generated folders are nested somewhere.
			                String library = null;
                            String filename = file.getName().replaceAll("\\.odvd", "");
			        		if (createCMakeFile) {
			            		library = new String("lib" + filename.toLowerCase());
			        		}
			        		else {
			        			library = new String(".");
			        		}
			        		
					        // File access to write the data.
					        DataStructureGenerator dsg = new DataStructureGenerator(library, filename);
					        DataStructureGenerator.FileSystemAccessWriter fileAccess = dsg.new FileSystemAccessWriter();

				        	// Check for unique names.
					        DataStructureGenerator.MyNamesAreUniqueValidator uniqueNames = dsg.new MyNamesAreUniqueValidator(file.getName());
					        NamesAreUniqueValidationHelper helper = new NamesAreUniqueValidationHelper();
					        uniqueNames.setHelper(helper);
					        uniqueNames.doCheckUniqueNames(resource, CancelIndicator.NullImpl);
					        
					        if (uniqueNames.hasUniqueNamesOnly()) {
						        // Setup the generator for the data structure.
						        IGenerator dataStructureGenerator = injector.getInstance(DataModelGenerator.class);        
						        dataStructureGenerator.doGenerate(resource, fileAccess);

						        // Generate super header file.
                                dsg.generateSuperHeaderFile();

						        if (createCMakeFile) {
						        	dsg.generateCMakeFile();
                                    dsg.generateCMakeModules();
						        }
						        
						        // Generating the .h, .cpp, and CMakeLists.txt was successful.
						        retVal = 0;
					        }
					        else {
								retVal = -6; // Duplicate names found while processing the given .odvd.
					        }
			        	}
			        	else {
					        for(Diagnostic diagnostic : resource.getWarnings()) {
					        	System.err.println("Warning while parsing '" + file.getName() + "' in line " + diagnostic.getLine() + ": " + diagnostic.getMessage());
					        }
							retVal = -5; // Warning while parsing the given .odvd.
			        	}
			        }
			        else {
				        for(Diagnostic diagnostic : resource.getErrors()) {
				        	System.err.println("Error while parsing '" + file.getName() + "' in line " + diagnostic.getLine() + ": " + diagnostic.getMessage());
				        }
						retVal = -4; // Error while parsing the given .odvd.
			        }
				}
				else {
					System.err.println("Error: '" + file.getName() + "' is not readable.");
					retVal = -3; // File does not end with .odvd.
				}
			}
			else {
				System.err.println("Error: '" + file.getName() + "' does not exist.");
				retVal = -2; // File does not exist.
			}
		}
		
		return retVal;
	}

	public static void main(String[] args) throws FileNotFoundException, IOException  {
		System.exit(process(args));
    }
}
