/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "UtilACE.h"
#include "Common.h"
#include "Errors.h" // for ASSERT
#include <memory>
#include <random>

#include <ace/Guard_T.h>
#include <ace/INET_Addr.h>

/// Check if the string is a valid ip address representation
bool IsIPAddress(char const* ipaddress)
{
    if (!ipaddress)
        return false;

    // Let the big boys do it.
    // Drawback: all valid ip address formats are recognized e.g.: 12.23, 121234, 0xABCD)
    return inet_addr(ipaddress) != INADDR_NONE;
}

std::string GetAddressString(ACE_INET_Addr const& addr)
{
    char buf[ACE_MAX_FULLY_QUALIFIED_NAME_LEN + 16];
    addr.addr_to_string(buf, ACE_MAX_FULLY_QUALIFIED_NAME_LEN + 16);
    return buf;
}

bool IsIPAddrInNetwork(ACE_INET_Addr const& net, ACE_INET_Addr const& addr, ACE_INET_Addr const& subnetMask)
{
    uint32 mask = subnetMask.get_ip_address();
    if ((net.get_ip_address() & mask) == (addr.get_ip_address() & mask))
        return true;
    return false;
}
