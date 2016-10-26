#!/bin/bash

# completeBuild.sh - Script to build OpenDaVINCI.
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

BUILD_AS=$1
TESTRUNNER_DISABLED=$2
UID_AS=$3

# Adding user for building.
groupadd $BUILD_AS
useradd $BUILD_AS -g $BUILD_AS

cat <<EOF > /opt/OpenDaVINCI.build/build.sh
#!/bin/bash
cd /opt/OpenDaVINCI.build

echo "[OpenDaVINCI Docker builder] Complete build."
export PATH=/usr/lib/ccache:$PATH
export CCACHE_DIR=/opt/ccache

cmake -E remove_directory .
cmake -D TESTRUNNER_DISABLED=$TESTRUNNER_DISABLED -D CMAKE_INSTALL_PREFIX=/opt/od4 /opt/OpenDaVINCI.sources

if [ "$TESTRUNNER_DISABLED" == "YES" ]; then
    make -j4
else
    make -j1
fi
EOF

chmod 755 /opt/OpenDaVINCI.build/build.sh
chown $UID_AS:$UID_AS /opt/OpenDaVINCI.build/build.sh
chown -R $UID_AS:$UID_AS /opt

su -m `getent passwd $UID_AS|cut -f1 -d":"` -c /opt/OpenDaVINCI.build/build.sh

