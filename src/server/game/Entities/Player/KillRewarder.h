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

#ifndef KillRewarder_h__
#define KillRewarder_h__

#include <set>
#include "Define.h"

class Player;
class Unit;
class Group;

class TC_GAME_API KillRewarder
{
public:
    KillRewarder(Player* killer, Unit* victim, bool isBattleGround);

    void Reward();

private:
    void InitXP(Player* player);
    void InitGroupData();

    void RewardHonor(Player* player);
    void RewardXP(Player* player, float rate);
    void RewardReputation(Player* player, float rate);
    void RewardKillCredit(Player* player);
    void RewardPlayer(Player* player, bool isDungeon);
    void RewardGroup();

    Player* _killer;
    Unit* _victim;
    Group* _group;
    float _groupRate;
    Player* _maxNotGrayMember;
    uint32 _count;
    uint32 _sumLevel;
    uint32 _xp;
    bool _isFullXP;
    uint8 _maxLevel;
    bool _isBattleGround;
    bool _isPvP;

    std::set<uint64> _rewardedGuilds;
};

#endif // KillRewarder_h__