How to install pre-compiled OpenDaVINCI libraries
=================================================

To explore the features of OpenDaVINCI and to use it in your own
projects, you can find pre-compiled packages in .deb and .rpm
format for x86, x86_64, and armfh.

Adding OpenDaVINCI to your Ubuntu Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ sudo wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ trusty main" >> /etc/apt/sources.list

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent opendavinci-odautomotivedata


Adding OpenDaVINCI to your Debian Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ sudo wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/debian/ wheezy main" >> /etc/apt/sources.list

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent opendavinci-odautomotivedata


Adding OpenDaVINCI to your Fedora Linux distribution
----------------------------------------------------

1. Add our repository itself to your sources.list::

    $ sudo echo "[myrepo]\r\nname=My Repository\r\nbaseurl=deb http://opendavinci.cse.chalmers.se/rpm-x86_64/repo\r\nenabled=1" >> etc/yum.repos.d/my.repo

2. Update your package database::

   $ sudo yum -y update

3. Install OpenDaVINCI::

   $ sudo yum --nogpgcheck install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent opendavinci-odautomotivedata
   
   
Adding OpenDaVINCI to your openSuse Linux distribution
------------------------------------------------------

1. Add the public key from our repository::

    $ sudo zypper --no-gpg-checks ar -f http://opendavinci.cse.chalmers.se/rpm-x86_64/repo OpenDaVINCI

2. Add our repository itself to your sources.list::

    $ sudo zypper --non-interactive --no-gpg-checks ar -f http://opendavinci.cse.chalmers.se/rpm-x86_64/repo OpenDaVINCI

3. Update your package database::

    $ sudo zypper --no-gpg-checks update

4. Install OpenDaVINCI::

   $ sudo zypper --no-gpg-checks install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent opendavinci-odautomotivedata


Using our Docker images
-----------------------

You also find pre-built Docker images for x86_64 and armhf. These images will be automatically
updated whenever new features or patches are released.

For Ubuntu/x86_64 (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-amd64/)::

    $ docker pull seresearch/opendavinci-ubuntu-amd64 

For Ubuntu/armhf (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-armhf/)::

    $ docker pull seresearch/opendavinci-ubuntu-armhf



