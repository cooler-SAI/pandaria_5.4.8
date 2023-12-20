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

#ifndef SF_TRINITY_CHANNELMGR_H
#define SF_TRINITY_CHANNELMGR_H

#include "Common.h"
#include "Channel.h"

#include <map>
#include <string>

#include "World.h"

class ChannelMgr
{
    typedef std::map<std::wstring, Channel*> ChannelMap;

    protected:
        explicit ChannelMgr(uint32 team) : team(team) { }
        ~ChannelMgr();

    public:

        static ChannelMgr * forTeam(uint32 team);
        void setTeam(uint32 newTeam) { team = newTeam; }

        Channel* GetJoinChannel(std::string const& name, uint32 channel_id);
        Channel* GetChannel(std::string const& name, Player* p, bool pkt = true);
        void LeftChannel(std::string const& name);

    private:
        ChannelMap channels;
        uint32 team;

        void MakeNotOnPacket(WorldPacket* data, std::string const& name);
};

#endif
