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

# Run this script as: cat <MyDBCFile.dbc> | gawk -f dbc2can.awk -v ODVD=<Name of the .odvd file>

BEGIN {
    CANMESSAGESDEFINITION = ""
    CANMAPPINGSDEFINITION = ""
    
    MessageHeader = "CAN Message"
    firstLine = 1
    mappingID = 0

    # Add "using" directive to point to .odvd file.
    if (ODVD != "") {
        CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("using %s; # This using directive points to the related .odvd file for the high-level message specifications.\n\n", gensub(/\.odvd/, "", "g", ODVD))
    }
    else {
        CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("#using <Specify your .odvd file>;\n\n")
    }
}

# Match "BO_" CAN frames and transform them to the .can format.
/^BO_/ {
    CANID = $2
    BYTES = gensub(/\:/, "", "g", $4)
    NAME = gensub(/\:/, "", "g", $3)
    
    if (1 == firstLine) {
        firstLine = 0
    }
    else {
        CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("}\n\n")
        CANMAPPINGSDEFINITION = CANMAPPINGSDEFINITION sprintf("#}\n\n")
        mappingID = 0
    }
    
    CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("%s 0x%x %s is %d bytes {\n", MessageHeader, CANID, tolower(NAME), BYTES)
    CANMAPPINGSDEFINITION = CANMAPPINGSDEFINITION "#unordered mapping <full qualified message name from your .odvd file> { # Mapping for CAN message '" NAME "'; example namespace.subnamespace.Message \n"
}

# Match "SG_" signals and transform them to the .can format.
/^.SG_ / {
    INPUT = gensub(/\:/, " ", "g", $0)
    INPUT = gensub(/\|/, " ", "g", INPUT)
    INPUT = gensub(/\ /, " ", "g", INPUT)
    INPUT = gensub(/@/, " ", "g", INPUT)
    INPUT = gensub(/\(/, " ", "g", INPUT)
    INPUT = gensub(/\)/, " ", "g", INPUT)
    INPUT = gensub(/\[/, " ", "g", INPUT)
    INPUT = gensub(/\]/, " ", "g", INPUT)
    INPUT = gensub(/\,/, " ", "g", INPUT)
    split(INPUT, SIGNAL, " ")
    
    # Capture endianness.
    if (SIGNAL[5] == "0+" || SIGNAL[5] == "0-") {
        ENDIAN = "big"
    }
    else {
        ENDIAN = "little"
    }

    # Capture signedness.
    if (SIGNAL[5] == "0+" || SIGNAL[5] == "1+") {
        SIGNED = "unsigned"
    }
    else {
        SIGNED = "signed"
    }
    
    # Convert scientific notation to decimal.
    if(index(SIGNAL[6], "E") != 0) {
        SIGNAL[6] = sprintf("%.12f", SIGNAL[6])
    }
    if(index(SIGNAL[7], "E") != 0) {
        SIGNAL[7] = sprintf("%.12f", SIGNAL[7])
    }
    if(index(SIGNAL[8], "E") != 0) {
        SIGNAL[8] = sprintf("%.12f", SIGNAL[8])
    }
    if(index(SIGNAL[9], "E") != 0) {
        SIGNAL[9] = sprintf("%.12f", SIGNAL[9])
    }

    # Increment the mapping ID.
    ++mappingID

    CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("\t%s at bit %s for %s bit is %s %s endian multiply by %s add %s with range [%s, %s];\n", tolower(SIGNAL[2]), SIGNAL[3], SIGNAL[4], SIGNED, ENDIAN, SIGNAL[6], SIGNAL[7], SIGNAL[8], SIGNAL[9])
    CANMAPPINGSDEFINITION = CANMAPPINGSDEFINITION sprintf("#\t%s.%s : %d; # The value following ':' must correspond to the field with the index '%d' in the respective high-level message defined in your .odvd file; otherwise, the mapping at runtime will fail.\n", tolower(NAME), tolower(SIGNAL[2]), mappingID, mappingID)
}

END {
    # Close the last message/mapping.
    CANMESSAGESDEFINITION = CANMESSAGESDEFINITION sprintf("}\n")
    CANMAPPINGSDEFINITION = CANMAPPINGSDEFINITION sprintf("#}\n\n")
    
    # Print the resulting output.
    printf("%s \n%s", CANMESSAGESDEFINITION, CANMAPPINGSDEFINITION)
}

