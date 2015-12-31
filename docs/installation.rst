How to install OpenDaVINCI on Linux-based Platforms
===================================================

.. include:: installation.archlinux.rst
.. include:: installation.centos7.rst
.. include:: installation.debian-7.8.rst
.. include:: installation.debian-8.1.rst
.. include:: installation.elementaryos.rst
.. include:: installation.fedora-20.rst
.. include:: installation.fedora-21.rst
.. include:: installation.fedora-22.rst
.. include:: installation.mageia.rst
.. include:: installation.mint-17.rst
.. include:: installation.opensuse-13.1.rst
.. include:: installation.opensuse-13.2.rst
.. include:: installation.scientificlinux-7.rst
.. include:: installation.ubuntu-14.04.rst
.. include:: installation.ubuntu-15.04.rst
.. include:: installation.zorin-9.1.rst
.. include:: installation.zorin-10.rst

How to install OpenDaVINCI on BSD-based Platforms
=================================================
.. include:: installation.dragonfly-4.0.5.rst
.. include:: installation.dragonfly-4.2.rst
.. include:: installation.freebsd-10.rst
.. include:: installation.netbsd-6.1.5.rst
.. include:: installation.netbsd-7.0.rst
.. include:: installation.openbsd-5.7.rst
.. include:: installation.openbsd-5.8.rst
.. include:: installation.macosx-10.rst

How to install OpenDaVINCI on Windows-based Platforms
=====================================================
.. include:: installation.windows.rst

How to compile OpenDaVINCI with Clang
=====================================

To compile OpenDaVINCI using Clang, change to your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder and specify the Clang toolchain::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_TOOLCHAIN_FILE=../cmake/clang-Toolchain.cmake ..

