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

package org.opendavinci.test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.Ignore;
import org.junit.Test;
import org.opendavinci.generator.DataStructureGenerator;

public class DataStructureGeneratorTest {

	String PATH_FOR_INPUT_FILES = this.getClass().getClassLoader().getResource("").getPath() + "../test/odvd/";
	String PATH_FOR_REFERENCE_FILES = this.getClass().getClassLoader().getResource("").getPath() + "../test/odvd/reference/";
	String PATH_FOR_GENERATED_FILES = this.getClass().getClassLoader().getResource("").getPath() + "../";

	@Ignore
	public class Entry {
		public String first = "";
		public String second = "";
		public boolean equal = false;
	}

	@Ignore
	public class TestDataSet {
		private int expectedRetVal = 0;
		private boolean withCMake = false;
		private File odvdFile = null;
		private List<File> listOfGeneratedFiles = null;
		private List<String> listOfGeneratedFilesAsString = null;
		private List<File> listOfReferenceFiles = null;

		private HashMap<String, Entry> entriesToCompare = null;

		private boolean successfullyInitialized = true;
		private boolean successfullyGenerated = true;

		public TestDataSet(int expectedRetVal, String odvdFile, boolean withCMake, String[] listOfGeneratedFiles, String[] listOfReferenceFiles) {
			this.expectedRetVal = expectedRetVal;
			
			this.withCMake = withCMake;
			
			this.odvdFile = new File(odvdFile);
			successfullyInitialized &= this.odvdFile.exists() && this.odvdFile.canRead();

			listOfGeneratedFilesAsString = new ArrayList<String>();
			for (String s : listOfGeneratedFiles) {
				listOfGeneratedFilesAsString.add(s);
			}

			this.listOfReferenceFiles = new ArrayList<File>();
			for (String s : listOfReferenceFiles) {
				File f = new File(PATH_FOR_REFERENCE_FILES + s);
				successfullyInitialized &= f.exists() && f.canRead();

				this.listOfReferenceFiles.add(f);
			}
		}
		
		protected void finalize() throws Throwable {
			removeGeneratedFiles();
		}
		
		public String[] get_args() {
			String[] args = new String[(withCMake ? 2 : 1)];
			int id = 0;
			if (withCMake) {
				args[id++] = "--withCMake";
			}
			args[id] = odvdFile.toString();
			
			return args;
		}
		
		public int getExpectedRetVal() {
			return expectedRetVal;
		}

		public boolean isSuccessfullyInitialized() {
			return successfullyInitialized;
		}

		public boolean isSuccessfullyGenerated() {
			if (listOfGeneratedFiles == null) {
				listOfGeneratedFiles = new ArrayList<File>();
				for (String s : listOfGeneratedFilesAsString) {
					File f = new File(PATH_FOR_GENERATED_FILES + s);
					successfullyGenerated &= f.exists() && f.canRead();

					listOfGeneratedFiles.add(f);
				}
			}
			
			return successfullyGenerated;
		}

		public void removeGeneratedFiles() {
			for (File f : listOfGeneratedFiles) {
				if (f.exists()) {
					System.out.println("Removing '" + f.toString() + "'.");
					f.delete();
				}
			}
		}

		public HashMap<String, Entry> getEntriesToCompare() {
			if (entriesToCompare == null) {
				// Read all the data.
				entriesToCompare = new HashMap<String, DataStructureGeneratorTest.Entry>();

				for (File fRef : listOfReferenceFiles) {
					for (File fGen : listOfGeneratedFiles) {
						String sRef = fRef.toString().replaceFirst(PATH_FOR_REFERENCE_FILES, "");
						String sGen = fGen.toString().replaceFirst(PATH_FOR_GENERATED_FILES, "");
						if (sRef.endsWith(sGen)) {
							String desc = "Comparing '" + fRef.toString() + "' with '" + fGen.toString() + "': ";

							Entry p = new Entry();
							p.first = read(fRef);
							p.second = read(fGen);
							p.equal = p.first.equals(p.second);

							entriesToCompare.put(desc, p);
							break;
						}
					}
				}
			}

			return entriesToCompare;
		}

