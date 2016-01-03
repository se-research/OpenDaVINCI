# OpenDaVINCI - Study to run boxparker in a simulation environment

This example was realized with OpenDaVINCI and demonstrates how to use the
framework in combination with the simulation environment to develop a
self-parking algorithm. The following instructions are tested with Ubuntu
14.04 LTS; further information for other platforms or how to build
OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

Further background about this project is provided here: http://arxiv.org/abs/1406.7768

This project demonstrates how to design simulation studies with OpenDaVINCI.

A simulation can be designed as a stand-alone application or embedded
into a unit test environment. This example demonstrates how to create
a CLI simulation using OpenDaVINCI and odSimulation; in addition, the
simulation is also embedded into a CxxTest test suite to be automatically
executed using a ``make test`` command.
