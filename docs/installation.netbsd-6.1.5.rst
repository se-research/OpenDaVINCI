Compiling OpenDaVINCI on NetBSD 6.1.5 (32bit and 64bit)
-------------------------------------------------------

Download and install NetBSD 6.1.4 and update the packages list as root::

    # pkgin update
  
Install the bash shell::

    # pkgin install bash
  
Change the shell by running::

    $ chsh
  
Set up the right locale::

    $ cat >.profile <<EOF
    export LANG="en_US.UTF-8"
    export LC_CTYPE="en_US.UTF-8"
    export LC_ALL=""
    EOF
  
Install the compiler::

    # pkgin install gcc
    # pkgin install cmake
    # pkgin install git
    # pkgin install python27
  
Add a symbolic link to python as root user::

    # ln -sf /usr/pkg/bin/python2.7 /usr/bin/python

Install Java to generate data structures::

    # cd /usr/pkgsrc/distfiles && wget http://ftp.osuosl.org/pub/funtoo/distfiles/oracle-java/jdk-7u72-linux-i586.tar.gz
    # cd /usr/pkgsrc/emulators/suse121_base && make install clean
    # cd /usr/pkgsrc/emulators/suse121_x11 && make install clean
    # cd /usr/pkgsrc/lang/sun-jdk7 && echo "ACCEPTABLE_LICENSES+=oracle-binary-code-license" >> /etc/mk.conf && make install clean
    # echo "procfs /usr/pkg/emul/linux/proc procfs rw,linux" >> /etc/fstab
    # cd /usr/pkg/bin && ln -sf sun7-java java
    # cd /usr/pkg/bin && ln -sf sun7-javac javac
    $ echo "ulimit -d 400000" >> .profile
  
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

    $ make all