		private String read(File f) {
			StringBuilder sb = new StringBuilder();
			try {
				BufferedReader br = new BufferedReader(new FileReader(f));
				String line = br.readLine();
				while (line != null) {
					sb.append(line);
					sb.append("\r\n");
					line = br.readLine();
				}
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return sb.toString();
		}
	}

	@Test
	public void testNullArgs() {
		try {
			int EXPECTED_RETVAL = -1;
			org.junit.Assert.assertTrue("Test null args given.", DataStructureGenerator.process(null) == EXPECTED_RETVAL);
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void testNoArgs() {
		try {
			int EXPECTED_RETVAL = -1;
			String[] args = new String[0];
			org.junit.Assert.assertTrue("Test no args given.", DataStructureGenerator.process(args) == EXPECTED_RETVAL);
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_odvd_notExists() {
		try {
			int EXPECTED_RETVAL = -2;
			String[] args = new String[1];
			args[0] = "ABC.odvd";
			org.junit.Assert.assertTrue("File " + args[0] + " does not exist test.", DataStructureGenerator.process(args) == EXPECTED_RETVAL);
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_corrupt_odvd() {
		try {
			int EXPECTED_RETVAL = -4;
			String[] args = new String[1];
			args[0] = PATH_FOR_INPUT_FILES + "test1.odvd";
			org.junit.Assert.assertTrue("File " + args[0] + " does not exist test.", DataStructureGenerator.process(args) == EXPECTED_RETVAL);
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_duplicate_entries() {
		try {
			int EXPECTED_RETVAL = -6;
			String[] args = new String[1];
			args[0] = PATH_FOR_INPUT_FILES + "test2-duplicate.odvd";
			org.junit.Assert.assertTrue("File " + args[0] + " with duplicate attributes test.", DataStructureGenerator.process(args) == EXPECTED_RETVAL);
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test2() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test2.odvd",
					withCMake,
					new String[]{"include/test2/generated/Test2.h",
					             "src/generated/Test2.cpp",
					             "include/test2/generated/Test2b.h",
					             "src/generated/Test2b.cpp"},       /* List of generated files. */
		            new String[]{"Test2/include/test2/generated/Test2.h",
            					 "Test2/src/generated/Test2.cpp",
            					 "Test2/include/test2/generated/Test2b.h",
            					 "Test2/src/generated/Test2b.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test2_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test2.odvd",
					withCMake,
					new String[]{"libtest2/CMakeLists.txt",
								 "libtest2/include/test2/generated/Test2.h",
					             "libtest2/src/generated/Test2.cpp",
					             "libtest2/include/test2/generated/Test2b.h",
					             "libtest2/src/generated/Test2b.cpp"},       /* List of generated files. */
		            new String[]{"Test2_withCMake/libtest2/CMakeLists.txt",
								 "Test2_withCMake/libtest2/include/test2/generated/Test2.h",
            					 "Test2_withCMake/libtest2/src/generated/Test2.cpp",
            					 "Test2_withCMake/libtest2/include/test2/generated/Test2b.h",
            					 "Test2_withCMake/libtest2/src/generated/Test2b.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test3() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test3.odvd",
					withCMake,
					new String[]{"include/test3/generated/Test3.h",
					             "src/generated/Test3.cpp"},       /* List of generated files. */
		            new String[]{"Test3/include/test3/generated/Test3.h",
            					 "Test3/src/generated/Test3.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test3_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test3.odvd",
					withCMake,
					new String[]{"libtest3/CMakeLists.txt",
								 "libtest3/include/test3/generated/Test3.h",
					             "libtest3/src/generated/Test3.cpp"},       /* List of generated files. */
		            new String[]{"Test3_withCMake/libtest3/CMakeLists.txt",
								 "Test3_withCMake/libtest3/include/test3/generated/Test3.h",
            					 "Test3_withCMake/libtest3/src/generated/Test3.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test4() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test4.odvd",
					withCMake,
					new String[]{"include/test4/generated/Test4.h",
					             "src/generated/Test4.cpp"},       /* List of generated files. */
		            new String[]{"Test4/include/test4/generated/Test4.h",
            					 "Test4/src/generated/Test4.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test4_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test4.odvd",
					withCMake,
					new String[]{"libtest4/CMakeLists.txt",
								 "libtest4/include/test4/generated/Test4.h",
					             "libtest4/src/generated/Test4.cpp"},       /* List of generated files. */
		            new String[]{"Test4_withCMake/libtest4/CMakeLists.txt",
								 "Test4_withCMake/libtest4/include/test4/generated/Test4.h",
            					 "Test4_withCMake/libtest4/src/generated/Test4.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test5() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test5.odvd",
					withCMake,
					new String[]{"include/test5/generated/testpackage/Test5.h",
					             "src/generated/testpackage/Test5.cpp"},       /* List of generated files. */
		            new String[]{"Test5/include/test5/generated/testpackage/Test5.h",
            					 "Test5/src/generated/testpackage/Test5.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test5_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test5.odvd",
					withCMake,
					new String[]{"libtest5/CMakeLists.txt",
								 "libtest5/include/test5/generated/testpackage/Test5.h",
					             "libtest5/src/generated/testpackage/Test5.cpp"},       /* List of generated files. */
		            new String[]{"Test5_withCMake/libtest5/CMakeLists.txt",
								 "Test5_withCMake/libtest5/include/test5/generated/testpackage/Test5.h",
            					 "Test5_withCMake/libtest5/src/generated/testpackage/Test5.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test6() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test6.odvd",
					withCMake,
					new String[]{"include/test6/generated/testpackage/Test6.h",
					             "src/generated/testpackage/Test6.cpp"},       /* List of generated files. */
		            new String[]{"Test6/include/test6/generated/testpackage/Test6.h",
            					 "Test6/src/generated/testpackage/Test6.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test6_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test6.odvd",
					withCMake,
					new String[]{"libtest6/CMakeLists.txt",
								 "libtest6/include/test6/generated/testpackage/Test6.h",
					             "libtest6/src/generated/testpackage/Test6.cpp"},       /* List of generated files. */
		            new String[]{"Test6_withCMake/libtest6/CMakeLists.txt",
								 "Test6_withCMake/libtest6/include/test6/generated/testpackage/Test6.h",
            					 "Test6_withCMake/libtest6/src/generated/testpackage/Test6.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test7() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test7.odvd",
					withCMake,
					new String[]{"include/test7/generated/testpackage/Test7A.h",
								 "include/test7/generated/testpackage/Test7B.h",
							 	 "src/generated/testpackage/Test7A.cpp",
								 "src/generated/testpackage/Test7B.cpp"},       /* List of generated files. */
			        new String[]{"Test7/include/test7/generated/testpackage/Test7A.h",
								 "Test7/include/test7/generated/testpackage/Test7B.h",
								 "Test7/src/generated/testpackage/Test7A.cpp",
								 "Test7/src/generated/testpackage/Test7B.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test7_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test7.odvd",
					withCMake,
					new String[]{"libtest7/CMakeLists.txt",
								 "libtest7/include/test7/generated/testpackage/Test7A.h",
								 "libtest7/include/test7/generated/testpackage/Test7B.h",
							 	 "libtest7/src/generated/testpackage/Test7A.cpp",
								 "libtest7/src/generated/testpackage/Test7B.cpp"},       /* List of generated files. */
		            new String[]{"Test7_withCMake/libtest7/CMakeLists.txt",
								 "Test7_withCMake/libtest7/include/test7/generated/testpackage/Test7A.h",
								 "Test7_withCMake/libtest7/include/test7/generated/testpackage/Test7B.h",
								 "Test7_withCMake/libtest7/src/generated/testpackage/Test7A.cpp",
            					 "Test7_withCMake/libtest7/src/generated/testpackage/Test7B.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test8() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test8.odvd",
					withCMake,
					new String[]{"include/test8/generated/testpackage/Test8A.h",
								 "include/test8/generated/testpackage/Test8B.h",
								 "include/test8/generated/testpackage/subpackage/Test8C.h",
							 	 "src/generated/testpackage/Test8A.cpp",
								 "src/generated/testpackage/Test8B.cpp",
								 "src/generated/testpackage/subpackage/Test8C.cpp"},       /* List of generated files. */
			        new String[]{"Test8/include/test8/generated/testpackage/Test8A.h",
								 "Test8/include/test8/generated/testpackage/Test8B.h",
								 "Test8/include/test8/generated/testpackage/subpackage/Test8C.h",
								 "Test8/src/generated/testpackage/Test8A.cpp",
								 "Test8/src/generated/testpackage/Test8B.cpp",
								 "Test8/src/generated/testpackage/subpackage/Test8C.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test8_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test8.odvd",
					withCMake,
					new String[]{"libtest8/CMakeLists.txt",
								 "libtest8/include/test8/generated/testpackage/Test8A.h",
								 "libtest8/include/test8/generated/testpackage/Test8B.h",
								 "libtest8/include/test8/generated/testpackage/subpackage/Test8C.h",
							 	 "libtest8/src/generated/testpackage/Test8A.cpp",
								 "libtest8/src/generated/testpackage/Test8B.cpp",
							 	 "libtest8/src/generated/testpackage/subpackage/Test8C.cpp"},       /* List of generated files. */
		            new String[]{"Test8_withCMake/libtest8/CMakeLists.txt",
								 "Test8_withCMake/libtest8/include/test8/generated/testpackage/Test8A.h",
								 "Test8_withCMake/libtest8/include/test8/generated/testpackage/Test8B.h",
								 "Test8_withCMake/libtest8/include/test8/generated/testpackage/subpackage/Test8C.h",
								 "Test8_withCMake/libtest8/src/generated/testpackage/Test8A.cpp",
            					 "Test8_withCMake/libtest8/src/generated/testpackage/Test8B.cpp",
            					 "Test8_withCMake/libtest8/src/generated/testpackage/subpackage/Test8C.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test9() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test9.odvd",
					withCMake,
					new String[]{"include/test9/generated/Test9A.h",
								 "include/test9/generated/Test9B.h",
								 "include/test9/generated/subpackage/Test9C.h",
							 	 "src/generated/Test9A.cpp",
								 "src/generated/Test9B.cpp",
								 "src/generated/subpackage/Test9C.cpp"},       /* List of generated files. */
			        new String[]{"Test9/include/test9/generated/Test9A.h",
								 "Test9/include/test9/generated/Test9B.h",
								 "Test9/include/test9/generated/subpackage/Test9C.h",
								 "Test9/src/generated/Test9A.cpp",
								 "Test9/src/generated/Test9B.cpp",
								 "Test9/src/generated/subpackage/Test9C.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test9_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test9.odvd",
					withCMake,
					new String[]{"libtest9/CMakeLists.txt",
								 "libtest9/include/test9/generated/Test9A.h",
								 "libtest9/include/test9/generated/Test9B.h",
								 "libtest9/include/test9/generated/subpackage/Test9C.h",
							 	 "libtest9/src/generated/Test9A.cpp",
								 "libtest9/src/generated/Test9B.cpp",
							 	 "libtest9/src/generated/subpackage/Test9C.cpp"},       /* List of generated files. */
		            new String[]{"Test9_withCMake/libtest9/CMakeLists.txt",
								 "Test9_withCMake/libtest9/include/test9/generated/Test9A.h",
								 "Test9_withCMake/libtest9/include/test9/generated/Test9B.h",
								 "Test9_withCMake/libtest9/include/test9/generated/subpackage/Test9C.h",
								 "Test9_withCMake/libtest9/src/generated/Test9A.cpp",
            					 "Test9_withCMake/libtest9/src/generated/Test9B.cpp",
            					 "Test9_withCMake/libtest9/src/generated/subpackage/Test9C.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test10() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test10.odvd",
					withCMake,
					new String[]{"include/test10/generated/Test10.h",
								 "src/generated/Test10.cpp"},       /* List of generated files. */
		            new String[]{"Test10_withCMake/libtest10/include/test10/generated/Test10.h",
            					 "Test10_withCMake/libtest10/src/generated/Test10.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test10_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test10.odvd",
					withCMake,
					new String[]{"libtest10/CMakeLists.txt",
								 "libtest10/include/test10/generated/Test10.h",
								 "libtest10/src/generated/Test10.cpp"},       /* List of generated files. */
		            new String[]{"Test10_withCMake/libtest10/CMakeLists.txt",
								 "Test10_withCMake/libtest10/include/test10/generated/Test10.h",
            					 "Test10_withCMake/libtest10/src/generated/Test10.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test11() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test11.odvd",
					withCMake,
					new String[]{"include/test11/generated/Test11Simple.h",
								 "include/test11/generated/Test11Lists.h",
								 "include/test11/generated/Test11MapBool.h",
								 "include/test11/generated/Test11MapChar.h",
								 "include/test11/generated/Test11MapUint32.h",
								 "include/test11/generated/Test11MapInt32.h",
								 "include/test11/generated/Test11MapFloat.h",
								 "include/test11/generated/Test11MapDouble.h",
								 "include/test11/generated/Test11MapString.h",
								 "src/generated/Test11Simple.cpp",
								 "src/generated/Test11Lists.cpp",
								 "src/generated/Test11MapBool.cpp",
								 "src/generated/Test11MapChar.cpp",
								 "src/generated/Test11MapUint32.cpp",
								 "src/generated/Test11MapInt32.cpp",
								 "src/generated/Test11MapFloat.cpp",
								 "src/generated/Test11MapDouble.cpp",
								 "src/generated/Test11MapString.cpp"},       /* List of generated files. */
		            new String[]{"Test11_withCMake/libtest11/include/test11/generated/Test11Simple.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11Lists.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapBool.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapChar.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapUint32.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapInt32.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapFloat.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapDouble.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapString.h",
								 "Test11_withCMake/libtest11/src/generated/Test11Simple.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11Lists.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapBool.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapChar.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapUint32.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapInt32.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapFloat.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapDouble.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapString.cpp"}  /* List of reference files. */
                    );
			
			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test11_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test11.odvd",
					withCMake,
					new String[]{"libtest11/CMakeLists.txt",
								 "libtest11/include/test11/generated/Test11Simple.h",
								 "libtest11/include/test11/generated/Test11Lists.h",
								 "libtest11/include/test11/generated/Test11MapBool.h",
								 "libtest11/include/test11/generated/Test11MapChar.h",
								 "libtest11/include/test11/generated/Test11MapUint32.h",
								 "libtest11/include/test11/generated/Test11MapInt32.h",
								 "libtest11/include/test11/generated/Test11MapFloat.h",
								 "libtest11/include/test11/generated/Test11MapDouble.h",
								 "libtest11/include/test11/generated/Test11MapString.h",
								 "libtest11/src/generated/Test11Simple.cpp",
								 "libtest11/src/generated/Test11Lists.cpp",
								 "libtest11/src/generated/Test11MapBool.cpp",
								 "libtest11/src/generated/Test11MapChar.cpp",
								 "libtest11/src/generated/Test11MapUint32.cpp",
								 "libtest11/src/generated/Test11MapInt32.cpp",
								 "libtest11/src/generated/Test11MapFloat.cpp",
								 "libtest11/src/generated/Test11MapDouble.cpp",
								 "libtest11/src/generated/Test11MapString.cpp"},       /* List of generated files. */
		            new String[]{"Test11_withCMake/libtest11/CMakeLists.txt",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11Simple.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11Lists.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapBool.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapChar.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapUint32.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapInt32.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapFloat.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapDouble.h",
								 "Test11_withCMake/libtest11/include/test11/generated/Test11MapString.h",
								 "Test11_withCMake/libtest11/src/generated/Test11Simple.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11Lists.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapBool.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapChar.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapUint32.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapInt32.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapFloat.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapDouble.cpp",
								 "Test11_withCMake/libtest11/src/generated/Test11MapString.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test12() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test12.odvd",
					withCMake,
					new String[]{"include/test12/generated/Test12Simple.h",
								 "include/test12/generated/Test12Complex.h",
								 "include/test12/generated/Test12Lists.h",
								 "include/test12/generated/Test12MapBool.h",
								 "include/test12/generated/Test12MapChar.h",
								 "include/test12/generated/Test12MapUint32.h",
								 "include/test12/generated/Test12MapInt32.h",
								 "include/test12/generated/Test12MapFloat.h",
								 "include/test12/generated/Test12MapDouble.h",
								 "include/test12/generated/Test12MapString.h",
								 "src/generated/Test12Simple.cpp",
								 "src/generated/Test12Complex.cpp",
								 "src/generated/Test12Lists.cpp",
								 "src/generated/Test12MapBool.cpp",
								 "src/generated/Test12MapChar.cpp",
								 "src/generated/Test12MapUint32.cpp",
								 "src/generated/Test12MapInt32.cpp",
								 "src/generated/Test12MapFloat.cpp",
								 "src/generated/Test12MapDouble.cpp",
								 "src/generated/Test12MapString.cpp"},       /* List of generated files. */
		            new String[]{"Test12_withCMake/libtest12/include/test12/generated/Test12Simple.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12Complex.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12Lists.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapBool.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapChar.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapUint32.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapInt32.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapFloat.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapDouble.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapString.h",
								 "Test12_withCMake/libtest12/src/generated/Test12Simple.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12Complex.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12Lists.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapBool.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapChar.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapUint32.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapInt32.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapFloat.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapDouble.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapString.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test12_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test12.odvd",
					withCMake,
					new String[]{"libtest12/CMakeLists.txt",
								 "libtest12/include/test12/generated/Test12Simple.h",
								 "libtest12/include/test12/generated/Test12Complex.h",
								 "libtest12/include/test12/generated/Test12Lists.h",
								 "libtest12/include/test12/generated/Test12MapBool.h",
								 "libtest12/include/test12/generated/Test12MapChar.h",
								 "libtest12/include/test12/generated/Test12MapUint32.h",
								 "libtest12/include/test12/generated/Test12MapInt32.h",
								 "libtest12/include/test12/generated/Test12MapFloat.h",
								 "libtest12/include/test12/generated/Test12MapDouble.h",
								 "libtest12/include/test12/generated/Test12MapString.h",
								 "libtest12/src/generated/Test12Simple.cpp",
								 "libtest12/src/generated/Test12Complex.cpp",
								 "libtest12/src/generated/Test12Lists.cpp",
								 "libtest12/src/generated/Test12MapBool.cpp",
								 "libtest12/src/generated/Test12MapChar.cpp",
								 "libtest12/src/generated/Test12MapUint32.cpp",
								 "libtest12/src/generated/Test12MapInt32.cpp",
								 "libtest12/src/generated/Test12MapFloat.cpp",
								 "libtest12/src/generated/Test12MapDouble.cpp",
								 "libtest12/src/generated/Test12MapString.cpp"},       /* List of generated files. */
		            new String[]{"Test12_withCMake/libtest12/CMakeLists.txt",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12Simple.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12Complex.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12Lists.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapBool.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapChar.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapUint32.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapInt32.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapFloat.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapDouble.h",
								 "Test12_withCMake/libtest12/include/test12/generated/Test12MapString.h",
								 "Test12_withCMake/libtest12/src/generated/Test12Simple.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12Complex.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12Lists.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapBool.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapChar.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapUint32.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapInt32.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapFloat.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapDouble.cpp",
								 "Test12_withCMake/libtest12/src/generated/Test12MapString.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test13() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test13.odvd",
					withCMake,
					new String[]{"include/test13/generated/Test13/subpackage/Test13Simple.h",
								 "src/generated/Test13/subpackage/Test13Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test13_withCMake/libtest13/include/test13/generated/Test13/subpackage/Test13Simple.h",
								 "Test13_withCMake/libtest13/src/generated/Test13/subpackage/Test13Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test13_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test13.odvd",
					withCMake,
					new String[]{"libtest13/CMakeLists.txt",
								 "libtest13/include/test13/generated/Test13/subpackage/Test13Simple.h",
								 "libtest13/src/generated/Test13/subpackage/Test13Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test13_withCMake/libtest13/CMakeLists.txt",
								 "Test13_withCMake/libtest13/include/test13/generated/Test13/subpackage/Test13Simple.h",
								 "Test13_withCMake/libtest13/src/generated/Test13/subpackage/Test13Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test14() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test14.odvd",
					withCMake,
					new String[]{"include/test14/generated/subpackage/Test14Simple.h",
								 "src/generated/subpackage/Test14Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test14_withCMake/libtest14/include/test14/generated/subpackage/Test14Simple.h",
								 "Test14_withCMake/libtest14/src/generated/subpackage/Test14Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test14_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test14.odvd",
					withCMake,
					new String[]{"libtest14/CMakeLists.txt",
								 "libtest14/include/test14/generated/subpackage/Test14Simple.h",
								 "libtest14/src/generated/subpackage/Test14Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test14_withCMake/libtest14/CMakeLists.txt",
								 "Test14_withCMake/libtest14/include/test14/generated/subpackage/Test14Simple.h",
								 "Test14_withCMake/libtest14/src/generated/subpackage/Test14Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test15() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test15.odvd",
					withCMake,
					new String[]{"include/test15/generated/Test15Simple.h",
								 "src/generated/Test15Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test15_withCMake/libtest15/include/test15/generated/Test15Simple.h",
								 "Test15_withCMake/libtest15/src/generated/Test15Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test15_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test15.odvd",
					withCMake,
					new String[]{"libtest15/CMakeLists.txt",
								 "libtest15/include/test15/generated/Test15Simple.h",
								 "libtest15/src/generated/Test15Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test15_withCMake/libtest15/CMakeLists.txt",
								 "Test15_withCMake/libtest15/include/test15/generated/Test15Simple.h",
								 "Test15_withCMake/libtest15/src/generated/Test15Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test16() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test16.odvd",
					withCMake,
					new String[]{"include/test16/generated/sub/structure/Test16Simple.h",
								 "src/generated/sub/structure/Test16Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test16_withCMake/libtest16/include/test16/generated/sub/structure/Test16Simple.h",
								 "Test16_withCMake/libtest16/src/generated/sub/structure/Test16Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test16_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test16.odvd",
					withCMake,
					new String[]{"libtest16/CMakeLists.txt",
								 "libtest16/include/test16/generated/sub/structure/Test16Simple.h",
								 "libtest16/src/generated/sub/structure/Test16Simple.cpp"},       /* List of generated files. */
		            new String[]{"Test16_withCMake/libtest16/CMakeLists.txt",
								 "Test16_withCMake/libtest16/include/test16/generated/sub/structure/Test16Simple.h",
								 "Test16_withCMake/libtest16/src/generated/sub/structure/Test16Simple.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	

	@Test
	public void test_generateFile_Test18() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test18.odvd",
					withCMake,
					new String[]{"include/test18/generated/Test18.h",
								 "src/generated/Test18.cpp"},       /* List of generated files. */
		            new String[]{"Test18_withCMake/libtest18/include/test18/generated/Test18.h",
								 "Test18_withCMake/libtest18/src/generated/Test18.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test18_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test18.odvd",
					withCMake,
					new String[]{"libtest18/CMakeLists.txt",
								 "libtest18/include/test18/generated/Test18.h",
								 "libtest18/src/generated/Test18.cpp"},       /* List of generated files. */
		            new String[]{"Test18_withCMake/libtest18/CMakeLists.txt",
								 "Test18_withCMake/libtest18/include/test18/generated/Test18.h",
								 "Test18_withCMake/libtest18/src/generated/Test18.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test19() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test19.odvd",
					withCMake,
					new String[]{"include/test19/generated/Test19a.h",
								 "src/generated/Test19a.cpp",
								 "include/test19/generated/Test19b.h",
								 "src/generated/Test19b.cpp",
								 "include/test19/generated/Test19c.h",
								 "src/generated/Test19c.cpp"},       /* List of generated files. */
			       new String[]{"Test19_withCMake/libtest19/include/test19/generated/Test19a.h",
								 "Test19_withCMake/libtest19/src/generated/Test19a.cpp",
								 "Test19_withCMake/libtest19/include/test19/generated/Test19b.h",
								 "Test19_withCMake/libtest19/src/generated/Test19b.cpp",
								 "Test19_withCMake/libtest19/include/test19/generated/Test19c.h",
								 "Test19_withCMake/libtest19/src/generated/Test19c.cpp"}  /* List of reference files. */
			       );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test19_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test19.odvd",
					withCMake,
					new String[]{"libtest19/CMakeLists.txt",
								 "libtest19/include/test19/generated/Test19a.h",
								 "libtest19/src/generated/Test19a.cpp",
								 "libtest19/include/test19/generated/Test19b.h",
								 "libtest19/src/generated/Test19b.cpp",
								 "libtest19/include/test19/generated/Test19c.h",
								 "libtest19/src/generated/Test19c.cpp"},       /* List of generated files. */
		            new String[]{"Test19_withCMake/libtest19/CMakeLists.txt",
								 "Test19_withCMake/libtest19/include/test19/generated/Test19a.h",
								 "Test19_withCMake/libtest19/src/generated/Test19a.cpp",
								 "Test19_withCMake/libtest19/include/test19/generated/Test19b.h",
								 "Test19_withCMake/libtest19/src/generated/Test19b.cpp",
								 "Test19_withCMake/libtest19/include/test19/generated/Test19c.h",
								 "Test19_withCMake/libtest19/src/generated/Test19c.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}

	@Test
	public void test_generateFile_Test20() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = false;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test20.odvd",
					withCMake,
					new String[]{"include/test20/generated/Test20a.h",
								 "src/generated/Test20a.cpp",
								 "include/test20/generated/sub/structure/Test20b.h",
								 "src/generated/sub/structure/Test20b.cpp",
								 "include/test20/generated/sub/structure2/Test20c.h",
								 "src/generated/sub/structure2/Test20c.cpp"},       /* List of generated files. */
			       new String[]{"Test20_withCMake/libtest20/include/test20/generated/Test20a.h",
								 "Test20_withCMake/libtest20/src/generated/Test20a.cpp",
								 "Test20_withCMake/libtest20/include/test20/generated/sub/structure/Test20b.h",
								 "Test20_withCMake/libtest20/src/generated/sub/structure/Test20b.cpp",
								 "Test20_withCMake/libtest20/include/test20/generated/sub/structure2/Test20c.h",
								 "Test20_withCMake/libtest20/src/generated/sub/structure2/Test20c.cpp"}  /* List of reference files. */
			       );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
	
	@Test
	public void test_generateFile_Test20_withCMake() {
		try {
			int EXPECTED_RETVAL = 0;
			boolean withCMake = true;
			
			TestDataSet tds = new TestDataSet(EXPECTED_RETVAL,
					PATH_FOR_INPUT_FILES + "Test20.odvd",
					withCMake,
					new String[]{"libtest20/CMakeLists.txt",
								 "libtest20/include/test20/generated/Test20a.h",
								 "libtest20/src/generated/Test20a.cpp",
								 "libtest20/include/test20/generated/sub/structure/Test20b.h",
								 "libtest20/src/generated/sub/structure/Test20b.cpp",
								 "libtest20/include/test20/generated/sub/structure2/Test20c.h",
								 "libtest20/src/generated/sub/structure2/Test20c.cpp"},       /* List of generated files. */
		            new String[]{"Test20_withCMake/libtest20/CMakeLists.txt",
								 "Test20_withCMake/libtest20/include/test20/generated/Test20a.h",
								 "Test20_withCMake/libtest20/src/generated/Test20a.cpp",
								 "Test20_withCMake/libtest20/include/test20/generated/sub/structure/Test20b.h",
								 "Test20_withCMake/libtest20/src/generated/sub/structure/Test20b.cpp",
								 "Test20_withCMake/libtest20/include/test20/generated/sub/structure2/Test20c.h",
								 "Test20_withCMake/libtest20/src/generated/sub/structure2/Test20c.cpp"}  /* List of reference files. */
                    );

			org.junit.Assert.assertTrue("Initialization of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyInitialized());
			org.junit.Assert.assertTrue("Calling DataStructureGenerator with '" + tds.get_args() + "'.", DataStructureGenerator.process(tds.get_args()) == tds.getExpectedRetVal());
			org.junit.Assert.assertTrue("Generation of DataStructureGenerator with '" + tds.get_args() + "' successful.", tds.isSuccessfullyGenerated());

			HashMap<String, DataStructureGeneratorTest.Entry> results = tds.getEntriesToCompare();
			for (Map.Entry<String, DataStructureGeneratorTest.Entry> entry : results.entrySet()) {
			    String key = entry.getKey();
			    Entry value = entry.getValue();
			    
				org.junit.Assert.assertTrue(key, value.equal);
			}
			
			tds.removeGeneratedFiles();
		} catch (FileNotFoundException e) {
			org.junit.Assert.fail(e.toString());
		} catch (IOException e) {
			org.junit.Assert.fail(e.toString());
		}
	}
}

