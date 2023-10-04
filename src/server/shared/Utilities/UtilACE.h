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

#ifndef _UTILACE_H
#define _UTILACE_H

#include "Common.h"
#include "Duration.h"
#include "Errors.h"

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <ctime>
#include <array>
#include <limits>

class ACE_INET_Addr;

bool IsIPAddress(char const* ipaddress);

/// Checks if address belongs to the a network with specified submask
bool IsIPAddrInNetwork(ACE_INET_Addr const& net, ACE_INET_Addr const& addr, ACE_INET_Addr const& subnetMask);

/// Transforms ACE_INET_Addr address into string format "dotted_ip:port"
std::string GetAddressString(ACE_INET_Addr const& addr);


#endif
