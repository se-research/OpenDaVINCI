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

###############################################################################
# Parameters for this Makefile.
BASE_IMAGE=seresearch/opendavinci-ubuntu-16.04
TESTRUNNER_DISABLED=NO

###############################################################################
# Tools.
DOCKER=$(shell which docker)
CMAKE=$(shell which cmake)

###############################################################################
# Determine Git-related setting.
GIT_CURRENT_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)
GIT_HASH=$(shell git rev-parse --short HEAD)
GIT_COMMITS_IN_CURRENT_BRANCH=$(shell git rev-list --count `git rev-parse --abbrev-ref HEAD`)
GIT_HAS_UNCOMMITTED_CHANGES=$(shell if [ "`git ls-files -m ..`" != "" ]; then echo "-modified"; else echo ""; fi)
BUILD_PATH=$(BUILD_PATH_BASE)/$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_CURRENT_BRANCH)

###############################################################################
# Directories.
SOURCE_TREE_PATH=$(shell dirname $(shell pwd))
BUILD_PATH_BASE=$(SOURCE_TREE_PATH)/docker/builds
RUN_BUILD_AS=$(shell whoami)
PACKAGES_DIR=$(BUILD_PATH)

###############################################################################
# Docker settings.
DOCKERFILE_BASEIMAGE=s%BASEIMAGE%$(BASE_IMAGE)%
DOCKER_IMAGE_NAME=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")
DOCKER_IMAGE_NAME_WITH_GIT_HASH=$(DOCKER_IMAGE_NAME)-$(GIT_HASH)
DOCKER_NETWORK_NAME=nw_$(DOCKER_IMAGE_NAME_WITH_GIT_HASH)
DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_HASH):$(GIT_COMMITS_IN_CURRENT_BRANCH)
DOCKER_IMAGE_NAME_SHORT_NAME=$(BASE_IMAGE)-complete:latest

###############################################################################

.PHONY: all buildComplete createDockerImage clean cleanAll cleanDocker removeExitedContainers removeNoneImagesFromDocker removeExistingImagesForBaseImageFromDocker

###############################################################################

all: createDockerImage

###############################################################################

clean:
	$(CMAKE) -E remove_directory $(BUILD_PATH)

cleanAll: clean cleanDocker

cleanDocker: removeExitedContainers removeNoneImagesFromDocker removeExistingImagesForBaseImageFromDocker

removeExitedContainers:
	$(DOCKER) rm $$($(DOCKER) ps -a -q) || exit 0

removeNoneImagesFromDocker:
	for i in $$($(DOCKER) images | grep none | tr -s " " ";" | cut -f3 -d";"); do $(DOCKER) rmi $$i; done

removeExistingImagesForBaseImageFromDocker:
	$(DOCKER) rmi -f `$(DOCKER) images | grep $(BASE_IMAGE)- | tr -s " " ";" | cut -f3 -d";"` || exit 0

###############################################################################
# This target uses a Docker container to build the OpenDaVINCI source tree using the selected Docker image.
buildComplete: $(BUILD_PATH)/build.incremental

# The complete build creates a stamp file.
$(BUILD_PATH)/OpenDaVINCI.build/build.incremental:
	$(CMAKE) -E make_directory $(BUILD_PATH)
	$(CMAKE) -E make_directory $(BUILD_PATH)/opt/od4
	$(CMAKE) -E make_directory $(BUILD_PATH)/OpenDaVINCI.build
	$(CMAKE) -E make_directory $(BUILD_PATH)/OpenDaVINCI.deb
	$(DOCKER) network inspect $(DOCKER_NETWORK_NAME) || $(DOCKER) network create $(DOCKER_NETWORK_NAME)
	$(DOCKER) network ls
	$(DOCKER) run -ti --rm -v $(SOURCE_TREE_PATH):/opt/OpenDaVINCI.sources -v $(BUILD_PATH)/OpenDaVINCI.build:/opt/OpenDaVINCI.build -v $(BUILD_PATH)/opt/od4:/opt/od4 -v $(SOURCE_TREE_PATH)/docker/doBuild.sh:/opt/doBuild.sh -w /opt $(BASE_IMAGE) /opt/doBuild.sh $(RUN_BUILD_AS) $(TESTRUNNER_DISABLED)
	$(DOCKER) network rm $(DOCKER_NETWORK_NAME)
	touch $(BUILD_PATH)/OpenDaVINCI.build/build.incremental

# Dependency to allow incremental builds.
buildIncremental: $(BUILD_PATH)/OpenDaVINCI.build/build.incremental
	$(DOCKER) run -ti --rm -v $(SOURCE_TREE_PATH):/opt/OpenDaVINCI.sources -v $(BUILD_PATH)/OpenDaVINCI.build:/opt/OpenDaVINCI.build -v $(BUILD_PATH)/opt/od4:/opt/od4 -v $(SOURCE_TREE_PATH)/docker/doBuild.sh:/opt/doBuild.sh -w /opt $(BASE_IMAGE) /opt/doBuild.sh $(RUN_BUILD_AS) TESTRUNNER_DISABLED=YES INCREMENTAL
	mkdir -p $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME) && for i in $$(find $(BUILD_PATH)/OpenDaVINCI.build -type f -name "*deb" | grep -v CPack); do cp $$i $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME); done

###############################################################################
# This target creates a new Docker image based on the selected Docker image using the freshly built binaries.
createDockerImage: buildIncremental
	cat $(SOURCE_TREE_PATH)/docker/Dockerfile.template | sed -e $(DOCKERFILE_BASEIMAGE) > $(BUILD_PATH)/Dockerfile
	echo "OpenDaVINCI.build" > $(BUILD_PATH)/.dockerignore
	cd $(BUILD_PATH) && $(DOCKER) build -t seresearch/$(DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH) . | tee $(BUILD_PATH)/OpenDaVINCI.build/build.log || exit 1
	$(DOCKER) images | grep $$(tail -1 $(BUILD_PATH)/OpenDaVINCI.build/build.log | cut -f3 -d" ") | grep "latest" && exit 0 || $(DOCKER) tag $$(tail -1 $(BUILD_PATH)/OpenDaVINCI.build/build.log | cut -f3 -d" ") $(DOCKER_IMAGE_NAME_SHORT_NAME)

###############################################################################

pushDockerImage: createDockerImage
	$(DOCKER) push $(DOCKER_IMAGE_NAME_SHORT_NAME)
	$(DOCKER) push seresearch/$(DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH)

