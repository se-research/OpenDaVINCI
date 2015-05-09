Compiling OpenDaVINCI on Windows 7, 8.1, and 10 (32bit and 64bit)
=================================================================


Download and install CMake for Windows (let the install add the CMake binary to the all users' path): http://www.cmake.org/files/v3.0/cmake-3.0.0-win32-x86.exe

Download and install Python 2.7.8 for Windows: https://www.python.org/ftp/python/2.7.8/python-2.7.8.msi. Let the installer add Python to the the system path so that you can run Python from the command line.

Download and install Git for Windows (choose "Use Git from Windows Command Prompt" & "Checkout Windows-style & commit Unix style": http://git-scm.com/download/win

Install Java to generate data structures: http://java.com/en/download/

Download and install Visual Studio 2013 Community Edition: http://go.microsoft.com/fwlink/?LinkId=517284



  <pre><code>
   $nmake
  </code></pre>

   Next, run the tests:
  <pre><code>
   $nmake test
  </code></pre>

  Install the binaries, libraries, and header files to /opt/odv:
  <pre><code>
   $nmake install
  </code></pre>
 </li>

 <li>Use cmake to create the build scripts for your build folder (Visual Studio build environment):
  <pre><code>
   $cd build
   $cmake -G "Visual Studio 12 2013" -D CMAKE_INSTALL_PREFIX=../myInstallDir ..
  </code></pre>

   Hereby, myInstallDir is the final install folder. Now, you can open the OPENDAVINCI.sln solution file in Visual Studio and trigger the build there.
 </li>

Download the latest OpenDaVINCI sources: http://opendavinci.cse.chalmers.se:8000/www/#download

Change your source folder, create a build directory, and create data structures::

   $ cd OpenDaVINCI && md build && generateDataStructures.bat

Use cmake to create the build scripts for your build folder (NMake files for building on console)::

   $ cd build
   $ cmake -G "NMake Makefiles" -D CMAKE_INSTALL_PREFIX=myInstallDir ..

Build the OpenDaVINCI sources::

   $ nmake

Run the tests for OpenDaVINCI::

   $ nmake test

Install the binaries, libraries, and header files to /usr/local::

   $ nmake install
