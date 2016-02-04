Using OpenDaVINCI for simulation and visualization (Ubuntu 14.04)
-----------------------------------------------------------

OpenDaVINCI has several extended libraries for simulation and visualization. The first extended library is odsimulation-odsimtools, which contains components such as odsimvehicle, odsimcamera, and odsimirus, for simulation. The second extended library is opendavinci-odcockpit used for visualization. odcockpit supports visualization for both simulation and real systems.

The tutorial on installing precompiled OpenDaVINCI libraries (http://opendavinci.readthedocs.org/en/latest/installation.pre-compiled.html#adding-opendavinci-to-your-ubuntu-14-04-linux-distribution) does not install these two libraries by default. In order to install odsimulation-odsimtools and opendavinci-odcockpit for simulation and visualization purposes, replace Step 4 at http://opendavinci.readthedocs.org/en/latest/installation.pre-compiled.html#adding-opendavinci-to-your-ubuntu-14-04-linux-distribution::

    $ sudo apt-get install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent

with

    $ sudo apt-get install opendavinci-odlib opendavinci-odtools opendavinci-odsupercomponent odsimulation-odsimtools opendavinci-odcockpit