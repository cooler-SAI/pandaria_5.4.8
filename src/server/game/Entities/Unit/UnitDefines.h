/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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

#ifndef UnitDefines_h__
#define UnitDefines_h__

#define BASE_MINDAMAGE 1.0f
#define BASE_MAXDAMAGE 2.0f
#define BASE_ATTACK_TIME 2000

// byte value (UNIT_FIELD_ANIM_TIER, 0)
// byte value (UNIT_FIELD_BYTES_1, 0)
enum UnitStandStateType : uint8
{
    UNIT_STAND_STATE_STAND = 0,
    UNIT_STAND_STATE_SIT = 1,
    UNIT_STAND_STATE_SIT_CHAIR = 2,
    UNIT_STAND_STATE_SLEEP = 3,
    UNIT_STAND_STATE_SIT_LOW_CHAIR = 4,
    UNIT_STAND_STATE_SIT_MEDIUM_CHAIR = 5,
    UNIT_STAND_STATE_SIT_HIGH_CHAIR = 6,
    UNIT_STAND_STATE_DEAD = 7,
    UNIT_STAND_STATE_KNEEL = 8,
    UNIT_STAND_STATE_SUBMERGED = 9,

    MAX_UNIT_STAND_STATE
};




// low byte (0 from 0..3) of UNIT_FIELD_SHAPESHIFT_FORM
// low byte (0 from 0..3) of UNIT_FIELD_BYTES_2
enum SheathState : uint8
{
    SHEATH_STATE_UNARMED = 0,                              // non prepared weapon
    SHEATH_STATE_MELEE = 1,                              // prepared melee weapon
    SHEATH_STATE_RANGED = 2,                               // prepared ranged weapon

    MAX_SHEATH_STATE
};


// byte (1 from 0..3) of UNIT_FIELD_SHAPESHIFT_FORM
// byte (1 from 0..3) of UNIT_FIELD_BYTES_2
enum UnitPVPStateFlags : uint8
{
    UNIT_BYTE2_FLAG_PVP = 0x01,
    UNIT_BYTE2_FLAG_UNK1 = 0x02,
    UNIT_BYTE2_FLAG_FFA_PVP = 0x04,
    UNIT_BYTE2_FLAG_SANCTUARY = 0x08,
    UNIT_BYTE2_FLAG_UNK4 = 0x10,
    UNIT_BYTE2_FLAG_UNK5 = 0x20,
    UNIT_BYTE2_FLAG_UNK6 = 0x40,
    UNIT_BYTE2_FLAG_UNK7 = 0x80
};



#endif // UnitDefines_h__