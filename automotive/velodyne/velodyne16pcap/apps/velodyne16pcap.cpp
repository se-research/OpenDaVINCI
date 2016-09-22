/**
 * velodyne16pcap is a program that reads VLP-16 data in .pcap format and 
 * sends out the decoded data as 3D shared point cloud, including x, y, z, and intensity (all float)
 * Copyright (C) 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Velodyne16pcap.h"

int32_t main(int32_t argc, char **argv) {
    automotive::VelodyneDecoder16pcap v16p(argc, argv);
    return v16p.runModule();
}
