How to install pre-compiled OpenDaVINCI libraries
=================================================

To explore the features of OpenDaVINCI and to use it in your own
projects, you can find pre-compiled packages in .deb and .rpm
format for x86, x86_64, and armfh.

Adding OpenDaVINCI to your Ubuntu 14.04 Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo sh -c 'echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ trusty main" >> /etc/apt/sources.list'

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your Ubuntu 15.04 Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo sh -c 'echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ vivid main" >> /etc/apt/sources.list'

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your Ubuntu 15.10 Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo sh -c 'echo "deb http://opendavinci.cse.chalmers.se/ubuntu-wily/ wily main" >> /etc/apt/sources.list'

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your Debian 8 Linux distribution
----------------------------------------------------

1. Add the public key from our repository::

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

2. Add our repository itself to your sources.list::

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/debian/ jessie main" >> /etc/apt/sources.list

3. Update your package database::

    $ sudo apt-get update

4. Install OpenDaVINCI::

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your CentOS 7 Linux distribution
----------------------------------------------------

1. Add our repository::

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

2. Update your package database::

   $ sudo yum -y update

3. Install OpenDaVINCI::

   $ sudo yum install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your Fedora 21 Linux distribution
----------------------------------------------------

1. Add our repository::

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

2. Update your package database::

    $ sudo yum -y update

3. Install OpenDaVINCI::

   $ sudo yum install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Adding OpenDaVINCI to your Fedora 22 Linux distribution
----------------------------------------------------

1. Add our repository::

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

2. Update your package database::

   $ sudo dnf -y upgrade

3. Install OpenDaVINCI::

   $ sudo dnf install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent
   
   
Adding OpenDaVINCI to your openSuSE 13 Linux distribution
------------------------------------------------------

1. Add our repository::

    $ cd /etc/zypp/repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

2. Update your package database::

    $ sudo zypper --no-gpg-checks refresh

3. Install OpenDaVINCI::

    $ sudo zypper install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


Using our Docker images
-----------------------

You also find pre-built Docker images for x86_64 and armhf. These images will be automatically
updated whenever new features or patches are released.

For Ubuntu/x86_64 (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-amd64/)::

    $ docker pull seresearch/opendavinci-ubuntu-amd64 

For Ubuntu/armhf (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-armhf/)::

    $ docker pull seresearch/opendavinci-ubuntu-armhf

