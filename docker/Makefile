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
BASE_IMAGE_VERSION=latest
TESTRUNNER_DISABLED=NO
BASE_IMAGE_MINIMAL=seresearch/opendavinci

###############################################################################
# Tools.
DOCKER=$(shell which docker)
CMAKE=$(shell which cmake)
HAS_UPX:=$(shell upx -V 2&>1 /dev/null)
UPX=$(shell which upx)

###############################################################################
# Determine Git-related setting.
VERSION=v$(shell head -1 ../VERSION | cut -f1 -d" ")
GIT_CURRENT_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)
GIT_HASH=$(shell git rev-parse --short HEAD)
GIT_COMMITS_IN_CURRENT_BRANCH=$(shell git rev-list --count `git rev-parse --abbrev-ref HEAD`)
GIT_HAS_UNCOMMITTED_CHANGES=$(shell if [ "`git ls-files -m ..`" != "" ]; then echo "-modified"; else echo ""; fi)
BUILD_PATH=$(BUILD_PATH_BASE)/$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_CURRENT_BRANCH)

###############################################################################
# Directories.
DEST_DIR=od4
PROJECT_NAME=OpenDaVINCI
SOURCE_TREE_PATH=$(shell dirname $(shell pwd))
BUILD_PATH_BASE=$(SOURCE_TREE_PATH)/docker/builds
CCACHE_PATH=$(HOME)/.ccache
RUN_BUILD_AS=odv # ${PROJECT_NAME} is built as odv.
RUN_BUILD_UID_AS=$(shell getent passwd `whoami` | cut -f3 -d":")
PACKAGES_DIR=$(BUILD_PATH)

###############################################################################
# Docker settings.
DOCKERFILE_BASEIMAGE=s%BASEIMAGE%$(BASE_IMAGE)%
DOCKER_IMAGE_NAME=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")
DOCKER_IMAGE_NAME_WITH_GIT_HASH=$(DOCKER_IMAGE_NAME)-$(GIT_HASH)
DOCKER_NETWORK_NAME=nw_$(DOCKER_IMAGE_NAME_WITH_GIT_HASH)
DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH=$(shell echo $(BASE_IMAGE) | cut -f2 -d"/")-$(GIT_HASH):$(GIT_COMMITS_IN_CURRENT_BRANCH)
DOCKER_IMAGE_NAME_SHORT_NAME=$(BASE_IMAGE)-complete
DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME=$(BASE_IMAGE_MINIMAL)-minimal
DOCKERFILE_BASEIMAGE_MINIMAL=s%BASEIMAGE%$(BASE_IMAGE_MINIMAL)%
DOCKER_MINIMAL_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH=$(shell echo $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME) | cut -f2 -d"/")-$(GIT_HASH):$(GIT_COMMITS_IN_CURRENT_BRANCH)

###############################################################################

.PHONY: all buildComplete createDockerImage clean cleanAll cleanDocker removeExitedContainers removeNoneImagesFromDocker removeExistingImagesForBaseImageFromDocker updateDockerBaseImage updateBuildComplete

###############################################################################

all: updateBuildComplete createDockerImage

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
	$(DOCKER) rmi -f `$(DOCKER) images | grep $(BASE_IMAGE_MINIMAL)- | tr -s " " ";" | cut -f3 -d";"` || exit 0

updateDockerBaseImage:
	$(DOCKER) pull $(BASE_IMAGE):$(BASE_IMAGE_VERSION)

###############################################################################
define compile
	$(CMAKE) -E make_directory $(BUILD_PATH)
	$(CMAKE) -E make_directory $(BUILD_PATH)/opt/${DEST_DIR}
	$(CMAKE) -E make_directory $(BUILD_PATH)/${PROJECT_NAME}.build
	$(CMAKE) -E make_directory $(BUILD_PATH)/${PROJECT_NAME}.deb
	$(DOCKER) network inspect $(DOCKER_NETWORK_NAME) || $(DOCKER) network create $(DOCKER_NETWORK_NAME)
	$(DOCKER) network ls
	$(DOCKER) run -ti --rm -v $(SOURCE_TREE_PATH):/opt/${PROJECT_NAME}.sources -v $(BUILD_PATH)/${PROJECT_NAME}.build:/opt/${PROJECT_NAME}.build -v $(CCACHE_PATH):/opt/ccache -v $(BUILD_PATH)/opt/${DEST_DIR}:/opt/${DEST_DIR} -v $(SOURCE_TREE_PATH)/docker/completeBuild.sh:/opt/completeBuild.sh -w /opt $(BASE_IMAGE):$(BASE_IMAGE_VERSION) /opt/completeBuild.sh $(RUN_BUILD_AS) $(TESTRUNNER_DISABLED) $(RUN_BUILD_UID_AS)
	$(DOCKER) network rm $(DOCKER_NETWORK_NAME)
	mkdir -p $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME) && for i in $$(find $(BUILD_PATH)/${PROJECT_NAME}.build -type f -name "*deb" | grep -v CPack); do cp $$i $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME); done
	touch $(BUILD_PATH)/${PROJECT_NAME}.build/build.incremental
endef

###############################################################################
# This target uses a Docker container to build the ${PROJECT_NAME} source tree using the selected Docker image.
$(BUILD_PATH)/${PROJECT_NAME}.build/build.incremental:
	$(call compile)

buildComplete:
	$(call compile)

updateBuildComplete: updateDockerBaseImage
	$(call compile)

