Compiling OpenDaVINCI on Windows 7, 8.1, and 10 (32bit and 64bit)
-----------------------------------------------------------------


Download and install CMake for Windows (let the install add the CMake binary to the all users' path): http://www.cmake.org/files/v3.0/cmake-3.0.0-win32-x86.exe

Download and install Python 2.7.8 for Windows: https://www.python.org/ftp/python/2.7.8/python-2.7.8.msi. Let the installer add Python to the the system path so that you can run Python from the command line.

Download and install Git for Windows (choose "Use Git from Windows Command Prompt" & "Checkout Windows-style & commit Unix style": http://git-scm.com/download/win

Install Java to generate data structures: http://java.com/en/download/

Download and install Visual Studio 2013 Community Edition: http://go.microsoft.com/fwlink/?LinkId=517284

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder (NMake files for building on console)::

    $ cd build
    $ cmake -G "NMake Makefiles" -D CMAKE_INSTALL_PREFIX=myInstallDir ..

Build the OpenDaVINCI sources::

    $ nmake

If you want to use Visual Studio for editing, let cmake create the build scripts::

    $ cd build
    $ cmake -G "Visual Studio 12 2013" -D CMAKE_INSTALL_PREFIX=../myInstallDir ..
