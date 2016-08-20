# Makefile - Makefile to create a Docker image based on a specific base Linux.
# Copyright (C) 2016 Christian Berger
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# Parameters for this Makefile.
BASE_IMAGE=seresearch/opendavinci-ubuntu-16.04
TESTRUNNER_DISABLED=NO

# Directories.
SOURCE_TREE_PATH=$(shell dirname $(shell pwd))
BUILD_PATH_BASE=$(SOURCE_TREE_PATH)/docker/builds
RUN_BUILD_AS=$(shell whoami)

# Tools.
DOCKER=$(shell which docker)
CMAKE=$(shell which cmake)

# Determine Git-related setting.
GIT_CURRENT_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)
GIT_HASH=$(shell git rev-parse --short HEAD)
GIT_COMMITS_IN_CURRENT_BRANCH=$(shell git rev-list --count `git rev-parse --abbrev-ref HEAD`)
GIT_HAS_UNCOMMITTED_CHANGES=$(shell if [ "`git ls-files -m ..`" != "" ]; then echo "-modified"; else echo ""; fi)
BUILD_PATH=$(BUILD_PATH_BASE)/$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_CURRENT_BRANCH)

# Docker settings.
DOCKERFILE_BASEIMAGE=s%BASEIMAGE%$(BASE_IMAGE)%
DOCKER_IMAGE_NAME=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_HASH)
DOCKER_NETWORK_NAME=nw_$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_HASH)
DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_HASH):$(GIT_COMMITS_IN_CURRENT_BRANCH)


.PHONY: all pull build


all: pull build createDockerImage

overview:
	echo "0: '$(DOCKERFILE_BASEIMAGE)'"
	echo "0: '$(DISABLE_TESTCASES)'"
	echo "0: '$(BASE_IMAGE)'"
	echo "1: '$(GIT_CURRENT_BRANCH)'"
	echo "2: '$(GIT_COMMITS_IN_CURRENT_BRANCH)'"
	echo "3: '$(GIT_HAS_UNCOMMITTED_CHANGES)'"
	echo "4: '$(GIT_HASH)'"
	echo "5: '$(HOST_PATH)'"
	echo "6: '$(BUILD_PATH)'"

pull:
	$(DOCKER) pull $(BASE_IMAGE)

# This target uses a Docker container to build the OpenDaVINCI source tree using the specified Docker image.
build:
	$(CMAKE) -E remove_directory $(BUILD_PATH)
	$(CMAKE) -E make_directory $(BUILD_PATH)
	$(CMAKE) -E make_directory $(BUILD_PATH)/opt/od4
	$(CMAKE) -E make_directory $(BUILD_PATH)/OpenDaVINCI.build
	$(DOCKER) network inspect $(DOCKER_NETWORK_NAME) || $(DOCKER) network create $(DOCKER_NETWORK_NAME)
	$(DOCKER) network ls
	$(DOCKER) run -ti --rm -v $(SOURCE_TREE_PATH):/opt/OpenDaVINCI.sources -v $(BUILD_PATH)/OpenDaVINCI.build:/opt/OpenDaVINCI.build -v $(BUILD_PATH)/opt/od4:/opt/od4 -v $(SOURCE_TREE_PATH)/docker/doBuild.sh:/opt/doBuild.sh -w /opt $(BASE_IMAGE) /opt/doBuild.sh $(RUN_BUILD_AS) $(TESTRUNNER_DISABLED)
	$(DOCKER) network rm nw_$(DOCKER_IMAGE_NAME)

# This target creates a new Docker image based on the specified Docker image using the freshly built binaries.
createDockerImage:
	cat $(SOURCE_TREE_PATH)/docker/Dockerfile.template | sed -e $(DOCKERFILE_BASEIMAGE) > $(BUILD_PATH)/Dockerfile
	echo "OpenDaVINCI.build" > $(BUILD_PATH)/.dockerignore
	cd $(BUILD_PATH) && $(DOCKER) build -t seresearch/$(DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH) .