# Dependency to allow incremental builds.
buildIncremental: $(BUILD_PATH)/${PROJECT_NAME}.build/build.incremental
	$(DOCKER) run -ti --rm -v $(SOURCE_TREE_PATH):/opt/${PROJECT_NAME}.sources -v $(BUILD_PATH)/${PROJECT_NAME}.build:/opt/${PROJECT_NAME}.build -v $(CCACHE_PATH):/opt/ccache -v $(BUILD_PATH)/opt/${DEST_DIR}:/opt/${DEST_DIR} -v $(SOURCE_TREE_PATH)/docker/incrementalBuild.sh:/opt/incrementalBuild.sh -w /opt $(BASE_IMAGE):$(BASE_IMAGE_VERSION) /opt/incrementalBuild.sh $(RUN_BUILD_AS) YES $(RUN_BUILD_UID_AS)
	mkdir -p $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME) && for i in $$(find $(BUILD_PATH)/${PROJECT_NAME}.build -type f -name "*deb" | grep -v CPack); do cp $$i $(PACKAGES_DIR)/$(DOCKER_IMAGE_NAME); done

###############################################################################
# This target creates a new Docker image based on the selected Docker image using the freshly built binaries.
createDockerImage: createDockerImageBasedOnBaseImage createMinimalDockerImage

createDockerImageBasedOnBaseImage:
	cat $(SOURCE_TREE_PATH)/docker/Dockerfile.template | sed -e $(DOCKERFILE_BASEIMAGE) > $(BUILD_PATH)/Dockerfile
	echo "${PROJECT_NAME}.build" > $(BUILD_PATH)/.dockerignore
	echo "${PROJECT_NAME}.deb" >> $(BUILD_PATH)/.dockerignore
	echo "opt-static" >> $(BUILD_PATH)/.dockerignore
	echo "$(DOCKER_IMAGE_NAME)" >> $(BUILD_PATH)/.dockerignore
	cd $(BUILD_PATH) && $(DOCKER) build -t seresearch/$(DOCKER_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH) . | tee $(BUILD_PATH)/${PROJECT_NAME}.build/build.log || exit 1
	$(DOCKER) images | grep $$(tail -1 $(BUILD_PATH)/${PROJECT_NAME}.build/build.log | cut -f3 -d" ") | grep "latest" && exit 0 || $(DOCKER) tag $$(tail -1 $(BUILD_PATH)/${PROJECT_NAME}.build/build.log | cut -f3 -d" ") $(DOCKER_IMAGE_NAME_SHORT_NAME):latest
	$(DOCKER) tag $(DOCKER_IMAGE_NAME_SHORT_NAME):latest $(DOCKER_IMAGE_NAME_SHORT_NAME):$(VERSION)

createMinimalDockerImage:
	cat $(SOURCE_TREE_PATH)/docker/Dockerfile.minimal | sed -e $(DOCKERFILE_BASEIMAGE_MINIMAL) > $(BUILD_PATH)/Dockerfile.minimal
	$(CMAKE) -E remove_directory $(BUILD_PATH)/opt-static && $(CMAKE) -E make_directory $(BUILD_PATH)/opt-static/${DEST_DIR}/bin
	$(CMAKE) -E copy_directory $(BUILD_PATH)/opt/${DEST_DIR}/bin-static $(BUILD_PATH)/opt-static/${DEST_DIR}/bin
	echo "${PROJECT_NAME}.build" > $(BUILD_PATH)/.dockerignore
	echo "${PROJECT_NAME}.deb" >> $(BUILD_PATH)/.dockerignore
	echo "opt" >> $(BUILD_PATH)/.dockerignore
	echo "$(DOCKER_IMAGE_NAME)" >> $(BUILD_PATH)/.dockerignore
ifdef HAS_UPX
#	for i in $$(find $(BUILD_PATH)/opt-static/${DEST_DIR}/bin -type f -executable); do $(UPX) --ultra-brute $$i; done
	for i in $$(find $(BUILD_PATH)/opt-static/${DEST_DIR}/bin -type f -executable); do $(UPX) -4 $$i; done
endif
	cd $(BUILD_PATH) && $(DOCKER) build -t seresearch/$(DOCKER_MINIMAL_IMAGE_NAME_WITH_GIT_COMMITS_IN_CURRENT_BRANCH) -f Dockerfile.minimal . | tee $(BUILD_PATH)/${PROJECT_NAME}.build/build.minimal.log || exit 1
	$(DOCKER) images | grep $$(tail -1 $(BUILD_PATH)/${PROJECT_NAME}.build/build.minimal.log | cut -f3 -d" ") | grep "latest" && exit 0 || $(DOCKER) tag $$(tail -1 $(BUILD_PATH)/${PROJECT_NAME}.build/build.minimal.log | cut -f3 -d" ") $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):latest
	$(DOCKER) tag $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):latest $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):$(VERSION)

###############################################################################

exportMinimalDockerImage: createMinimalDockerImage
	$(DOCKER) save $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):latest | bzip2 -9 -c > $(shell echo $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME) | cut -f2 -d"/")-latest.tar.bz2

###############################################################################

pushDockerImage:  pushDockerImageBasedOnBaseImage pushMinimalDockerImage

pushDockerImageBasedOnBaseImage: createDockerImageBasedOnBaseImage
	$(DOCKER) push $(DOCKER_IMAGE_NAME_SHORT_NAME):latest
	$(DOCKER) push $(DOCKER_IMAGE_NAME_SHORT_NAME):$(VERSION)

pushMinimalDockerImage: createMinimalDockerImage
	$(DOCKER) push $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):latest
	$(DOCKER) push $(DOCKER_MINIMAL_IMAGE_NAME_SHORT_NAME):$(VERSION)

