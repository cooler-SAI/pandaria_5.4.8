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

#ifndef TRINITY_SHAREDDEFINES_H
#define TRINITY_SHAREDDEFINES_H

#include "DetourNavMesh.h"
#include "Define.h"
#include <cassert>

#define MAX_CREATURE_BASE_HP 5
#define MAX_CREATURE_BASE_DAMAGE 5

enum SpellEffIndex
{
    EFFECT_0 = 0,
    EFFECT_1 = 1,
    EFFECT_2 = 2,
    EFFECT_3 = 3,
    EFFECT_4 = 4,
    EFFECT_5 = 5,
    EFFECT_6 = 6,
    EFFECT_7 = 7,
    EFFECT_8 = 8,
    EFFECT_9 = 9,
    EFFECT_10 = 10,
    EFFECT_11 = 11,
    EFFECT_12 = 12,
    EFFECT_13 = 13,
    EFFECT_14 = 14,
    EFFECT_15 = 15,
    EFFECT_16 = 16,
    EFFECT_17 = 17,
    EFFECT_18 = 18,
    EFFECT_19 = 19,
    EFFECT_20 = 20,
    EFFECT_21 = 21,
    EFFECT_22 = 22,
    EFFECT_23 = 23,
    EFFECT_24 = 24,
    EFFECT_25 = 25,
    EFFECT_26 = 26,
    EFFECT_27 = 27,
    EFFECT_28 = 28,
    EFFECT_29 = 29,
    EFFECT_30 = 30,
    EFFECT_31 = 31
};

// used in script definitions
#define EFFECT_FIRST_FOUND 254
#define EFFECT_ALL 255

// loot modes for creatures and gameobjects, bitmask!
enum LootModes
{
    LOOT_MODE_DEFAULT                  = 0x1,
    LOOT_MODE_HARD_MODE_1              = 0x2,
    LOOT_MODE_HARD_MODE_2              = 0x4,
    LOOT_MODE_HARD_MODE_3              = 0x8,
    LOOT_MODE_HARD_MODE_4              = 0x10
};

enum Expansions
{
    EXPANSION_CLASSIC = 0,
    EXPANSION_THE_BURNING_CRUSADE = 1,
    EXPANSION_WRATH_OF_THE_LICH_KING = 2,
    EXPANSION_CATACLYSM = 3,
    EXPANSION_MISTS_OF_PANDARIA = 4,
    MAX_EXPANSIONS = 5
};

enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2,
    GENDER_BOTH                        = 3
};

// Race value is index in ChrRaces.dbc
enum Races
{
    RACE_NONE               = 0,
    RACE_HUMAN              = 1,
    RACE_ORC                = 2,
    RACE_DWARF              = 3,
    RACE_NIGHTELF           = 4,
    RACE_UNDEAD_PLAYER      = 5,
    RACE_TAUREN             = 6,
    RACE_GNOME              = 7,
    RACE_TROLL              = 8,
    RACE_GOBLIN             = 9,
    RACE_BLOODELF           = 10,
    RACE_DRAENEI            = 11,
    //RACE_FEL_ORC            = 12,
    //RACE_NAGA               = 13,
    //RACE_BROKEN             = 14,
    //RACE_SKELETON           = 15,
    //RACE_VRYKUL             = 16,
    //RACE_TUSKARR            = 17,
    //RACE_FOREST_TROLL       = 18,
    //RACE_TAUNKA             = 19,
    //RACE_NORTHREND_SKELETON = 20,
    //RACE_ICE_TROLL          = 21,
    RACE_WORGEN             = 22,
    //RACE_GILNEAN            = 23
    RACE_PANDAREN_NEUTRAL   = 24,
    RACE_PANDAREN_ALLIANCE  = 25,
    RACE_PANDAREN_HORDE     = 26,

    // max+1 for player race
    MAX_RACES               = 27,

    RACEMASK_ALL_PLAYABLE   =   (1<<(RACE_HUMAN-1))   |(1<<(RACE_ORC-1))          |(1<<(RACE_DWARF-1))   |
                                (1<<(RACE_NIGHTELF-1))|(1<<(RACE_UNDEAD_PLAYER-1))|(1<<(RACE_TAUREN-1))  |
                                (1<<(RACE_GNOME-1))   |(1<<(RACE_TROLL-1))        |(1<<(RACE_BLOODELF-1))|
                                (1<<(RACE_DRAENEI-1)) |(1<<(RACE_GOBLIN-1))       |(1<<(RACE_WORGEN-1))  |
                                (1<<(RACE_PANDAREN_NEUTRAL-1)) | (1<<(RACE_PANDAREN_ALLIANCE-1)) | (1<<(RACE_PANDAREN_HORDE-1)),

    RACEMASK_ALLIANCE       =   (1<<(RACE_HUMAN-1)) | (1<<(RACE_DWARF-1)) | (1<<(RACE_NIGHTELF-1)) |
                                (1<<(RACE_GNOME-1)) | (1<<(RACE_DRAENEI-1)) | (1<<(RACE_WORGEN-1)) |
                                (1<<(RACE_PANDAREN_NEUTRAL-1)) | (1<<(RACE_PANDAREN_ALLIANCE-1)),

    RACEMASK_HORDE  = RACEMASK_ALL_PLAYABLE & ~RACEMASK_ALLIANCE
};

// Class value is index in ChrClasses.dbc
enum Classes
{
    CLASS_NONE          = 0,
    CLASS_WARRIOR       = 1,
    CLASS_PALADIN       = 2,
    CLASS_HUNTER        = 3,
    CLASS_ROGUE         = 4,
    CLASS_PRIEST        = 5,
    CLASS_DEATH_KNIGHT  = 6,
    CLASS_SHAMAN        = 7,
    CLASS_MAGE          = 8,
    CLASS_WARLOCK       = 9,
    CLASS_MONK          = 10,
    CLASS_DRUID         = 11
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1)) | \
    (1<<(CLASS_DEATH_KNIGHT-1)) | (1<<(CLASS_MONK-1)))

#define CLASSMASK_SHADOW_MOURNE  ((1 << (CLASS_WARRIOR - 1)) | (1 << (CLASS_PALADIN - 1)) | (1 << (CLASS_DEATH_KNIGHT - 1)))
#define CLASSMASK_DRAGONWRATH  ((1 << (CLASS_PRIEST - 1)) | (1 << (CLASS_SHAMAN - 1)) | (1 << (CLASS_MAGE - 1))  | (1 << (CLASS_WARLOCK - 1))  | (1 << (CLASS_MONK - 1))  | (1 << (CLASS_DRUID - 1)))
#define CLASSMASK_FANGS_OF_THE_FATHER  (1 << (CLASS_ROGUE - 1))

// valid classes for creature_template.unit_class
enum UnitClass
{
    UNIT_CLASS_WARRIOR                  = 1,
    UNIT_CLASS_PALADIN                  = 2,
    UNIT_CLASS_ROGUE                    = 4,
    UNIT_CLASS_MAGE                     = 8
};

#define CLASSMASK_ALL_CREATURES ((1<<(UNIT_CLASS_WARRIOR-1)) | (1<<(UNIT_CLASS_PALADIN-1)) | (1<<(UNIT_CLASS_ROGUE-1)) | (1<<(UNIT_CLASS_MAGE-1)))

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

#define PLAYER_MAX_BATTLEGROUND_QUEUES 2

enum ReputationRank
{
    REP_HATED       = 0,
    REP_HOSTILE     = 1,
    REP_UNFRIENDLY  = 2,
    REP_NEUTRAL     = 3,
    REP_FRIENDLY    = 4,
    REP_HONORED     = 5,
    REP_REVERED     = 6,
    REP_EXALTED     = 7
};

#define MIN_REPUTATION_RANK (REP_HATED)
#define MAX_REPUTATION_RANK 8

#define MAX_SPILLOVER_FACTIONS 5

enum MoneyConstants
{
    COPPER = 1,
    SILVER = COPPER*100,
    GOLD   = SILVER*100
};

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    POWER_MANA                          = 0,
    POWER_RAGE                          = 1,
    POWER_FOCUS                         = 2,
    POWER_ENERGY                        = 3,
    POWER_LIGHT_FORCE                   = 4, // unused since 5.1.0 - WOD NOTE: POWER_COMBO_POINTS
    POWER_RUNES                         = 5,
    POWER_RUNIC_POWER                   = 6,
    POWER_SOUL_SHARDS                   = 7,
    POWER_ECLIPSE                       = 8,
    POWER_HOLY_POWER                    = 9,
    POWER_ALTERNATE_POWER               = 10,
    POWER_DARK_FORCE                    = 11,
    POWER_CHI                           = 12,
    POWER_SHADOW_ORBS                   = 13,
    POWER_BURNING_EMBERS                = 14,
    POWER_DEMONIC_FURY                  = 15,
    POWER_ARCANE_CHARGES                = 16,
    MAX_POWERS                          = 17,
    POWER_ALL                           = 127,
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS_PER_CLASS            5

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6
};

#define MAX_SPELL_SCHOOL                  7

enum SpellSchoolMask
{
    SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
    SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
    SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY),
    SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE),
    SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
    SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST),
    SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
    SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

    // unions

    // 124, not include normal and holy damage
    SPELL_SCHOOL_MASK_SPELL   = (SPELL_SCHOOL_MASK_FIRE   |
                                  SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
                                  SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE),
    // 126
    SPELL_SCHOOL_MASK_MAGIC   = (SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL),

    // 127
    SPELL_SCHOOL_MASK_ALL     = (SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC)
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
    for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
        if (mask & (1 << i))
            return SpellSchools(i);

    return SPELL_SCHOOL_NORMAL;
}

enum ItemQualities
{
    ITEM_QUALITY_POOR                  = 0,                 //GREY
    ITEM_QUALITY_NORMAL                = 1,                 //WHITE
    ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
    ITEM_QUALITY_RARE                  = 3,                 //BLUE
    ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
    ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
    ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
    ITEM_QUALITY_HEIRLOOM              = 7
};

#define MAX_ITEM_QUALITY                 8

enum SpellCategory
{
    SPELL_CATEGORY_FOOD             = 11,
    SPELL_CATEGORY_DRINK            = 59
};

const uint32 ItemQualityColors[MAX_ITEM_QUALITY] =
{
    0xff9d9d9d,        //GREY
    0xffffffff,        //WHITE
    0xff1eff00,        //GREEN
    0xff0070dd,        //BLUE
    0xffa335ee,        //PURPLE
    0xffff8000,        //ORANGE
    0xffe6cc80,        //LIGHT YELLOW
    0xffe6cc80         //LIGHT YELLOW
};

// ***********************************
// Spell Attributes definitions
// ***********************************

enum SpellAttr0
{
    SPELL_ATTR0_UNK0                             = 0x00000001, //  0
    SPELL_ATTR0_REQ_AMMO                         = 0x00000002, //  1 on next ranged
    SPELL_ATTR0_ON_NEXT_SWING                    = 0x00000004, //  2
    SPELL_ATTR0_IS_REPLENISHMENT                 = 0x00000008, //  3 not set in 3.0.3
    SPELL_ATTR0_ABILITY                          = 0x00000010, //  4 client puts 'ability' instead of 'spell' in game strings for these spells
    SPELL_ATTR0_TRADESPELL                       = 0x00000020, //  5 trade spells (recipes), will be added by client to a sublist of profession spell
    SPELL_ATTR0_PASSIVE                          = 0x00000040, //  6 Passive spell
    SPELL_ATTR0_HIDDEN_CLIENTSIDE                = 0x00000080, //  7 Spells with this attribute are not visible in spellbook or aura bar
    SPELL_ATTR0_HIDE_IN_COMBAT_LOG               = 0x00000100, //  8 This attribite controls whether spell appears in combat logs
    SPELL_ATTR0_TARGET_MAINHAND_ITEM             = 0x00000200, //  9 Client automatically selects item from mainhand slot as a cast target
    SPELL_ATTR0_ON_NEXT_SWING_2                  = 0x00000400, // 10
    SPELL_ATTR0_UNK11                            = 0x00000800, // 11
    SPELL_ATTR0_DAYTIME_ONLY                     = 0x00001000, // 12 only useable at daytime, not set in 2.4.2
    SPELL_ATTR0_NIGHT_ONLY                       = 0x00002000, // 13 only useable at night, not set in 2.4.2
    SPELL_ATTR0_INDOORS_ONLY                     = 0x00004000, // 14 only useable indoors, not set in 2.4.2
    SPELL_ATTR0_OUTDOORS_ONLY                    = 0x00008000, // 15 Only useable outdoors.
    SPELL_ATTR0_NOT_SHAPESHIFT                   = 0x00010000, // 16 Not while shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                   = 0x00020000, // 17 Must be in stealth
    SPELL_ATTR0_DONT_AFFECT_SHEATH_STATE         = 0x00040000, // 18 client won't hide unit weapons in sheath on cast/channel
    SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION         = 0x00080000, // 19 spelldamage depends on caster level
    SPELL_ATTR0_STOP_ATTACK_TARGET               = 0x00100000, // 20 Stop attack after use this spell (and not begin attack if use)
    SPELL_ATTR0_IMPOSSIBLE_DODGE_PARRY_BLOCK     = 0x00200000, // 21 Cannot be dodged/parried/blocked
    SPELL_ATTR0_CAST_TRACK_TARGET                = 0x00400000, // 22 Client automatically forces player to face target when casting
    SPELL_ATTR0_CASTABLE_WHILE_DEAD              = 0x00800000, // 23 castable while dead?
    SPELL_ATTR0_CASTABLE_WHILE_MOUNTED           = 0x01000000, // 24 castable while mounted
    SPELL_ATTR0_DISABLED_WHILE_ACTIVE            = 0x02000000, // 25 Activate and start cooldown after aura fade or remove summoned creature or go
    SPELL_ATTR0_NEGATIVE_1                       = 0x04000000, // 26 Many negative spells have this attr
    SPELL_ATTR0_CASTABLE_WHILE_SITTING           = 0x08000000, // 27 castable while sitting
    SPELL_ATTR0_CANT_USED_IN_COMBAT              = 0x10000000, // 28 Cannot be used in combat
    SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY    = 0x20000000, // 29 unaffected by invulnerability (hmm possible not...)
    SPELL_ATTR0_BREAKABLE_BY_DAMAGE              = 0x40000000, // 30 random chance the effect will end TODO: implement core support
    SPELL_ATTR0_CANT_CANCEL                      = 0x80000000  // 31 positive aura can't be canceled
};

enum SpellAttr1
{
    SPELL_ATTR1_DISMISS_PET                      = 0x00000001, //  0 for spells without this flag client doesn't allow to summon pet if caster has a pet
    SPELL_ATTR1_DRAIN_ALL_POWER                  = 0x00000002, //  1 use all power (Only paladin Lay of Hands and Bunyanize)
    SPELL_ATTR1_CHANNELED_1                      = 0x00000004, //  2 clientside checked? cancelable?
    SPELL_ATTR1_CANT_BE_REDIRECTED               = 0x00000008, //  3
    SPELL_ATTR1_UNK4                             = 0x00000010, //  4 stealth and whirlwind
    SPELL_ATTR1_NOT_BREAK_STEALTH                = 0x00000020, //  5 Not break stealth
    SPELL_ATTR1_CHANNELED_2                      = 0x00000040, //  6
    SPELL_ATTR1_CANT_BE_REFLECTED                = 0x00000080, //  7
    SPELL_ATTR1_CANT_TARGET_IN_COMBAT            = 0x00000100, //  8 can target only out of combat units
    SPELL_ATTR1_MELEE_COMBAT_START               = 0x00000200, //  9 player starts melee combat after this spell is cast
    SPELL_ATTR1_NO_THREAT                        = 0x00000400, // 10 no generates threat on cast 100% (old NO_INITIAL_AGGRO)
    SPELL_ATTR1_UNK11                            = 0x00000800, // 11 aura
    SPELL_ATTR1_IS_PICKPOCKET                    = 0x00001000, // 12 Pickpocket
    SPELL_ATTR1_FARSIGHT                         = 0x00002000, // 13 Client removes farsight on aura loss
    SPELL_ATTR1_CHANNEL_TRACK_TARGET             = 0x00004000, // 14 Client automatically forces player to face target when channeling
    SPELL_ATTR1_DISPEL_AURAS_ON_IMMUNITY         = 0x00008000, // 15 remove auras on immunity
    SPELL_ATTR1_UNAFFECTED_BY_SCHOOL_IMMUNE      = 0x00010000, // 16 on immuniy
    SPELL_ATTR1_UNAUTOCASTABLE_BY_PET            = 0x00020000, // 17
    SPELL_ATTR1_UNK18                            = 0x00040000, // 18 stun, polymorph, daze, hex
    SPELL_ATTR1_CANT_TARGET_SELF                 = 0x00080000, // 19
    SPELL_ATTR1_REQ_COMBO_POINTS1                = 0x00100000, // 20 Req combo points on target
    SPELL_ATTR1_UNK21                            = 0x00200000, // 21
    SPELL_ATTR1_REQ_COMBO_POINTS2                = 0x00400000, // 22 Req combo points on target
    SPELL_ATTR1_UNK23                            = 0x00800000, // 23
    SPELL_ATTR1_IS_FISHING                       = 0x01000000, // 24 only fishing spells
    SPELL_ATTR1_UNK25                            = 0x02000000, // 25
    SPELL_ATTR1_UNK26                            = 0x04000000, // 26 works correctly with [target=focus] and [target=mouseover] macros?
    SPELL_ATTR1_UNK27                            = 0x08000000, // 27 melee spell?
    SPELL_ATTR1_DONT_DISPLAY_IN_AURA_BAR         = 0x10000000, // 28 client doesn't display these spells in aura bar
    SPELL_ATTR1_CHANNEL_DISPLAY_SPELL_NAME       = 0x20000000, // 29 spell name is displayed in cast bar instead of 'channeling' text
    SPELL_ATTR1_ENABLE_AT_DODGE                  = 0x40000000, // 30 Overpower
    SPELL_ATTR1_UNK31                            = 0x80000000  // 31
};

enum SpellAttr2
{
    SPELL_ATTR2_CAN_TARGET_DEAD                  = 0x00000001, //  0 can target dead unit or corpse
    SPELL_ATTR2_UNK1                             = 0x00000002, //  1 vanish, shadowform, Ghost Wolf and other
    SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS            = 0x00000004, //  2 26368 4.0.1 dbc change
    SPELL_ATTR2_UNK3                             = 0x00000008, //  3
    SPELL_ATTR2_DISPLAY_IN_STANCE_BAR            = 0x00000010, //  4 client displays icon in stance bar when learned, even if not shapeshift
    SPELL_ATTR2_AUTOREPEAT_FLAG                  = 0x00000020, //  5
    SPELL_ATTR2_CANT_TARGET_TAPPED               = 0x00000040, //  6 target must be tapped by caster
    SPELL_ATTR2_UNK7                             = 0x00000080, //  7
    SPELL_ATTR2_UNK8                             = 0x00000100, //  8 not set in 3.0.3
    SPELL_ATTR2_UNK9                             = 0x00000200, //  9
    SPELL_ATTR2_UNK10                            = 0x00000400, // 10 related to tame
    SPELL_ATTR2_HEALTH_FUNNEL                    = 0x00000800, // 11
    SPELL_ATTR2_UNK12                            = 0x00001000, // 12 Cleave, Heart Strike, Maul, Sunder Armor, Swipe
    SPELL_ATTR2_PRESERVE_ENCHANT_IN_ARENA        = 0x00002000, // 13 Items enchanted by spells with this flag preserve the enchant to arenas
    SPELL_ATTR2_UNK14                            = 0x00004000, // 14
    SPELL_ATTR2_UNK15                            = 0x00008000, // 15 not set in 3.0.3
    SPELL_ATTR2_TAME_BEAST                       = 0x00010000, // 16
    SPELL_ATTR2_NOT_RESET_AUTO_ACTIONS           = 0x00020000, // 17 don't reset timers for melee autoattacks (swings) or ranged autoattacks (autoshoots)
    SPELL_ATTR2_REQ_DEAD_PET                     = 0x00040000, // 18 Only Revive pet and Heart of the Pheonix
    SPELL_ATTR2_NOT_NEED_SHAPESHIFT              = 0x00080000, // 19 does not necessarly need shapeshift
    SPELL_ATTR2_UNK20                            = 0x00100000, // 20
    SPELL_ATTR2_DAMAGE_REDUCED_SHIELD            = 0x00200000, // 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
    SPELL_ATTR2_UNK22                            = 0x00400000, // 22 Ambush, Backstab, Cheap Shot, Death Grip, Garrote, Judgements, Mutilate, Pounce, Ravage, Shiv, Shred
    SPELL_ATTR2_IS_ARCANE_CONCENTRATION          = 0x00800000, // 23 Only mage Arcane Concentration have this flag
    SPELL_ATTR2_UNK24                            = 0x01000000, // 24
    SPELL_ATTR2_UNK25                            = 0x02000000, // 25
    SPELL_ATTR2_NOT_DISPELED_BY_SCHOOL_IMMUNITY  = 0x04000000, // 26 unaffected by school immunity
    SPELL_ATTR2_UNK27                            = 0x08000000, // 27
    SPELL_ATTR2_UNK28                            = 0x10000000, // 28
    SPELL_ATTR2_CANT_CRIT                        = 0x20000000, // 29 Spell can't crit
    SPELL_ATTR2_TRIGGERED_CAN_TRIGGER_PROC       = 0x40000000, // 30 spell can trigger even if triggered
    SPELL_ATTR2_FOOD_BUFF                        = 0x80000000  // 31 Food or Drink Buff (like Well Fed)
};

enum SpellAttr3
{
    SPELL_ATTR3_UNK0                             = 0x00000001, //  0
    SPELL_ATTR3_UNK1                             = 0x00000002, //  1
    SPELL_ATTR3_UNK2                             = 0x00000004, //  2
    SPELL_ATTR3_BLOCKABLE_SPELL                  = 0x00000008, //  3 Only dmg class melee in 3.1.3
    SPELL_ATTR3_IGNORE_RESURRECTION_TIMER        = 0x00000010, //  4 you don't have to wait to be resurrected with these spells
    SPELL_ATTR3_UNK5                             = 0x00000020, //  5
    SPELL_ATTR3_UNK6                             = 0x00000040, //  6
    SPELL_ATTR3_STACK_FOR_DIFF_CASTERS           = 0x00000080, //  7 separate stack for every caster
    SPELL_ATTR3_ONLY_TARGET_PLAYERS              = 0x00000100, //  8 can only target players
    SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2     = 0x00000200, //  9 triggered from effect?
    SPELL_ATTR3_MAIN_HAND                        = 0x00000400, // 10 Main hand weapon required
    SPELL_ATTR3_BATTLEGROUND                     = 0x00000800, // 11 Can casted only on battleground
    SPELL_ATTR3_ONLY_TARGET_GHOSTS               = 0x00001000, // 12
    SPELL_ATTR3_UNK13                            = 0x00002000, // 13
    SPELL_ATTR3_IS_HONORLESS_TARGET              = 0x00004000, // 14 "Honorless Target" only this spells have this flag
    SPELL_ATTR3_UNK15                            = 0x00008000, // 15 Auto Shoot, Shoot, Throw,  - this is autoshot flag
    SPELL_ATTR3_CANT_TRIGGER_PROC                = 0x00010000, // 16 confirmed with many patchnotes
    SPELL_ATTR3_NO_INITIAL_AGGRO                 = 0x00020000, // 17 Soothe Animal, 39758, Mind Soothe
    SPELL_ATTR3_IGNORE_HIT_RESULT                = 0x00040000, // 18 Spell should always hit its target
    SPELL_ATTR3_DISABLE_PROC                     = 0x00080000, // 19 during aura proc no spells can trigger (20178, 20375)
    SPELL_ATTR3_DEATH_PERSISTENT                 = 0x00100000, // 20 Death persistent spells
    SPELL_ATTR3_UNK21                            = 0x00200000, // 21 unused
    SPELL_ATTR3_REQ_WAND                         = 0x00400000, // 22 Req wand
    SPELL_ATTR3_UNK23                            = 0x00800000, // 23
    SPELL_ATTR3_REQ_OFFHAND                      = 0x01000000, // 24 Req offhand weapon
    SPELL_ATTR3_NO_PUSHBACK_ON_DAMAGE            = 0x02000000, // 25 no cause spell pushback ?
    SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED          = 0x04000000, // 26 auras with this attribute can proc from triggered spell casts with SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2 (67736 + 52999)
    SPELL_ATTR3_DRAIN_SOUL                       = 0x08000000, // 27 only drain soul has this flag
    SPELL_ATTR3_UNK28                            = 0x10000000, // 28
    SPELL_ATTR3_NO_DONE_BONUS                    = 0x20000000, // 29 Ignore caster spellpower and done damage mods?  client doesn't apply spellmods for those spells
    SPELL_ATTR3_DONT_DISPLAY_RANGE               = 0x40000000, // 30 client doesn't display range in tooltip for those spells
    SPELL_ATTR3_UNK31                            = 0x80000000  // 31
};

enum SpellAttr4
{
    SPELL_ATTR4_IGNORE_RESISTANCES               = 0x00000001, //  0 spells with this attribute will completely ignore the target's resistance (these spells can't be resisted)
    SPELL_ATTR4_PROC_ONLY_ON_CASTER              = 0x00000002, //  1 proc only on effects with TARGET_UNIT_CASTER?
    SPELL_ATTR4_UNK2                             = 0x00000004, //  2
    SPELL_ATTR4_UNK3                             = 0x00000008, //  3
    SPELL_ATTR4_UNK4                             = 0x00000010, //  4 This will no longer cause guards to attack on use??
    SPELL_ATTR4_UNK5                             = 0x00000020, //  5
    SPELL_ATTR4_NOT_STEALABLE                    = 0x00000040, //  6 although such auras might be dispellable, they cannot be stolen
    SPELL_ATTR4_TRIGGERED                        = 0x00000080, //  7 spells forced to be triggered
    SPELL_ATTR4_FIXED_DAMAGE                     = 0x00000100, //  8 ignores taken percent damage mods?
    SPELL_ATTR4_TRIGGER_ACTIVATE                 = 0x00000200, //  9 initially disabled / trigger activate from event (Execute, Riposte, Deep Freeze end other)
    SPELL_ATTR4_SPELL_VS_EXTEND_COST             = 0x00000400, // 10 Rogue Shiv have this flag
    SPELL_ATTR4_UNK11                            = 0x00000800, // 11
    SPELL_ATTR4_UNK12                            = 0x00001000, // 12
    SPELL_ATTR4_UNK13                            = 0x00002000, // 13
    SPELL_ATTR4_DAMAGE_DOESNT_BREAK_AURAS        = 0x00004000, // 14 doesn't break auras by damage from these spells
    SPELL_ATTR4_UNK15                            = 0x00008000, // 15
    SPELL_ATTR4_NOT_USABLE_IN_ARENA_OR_RATED_BG  = 0x00010000, // 16 Cannot be used in both Arenas or Rated Battlegrounds
    SPELL_ATTR4_USABLE_IN_ARENA                  = 0x00020000, // 17
    SPELL_ATTR4_AREA_TARGET_CHAIN                = 0x00040000, // 18 (NYI)hits area targets one after another instead of all at once
    SPELL_ATTR4_UNK19                            = 0x00080000, // 19 proc dalayed, after damage or don't proc on absorb?
    SPELL_ATTR4_NOT_CHECK_SELFCAST_POWER         = 0x00100000, // 20 supersedes message "More powerful spell applied" for self casts.
    SPELL_ATTR4_UNK21                            = 0x00200000, // 21 Pally aura, dk presence, dudu form, warrior stance, shadowform, hunter track
    SPELL_ATTR4_UNK22                            = 0x00400000, // 22 Seal of Command (42058, 57770) and Gymer's Smash 55426
    SPELL_ATTR4_UNK23                            = 0x00800000, // 23
    SPELL_ATTR4_UNK24                            = 0x01000000, // 24 some shoot spell
    SPELL_ATTR4_IS_PET_SCALING                   = 0x02000000, // 25 pet scaling auras
    SPELL_ATTR4_CAST_ONLY_IN_OUTLAND             = 0x04000000, // 26 Can only be used in Outland.
    SPELL_ATTR4_UNK27                            = 0x08000000, // 27
    SPELL_ATTR4_UNK28                            = 0x10000000, // 28 Aimed Shot
    SPELL_ATTR4_UNK29                            = 0x20000000, // 29
    SPELL_ATTR4_UNK30                            = 0x40000000, // 30
    SPELL_ATTR4_UNK31                            = 0x80000000  // 31 Polymorph (chicken) 228 and Sonic Boom (38052, 38488)
};

enum SpellAttr5
{
    SPELL_ATTR5_UNK0                             = 0x00000001, //  0
    SPELL_ATTR5_NO_REAGENT_WHILE_PREP            = 0x00000002, //  1 not need reagents if UNIT_FLAG_PREPARATION
    SPELL_ATTR5_UNK2                             = 0x00000004, //  2
    SPELL_ATTR5_USABLE_WHILE_STUNNED             = 0x00000008, //  3 usable while stunned
    SPELL_ATTR5_UNK4                             = 0x00000010, //  4
    SPELL_ATTR5_SINGLE_TARGET_SPELL              = 0x00000020, //  5 Only one target can be apply at a time
    SPELL_ATTR5_UNK6                             = 0x00000040, //  6
    SPELL_ATTR5_UNK7                             = 0x00000080, //  7
    SPELL_ATTR5_UNK8                             = 0x00000100, //  8
    SPELL_ATTR5_START_PERIODIC_AT_APPLY          = 0x00000200, //  9 begin periodic tick at aura apply
    SPELL_ATTR5_HIDE_DURATION                    = 0x00000400, // 10 do not send duration to client
    SPELL_ATTR5_ALLOW_TARGET_OF_TARGET_AS_TARGET = 0x00000800, // 11 (NYI) uses target's target as target if original target not valid (intervene for example)
    SPELL_ATTR5_UNK12                            = 0x00001000, // 12 Cleave related?
    SPELL_ATTR5_HASTE_AFFECT_DURATION            = 0x00002000, // 13 haste effects decrease duration of this
    SPELL_ATTR5_UNK14                            = 0x00004000, // 14
    SPELL_ATTR5_UNK15                            = 0x00008000, // 15 Inflits on multiple targets?
    SPELL_ATTR5_SPECIAL_ITEM_CLASS_CHECK         = 0x00010000, // 16 this allows spells with EquippedItemClass to affect spells from other items if the required item is equipped
    SPELL_ATTR5_USABLE_WHILE_FEARED              = 0x00020000, // 17 usable while feared
    SPELL_ATTR5_USABLE_WHILE_CONFUSED            = 0x00040000, // 18 usable while confused
    SPELL_ATTR5_DONT_TURN_DURING_CAST            = 0x00080000, // 19 Blocks caster's turning when casting (client does not automatically turn caster's model to face UNIT_FIELD_TARGET)
    SPELL_ATTR5_UNK20                            = 0x00100000, // 20
    SPELL_ATTR5_UNK21                            = 0x00200000, // 21
    SPELL_ATTR5_UNK22                            = 0x00400000, // 22
    SPELL_ATTR5_UNK23                            = 0x00800000, // 23
    SPELL_ATTR5_UNK24                            = 0x01000000, // 24
    SPELL_ATTR5_UNK25                            = 0x02000000, // 25
    SPELL_ATTR5_UNK26                            = 0x04000000, // 26 aoe related - Boulder, Cannon, Corpse Explosion, Fire Nova, Flames, Frost Bomb, Living Bomb, Seed of Corruption, Starfall, Thunder Clap, Volley
    SPELL_ATTR5_DONT_SHOW_AURA_IF_SELF_CAST      = 0x08000000, // 27 Auras with this attribute are not visible on units that are the caster
    SPELL_ATTR5_DONT_SHOW_AURA_IF_NOT_SELF_CAST  = 0x10000000, // 28 Auras with this attribute are not visible on units that are not the caster
    SPELL_ATTR5_UNK29                            = 0x20000000, // 29
    SPELL_ATTR5_UNK30                            = 0x40000000, // 30
    SPELL_ATTR5_UNK31                            = 0x80000000  // 31 Forces all nearby enemies to focus attacks caster
};

enum SpellAttr6
{
    SPELL_ATTR6_DONT_DISPLAY_COOLDOWN            = 0x00000001, //  0 client doesn't display cooldown in tooltip for these spells
    SPELL_ATTR6_ONLY_IN_ARENA                    = 0x00000002, //  1 only usable in arena
    SPELL_ATTR6_IGNORE_CASTER_AURAS              = 0x00000004, //  2
    SPELL_ATTR6_ASSIST_IGNORE_IMMUNE_FLAG        = 0x00000008, //  3 skips checking UNIT_FLAG_IMMUNE_TO_PC and UNIT_FLAG_IMMUNE_TO_NPC flags on assist
    SPELL_ATTR6_UNK4                             = 0x00000010, //  4
    SPELL_ATTR6_UNK5                             = 0x00000020, //  5
    SPELL_ATTR6_USE_SPELL_CAST_EVENT             = 0x00000040, //  6 Auras with this attribute trigger SPELL_CAST combat log event instead of SPELL_AURA_START (clientside attribute)
    SPELL_ATTR6_UNK7                             = 0x00000080, //  7
    SPELL_ATTR6_CANT_TARGET_CROWD_CONTROLLED     = 0x00000100, //  8
    SPELL_ATTR6_UNK9                             = 0x00000200, //  9
    SPELL_ATTR6_CAN_TARGET_POSSESSED_FRIENDS     = 0x00000400, // 10 NYI!
    SPELL_ATTR6_NOT_IN_RAID_INSTANCE             = 0x00000800, // 11 not usable in raid instance
    SPELL_ATTR6_CASTABLE_WHILE_ON_VEHICLE        = 0x00001000, // 12 castable while caster is on vehicle
    SPELL_ATTR6_CAN_TARGET_INVISIBLE             = 0x00002000, // 13 ignore visibility requirement for spell target (phases, invisibility, etc.)
    SPELL_ATTR6_UNK14                            = 0x00004000, // 14
    SPELL_ATTR6_UNK15                            = 0x00008000, // 15 only 54368, 67892
    SPELL_ATTR6_UNK16                            = 0x00010000, // 16
    SPELL_ATTR6_UNK17                            = 0x00020000, // 17 Mount spell
    SPELL_ATTR6_CAST_BY_CHARMER                  = 0x00040000, // 18 client won't allow to cast these spells when unit is not possessed && charmer of caster will be original caster
    SPELL_ATTR6_UNK19                            = 0x00080000, // 19 only 47488, 50782
    SPELL_ATTR6_ONLY_VISIBLE_TO_CASTER           = 0x00100000, // 20 Auras with this attribute are only visible to their caster (or pet's owner)
    SPELL_ATTR6_CLIENT_UI_TARGET_EFFECTS         = 0x00200000, // 21 it's only client-side attribute
    SPELL_ATTR6_UNK22                            = 0x00400000, // 22 only 72054
    SPELL_ATTR6_UNK23                            = 0x00800000, // 23
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE          = 0x01000000, // 24
    SPELL_ATTR6_UNK25                            = 0x02000000, // 25 Exorcism, Flash of Light
    SPELL_ATTR6_UNK26                            = 0x04000000, // 26 related to player castable positive buff
    SPELL_ATTR6_NO_DONE_HEALING_BONUS            = 0x08000000, // 27 Also few damage spells, but overlaps with SPELL_ATTR3_NO_DONE_BONUS
    SPELL_ATTR6_UNK28                            = 0x10000000, // 28 Death Grip
    SPELL_ATTR6_NO_DONE_PCT_DAMAGE_MODS          = 0x20000000, // 29 ignores done percent damage mods?
    SPELL_ATTR6_UNK30                            = 0x40000000, // 30
    SPELL_ATTR6_IGNORE_CATEGORY_COOLDOWN_MODS    = 0x80000000  // 31 Spells with this attribute skip applying modifiers to category cooldowns
};

enum SpellAttr7
{
    SPELL_ATTR7_UNK0                             = 0x00000001, //  0 Shaman's new spells (Call of the ...), Feign Death.
    SPELL_ATTR7_UNK1                             = 0x00000002, //  1 Not set in 3.2.2a.
    SPELL_ATTR7_REACTIVATE_AT_RESURRECT          = 0x00000004, //  2 Paladin's auras and 65607 only.
    SPELL_ATTR7_IS_CHEAT_SPELL                   = 0x00000008, //  3 Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_UNK4                             = 0x00000010, //  4 Only 47883 (Soulstone Resurrection) and test spell.
    SPELL_ATTR7_SUMMON_TOTEM                     = 0x00000020, //  5 Only Shaman totems.
    SPELL_ATTR7_UNK6                             = 0x00000040, //  6 Dark Surge, Surge of Light, Burning Breath triggers (boss spells).
    SPELL_ATTR7_UNK7                             = 0x00000080, //  7 66218 (Launch) spell.
    SPELL_ATTR7_HORDE_ONLY                       = 0x00000100, //  8 Teleports, mounts and other spells.
    SPELL_ATTR7_ALLIANCE_ONLY                    = 0x00000200, //  9 Teleports, mounts and other spells.
    SPELL_ATTR7_DISPEL_CHARGES                   = 0x00000400, // 10 Dispel and Spellsteal individual charges instead of whole aura.
    SPELL_ATTR7_INTERRUPT_ONLY_NONPLAYER         = 0x00000800, // 11 Only non-player casts interrupt, though Feral Charge - Bear has it.
    SPELL_ATTR7_UNK12                            = 0x00001000, // 12 Not set in 3.2.2a.
    SPELL_ATTR7_UNK13                            = 0x00002000, // 13 Not set in 3.2.2a.
    SPELL_ATTR7_UNK14                            = 0x00004000, // 14 Only 52150 (Raise Dead - Pet) spell.
    SPELL_ATTR7_UNK15                            = 0x00008000, // 15 Exorcism. Usable on players? 100% crit chance on undead and demons?
    SPELL_ATTR7_UNK16                            = 0x00010000, // 16 Druid spells (29166, 54833, 64372, 68285).
    SPELL_ATTR7_UNK17                            = 0x00020000, // 17 Only 27965 (Suicide) spell.
    SPELL_ATTR7_HAS_CHARGE_EFFECT                = 0x00040000, // 18 Only spells that have Charge among effects.
    SPELL_ATTR7_ZONE_TELEPORT                    = 0x00080000, // 19 Teleports to specific zones.
    SPELL_ATTR7_UNK20                            = 0x00100000, // 20 Blink, Divine Shield, Ice Block
    SPELL_ATTR7_UNK21                            = 0x00200000, // 21 Not set
    SPELL_ATTR7_UNK22                            = 0x00400000, // 22
    SPELL_ATTR7_UNK23                            = 0x00800000, // 23 Motivate, Mutilate, Shattering Throw
    SPELL_ATTR7_UNK24                            = 0x01000000, // 24 Motivate, Mutilate, Perform Speech, Shattering Throw
    SPELL_ATTR7_UNK25                            = 0x02000000, // 25
    SPELL_ATTR7_UNK26                            = 0x04000000, // 26
    SPELL_ATTR7_UNK27                            = 0x08000000, // 27 Not set
    SPELL_ATTR7_CONSOLIDATED_RAID_BUFF           = 0x10000000, // 28 May be collapsed in raid buff frame (clientside attribute)
    SPELL_ATTR7_UNK29                            = 0x20000000, // 29 only 69028, 71237
    SPELL_ATTR7_UNK30                            = 0x40000000, // 30 Burning Determination, Divine Sacrifice, Earth Shield, Prayer of Mending
    SPELL_ATTR7_CLIENT_INDICATOR                 = 0x80000000
};

enum SpellAttr8
{
    SPELL_ATTR8_CANT_MISS                        = 0x00000001, //  0
    SPELL_ATTR8_UNK1                             = 0x00000002, //  1
    SPELL_ATTR8_UNK2                             = 0x00000004, //  2
    SPELL_ATTR8_UNK3                             = 0x00000008, //  3
    SPELL_ATTR8_UNK4                             = 0x00000010, //  4
    SPELL_ATTR8_UNK5                             = 0x00000020, //  5
    SPELL_ATTR8_UNK6                             = 0x00000040, //  6
    SPELL_ATTR8_UNK7                             = 0x00000080, //  7
    SPELL_ATTR8_AFFECT_PARTY_AND_RAID            = 0x00000100, //  8 Nearly all spells have "all party and raid" in description
    SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER        = 0x00000200, //  9 Periodic auras with this flag keep old periodic timer when refreshing at close to one tick remaining (kind of anti DoT clipping)
    SPELL_ATTR8_NAME_CHANGED_DURING_TRANSFORM    = 0x00000400, // 10 according to wowhead comments, name changes, title remains
    SPELL_ATTR8_UNK11                            = 0x00000800, // 11
    SPELL_ATTR8_AURA_SEND_AMOUNT                 = 0x00001000, // 12 Aura must have flag AFLAG_ANY_EFFECT_AMOUNT_SENT to send amount
    SPELL_ATTR8_UNK13                            = 0x00002000, // 13
    SPELL_ATTR8_UNK14                            = 0x00004000, // 14
    SPELL_ATTR8_WATER_MOUNT                      = 0x00008000, // 15 only one River Boat used in Thousand Needles
    SPELL_ATTR8_UNK16                            = 0x00010000, // 16
    SPELL_ATTR8_UNK17                            = 0x00020000, // 17
    SPELL_ATTR8_REMEMBER_SPELLS                  = 0x00040000, // 18 at some point in time, these auras remember spells and allow to cast them later
    SPELL_ATTR8_USE_COMBO_POINTS_ON_ANY_TARGET   = 0x00080000, // 19 allows to consume combo points from dead targets
    SPELL_ATTR8_ARMOR_SPECIALIZATION             = 0x00100000, // 20
    SPELL_ATTR8_UNK21                            = 0x00200000, // 21
    SPELL_ATTR8_HASTE_AFFECT_DURATION            = 0x00400000, // 22
    SPELL_ATTR8_BATTLE_RESURRECTION              = 0x00800000, // 23 For those resurrection spells that can be used in combat
    SPELL_ATTR8_HEALING_SPELL                    = 0x01000000, // 24
    SPELL_ATTR8_UNK25                            = 0x02000000, // 25
    SPELL_ATTR8_RAID_MARKER                      = 0x04000000, // 26 probably spell no need learn to cast
    SPELL_ATTR8_UNK27                            = 0x08000000, // 27
    SPELL_ATTR8_NOT_IN_BG_OR_ARENA               = 0x10000000, // 28 not allow to cast or deactivate currently active effect, not sure about Fast Track
    SPELL_ATTR8_MASTERY_SPECIALIZATION           = 0x20000000, // 29
    SPELL_ATTR8_UNK30                            = 0x40000000, // 30
    SPELL_ATTR8_ATTACK_IGNORE_IMMUNE_TO_PC_FLAG  = 0x80000000  // 31 Do not check UNIT_FLAG_IMMUNE_TO_PC in IsValidAttackTarget
};

enum SpellAttr9
{
    SPELL_ATTR9_UNK0                             = 0x00000001, //  0
    SPELL_ATTR9_UNK1                             = 0x00000002, //  1
    SPELL_ATTR9_RESTRICTED_FLIGHT_AREA           = 0x00000004, //  2 Dalaran and Wintergrasp flight area auras have it
    SPELL_ATTR9_UNK3                             = 0x00000008, //  3
    SPELL_ATTR9_SPECIAL_DELAY_CALCULATION        = 0x00000010, //  4
    SPELL_ATTR9_SUMMON_PLAYER_TOTEM              = 0x00000020, //  5
    SPELL_ATTR9_UNK6                             = 0x00000040, //  6
    SPELL_ATTR9_UNK7                             = 0x00000080, //  7
    SPELL_ATTR9_AIMED_SHOT                       = 0x00000100, //  8
    SPELL_ATTR9_NOT_USABLE_IN_ARENA              = 0x00000200, //  9 Cannot be used in arenas
    SPELL_ATTR9_UNK10                            = 0x00000400, // 10
    SPELL_ATTR9_UNK11                            = 0x00000800, // 11
    SPELL_ATTR9_UNK12                            = 0x00001000, // 12
    SPELL_ATTR9_SLAM                             = 0x00002000, // 13
    SPELL_ATTR9_USABLE_IN_RATED_BATTLEGROUNDS    = 0x00004000, // 14 Can be used in Rated Battlegrounds
    SPELL_ATTR9_UNK15                            = 0x00008000, // 15
    SPELL_ATTR9_UNK16                            = 0x00010000, // 16
    SPELL_ATTR9_UNK17                            = 0x00020000, // 17
    SPELL_ATTR9_UNK18                            = 0x00040000, // 18
    SPELL_ATTR9_UNK19                            = 0x00080000, // 19
    SPELL_ATTR9_UNK20                            = 0x00100000, // 20
    SPELL_ATTR9_UNK21                            = 0x00200000, // 21
    SPELL_ATTR9_UNK22                            = 0x00400000, // 22
    SPELL_ATTR9_UNK23                            = 0x00800000, // 23
    SPELL_ATTR9_UNK24                            = 0x01000000, // 24
    SPELL_ATTR9_UNK25                            = 0x02000000, // 25
    SPELL_ATTR9_UNK26                            = 0x04000000, // 26
    SPELL_ATTR9_UNK27                            = 0x08000000, // 27
    SPELL_ATTR9_UNK28                            = 0x10000000, // 28
    SPELL_ATTR9_UNK29                            = 0x20000000, // 29
    SPELL_ATTR9_UNK30                            = 0x40000000, // 30
    SPELL_ATTR9_UNK31                            = 0x80000000  // 31
};

enum SpellAttr10
{
    SPELL_ATTR10_UNK0                             = 0x00000001, //  0
    SPELL_ATTR10_UNK1                             = 0x00000002, //  1
    SPELL_ATTR10_UNK2                             = 0x00000004, //  2
    SPELL_ATTR10_UNK3                             = 0x00000008, //  3
    SPELL_ATTR10_WATER_SPOUT                      = 0x00000010, //  4
    SPELL_ATTR10_UNK5                             = 0x00000020, //  5
    SPELL_ATTR10_UNK6                             = 0x00000040, //  6
    SPELL_ATTR10_TELEPORT_PLAYER                  = 0x00000080, //  7 4 Teleport Player spells
    SPELL_ATTR10_UNK8                             = 0x00000100, //  8
    SPELL_ATTR10_UNK9                             = 0x00000200, //  9
    SPELL_ATTR10_UNK10                            = 0x00000400, // 10
    SPELL_ATTR10_HERB_GATHERING_MINING            = 0x00000800, // 11 Only Herb Gathering and Mining
    SPELL_ATTR10_UNK12                            = 0x00001000, // 12
    SPELL_ATTR10_UNK13                            = 0x00002000, // 13
    SPELL_ATTR10_CUMULATIVE_PERIODIC              = 0x00004000, // 14
    SPELL_ATTR10_UNK15                            = 0x00008000, // 15
    SPELL_ATTR10_UNK16                            = 0x00010000, // 16
    SPELL_ATTR10_UNK17                            = 0x00020000, // 17
    SPELL_ATTR10_UNK18                            = 0x00040000, // 18
    SPELL_ATTR10_UNK19                            = 0x00080000, // 19
    SPELL_ATTR10_UNK20                            = 0x00100000, // 20
    SPELL_ATTR10_UNK21                            = 0x00200000, // 21
    SPELL_ATTR10_UNK22                            = 0x00400000, // 22
    SPELL_ATTR10_UNK23                            = 0x00800000, // 23
    SPELL_ATTR10_UNK24                            = 0x01000000, // 24
    SPELL_ATTR10_UNK25                            = 0x02000000, // 25
    SPELL_ATTR10_UNK26                            = 0x04000000, // 26
    SPELL_ATTR10_UNK27                            = 0x08000000, // 27
    SPELL_ATTR10_UNK28                            = 0x10000000, // 28
    SPELL_ATTR10_MOUNT_CHARACTER                  = 0x20000000, // 29
    SPELL_ATTR10_UNK30                            = 0x40000000, // 30
    SPELL_ATTR10_UNK31                            = 0x80000000  // 31
};

enum SpellAttr11
{
    SPELL_ATTR11_DONT_TURN_DURING_CAST          = 0x00000001,   // Dunno why this is splitted from SPELL_ATTR5_DONT_TURN_DURING_CAST, may be different behaviour for orientation update
    SPELL_ATTR11_SCALING_FROM_ITEM              = 0x00000004,
    SPELL_ATTR11_NOT_USABLE_IN_CHALLENGES       = 0x00010000,
    SPELL_ATTR11_USABLE_WHILE_STUNNED           = 0x04000000,
};

enum Roles
{
    ROLES_DEFAULT   = 0,
    ROLES_HEALER    = 1,
    ROLES_DPS       = 2,
    ROLES_TANK      = 3,
};

enum Specializations
{
    SPEC_NONE                           = 0,
    SPEC_MAGE_ARCANE                    = 62,
    SPEC_MAGE_FIRE                      = 63,
    SPEC_MAGE_FROST                     = 64,
    SPEC_PALADIN_HOLY                   = 65,
    SPEC_PALADIN_PROTECTION             = 66,
    SPEC_PALADIN_RETRIBUTION            = 70,
    SPEC_WARRIOR_ARMS                   = 71,
    SPEC_WARRIOR_FURY                   = 72,
    SPEC_WARRIOR_PROTECTION             = 73,
    SPEC_PET_FEROCITY                   = 74,
    SPEC_PET_CUNNING                    = 79,
    SPEC_PET_TENACITY                   = 81,
    SPEC_DRUID_BALANCE                  = 102,
    SPEC_DRUID_FERAL                    = 103,
    SPEC_DRUID_GUARDIAN                 = 104,
    SPEC_DRUID_RESTORATION              = 105,
    SPEC_DEATH_KNIGHT_BLOOD             = 250,
    SPEC_DEATH_KNIGHT_FROST             = 251,
    SPEC_DEATH_KNIGHT_UNHOLY            = 252,
    SPEC_HUNTER_BEAST_MASTERY           = 253,
    SPEC_HUNTER_MARKSMANSHIP            = 254,
    SPEC_HUNTER_SURVIVAL                = 255,
    SPEC_PRIEST_DISCIPLINE              = 256,
    SPEC_PRIEST_HOLY                    = 257,
    SPEC_PRIEST_SHADOW                  = 258,
    SPEC_ROGUE_ASSASSINATION            = 259,
    SPEC_ROGUE_COMBAT                   = 260,
    SPEC_ROGUE_SUBTLETY                 = 261,
    SPEC_SHAMAN_ELEMENTAL               = 262,
    SPEC_SHAMAN_ENHANCEMENT             = 263,
    SPEC_SHAMAN_RESTORATION             = 264,
    SPEC_WARLOCK_AFFLICTION             = 265,
    SPEC_WARLOCK_DEMONOLOGY             = 266,
    SPEC_WARLOCK_DESTRUCTION            = 267,
    SPEC_MONK_BREWMASTER                = 268,
    SPEC_MONK_WINDWALKER                = 269,
    SPEC_MONK_MISTWEAVER                = 270
};

#define MIN_TALENT_SPEC         0
#define MAX_TALENT_SPEC         1
#define MIN_TALENT_SPECS        1
#define MAX_TALENT_SPECS        2
#define MAX_GLYPH_SLOT_INDEX    6

// Custom values
enum SpellClickUserTypes
{
    SPELL_CLICK_USER_ANY = 0,
    SPELL_CLICK_USER_FRIEND = 1,
    SPELL_CLICK_USER_RAID = 2,
    SPELL_CLICK_USER_PARTY = 3,
    SPELL_CLICK_USER_MAX = 4
};

enum SpellClickCastFlags
{
    NPC_CLICK_CAST_CASTER_CLICKER       = 0x01,
    NPC_CLICK_CAST_TARGET_CLICKER       = 0x02,
    NPC_CLICK_CAST_ORIG_CASTER_OWNER    = 0x04
};

enum SheathTypes
{
    SHEATHETYPE_NONE                   = 0,
    SHEATHETYPE_MAINHAND               = 1,
    SHEATHETYPE_OFFHAND                = 2,
    SHEATHETYPE_LARGEWEAPONLEFT        = 3,
    SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
    SHEATHETYPE_HIPWEAPONLEFT          = 5,
    SHEATHETYPE_HIPWEAPONRIGHT         = 6,
    SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum CharacterSlot
{
    SLOT_HEAD                          = 0,
    SLOT_NECK                          = 1,
    SLOT_SHOULDERS                     = 2,
    SLOT_SHIRT                         = 3,
    SLOT_CHEST                         = 4,
    SLOT_WAIST                         = 5,
    SLOT_LEGS                          = 6,
    SLOT_FEET                          = 7,
    SLOT_WRISTS                        = 8,
    SLOT_HANDS                         = 9,
    SLOT_FINGER1                       = 10,
    SLOT_FINGER2                       = 11,
    SLOT_TRINKET1                      = 12,
    SLOT_TRINKET2                      = 13,
    SLOT_BACK                          = 14,
    SLOT_MAIN_HAND                     = 15,
    SLOT_OFF_HAND                      = 16,
    SLOT_RANGED                        = 17,
    SLOT_TABARD                        = 18,
    SLOT_EMPTY                         = 19
};

enum Language
{
    LANG_UNIVERSAL         = 0,
    LANG_ORCISH            = 1,
    LANG_DARNASSIAN        = 2,
    LANG_TAURAHE           = 3,
    LANG_DWARVISH          = 6,
    LANG_COMMON            = 7,
    LANG_DEMONIC           = 8,
    LANG_TITAN             = 9,
    LANG_THALASSIAN        = 10,
    LANG_DRACONIC          = 11,
    LANG_KALIMAG           = 12,
    LANG_GNOMISH           = 13,
    LANG_TROLL             = 14,
    LANG_GUTTERSPEAK       = 33,
    LANG_DRAENEI           = 35,
    LANG_ZOMBIE            = 36,
    LANG_GNOMISH_BINARY    = 37,
    LANG_GOBLIN_BINARY     = 38,
    LANG_WORGEN            = 39,
    LANG_GOBLIN            = 40,
    LANG_PANDAREN_NEUTRAL  = 42,
    LANG_PANDAREN_ALLIANCE = 43,
    LANG_PANDAREN_HORDE    = 44,
    LANG_RIKKITUN          = 168,
    LANG_ADDON             = 0xFFFFFFFF                        // used by addons, in 2.4.0 not exist, replaced by messagetype?
};

#define LANGUAGES_COUNT   24

enum TeamId
{
    TEAM_ALLIANCE = 0,
    TEAM_HORDE,
    TEAM_NEUTRAL
};

enum Team
{
    HORDE						= 67,
    ALLIANCE					= 469,
    //TEAM_STEAMWHEEDLE_CARTEL  = 169,   // not used in code
    //TEAM_ALLIANCE_FORCES      = 891,
    //TEAM_HORDE_FORCES         = 892,
    //TEAM_SANCTUARY            = 936,
    //TEAM_OUTLAND              = 980,
	PANDAREN_NEUTRAL		    = 1249,  // Pandaren is neutral on start
    TEAM_OTHER                  = 0      // if ReputationListId > 0 && Flags != FACTION_FLAG_TEAM_HEADER
};

enum SpellEffects
{
    SPELL_EFFECT_INSTAKILL                          = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE                      = 2,
    SPELL_EFFECT_DUMMY                              = 3,
    SPELL_EFFECT_PORTAL_TELEPORT                    = 4, // Unused (4.3.4)
    SPELL_EFFECT_TELEPORT_UNITS                     = 5,
    SPELL_EFFECT_APPLY_AURA                         = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE               = 7,
    SPELL_EFFECT_POWER_DRAIN                        = 8,
    SPELL_EFFECT_HEALTH_LEECH                       = 9,
    SPELL_EFFECT_HEAL                               = 10,
    SPELL_EFFECT_BIND                               = 11,
    SPELL_EFFECT_PORTAL                             = 12,
    SPELL_EFFECT_RITUAL_BASE                        = 13, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_SPECIALIZE                  = 14, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL             = 15, // Unused (4.3.4)
    SPELL_EFFECT_QUEST_COMPLETE                     = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL             = 17,
    SPELL_EFFECT_RESURRECT                          = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS                  = 19,
    SPELL_EFFECT_DODGE                              = 20,
    SPELL_EFFECT_EVADE                              = 21,
    SPELL_EFFECT_PARRY                              = 22,
    SPELL_EFFECT_BLOCK                              = 23,
    SPELL_EFFECT_CREATE_ITEM                        = 24,
    SPELL_EFFECT_WEAPON                             = 25,
    SPELL_EFFECT_DEFENSE                            = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA               = 27,
    SPELL_EFFECT_SUMMON                             = 28,
    SPELL_EFFECT_LEAP                               = 29,
    SPELL_EFFECT_ENERGIZE                           = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE              = 31,
    SPELL_EFFECT_TRIGGER_MISSILE                    = 32,
    SPELL_EFFECT_OPEN_LOCK                          = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM                 = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY              = 35,
    SPELL_EFFECT_LEARN_SPELL                        = 36,
    SPELL_EFFECT_SPELL_DEFENSE                      = 37,
    SPELL_EFFECT_DISPEL                             = 38,
    SPELL_EFFECT_LANGUAGE                           = 39,
    SPELL_EFFECT_DUAL_WIELD                         = 40,
    SPELL_EFFECT_JUMP                               = 41,
    SPELL_EFFECT_JUMP_DEST                          = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER         = 43,
    SPELL_EFFECT_SKILL_STEP                         = 44,
    SPELL_EFFECT_PLAY_MOVIE                         = 45,
    SPELL_EFFECT_SPAWN                              = 46,
    SPELL_EFFECT_TRADE_SKILL                        = 47,
    SPELL_EFFECT_STEALTH                            = 48,
    SPELL_EFFECT_DETECT                             = 49,
    SPELL_EFFECT_TRANS_DOOR                         = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT                 = 51, // Unused (4.3.4)
    SPELL_EFFECT_GUARANTEE_HIT                      = 52, // Unused (4.3.4)
    SPELL_EFFECT_ENCHANT_ITEM                       = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY             = 54,
    SPELL_EFFECT_TAMECREATURE                       = 55,
    SPELL_EFFECT_SUMMON_PET                         = 56,
    SPELL_EFFECT_LEARN_PET_SPELL                    = 57,
    SPELL_EFFECT_WEAPON_DAMAGE                      = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM                 = 59,
    SPELL_EFFECT_PROFICIENCY                        = 60,
    SPELL_EFFECT_SEND_EVENT                         = 61,
    SPELL_EFFECT_POWER_BURN                         = 62,
    SPELL_EFFECT_THREAT                             = 63,
    SPELL_EFFECT_TRIGGER_SPELL                      = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID               = 65,
    SPELL_EFFECT_CREATE_MANA_GEM                    = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH                    = 67,
    SPELL_EFFECT_INTERRUPT_CAST                     = 68,
    SPELL_EFFECT_DISTRACT                           = 69,
    SPELL_EFFECT_PULL                               = 70,
    SPELL_EFFECT_PICKPOCKET                         = 71,
    SPELL_EFFECT_ADD_FARSIGHT                       = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS                    = 73,
    SPELL_EFFECT_APPLY_GLYPH                        = 74,
    SPELL_EFFECT_HEAL_MECHANICAL                    = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD                 = 76,
    SPELL_EFFECT_SCRIPT_EFFECT                      = 77,
    SPELL_EFFECT_ATTACK                             = 78,
    SPELL_EFFECT_SANCTUARY                          = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS                   = 80,
    SPELL_EFFECT_CREATE_HOUSE                       = 81,
    SPELL_EFFECT_BIND_SIGHT                         = 82,
    SPELL_EFFECT_DUEL                               = 83,
    SPELL_EFFECT_STUCK                              = 84,
    SPELL_EFFECT_SUMMON_PLAYER                      = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT                    = 86,
    SPELL_EFFECT_GAMEOBJECT_DAMAGE                  = 87,
    SPELL_EFFECT_GAMEOBJECT_REPAIR                  = 88,
    SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE   = 89,
    SPELL_EFFECT_KILL_CREDIT                        = 90,
    SPELL_EFFECT_THREAT_ALL                         = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM                  = 92,
    SPELL_EFFECT_FORCE_DESELECT                     = 93,
    SPELL_EFFECT_SELF_RESURRECT                     = 94,
    SPELL_EFFECT_SKINNING                           = 95,
    SPELL_EFFECT_CHARGE                             = 96,
    SPELL_EFFECT_CAST_BUTTON                        = 97,
    SPELL_EFFECT_KNOCK_BACK                         = 98,
    SPELL_EFFECT_DISENCHANT                         = 99,
    SPELL_EFFECT_INEBRIATE                          = 100,
    SPELL_EFFECT_FEED_PET                           = 101,
    SPELL_EFFECT_DISMISS_PET                        = 102,
    SPELL_EFFECT_REPUTATION                         = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1                = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2                = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3                = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4                = 107,
    SPELL_EFFECT_DISPEL_MECHANIC                    = 108,
    SPELL_EFFECT_RESURRECT_PET                      = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS                 = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE                  = 111,
    SPELL_EFFECT_112                                = 112,
    SPELL_EFFECT_RESURRECT_NEW                      = 113,
    SPELL_EFFECT_ATTACK_ME                          = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT              = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE                 = 116,
    SPELL_EFFECT_SPIRIT_HEAL                        = 117,
    SPELL_EFFECT_SKILL                              = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET                = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD                 = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG              = 121,
    SPELL_EFFECT_122                                = 122, // Unused (4.3.4)
    SPELL_EFFECT_SEND_TAXI                          = 123,
    SPELL_EFFECT_PULL_TOWARDS                       = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT              = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF              = 126,
    SPELL_EFFECT_PROSPECTING                        = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND             = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY              = 129,
    SPELL_EFFECT_REDIRECT_THREAT                    = 130,
    SPELL_EFFECT_PLAY_SOUND                         = 131,
    SPELL_EFFECT_PLAY_MUSIC                         = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION             = 133,
    SPELL_EFFECT_KILL_CREDIT2                       = 134,
    SPELL_EFFECT_CALL_PET                           = 135,
    SPELL_EFFECT_HEAL_PCT                           = 136,
    SPELL_EFFECT_ENERGIZE_PCT                       = 137,
    SPELL_EFFECT_LEAP_BACK                          = 138,
    SPELL_EFFECT_CLEAR_QUEST                        = 139,
    SPELL_EFFECT_FORCE_CAST                         = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE              = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE           = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER              = 143,
    SPELL_EFFECT_KNOCK_BACK_DEST                    = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST                  = 145,
    SPELL_EFFECT_ACTIVATE_RUNE                      = 146,
    SPELL_EFFECT_QUEST_FAIL                         = 147,
    SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE   = 148,
    SPELL_EFFECT_CHARGE_DEST                        = 149,
    SPELL_EFFECT_QUEST_START                        = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2                    = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND                  = 152,
    SPELL_EFFECT_CREATE_TAMED_PET                   = 153,
    SPELL_EFFECT_DISCOVER_TAXI                      = 154,
    SPELL_EFFECT_TITAN_GRIP                         = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC             = 156,
    SPELL_EFFECT_CREATE_ITEM_2                      = 157,
    SPELL_EFFECT_MILLING                            = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET                   = 159,
    SPELL_EFFECT_160                                = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT                  = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT                 = 162,
    SPELL_EFFECT_163                                = 163, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_AURA                        = 164,
    SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT         = 165,
    SPELL_EFFECT_GIVE_CURRENCY                      = 166,
    SPELL_EFFECT_167                                = 167,
    SPELL_EFFECT_168                                = 168,
    SPELL_EFFECT_DESTROY_ITEM                       = 169,
    SPELL_EFFECT_170                                = 170,
    SPELL_EFFECT_171                                = 171, // Summons gamebject
    SPELL_EFFECT_RESURRECT_WITH_AURA                = 172,
    SPELL_EFFECT_UNLOCK_GUILD_VAULT_TAB             = 173, // Guild tab unlocked (guild perk)
    SPELL_EFFECT_APPLY_AREA_AURA_ENTRY              = 174,
    SPELL_EFFECT_175                                = 175, // Unused (4.3.4)
    SPELL_EFFECT_SANCTURAY2                         = 176, // Some kind of sanctuary effect (Vanish)
    SPELL_EFFECT_177                                = 177,
    SPELL_EFFECT_178                                = 178, // Unused (4.3.4)
    SPELL_EFFECT_CREATE_AREATRIGGER                 = 179,
    SPELL_EFFECT_180                                = 180, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_TALENT                      = 181, // Eg: Tome of the Clear Mind
    SPELL_EFFECT_182                                = 182,
    SPELL_EFFECT_183                                = 183,
    SPELL_EFFECT_184                                = 184,
    SPELL_EFFECT_185                                = 185,
    SPELL_EFFECT_186                                = 186,
    SPELL_EFFECT_RANDOMIZE_DIGSITES                 = 187,
    SPELL_EFFECT_188                                = 188,
    SPELL_EFFECT_BONUS_ROLL                         = 189,
    SPELL_EFFECT_190                                = 190,
    SPELL_EFFECT_TELEPORT_TO_DIGSITE                = 191, // Teleport player to an random digsite (Archaeology)
    SPELL_EFFECT_UNCAGE_BATTLE_PET                  = 192,
    SPELL_EFFECT_193                                = 193,
    SPELL_EFFECT_194                                = 194,
    SPELL_EFFECT_PLAY_SCENE_PACKAGE                 = 195,
    SPELL_EFFECT_196                                = 196,
    SPELL_EFFECT_197                                = 197,
    SPELL_EFFECT_PLAY_SCENE_ID                      = 198,
    SPELL_EFFECT_199                                = 199,
    SPELL_EFFECT_HEAL_BATTLEPET_PCT                 = 200,
    SPELL_EFFECT_UNLOCK_BATTLE_PETS                 = 201,
    SPELL_EFFECT_202                                = 202,
    SPELL_EFFECT_203                                = 203,
    SPELL_EFFECT_204                                = 204,
    SPELL_EFFECT_PLAYER_CHOICE                      = 205,
    SPELL_EFFECT_206                                = 206,
    SPELL_EFFECT_207                                = 207,
    SPELL_EFFECT_208                                = 208,
    SPELL_EFFECT_209                                = 209,
    SPELL_EFFECT_210                                = 210,
    SPELL_EFFECT_211                                = 211,
    SPELL_EFFECT_212                                = 212,
    SPELL_EFFECT_JUMP_DEST_2                        = 213,
    TOTAL_SPELL_EFFECTS                             = 214,
};

enum SpellCastResult
{
    SPELL_FAILED_SUCCESS                         = 0,
    SPELL_FAILED_AFFECTING_COMBAT                = 1,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH          = 2,
    SPELL_FAILED_ALREADY_AT_FULL_MANA            = 3,
    SPELL_FAILED_ALREADY_AT_FULL_POWER           = 4,
    SPELL_FAILED_ALREADY_BEING_TAMED             = 5,
    SPELL_FAILED_ALREADY_HAVE_CHARM              = 6,
    SPELL_FAILED_ALREADY_HAVE_SUMMON             = 7,
    SPELL_FAILED_ALREADY_HAVE_PET                = 8,
    SPELL_FAILED_ALREADY_OPEN                    = 9,
    SPELL_FAILED_STRONGER_SPELL_IN_PROGRESS      = 10,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED           = 11,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS            = 12,
    SPELL_FAILED_BAD_TARGETS                     = 13,
    SPELL_FAILED_CANT_BE_CHARMED                 = 14,
    SPELL_FAILED_CANT_BE_DISENCHANTED            = 15,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL      = 16,
    SPELL_FAILED_CANT_BE_MILLED                  = 17,
    SPELL_FAILED_CANT_BE_PROSPECTED              = 18,
    SPELL_FAILED_CANT_CAST_ON_TAPPED             = 19,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE       = 20,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED       = 21,
    SPELL_FAILED_CANT_STEALTH                    = 22,
    SPELL_FAILED_CANT_UNTALENT                   = 23,
    SPELL_FAILED_CASTER_AURASTATE                = 24,
    SPELL_FAILED_CASTER_DEAD                     = 25,
    SPELL_FAILED_CHARMED                         = 26,
    SPELL_FAILED_CHEST_IN_USE                    = 27,
    SPELL_FAILED_CONFUSED                        = 28,
    SPELL_FAILED_DONT_REPORT                     = 29,
    SPELL_FAILED_EQUIPPED_ITEM                   = 30,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS             = 31,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND    = 32,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND     = 33,
    SPELL_FAILED_ERROR                           = 34,
    SPELL_FAILED_FALLING                         = 35,
    SPELL_FAILED_FIZZLE                          = 36,
    SPELL_FAILED_FLEEING                         = 37,
    SPELL_FAILED_FOOD_LOWLEVEL                   = 38,
    SPELL_FAILED_HIGHLEVEL                       = 39,
    SPELL_FAILED_HUNGER_SATIATED                 = 40,
    SPELL_FAILED_IMMUNE                          = 41,
    SPELL_FAILED_INCORRECT_AREA                  = 42,
    SPELL_FAILED_INTERRUPTED                     = 43,
    SPELL_FAILED_INTERRUPTED_COMBAT              = 44,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED          = 45,
    SPELL_FAILED_ITEM_GONE                       = 46,
    SPELL_FAILED_ITEM_NOT_FOUND                  = 47,
    SPELL_FAILED_ITEM_NOT_READY                  = 48,
    SPELL_FAILED_LEVEL_REQUIREMENT               = 49,
    SPELL_FAILED_LINE_OF_SIGHT                   = 50,
    SPELL_FAILED_LOWLEVEL                        = 51,
    SPELL_FAILED_LOW_CASTLEVEL                   = 52,
    SPELL_FAILED_MAINHAND_EMPTY                  = 53,
    SPELL_FAILED_MOVING                          = 54,
    SPELL_FAILED_NEED_AMMO                       = 55,
    SPELL_FAILED_NEED_AMMO_POUCH                 = 56,
    SPELL_FAILED_NEED_EXOTIC_AMMO                = 57,
    SPELL_FAILED_NEED_MORE_ITEMS                 = 58,
    SPELL_FAILED_NOPATH                          = 59,
    SPELL_FAILED_NOT_BEHIND                      = 60,
    SPELL_FAILED_NOT_FISHABLE                    = 61,
    SPELL_FAILED_NOT_FLYING                      = 62,
    SPELL_FAILED_NOT_HERE                        = 63,
    SPELL_FAILED_NOT_INFRONT                     = 64,
    SPELL_FAILED_NOT_IN_CONTROL                  = 65,
    SPELL_FAILED_NOT_KNOWN                       = 66,
    SPELL_FAILED_NOT_MOUNTED                     = 67,
    SPELL_FAILED_NOT_ON_TAXI                     = 68,
    SPELL_FAILED_NOT_ON_TRANSPORT                = 69,
    SPELL_FAILED_NOT_READY                       = 70,
    SPELL_FAILED_NOT_SHAPESHIFT                  = 71,
    SPELL_FAILED_NOT_STANDING                    = 72,
    SPELL_FAILED_NOT_TRADEABLE                   = 73,
    SPELL_FAILED_NOT_TRADING                     = 74,
    SPELL_FAILED_NOT_UNSHEATHED                  = 75,
    SPELL_FAILED_NOT_WHILE_GHOST                 = 76,
    SPELL_FAILED_NOT_WHILE_LOOTING               = 77,
    SPELL_FAILED_NO_AMMO                         = 78,
    SPELL_FAILED_NO_CHARGES_REMAIN               = 79,
    SPELL_FAILED_NO_CHAMPION                     = 80,
    SPELL_FAILED_NO_COMBO_POINTS                 = 81,
    SPELL_FAILED_NO_DUELING                      = 82,
    SPELL_FAILED_NO_ENDURANCE                    = 83,
    SPELL_FAILED_NO_FISH                         = 84,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED     = 85,
    SPELL_FAILED_NO_MOUNTS_ALLOWED               = 86,
    SPELL_FAILED_NO_PET                          = 87,
    SPELL_FAILED_NO_POWER                        = 88,
    SPELL_FAILED_NOTHING_TO_DISPEL               = 89,
    SPELL_FAILED_NOTHING_TO_STEAL                = 90,
    SPELL_FAILED_ONLY_ABOVEWATER                 = 91,
    SPELL_FAILED_ONLY_DAYTIME                    = 92,
    SPELL_FAILED_ONLY_INDOORS                    = 93,
    SPELL_FAILED_ONLY_MOUNTED                    = 94,
    SPELL_FAILED_ONLY_NIGHTTIME                  = 95,
    SPELL_FAILED_ONLY_OUTDOORS                   = 96,
    SPELL_FAILED_ONLY_SHAPESHIFT                 = 97,
    SPELL_FAILED_ONLY_STEALTHED                  = 98,
    SPELL_FAILED_ONLY_UNDERWATER                 = 99,
    SPELL_FAILED_OUT_OF_RANGE                    = 100,
    SPELL_FAILED_PACIFIED                        = 101,
    SPELL_FAILED_POSSESSED                       = 102,
    SPELL_FAILED_REAGENTS                        = 103,
    SPELL_FAILED_REQUIRES_AREA                   = 104,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS            = 105,
    SPELL_FAILED_ROOTED                          = 106,
    SPELL_FAILED_SILENCED                        = 107,
    SPELL_FAILED_SPELL_IN_PROGRESS               = 108,
    SPELL_FAILED_SPELL_LEARNED                   = 109,
    SPELL_FAILED_SPELL_UNAVAILABLE               = 110,
    SPELL_FAILED_STUNNED                         = 111,
    SPELL_FAILED_TARGETS_DEAD                    = 112,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT         = 113,
    SPELL_FAILED_TARGET_AURASTATE                = 114,
    SPELL_FAILED_TARGET_DUELING                  = 115,
    SPELL_FAILED_TARGET_ENEMY                    = 116,
    SPELL_FAILED_TARGET_ENRAGED                  = 117,
    SPELL_FAILED_TARGET_FRIENDLY                 = 118,
    SPELL_FAILED_TARGET_IN_COMBAT                = 119,
    SPELL_FAILED_TARGET_IN_PET_BATTLE            = 120,
    SPELL_FAILED_TARGET_IS_PLAYER                = 121,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED     = 122,
    SPELL_FAILED_TARGET_NOT_DEAD                 = 123,
    SPELL_FAILED_TARGET_NOT_IN_PARTY             = 124,
    SPELL_FAILED_TARGET_NOT_LOOTED               = 125,
    SPELL_FAILED_TARGET_NOT_PLAYER               = 126,
    SPELL_FAILED_TARGET_NO_POCKETS               = 127,
    SPELL_FAILED_TARGET_NO_WEAPONS               = 128,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS        = 129,
    SPELL_FAILED_TARGET_UNSKINNABLE              = 130,
    SPELL_FAILED_THIRST_SATIATED                 = 131,
    SPELL_FAILED_TOO_CLOSE                       = 132,
    SPELL_FAILED_TOO_MANY_OF_ITEM                = 133,
    SPELL_FAILED_TOTEM_CATEGORY                  = 134,
    SPELL_FAILED_TOTEMS                          = 135,
    SPELL_FAILED_TRY_AGAIN                       = 136,
    SPELL_FAILED_UNIT_NOT_BEHIND                 = 137,
    SPELL_FAILED_UNIT_NOT_INFRONT                = 138,
    SPELL_FAILED_VISION_OBSCURED                 = 139,
    SPELL_FAILED_WRONG_PET_FOOD                  = 140,
    SPELL_FAILED_NOT_WHILE_FATIGUED              = 141,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE          = 142,
    SPELL_FAILED_NOT_WHILE_TRADING               = 143,
    SPELL_FAILED_TARGET_NOT_IN_RAID              = 144,
    SPELL_FAILED_TARGET_FREEFORALL               = 145,
    SPELL_FAILED_NO_EDIBLE_CORPSES               = 146,
    SPELL_FAILED_ONLY_BATTLEGROUNDS              = 147,
    SPELL_FAILED_TARGET_NOT_GHOST                = 148,
    SPELL_FAILED_TRANSFORM_UNUSABLE              = 149,
    SPELL_FAILED_WRONG_WEATHER                   = 150,
    SPELL_FAILED_DAMAGE_IMMUNE                   = 151,
    SPELL_FAILED_PREVENTED_BY_MECHANIC           = 152,
    SPELL_FAILED_PLAY_TIME                       = 153,
    SPELL_FAILED_REPUTATION                      = 154,
    SPELL_FAILED_MIN_SKILL                       = 155,
    SPELL_FAILED_NOT_IN_RATED_BATTLEGROUND       = 156,
    SPELL_FAILED_NOT_ON_SHAPESHIFT               = 157,
    SPELL_FAILED_NOT_ON_STEALTHED                = 158,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE            = 159,
    SPELL_FAILED_NOT_ON_MOUNTED                  = 160,
    SPELL_FAILED_TOO_SHALLOW                     = 161,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY         = 162,
    SPELL_FAILED_TARGET_IS_TRIVIAL               = 163,
    SPELL_FAILED_BM_OR_INVISGOD                  = 164,
    SPELL_FAILED_APPRENTICE_RIDING_REQUIREMENT   = 165,
    SPELL_FAILED_JOURNEYMAN_RIDING_REQUIREMENT   = 166,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT       = 167,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT      = 168,
    SPELL_FAILED_MASTER_RIDING_REQUIREMENT       = 169,
    SPELL_FAILED_COLD_RIDING_REQUIREMENT         = 170,
    SPELL_FAILED_FLIGHT_MASTER_RIDING_REQUIREMENT = 171,
    SPELL_FAILED_CS_RIDING_REQUIREMENT           = 172,
    SPELL_FAILED_PANDA_RIDING_REQUIREMENT        = 173,
    SPELL_FAILED_NOT_IDLE                        = 174,
    SPELL_FAILED_NOT_INACTIVE                    = 175,
    SPELL_FAILED_PARTIAL_PLAYTIME                = 176,
    SPELL_FAILED_NO_PLAYTIME                     = 177,
    SPELL_FAILED_NOT_IN_BATTLEGROUND             = 178,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE            = 179,
    SPELL_FAILED_ONLY_IN_ARENA                   = 180,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE  = 181,
    SPELL_FAILED_ON_USE_ENCHANT                  = 182,
    SPELL_FAILED_NOT_ON_GROUND                   = 183,
    SPELL_FAILED_CUSTOM_ERROR                    = 184,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW          = 185,
    SPELL_FAILED_TOO_MANY_SOCKETS                = 186,
    SPELL_FAILED_INVALID_GLYPH                   = 187,
    SPELL_FAILED_UNIQUE_GLYPH                    = 188,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED             = 189,
    SPELL_FAILED_NO_VALID_TARGETS                = 190,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES             = 191,
    SPELL_FAILED_NOT_IN_BARBERSHOP               = 192,
    SPELL_FAILED_FISHING_TOO_LOW                 = 193,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW       = 194,
    SPELL_FAILED_SUMMON_PENDING                  = 195,
    SPELL_FAILED_MAX_SOCKETS                     = 196,
    SPELL_FAILED_PET_CAN_RENAME                  = 197,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED    = 198,
    SPELL_FAILED_NO_ACTIONS                      = 199,
    SPELL_FAILED_CURRENCY_WEIGHT_MISMATCH        = 200,
    SPELL_FAILED_WEIGHT_NOT_ENOUGH               = 201,
    SPELL_FAILED_WEIGHT_TOO_MUCH                 = 202,
    SPELL_FAILED_NO_VACANT_SEAT                  = 203,
    SPELL_FAILED_NO_LIQUID                       = 204,
    SPELL_FAILED_ONLY_NOT_SWIMMING               = 205,
    SPELL_FAILED_BY_NOT_MOVING                   = 206,
    SPELL_FAILED_IN_COMBAT_RES_LIMIT_REACHED     = 207,
    SPELL_FAILED_NOT_IN_ARENA                    = 208,
    SPELL_FAILED_TARGET_NOT_GROUNDED             = 209,
    SPELL_FAILED_EXCEEDED_WEEKLY_USAGE           = 210,
    SPELL_FAILED_NOT_IN_LFG_DUNGEON              = 211,
    SPELL_FAILED_BAD_TARGET_FILTER               = 212,
    SPELL_FAILED_NOT_ENOUGH_TARGETS              = 213,
    SPELL_FAILED_NO_SPEC                         = 214,
    SPELL_FAILED_CANT_ADD_BATTLE_PET             = 215,
    SPELL_FAILED_CANT_UPGRADE_BATTLE_PET         = 216,
    SPELL_FAILED_WRONG_BATTLE_PET_TYPE           = 217,
    SPELL_FAILED_NO_DUNGEON_ENCOUNTER            = 218,
    SPELL_FAILED_NO_TELEPORT_FROM_DUNGEON        = 219,
    SPELL_FAILED_MAX_LEVEL_TOO_LOW               = 220,
    SPELL_FAILED_UNKNOWN                         = 254, // custom value, default case
    SPELL_CAST_OK                                = 255, // custom value, must not be sent to client
};

enum SpellCustomErrors
{
    SPELL_CUSTOM_ERROR_NONE                             =  0,
    SPELL_CUSTOM_ERROR_CUSTOM_MSG                       =  1, // Something bad happened, and we want to display a custom message!
    SPELL_CUSTOM_ERROR_ALEX_BROKE_QUEST                 =  2, // Alex broke your quest! Thank him later!
    SPELL_CUSTOM_ERROR_NEED_HELPLESS_VILLAGER           =  3, // This spell may only be used on Helpless Wintergarde Villagers that have not been rescued.
    SPELL_CUSTOM_ERROR_NEED_WARSONG_DISGUISE            =  4, // Requires that you be wearing the Warsong Orc Disguise.
    SPELL_CUSTOM_ERROR_REQUIRES_PLAGUE_WAGON            =  5, // You must be closer to a plague wagon in order to drop off your 7th Legion Siege Engineer.
    SPELL_CUSTOM_ERROR_CANT_TARGET_FRIENDLY_NONPARTY    =  6, // You cannot target friendly units outside your party.
    SPELL_CUSTOM_ERROR_NEED_CHILL_NYMPH                 =  7, // You must target a weakened chill nymph.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_ENKILAH               =  8, // The Imbued Scourge Shroud will only work when equipped in the Temple City of En'kilah.
    SPELL_CUSTOM_ERROR_REQUIRES_CORPSE_DUST             =  9, // Requires Corpse Dust
    SPELL_CUSTOM_ERROR_CANT_SUMMON_GARGOYLE             = 10, // You cannot summon another gargoyle yet.
    SPELL_CUSTOM_ERROR_NEED_CORPSE_DUST_IF_NO_TARGET    = 11, // Requires Corpse Dust if the target is not dead and humanoid.
    SPELL_CUSTOM_ERROR_MUST_BE_AT_SHATTERHORN           = 12, // Can only be placed near Shatterhorn
    SPELL_CUSTOM_ERROR_MUST_TARGET_PROTO_DRAKE_EGG      = 13, // You must first select a Proto-Drake Egg.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_TREE            = 14, // You must be close to a marked tree.
    SPELL_CUSTOM_ERROR_MUST_TARGET_TURKEY               = 15, // You must target a Fjord Turkey.
    SPELL_CUSTOM_ERROR_MUST_TARGET_HAWK                 = 16, // You must target a Fjord Hawk.
    SPELL_CUSTOM_ERROR_TOO_FAR_FROM_BOUY                = 17, // You are too far from the bouy.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_OIL_SLICK       = 18, // Must be used near an oil slick.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_BOUY            = 19, // You must be closer to the buoy!
    SPELL_CUSTOM_ERROR_WYRMREST_VANQUISHER              = 20, // You may only call for the aid of a Wyrmrest Vanquisher in Wyrmrest Temple, The Dragon Wastes, Galakrond's Rest or The Wicked Coil.
    SPELL_CUSTOM_ERROR_MUST_TARGET_ICE_HEART_JORMUNGAR  = 21, // That can only be used on a Ice Heart Jormungar Spawn.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_SINKHOLE        = 22, // You must be closer to a sinkhole to use your map.
    SPELL_CUSTOM_ERROR_REQUIRES_HAROLD_LANE             = 23, // You may only call down a stampede on Harold Lane.
    SPELL_CUSTOM_ERROR_REQUIRES_GAMMOTH_MAGNATAUR       = 24, // You may only use the Pouch of Crushed Bloodspore on Gammothra or other magnataur in the Bloodspore Plains and Gammoth.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_RESURRECTION_CHAMBER  = 25, // Requires the magmawyrm resurrection chamber in the back of the Maw of Neltharion.
    SPELL_CUSTOM_ERROR_CANT_CALL_WINTERGARDE_HERE       = 26, // You may only call down a Wintergarde Gryphon in Wintergarde Keep or the Carrion Fields.
    SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM              = 27, // What are you doing? Only aim that thing at Wilhelm!
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH                = 28, // Not enough health!
    SPELL_CUSTOM_ERROR_NO_NEARBY_CORPSES                = 29, // There are no nearby corpses to use
    SPELL_CUSTOM_ERROR_TOO_MANY_GHOULS                  = 30, // You've created enough ghouls. Return to Gothik the Harvester at Death's Breach.
    SPELL_CUSTOM_ERROR_GO_FURTHER_FROM_SUNDERED_SHARD   = 31, // Your companion does not want to come here.  Go further from the Sundered Shard.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_CAT_FORM              = 32, // Must be in Cat Form
    SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT             = 33, // Only Death Knights may enter Ebon Hold.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_FERAL_FORM            = 34, // Must be in Cat Form, Bear Form, or Dire Bear Form
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_HELPLESS_VILLAGER   = 35, // You must be within range of a Helpless Wintergarde Villager.
    SPELL_CUSTOM_ERROR_CANT_TARGET_ELEMENTAL_MECHANICAL = 36, // You cannot target an elemental or mechanical corpse.
    SPELL_CUSTOM_ERROR_MUST_HAVE_USED_DALARAN_CRYSTAL   = 37, // This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once.
    SPELL_CUSTOM_ERROR_YOU_ALREADY_HOLD_SOMETHING       = 38, // You are already holding something in your hand. You must throw the creature in your hand before picking up another.
    SPELL_CUSTOM_ERROR_YOU_DONT_HOLD_ANYTHING           = 39, // You don't have anything to throw! Find a Vargul and use Gymer Grab to pick one up!
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_VALDURAN        = 40, // Bouldercrag's War Horn can only be used within 10 yards of Valduran the Stormborn.
    SPELL_CUSTOM_ERROR_NO_PASSENGER                     = 41, // You are not carrying a passenger. There is nobody to drop off.
    SPELL_CUSTOM_ERROR_CANT_BUILD_MORE_VEHICLES         = 42, // You cannot build any more siege vehicles.
    SPELL_CUSTOM_ERROR_ALREADY_CARRYING_CRUSADER        = 43, // You are already carrying a captured Argent Crusader. You must return to the Argent Vanguard infirmary and drop off your passenger before you may pick up another.
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED             = 44, // You can't do that while rooted.
    SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_TARGET           = 45, // Requires a nearby target.
    SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER              = 46, // Nothing left to discover.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_TARGETS               = 47, // No targets close enough to bluff.
    SPELL_CUSTOM_ERROR_CONSTRUCT_TOO_FAR                = 48, // Your Iron Rune Construct is out of range.
    SPELL_CUSTOM_ERROR_REQUIRES_GRAND_MASTER_ENGINEER   = 49, // Requires Grand Master Engineer
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_MOUNT              = 50, // You can't use that mount.
    SPELL_CUSTOM_ERROR_NOONE_TO_EJECT                   = 51, // There is nobody to eject!
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_BOUND             = 52, // The target must be bound to you.
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_UNDEAD            = 53, // Target must be undead.
    SPELL_CUSTOM_ERROR_TARGET_TOO_FAR                   = 54, // You have no target or your target is too far away.
    SPELL_CUSTOM_ERROR_MISSING_DARK_MATTER              = 55, // Missing Reagents: Dark Matter
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_ITEM               = 56, // You can't use that item
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_CYCYLONED          = 57, // You can't do that while Cycloned
    SPELL_CUSTOM_ERROR_TARGET_HAS_SCROLL                = 58, // Target is already affected by a scroll
    SPELL_CUSTOM_ERROR_POISON_TOO_STRONG                = 59, // That anti-venom is not strong enough to dispel that poison
    SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_MAIDEN          = 61, // You must be near the Maiden of Winter's Breath Lake.
    SPELL_CUSTOM_ERROR_LEARNED_EVERYTHING               = 62, // You have learned everything from that book
    SPELL_CUSTOM_ERROR_PET_IS_DEAD                      = 63, // Your pet is dead
    SPELL_CUSTOM_ERROR_NO_VALID_TARGETS                 = 64, // There are no valid targets within range.
    SPELL_CUSTOM_ERROR_GM_ONLY                          = 65, // Only GMs may use that. Your account has been reported for investigation.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_58                = 66, // You must reach level 58 to use this portal.
    SPELL_CUSTOM_ERROR_AT_HONOR_CAP                     = 67, // You already have the maximum amount of honor.
    SPELL_CUSTOM_ERROR_HAVE_HOT_ROD                     = 68, // You already have a Hot Rod.
    SPELL_CUSTOM_ERROR_PARTYGOER_MORE_BUBBLY            = 69, // This partygoer wants some more bubbly
    SPELL_CUSTOM_ERROR_PARTYGOER_NEED_BUCKET            = 70, // This partygoer needs a bucket!
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_TO_DANCE          = 71, // This partygoer wants to dance with you.
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_FIREWORKS         = 72, // This partygoer wants to see some fireworks.
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_APPETIZER         = 73, // This partygoer wants some more hors d'oeuvres.
    SPELL_CUSTOM_ERROR_GOBLIN_BATTERY_DEPLETED          = 74, // The Goblin All-In-1-Der Belt's battery is depleted.
    SPELL_CUSTOM_ERROR_MUST_HAVE_DEMONIC_CIRCLE         = 75, // You must have a demonic circle active.
    SPELL_CUSTOM_ERROR_AT_MAX_RAGE                      = 76, // You already have maximum rage
    SPELL_CUSTOM_ERROR_REQUIRES_350_ENGINEERING         = 77, // Requires Engineering (350)
    SPELL_CUSTOM_ERROR_SOUL_BELONGS_TO_LICH_KING        = 78, // Your soul belongs to the Lich King
    SPELL_CUSTOM_ERROR_ATTENDANT_HAS_PONY               = 79, // Your attendant already has an Argent Pony
    SPELL_CUSTOM_ERROR_GOBLIN_STARTING_MISSION          = 80, // First, Overload the Defective Generator, Activate the Leaky Stove, and Drop a Cigar on the Flammable Bed.
    SPELL_CUSTOM_ERROR_GASBOT_ALREADY_SENT              = 81, // You've already sent in the Gasbot and destroyed headquarters!
    SPELL_CUSTOM_ERROR_GOBLIN_IS_PARTIED_OUT            = 82, // This goblin is all partied out!
    SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM             = 83, // You must have a Fire Totem active.
    SPELL_CUSTOM_ERROR_CANT_TARGET_VAMPIRES             = 84, // You may not bite other vampires.
    SPELL_CUSTOM_ERROR_PET_ALREADY_AT_YOUR_LEVEL        = 85, // Your pet is already at your level.
    SPELL_CUSTOM_ERROR_MISSING_ITEM_REQUIREMENS         = 86, // You do not meet the level requirements for this item.
    SPELL_CUSTOM_ERROR_TOO_MANY_ABOMINATIONS            = 87, // There are too many Mutated Abominations.
    SPELL_CUSTOM_ERROR_ALL_POTIONS_USED                 = 88, // The potions have all been depleted by Professor Putricide.
    SPELL_CUSTOM_ERROR_DEFEATED_ENOUGH_ALREADY          = 89, // You have already defeated enough of them.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_65                = 90, // Requires level 65
    SPELL_CUSTOM_ERROR_DESTROYED_KTC_OIL_PLATFORM       = 91, // You have already destroyed the KTC Oil Platform.
    SPELL_CUSTOM_ERROR_LAUNCHED_ENOUGH_CAGES            = 92, // You have already launched enough cages.
    SPELL_CUSTOM_ERROR_REQUIRES_BOOSTER_ROCKETS         = 93, // Requires Single-Stage Booster Rockets. Return to Hobart Grapplehammer to get more.
    SPELL_CUSTOM_ERROR_ENOUGH_WILD_CLUCKERS             = 94, // You have already captured enough wild cluckers.
    SPELL_CUSTOM_ERROR_REQUIRES_CONTROL_FIREWORKS       = 95, // Requires Remote Control Fireworks. Return to Hobart Grapplehammer to get more.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_RECRUITS           = 96, // You already have the max number of recruits.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_VOLUNTEERS         = 97, // You already have the max number of volunteers.
    SPELL_CUSTOM_ERROR_FROSTMOURNE_RENDERED_RESSURECT   = 98, // Frostmourne has rendered you unable to ressurect.
    SPELL_CUSTOM_ERROR_CANT_MOUNT_WITH_SHAPESHIFT       = 99, // You can't mount while affected by that shapeshift.
    SPELL_CUSTOM_ERROR_FAWNS_ALREADY_FOLLOWING          = 100, // Three fawns are already following you!
    SPELL_CUSTOM_ERROR_ALREADY_HAVE_RIVER_BOAT          = 101, // You already have a River Boat.
    SPELL_CUSTOM_ERROR_NO_ACTIVE_ENCHANTMENT            = 102, // You have no active enchantment to unleash.
    SPELL_CUSTOM_ERROR_ENOUGH_HIGHBOURNE_SOULS          = 103, // You have bound enough Highborne souls. Return to Arcanist Valdurian.
    SPELL_CUSTOM_ERROR_ATLEAST_40YD_FROM_OIL_DRILLING   = 104, // You must be at least 40 yards away from all other Oil Drilling Rigs.
    SPELL_CUSTOM_ERROR_ABOVE_ENSLAVED_PEARL_MINER       = 106, // You must be above the Enslaved Pearl Miner.
    SPELL_CUSTOM_ERROR_MUST_TARGET_CORPSE_SPECIAL_1     = 107, // You must target the corpse of a Seabrush Terrapin, Scourgut Remora, or Spinescale Hammerhead.
    SPELL_CUSTOM_ERROR_SLAGHAMMER_ALREADY_PRISONER      = 108, // Ambassador Slaghammer is already your prisoner.
    SPELL_CUSTOM_ERROR_REQUIRE_ATTUNED_LOCATION_1       = 109, // Requires a location that is attuned with the Naz'jar Battlemaiden.
    SPELL_CUSTOM_ERROR_NEED_TO_FREE_DRAKE_FIRST         = 110, // Free the Drake from the net first!
    SPELL_CUSTOM_ERROR_DRAGONMAW_ALLIES_ALREADY_FOLLOW  = 111, // You already have three Dragonmaw allies following you.
    SPELL_CUSTOM_ERROR_REQUIRE_OPPOSABLE_THUMBS         = 112, // Requires Opposable Thumbs.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH_2              = 113, // Not enough health
    SPELL_CUSTOM_ERROR_ENOUGH_FORSAKEN_TROOPERS         = 114, // You already have enough Forsaken Troopers.
    SPELL_CUSTOM_ERROR_CANNOT_JUMP_TO_BOULDER           = 115, // You cannot jump to another boulder yet.
    SPELL_CUSTOM_ERROR_SKILL_TOO_HIGH                   = 116, // Skill too high.
    SPELL_CUSTOM_ERROR_ALREADY_6_SURVIVORS_RESCUED      = 117, // You have already rescued 6 Survivors.
    SPELL_CUSTOM_ERROR_MUST_FACE_SHIPS_FROM_BALLOON     = 118, // You need to be facing the ships from the rescue balloon.
    SPELL_CUSTOM_ERROR_CANNOT_SUPERVISE_MORE_CULTISTS   = 119, // You cannot supervise more than 5 Arrested Cultists at a time.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_85                = 120, // You must reach level 85 to use this portal.
    SPELL_CUSTOM_ERROR_MUST_BE_BELOW_35_HEALTH          = 121, // Your target must be below 35% health.
    SPELL_CUSTOM_ERROR_MUST_SELECT_TALENT_SPECIAL       = 122, // You must select a talent specialization first.
    SPELL_CUSTOM_ERROR_TOO_WISE_AND_POWERFUL            = 123, // You are too wise and powerful to gain any benefit from that item.
    SPELL_CUSTOM_ERROR_TOO_CLOSE_ARGENT_LIGHTWELL       = 124, // You are within 10 yards of another Argent Lightwell.
    SPELL_CUSTOM_ERROR_NOT_WHILE_SHAPESHIFTED           = 125, // You can't do that while shapeshifted.
    SPELL_CUSTOM_ERROR_MANA_GEM_IN_BANK                 = 126, // You already have a Mana Gem in your bank.
    SPELL_CUSTOM_ERROR_FLAME_SHOCK_NOT_ACTIVE           = 127, // You must have at least one Flame Shock active.
    SPELL_CUSTOM_ERROR_CANT_TRANSFORM                   = 128, // You cannot transform right now
    SPELL_CUSTOM_ERROR_PET_MUST_BE_ATTACKING            = 129, // Your pet must be attacking a target.
    SPELL_CUSTOM_ERROR_GNOMISH_ENGINEERING              = 130, // Requires Gnomish Engineering
    SPELL_CUSTOM_ERROR_GOBLIN_ENGINEERING               = 131, // Requires Goblin Engineering
    SPELL_CUSTOM_ERROR_NO_TARGET                        = 132, // You have no target.
    SPELL_CUSTOM_ERROR_PET_OUT_OF_RANGE                 = 133, // Your Pet is out of range of the target.
    SPELL_CUSTOM_ERROR_HOLDING_FLAG                     = 134, // You can't do that while holding the flag.
    SPELL_CUSTOM_ERROR_TARGET_HOLDING_FLAG              = 135, // You can't do that to targets holding the flag.
    SPELL_CUSTOM_ERROR_PORTAL_NOT_OPEN                  = 136, // The portal is not yet open. Continue helping the druids at the Sanctuary of Malorne.
    SPELL_CUSTOM_ERROR_AGGRA_AIR_TOTEM                  = 137, // You need to be closer to Aggra's Air Totem, in the west.
    SPELL_CUSTOM_ERROR_AGGRA_WATER_TOTEM                = 138, // You need to be closer to Aggra's Water Totem, in the north.
    SPELL_CUSTOM_ERROR_AGGRA_EARTH_TOTEM                = 139, // You need to be closer to Aggra's Earth Totem, in the east.
    SPELL_CUSTOM_ERROR_AGGRA_FIRE_TOTEM                 = 140, // You need to be closer to Aggra's Fire Totem, near Thrall.
    SPELL_CUSTOM_ERROR_TARGET_HAS_STARTDUST_2           = 148, // Target is already affected by Stardust No. 2.
    SPELL_CUSTOM_ERROR_ELEMENTIUM_GEM_CLUSTERS          = 149, // You cannot deconstruct Elementium Gem Clusters while collecting them!
    SPELL_CUSTOM_ERROR_YOU_DONT_HAVE_ENOUGH_HELTH                               = 150, // You don't have enough health
    SPELL_CUSTOM_ERROR_CANNOT_USE_GATEWAY_YET                                   = 151, // You cannot use the gateway yey
    SPELL_CUSTOM_ERROR_MUST_CHOOSE_SPEC_ASCENDANCE                              = 152, // You must choose a specialization to use Ascendance
    SPELL_CUSTOM_ERROR_INSUFFICIENT_BLOOD_CHARGES                               = 153, // You have insufficient Blood Charges
    SPELL_CUSTOM_ERROR_NO_FULLY_DEPLETED_RUNES                                  = 154, // No fully depleted runes
    SPELL_CUSTOM_ERROR_NO_MORE_CHARGES                                          = 155, // No more charges
    SPELL_CUSTOM_ERROR_STATUE_OUT_OF_RANGE                                      = 156, // Statue is out of range of the target
    SPELL_CUSTOM_ERROR_NO_STATUE_SUMMONED                                       = 157, // You don't have a statue summoned
    SPELL_CUSTOM_ERROR_NO_SPIRIT_ACTIVE                                         = 158, // You have no spirit active
    SPELL_CUSTOM_ERROR_BOTH_FROST_FEVER_BLOOD_PLAGUE                            = 159, // Both Frost Fever and Blood Plague must be present on the target
    SPELL_CUSTOM_ERROR_NOT_WHILE_HOLDING_ORB_OF_POWER                           = 160, // You can't do that while holding an Orb of Power
    SPELL_CUSTOM_ERROR_NOT_WHILE_JUMPING_OR_FALLING                             = 161, // You can't do that while jumping or falling
    SPELL_CUSTOM_ERROR_MUST_BE_TRANSFORMED_BY_POLYMORPHIC_ACID                  = 162, // You must be transformed by Polymorphic Acid
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_ACID_TO_STORE_TRANSFORMATION                  = 163, // There isn't enough acid left to store this transformation
    SPELL_CUSTOM_ERROR_MUST_OBTAIN_FLIGHT_MASTER_LICENSE                        = 164, // You must obtain a Flight Master's license before using this spell
    SPELL_CUSTOM_ERROR_ALREADY_HAVE_SAMPLED_SAP                                 = 165, // You have already sampled sap from this Feeder
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_MANTID_FEEDER                               = 166, // Requires you to be near a Mantid Feeder in the Heart of Fear
    SPELL_CUSTOM_ERROR_MUST_BE_DIRECTLY_IN_FRONT                                = 167, // Target must be directly in front of you
    SPELL_CUSTOM_ERROR_NOT_DURING_CHALLENGE_MODE                                = 168, // You can't do that during a Challenge Mode
    SPELL_CUSTOM_ERROR_NOT_CORRECT_CLASS_FOR_THAT_MOUNT                         = 169, // You are not the correct class for that mount
    SPELL_CUSTOM_ERROR_NOTHING_LEFT_TO_DISCOVER                                 = 170, // Nothing left to discover
    SPELL_CUSTOM_ERROR_NO_EXPLOSIVES_AVAILABLE                                  = 171, // There are no explosives available
    SPELL_CUSTOM_ERROR_MUST_BE_FLAGGED_FOR_PVP                                  = 172, // You must be flagged for PvP
    SPELL_CUSTOM_ERROR_REQUIRES_BATTLE_RATIONS_OR_MEATY_HAUNCH                  = 173, // Requires Battle Rations or Meaty Haunch
    SPELL_CUSTOM_ERROR_REQUIRES_BRITTLE_ROOT                                    = 174, // Requires Brittle Root
    SPELL_CUSTOM_ERROR_REQUIRES_LABORER_TOOL                                    = 175, // Requires Laborer's Tool
    SPELL_CUSTOM_ERROR_REQUIRES_UNEXPLODED_CANNONBALL                           = 176, // Requires Unexploded Cannonball
    SPELL_CUSTOM_ERROR_REQUIRES_MISPLACED_KEG                                   = 177, // Requires Misplaced Keg
    SPELL_CUSTOM_ERROR_REQUIRES_LIQUID_FIRE_JUNGLE_HOPS_OR_SPIRIT_KISSED_WATER  = 178, // Requires Liquid Fire, Jungle Hops, or Spirit-kissed Water
    SPELL_CUSTOM_ERROR_REQUIRES_KRASARI_IRON                                    = 179, // Requires Krasari Iron
    SPELL_CUSTOM_ERROR_REQUIRES_SPIRIT_KISSED_WATER                             = 180, // Requires Spirit-kissed Water
    SPELL_CUSTOM_ERROR_REQUIRES_SNAKE_OIL                                       = 181, // Requires Snake Oil
    SPELL_CUSTOM_ERROR_NOT_WHILE_SCENARIO_IS_IN_PROGRESS                        = 182, // You can't do that while a Scenario is in progress
    SPELL_CUSTOM_ERROR_REQUIRES_DARKMOON_FAIRE_TO_BE_OPEN                       = 183, // Requires the Darkmoon Faire to be open
    SPELL_CUSTOM_ERROR_ALREADY_AT_VALOR_CAP                                     = 184, // Already at Valor cap
    SPELL_CUSTOM_ERROR_ALREADY_COMMENDED_BY_THIS_FACTION                        = 185, // Already commended by this faction
    SPELL_CUSTOM_ERROR_OUT_OF_COINS_PICKPOCKET_HUMANOIDS_TO_GET_MORE            = 186, // Out of coins! Pickpocket humanoids to get more
    SPELL_CUSTOM_ERROR_ONLY_ONE_ELEMENTAL_SPIRIT_ON_A_TARGET_AT_A_TIME          = 187, // Only one elemental spirit on a target at a time
    SPELL_CUSTOM_ERROR_YOU_DONT_KNOW_HOW_TO_TAME_DIREHORNS                      = 188, // You do not know how to tame Direhorns
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_THE_BLOODIED_COURT_GATE                     = 189, // You must be near the Bloodied Court gate
    SPELL_CUSTOM_ERROR_YOU_ARE_NOT_ELECTRIFIED                                  = 190, // You are not Electrified
    SPELL_CUSTOM_ERROR_THERE_IS_NOTHING_TO_BE_FETCHED                           = 191, // There is nothing to be fetched
    SPELL_CUSTOM_ERROR_REQUIRES_THE_THUNDER_FORGE                               = 192, // Requires The Thunder Forge
    SPELL_CUSTOM_ERROR_CANNOT_USE_THE_DICE_AGAIN_YET                            = 193, // You cannot use the dice again yet
    SPELL_CUSTOM_ERROR_ALREADY_A_MEMBER_OF_THE_BRAWLER_GUILD                    = 194, // You are already a member of the Brawler's Guild
    SPELL_CUSTOM_ERROR_CANT_CHANGE_SPEC_DURING_CELESTIAL_CHALLENGE              = 195, // You may not change talent specializations during a celestial challenge
    SPELL_CUSTOM_ERROR_YOUR_SPEC_DOES_NOT_MATCH_SELECTED_CHALLENGE              = 196, // Your talent specialization does not match the selected challenge
    SPELL_CUSTOM_ERROR_YOU_DONT_HAVE_ENOUGH_CURRENCY                            = 197, // You don't have enough currency to do that
    SPELL_CUSTOM_ERROR_TARGET_CANT_BENEFIT_FROM_THAT_SPELL                      = 198, // Target cannot benefit from that spell
    SPELL_CUSTOM_ERROR_ONLY_ONE_HEALING_RAIN_ACTIVE_AT_A_TIME                   = 199, // You can only have one Healing Rain active at a time
    SPELL_CUSTOM_ERROR_THE_DOOR_IS_LOCKED                                       = 200, // The door is locked
    SPELL_CUSTOM_ERROR_NEED_SELECT_A_CUSTOMER_WHO_IS_WAITING_IN_LINE            = 201, // You need to select a customer who is waiting in line first
    SPELL_CUSTOM_ERROR_CANT_CHANGE_SPEC_WHILE_TRIAL_IS_IN_PROGRESS              = 202, // You may not change specialization while a trial is in progress
    SPELL_CUSTOM_ERROR_MUST_WAIT_FOR_CUSTOMERS_TO_GET_IN_LINE                   = 203, // You must wait for customers to get in line before you can select them to be seated
};

enum StealthType
{
    STEALTH_GENERAL     = 0,
    STEALTH_TRAP        = 1,

    TOTAL_STEALTH_TYPES = 2
};

enum InvisibilityType
{
    INVISIBILITY_GENERAL     =  0,
    INVISIBILITY_UNK1        =  1,
    INVISIBILITY_UNK2        =  2,
    INVISIBILITY_TRAP        =  3,
    INVISIBILITY_UNK4        =  4,
    INVISIBILITY_UNK5        =  5,
    INVISIBILITY_DRUNK       =  6,
    INVISIBILITY_UNK7        =  7,
    INVISIBILITY_UNK8        =  8,
    INVISIBILITY_UNK9        =  9,
    INVISIBILITY_UNK10       = 10,
    INVISIBILITY_UNK11       = 11,
    INVISIBILITY_UNK12       = 12,
    INVISIBILITY_UNK13       = 13,
    INVISIBILITY_UNK14       = 14,
    INVISIBILITY_UNK15       = 15,
    INVISIBILITY_UNK16       = 16,
    INVISIBILITY_UNK17       = 17,
    INVISIBILITY_UNK18       = 18,
    INVISIBILITY_UNK19       = 19,
    INVISIBILITY_UNK20       = 20,
    INVISIBILITY_UNK21       = 21,
    INVISIBILITY_UNK22       = 22,
    INVISIBILITY_UNK23       = 23,
    INVISIBILITY_UNK24       = 24,
    INVISIBILITY_UNK25       = 25,
    INVISIBILITY_UNK26       = 26,
    INVISIBILITY_UNK27       = 27,
    INVISIBILITY_UNK28       = 28,
    INVISIBILITY_UNK29       = 29,
    INVISIBILITY_UNK30       = 30,
    INVISIBILITY_UNK31       = 31,
    INVISIBILITY_UNK32       = 32,
    INVISIBILITY_UNK33       = 33,
    INVISIBILITY_UNK34       = 34,
    INVISIBILITY_UNK35       = 35,
    INVISIBILITY_UNK36       = 36,
    INVISIBILITY_UNK37       = 37,

    TOTAL_INVISIBILITY_TYPES = 38
};

enum ServerSideVisibilityType
{
    SERVERSIDE_VISIBILITY_GM          = 0,
    SERVERSIDE_VISIBILITY_GHOST       = 1,

    TOTAL_SERVERSIDE_VISIBILITY_TYPES = 2
};

enum GhostVisibilityType
{
    GHOST_VISIBILITY_ALIVE = 0x1,
    GHOST_VISIBILITY_GHOST = 0x2
};

// Spell aura states
enum AuraStateType
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE                         = 0,            // C   |
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    //AURA_STATE_UNKNOWN6                   = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    //AURA_STATE_UNKNOWN7                   = 7,            //  c  | creature cheap shot / focused bursts spells
    //AURA_STATE_UNKNOWN8                   = 8,            //    t| test spells
    //AURA_STATE_UNKNOWN9                   = 9,            //     |
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    //AURA_STATE_UNKNOWN11                  = 11,           // C  t| 60348 - Maelstrom Ready!, test spells
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_DAMAGE_TAKEN_14              = 14,           //   T |
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    AURA_STATE_BLEEDING                     = 18,           //    T|
    AURA_STATE_UNKNOWN19                    = 19,           //     |
    AURA_STATE_PREPARATION                  = 20,           //  c  | only (45317 Suicide)
    //AURA_STATE_UNKNOWN21                  = 21,           //     | not used
    AURA_STATE_UNKNOWN22                    = 22,           // C  t| varius spells (63884, 50240)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23            // C   |
};

#define PER_CASTER_AURA_STATE_MASK (\
    (1<<(AURA_STATE_DEADLY_POISON-1)))

// Spell mechanics
enum Mechanics
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_SLOW_ATTACK      = 8,
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31,
    MECHANIC_WOUNDED          = 32,
    MAX_MECHANIC = 33
};

// Used for spell 42292 Immune Movement Impairment and Loss of Control (0x49967ca6)
#define IMMUNE_TO_MOVEMENT_IMPAIRMENT_AND_LOSS_CONTROL_MASK (\
    (1<<MECHANIC_CHARM)|(1<<MECHANIC_DISORIENTED)|(1<<MECHANIC_FEAR)| \
    (1<<MECHANIC_ROOT)|(1<<MECHANIC_SLEEP)|(1<<MECHANIC_SNARE)| \
    (1<<MECHANIC_STUN)|(1<<MECHANIC_FREEZE)|(1<<MECHANIC_SILENCE)|(1<<MECHANIC_DISARM)|(1<<MECHANIC_KNOCKOUT)| \
    (1<<MECHANIC_POLYMORPH)|(1<<MECHANIC_BANISH)|(1<<MECHANIC_SHACKLE)| \
    (1<<MECHANIC_TURN)|(1<<MECHANIC_HORROR)|(1<<MECHANIC_DAZE)| \
    (1<<MECHANIC_SAPPED))

// Spell dispel type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

#define DISPEL_ALL_MASK ((1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_DISEASE) | (1<<DISPEL_POISON))

//To all Immune system, if target has immunes,
//some spell that related to ImmuneToDispel or ImmuneToSchool or ImmuneToDamage type can't cast to it,
//some spell_effects that related to ImmuneToEffect<effect>(only this effect in the spell) can't cast to it,
//some aura(related to Mechanics or ImmuneToState<aura>) can't apply to it.
enum SpellImmunity
{
    IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
    IMMUNITY_STATE                 = 1,                     // enum AuraType
    IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
    IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
    IMMUNITY_DISPEL                = 4,                     // enum DispelType
    IMMUNITY_MECHANIC              = 5,                     // enum Mechanics
    IMMUNITY_ID                    = 6
};

#define MAX_SPELL_IMMUNITY           7

// target enum name consist of:
// TARGET_[OBJECT_TYPE]_[REFERENCE_TYPE(skipped for caster)]_[SELECTION_TYPE(skipped for default)]_[additional specifiers(friendly, BACK_LEFT, etc.]
enum Targets
{
    TARGET_UNIT_CASTER                 = 1,
    TARGET_UNIT_NEARBY_ENEMY           = 2,
    TARGET_UNIT_NEARBY_PARTY           = 3,
    TARGET_UNIT_NEARBY_ALLY            = 4,
    TARGET_UNIT_PET                    = 5,
    TARGET_UNIT_TARGET_ENEMY           = 6,
    TARGET_UNIT_SRC_AREA_ENTRY         = 7,
    TARGET_UNIT_DEST_AREA_ENTRY        = 8,
    TARGET_DEST_HOME                   = 9,
    TARGET_UNIT_SRC_AREA_UNK_11        = 11,
    TARGET_UNIT_SRC_AREA_ENEMY         = 15,
    TARGET_UNIT_DEST_AREA_ENEMY        = 16,
    TARGET_DEST_DB                     = 17,
    TARGET_DEST_CASTER                 = 18,
    TARGET_UNIT_CASTER_AREA_PARTY      = 20,
    TARGET_UNIT_TARGET_ALLY            = 21,
    TARGET_SRC_CASTER                  = 22,
    TARGET_GAMEOBJECT_TARGET           = 23,
    TARGET_UNIT_CONE_ENEMY_24          = 24,
    TARGET_UNIT_TARGET_ANY             = 25,
    TARGET_GAMEOBJECT_ITEM_TARGET      = 26,
    TARGET_UNIT_MASTER                 = 27,
    TARGET_DEST_DYNOBJ_ENEMY           = 28,
    TARGET_DEST_DYNOBJ_ALLY            = 29,
    TARGET_UNIT_SRC_AREA_ALLY          = 30,
    TARGET_UNIT_DEST_AREA_ALLY         = 31,
    TARGET_DEST_CASTER_SUMMON          = 32, // front left, doesn't use radius
    TARGET_UNIT_SRC_AREA_PARTY         = 33,
    TARGET_UNIT_DEST_AREA_PARTY        = 34,
    TARGET_UNIT_TARGET_PARTY           = 35,
    TARGET_DEST_CASTER_UNK_36          = 36,
    TARGET_UNIT_LASTTARGET_AREA_PARTY  = 37,
    TARGET_UNIT_NEARBY_ENTRY           = 38,
    TARGET_DEST_CASTER_FISHING         = 39,
    TARGET_GAMEOBJECT_NEARBY_ENTRY     = 40,
    TARGET_DEST_CASTER_FRONT_RIGHT     = 41,
    TARGET_DEST_CASTER_BACK_RIGHT      = 42,
    TARGET_DEST_CASTER_BACK_LEFT       = 43,
    TARGET_DEST_CASTER_FRONT_LEFT      = 44,
    TARGET_UNIT_TARGET_CHAINHEAL_ALLY  = 45,
    TARGET_DEST_NEARBY_ENTRY           = 46,
    TARGET_DEST_CASTER_FRONT           = 47,
    TARGET_DEST_CASTER_BACK            = 48,
    TARGET_DEST_CASTER_RIGHT           = 49,
    TARGET_DEST_CASTER_LEFT            = 50,
    TARGET_GAMEOBJECT_SRC_AREA         = 51,
    TARGET_GAMEOBJECT_DEST_AREA        = 52,
    TARGET_DEST_TARGET_ENEMY           = 53,
    TARGET_UNIT_CONE_ENEMY_WITH_OFFSET = 54,
    TARGET_DEST_CASTER_FRONT_LEAP      = 55, // for a leap spell
    TARGET_UNIT_CASTER_AREA_RAID       = 56,
    TARGET_UNIT_TARGET_RAID            = 57,
    TARGET_UNIT_NEARBY_RAID            = 58,
    TARGET_UNIT_CONE_ALLY              = 59,
    TARGET_UNIT_CONE_ENTRY             = 60,
    TARGET_UNIT_TARGET_AREA_RAID_CLASS = 61,
    TARGET_UNK_62                      = 62,
    TARGET_DEST_TARGET_ANY             = 63,
    TARGET_DEST_TARGET_FRONT           = 64,
    TARGET_DEST_TARGET_BACK            = 65,
    TARGET_DEST_TARGET_RIGHT           = 66,
    TARGET_DEST_TARGET_LEFT            = 67,
    TARGET_DEST_TARGET_FRONT_RIGHT     = 68,
    TARGET_DEST_TARGET_BACK_RIGHT      = 69,
    TARGET_DEST_TARGET_BACK_LEFT       = 70,
    TARGET_DEST_TARGET_FRONT_LEFT      = 71,
    TARGET_DEST_CASTER_RANDOM          = 72,
    TARGET_DEST_CASTER_RADIUS          = 73,
    TARGET_DEST_TARGET_RANDOM          = 74,
    TARGET_DEST_TARGET_RADIUS          = 75,
    TARGET_DEST_CHANNEL_TARGET         = 76,
    TARGET_UNIT_CHANNEL_TARGET         = 77,
    TARGET_DEST_DEST_FRONT             = 78,
    TARGET_DEST_DEST_BACK              = 79,
    TARGET_DEST_DEST_RIGHT             = 80,
    TARGET_DEST_DEST_LEFT              = 81,
    TARGET_DEST_DEST_FRONT_RIGHT       = 82,
    TARGET_DEST_DEST_BACK_RIGHT        = 83,
    TARGET_DEST_DEST_BACK_LEFT         = 84,
    TARGET_DEST_DEST_FRONT_LEFT        = 85,
    TARGET_DEST_DEST_RANDOM            = 86,
    TARGET_DEST_DEST                   = 87,
    TARGET_DEST_DYNOBJ_NONE            = 88,
    TARGET_DEST_TRAJ                   = 89,
    TARGET_UNIT_TARGET_MINIPET         = 90,
    TARGET_DEST_DEST_RADIUS            = 91,
    TARGET_UNIT_SUMMONER               = 92,
    TARGET_CORPSE_SRC_AREA_ENEMY       = 93, // NYI
    TARGET_UNIT_VEHICLE                = 94,
    TARGET_UNIT_TARGET_PASSENGER       = 95,
    TARGET_UNIT_PASSENGER_0            = 96,
    TARGET_UNIT_PASSENGER_1            = 97,
    TARGET_UNIT_PASSENGER_2            = 98,
    TARGET_UNIT_PASSENGER_3            = 99,
    TARGET_UNIT_PASSENGER_4            = 100,
    TARGET_UNIT_PASSENGER_5            = 101,
    TARGET_UNIT_PASSENGER_6            = 102,
    TARGET_UNIT_PASSENGER_7            = 103,
    TARGET_UNIT_CONE_ENEMY_104         = 104,
    TARGET_UNIT_UNK_105                = 105, // 1 spell
    TARGET_DEST_CHANNEL_CASTER         = 106,
    TARGET_UNK_DEST_AREA_UNK_107       = 107, // not enough info - only generic spells avalible
    TARGET_GAMEOBJECT_CONE             = 108,
    TARGET_UNIT_CONE_ENEMY_110         = 110,
    TARGET_UNK_111                     = 111,
    TARGET_UNK_112                     = 112,
    TARGET_UNK_113                     = 113,
    TARGET_UNK_114                     = 114,
    TARGET_UNK_115                     = 115,
    TARGET_UNK_116                     = 116,
    TARGET_UNK_117                     = 117,
    TARGET_UNIT_TARGET_OR_UNIT_PARTY   = 118, // Raid buffs.
    TARGET_UNIT_TARGET_RAID_DEAD       = 119,
    TARGET_UNK_120                     = 120,
    TARGET_UNK_121                     = 121,
    TARGET_UNK_122                     = 122,
    TARGET_UNIT_RECIPIENT_RAID         = 123,
    TARGET_UNK_124                     = 124,
    TARGET_UNK_125                     = 125,
    TARGET_UNK_126                     = 126,
    TARGET_UNK_127                     = 127,
    TARGET_UNK_128                     = 128,
    TARGET_UNIT_CONE_ENEMY_129         = 129,
    TARGET_UNIT_CONE_UNK_130           = 130,
    TARGET_UNK_131                     = 131,
    TARGET_DEST_TARGET_ALLY            = 132,
    TARGET_UNK_133                     = 133,
    TARGET_UNK_134                     = 134,
    TARGET_UNK_135                     = 135,
    TARGET_UNIT_CONE_ALLY_136          = 136,
    TARGET_DEST_CASTER_MOVEMENT_DIR    = 137,
    TARGET_UNK_138                     = 138,
    TARGET_UNK_139                     = 139,
    TARGET_UNK_140                     = 140,
    TARGET_UNK_141                     = 141,
    TARGET_UNK_142                     = 142,
    TARGET_UNK_143                     = 143,
    TOTAL_SPELL_TARGETS
};

enum SpellMissInfo
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8, // one of these 2 is MISS_TEMPIMMUNE
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

enum SpellHitType
{
    SPELL_HIT_TYPE_UNK1 = 0x00001,
    SPELL_HIT_TYPE_CRIT = 0x00002,
    SPELL_HIT_TYPE_UNK3 = 0x00004,
    SPELL_HIT_TYPE_UNK4 = 0x00008,
    SPELL_HIT_TYPE_UNK5 = 0x00010,                          // replace caster?
    SPELL_HIT_TYPE_UNK6 = 0x00020
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE      = 0x00,
    SPELL_PREVENTION_TYPE_SILENCE   = 0x01,
    SPELL_PREVENTION_TYPE_PACIFY    = 0x02,
    SPELL_PREVENTION_TYPE_POLYMORPH = 0x04, // Guess
};

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35,
    GAMEOBJECT_TYPE_FLAGSTAND_2            = 36,
};

#define MAX_GAMEOBJECT_TYPE                  38             // sending to client this or greater value can crash client.
#define MAX_GAMEOBJECT_DATA                  32             // Max number of uint32 vars in gameobject_template data field

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   // disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   // cannot interact (condition to interact)
    GO_FLAG_TRANSPORT       = 0x00000008,                   // any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_NOT_SELECTABLE  = 0x00000010,                   // not selectable even in GM mode
    GO_FLAG_NODESPAWN       = 0x00000020,                   // never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED       = 0x00000040,                   // typically, summoned objects. Triggered by spell or other events
    GO_FLAG_DAMAGED         = 0x00000200,
    GO_FLAG_DESTROYED       = 0x00000400
};

// flags shifting needs to be verified / everything was swifted by 1
enum GameObjectDynamicLowFlags
{
    GO_UNK_MOP                      = 0x01,                  // makes gameobject dissapear
    GO_DYNFLAG_LO_ACTIVATE          = 0x02,                 // enables interaction with GO
    GO_DYNFLAG_LO_ANIMATE           = 0x04,                 // possibly more distinct animation of GO
    GO_DYNFLAG_LO_NO_INTERACT       = 0x08,                 // appears to disable interaction (not fully verified)
    GO_DYNFLAG_LO_SPARKLE           = 0x10,                 // makes GO sparkle
    GO_DYNFLAG_LO_STOPPED           = 0x20                  // Transport is stopped
};

enum GameObjectDestructibleState
{
    GO_DESTRUCTIBLE_INTACT      = 0,
    GO_DESTRUCTIBLE_DAMAGED     = 1,
    GO_DESTRUCTIBLE_DESTROYED   = 2,
    GO_DESTRUCTIBLE_REBUILDING  = 3
};

// EmotesText.dbc
enum TextEmotes
{
    TEXT_EMOTE_AGREE                = 1,
    TEXT_EMOTE_AMAZE                = 2,
    TEXT_EMOTE_ANGRY                = 3,
    TEXT_EMOTE_APOLOGIZE            = 4,
    TEXT_EMOTE_APPLAUD              = 5,
    TEXT_EMOTE_BASHFUL              = 6,
    TEXT_EMOTE_BECKON               = 7,
    TEXT_EMOTE_BEG                  = 8,
    TEXT_EMOTE_BITE                 = 9,
    TEXT_EMOTE_BLEED                = 10,
    TEXT_EMOTE_BLINK                = 11,
    TEXT_EMOTE_BLUSH                = 12,
    TEXT_EMOTE_BONK                 = 13,
    TEXT_EMOTE_BORED                = 14,
    TEXT_EMOTE_BOUNCE               = 15,
    TEXT_EMOTE_BRB                  = 16,
    TEXT_EMOTE_BOW                  = 17,
    TEXT_EMOTE_BURP                 = 18,
    TEXT_EMOTE_BYE                  = 19,
    TEXT_EMOTE_CACKLE               = 20,
    TEXT_EMOTE_CHEER                = 21,
    TEXT_EMOTE_CHICKEN              = 22,
    TEXT_EMOTE_CHUCKLE              = 23,
    TEXT_EMOTE_CLAP                 = 24,
    TEXT_EMOTE_CONFUSED             = 25,
    TEXT_EMOTE_CONGRATULATE         = 26,
    TEXT_EMOTE_COUGH                = 27,
    TEXT_EMOTE_COWER                = 28,
    TEXT_EMOTE_CRACK                = 29,
    TEXT_EMOTE_CRINGE               = 30,
    TEXT_EMOTE_CRY                  = 31,
    TEXT_EMOTE_CURIOUS              = 32,
    TEXT_EMOTE_CURTSEY              = 33,
    TEXT_EMOTE_DANCE                = 34,
    TEXT_EMOTE_DRINK                = 35,
    TEXT_EMOTE_DROOL                = 36,
    TEXT_EMOTE_EAT                  = 37,
    TEXT_EMOTE_EYE                  = 38,
    TEXT_EMOTE_FART                 = 39,
    TEXT_EMOTE_FIDGET               = 40,
    TEXT_EMOTE_FLEX                 = 41,
    TEXT_EMOTE_FROWN                = 42,
    TEXT_EMOTE_GASP                 = 43,
    TEXT_EMOTE_GAZE                 = 44,
    TEXT_EMOTE_GIGGLE               = 45,
    TEXT_EMOTE_GLARE                = 46,
    TEXT_EMOTE_GLOAT                = 47,
    TEXT_EMOTE_GREET                = 48,
    TEXT_EMOTE_GRIN                 = 49,
    TEXT_EMOTE_GROAN                = 50,
    TEXT_EMOTE_GROVEL               = 51,
    TEXT_EMOTE_GUFFAW               = 52,
    TEXT_EMOTE_HAIL                 = 53,
    TEXT_EMOTE_HAPPY                = 54,
    TEXT_EMOTE_HELLO                = 55,
    TEXT_EMOTE_HUG                  = 56,
    TEXT_EMOTE_HUNGRY               = 57,
    TEXT_EMOTE_KISS                 = 58,
    TEXT_EMOTE_KNEEL                = 59,
    TEXT_EMOTE_LAUGH                = 60,
    TEXT_EMOTE_LAYDOWN              = 61,
    TEXT_EMOTE_MESSAGE              = 62,
    TEXT_EMOTE_MOAN                 = 63,
    TEXT_EMOTE_MOON                 = 64,
    TEXT_EMOTE_MOURN                = 65,
    TEXT_EMOTE_NO                   = 66,
    TEXT_EMOTE_NOD                  = 67,
    TEXT_EMOTE_NOSEPICK             = 68,
    TEXT_EMOTE_PANIC                = 69,
    TEXT_EMOTE_PEER                 = 70,
    TEXT_EMOTE_PLEAD                = 71,
    TEXT_EMOTE_POINT                = 72,
    TEXT_EMOTE_POKE                 = 73,
    TEXT_EMOTE_PRAY                 = 74,
    TEXT_EMOTE_ROAR                 = 75,
    TEXT_EMOTE_ROFL                 = 76,
    TEXT_EMOTE_RUDE                 = 77,
    TEXT_EMOTE_SALUTE               = 78,
    TEXT_EMOTE_SCRATCH              = 79,
    TEXT_EMOTE_SEXY                 = 80,
    TEXT_EMOTE_SHAKE                = 81,
    TEXT_EMOTE_SHOUT                = 82,
    TEXT_EMOTE_SHRUG                = 83,
    TEXT_EMOTE_SHY                  = 84,
    TEXT_EMOTE_SIGH                 = 85,
    TEXT_EMOTE_SIT                  = 86,
    TEXT_EMOTE_SLEEP                = 87,
    TEXT_EMOTE_SNARL                = 88,
    TEXT_EMOTE_SPIT                 = 89,
    TEXT_EMOTE_STARE                = 90,
    TEXT_EMOTE_SURPRISED            = 91,
    TEXT_EMOTE_SURRENDER            = 92,
    TEXT_EMOTE_TALK                 = 93,
    TEXT_EMOTE_TALKEX               = 94,
    TEXT_EMOTE_TALKQ                = 95,
    TEXT_EMOTE_TAP                  = 96,
    TEXT_EMOTE_THANK                = 97,
    TEXT_EMOTE_THREATEN             = 98,
    TEXT_EMOTE_TIRED                = 99,
    TEXT_EMOTE_VICTORY              = 100,
    TEXT_EMOTE_WAVE                 = 101,
    TEXT_EMOTE_WELCOME              = 102,
    TEXT_EMOTE_WHINE                = 103,
    TEXT_EMOTE_WHISTLE              = 104,
    TEXT_EMOTE_WORK                 = 105,
    TEXT_EMOTE_YAWN                 = 106,
    TEXT_EMOTE_BOGGLE               = 107,
    TEXT_EMOTE_CALM                 = 108,
    TEXT_EMOTE_COLD                 = 109,
    TEXT_EMOTE_COMFORT              = 110,
    TEXT_EMOTE_CUDDLE               = 111,
    TEXT_EMOTE_DUCK                 = 112,
    TEXT_EMOTE_INSULT               = 113,
    TEXT_EMOTE_INTRODUCE            = 114,
    TEXT_EMOTE_JK                   = 115,
    TEXT_EMOTE_LICK                 = 116,
    TEXT_EMOTE_LISTEN               = 117,
    TEXT_EMOTE_LOST                 = 118,
    TEXT_EMOTE_MOCK                 = 119,
    TEXT_EMOTE_PONDER               = 120,
    TEXT_EMOTE_POUNCE               = 121,
    TEXT_EMOTE_PRAISE               = 122,
    TEXT_EMOTE_PURR                 = 123,
    TEXT_EMOTE_PUZZLE               = 124,
    TEXT_EMOTE_RAISE                = 125,
    TEXT_EMOTE_READY                = 126,
    TEXT_EMOTE_SHIMMY               = 127,
    TEXT_EMOTE_SHIVER               = 128,
    TEXT_EMOTE_SHOO                 = 129,
    TEXT_EMOTE_SLAP                 = 130,
    TEXT_EMOTE_SMIRK                = 131,
    TEXT_EMOTE_SNIFF                = 132,
    TEXT_EMOTE_SNUB                 = 133,
    TEXT_EMOTE_SOOTHE               = 134,
    TEXT_EMOTE_STINK                = 135,
    TEXT_EMOTE_TAUNT                = 136,
    TEXT_EMOTE_TEASE                = 137,
    TEXT_EMOTE_THIRSTY              = 138,
    TEXT_EMOTE_VETO                 = 139,
    TEXT_EMOTE_SNICKER              = 140,
    TEXT_EMOTE_STAND                = 141,
    TEXT_EMOTE_TICKLE               = 142,
    TEXT_EMOTE_VIOLIN               = 143,
    TEXT_EMOTE_SMILE                = 163,
    TEXT_EMOTE_RASP                 = 183,
    TEXT_EMOTE_PITY                 = 203,
    TEXT_EMOTE_GROWL                = 204,
    TEXT_EMOTE_BARK                 = 205,
    TEXT_EMOTE_SCARED               = 223,
    TEXT_EMOTE_FLOP                 = 224,
    TEXT_EMOTE_LOVE                 = 225,
    TEXT_EMOTE_MOO                  = 226,
    TEXT_EMOTE_COMMEND              = 243,
    TEXT_EMOTE_TRAIN                = 264,
    TEXT_EMOTE_HELPME               = 303,
    TEXT_EMOTE_INCOMING             = 304,
    TEXT_EMOTE_CHARGE               = 305,
    TEXT_EMOTE_FLEE                 = 306,
    TEXT_EMOTE_ATTACKMYTARGET       = 307,
    TEXT_EMOTE_OOM                  = 323,
    TEXT_EMOTE_FOLLOW               = 324,
    TEXT_EMOTE_WAIT                 = 325,
    TEXT_EMOTE_HEALME               = 326,
    TEXT_EMOTE_OPENFIRE             = 327,
    TEXT_EMOTE_FLIRT                = 328,
    TEXT_EMOTE_JOKE                 = 329,
    TEXT_EMOTE_GOLFCLAP             = 343,
    TEXT_EMOTE_WINK                 = 363,
    TEXT_EMOTE_PAT                  = 364,
    TEXT_EMOTE_SERIOUS              = 365,
    TEXT_EMOTE_MOUNT_SPECIAL        = 366,
    TEXT_EMOTE_GOODLUCK             = 367,
    TEXT_EMOTE_BLAME                = 368,
    TEXT_EMOTE_BLANK                = 369,
    TEXT_EMOTE_BRANDISH             = 370,
    TEXT_EMOTE_BREATH               = 371,
    TEXT_EMOTE_DISAGREE             = 372,
    TEXT_EMOTE_DOUBT                = 373,
    TEXT_EMOTE_EMBARRASS            = 374,
    TEXT_EMOTE_ENCOURAGE            = 375,
    TEXT_EMOTE_ENEMY                = 376,
    TEXT_EMOTE_EYEBROW              = 377,
    TEXT_EMOTE_TOAST                = 378,
    TEXT_EMOTE_FAIL                 = 379,
    TEXT_EMOTE_HIGHFIVE             = 380,
    TEXT_EMOTE_ABSENT               = 381,
    TEXT_EMOTE_ARM                  = 382,
    TEXT_EMOTE_AWE                  = 383,
    TEXT_EMOTE_BACKPACK             = 384,
    TEXT_EMOTE_BADFEELING           = 385,
    TEXT_EMOTE_CHALLENGE            = 386,
    TEXT_EMOTE_CHUG                 = 387,
    TEXT_EMOTE_DING                 = 389,
    TEXT_EMOTE_FACEPALM             = 390,
    TEXT_EMOTE_FAINT                = 391,
    TEXT_EMOTE_GO                   = 392,
    TEXT_EMOTE_GOING                = 393,
    TEXT_EMOTE_GLOWER               = 394,
    TEXT_EMOTE_HEADACHE             = 395,
    TEXT_EMOTE_HICCUP               = 396,
    TEXT_EMOTE_HISS                 = 398,
    TEXT_EMOTE_HOLDHAND             = 399,
    TEXT_EMOTE_HURRY                = 401,
    TEXT_EMOTE_IDEA                 = 402,
    TEXT_EMOTE_JEALOUS              = 403,
    TEXT_EMOTE_LUCK                 = 404,
    TEXT_EMOTE_MAP                  = 405,
    TEXT_EMOTE_MERCY                = 406,
    TEXT_EMOTE_MUTTER               = 407,
    TEXT_EMOTE_NERVOUS              = 408,
    TEXT_EMOTE_OFFER                = 409,
    TEXT_EMOTE_PET                  = 410,
    TEXT_EMOTE_PINCH                = 411,
    TEXT_EMOTE_PROUD                = 413,
    TEXT_EMOTE_PROMISE              = 414,
    TEXT_EMOTE_PULSE                = 415,
    TEXT_EMOTE_PUNCH                = 416,
    TEXT_EMOTE_POUT                 = 417,
    TEXT_EMOTE_REGRET               = 418,
    TEXT_EMOTE_REVENGE              = 420,
    TEXT_EMOTE_ROLLEYES             = 421,
    TEXT_EMOTE_RUFFLE               = 422,
    TEXT_EMOTE_SAD                  = 423,
    TEXT_EMOTE_SCOFF                = 424,
    TEXT_EMOTE_SCOLD                = 425,
    TEXT_EMOTE_SCOWL                = 426,
    TEXT_EMOTE_SEARCH               = 427,
    TEXT_EMOTE_SHAKEFIST            = 428,
    TEXT_EMOTE_SHIFTY               = 429,
    TEXT_EMOTE_SHUDDER              = 430,
    TEXT_EMOTE_SIGNAL               = 431,
    TEXT_EMOTE_SILENCE              = 432,
    TEXT_EMOTE_SING                 = 433,
    TEXT_EMOTE_SMACK                = 434,
    TEXT_EMOTE_SNEAK                = 435,
    TEXT_EMOTE_SNEEZE               = 436,
    TEXT_EMOTE_SNORT                = 437,
    TEXT_EMOTE_SQUEAL               = 438,
    TEXT_EMOTE_STOPATTACK           = 439,
    TEXT_EMOTE_SUSPICIOUS           = 440,
    TEXT_EMOTE_THINK                = 441,
    TEXT_EMOTE_TRUCE                = 442,
    TEXT_EMOTE_TWIDDLE              = 443,
    TEXT_EMOTE_WARN                 = 444,
    TEXT_EMOTE_SNAP                 = 445,
    TEXT_EMOTE_CHARM                = 446,
    TEXT_EMOTE_COVEREARS            = 447,
    TEXT_EMOTE_CROSSARMS            = 448,
    TEXT_EMOTE_LOOK                 = 449,
    TEXT_EMOTE_OBJECT               = 450,
    TEXT_EMOTE_SWEAT                = 451,
    TEXT_EMOTE_YW                   = 453,
    TEXT_EMOTE_READ                 = 456,
    TEXT_EMOTE_BOOT                 = 506
};

// Emotes.dbc
enum Emote
{
    EMOTE_ONESHOT_NONE                  = 0,
    EMOTE_ONESHOT_TALK                  = 1,
    EMOTE_ONESHOT_BOW                   = 2,
    EMOTE_ONESHOT_WAVE                  = 3,
    EMOTE_ONESHOT_CHEER                 = 4,
    EMOTE_ONESHOT_EXCLAMATION           = 5,
    EMOTE_ONESHOT_QUESTION              = 6,
    EMOTE_ONESHOT_EAT                   = 7,
    EMOTE_STATE_DANCE                   = 10,
    EMOTE_ONESHOT_LAUGH                 = 11,
    EMOTE_STATE_SLEEP                   = 12,
    EMOTE_STATE_SIT                     = 13,
    EMOTE_ONESHOT_RUDE                  = 14,
    EMOTE_ONESHOT_ROAR                  = 15,
    EMOTE_ONESHOT_KNEEL                 = 16,
    EMOTE_ONESHOT_KISS                  = 17,
    EMOTE_ONESHOT_CRY                   = 18,
    EMOTE_ONESHOT_CHICKEN               = 19,
    EMOTE_ONESHOT_BEG                   = 20,
    EMOTE_ONESHOT_APPLAUD               = 21,
    EMOTE_ONESHOT_SHOUT                 = 22,
    EMOTE_ONESHOT_FLEX                  = 23,
    EMOTE_ONESHOT_SHY                   = 24,
    EMOTE_ONESHOT_POINT                 = 25,
    EMOTE_STATE_STAND                   = 26,
    EMOTE_STATE_READY_UNARMED           = 27,
    EMOTE_STATE_WORK_SHEATHED           = 28,
    EMOTE_STATE_POINT                   = 29,
    EMOTE_STATE_NONE                    = 30,
    EMOTE_ONESHOT_WOUND                 = 33,
    EMOTE_ONESHOT_WOUND_CRITICAL        = 34,
    EMOTE_ONESHOT_ATTACK_UNARMED        = 35,
    EMOTE_ONESHOT_ATTACK1H              = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT         = 37,
    EMOTE_ONESHOT_ATTACK2H_LOOSE        = 38,
    EMOTE_ONESHOT_PARRY_UNARMED         = 39,
    EMOTE_ONESHOT_PARRY_SHIELD          = 43,
    EMOTE_ONESHOT_READY_UNARMED         = 44,
    EMOTE_ONESHOT_READY1H               = 45,
    EMOTE_ONESHOT_READY_BOW             = 48,
    EMOTE_ONESHOT_SPELL_PRECAST         = 50,
    EMOTE_ONESHOT_SPELL_CAST            = 51,
    EMOTE_ONESHOT_BATTLE_ROAR           = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H       = 54,
    EMOTE_ONESHOT_KICK                  = 60,
    EMOTE_ONESHOT_ATTACK_THROWN         = 61,
    EMOTE_STATE_STUN                    = 64,
    EMOTE_STATE_DEAD                    = 65,
    EMOTE_ONESHOT_SALUTE                = 66,
    EMOTE_STATE_KNEEL_DONT_WORK         = 68,
    EMOTE_STATE_USE_STANDING            = 69,
    EMOTE_ONESHOT_WAVE_NO_SHEATHE       = 70,
    EMOTE_ONESHOT_CHEER_NO_SHEATHE      = 71,
    EMOTE_ONESHOT_EAT_NO_SHEATHE        = 92,
    EMOTE_STATE_STUN_NO_SHEATHE         = 93,
    EMOTE_ONESHOT_DANCE                 = 94,
    EMOTE_ONESHOT_SALUTE_NO_SHEATH      = 113,
    EMOTE_STATE_USE_STANDING_NO_SHEATHE = 133,
    EMOTE_ONESHOT_LAUGH_NO_SHEATHE      = 153,
    EMOTE_STATE_WORK                    = 173,
    EMOTE_STATE_SPELL_PRECAST           = 193,
    EMOTE_ONESHOT_READY_RIFLE           = 213,
    EMOTE_STATE_READY_RIFLE             = 214,
    EMOTE_STATE_WORK_MINING             = 233,
    EMOTE_STATE_WORK_CHOPWOOD           = 234,
    EMOTE_STATE_APPLAUD                 = 253,
    EMOTE_ONESHOT_LIFTOFF               = 254,
    EMOTE_ONESHOT_YES                   = 273,
    EMOTE_ONESHOT_NO                    = 274,
    EMOTE_ONESHOT_TRAIN                 = 275,
    EMOTE_ONESHOT_LAND                  = 293,
    EMOTE_STATE_AT_EASE                 = 313,
    EMOTE_STATE_READY1H                 = 333,
    EMOTE_STATE_SPELL_KNEEL_START       = 353,
    EMOTE_STATE_SUBMERGED               = 373,
    EMOTE_ONESHOT_SUBMERGE              = 374,
    EMOTE_STATE_READY2H                 = 375,
    EMOTE_STATE_READY_BOW               = 376,
    EMOTE_ONESHOT_MOUNT_SPECIAL         = 377,
    EMOTE_STATE_TALK                    = 378,
    EMOTE_STATE_FISHING                 = 379,
    EMOTE_ONESHOT_FISHING               = 380,
    EMOTE_ONESHOT_LOOT                  = 381,
    EMOTE_STATE_WHIRLWIND               = 382,
    EMOTE_STATE_DROWNED                 = 383,
    EMOTE_STATE_HOLD_BOW                = 384,
    EMOTE_STATE_HOLD_RIFLE              = 385,
    EMOTE_STATE_HOLD_THROWN             = 386,
    EMOTE_ONESHOT_DROWN                 = 387,
    EMOTE_ONESHOT_STOMP                 = 388,
    EMOTE_ONESHOT_ATTACK_OFF            = 389,
    EMOTE_ONESHOT_ATTACK_OFF_PIERCE     = 390,
    EMOTE_STATE_ROAR                    = 391,
    EMOTE_STATE_LAUGH                   = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL      = 393,
    EMOTE_ONESHOT_JUMPLANDRUN           = 394,
    EMOTE_ONESHOT_JUMPEND               = 395,
    EMOTE_ONESHOT_TALK_NO_SHEATHE       = 396,
    EMOTE_ONESHOT_POINT_NO_SHEATHE      = 397,
    EMOTE_STATE_CANNIBALIZE             = 398,
    EMOTE_ONESHOT_JUMPSTART             = 399,
    EMOTE_STATE_DANCESPECIAL            = 400,
    EMOTE_ONESHOT_DANCESPECIAL          = 401,
    EMOTE_ONESHOT_CUSTOM_SPELL_01       = 402,
    EMOTE_ONESHOT_CUSTOM_SPELL_02       = 403,
    EMOTE_ONESHOT_CUSTOM_SPELL_03       = 404,
    EMOTE_ONESHOT_CUSTOM_SPELL_04       = 405,
    EMOTE_ONESHOT_CUSTOM_SPELL_05       = 406,
    EMOTE_ONESHOT_CUSTOM_SPELL_06       = 407,
    EMOTE_ONESHOT_CUSTOM_SPELL_07       = 408,
    EMOTE_ONESHOT_CUSTOM_SPELL_08       = 409,
    EMOTE_ONESHOT_CUSTOM_SPELL_09       = 410,
    EMOTE_ONESHOT_CUSTOM_SPELL_10       = 411,
    EMOTE_STATE_EXCLAIM                 = 412,
    EMOTE_STATE_DANCE_CUSTOM            = 413,
    EMOTE_STATE_SIT_CHAIR_MED           = 415,
    EMOTE_STATE_CUSTOM_SPELL_01         = 416,
    EMOTE_STATE_CUSTOM_SPELL_02         = 417,
    EMOTE_STATE_EAT                     = 418,
    EMOTE_STATE_CUSTOM_SPELL_04         = 419,
    EMOTE_STATE_CUSTOM_SPELL_03         = 420,
    EMOTE_STATE_CUSTOM_SPELL_05         = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD        = 422,
    EMOTE_STATE_EAT_NO_SHEATHE          = 423,
    EMOTE_STATE_MOUNT                   = 424,
    EMOTE_STATE_READY2HL                = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH          = 426,
    EMOTE_STATE_FALL                    = 427,
    EMOTE_STATE_LOOT                    = 428,
    EMOTE_STATE_SUBMERGED_NEW           = 429,
    EMOTE_ONESHOT_COWER                 = 430,
    EMOTE_STATE_COWER                   = 431,
    EMOTE_ONESHOT_USE_STANDING          = 432,
    EMOTE_STATE_STEALTH_STAND           = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL        = 434,
    EMOTE_ONESHOT_ATTACK_BOW            = 435,
    EMOTE_ONESHOT_ATTACK_RIFLE          = 436,
    EMOTE_STATE_SWIM_IDLE               = 437,
    EMOTE_STATE_ATTACK_UNARMED          = 438,
    EMOTE_ONESHOT_SPELL_CAST_W_SOUND    = 439,
    EMOTE_ONESHOT_DODGE                 = 440,
    EMOTE_ONESHOT_PARRY1H               = 441,
    EMOTE_ONESHOT_PARRY2H               = 442,
    EMOTE_ONESHOT_PARRY2HL              = 443,
    EMOTE_STATE_FLYFALL                 = 444,
    EMOTE_ONESHOT_FLYDEATH              = 445,
    EMOTE_STATE_FLY_FALL                = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN   = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP     = 448,
    EMOTE_ONESHOT_EMERGE                = 449,
    EMOTE_ONESHOT_DRAGON_SPIT           = 450,
    EMOTE_STATE_SPECIAL_UNARMED         = 451,
    EMOTE_ONESHOT_FLYGRAB               = 452,
    EMOTE_STATE_FLYGRABCLOSED           = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN         = 454,
    EMOTE_STATE_FLY_SIT_GROUND          = 455,
    EMOTE_STATE_WALK_BACKWARDS          = 456,
    EMOTE_ONESHOT_FLYTALK               = 457,
    EMOTE_ONESHOT_FLYATTACK1H           = 458,
    EMOTE_STATE_CUSTOMSPELL08           = 459,
    EMOTE_ONESHOT_FLY_DRAGON_SPIT       = 460,
    EMOTE_STATE_SIT_CHAIR_LOW           = 461,
    EMOTE_ONESHOT_STUN                  = 462,
    EMOTE_ONESHOT_SPELL_CAST_OMNI       = 463,
    EMOTE_STATE_READY_THROWN            = 465,
    EMOTE_ONESHOT_WORK_CHOPWOOD         = 466,
    EMOTE_ONESHOT_WORK_MINING           = 467,
    EMOTE_STATE_SPELL_CHANNEL_OMNI      = 468,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED  = 469,
    EMOTE_STAND_STATE_NONE              = 470,
    EMOTE_STATE_READYJOUST              = 471,
    EMOTE_STATE_STRANGULATE             = 473,
    EMOTE_STATE_READY_SPELL_OMNI        = 474,
    EMOTE_STATE_HOLD_JOUST              = 475,
    EMOTE_ONESHOT_CRY_JAINA             = 476,
    EMOTE_ONESHOT_SPECIAL_UNARMED       = 477,
    EMOTE_STATE_DANCE_NOSHEATHE         = 478,
    EMOTE_ONESHOT_SNIFF                 = 479,
    EMOTE_ONESHOT_DRAGONSTOMP           = 480,
    EMOTE_ONESHOT_KNOCKDOWN             = 482,
    EMOTE_STATE_READ                    = 483,
    EMOTE_ONESHOT_FLYEMOTETALK          = 485,
    EMOTE_STATE_READ_ALLOWMOVEMENT      = 492,
    EMOTE_STATE_CUSTOM_SPELL_06         = 498,
    EMOTE_STATE_CUSTOM_SPELL_07         = 499,
    EMOTE_STATE_CUSTOM_SPELL_08         = 500,
    EMOTE_STATE_CUSTOM_SPELL_09         = 501,
    EMOTE_STATE_CUSTOM_SPELL_10         = 502,
    EMOTE_STATE_READY1H_ALLOW_MOVEMENT  = 505,
    EMOTE_STATE_READY2H_ALLOW_MOVEMENT  = 506,
    EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED = 507,
    EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED = 508,
    EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED = 509,
    EMOTE_STATE_MONKOFFENSE_READYUNARMED = 510,
    EMOTE_ONESHOT_PALMSTRIKE            = 511,
    EMOTE_STATE_CRANE                   = 512,
    EMOTE_ONESHOT_OPEN                  = 517,
    EMOTE_STATE_READ_CHRISTMAS          = 518,
    EMOTE_ONESHOT_FLYATTACK2HL          = 526,
    EMOTE_ONESHOT_FLYATTACKTHROWN       = 527,
    EMOTE_STATE_FLYREADYSPELLDIRECTED   = 528,
    EMOTE_STATE_FLY_READY_1H            = 531,
    EMOTE_STATE_MEDITATE                = 533,
    EMOTE_STATE_FLY_READY_2HL           = 534,
    EMOTE_ONESHOT_TOGROUND              = 535,
    EMOTE_ONESHOT_TOFLY                 = 536,
    EMOTE_STATE_ATTACKTHROWN            = 537,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED_NOSOUND = 538,
    EMOTE_ONESHOT_WORK                  = 539,
    EMOTE_STATE_READYUNARMED_NOSOUND    = 540,
    EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMEDOFF = 543,
    EMOTE_RECLINED_MOUNT_PASSENGER      = 546,
    EMOTE_ONESHOT_QUESTION2             = 547,
    EMOTE_ONESHOT_SPELL_CHANNEL_DIRECTED_NOSOUND = 549,
    EMOTE_STATE_KNEEL                   = 550,
    EMOTE_ONESHOT_FLYATTACKUNARMED      = 551,
    EMOTE_ONESHOT_FLYCOMBATWOUND        = 552,
    EMOTE_ONESHOT_MOUNTSELFSPECIAL      = 553,
    EMOTE_ONESHOT_ATTACKUNARMED_NOSOUND = 554,
    EMOTE_STATE_WOUNDCRITICAL_DONT_WORK = 555,
    EMOTE_ONESHOT_ATTACK1H_NOSOUND      = 556,
    EMOTE_STATE_MOUNT_SELF_IDLE         = 557,
    EMOTE_ONESHOT_WALK                  = 558,
    EMOTE_STATE_OPENED                  = 559,
    EMOTE_ONESHOT_YELL_DONOTUSE         = 560,
    EMOTE_ONESHOT_BREATHOFFIRE          = 565,
    EMOTE_STATE_ATTACK1H                = 567,
    EMOTE_STATE_USESTANDIN              = 572,
    EMOTE_ONESHOT_LAUGH_NOSOUND         = 574
};

// AnimationData.dbc
enum Anim
{
    ANIM_STAND                             = 0,
    ANIM_DEATH                             = 1,
    ANIM_SPELL                             = 2,
    ANIM_STOP                              = 3,
    ANIM_WALK                              = 4,
    ANIM_RUN                               = 5,
    ANIM_DEAD                              = 6,
    ANIM_RISE                              = 7,
    ANIM_STAND_WOUND                       = 8,
    ANIM_COMBAT_WOUND                      = 9,
    ANIM_COMBAT_CRITICAL                   = 10,
    ANIM_SHUFFLE_LEFT                      = 11,
    ANIM_SHUFFLE_RIGHT                     = 12,
    ANIM_WALK_BACKWARDS                    = 13,
    ANIM_STUN                              = 14,
    ANIM_HANDS_CLOSED                      = 15,
    ANIM_ATTACK_UNARMED                    = 16,
    ANIM_ATTACK1H                          = 17,
    ANIM_ATTACK2H                          = 18,
    ANIM_ATTACK2HL                         = 19,
    ANIM_PARRY_UNARMED                     = 20,
    ANIM_PARRY1H                           = 21,
    ANIM_PARRY2H                           = 22,
    ANIM_PARRY2HL                          = 23,
    ANIM_SHIELD_BLOCK                      = 24,
    ANIM_READY_UNARMED                     = 25,
    ANIM_READY1H                           = 26,
    ANIM_READY2H                           = 27,
    ANIM_READY2HL                          = 28,
    ANIM_READY_BOW                         = 29,
    ANIM_DODGE                             = 30,
    ANIM_SPELL_PRECAST                     = 31,
    ANIM_SPELL_CAST                        = 32,
    ANIM_SPELL_CAST_AREA                   = 33,
    ANIM_NPC_WELCOME                       = 34,
    ANIM_NPC_GOODBYE                       = 35,
    ANIM_BLOCK                             = 36,
    ANIM_JUMP_START                        = 37,
    ANIM_JUMP                              = 38,
    ANIM_JUMP_END                          = 39,
    ANIM_FALL                              = 40,
    ANIM_SWIM_IDLE                         = 41,
    ANIM_SWIM                              = 42,
    ANIM_SWIM_LEFT                         = 43,
    ANIM_SWIM_RIGHT                        = 44,
    ANIM_SWIM_BACKWARDS                    = 45,
    ANIM_ATTACK_BOW                        = 46,
    ANIM_FIRE_BOW                          = 47,
    ANIM_READY_RIFLE                       = 48,
    ANIM_ATTACK_RIFLE                      = 49,
    ANIM_LOOT                              = 50,
    ANIM_READY_SPELL_DIRECTED              = 51,
    ANIM_READY_SPELL_OMNI                  = 52,
    ANIM_SPELL_CAST_DIRECTED               = 53,
    ANIM_SPELL_CAST_OMNI                   = 54,
    ANIM_BATTLE_ROAR                       = 55,
    ANIM_READY_ABILITY                     = 56,
    ANIM_SPECIAL1H                         = 57,
    ANIM_SPECIAL2H                         = 58,
    ANIM_SHIELD_BASH                       = 59,
    ANIM_EMOTE_TALK                        = 60,
    ANIM_EMOTE_EAT                         = 61,
    ANIM_EMOTE_WORK                        = 62,
    ANIM_EMOTE_USE_STANDING                = 63,
    ANIM_EMOTE_TALK_EXCLAMATION            = 64,
    ANIM_EMOTE_TALK_QUESTION               = 65,
    ANIM_EMOTE_BOW                         = 66,
    ANIM_EMOTE_WAVE                        = 67,
    ANIM_EMOTE_CHEER                       = 68,
    ANIM_EMOTE_DANCE                       = 69,
    ANIM_EMOTE_LAUGH                       = 70,
    ANIM_EMOTE_SLEEP                       = 71,
    ANIM_EMOTE_SIT_GROUND                  = 72,
    ANIM_EMOTE_RUDE                        = 73,
    ANIM_EMOTE_ROAR                        = 74,
    ANIM_EMOTE_KNEEL                       = 75,
    ANIM_EMOTE_KISS                        = 76,
    ANIM_EMOTE_CRY                         = 77,
    ANIM_EMOTE_CHICKEN                     = 78,
    ANIM_EMOTE_BEG                         = 79,
    ANIM_EMOTE_APPLAUD                     = 80,
    ANIM_EMOTE_SHOUT                       = 81,
    ANIM_EMOTE_FLEX                        = 82,
    ANIM_EMOTE_SHY                         = 83,
    ANIM_EMOTE_POINT                       = 84,
    ANIM_ATTACK1H_PIERCE                   = 85,
    ANIM_ATTACK2H_LOOSE_PIERCE             = 86,
    ANIM_ATTACK_OFF                        = 87,
    ANIM_ATTACK_OFF_PIERCE                 = 88,
    ANIM_SHEATHE                           = 89,
    ANIM_HIP_SHEATHE                       = 90,
    ANIM_MOUNT                             = 91,
    ANIM_RUN_RIGHT                         = 92,
    ANIM_RUN_LEFT                          = 93,
    ANIM_MOUNT_SPECIAL                     = 94,
    ANIM_KICK                              = 95,
    ANIM_SIT_GROUND_DOWN                   = 96,
    ANIM_SIT_GROUND                        = 97,
    ANIM_SIT_GROUND_UP                     = 98,
    ANIM_SLEEP_DOWN                        = 99,
    ANIM_SLEEP                             = 100,
    ANIM_SLEEP_UP                          = 101,
    ANIM_SIT_CHAIR_LOW                     = 102,
    ANIM_SIT_CHAIR_MED                     = 103,
    ANIM_SIT_CHAIR_HIGH                    = 104,
    ANIM_LOAD_BOW                          = 105,
    ANIM_LOAD_RIFLE                        = 106,
    ANIM_ATTACK_THROWN                     = 107,
    ANIM_READY_THROWN                      = 108,
    ANIM_HOLD_BOW                          = 109,
    ANIM_HOLD_RIFLE                        = 110,
    ANIM_HOLD_THROWN                       = 111,
    ANIM_LOAD_THROWN                       = 112,
    ANIM_EMOTE_SALUTE                      = 113,
    ANIM_KNEEL_START                       = 114,
    ANIM_KNEEL_LOOP                        = 115,
    ANIM_KNEEL_END                         = 116,
    ANIM_ATTACK_UNARMED_OFF                = 117,
    ANIM_SPECIAL_UNARMED                   = 118,
    ANIM_STEALTH_WALK                      = 119,
    ANIM_STEALTH_STAND                     = 120,
    ANIM_KNOCKDOWN                         = 121,
    ANIM_EATING_LOOP                       = 122,
    ANIM_USE_STANDING_LOOP                 = 123,
    ANIM_CHANNEL_CAST_DIRECTED             = 124,
    ANIM_CHANNEL_CAST_OMNI                 = 125,
    ANIM_WHIRLWIND                         = 126,
    ANIM_BIRTH                             = 127,
    ANIM_USE_STANDING_START                = 128,
    ANIM_USE_STANDING_END                  = 129,
    ANIM_CREATURE_SPECIAL                  = 130,
    ANIM_DROWN                             = 131,
    ANIM_DROWNED                           = 132,
    ANIM_FISHING_CAST                      = 133,
    ANIM_FISHING_LOOP                      = 134,
    ANIM_FLY                               = 135,
    ANIM_EMOTE_WORK_NO_SHEATHE             = 136,
    ANIM_EMOTE_STUN_NO_SHEATHE             = 137,
    ANIM_EMOTE_USE_STANDING_NO_SHEATHE     = 138,
    ANIM_SPELL_SLEEP_DOWN                  = 139,
    ANIM_SPELL_KNEEL_START                 = 140,
    ANIM_SPELL_KNEEL_LOOP                  = 141,
    ANIM_SPELL_KNEEL_END                   = 142,
    ANIM_SPRINT                            = 143,
    ANIM_IN_FIGHT                          = 144,
    ANIM_SPAWN                             = 145,
    ANIM_CLOSE                             = 146,
    ANIM_CLOSED                            = 147,
    ANIM_OPEN                              = 148,
    ANIM_OPENED                            = 149,
    ANIM_DESTROY                           = 150,
    ANIM_DESTROYED                         = 151,
    ANIM_REBUILD                           = 152,
    ANIM_CUSTOM_0                          = 153,
    ANIM_CUSTOM_1                          = 154,
    ANIM_CUSTOM_2                          = 155,
    ANIM_CUSTOM_3                          = 156,
    ANIM_DESPAWN                           = 157,
    ANIM_HOLD                              = 158,
    ANIM_DECAY                             = 159,
    ANIM_BOW_PULL                          = 160,
    ANIM_BOW_RELEASE                       = 161,
    ANIM_SHIP_START                        = 162,
    ANIM_SHIP_MOVING                       = 163,
    ANIM_SHIP_STOP                         = 164,
    ANIM_GROUP_ARROW                       = 165,
    ANIM_ARROW                             = 166,
    ANIM_CORPSE_ARROW                      = 167,
    ANIM_GUIDE_ARROW                       = 168,
    ANIM_SWAY                              = 169,
    ANIM_DRUID_CAT_POUNCE                  = 170,
    ANIM_DRUID_CAT_RIP                     = 171,
    ANIM_DRUID_CAT_RAKE                    = 172,
    ANIM_DRUID_CAT_RAVAGE                  = 173,
    ANIM_DRUID_CAT_CLAW                    = 174,
    ANIM_DRUID_CAT_COWER                   = 175,
    ANIM_DRUID_BEAR_SWIPE                  = 176,
    ANIM_DRUID_BEAR_BITE                   = 177,
    ANIM_DRUID_BEAR_MAUL                   = 178,
    ANIM_DRUID_BEAR_BASH                   = 179,
    ANIM_DRAGON_TAIL                       = 180,
    ANIM_DRAGON_STOMP                      = 181,
    ANIM_DRAGON_SPIT                       = 182,
    ANIM_DRAGON_SPIT_HOVER                 = 183,
    ANIM_DRAGON_SPIT_FLY                   = 184,
    ANIM_EMOTE_YES                         = 185,
    ANIM_EMOTE_NO                          = 186,
    ANIM_JUMP_LAND_RUN                     = 187,
    ANIM_LOOT_HOLD                         = 188,
    ANIM_LOOT_UP                           = 189,
    ANIM_STAND_HIGH                        = 190,
    ANIM_IMPACT                            = 191,
    ANIM_LIFTOFF                           = 192,
    ANIM_HOVER                             = 193,
    ANIM_SUCCUBUS_ENTICE                   = 194,
    ANIM_EMOTE_TRAIN                       = 195,
    ANIM_EMOTE_DEAD                        = 196,
    ANIM_EMOTE_DANCE_ONCE                  = 197,
    ANIM_DEFLECT                           = 198,
    ANIM_EMOTE_EAT_NO_SHEATHE              = 199,
    ANIM_LAND                              = 200,
    ANIM_SUBMERGE                          = 201,
    ANIM_SUBMERGED                         = 202,
    ANIM_CANNIBALIZE                       = 203,
    ANIM_ARROW_BIRTH                       = 204,
    ANIM_GROUP_ARROW_BIRTH                 = 205,
    ANIM_CORPSE_ARROW_BIRTH                = 206,
    ANIM_GUIDE_ARROW_BIRTH                 = 207,
    ANIM_EMOTE_TALK_NO_SHEATHE             = 208,
    ANIM_EMOTE_POINT_NO_SHEATHE            = 209,
    ANIM_EMOTE_SALUTE_NO_SHEATHE           = 210,
    ANIM_EMOTE_DANCE_SPECIAL               = 211,
    ANIM_MUTILATE                          = 212,
    ANIM_CUSTOM_SPELL_01                   = 213,
    ANIM_CUSTOM_SPELL_02                   = 214,
    ANIM_CUSTOM_SPELL_03                   = 215,
    ANIM_CUSTOM_SPELL_04                   = 216,
    ANIM_CUSTOM_SPELL_05                   = 217,
    ANIM_CUSTOM_SPELL_06                   = 218,
    ANIM_CUSTOM_SPELL_07                   = 219,
    ANIM_CUSTOM_SPELL_08                   = 220,
    ANIM_CUSTOM_SPELL_09                   = 221,
    ANIM_CUSTOM_SPELL_10                   = 222,
    ANIM_STEALTH_RUN                       = 223,
    ANIM_EMERGE                            = 224,
    ANIM_COWER                             = 225,
    ANIM_GRAB                              = 226,
    ANIM_GRAB_CLOSED                       = 227,
    ANIM_GRAB_THROWN                       = 228,
    ANIM_FLY_STAND                         = 229,
    ANIM_FLY_DEATH                         = 230,
    ANIM_FLY_SPELL                         = 231,
    ANIM_FLY_STOP                          = 232,
    ANIM_FLY_WALK                          = 233,
    ANIM_FLY_RUN                           = 234,
    ANIM_FLY_DEAD                          = 235,
    ANIM_FLY_RISE                          = 236,
    ANIM_FLY_STAND_WOUND                   = 237,
    ANIM_FLY_COMBAT_WOUND                  = 238,
    ANIM_FLY_COMBAT_CRITICAL               = 239,
    ANIM_FLY_SHUFFLE_LEFT                  = 240,
    ANIM_FLY_SHUFFLE_RIGHT                 = 241,
    ANIM_FLY_WALK_BACKWARDS                = 242,
    ANIM_FLY_STUN                          = 243,
    ANIM_FLY_HANDS_CLOSED                  = 244,
    ANIM_FLY_ATTACK_UNARMED                = 245,
    ANIM_FLY_ATTACK1H                      = 246,
    ANIM_FLY_ATTACK2H                      = 247,
    ANIM_FLY_ATTACK2HL                     = 248,
    ANIM_FLY_PARRY_UNARMED                 = 249,
    ANIM_FLY_PARRY1H                       = 250,
    ANIM_FLY_PARRY2H                       = 251,
    ANIM_FLY_PARRY2HL                      = 252,
    ANIM_FLY_SHIELD_BLOCK                  = 253,
    ANIM_FLY_READY_UNARMED                 = 254,
    ANIM_FLY_READY1H                       = 255,
    ANIM_FLY_READY2H                       = 256,
    ANIM_FLY_READY2HL                      = 257,
    ANIM_FLY_READY_BOW                     = 258,
    ANIM_FLY_DODGE                         = 259,
    ANIM_FLY_SPELL_PRECAST                 = 260,
    ANIM_FLY_SPELL_CAST                    = 261,
    ANIM_FLY_SPELL_CAST_AREA               = 262,
    ANIM_FLY_NPC_WELCOME                   = 263,
    ANIM_FLY_NPC_GOODBYE                   = 264,
    ANIM_FLY_BLOCK                         = 265,
    ANIM_FLY_JUMP_START                    = 266,
    ANIM_FLY_JUMP                          = 267,
    ANIM_FLY_JUMP_END                      = 268,
    ANIM_FLY_FALL                          = 269,
    ANIM_FLY_SWIM_IDLE                     = 270,
    ANIM_FLY_SWIM                          = 271,
    ANIM_FLY_SWIM_LEFT                     = 272,
    ANIM_FLY_SWIM_RIGHT                    = 273,
    ANIM_FLY_SWIM_BACKWARDS                = 274,
    ANIM_FLY_ATTACK_BOW                    = 275,
    ANIM_FLY_FIRE_BOW                      = 276,
    ANIM_FLY_READY_RIFLE                   = 277,
    ANIM_FLY_ATTACK_RIFLE                  = 278,
    ANIM_FLY_LOOT                          = 279,
    ANIM_FLY_READY_SPELL_DIRECTED          = 280,
    ANIM_FLY_READY_SPELL_OMNI              = 281,
    ANIM_FLY_SPELL_CAST_DIRECTED           = 282,
    ANIM_FLY_SPELL_CAST_OMNI               = 283,
    ANIM_FLY_SPELL_BATTLE_ROAR             = 284,
    ANIM_FLY_READY_ABILITY                 = 285,
    ANIM_FLY_SPECIAL1H                     = 286,
    ANIM_FLY_SPECIAL2H                     = 287,
    ANIM_FLY_SHIELD_BASH                   = 288,
    ANIM_FLY_EMOTE_TALK                    = 289,
    ANIM_FLY_EMOTE_EAT                     = 290,
    ANIM_FLY_EMOTE_WORK                    = 291,
    ANIM_FLY_USE_STANDING                  = 292,
    ANIM_FLY_EMOTE_TALK_EXCLAMATION        = 293,
    ANIM_FLY_EMOTE_TALK_QUESTION           = 294,
    ANIM_FLY_EMOTE_BOW                     = 295,
    ANIM_FLY_EMOTE_WAVE                    = 296,
    ANIM_FLY_EMOTE_CHEER                   = 297,
    ANIM_FLY_EMOTE_DANCE                   = 298,
    ANIM_FLY_EMOTE_LAUGH                   = 299,
    ANIM_FLY_EMOTE_SLEEP                   = 300,
    ANIM_FLY_EMOTE_SIT_GROUND              = 301,
    ANIM_FLY_EMOTE_RUDE                    = 302,
    ANIM_FLY_EMOTE_ROAR                    = 303,
    ANIM_FLY_EMOTE_KNEEL                   = 304,
    ANIM_FLY_EMOTE_KISS                    = 305,
    ANIM_FLY_EMOTE_CRY                     = 306,
    ANIM_FLY_EMOTE_CHICKEN                 = 307,
    ANIM_FLY_EMOTE_BEG                     = 308,
    ANIM_FLY_EMOTE_APPLAUD                 = 309,
    ANIM_FLY_EMOTE_SHOUT                   = 310,
    ANIM_FLY_EMOTE_FLEX                    = 311,
    ANIM_FLY_EMOTE_SHY                     = 312,
    ANIM_FLY_EMOTE_POINT                   = 313,
    ANIM_FLY_ATTACK1H_PIERCE               = 314,
    ANIM_FLY_ATTACK2H_LOOSE_PIERCE         = 315,
    ANIM_FLY_ATTACK_OFF                    = 316,
    ANIM_FLY_ATTACK_OFF_PIERCE             = 317,
    ANIM_FLY_SHEATH                        = 318,
    ANIM_FLY_HIP_SHEATH                    = 319,
    ANIM_FLY_MOUNT                         = 320,
    ANIM_FLY_RUN_RIGHT                     = 321,
    ANIM_FLY_RUN_LEFT                      = 322,
    ANIM_FLY_MOUNT_SPECIAL                 = 323,
    ANIM_FLY_KICK                          = 324,
    ANIM_FLY_SIT_GROUND_DOWN               = 325,
    ANIM_FLY_SIT_GROUND                    = 326,
    ANIM_FLY_SIT_GROUND_UP                 = 327,
    ANIM_FLY_SLEEP_DOWN                    = 328,
    ANIM_FLY_SLEEP                         = 329,
    ANIM_FLY_SLEEP_UP                      = 330,
    ANIM_FLY_SIT_CHAIR_LOW                 = 331,
    ANIM_FLY_SIT_CHAIR_MED                 = 332,
    ANIM_FLY_SIT_CHAIR_HIGH                = 333,
    ANIM_FLY_LOAD_BOW                      = 334,
    ANIM_FLY_LOAD_RIFLE                    = 335,
    ANIM_FLY_ATTACK_THROWN                 = 336,
    ANIM_FLY_READY_THROWN                  = 337,
    ANIM_FLY_HOLD_BOW                      = 338,
    ANIM_FLY_HOLD_RIFLE                    = 339,
    ANIM_FLY_HOLD_THROWN                   = 340,
    ANIM_FLY_LOAD_THROWN                   = 341,
    ANIM_FLY_EMOTE_SALUTE                  = 342,
    ANIM_FLY_KNEEL_START                   = 343,
    ANIM_FLY_KNEEL_LOOP                    = 344,
    ANIM_FLY_KNEEL_END                     = 345,
    ANIM_FLY_ATTACK_UNARMED_OFF            = 346,
    ANIM_FLY_SPECIAL_UNARMED               = 347,
    ANIM_FLY_STEALTH_WALK                  = 348,
    ANIM_FLY_STEALTH_STAND                 = 349,
    ANIM_FLY_KNOCKDOWN                     = 350,
    ANIM_FLY_EATING_LOOP                   = 351,
    ANIM_FLY_USE_STANDING_LOOP             = 352,
    ANIM_FLY_CHANNEL_CAST_DIRECTED         = 353,
    ANIM_FLY_CHANNEL_CAST_OMNI             = 354,
    ANIM_FLY_WHIRLWIND                     = 355,
    ANIM_FLY_BIRTH                         = 356,
    ANIM_FLY_USE_STANDING_START            = 357,
    ANIM_FLY_USE_STANDING_END              = 358,
    ANIM_FLY_CREATURE_SPECIAL              = 359,
    ANIM_FLY_DROWN                         = 360,
    ANIM_FLY_DROWNED                       = 361,
    ANIM_FLY_FISHING_CAST                  = 362,
    ANIM_FLY_FISHING_LOOP                  = 363,
    ANIM_FLY_FLY                           = 364,
    ANIM_FLY_EMOTE_WORK_NO_SHEATHE         = 365,
    ANIM_FLY_EMOTE_STUN_NO_SHEATHE         = 366,
    ANIM_FLY_EMOTE_USE_STANDING_NO_SHEATHE = 367,
    ANIM_FLY_SPELL_SLEEP_DOWN              = 368,
    ANIM_FLY_SPELL_KNEEL_START             = 369,
    ANIM_FLY_SPELL_KNEEL_LOOP              = 370,
    ANIM_FLY_SPELL_KNEEL_END               = 371,
    ANIM_FLY_SPRINT                        = 372,
    ANIM_FLY_IN_FLIGHT                     = 373,
    ANIM_FLY_SPAWN                         = 374,
    ANIM_FLY_CLOSE                         = 375,
    ANIM_FLY_CLOSED                        = 376,
    ANIM_FLY_OPEN                          = 377,
    ANIM_FLY_OPENED                        = 378,
    ANIM_FLY_DESTROY                       = 379,
    ANIM_FLY_DESTROYED                     = 380,
    ANIM_FLY_REBUILD                       = 381,
    ANIM_FLY_CUSTOM_0                      = 382,
    ANIM_FLY_CUSTOM_1                      = 383,
    ANIM_FLY_CUSTOM_2                      = 384,
    ANIM_FLY_CUSTOM_3                      = 385,
    ANIM_FLY_DESPAWN                       = 386,
    ANIM_FLY_HOLD                          = 387,
    ANIM_FLY_DECAY                         = 388,
    ANIM_FLY_BOW_PULL                      = 389,
    ANIM_FLY_BOW_RELEASE                   = 390,
    ANIM_FLY_SHIP_START                    = 391,
    ANIM_FLY_SHIP_MOVING                   = 392,
    ANIM_FLY_SHIP_STOP                     = 393,
    ANIM_FLY_GROUP_ARROW                   = 394,
    ANIM_FLY_ARROW                         = 395,
    ANIM_FLY_CORPSE_ARROW                  = 396,
    ANIM_FLY_GUIDE_ARROW                   = 397,
    ANIM_FLY_SWAY                          = 398,
    ANIM_FLY_DRUID_CAT_POUNCE              = 399,
    ANIM_FLY_DRUID_CAT_RIP                 = 400,
    ANIM_FLY_DRUID_CAT_RAKE                = 401,
    ANIM_FLY_DRUID_CAT_RAVAGE              = 402,
    ANIM_FLY_DRUID_CAT_CLAW                = 403,
    ANIM_FLY_DRUID_CAT_COWER               = 404,
    ANIM_FLY_DRUID_BEAR_SWIPE              = 405,
    ANIM_FLY_DRUID_BEAR_BITE               = 406,
    ANIM_FLY_DRUID_BEAR_MAUL               = 407,
    ANIM_FLY_DRUID_BEAR_BASH               = 408,
    ANIM_FLY_DRAGON_TAIL                   = 409,
    ANIM_FLY_DRAGON_STOMP                  = 410,
    ANIM_FLY_DRAGON_SPIT                   = 411,
    ANIM_FLY_DRAGON_SPIT_HOVER             = 412,
    ANIM_FLY_DRAGON_SPIT_FLY               = 413,
    ANIM_FLY_EMOTE_YES                     = 414,
    ANIM_FLY_EMOTE_NO                      = 415,
    ANIM_FLY_JUMP_LAND_RUN                 = 416,
    ANIM_FLY_LOOT_HOLD                     = 417,
    ANIM_FLY_LOOT_UP                       = 418,
    ANIM_FLY_STAND_HIGH                    = 419,
    ANIM_FLY_IMPACT                        = 420,
    ANIM_FLY_LIFTOFF                       = 421,
    ANIM_FLY_HOVER                         = 422,
    ANIM_FLY_SUCCUBUS_ENTICE               = 423,
    ANIM_FLY_EMOTE_TRAIN                   = 424,
    ANIM_FLY_EMOTE_DEAD                    = 425,
    ANIM_FLY_EMOTE_DANCE_ONCE              = 426,
    ANIM_FLY_DEFLECT                       = 427,
    ANIM_FLY_EMOTE_EAT_NO_SHEATHE          = 428,
    ANIM_FLY_LAND                          = 429,
    ANIM_FLY_SUBMERGE                      = 430,
    ANIM_FLY_SUBMERGED                     = 431,
    ANIM_FLY_CANNIBALIZE                   = 432,
    ANIM_FLY_ARROW_BIRTH                   = 433,
    ANIM_FLY_GROUP_ARROW_BIRTH             = 434,
    ANIM_FLY_CORPSE_ARROW_BIRTH            = 435,
    ANIM_FLY_GUIDE_ARROW_BIRTH             = 436,
    ANIM_FLY_EMOTE_TALK_NO_SHEATHE         = 437,
    ANIM_FLY_EMOTE_POINT_NO_SHEATHE        = 438,
    ANIM_FLY_EMOTE_SALUTE_NO_SHEATHE       = 439,
    ANIM_FLY_EMOTE_DANCE_SPECIAL           = 440,
    ANIM_FLY_MUTILATE                      = 441,
    ANIM_FLY_CUSTOM_SPELL_01               = 442,
    ANIM_FLY_CUSTOM_SPELL_02               = 443,
    ANIM_FLY_CUSTOM_SPELL_03               = 444,
    ANIM_FLY_CUSTOM_SPELL_04               = 445,
    ANIM_FLY_CUSTOM_SPELL_05               = 446,
    ANIM_FLY_CUSTOM_SPELL_06               = 447,
    ANIM_FLY_CUSTOM_SPELL_07               = 448,
    ANIM_FLY_CUSTOM_SPELL_08               = 449,
    ANIM_FLY_CUSTOM_SPELL_09               = 450,
    ANIM_FLY_CUSTOM_SPELL_10               = 451,
    ANIM_FLY_STEALTH_RUN                   = 452,
    ANIM_FLY_EMERGE                        = 453,
    ANIM_FLY_COWER                         = 454,
    ANIM_FLY_GRAB                          = 455,
    ANIM_FLY_GRAB_CLOSED                   = 456,
    ANIM_FLY_GRAB_THROWN                   = 457,
    ANIM_TO_FLY                            = 458,
    ANIM_TO_HOVER                          = 459,
    ANIM_TO_GROUND                         = 460,
    ANIM_FLY_TO_FLY                        = 461,
    ANIM_FLY_TO_HOVER                      = 462,
    ANIM_FLY_TO_GROUND                     = 463,
    ANIM_SETTLE                            = 464,
    ANIM_FLY_SETTLE                        = 465,
    ANIM_DEATH_START                       = 466,
    ANIM_DEATH_LOOP                        = 467,
    ANIM_DEATH_END                         = 468,
    ANIM_FLY_DEATH_START                   = 469,
    ANIM_FLY_DEATH_LOOP                    = 470,
    ANIM_FLY_DEATH_END                     = 471,
    ANIM_DEATH_END_HOLD                    = 472,
    ANIM_FLY_DEATH_END_HOLD                = 473,
    ANIM_STRANGULATE                       = 474,
    ANIM_FLY_STRANGULATE                   = 475,
    ANIM_READY_JOUST                       = 476,
    ANIM_LOAD_JOUST                        = 477,
    ANIM_HOLD_JOUST                        = 478,
    ANIM_FLY_READY_JOUST                   = 479,
    ANIM_FLY_LOAD_JOUST                    = 480,
    ANIM_FLY_HOLD_JOUST                    = 481,
    ANIM_ATTACK_JOUST                      = 482,
    ANIM_FLY_ATTACK_JOUST                  = 483,
    ANIM_RECLINED_MOUNT                    = 484,
    ANIM_FLY_RECLINED_MOUNT                = 485,
    ANIM_TO_ALTERED                        = 486,
    ANIM_FROM_ALTERED                      = 487,
    ANIM_FLY_TO_ALTERED                    = 488,
    ANIM_FLY_FROM_ALTERED                  = 489,
    ANIM_IN_STOCKS                         = 490,
    ANIM_FLY_IN_STOCKS                     = 491,
    ANIM_VEHICLE_GRAB                      = 492,
    ANIM_VEHICLE_THROW                     = 493,
    ANIM_FLY_VEHICLE_GRAB                  = 494,
    ANIM_FLY_VEHICLE_THROW                 = 495,
    ANIM_TO_ALTERED_POST_SWAP              = 496,
    ANIM_FROM_ALTERED_POST_SWAP            = 497,
    ANIM_FLY_TO_ALTERED_POST_SWAP          = 498,
    ANIM_FLY_FROM_ALTERED_POST_SWAP        = 499,
    ANIM_RECLINED_MOUNT_PASSENGER          = 500,
    ANIM_FLY_RECLINED_MOUNT_PASSENGER      = 501,
    ANIM_CARRY2H                           = 502,
    ANIM_CARRIED2H                         = 503,
    ANIM_FLY_CARRY2H                       = 504,
    ANIM_FLY_CARRIED2H                     = 505,
    ANIM_EMOTE_SNIFF                       = 506,
    ANIM_EMOTE_FLY_SNIFF                   = 507,
    ANIM_ATTACK_FIST1H                     = 508,
    ANIM_FLY_ATTACK_FIST1H                 = 509,
    ANIM_ATTACK_FIST_1H_OFF                = 510,
    ANIM_FLY_ATTACK_FIST_1H_OFF            = 511,
    ANIM_PARRY_FIST1H                      = 512,
    ANIM_FLY_PARRY_FIST1H                  = 513,
    ANIM_READY_FIST1H                      = 514,
    ANIM_FLY_READY_FIST1H                  = 515,
    ANIM_SPECIAL_FIST1H                    = 516,
    ANIM_FLY_SPECIAL_FIST1H                = 517,
    ANIM_EMOTE_READ_START                  = 518,
    ANIM_FLY_EMOTE_READ_START              = 519,
    ANIM_EMOTE_READ_LOOP                   = 520,
    ANIM_FLY_EMOTE_READ_LOOP               = 521,
    ANIM_EMOTE_READ_END                    = 522,
    ANIM_FLY_EMOTE_READ_END                = 523,
    ANIM_SWIM_RUN                          = 524,
    ANIM_FLY_SWIM_RUN                      = 525,
    ANIM_SWIM_WALK                         = 526,
    ANIM_FLY_SWIM_WALK                     = 527,
    ANIM_SWIM_WALK_BACKWARDS               = 528,
    ANIM_FLY_SWIM_WALK_BACKWARDS           = 529,
    ANIM_SWIM_SPRINT                       = 530,
    ANIM_FLY_SWIM_SPRINT                   = 531,
    ANIM_MOUNT_SWIM_IDLE                   = 532,
    ANIM_FLY_MOUNT_SWIM_IDLE               = 533,
    ANIM_MOUNT_SWIM_BACKWARDS              = 534,
    ANIM_FLY_MOUNT_SWIM_BACKWARDS          = 535,
    ANIM_MOUNT_SWIM_LEFT                   = 536,
    ANIM_FLY_MOUNT_SWIM_LEFT               = 537,
    ANIM_MOUNT_SWIM_RIGHT                  = 538,
    ANIM_FLY_MOUNT_SWIM_RIGHT              = 539,
    ANIM_MOUNT_SWIM_RUN                    = 540,
    ANIM_FLY_MOUNT_SWIM_RUN                = 541,
    ANIM_MOUNT_SWIM_SPRINT                 = 542,
    ANIM_FLY_MOUNT_SWIM_SPRINT             = 543,
    ANIM_MOUNT_SWIM_WALK                   = 544,
    ANIM_FLY_MOUNT_SWIM_WALK               = 545,
    ANIM_MOUNT_SWIM_WALK_BACKWARDS         = 546,
    ANIM_FLY_MOUNT_SWIM_WALK_BACKWARDS     = 547,
    ANIM_MOUNT_FLIGHT_IDLE                 = 548,
    ANIM_FLY_MOUNT_FLIGHT_IDLE             = 549,
    ANIM_MOUNT_FLIGHT_BACKWARDS            = 550,
    ANIM_FLY_MOUNT_FLIGHT_BACKWARDS        = 551,
    ANIM_MOUNT_FLIGHT_LEFT                 = 552,
    ANIM_FLY_MOUNT_FLIGHT_LEFT             = 553,
    ANIM_MOUNT_FLIGHT_RIGHT                = 554,
    ANIM_FLY_MOUNT_FLIGHT_RIGHT            = 555,
    ANIM_MOUNT_FLIGHT_RUN                  = 556,
    ANIM_FLY_MOUNT_FLIGHT_RUN              = 557,
    ANIM_MOUNT_FLIGHT_SPRINT               = 558,
    ANIM_FLY_MOUNT_FLIGHT_SPRINT           = 559,
    ANIM_MOUNT_FLIGHT_WALK                 = 560,
    ANIM_FLY_MOUNT_FLIGHT_WALK             = 561,
    ANIM_MOUNT_FLIGHT_WALK_BACKWARDS       = 562,
    ANIM_FLY_MOUNT_FLIGHT_WALK_BACKWARDS   = 563,
    ANIM_MOUNT_FLIGHT_START                = 564,
    ANIM_FLY_MOUNT_FLIGHT_START            = 565,
    ANIM_MOUNT_SWIM_START                  = 566,
    ANIM_FLY_MOUNT_SWIM_START              = 567,
    ANIM_MOUNT_SWIM_LAND                   = 568,
    ANIM_FLY_MOUNT_SWIM_LAND               = 569,
    ANIM_MOUNT_SWIM_LAND_RUN               = 570,
    ANIM_FLY_MOUNT_SWIM_LAND_RUN           = 571,
    ANIM_MOUNT_FLIGHT_LAND                 = 572,
    ANIM_FLY_MOUNT_FLIGHT_LAND             = 573,
    ANIM_MOUNT_FLIGHT_LAND_RUN             = 574,
    ANIM_FLY_MOUNT_FLIGHT_LAND_RUN         = 575,
    ANIM_READY_BLOW_DART                   = 576,
    ANIM_FLY_READY_BLOW_DART               = 577,
    ANIM_LOAD_BLOW_DART                    = 578,
    ANIM_FLY_LOAD_BLOW_DART                = 579,
    ANIM_HOLD_BLOW_DART                    = 580,
    ANIM_FLY_HOLD_BLOW_DART                = 581,
    ANIM_ATTACK_BLOW_DART                  = 582,
    ANIM_FLY_ATTACK_BLOW_DART              = 583,
    ANIM_CARRIAGE_MOUNT                    = 584,
    ANIM_FLY_CARRIAGE_MOUNT                = 585,
    ANIM_CARRIAGE_PASSENGER_MOUNT          = 586,
    ANIM_FLY_CARRIAGE_PASSENGER_MOUNT      = 587,
    ANIM_CARRIAGE_MOUNT_ATTACK             = 588,
    ANIM_FLY_CARRIAGE_MOUNT_ATTACK         = 589,
    ANIM_BARTENDER_STAND                   = 590,
    ANIM_FLY_BARTENDER_STAND               = 591,
    ANIM_BARTENDER_WALK                    = 592,
    ANIM_FLY_BARTENDER_WALK                = 593,
    ANIM_BARTENDER_RUN                     = 594,
    ANIM_FLY_BARTENDER_RUN                 = 595,
    ANIM_BARTENDER_SHUFFLE_LEFT            = 596,
    ANIM_FLY_BARTENDER_SHUFFLE_LEFT        = 597,
    ANIM_BARTENDER_SHUFFLE_RIGHT           = 598,
    ANIM_FLY_BARTENDER_SHUFFLE_RIGHT       = 599,
    ANIM_BARTENDER_EMOTE_TALK              = 600,
    ANIM_FLY_BARTENDER_EMOTE_TALK          = 601,
    ANIM_BARTENDER_EMOTE_POINT             = 602,
    ANIM_FLY_BARTENDER_EMOTE_POINT         = 603,
    ANIM_BARMAID_STAND                     = 604,
    ANIM_FLY_BARMAID_STAND                 = 605,
    ANIM_BARMAID_WALK                      = 606,
    ANIM_FLY_BARMAID_WALK                  = 607,
    ANIM_BARMAID_RUN                       = 608,
    ANIM_FLY_BARMAID_RUN                   = 609,
    ANIM_BARMAID_SHUFFLE_LEFT              = 610,
    ANIM_FLY_BARMAID_SHUFFLE_LEFT          = 611,
    ANIM_BARMAID_SHUFFLE_RIGHT             = 612,
    ANIM_FLY_BARMAID_SHUFFLE_RIGHT         = 613,
    ANIM_BARMAID_EMOTE_TALK                = 614,
    ANIM_FLY_BARMAID_EMOTE_TALK            = 615,
    ANIM_BARMAID_EMOTE_POINT               = 616,
    ANIM_FLY_BARMAID_EMOTE_POINT           = 617,
    ANIM_MOUNT_SELF_IDLE                   = 618,
    ANIM_FLY_MOUNT_SELF_IDLE               = 619,
    ANIM_MOUNT_SELF_WALK                   = 620,
    ANIM_FLY_MOUNT_SELF_WALK               = 621,
    ANIM_MOUNT_SELF_RUN                    = 622,
    ANIM_FLY_MOUNT_SELF_RUN                = 623,
    ANIM_MOUNT_SELF_SPRINT                 = 624,
    ANIM_FLY_MOUNT_SELF_SPRINT             = 625,
    ANIM_MOUNT_SELF_RUN_LEFT               = 626,
    ANIM_FLY_MOUNT_SELF_RUN_LEFT           = 627,
    ANIM_MOUNT_SELF_RUN_RIGHT              = 628,
    ANIM_FLY_MOUNT_SELF_RUN_RIGHT          = 629,
    ANIM_MOUNT_SELF_SHUFFLE_LEFT           = 630,
    ANIM_FLY_MOUNT_SELF_SHUFFLE_LEFT       = 631,
    ANIM_MOUNT_SELF_SHUFFLE_RIGHT          = 632,
    ANIM_FLY_MOUNT_SELF_SHUFFLE_RIGHT      = 633,
    ANIM_MOUNT_SELF_WALK_BACKWARDS         = 634,
    ANIM_FLY_MOUNT_SELF_WALK_BACKWARDS     = 635,
    ANIM_MOUNT_SELF_SPECIAL                = 636,
    ANIM_FLY_MOUNT_SELF_SPECIAL            = 637,
    ANIM_MOUNT_SELF_JUMP                   = 638,
    ANIM_FLY_MOUNT_SELF_JUMP               = 639,
    ANIM_MOUNT_SELF_JUMP_START             = 640,
    ANIM_FLY_MOUNT_SELF_JUMP_START         = 641,
    ANIM_MOUNT_SELF_JUMP_END               = 642,
    ANIM_FLY_MOUNT_SELF_JUMP_END           = 643,
    ANIM_MOUNT_SELF_JUMP_LAND_RUN          = 644,
    ANIM_FLY_MOUNT_SELF_JUMP_LAND_RUN      = 645,
    ANIM_MOUNT_SELF_START                  = 646,
    ANIM_FLY_MOUNT_SELF_START              = 647,
    ANIM_MOUNT_SELF_FALL                   = 648,
    ANIM_FLY_MOUNT_SELF_FALL               = 649,
    ANIM_STORMSTRIKE                       = 650,
    ANIM_FLY_STORMSTRIKE                   = 651,
    ANIM_READY_JOUST_NO_SHEATHE            = 652,
    ANIM_FLY_READY_JOUST_NO_SHEATHE        = 653,
    ANIM_SLAM                              = 654,
    ANIM_FLY_SLAM                          = 655,
    ANIM_DEATH_STRIKE                      = 656,
    ANIM_FLY_DEATH_STRIKE                  = 657,
    ANIM_SWIM_ATTACK_UNARMED               = 658,
    ANIM_FLY_SWIM_ATTACK_UNARMED           = 659
};

enum LockKeyType
{
    LOCK_KEY_NONE  = 0,
    LOCK_KEY_ITEM  = 1,
    LOCK_KEY_SKILL = 2,
    LOCK_KEY_SPELL = 3,
};

enum LockType
{
    LOCKTYPE_PICKLOCK              = 1,
    LOCKTYPE_HERBALISM             = 2,
    LOCKTYPE_MINING                = 3,
    LOCKTYPE_DISARM_TRAP           = 4,
    LOCKTYPE_OPEN                  = 5,
    LOCKTYPE_TREASURE              = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS  = 7,
    LOCKTYPE_CLOSE                 = 8,
    LOCKTYPE_ARM_TRAP              = 9,
    LOCKTYPE_QUICK_OPEN            = 10,
    LOCKTYPE_QUICK_CLOSE           = 11,
    LOCKTYPE_OPEN_TINKERING        = 12,
    LOCKTYPE_OPEN_KNEELING         = 13,
    LOCKTYPE_OPEN_ATTACKING        = 14,
    LOCKTYPE_GAHZRIDIAN            = 15,
    LOCKTYPE_BLASTING              = 16,
    LOCKTYPE_PVP_OPEN              = 17,
    LOCKTYPE_PVP_CLOSE             = 18,
    LOCKTYPE_FISHING               = 19,
    LOCKTYPE_INSCRIPTION           = 20,
    LOCKTYPE_OPEN_FROM_VEHICLE     = 21,
    LOCKTYPE_ARCHAEOLOGY           = 22,
    LOCKTYPE_PVP_QUICK_OPEN        = 23
};

enum TrainerType                                            // this is important type for npcs!
{
    TRAINER_TYPE_CLASS             = 0,
    TRAINER_TYPE_MOUNTS            = 1,                     // on blizz it's 2
    TRAINER_TYPE_TRADESKILLS       = 2,
    TRAINER_TYPE_PETS              = 3
};

#define MAX_TRAINER_TYPE 4

// CreatureType.dbc
enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13,
    CREATURE_TYPE_WILD_PET         = 14,
    CREATURE_TYPE_ABERRATION       = 15
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL-1)) | (1 << (CREATURE_TYPE_ELEMENTAL-1));

// CreatureFamily.dbc
enum CreatureFamily
{
    CREATURE_FAMILY_WOLF                = 1,
    CREATURE_FAMILY_CAT                 = 2,
    CREATURE_FAMILY_SPIDER              = 3,
    CREATURE_FAMILY_BEAR                = 4,
    CREATURE_FAMILY_BOAR                = 5,
    CREATURE_FAMILY_CROCOLISK           = 6,
    CREATURE_FAMILY_CARRION_BIRD        = 7,
    CREATURE_FAMILY_CRAB                = 8,
    CREATURE_FAMILY_GORILLA             = 9,
    CREATURE_FAMILY_HORSE_CUSTOM        = 10,   // Does not exist in DBC but used for horse like beasts in DB
    CREATURE_FAMILY_RAPTOR              = 11,
    CREATURE_FAMILY_TALLSTRIDER         = 12,
    CREATURE_FAMILY_FELHUNTER           = 15,
    CREATURE_FAMILY_VOIDWALKER          = 16,
    CREATURE_FAMILY_SUCCUBUS            = 17,
    CREATURE_FAMILY_DOOMGUARD           = 19,
    CREATURE_FAMILY_SCORPID             = 20,
    CREATURE_FAMILY_TURTLE              = 21,
    CREATURE_FAMILY_IMP                 = 23,
    CREATURE_FAMILY_BAT                 = 24,
    CREATURE_FAMILY_HYENA               = 25,
    CREATURE_FAMILY_BIRD_OF_PREY        = 26,
    CREATURE_FAMILY_WIND_SERPENT        = 27,
    CREATURE_FAMILY_REMOTE_CONTROL      = 28,
    CREATURE_FAMILY_FELGUARD            = 29,
    CREATURE_FAMILY_DRAGONHAWK          = 30,
    CREATURE_FAMILY_RAVAGER             = 31,
    CREATURE_FAMILY_WARP_STALKER        = 32,
    CREATURE_FAMILY_SPOREBAT            = 33,
    CREATURE_FAMILY_NETHER_RAY          = 34,
    CREATURE_FAMILY_SERPENT             = 35,
    CREATURE_FAMILY_MOTH                = 37,
    CREATURE_FAMILY_CHIMAERA            = 38,
    CREATURE_FAMILY_DEVILSAUR           = 39,
    CREATURE_FAMILY_GHOUL               = 40,
    CREATURE_FAMILY_SILITHID            = 41,
    CREATURE_FAMILY_WORM                = 42,
    CREATURE_FAMILY_RHINO               = 43,
    CREATURE_FAMILY_WASP                = 44,
    CREATURE_FAMILY_CORE_HOUND          = 45,
    CREATURE_FAMILY_SPIRIT_BEAST        = 46,
    CREATURE_FAMILY_WATER_ELEMENTAL     = 49,
    CREATURE_FAMILY_FOX                 = 50,
    CREATURE_FAMILY_MONKEY              = 51,
    CREATURE_FAMILY_DOG                 = 52,
    CREATURE_FAMILY_BEETLE              = 53,
    CREATURE_FAMILY_SHALE_SPIDER        = 55,
    CREATURE_FAMILY_ZOMBIE              = 56,
    CREATURE_FAMILY_QA_TEST_FAMILY      = 57,
    CREATURE_FAMILY_SILITHID_2          = 59,
    CREATURE_FAMILY_WASP_2              = 66,
    CREATURE_FAMILY_HYDRA               = 68,
    CREATURE_FAMILY_FEL_IMP             = 100,
    CREATURE_FAMILY_VOIDLORD            = 101,
    CREATURE_FAMILY_SHIVARRA            = 102,
    CREATURE_FAMILY_OBSERVER            = 103,
    CREATURE_FAMILY_WRATHGUARD          = 104,
    CREATURE_FAMILY_INFERNAL            = 108,
    CREATURE_FAMILY_FIRE_ELEMENTAL      = 116,
    CREATURE_FAMILY_EARTH_ELEMENTAL     = 117,
    CREATURE_FAMILY_CRANE               = 125,
    CREATURE_FAMILY_WATER_STRIDER       = 126,
    CREATURE_FAMILY_PORCUPINE           = 127,
    CREATURE_FAMILY_QUILEN              = 128,
    CREATURE_FAMILY_GOAT                = 129,
    CREATURE_FAMILY_BASILISK            = 130,
    CREATURE_FAMILY_DIREHORN            = 138
};

enum CreatureTypeFlags
{
    CREATURE_TYPEFLAGS_TAMEABLE         = 0x00000001,         // Tameable by any hunter
    CREATURE_TYPEFLAGS_GHOST            = 0x00000002,         // Creature are also visible for not alive player. Allow gossip interaction if npcflag allow?
    CREATURE_TYPEFLAGS_BOSS             = 0x00000004,
    CREATURE_TYPEFLAGS_UNK3             = 0x00000008,
    CREATURE_TYPEFLAGS_UNK4             = 0x00000010,
    CREATURE_TYPEFLAGS_UNK5             = 0x00000020,
    CREATURE_TYPEFLAGS_UNK6             = 0x00000040,
    CREATURE_TYPEFLAGS_DEAD_INTERACT    = 0x00000080,         // Player can interact with the creature if its dead (not player dead)
    CREATURE_TYPEFLAGS_HERBLOOT         = 0x00000100,         // Can be looted by herbalist
    CREATURE_TYPEFLAGS_MININGLOOT       = 0x00000200,         // Can be looted by miner
    CREATURE_TYPEFLAGS_UNK10            = 0x00000400,
    CREATURE_TYPEFLAGS_MOUNTED_COMBAT   = 0x00000800,         // Creature can remain mounted when entering combat
    CREATURE_TYPEFLAGS_AID_PLAYERS      = 0x00001000,         // ? Can aid any player in combat if in range?
    CREATURE_TYPEFLAGS_UNK13            = 0x00002000,
    CREATURE_TYPEFLAGS_UNK14            = 0x00004000,         // ? Possibly not in use
    CREATURE_TYPEFLAGS_ENGINEERLOOT     = 0x00008000,         // Can be looted by engineer
    CREATURE_TYPEFLAGS_EXOTIC           = 0x00010000,         // Can be tamed by hunter as exotic pet
    CREATURE_TYPEFLAGS_UNK17            = 0x00020000,         // ? Related to vehicles/pvp?
    CREATURE_TYPEFLAGS_UNK18            = 0x00040000,         // ? Related to vehicle/siege weapons?
    CREATURE_TYPEFLAGS_UNK19            = 0x00080000,
    CREATURE_TYPEFLAGS_UNK20            = 0x00100000,
    CREATURE_TYPEFLAGS_UNK21            = 0x00200000,
    CREATURE_TYPEFLAGS_UNK22            = 0x00400000,
    CREATURE_TYPEFLAGS_UNK23            = 0x00800000,         // ? First seen in 3.2.2. Related to banner/backpack of creature/companion?
    CREATURE_TYPEFLAGS_UNK24            = 0x01000000,
    CREATURE_TYPEFLAGS_UNK25            = 0x02000000,
    CREATURE_TYPEFLAGS_PARTY_MEMBER     = 0x04000000,         //! Creature can be targeted by spells that require target to be in caster's party/raid
    CREATURE_TYPEFLAGS_UNK27            = 0x08000000,
    CREATURE_TYPEFLAGS_UNK28            = 0x10000000,
    CREATURE_TYPEFLAGS_UNK29            = 0x20000000,
    CREATURE_TYPEFLAGS_UNK30            = 0x40000000,
    CREATURE_TYPEFLAGS_UNK31            = 0x80000000
};

enum CreatureTypeFlags2
{
    CREATURE_TYPEFLAGS_2_UNK1           = 0x00000001,
    CREATURE_TYPEFLAGS_2_UNK2           = 0x00000002,
    CREATURE_TYPEFLAGS_2_UNK3           = 0x00000004,
    CREATURE_TYPEFLAGS_2_UNK4           = 0x00000008,
    CREATURE_TYPEFLAGS_2_UNK5           = 0x00000010,
    CREATURE_TYPEFLAGS_2_UNK6           = 0x00000020,
    CREATURE_TYPEFLAGS_2_UNK7           = 0x00000040,
    CREATURE_TYPEFLAGS_2_UNK8           = 0x00000080
};

enum CreatureEliteType
{
    CREATURE_ELITE_NORMAL          = 0,
    CREATURE_ELITE_ELITE           = 1,
    CREATURE_ELITE_RAREELITE       = 2,
    CREATURE_ELITE_WORLDBOSS       = 3,
    CREATURE_ELITE_RARE            = 4,
    CREATURE_UNKNOWN               = 5,                      // found in 2.2.3 for 2 mobs
    CREATURE_WEAK                  = 6
};

// values based at Holidays.dbc
enum HolidayIds
{
    HOLIDAY_NONE                     = 0,

    HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
    HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
    HOLIDAY_NOBLEGARDEN              = 181,
    HOLIDAY_CHILDRENS_WEEK           = 201,
    HOLIDAY_CALL_TO_ARMS_AV_4D       = 283,
    HOLIDAY_CALL_TO_ARMS_WS_4D       = 284,
    HOLIDAY_CALL_TO_ARMS_AB_4D       = 285,
    HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
    HOLIDAY_HARVEST_FESTIVAL         = 321,
    HOLIDAY_HALLOWS_END              = 324,
    HOLIDAY_LUNAR_FESTIVAL           = 327,
    //HOLIDAY_LOVE_IS_IN_THE_AIR       = 335, unused/duplicated
    HOLIDAY_FIRE_FESTIVAL            = 341,
    HOLIDAY_CALL_TO_ARMS_EY_4D       = 353,
    HOLIDAY_BREWFEST                 = 372,
    HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
    HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
    HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
    HOLIDAY_PIRATES_DAY              = 398,
    HOLIDAY_CALL_TO_ARMS_SA_4D       = 400,
    HOLIDAY_PILGRIMS_BOUNTY          = 404,
    HOLIDAY_WOTLK_LAUNCH             = 406,
    HOLIDAY_DAY_OF_DEAD              = 409,
    HOLIDAY_CALL_TO_ARMS_IC_4D       = 420,
    HOLIDAY_LOVE_IS_IN_THE_AIR       = 423,
    HOLIDAY_KALU_AK_FISHING_DERBY    = 424,
    HOLIDAY_CALL_TO_ARMS_BFG_4D      = 435,
    HOLIDAY_CALL_TO_ARMS_TP_4D       = 436,
    HOLIDAY_RATED_BG_15_VS_15        = 442,
    HOLIDAY_RATED_BG_25_VS_25        = 443,
    HOLIDAY_ANNIVERSARY_7_YEARS      = 467,
    HOLIDAY_DARKMOON_FAIRE_TEROKKAR  = 479,
    HOLIDAY_ANNIVERSARY_8_YEARS      = 484,
    HOLIDAY_CALL_TO_ARMS_SM_4D       = 488,
    HOLIDAY_CALL_TO_ARMS_TOK_4D      = 489,
    HOLIDAY_CALL_TO_ARMS_AV_3D       = 490,
    HOLIDAY_CALL_TO_ARMS_WS_3D       = 499,
    HOLIDAY_CALL_TO_ARMS_AB_3D       = 491,
    HOLIDAY_CALL_TO_ARMS_EY_3D       = 492,
    HOLIDAY_CALL_TO_ARMS_IC_3D       = 493,
    HOLIDAY_CALL_TO_ARMS_SM_3D       = 494,
    HOLIDAY_CALL_TO_ARMS_SA_3D       = 495,
    HOLIDAY_CALL_TO_ARMS_TOK_3D      = 496,
    HOLIDAY_CALL_TO_ARMS_BFG_3D      = 497,
    HOLIDAY_CALL_TO_ARMS_TP_3D       = 498,
    HOLIDAY_CALL_TO_ARMS_DG_4D       = 515,
    HOLIDAY_CALL_TO_ARMS_DG_3D       = 516,
};

// values based at QuestInfo.dbc
enum QuestTypes
{
    QUEST_TYPE_GROUP               = 1,
    QUEST_TYPE_CLASS               = 21,
    QUEST_TYPE_PVP                 = 41,
    QUEST_TYPE_RAID                = 62,
    QUEST_TYPE_DUNGEON             = 81,
    QUEST_TYPE_WORLD_EVENT         = 82,
    QUEST_TYPE_LEGENDARY           = 83,
    QUEST_TYPE_ESCORT              = 84,
    QUEST_TYPE_HEROIC              = 85,
    QUEST_TYPE_RAID_10             = 88,
    QUEST_TYPE_RAID_25             = 89,
    QUEST_TYPE_SCENARIO            = 98,
    QUEST_TYPE_ACCOUNT             = 102,
};

// values based at QuestSort.dbc
enum QuestSort
{
    QUEST_SORT_EPIC                = 1,
    QUEST_SORT_HALLOWS_END         = 21,
    QUEST_SORT_SEASONAL            = 22,
    QUEST_SORT_CATACLYSM           = 23,
    QUEST_SORT_HERBALISM           = 24,
    QUEST_SORT_BATTLEGROUNDS       = 25,
    QUEST_SORT_DAY_OF_THE_DEAD     = 41,
    QUEST_SORT_WARLOCK             = 61,
    QUEST_SORT_WARRIOR             = 81,
    QUEST_SORT_SHAMAN              = 82,
    QUEST_SORT_FISHING             = 101,
    QUEST_SORT_BLACKSMITHING       = 121,
    QUEST_SORT_PALADIN             = 141,
    QUEST_SORT_MAGE                = 161,
    QUEST_SORT_ROGUE               = 162,
    QUEST_SORT_ALCHEMY             = 181,
    QUEST_SORT_LEATHERWORKING      = 182,
    QUEST_SORT_ENGINEERING         = 201,
    QUEST_SORT_TREASURE_MAP        = 221,
    QUEST_SORT_TOURNAMENT          = 241,
    QUEST_SORT_HUNTER              = 261,
    QUEST_SORT_PRIEST              = 262,
    QUEST_SORT_DRUID               = 263,
    QUEST_SORT_TAILORING           = 264,
    QUEST_SORT_SPECIAL             = 284,
    QUEST_SORT_COOKING             = 304,
    QUEST_SORT_FIRST_AID           = 324,
    QUEST_SORT_LEGENDARY           = 344,
    QUEST_SORT_DARKMOON_FAIRE      = 364,
    QUEST_SORT_AHN_QIRAJ_WAR       = 365,
    QUEST_SORT_LUNAR_FESTIVAL      = 366,
    QUEST_SORT_REPUTATION          = 367,
    QUEST_SORT_INVASION            = 368,
    QUEST_SORT_MIDSUMMER           = 369,
    QUEST_SORT_BREWFEST            = 370,
    QUEST_SORT_INSCRIPTION         = 371,
    QUEST_SORT_DEATH_KNIGHT        = 372,
    QUEST_SORT_JEWELCRAFTING       = 373,
    QUEST_SORT_NOBLEGARDEN         = 374,
    QUEST_SORT_PILGRIMS_BOUNTY     = 375,
    QUEST_SORT_LOVE_IS_IN_THE_AIR  = 376,
    QUEST_SORT_ARCHAEOLOGY         = 377,
    QUEST_SORT_CHILDRENS_WEEK      = 378,
    QUEST_SORT_FIRELANDS_INVASION  = 379,
    QUEST_SORT_ZANDALARI           = 380,
    QUEST_SORT_ELEMENTAL_BONDS     = 381,
    QUEST_SORT_PANDAREN_BREWMASTER = 391,
    QUEST_SORT_SCENRAIO            = 392,
    QUEST_SORT_BATTLE_PETS         = 394,
    QUEST_SORT_MONK                = 395,
    QUEST_SORT_LANDFALL            = 396,
    QUEST_SORT_PANDAREN_CAMPAIGN   = 397,
    QUEST_SORT_RIDING              = 398,
    QUEST_SORT_BRAWLERS_GUILD      = 399,
    QUEST_SORT_PROVING_GROUNDS     = 400
};

inline uint8 ClassByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_WARLOCK:        return CLASS_WARLOCK;
        case QUEST_SORT_WARRIOR:        return CLASS_WARRIOR;
        case QUEST_SORT_SHAMAN:         return CLASS_SHAMAN;
        case QUEST_SORT_PALADIN:        return CLASS_PALADIN;
        case QUEST_SORT_MAGE:           return CLASS_MAGE;
        case QUEST_SORT_ROGUE:          return CLASS_ROGUE;
        case QUEST_SORT_HUNTER:         return CLASS_HUNTER;
        case QUEST_SORT_PRIEST:         return CLASS_PRIEST;
        case QUEST_SORT_DRUID:          return CLASS_DRUID;
        case QUEST_SORT_DEATH_KNIGHT:   return CLASS_DEATH_KNIGHT;
        case QUEST_SORT_MONK:           return CLASS_MONK;
    }
    return 0;
}

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_TIGER             = 150,
    SKILL_RIDING_RAM               = 152,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINEERING              = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,   // SkillCategory = -1
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788,
    SKILL_RACIAL_WORGEN            = 789,
    SKILL_RACIAL_GOBLIN            = 790,
    SKILL_LANG_WORGEN              = 791,
    SKILL_LANG_GOBLIN              = 792,
    SKILL_ARCHAEOLOGY              = 794,
    SKILL_GENERAL_HUNTER           = 795,
    SKILL_GENERAL_DEATH_KNIGHT     = 796,
    SKILL_GENERAL_ROGUE            = 797,
    SKILL_GENERAL_DRUID            = 798,
    SKILL_GENERAL_MAGE             = 799,
    SKILL_GENERAL_PALADIN          = 800,
    SKILL_GENERAL_SHAMAN           = 801,
    SKILL_GENERAL_WARLOCK          = 802,
    SKILL_GENERAL_WARRIOR          = 803,
    SKILL_GENERAL_PRIEST           = 804,
    SKILL_PET_WATER_ELEMENTAL      = 805,
    SKILL_PET_FOX                  = 808,
    SKILL_ALL_GLYPHS               = 810,
    SKILL_PET_DOG                  = 811,
    SKILL_PET_MONKEY               = 815,
    SKILL_PET_SHALE_SPIDER         = 817,
    SKILL_PET_BEETLE               = 818,
    SKILL_ALL_GUILD_PERKS          = 821,
    SKILL_PET_HYDRA                = 824,
    SKILL_LANG_PANDAREN_NEUTRAL    = 905,
    SKILL_LANG_PANDAREN_ALLIANCE   = 906,
    SKILL_LANG_PANDAREN_HORDE      = 907,
    SKILL_WAY_OF_THE_GRILL         = 975,
    SKILL_WAY_OF_THE_WOK           = 976,
    SKILL_WAY_OF_THE_POT           = 977,
    SKILL_WAY_OF_THE_STEAMER       = 978,
    SKILL_WAY_OF_THE_OVEN          = 979,
    SKILL_WAY_OF_THE_BREW          = 980,
};

#define MAX_SKILL_TYPE               908

inline SkillType SkillByLockType(LockType locktype)
{
    switch (locktype)
    {
        case LOCKTYPE_PICKLOCK:    return SKILL_LOCKPICKING;
        case LOCKTYPE_HERBALISM:   return SKILL_HERBALISM;
        case LOCKTYPE_MINING:      return SKILL_MINING;
        case LOCKTYPE_FISHING:     return SKILL_FISHING;
        case LOCKTYPE_INSCRIPTION: return SKILL_INSCRIPTION;
        case LOCKTYPE_ARCHAEOLOGY: return SKILL_ARCHAEOLOGY;
        default: break;
    }
    return SKILL_NONE;
}

inline uint32 SkillByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_HERBALISM:      return SKILL_HERBALISM;
        case QUEST_SORT_FISHING:        return SKILL_FISHING;
        case QUEST_SORT_BLACKSMITHING:  return SKILL_BLACKSMITHING;
        case QUEST_SORT_ALCHEMY:        return SKILL_ALCHEMY;
        case QUEST_SORT_LEATHERWORKING: return SKILL_LEATHERWORKING;
        case QUEST_SORT_ENGINEERING:    return SKILL_ENGINEERING;
        case QUEST_SORT_TAILORING:      return SKILL_TAILORING;
        case QUEST_SORT_COOKING:        return SKILL_COOKING;
        case QUEST_SORT_FIRST_AID:      return SKILL_FIRST_AID;
        case QUEST_SORT_JEWELCRAFTING:  return SKILL_JEWELCRAFTING;
        case QUEST_SORT_INSCRIPTION:    return SKILL_INSCRIPTION;
        case QUEST_SORT_ARCHAEOLOGY:    return SKILL_ARCHAEOLOGY;
    }
    return 0;
}

enum SkillCategory
{
    SKILL_CATEGORY_UNK1          = 0,
    SKILL_CATEGORY_ATTRIBUTES    = 5,
    SKILL_CATEGORY_WEAPON        = 6,
    SKILL_CATEGORY_CLASS         = 7,
    SKILL_CATEGORY_ARMOR         = 8,
    SKILL_CATEGORY_SECONDARY     = 9,                       // secondary professions
    SKILL_CATEGORY_LANGUAGES     = 10,
    SKILL_CATEGORY_PROFESSION    = 11,                      // primary professions
    SKILL_CATEGORY_GENERIC       = 12
};

enum TotemCategory
{
    TC_SKINNING_SKIFE_OLD          = 1,
    TC_EARTH_TOTEM                 = 2,
    TC_AIR_TOTEM                   = 3,
    TC_FIRE_TOTEM                  = 4,
    TC_WATER_TOTEM                 = 5,
    TC_COPPER_ROD                  = 6,
    TC_SILVER_ROD                  = 7,
    TC_GOLDEN_ROD                  = 8,
    TC_TRUESILVER_ROD              = 9,
    TC_ARCANITE_ROD                = 10,
    TC_MINING_PICK_OLD             = 11,
    TC_PHILOSOPHERS_STONE          = 12,
    TC_BLACKSMITH_HAMMER_OLD       = 13,
    TC_ARCLIGHT_SPANNER            = 14,
    TC_GYROMATIC_MA                = 15,
    TC_MASTER_TOTEM                = 21,
    TC_FEL_IRON_ROD                = 41,
    TC_ADAMANTITE_ROD              = 62,
    TC_ETERNIUM_ROD                = 63,
    TC_HOLLOW_QUILL                = 81,
    TC_RUNED_AZURITE_ROD           = 101,
    TC_VIRTUOSO_INKING_SET         = 121,
    TC_DRUMS                       = 141,
    TC_GNOMISH_ARMY_KNIFE          = 161,
    TC_BLACKSMITH_HAMMER           = 162,
    TC_MINING_PICK                 = 165,
    TC_SKINNING_KNIFE              = 166,
    TC_HAMMER_PICK                 = 167,
    TC_BLADED_PICKAXE              = 168,
    TC_FLINT_AND_TINDER            = 169,
    TC_RUNED_COBALT_ROD            = 189,
    TC_RUNED_TITANIUM_ROD          = 190,
    TC_RUNED_ELEMENTIUM_ROD        = 209,
    TC_HIGH_POWERED_BOLT_GUN       = 210,
};

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    // UNIT_DYNFLAG_UNK1                    = 0x0001,       // Could be related to battle pet tracking
    UNIT_DYNFLAG_LOOTABLE                   = 0x0002,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0004,
    UNIT_DYNFLAG_TAPPED                     = 0x0008,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0010,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0020,
    UNIT_DYNFLAG_DEAD                       = 0x0040,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0080,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0100        // Lua_UnitIsTappedByAllThreatList
};

enum CorpseDynFlags
{
    CORPSE_DYNFLAG_LOOTABLE        = 0x0001
};

enum WeatherType
{
    WEATHER_TYPE_FINE       = 0,
    WEATHER_TYPE_RAIN       = 1,
    WEATHER_TYPE_SNOW       = 2,
    WEATHER_TYPE_STORM      = 3,
    WEATHER_TYPE_THUNDERS   = 86,
    WEATHER_TYPE_BLACKRAIN  = 90
};

#define MAX_WEATHER_TYPE 4

enum ChatMsg : uint8
{
    CHAT_MSG_ADDON                  = 0xFF, // Generally it is not correct and enum must be signed
    CHAT_MSG_SYSTEM                 = 0,
    CHAT_MSG_SAY                    = 1,
    CHAT_MSG_PARTY                  = 2,
    CHAT_MSG_RAID                   = 3,
    CHAT_MSG_GUILD                  = 4,
    CHAT_MSG_OFFICER                = 5,
    CHAT_MSG_YELL                   = 6,
    CHAT_MSG_WHISPER                = 7,
    CHAT_MSG_WHISPER_FOREIGN        = 8,
    CHAT_MSG_WHISPER_INFORM         = 9,
    CHAT_MSG_EMOTE                  = 10,
    CHAT_MSG_TEXT_EMOTE             = 11,
    CHAT_MSG_MONSTER_SAY            = 12,
    CHAT_MSG_MONSTER_PARTY          = 13,
    CHAT_MSG_MONSTER_YELL           = 14,
    CHAT_MSG_MONSTER_WHISPER        = 15,
    CHAT_MSG_MONSTER_EMOTE          = 16,
    CHAT_MSG_CHANNEL                = 17,
    CHAT_MSG_CHANNEL_JOIN           = 18,
    CHAT_MSG_CHANNEL_LEAVE          = 19,
    CHAT_MSG_CHANNEL_LIST           = 19,
    CHAT_MSG_CHANNEL_NOTICE         = 20,
    CHAT_MSG_CHANNEL_NOTICE_USER    = 21,
    // CHAT_MSG_TARGETICONS
    CHAT_MSG_AFK                    = 23,
    CHAT_MSG_DND                    = 24,
    CHAT_MSG_IGNORED                = 25,
    CHAT_MSG_SKILL                  = 26,
    CHAT_MSG_LOOT                   = 27,
    CHAT_MSG_MONEY                  = 28,
    CHAT_MSG_OPENING                = 29,
    CHAT_MSG_TRADESKILLS            = 30,
    CHAT_MSG_PET_INFO               = 31,
    CHAT_MSG_COMBAT_MISC_INFO       = 32,
    CHAT_MSG_COMBAT_XP_GAIN         = 33,
    CHAT_MSG_COMBAT_HONOR_GAIN      = 34,
    CHAT_MSG_COMBAT_FACTION_CHANGE  = 35,
    CHAT_MSG_BG_SYSTEM_NEUTRAL      = 36,
    CHAT_MSG_BG_SYSTEM_ALLIANCE     = 37,
    CHAT_MSG_BG_SYSTEM_HORDE        = 38,
    CHAT_MSG_RAID_LEADER            = 39,
    CHAT_MSG_RAID_WARNING           = 40,
    CHAT_MSG_RAID_BOSS_EMOTE        = 41,
    CHAT_MSG_RAID_BOSS_WHISPER      = 42,
    CHAT_MSG_FILTERED               = 43,
    CHAT_MSG_RESTRICTED             = 44,
    //CHAT_MSG_UNKNOWN                = 45,   // Has "WHISPER" lable in client. May be outgoing for 51. Need to reverse for more information.
    CHAT_MSG_ACHIEVEMENT            = 46,
    CHAT_MSG_GUILD_ACHIEVEMENT      = 47,
    //CHAT_MSG_UNKNOWN                = 48,
    CHAT_MSG_PARTY_LEADER           = 49,
    CHAT_MSG_ARENA_POINTS           = 50,
    //CHAT_MSG_UNK_WHISPER_IN         = 51,   // Has "WHISPER" lable in client, incoming, cyan color.
    CHAT_MSG_INSTANCE_CHAT          = 66,
    CHAT_MSG_INSTANCE_CHAT_LEADER   = 67,
};

#define MSG_NULL_ACTION 0x34
#define MAX_CHAT_MSG_TYPE 0x41

enum ChatLinkColors
{
    CHAT_LINK_COLOR_TRADE       = 0xffffd000,   // orange
    CHAT_LINK_COLOR_TALENT      = 0xff71d5ff,   // same as spell
    CHAT_LINK_COLOR_SPELL       = 0xff71d5ff,   // bright blue
    CHAT_LINK_COLOR_ENCHANT     = 0xffffd000,   // orange
    CHAT_LINK_COLOR_ACHIEVEMENT = 0xffffff00,
    CHAT_LINK_COLOR_GLYPH       = 0xff66bbff
};

// Values from ItemPetFood (power of (value-1) used for compare with CreatureFamilyEntry.petDietMask
enum PetDiet
{
    PET_DIET_MEAT     = 1,
    PET_DIET_FISH     = 2,
    PET_DIET_CHEESE   = 3,
    PET_DIET_BREAD    = 4,
    PET_DIET_FUNGAS   = 5,
    PET_DIET_FRUIT    = 6,
    PET_DIET_RAW_MEAT = 7,
    PET_DIET_RAW_FISH = 8
};

#define MAX_PET_DIET 9

#define CHAIN_SPELL_JUMP_RADIUS 8

enum GuildLogs
{
    GUILD_BANKLOG_MAX_RECORDS   = 25,
    GUILD_EVENTLOG_MAX_RECORDS  = 100,
    GUILD_NEWSLOG_MAX_RECORDS   = 250
};

enum AiReaction
{
    AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
    AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
    AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
    AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
    AI_REACTION_DESTROY  = 4                                // used on object destroy (NOT used in client packet handler)
};

// Diminishing Returns Types
enum DiminishingReturnsType
{
    DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
    DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
    DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

// Diminishing Return Groups
enum DiminishingGroup
{
    DIMINISHING_NONE                = 0,
    DIMINISHING_BANISH              = 1,
    DIMINISHING_CYCLONE             = 2,
    DIMINISHING_DISARM              = 3,
    DIMINISHING_MESMERIZES          = 4,
    DIMINISHING_MESMERIZES_SHORT    = 5,
    DIMINISHING_FEAR                = 6,
    DIMINISHING_HORROR              = 7,
    DIMINISHING_MIND_CONTROL        = 8,
    DIMINISHING_ROOT                = 9,
    DIMINISHING_ROOT_SHORT          = 10,
    DIMINISHING_STUN                = 11,
    DIMINISHING_STUN_SHORT          = 12,
    DIMINISHING_SILENCE             = 13,
    DIMINISHING_SLEEP               = 14,
    DIMINISHING_TAUNT               = 15,
    DIMINISHING_LIMITONLY           = 16,
};

enum SummonCategory
{
    SUMMON_CATEGORY_WILD        = 0,
    SUMMON_CATEGORY_ALLY        = 1,
    SUMMON_CATEGORY_PET         = 2,
    SUMMON_CATEGORY_PUPPET      = 3,
    SUMMON_CATEGORY_VEHICLE     = 4,
    SUMMON_CATEGORY_UNK         = 5  // as of patch 3.3.5a only Bone Spike in Icecrown Citadel
                                     // uses this category
};

enum SummonType
{
    SUMMON_TYPE_NONE        = 0,
    SUMMON_TYPE_PET         = 1,
    SUMMON_TYPE_GUARDIAN    = 2,
    SUMMON_TYPE_MINION      = 3,
    SUMMON_TYPE_TOTEM       = 4,
    SUMMON_TYPE_MINIPET     = 5,
    SUMMON_TYPE_GUARDIAN2   = 6,
    SUMMON_TYPE_WILD2       = 7,
    SUMMON_TYPE_WILD3       = 8,    // Related to phases and DK prequest line (3.3.5a)
    SUMMON_TYPE_VEHICLE     = 9,
    SUMMON_TYPE_VEHICLE2    = 10,   // Oculus and Argent Tournament vehicles (3.3.5a)
    SUMMON_TYPE_LIGHTWELL   = 11,
    SUMMON_TYPE_JEEVES      = 12,
    SUMMON_TYPE_UNK13       = 13,
    SUMMON_TYPE_UNK14       = 14,
    SUMMON_TYPE_UNK15       = 15,
    SUMMON_TYPE_STATUE      = 16,
    SUMMON_TYPE_UNK17       = 17,
    SUMMON_TYPE_WARBANNER   = 18,
    SUMMON_TYPE_UNK19       = 19,
    SUMMON_TYPE_UNK20       = 20,
    SUMMON_TYPE_UNK21       = 21,
    SUMMON_TYPE_UNK22       = 22,
    SUMMON_TYPE_UNK24       = 24
};

enum EventId
{
    EVENT_CHARGE            = 1003,
    EVENT_JUMP              = 1004,

    /// Special charge event which is used for charge spells that have explicit targets
    /// and had a path already generated - using it in PointMovementGenerator will not
    /// create a new spline and launch it
    EVENT_CHARGE_PREPATH    = 1005
};

enum ResponseCodes
{
    RESPONSE_SUCCESS                                       = 0,
    RESPONSE_FAILURE                                       = 1,
    RESPONSE_CANCELLED                                     = 2,
    RESPONSE_DISCONNECTED                                  = 3,
    RESPONSE_FAILED_TO_CONNECT                             = 4,
    RESPONSE_CONNECTED                                     = 5,
    RESPONSE_VERSION_MISMATCH                              = 6,

    CSTATUS_CONNECTING                                     = 7,
    CSTATUS_NEGOTIATING_SECURITY                           = 8,
    CSTATUS_NEGOTIATION_COMPLETE                           = 9,
    CSTATUS_NEGOTIATION_FAILED                             = 10,
    CSTATUS_AUTHENTICATING                                 = 11,

    AUTH_OK                                                = 12,
    AUTH_FAILED                                            = 13,
    AUTH_REJECT                                            = 14,
    AUTH_BAD_SERVER_PROOF                                  = 15,
    AUTH_UNAVAILABLE                                       = 16,
    AUTH_SYSTEM_ERROR                                      = 17,
    AUTH_BILLING_ERROR                                     = 18,
    AUTH_BILLING_EXPIRED                                   = 19,
    AUTH_VERSION_MISMATCH                                  = 20,
    AUTH_UNKNOWN_ACCOUNT                                   = 21,
    AUTH_INCORRECT_PASSWORD                                = 22,
    AUTH_SESSION_EXPIRED                                   = 23,
    AUTH_SERVER_SHUTTING_DOWN                              = 24,
    AUTH_ALREADY_LOGGING_IN                                = 25,
    AUTH_LOGIN_SERVER_NOT_FOUND                            = 26,
    AUTH_WAIT_QUEUE                                        = 27,
    AUTH_BANNED                                            = 28,
    AUTH_ALREADY_ONLINE                                    = 29,
    AUTH_NO_TIME                                           = 30,
    AUTH_DB_BUSY                                           = 31,
    AUTH_SUSPENDED                                         = 32,
    AUTH_PARENTAL_CONTROL                                  = 33,
    AUTH_LOCKED_ENFORCED                                   = 34,

    REALM_LIST_IN_PROGRESS                                 = 35,
    REALM_LIST_SUCCESS                                     = 36,
    REALM_LIST_FAILED                                      = 37,
    REALM_LIST_INVALID                                     = 38,
    REALM_LIST_REALM_NOT_FOUND                             = 39,

    ACCOUNT_CREATE_IN_PROGRESS                             = 40,
    ACCOUNT_CREATE_SUCCESS                                 = 41,
    ACCOUNT_CREATE_FAILED                                  = 42,

    CHAR_LIST_RETRIEVING                                   = 43,
    CHAR_LIST_RETRIEVED                                    = 44,
    CHAR_LIST_FAILED                                       = 45,

    CHAR_CREATE_IN_PROGRESS                                = 46,
    CHAR_CREATE_SUCCESS                                    = 47,
    CHAR_CREATE_ERROR                                      = 48,
    CHAR_CREATE_FAILED                                     = 49,
    CHAR_CREATE_NAME_IN_USE                                = 50,
    CHAR_CREATE_DISABLED                                   = 51,
    CHAR_CREATE_PVP_TEAMS_VIOLATION                        = 52,
    CHAR_CREATE_SERVER_LIMIT                               = 53,
    CHAR_CREATE_ACCOUNT_LIMIT                              = 54,
    CHAR_CREATE_SERVER_QUEUE                               = 55,
    CHAR_CREATE_ONLY_EXISTING                              = 56,
    CHAR_CREATE_EXPANSION                                  = 57,
    CHAR_CREATE_EXPANSION_CLASS                            = 58,
    CHAR_CREATE_LEVEL_REQUIREMENT                          = 59,
    CHAR_CREATE_UNIQUE_CLASS_LIMIT                         = 60,
    CHAR_CREATE_CHARACTER_IN_GUILD                         = 61,
    CHAR_CREATE_RESTRICTED_RACECLASS                       = 62,
    CHAR_CREATE_CHARACTER_CHOOSE_RACE                      = 63,
    CHAR_CREATE_CHARACTER_ARENA_LEADER                     = 64,
    CHAR_CREATE_CHARACTER_DELETE_MAIL                      = 65,
    CHAR_CREATE_CHARACTER_SWAP_FACTION                     = 66,
    CHAR_CREATE_CHARACTER_RACE_ONLY                        = 67,
    CHAR_CREATE_CHARACTER_GOLD_LIMIT                       = 68,
    CHAR_CREATE_FORCE_LOGIN                                = 69,
    CHAR_CREATE_TRIAL                                      = 70,

    CHAR_DELETE_IN_PROGRESS                                = 71,
    CHAR_DELETE_SUCCESS                                    = 72,
    CHAR_DELETE_FAILED                                     = 73,
    CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER                 = 74,
    CHAR_DELETE_FAILED_GUILD_LEADER                        = 75,
    CHAR_DELETE_FAILED_ARENA_CAPTAIN                       = 76,
    CHAR_DELETE_FAILED_HAS_HEIRLOOM_OR_MAIL                = 77,

    CHAR_LOGIN_IN_PROGRESS                                 = 78,
    CHAR_LOGIN_SUCCESS                                     = 79,
    CHAR_LOGIN_NO_WORLD                                    = 80,
    CHAR_LOGIN_DUPLICATE_CHARACTER                         = 81,
    CHAR_LOGIN_NO_INSTANCES                                = 82,
    CHAR_LOGIN_FAILED                                      = 83,
    CHAR_LOGIN_DISABLED                                    = 84,
    CHAR_LOGIN_NO_CHARACTER                                = 85,
    CHAR_LOGIN_LOCKED_FOR_TRANSFER                         = 86,
    CHAR_LOGIN_LOCKED_BY_BILLING                           = 87,
    CHAR_LOGIN_LOCKED_BY_MOBILE_AH                         = 88,
    CHAR_LOGIN_TEMPORARY_GM_LOCK                           = 89,
    CHAR_LOGIN_LOCKED_BY_CHARACTER_UPGRADE                 = 90,
    CHAR_LOGIN_LOCKED_BY_REVOKED_CHARACTER_UPGRADE         = 91,

    CHAR_NAME_SUCCESS                                      = 92,
    CHAR_NAME_FAILURE                                      = 93,
    CHAR_NAME_NO_NAME                                      = 94,
    CHAR_NAME_TOO_SHORT                                    = 95,
    CHAR_NAME_TOO_LONG                                     = 96,
    CHAR_NAME_INVALID_CHARACTER                            = 97,
    CHAR_NAME_MIXED_LANGUAGES                              = 98,
    CHAR_NAME_PROFANE                                      = 99,
    CHAR_NAME_RESERVED                                     = 100,
    CHAR_NAME_INVALID_APOSTROPHE                           = 101,
    CHAR_NAME_MULTIPLE_APOSTROPHES                         = 102,
    CHAR_NAME_THREE_CONSECUTIVE                            = 103,
    CHAR_NAME_INVALID_SPACE                                = 104,
    CHAR_NAME_CONSECUTIVE_SPACES                           = 105,
    CHAR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS        = 106,
    CHAR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END = 107,
    CHAR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME            = 108,
};

/// Ban function modes
enum BanMode
{
    BAN_ACCOUNT,
    BAN_CHARACTER,
    BAN_IP,
    BAN_SOLO,
};

/// Ban function return codes
enum BanReturn
{
    BAN_SUCCESS,
    BAN_SYNTAX_ERROR,
    BAN_NOTFOUND
};

// indexes of BattlemasterList.dbc
enum BattlegroundTypeId
{
    BATTLEGROUND_TYPE_NONE      = 0, // None
    BATTLEGROUND_AV             = 1, // Alterac Valley
    BATTLEGROUND_WS             = 2, // Warsong Gulch
    BATTLEGROUND_AB             = 3, // Arathi Basin
    BATTLEGROUND_NA             = 4, // Nagrand Arena
    BATTLEGROUND_BE             = 5, // Blade's Edge Arena
    BATTLEGROUND_AA             = 6, // All Arenas
    BATTLEGROUND_EY             = 7, // Eye of the Storm
    BATTLEGROUND_RL             = 8, // Ruins of Lordaernon
    BATTLEGROUND_SA             = 9, // Strand of the Ancients
    BATTLEGROUND_DS             = 10, // Dalaran Sewers
    BATTLEGROUND_RV             = 11, // Ring of Valor
    BATTLEGROUND_IC             = 30, // Isle of Conquest
    BATTLEGROUND_RB             = 32, // Random Battleground
    BATTLEGROUND_RATED_10_VS_10 = 100, // Rated BG 10 vs 10
    BATTLEGROUND_RATED_15_VS_15 = 101, // Rated BG 15 vs 15
    BATTLEGROUND_RATED_25_VS_25 = 102, // Rated BG 25 vs 25
    BATTLEGROUND_TP             = 108, // Twin Peaks
    BATTLEGROUND_BFG            = 120, // Battle For Gilneas
    BATTLEGROUND_REY            = 656, // Rated Eye of the Storm
    BATTLEGROUND_TOK            = 699, // 5.x Temple of Kotmogu
    BATTLEGROUND_CTF            = 706, // 5.x CTF3
    BATTLEGROUND_SM             = 708, // 5.x Silvershard Mines
    BATTLEGROUND_TV             = 719, // 5.x Tol'Vir Arena
    BATTLEGROUND_DG             = 754, // 5.x Deepwind Gorge
    BATTLEGROUND_TTP            = 757, // 5.x The Tiger's Peak
};

#define MAX_BATTLEGROUND_TYPE_ID 758

enum MailResponseType
{
    MAIL_SEND               = 0,
    MAIL_MONEY_TAKEN        = 1,
    MAIL_ITEM_TAKEN         = 2,
    MAIL_RETURNED_TO_SENDER = 3,
    MAIL_DELETED            = 4,
    MAIL_MADE_PERMANENT     = 5
};

enum MailResponseResult
{
    MAIL_OK                            = 0,
    MAIL_ERR_EQUIP_ERROR               = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF       = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY          = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND       = 4,
    MAIL_ERR_NOT_YOUR_TEAM             = 5,
    MAIL_ERR_INTERNAL_ERROR            = 6,
    MAIL_ERR_DISABLED_FOR_TRIAL_ACC    = 14,
    MAIL_ERR_RECIPIENT_CAP_REACHED     = 15,
    MAIL_ERR_CANT_SEND_WRAPPED_COD     = 16,
    MAIL_ERR_MAIL_AND_CHAT_SUSPENDED   = 17,
    MAIL_ERR_TOO_MANY_ATTACHMENTS      = 18,
    MAIL_ERR_MAIL_ATTACHMENT_INVALID   = 19,
    MAIL_ERR_SILENT                    = 20,
    MAIL_ERR_ITEM_HAS_EXPIRED          = 21
};

enum SpellFamilyNames
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_UNK1        = 1,                            // events, holidays
    // 2 - unused
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_UNK2        = 12,                           // 2 spells (silence resistance)
    SPELLFAMILY_POTION      = 13,
    // 14 - unused
    SPELLFAMILY_DEATHKNIGHT = 15,
    // 16 - unused
    SPELLFAMILY_PET         = 17,
    SPELLFAMILY_TOTEMS      = 50,
    SPELLFAMILY_MONK        = 53,
    SPELLFAMILY_WARLOCK_PET = 57
};

enum TradeStatus
{
    TRADE_STATUS_FAILED                = 0,
    TRADE_STATUS_TARGET_STUNNED        = 1,
    TRADE_STATUS_INITIATED             = 2,
    TRADE_STATUS_CURRENCY_NOT_TRADABLE = 3,
    TRADE_STATUS_PLAYER_NOT_FOUND      = 4,
    TRADE_STATUS_TOO_FAR_AWAY          = 5,
    TRADE_STATUS_ACCEPTED              = 6,
    TRADE_STATUS_DEAD                  = 7,
    TRADE_STATUS_STATE_CHANGED         = 9,
    TRADE_STATUS_WRONG_FACTION         = 10,
    TRADE_STATUS_ALREADY_TRADING       = 11,
    TRADE_STATUS_RESTRICTED_ACCOUNT    = 13,
    TRADE_STATUS_COMPLETE              = 14,
    TRADE_STATUS_LOGGING_OUT           = 15,
    TRADE_STATUS_PLAYER_IGNORED        = 16,
    TRADE_STATUS_TARGET_LOGGING_OUT    = 17,
    TRADE_STATUS_PETITION              = 18,
    TRADE_STATUS_STUNNED               = 20,
    TRADE_STATUS_PLAYER_BUSY           = 21,
    TRADE_STATUS_WRONG_REALM           = 22,
    TRADE_STATUS_NOT_ENOUGH_CURRENCY   = 23,
    TRADE_STATUS_PROPOSED              = 24,
    TRADE_STATUS_UNACCEPTED            = 27,
    TRADE_STATUS_TARGET_DEAD           = 28,
    TRADE_STATUS_CANCELLED             = 30,
    TRADE_STATUS_NOT_ON_TAPLIST        = 31,
};

enum XPColorChar
{
    XP_RED,
    XP_ORANGE,
    XP_YELLOW,
    XP_GREEN,
    XP_GRAY
};

enum RemoveMethod
{
    GROUP_REMOVEMETHOD_DEFAULT  = 0,
    GROUP_REMOVEMETHOD_KICK     = 1,
    GROUP_REMOVEMETHOD_LEAVE    = 2,
    GROUP_REMOVEMETHOD_KICK_LFG = 3
};

enum ActivateTaxiReply
{
    ERR_UNK_1                         = 0,
    ERR_UNK_2                         = 1,
    ERR_TAXI_SAME_NODE                = 2,  // You are already there!
    ERR_TAXI_PLAYER_MOVING            = 3,  // You are moving!
    ERR_TAXI_NOT_ENOUGH_MONEY         = 4,  // You don`t have enough money!
    ERR_TAXI_UNSPECIFIED_SERVER_ERROR = 5,  // UNSPECIFIED TAXI SERVER ERROR
    ERR_TAXI_NO_SUCH_PATH             = 6,  // There is no direct path to that destination!
    ERR_TAXI_PLAYER_ALREADY_MOUNTED   = 7,  // You are already mounted! Dismount first!
    ERR_TAXI_OK                       = 8,
    ERR_TAXI_PLAYER_SHAPESHIFTED      = 9,  // You can`t take taxi while shapeshifted!
    ERR_TAXI_PLAYER_BUSY              = 10, // You are busy and cant use the taxi service now!
    ERR_TAXI_NOT_STANDING             = 11, // You need to be standing to go anywhere!
    ERR_TAXI_NO_VENDOR_NEARBY         = 12, // There is no taxi vendor nearby!
    ERR_TAXI_TOO_FAR_AWAY             = 13, // You are too far away from the taxi stand!
    ERR_UNK_3                         = 14,
    ERR_TAXI_NOT_VISITED              = 15, // You haven`t reached that taxi node on foot yet!
};

enum ProfessionUI
{
    MAX_PRIMARY_PROFESSIONS = 2,
    MAX_SECONDARY_SKILLS = 5
};

enum DuelCompleteType
{
    DUEL_INTERRUPTED = 0,
    DUEL_WON         = 1,
    DUEL_FLED        = 2,
    DUEL_SURRENDER   = 3,
};
// handle the queue types and bg types separately to enable joining queue for different sized arenas at the same time
enum BattlegroundQueueTypeId
{
    BATTLEGROUND_QUEUE_NONE,
    BATTLEGROUND_QUEUE_AV,
    BATTLEGROUND_QUEUE_WS,
    BATTLEGROUND_QUEUE_AB,
    BATTLEGROUND_QUEUE_EY,
    BATTLEGROUND_QUEUE_SA,
    BATTLEGROUND_QUEUE_IC,
    BATTLEGROUND_QUEUE_TP,
    BATTLEGROUND_QUEUE_BFG,
    BATTLEGROUND_QUEUE_TOK,
    BATTLEGROUND_QUEUE_SM,
    BATTLEGROUND_QUEUE_DG,
    BATTLEGROUND_QUEUE_RB,
    BATTLEGROUND_QUEUE_2v2,
    BATTLEGROUND_QUEUE_3v3,
    BATTLEGROUND_QUEUE_5v5,
    BATTLEGORUND_QUEUE_RATED_BG,
    BATTLEGROUND_QUEUE_SOLO,
    MAX_BATTLEGROUND_QUEUE_TYPES
};

enum GroupJoinBattlegroundResult
{
    ERR_BATTLEGROUND_NONE                           = 0,
    ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS           = 2,        // You cannot join the battleground yet because you or one of your party members is flagged as a Deserter.
    ERR_ARENA_TEAM_PARTY_SIZE                       = 3,        // Incorrect party size for this arena.
    ERR_BATTLEGROUND_TOO_MANY_QUEUES                = 4,        // You can only be queued for 2 battles at once
    ERR_BATTLEGROUND_CANNOT_QUEUE_FOR_RATED         = 5,        // You cannot queue for a rated match while queued for other battles
    ERR_BATTLEGROUND_QUEUED_FOR_RATED               = 6,        // You cannot queue for another battle while queued for a rated arena match
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE                = 7,        // Your team has left the arena queue
    ERR_BATTLEGROUND_NOT_IN_BATTLEGROUND            = 8,        // You can't do that in a battleground.
    ERR_BATTLEGROUND_JOIN_XP_GAIN                   = 9,        // wtf, doesn't exist in client...
    ERR_BATTLEGROUND_JOIN_RANGE_INDEX               = 10,       // Cannot join the queue unless all members of your party are in the same battleground level range.
    ERR_BATTLEGROUND_JOIN_TIMED_OUT                 = 11,       // %s was unavailable to join the queue. (uint64 guid exist in client cache)
    //ERR_BATTLEGROUND_JOIN_TIMED_OUT               = 12,       // same as 11
    //ERR_BATTLEGROUND_TEAM_LEFT_QUEUE              = 13,       // same as 7
    ERR_LFG_CANT_USE_BATTLEGROUND                   = 14,       // You cannot queue for a battleground or arena while using the dungeon system.
    ERR_IN_RANDOM_BG                                = 15,       // Can't do that while in a Random Battleground queue.
    ERR_IN_NON_RANDOM_BG                            = 16,       // Can't queue for Random Battleground while in another Battleground queue.
    ERR_BG_DEVELOPER_ONLY                           = 17,
    ERR_BATTLEGROUND_INVITATION_DECLINED            = 18,
    ERR_MEETING_STONE_NOT_FOUND                     = 19,
    ERR_WARGAME_REQUEST_FAILURE                     = 20,
    ERR_BATTLEFIELD_TEAM_PARTY_SIZE                 = 22,
    ERR_NOT_ON_TOURNAMENT_REALM                     = 23,
    ERR_BATTLEGROUND_PLAYERS_FROM_DIFFERENT_REALMS  = 24,
    ERR_REMOVE_FROM_PVP_QUEUE_GRANT_LEVEL           = 33,
    ERR_REMOVE_FROM_PVP_QUEUE_FACTION_CHANGE        = 34,
    ERR_BATTLEGROUND_JOIN_FAILED                    = 35,
    ERR_BATTLEGROUND_DUPE_QUEUE                     = 43
};

enum PetNameInvalidReason
{
    // custom, not send
    PET_NAME_SUCCESS                                        = 0,

    PET_NAME_INVALID                                        = 1,
    PET_NAME_NO_NAME                                        = 2,
    PET_NAME_TOO_SHORT                                      = 3,
    PET_NAME_TOO_LONG                                       = 4,
    PET_NAME_MIXED_LANGUAGES                                = 6,
    PET_NAME_PROFANE                                        = 7,
    PET_NAME_RESERVED                                       = 8,
    PET_NAME_THREE_CONSECUTIVE                              = 11,
    PET_NAME_INVALID_SPACE                                  = 12,
    PET_NAME_CONSECUTIVE_SPACES                             = 13,
    PET_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS          = 14,
    PET_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END   = 15,
    PET_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME              = 16
};

enum DungeonStatusFlag
{
    DUNGEON_STATUSFLAG_NORMAL    = 0x01,
    DUNGEON_STATUSFLAG_HEROIC    = 0x02,
    DUNGEON_STATUSFLAG_CHALLENGE = 0x04,

    RAID_STATUSFLAG_10MAN_NORMAL = 0x01,
    RAID_STATUSFLAG_25MAN_NORMAL = 0x02,
    RAID_STATUSFLAG_10MAN_HEROIC = 0x04,
    RAID_STATUSFLAG_25MAN_HEROIC = 0x08,
    RAID_STATUSFLAG_1025MAN_FLEX = 0x10,
    RAID_STATUSFLAG_25MAN_LFR    = 0x20,
    RAID_STATUSFLAG_40MAN        = 0x40,

    SCENARIO_STATUSFLAG_NORMAL   = 0x01,
    SCENARIO_STATUSFLAG_HEROIC   = 0x02
};

#define VOID_STORAGE_UNLOCK       100*GOLD
#define VOID_STORAGE_STORE_ITEM   25*GOLD
#define VOID_STORAGE_MAX_DEPOSIT  9
#define VOID_STORAGE_MAX_WITHDRAW 9
#define VOID_STORAGE_MAX_SLOT     80

enum VoidTransferError
{
    VOID_TRANSFER_ERROR_NO_ERROR          = 0,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_1  = 1, // Internal void storage Error.
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_2  = 2, // Internal void storage Error.
    VOID_TRANSFER_ERROR_FULL              = 3, // There is not enough room in void storage to complete the deposit.
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_3  = 4, // Internal void storage Error.
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_4  = 5, // Internal void storage Error.
    VOID_TRANSFER_ERROR_NOT_ENOUGH_MONEY  = 6, // You don't have enough money.
    VOID_TRANSFER_ERROR_INVENTORY_FULL    = 7, // There is not enough room in your bags to complete the withdrawal.
    VOID_TRANSFER_ERROR_INELIGIBLE_ITEMS  = 8, // One or more of your items are ineligible to be deposited into void storage.
    VOID_TRANSFER_ERROR_TRANSFER_UNKNOWN  = 9,
};

#define CURRENCY_PRECISION 100

enum PartyResult
{
    ERR_PARTY_RESULT_OK                 = 0,
    ERR_BAD_PLAYER_NAME_S               = 1,
    ERR_TARGET_NOT_IN_GROUP_S           = 2,
    ERR_TARGET_NOT_IN_INSTANCE_S        = 3,
    ERR_GROUP_FULL                      = 4,
    ERR_ALREADY_IN_GROUP_S              = 5,
    ERR_NOT_IN_GROUP                    = 6,
    ERR_NOT_LEADER                      = 7,
    ERR_PLAYER_WRONG_FACTION            = 8,
    ERR_IGNORING_YOU_S                  = 9,
    ERR_LFG_PENDING                     = 12,
    ERR_INVITE_RESTRICTED               = 13,
    ERR_GROUP_SWAP_FAILED               = 14,               // if (PartyOperation == PARTY_OP_SWAP) ERR_GROUP_SWAP_FAILED else ERR_INVITE_IN_COMBAT
    ERR_INVITE_UNKNOWN_REALM            = 15,
    ERR_INVITE_NO_PARTY_SERVER          = 16,
    ERR_INVITE_PARTY_BUSY               = 17,
    ERR_PARTY_TARGET_AMBIGUOUS          = 18,
    ERR_PARTY_LFG_INVITE_RAID_LOCKED    = 19,
    ERR_PARTY_LFG_BOOT_LIMIT            = 20,
    ERR_PARTY_LFG_BOOT_COOLDOWN_S       = 21,
    ERR_PARTY_LFG_BOOT_IN_PROGRESS      = 22,
    ERR_PARTY_LFG_BOOT_TOO_FEW_PLAYERS  = 23,
    ERR_PARTY_LFG_BOOT_NOT_ELIGIBLE_S   = 24,
    ERR_RAID_DISALLOWED_BY_LEVEL        = 25,
    ERR_PARTY_LFG_BOOT_IN_COMBAT        = 26,
    ERR_VOTE_KICK_REASON_NEEDED         = 27,
    ERR_PARTY_LFG_BOOT_DUNGEON_COMPLETE = 28,
    ERR_PARTY_LFG_BOOT_LOOT_ROLLS       = 29,
    ERR_PARTY_LFG_TELEPORT_IN_COMBAT    = 30
};

const uint32 MMAP_MAGIC = 0x4d4d4150; // 'MMAP'
#define MMAP_VERSION 7

struct MmapTileHeader
{
    uint32 mmapMagic;
    uint32 dtVersion;
    uint32 mmapVersion;
    uint32 size;
    bool usesLiquids : 1;

    MmapTileHeader() : mmapMagic(MMAP_MAGIC), dtVersion(DT_NAVMESH_VERSION),
        mmapVersion(MMAP_VERSION), size(0), usesLiquids(true) { }
};

enum NavTerrain
{
    NAV_EMPTY   = 0x00,
    NAV_GROUND  = 0x01,
    NAV_MAGMA   = 0x02,
    NAV_SLIME   = 0x04,
    NAV_WATER   = 0x08,
    NAV_UNUSED1 = 0x10,
    NAV_UNUSED2 = 0x20,
    NAV_UNUSED3 = 0x40,
    NAV_UNUSED4 = 0x80
    // we only have 8 bits
};

enum DiminishingLevels
{
    DIMINISHING_LEVEL_1             = 0,
    DIMINISHING_LEVEL_2             = 1,
    DIMINISHING_LEVEL_3             = 2,
    DIMINISHING_LEVEL_IMMUNE        = 3,
    DIMINISHING_LEVEL_4             = 3,
    DIMINISHING_LEVEL_TAUNT_IMMUNE  = 4
};

enum class GameError
{
    ERR_INV_FULL                                               = 0,
    ERR_BANK_FULL                                              = 1,
    ERR_CANT_EQUIP_LEVEL_I                                     = 2,
    ERR_CANT_EQUIP_SKILL                                       = 3,
    ERR_CANT_EQUIP_EVER                                        = 4,
    ERR_CANT_EQUIP_RANK                                        = 5,
    ERR_CANT_EQUIP_RATING                                      = 6,
    ERR_CANT_EQUIP_REPUTATION                                  = 7,
    ERR_PROFICIENCY_NEEDED                                     = 8,
    ERR_WRONG_SLOT                                             = 9,
    ERR_CANT_EQUIP_NEED_TALENT                                 = 10,
    ERR_BAG_FULL                                               = 11,
    ERR_INTERNAL_BAG_ERROR                                     = 12,
    ERR_DESTROY_NONEMPTY_BAG                                   = 13,
    ERR_BAG_IN_BAG                                             = 14,
    ERR_TOO_MANY_SPECIAL_BAGS                                  = 15,
    ERR_TRADE_EQUIPPED_BAG                                     = 16,
    ERR_AMMO_ONLY                                              = 17,
    ERR_NO_SLOT_AVAILABLE                                      = 18,
    ERR_WRONG_BAG_TYPE                                         = 19,
    ERR_ITEM_MAX_COUNT                                         = 20,
    ERR_NOT_EQUIPPABLE                                         = 21,
    ERR_CANT_STACK                                             = 22,
    ERR_CANT_SWAP                                              = 23,
    ERR_SLOT_EMPTY                                             = 24,
    ERR_ITEM_NOT_FOUND                                         = 25,
    ERR_TOO_FEW_TO_SPLIT                                       = 26,
    ERR_SPLIT_FAILED                                           = 27,
    ERR_NOT_A_BAG                                              = 28,
    ERR_NOT_OWNER                                              = 29,
    ERR_ONLY_ONE_QUIVER                                        = 30,
    ERR_NO_BANK_SLOT                                           = 31,
    ERR_NO_BANK_HERE                                           = 32,
    ERR_ITEM_LOCKED                                            = 33,
    ERR_2HANDED_EQUIPPED                                       = 34,
    ERR_VENDOR_NOT_INTERESTED                                  = 35,
    ERR_VENDOR_HATES_YOU                                       = 36,
    ERR_VENDOR_SOLD_OUT                                        = 37,
    ERR_VENDOR_TOO_FAR                                         = 38,
    ERR_VENDOR_DOESNT_BUY                                      = 39,
    ERR_NOT_ENOUGH_MONEY                                       = 40,
    ERR_RECEIVE_ITEM_S                                         = 41,
    ERR_DROP_BOUND_ITEM                                        = 42,
    ERR_TRADE_BOUND_ITEM                                       = 43,
    ERR_TRADE_QUEST_ITEM                                       = 44,
    ERR_TRADE_TEMP_ENCHANT_BOUND                               = 45,
    ERR_TRADE_GROUND_ITEM                                      = 46,
    ERR_TRADE_BAG                                              = 47,
    ERR_SPELL_FAILED_S                                         = 48,
    ERR_ITEM_COOLDOWN                                          = 49,
    ERR_POTION_COOLDOWN                                        = 50,
    ERR_FOOD_COOLDOWN                                          = 51,
    ERR_SPELL_COOLDOWN                                         = 52,
    ERR_ABILITY_COOLDOWN                                       = 53,
    ERR_SPELL_ALREADY_KNOWN_S                                  = 54,
    ERR_PET_SPELL_ALREADY_KNOWN_S                              = 55,
    ERR_PROFICIENCY_GAINED_S                                   = 56,
    ERR_SKILL_GAINED_S                                         = 57,
    ERR_SKILL_UP_SI                                            = 58,
    ERR_LEARN_SPELL_S                                          = 59,
    ERR_LEARN_ABILITY_S                                        = 60,
    ERR_LEARN_PASSIVE_S                                        = 61,
    ERR_LEARN_RECIPE_S                                         = 62,
    ERR_LEARN_COMPANION_S                                      = 63,
    ERR_LEARN_MOUNT_S                                          = 64,
    ERR_INVITE_PLAYER_S                                        = 65,
    ERR_INVITE_SELF                                            = 66,
    ERR_INVITED_TO_GROUP_SS                                    = 67,
    ERR_INVITED_ALREADY_IN_GROUP_SS                            = 68,
    ERR_ALREADY_IN_GROUP_S                                     = 69,
    ERR_CROSS_REALM_RAID_INVITE                                = 70,
    ERR_PLAYER_BUSY_S                                          = 71,
    ERR_NEW_LEADER_S                                           = 72,
    ERR_NEW_LEADER_YOU                                         = 73,
    ERR_NEW_GUIDE_S                                            = 74,
    ERR_NEW_GUIDE_YOU                                          = 75,
    ERR_LEFT_GROUP_S                                           = 76,
    ERR_LEFT_GROUP_YOU                                         = 77,
    ERR_GROUP_DISBANDED                                        = 78,
    ERR_DECLINE_GROUP_S                                        = 79,
    ERR_JOINED_GROUP_S                                         = 80,
    ERR_UNINVITE_YOU                                           = 81,
    ERR_BAD_PLAYER_NAME_S                                      = 82,
    ERR_NOT_IN_GROUP                                           = 83,
    ERR_TARGET_NOT_IN_GROUP_S                                  = 84,
    ERR_TARGET_NOT_IN_INSTANCE_S                               = 85,
    ERR_NOT_IN_INSTANCE_GROUP                                  = 86,
    ERR_GROUP_FULL                                             = 87,
    ERR_NOT_LEADER                                             = 88,
    ERR_PLAYER_DIED_S                                          = 89,
    ERR_GUILD_CREATE_S                                         = 90,
    ERR_GUILD_INVITE_S                                         = 91,
    ERR_INVITED_TO_GUILD_SSS                                   = 92,
    ERR_ALREADY_IN_GUILD_S                                     = 93,
    ERR_ALREADY_INVITED_TO_GUILD_S                             = 94,
    ERR_INVITED_TO_GUILD                                       = 95,
    ERR_ALREADY_IN_GUILD                                       = 96,
    ERR_GUILD_ACCEPT                                           = 97,
    ERR_GUILD_DECLINE_S                                        = 98,
    ERR_GUILD_DECLINE_AUTO_S                                   = 99,
    ERR_GUILD_PERMISSIONS                                      = 100,
    ERR_GUILD_JOIN_S                                           = 101,
    ERR_GUILD_FOUNDER_S                                        = 102,
    ERR_GUILD_PROMOTE_SSS                                      = 103,
    ERR_GUILD_DEMOTE_SS                                        = 104,
    ERR_GUILD_DEMOTE_SSS                                       = 105,
    ERR_GUILD_INVITE_SELF                                      = 106,
    ERR_GUILD_QUIT_S                                           = 107,
    ERR_GUILD_LEAVE_S                                          = 108,
    ERR_GUILD_REMOVE_SS                                        = 109,
    ERR_GUILD_REMOVE_SELF                                      = 110,
    ERR_GUILD_DISBAND_S                                        = 111,
    ERR_GUILD_DISBAND_SELF                                     = 112,
    ERR_GUILD_LEADER_S                                         = 113,
    ERR_GUILD_LEADER_SELF                                      = 114,
    ERR_GUILD_PLAYER_NOT_FOUND_S                               = 115,
    ERR_GUILD_PLAYER_NOT_IN_GUILD_S                            = 116,
    ERR_GUILD_PLAYER_NOT_IN_GUILD                              = 117,
    ERR_GUILD_CANT_PROMOTE_S                                   = 118,
    ERR_GUILD_CANT_DEMOTE_S                                    = 119,
    ERR_GUILD_NOT_IN_A_GUILD                                   = 120,
    ERR_GUILD_INTERNAL                                         = 121,
    ERR_GUILD_LEADER_IS_S                                      = 122,
    ERR_GUILD_LEADER_CHANGED_SS                                = 123,
    ERR_GUILD_DISBANDED                                        = 124,
    ERR_GUILD_NOT_ALLIED                                       = 125,
    ERR_GUILD_LEADER_LEAVE                                     = 126,
    ERR_GUILD_RANKS_LOCKED                                     = 127,
    ERR_GUILD_RANK_IN_USE                                      = 128,
    ERR_GUILD_RANK_TOO_HIGH_S                                  = 129,
    ERR_GUILD_RANK_TOO_LOW_S                                   = 130,
    ERR_GUILD_NAME_EXISTS_S                                    = 131,
    ERR_GUILD_WITHDRAW_LIMIT                                   = 132,
    ERR_GUILD_NOT_ENOUGH_MONEY                                 = 133,
    ERR_GUILD_TOO_MUCH_MONEY                                   = 134,
    ERR_GUILD_BANK_CONJURED_ITEM                               = 135,
    ERR_GUILD_BANK_EQUIPPED_ITEM                               = 136,
    ERR_GUILD_BANK_BOUND_ITEM                                  = 137,
    ERR_GUILD_BANK_QUEST_ITEM                                  = 138,
    ERR_GUILD_BANK_WRAPPED_ITEM                                = 139,
    ERR_GUILD_BANK_FULL                                        = 140,
    ERR_GUILD_BANK_WRONG_TAB                                   = 141,
    ERR_NO_GUILD_CHARTER                                       = 142,
    ERR_OUT_OF_RANGE                                           = 143,
    ERR_PLAYER_DEAD                                            = 144,
    ERR_CLIENT_LOCKED_OUT                                      = 145,
    ERR_KILLED_BY_S                                            = 146,
    ERR_LOOT_LOCKED                                            = 147,
    ERR_LOOT_TOO_FAR                                           = 148,
    ERR_LOOT_DIDNT_KILL                                        = 149,
    ERR_LOOT_BAD_FACING                                        = 150,
    ERR_LOOT_NOTSTANDING                                       = 151,
    ERR_LOOT_STUNNED                                           = 152,
    ERR_LOOT_NO_UI                                             = 153,
    ERR_LOOT_WHILE_INVULNERABLE                                = 154,
    ERR_NO_LOOT                                                = 155,
    ERR_QUEST_ACCEPTED_S                                       = 156,
    ERR_QUEST_COMPLETE_S                                       = 157,
    ERR_QUEST_FAILED_S                                         = 158,
    ERR_QUEST_FAILED_BAG_FULL_S                                = 159,
    ERR_QUEST_FAILED_MAX_COUNT_S                               = 160,
    ERR_QUEST_FAILED_LOW_LEVEL                                 = 161,
    ERR_QUEST_FAILED_MISSING_ITEMS                             = 162,
    ERR_QUEST_FAILED_WRONG_RACE                                = 163,
    ERR_QUEST_FAILED_NOT_ENOUGH_MONEY                          = 164,
    ERR_QUEST_FAILED_EXPANSION                                 = 165,
    ERR_QUEST_ONLY_ONE_TIMED                                   = 166,
    ERR_QUEST_NEED_PREREQS                                     = 167,
    ERR_QUEST_NEED_PREREQS_CUSTOM                              = 168,
    ERR_QUEST_ALREADY_ON                                       = 169,
    ERR_QUEST_ALREADY_DONE                                     = 170,
    ERR_QUEST_ALREADY_DONE_DAILY                               = 171,
    ERR_QUEST_REWARD_EXP_I                                     = 172,
    ERR_QUEST_REWARD_ITEM_S                                    = 173,
    ERR_QUEST_REWARD_ITEM_MULT_IS                              = 174,
    ERR_QUEST_REWARD_MONEY_S                                   = 175,
    ERR_QUEST_MUST_CHOOSE                                      = 176,
    ERR_QUEST_LOG_FULL                                         = 177,
    ERR_COMBAT_DAMAGE_SSI                                      = 178,
    ERR_INSPECT_S                                              = 179,
    ERR_CANT_USE_ITEM                                          = 180,
    ERR_CANT_USE_ITEM_IN_ARENA                                 = 181,
    ERR_CANT_USE_ITEM_IN_RATED_BATTLEGROUND                    = 182,
    ERR_MUST_EQUIP_ITEM                                        = 183,
    ERR_PASSIVE_ABILITY                                        = 184,
    ERR_2HSKILLNOTFOUND                                        = 185,
    ERR_NO_ATTACK_TARGET                                       = 186,
    ERR_INVALID_ATTACK_TARGET                                  = 187,
    ERR_ATTACK_STUNNED                                         = 188,
    ERR_ATTACK_PACIFIED                                        = 189,
    ERR_ATTACK_MOUNTED                                         = 190,
    ERR_ATTACK_FLEEING                                         = 191,
    ERR_ATTACK_CONFUSED                                        = 192,
    ERR_ATTACK_CHARMED                                         = 193,
    ERR_ATTACK_DEAD                                            = 194,
    ERR_ATTACK_PREVENTED_BY_MECHANIC_S                         = 195,
    ERR_ATTACK_CHANNEL                                         = 196,
    ERR_TAXI_SAME_NODE                                         = 197,
    ERR_TAXI_NO_SUCH_PATH                                      = 198,
    ERR_TAXI_UNSPECIFIED_SERVER_ERROR                          = 199,
    ERR_TAXI_NOT_ENOUGH_MONEY                                  = 200,
    ERR_TAXI_TOO_FAR_AWAY                                      = 201,
    ERR_TAXI_NO_VENDOR_NEARBY                                  = 202,
    ERR_TAXI_NOT_VISITED                                       = 203,
    ERR_TAXI_PLAYER_BUSY                                       = 204,
    ERR_TAXI_PLAYER_ALREADY_MOUNTED                            = 205,
    ERR_TAXI_PLAYER_SHAPESHIFTED                               = 206,
    ERR_TAXI_PLAYER_MOVING                                     = 207,
    ERR_TAXI_NO_PATHS                                          = 208,
    ERR_TAXI_NOT_ELIGIBLE                                      = 209,
    ERR_TAXI_NOT_STANDING                                      = 210,
    ERR_NO_REPLY_TARGET                                        = 211,
    ERR_GENERIC_NO_TARGET                                      = 212,
    ERR_INITIATE_TRADE_S                                       = 213,
    ERR_TRADE_REQUEST_S                                        = 214,
    ERR_TRADE_BLOCKED_S                                        = 215,
    ERR_TRADE_TARGET_DEAD                                      = 216,
    ERR_TRADE_TOO_FAR                                          = 217,
    ERR_TRADE_CANCELLED                                        = 218,
    ERR_TRADE_COMPLETE                                         = 219,
    ERR_TRADE_BAG_FULL                                         = 220,
    ERR_TRADE_TARGET_BAG_FULL                                  = 221,
    ERR_TRADE_MAX_COUNT_EXCEEDED                               = 222,
    ERR_TRADE_TARGET_MAX_COUNT_EXCEEDED                        = 223,
    ERR_ALREADY_TRADING                                        = 224,
    ERR_MOUNT_INVALIDMOUNTEE                                   = 225,
    ERR_MOUNT_TOOFARAWAY                                       = 226,
    ERR_MOUNT_ALREADYMOUNTED                                   = 227,
    ERR_MOUNT_NOTMOUNTABLE                                     = 228,
    ERR_MOUNT_NOTYOURPET                                       = 229,
    ERR_MOUNT_OTHER                                            = 230,
    ERR_MOUNT_LOOTING                                          = 231,
    ERR_MOUNT_RACECANTMOUNT                                    = 232,
    ERR_MOUNT_SHAPESHIFTED                                     = 233,
    ERR_DISMOUNT_NOPET                                         = 234,
    ERR_DISMOUNT_NOTMOUNTED                                    = 235,
    ERR_DISMOUNT_NOTYOURPET                                    = 236,
    ERR_SPELL_FAILED_TOTEMS                                    = 237,
    ERR_SPELL_FAILED_REAGENTS                                  = 238,
    ERR_SPELL_FAILED_REAGENTS_GENERIC                          = 239,
    ERR_SPELL_FAILED_EQUIPPED_ITEM                             = 240,
    ERR_SPELL_FAILED_EQUIPPED_ITEM_CLASS_S                     = 241,
    ERR_SPELL_FAILED_SHAPESHIFT_FORM_S                         = 242,
    ERR_BADATTACKFACING                                        = 243,
    ERR_BADATTACKPOS                                           = 244,
    ERR_CHEST_IN_USE                                           = 245,
    ERR_USE_CANT_OPEN                                          = 246,
    ERR_USE_LOCKED                                             = 247,
    ERR_DOOR_LOCKED                                            = 248,
    ERR_BUTTON_LOCKED                                          = 249,
    ERR_USE_LOCKED_WITH_ITEM_S                                 = 250,
    ERR_USE_LOCKED_WITH_SPELL_S                                = 251,
    ERR_USE_LOCKED_WITH_SPELL_KNOWN_SI                         = 252,
    ERR_USE_TOO_FAR                                            = 253,
    ERR_USE_BAD_ANGLE                                          = 254,
    ERR_USE_OBJECT_MOVING                                      = 255,
    ERR_USE_SPELL_FOCUS                                        = 256,
    ERR_USE_DESTROYED                                          = 257,
    ERR_SET_LOOT_FREEFORALL                                    = 258,
    ERR_SET_LOOT_ROUNDROBIN                                    = 259,
    ERR_SET_LOOT_MASTER                                        = 260,
    ERR_SET_LOOT_GROUP                                         = 261,
    ERR_SET_LOOT_NBG                                           = 262,
    ERR_SET_LOOT_THRESHOLD_S                                   = 263,
    ERR_NEW_LOOT_MASTER_S                                      = 264,
    ERR_SPECIFY_MASTER_LOOTER                                  = 265,
    ERR_LOOT_SPEC_CHANGED_S                                    = 266,
    ERR_TAME_FAILED                                            = 267,
    ERR_CHAT_WHILE_DEAD                                        = 268,
    ERR_CHAT_PLAYER_NOT_FOUND_S                                = 269,
    ERR_NEWTAXIPATH                                            = 270,
    ERR_NO_PET                                                 = 271,
    ERR_NOTYOURPET                                             = 272,
    ERR_PET_NOT_RENAMEABLE                                     = 273,
    ERR_QUEST_OBJECTIVE_COMPLETE_S                             = 274,
    ERR_QUEST_UNKNOWN_COMPLETE                                 = 275,
    ERR_QUEST_ADD_KILL_SII                                     = 276,
    ERR_QUEST_ADD_FOUND_SII                                    = 277,
    ERR_QUEST_ADD_ITEM_SII                                     = 278,
    ERR_QUEST_ADD_PLAYER_KILL_SII                              = 279,
    ERR_CANNOTCREATEDIRECTORY                                  = 280,
    ERR_CANNOTCREATEFILE                                       = 281,
    ERR_PLAYER_WRONG_FACTION                                   = 282,
    ERR_PLAYER_IS_NEUTRAL                                      = 283,
    ERR_BANKSLOT_FAILED_TOO_MANY                               = 284,
    ERR_BANKSLOT_INSUFFICIENT_FUNDS                            = 285,
    ERR_BANKSLOT_NOTBANKER                                     = 286,
    ERR_FRIEND_DB_ERROR                                        = 287,
    ERR_FRIEND_LIST_FULL                                       = 288,
    ERR_FRIEND_ADDED_S                                         = 289,
    ERR_BATTLETAG_FRIEND_ADDED_S                               = 290,
    ERR_FRIEND_ONLINE_SS                                       = 291,
    ERR_FRIEND_OFFLINE_S                                       = 292,
    ERR_FRIEND_NOT_FOUND                                       = 293,
    ERR_FRIEND_WRONG_FACTION                                   = 294,
    ERR_FRIEND_REMOVED_S                                       = 295,
    ERR_BATTLETAG_FRIEND_REMOVED_S                             = 296,
    ERR_FRIEND_ERROR                                           = 297,
    ERR_FRIEND_ALREADY_S                                       = 298,
    ERR_FRIEND_SELF                                            = 299,
    ERR_FRIEND_DELETED                                         = 300,
    ERR_IGNORE_FULL                                            = 301,
    ERR_IGNORE_SELF                                            = 302,
    ERR_IGNORE_NOT_FOUND                                       = 303,
    ERR_IGNORE_ALREADY_S                                       = 304,
    ERR_IGNORE_ADDED_S                                         = 305,
    ERR_IGNORE_REMOVED_S                                       = 306,
    ERR_IGNORE_AMBIGUOUS                                       = 307,
    ERR_IGNORE_DELETED                                         = 308,
    ERR_ONLY_ONE_BOLT                                          = 309,
    ERR_ONLY_ONE_AMMO                                          = 310,
    ERR_SPELL_FAILED_EQUIPPED_SPECIFIC_ITEM                    = 311,
    ERR_WRONG_BAG_TYPE_SUBCLASS                                = 312,
    ERR_CANT_WRAP_STACKABLE                                    = 313,
    ERR_CANT_WRAP_EQUIPPED                                     = 314,
    ERR_CANT_WRAP_WRAPPED                                      = 315,
    ERR_CANT_WRAP_BOUND                                        = 316,
    ERR_CANT_WRAP_UNIQUE                                       = 317,
    ERR_CANT_WRAP_BAGS                                         = 318,
    ERR_OUT_OF_MANA                                            = 319,
    ERR_OUT_OF_RAGE                                            = 320,
    ERR_OUT_OF_FOCUS                                           = 321,
    ERR_OUT_OF_ENERGY                                          = 322,
    ERR_OUT_OF_CHI                                             = 323,
    ERR_OUT_OF_HEALTH                                          = 324,
    ERR_OUT_OF_RUNES                                           = 325,
    ERR_OUT_OF_RUNIC_POWER                                     = 326,
    ERR_OUT_OF_SOUL_SHARDS                                     = 327,
    ERR_OUT_OF_BALANCE_POSITIVE                                = 328,
    ERR_OUT_OF_BALANCE_NEGATIVE                                = 329,
    ERR_OUT_OF_HOLY_POWER                                      = 330,
    ERR_OUT_OF_DARK_FORCE                                      = 331,
    ERR_OUT_OF_LIGHT_FORCE                                     = 332,
    ERR_OUT_OF_SHADOW_ORBS                                     = 333,
    ERR_OUT_OF_BURNING_EMBERS                                  = 334,
    ERR_OUT_OF_DEMONIC_FURY                                    = 335,
    ERR_OUT_OF_ARCANE_CHARGES                                  = 336,
    ERR_OUT_OF_POWER_DISPLAY                                   = 337,
    ERR_LOOT_GONE                                              = 338,
    ERR_MOUNT_FORCEDDISMOUNT                                   = 339,
    ERR_AUTOFOLLOW_TOO_FAR                                     = 340,
    ERR_UNIT_NOT_FOUND                                         = 341,
    ERR_INVALID_FOLLOW_TARGET                                  = 342,
    ERR_INVALID_INSPECT_TARGET                                 = 343,
    ERR_GUILDEMBLEM_SUCCESS                                    = 344,
    ERR_GUILDEMBLEM_INVALID_TABARD_COLORS                      = 345,
    ERR_GUILDEMBLEM_NOGUILD                                    = 346,
    ERR_GUILDEMBLEM_NOTGUILDMASTER                             = 347,
    ERR_GUILDEMBLEM_NOTENOUGHMONEY                             = 348,
    ERR_GUILDEMBLEM_INVALIDVENDOR                              = 349,
    ERR_EMBLEMERROR_NOTABARDGEOSET                             = 350,
    ERR_SPELL_OUT_OF_RANGE                                     = 351,
    ERR_COMMAND_NEEDS_TARGET                                   = 352,
    ERR_NOAMMO_S                                               = 353,
    ERR_TOOBUSYTOFOLLOW                                        = 354,
    ERR_DUEL_REQUESTED                                         = 355,
    ERR_DUEL_CANCELLED                                         = 356,
    ERR_DEATHBINDALREADYBOUND                                  = 357,
    ERR_DEATHBIND_SUCCESS_S                                    = 358,
    ERR_NOEMOTEWHILERUNNING                                    = 359,
    ERR_ZONE_EXPLORED                                          = 360,
    ERR_ZONE_EXPLORED_XP                                       = 361,
    ERR_INVALID_ITEM_TARGET                                    = 362,
    ERR_IGNORING_YOU_S                                         = 363,
    ERR_FISH_NOT_HOOKED                                        = 364,
    ERR_FISH_ESCAPED                                           = 365,
    ERR_SPELL_FAILED_NOTUNSHEATHED                             = 366,
    ERR_PETITION_OFFERED_S                                     = 367,
    ERR_PETITION_SIGNED                                        = 368,
    ERR_PETITION_SIGNED_S                                      = 369,
    ERR_PETITION_DECLINED_S                                    = 370,
    ERR_PETITION_ALREADY_SIGNED                                = 371,
    ERR_PETITION_RESTRICTED_ACCOUNT                            = 372,
    ERR_PETITION_ALREADY_SIGNED_OTHER                          = 373,
    ERR_PETITION_IN_GUILD                                      = 374,
    ERR_PETITION_CREATOR                                       = 375,
    ERR_PETITION_NOT_ENOUGH_SIGNATURES                         = 376,
    ERR_PETITION_NOT_SAME_SERVER                               = 377,
    ERR_PETITION_FULL                                          = 378,
    ERR_PETITION_ALREADY_SIGNED_BY_S                           = 379,
    ERR_GUILD_NAME_INVALID                                     = 380,
    ERR_SPELL_UNLEARNED_S                                      = 381,
    ERR_PET_SPELL_ROOTED                                       = 382,
    ERR_PET_SPELL_AFFECTING_COMBAT                             = 383,
    ERR_PET_SPELL_OUT_OF_RANGE                                 = 384,
    ERR_PET_SPELL_NOT_BEHIND                                   = 385,
    ERR_PET_SPELL_TARGETS_DEAD                                 = 386,
    ERR_PET_SPELL_DEAD                                         = 387,
    ERR_PET_SPELL_NOPATH                                       = 388,
    ERR_ITEM_CANT_BE_DESTROYED                                 = 389,
    ERR_TICKET_ALREADY_EXISTS                                  = 390,
    ERR_TICKET_CREATE_ERROR                                    = 391,
    ERR_TICKET_UPDATE_ERROR                                    = 392,
    ERR_TICKET_DB_ERROR                                        = 393,
    ERR_TICKET_NO_TEXT                                         = 394,
    ERR_TICKET_TEXT_TOO_LONG                                   = 395,
    ERR_OBJECT_IS_BUSY                                         = 396,
    ERR_EXHAUSTION_WELLRESTED                                  = 397,
    ERR_EXHAUSTION_RESTED                                      = 398,
    ERR_EXHAUSTION_NORMAL                                      = 399,
    ERR_EXHAUSTION_TIRED                                       = 400,
    ERR_EXHAUSTION_EXHAUSTED                                   = 401,
    ERR_NO_ITEMS_WHILE_SHAPESHIFTED                            = 402,
    ERR_CANT_INTERACT_SHAPESHIFTED                             = 403,
    ERR_REALM_NOT_FOUND                                        = 404,
    ERR_MAIL_QUEST_ITEM                                        = 405,
    ERR_MAIL_BOUND_ITEM                                        = 406,
    ERR_MAIL_CONJURED_ITEM                                     = 407,
    ERR_MAIL_BAG                                               = 408,
    ERR_MAIL_TO_SELF                                           = 409,
    ERR_MAIL_TARGET_NOT_FOUND                                  = 410,
    ERR_MAIL_DATABASE_ERROR                                    = 411,
    ERR_MAIL_DELETE_ITEM_ERROR                                 = 412,
    ERR_MAIL_WRAPPED_COD                                       = 413,
    ERR_MAIL_CANT_SEND_REALM                                   = 414,
    ERR_MAIL_SENT                                              = 415,
    ERR_NOT_HAPPY_ENOUGH                                       = 416,
    ERR_USE_CANT_IMMUNE                                        = 417,
    ERR_CANT_BE_DISENCHANTED                                   = 418,
    ERR_CANT_USE_DISARMED                                      = 419,
    ERR_AUCTION_QUEST_ITEM                                     = 420,
    ERR_AUCTION_BOUND_ITEM                                     = 421,
    ERR_AUCTION_CONJURED_ITEM                                  = 422,
    ERR_AUCTION_LIMITED_DURATION_ITEM                          = 423,
    ERR_AUCTION_WRAPPED_ITEM                                   = 424,
    ERR_AUCTION_LOOT_ITEM                                      = 425,
    ERR_AUCTION_BAG                                            = 426,
    ERR_AUCTION_EQUIPPED_BAG                                   = 427,
    ERR_AUCTION_DATABASE_ERROR                                 = 428,
    ERR_AUCTION_BID_OWN                                        = 429,
    ERR_AUCTION_BID_INCREMENT                                  = 430,
    ERR_AUCTION_HIGHER_BID                                     = 431,
    ERR_AUCTION_MIN_BID                                        = 432,
    ERR_AUCTION_REPAIR_ITEM                                    = 433,
    ERR_AUCTION_USED_CHARGES                                   = 434,
    ERR_AUCTION_ALREADY_BID                                    = 435,
    ERR_AUCTION_STARTED                                        = 436,
    ERR_AUCTION_REMOVED                                        = 437,
    ERR_AUCTION_OUTBID_S                                       = 438,
    ERR_AUCTION_WON_S                                          = 439,
    ERR_AUCTION_SOLD_S                                         = 440,
    ERR_AUCTION_EXPIRED_S                                      = 441,
    ERR_AUCTION_REMOVED_S                                      = 442,
    ERR_AUCTION_BID_PLACED                                     = 443,
    ERR_LOGOUT_FAILED                                          = 444,
    ERR_QUEST_PUSH_SUCCESS_S                                   = 445,
    ERR_QUEST_PUSH_INVALID_S                                   = 446,
    ERR_QUEST_PUSH_ACCEPTED_S                                  = 447,
    ERR_QUEST_PUSH_DECLINED_S                                  = 448,
    ERR_QUEST_PUSH_BUSY_S                                      = 449,
    ERR_QUEST_PUSH_DEAD_S                                      = 450,
    ERR_QUEST_PUSH_LOG_FULL_S                                  = 451,
    ERR_QUEST_PUSH_ONQUEST_S                                   = 452,
    ERR_QUEST_PUSH_ALREADY_DONE_S                              = 453,
    ERR_QUEST_PUSH_NOT_DAILY_S                                 = 454,
    ERR_QUEST_PUSH_TIMER_EXPIRED_S                             = 455,
    ERR_QUEST_PUSH_NOT_IN_PARTY_S                              = 456,
    ERR_QUEST_PUSH_DIFFERENT_SERVER_DAILY_S                    = 457,
    ERR_QUEST_PUSH_NOT_ALLOWED_S                               = 458,
    ERR_RAID_GROUP_LOWLEVEL                                    = 459,
    ERR_RAID_GROUP_ONLY                                        = 460,
    ERR_RAID_GROUP_FULL                                        = 461,
    ERR_RAID_GROUP_REQUIREMENTS_UNMATCH                        = 462,
    ERR_CORPSE_IS_NOT_IN_INSTANCE                              = 463,
    ERR_PVP_KILL_HONORABLE                                     = 464,
    ERR_PVP_KILL_DISHONORABLE                                  = 465,
    ERR_SPELL_FAILED_ALREADY_AT_FULL_HEALTH                    = 466,
    ERR_SPELL_FAILED_ALREADY_AT_FULL_MANA                      = 467,
    ERR_SPELL_FAILED_ALREADY_AT_FULL_POWER_S                   = 468,
    ERR_AUTOLOOT_MONEY_S                                       = 469,
    ERR_GENERIC_STUNNED                                        = 470,
    ERR_TARGET_STUNNED                                         = 471,
    ERR_MUST_REPAIR_DURABILITY                                 = 472,
    ERR_RAID_YOU_JOINED                                        = 473,
    ERR_RAID_YOU_LEFT                                          = 474,
    ERR_INSTANCE_GROUP_JOINED_WITH_PARTY                       = 475,
    ERR_INSTANCE_GROUP_JOINED_WITH_RAID                        = 476,
    ERR_RAID_MEMBER_ADDED_S                                    = 477,
    ERR_RAID_MEMBER_REMOVED_S                                  = 478,
    ERR_INSTANCE_GROUP_ADDED_S                                 = 479,
    ERR_INSTANCE_GROUP_REMOVED_S                               = 480,
    ERR_CLICK_ON_ITEM_TO_FEED                                  = 481,
    ERR_TOO_MANY_CHAT_CHANNELS                                 = 482,
    ERR_LOOT_ROLL_PENDING                                      = 483,
    ERR_LOOT_PLAYER_NOT_FOUND                                  = 484,
    ERR_NOT_IN_RAID                                            = 485,
    ERR_LOGGING_OUT                                            = 486,
    ERR_TARGET_LOGGING_OUT                                     = 487,
    ERR_NOT_WHILE_MOUNTED                                      = 488,
    ERR_NOT_WHILE_SHAPESHIFTED                                 = 489,
    ERR_NOT_IN_COMBAT                                          = 490,
    ERR_NOT_WHILE_DISARMED                                     = 491,
    ERR_PET_BROKEN                                             = 492,
    ERR_TALENT_WIPE_ERROR                                      = 493,
    ERR_SPEC_WIPE_ERROR                                        = 494,
    ERR_GLYPH_WIPE_ERROR                                       = 495,
    ERR_PET_SPEC_WIPE_ERROR                                    = 496,
    ERR_FEIGN_DEATH_RESISTED                                   = 497,
    ERR_MEETING_STONE_IN_QUEUE_S                               = 498,
    ERR_MEETING_STONE_LEFT_QUEUE_S                             = 499,
    ERR_MEETING_STONE_OTHER_MEMBER_LEFT                        = 500,
    ERR_MEETING_STONE_PARTY_KICKED_FROM_QUEUE                  = 501,
    ERR_MEETING_STONE_MEMBER_STILL_IN_QUEUE                    = 502,
    ERR_MEETING_STONE_SUCCESS                                  = 503,
    ERR_MEETING_STONE_IN_PROGRESS                              = 504,
    ERR_MEETING_STONE_MEMBER_ADDED_S                           = 505,
    ERR_MEETING_STONE_GROUP_FULL                               = 506,
    ERR_MEETING_STONE_NOT_LEADER                               = 507,
    ERR_MEETING_STONE_INVALID_LEVEL                            = 508,
    ERR_MEETING_STONE_TARGET_NOT_IN_PARTY                      = 509,
    ERR_MEETING_STONE_TARGET_INVALID_LEVEL                     = 510,
    ERR_MEETING_STONE_MUST_BE_LEADER                           = 511,
    ERR_MEETING_STONE_NO_RAID_GROUP                            = 512,
    ERR_MEETING_STONE_NEED_PARTY                               = 513,
    ERR_MEETING_STONE_NOT_FOUND                                = 514,
    ERR_GUILDEMBLEM_SAME                                       = 515,
    ERR_EQUIP_TRADE_ITEM                                       = 516,
    ERR_PVP_TOGGLE_ON                                          = 517,
    ERR_PVP_TOGGLE_OFF                                         = 518,
    ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS                      = 519,
    ERR_GROUP_JOIN_BATTLEGROUND_S                              = 520,
    ERR_GROUP_JOIN_BATTLEGROUND_FAIL                           = 521,
    ERR_GROUP_JOIN_BATTLEGROUND_TOO_MANY                       = 522,
    ERR_SOLO_JOIN_BATTLEGROUND_S                               = 523,
    ERR_BATTLEGROUND_TOO_MANY_QUEUES                           = 524,
    ERR_BATTLEGROUND_CANNOT_QUEUE_FOR_RATED                    = 525,
    ERR_BATTLEDGROUND_QUEUED_FOR_RATED                         = 526,
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE                           = 527,
    ERR_BATTLEGROUND_NOT_IN_BATTLEGROUND                       = 528,
    ERR_INVALID_PROMOTION_CODE                                 = 529,
    ERR_BG_PLAYER_JOINED_SS                                    = 530,
    ERR_BG_PLAYER_LEFT_S                                       = 531,
    ERR_RESTRICTED_ACCOUNT                                     = 532,
    ERR_PLAY_TIME_EXCEEDED                                     = 533,
    ERR_APPROACHING_PARTIAL_PLAY_TIME                          = 534,
    ERR_APPROACHING_PARTIAL_PLAY_TIME_2                        = 535,
    ERR_APPROACHING_NO_PLAY_TIME                               = 536,
    ERR_APPROACHING_NO_PLAY_TIME_2                             = 537,
    ERR_UNHEALTHY_TIME                                         = 538,
    ERR_CHAT_RESTRICTED                                        = 539,
    ERR_CHAT_THROTTLED                                         = 540,
    ERR_MAIL_REACHED_CAP                                       = 541,
    ERR_INVALID_RAID_TARGET                                    = 542,
    ERR_RAID_LEADER_READY_CHECK_START_S                        = 543,
    ERR_READY_CHECK_IN_PROGRESS                                = 544,
    ERR_READY_CHECK_THROTTLED                                  = 545,
    ERR_DUNGEON_DIFFICULTY_FAILED                              = 546,
    ERR_DUNGEON_DIFFICULTY_CHANGED_S                           = 547,
    ERR_TRADE_WRONG_REALM                                      = 548,
    ERR_TRADE_NOT_ON_TAPLIST                                   = 549,
    ERR_CHAT_PLAYER_AMBIGUOUS_S                                = 550,
    ERR_LOOT_CANT_LOOT_THAT_NOW                                = 551,
    ERR_LOOT_MASTER_INV_FULL                                   = 552,
    ERR_LOOT_MASTER_UNIQUE_ITEM                                = 553,
    ERR_LOOT_MASTER_OTHER                                      = 554,
    ERR_FILTERING_YOU_S                                        = 555,
    ERR_USE_PREVENTED_BY_MECHANIC_S                            = 556,
    ERR_ITEM_UNIQUE_EQUIPPABLE                                 = 557,
    ERR_LFG_LEADER_IS_LFM_S                                    = 558,
    ERR_LFG_PENDING                                            = 559,
    ERR_ARENA_NO_TEAM_II                                       = 560,
    ERR_ARENA_TEAM_CREATE_S                                    = 561,
    ERR_ARENA_TEAM_INVITE_SS                                   = 562,
    ERR_ARENA_TEAM_QUIT_S                                      = 563,
    ERR_ARENA_TEAM_FOUNDER_S                                   = 564,
    ERR_ARENA_TEAM_INTERNAL                                    = 565,
    ERR_ALREADY_IN_ARENA_TEAM                                  = 566,
    ERR_ALREADY_IN_ARENA_TEAM_S                                = 567,
    ERR_INVITED_TO_ARENA_TEAM                                  = 568,
    ERR_ALREADY_INVITED_TO_ARENA_TEAM_S                        = 569,
    ERR_ARENA_TEAM_NAME_INVALID                                = 570,
    ERR_ARENA_TEAM_NAME_EXISTS_S                               = 571,
    ERR_ARENA_TEAM_LEADER_LEAVE_S                              = 572,
    ERR_ARENA_TEAM_PERMISSIONS                                 = 573,
    ERR_ARENA_TEAM_PLAYER_NOT_IN_TEAM                          = 574,
    ERR_ARENA_TEAM_PLAYER_NOT_IN_TEAM_SS                       = 575,
    ERR_ARENA_TEAM_PLAYER_NOT_FOUND_S                          = 576,
    ERR_ARENA_TEAM_NOT_ALLIED                                  = 577,
    ERR_ARENA_TEAM_JOIN_SS                                     = 578,
    ERR_ARENA_TEAM_YOU_JOIN_S                                  = 579,
    ERR_ARENA_TEAM_LEAVE_SS                                    = 580,
    ERR_ARENA_TEAM_LEADER_IS_SS                                = 581,
    ERR_ARENA_TEAM_LEADER_CHANGED_SSS                          = 582,
    ERR_ARENA_TEAM_REMOVE_SSS                                  = 583,
    ERR_ARENA_TEAM_DISBANDED_S                                 = 584,
    ERR_ARENA_TEAM_TARGET_TOO_LOW_S                            = 585,
    ERR_ARENA_TEAM_TARGET_TOO_HIGH_S                           = 586,
    ERR_ARENA_TEAM_TOO_MANY_MEMBERS_S                          = 587,
    ERR_ARENA_TEAM_LEVEL_TOO_LOW_I                             = 588,
    ERR_ARENA_TEAM_NOT_FOUND                                   = 589,
    ERR_ARENA_TEAMS_LOCKED                                     = 590,
    ERR_ARENA_TEAM_TOO_MANY_CREATE                             = 591,
    ERR_NO_ARENA_CHARTER                                       = 592,
    ERR_CANT_SPEAK_LANGAGE                                     = 593,
    ERR_VENDOR_MISSING_TURNINS                                 = 594,
    ERR_BATTLEGROUND_NOT_IN_TEAM                               = 595,
    ERR_NOT_IN_BATTLEGROUND                                    = 596,
    ERR_NOT_ENOUGH_HONOR_POINTS                                = 597,
    ERR_NOT_ENOUGH_ARENA_POINTS                                = 598,
    ERR_SOCKETING_REQUIRES_META_GEM                            = 599,
    ERR_SOCKETING_META_GEM_ONLY_IN_METASLOT                    = 600,
    ERR_SOCKETING_REQUIRES_HYDRAULIC_GEM                       = 601,
    ERR_SOCKETING_HYDRAULIC_GEM_ONLY_IN_HYDRAULICSLOT          = 602,
    ERR_SOCKETING_REQUIRES_COGWHEEL_GEM                        = 603,
    ERR_SOCKETING_COGWHEEL_GEM_ONLY_IN_COGWHEELSLOT            = 604,
    ERR_SOCKETING_ITEM_TOO_LOW_LEVEL                           = 605,
    ERR_ITEM_MAX_COUNT_SOCKETED                                = 606,
    ERR_SYSTEM_DISABLED                                        = 607,
    ERR_QUEST_FAILED_TOO_MANY_DAILY_QUESTS_I                   = 608,
    ERR_ITEM_MAX_COUNT_EQUIPPED_SOCKETED                       = 609,
    ERR_ITEM_UNIQUE_EQUIPPABLE_SOCKETED                        = 610,
    ERR_USER_SQUELCHED                                         = 611,
    ERR_TOO_MUCH_GOLD                                          = 612,
    ERR_NOT_BARBER_SITTING                                     = 613,
    ERR_QUEST_FAILED_CAIS                                      = 614,
    ERR_INVITE_RESTRICTED                                      = 615,
    ERR_VOICE_IGNORE_FULL                                      = 616,
    ERR_VOICE_IGNORE_SELF                                      = 617,
    ERR_VOICE_IGNORE_NOT_FOUND                                 = 618,
    ERR_VOICE_IGNORE_ALREADY_S                                 = 619,
    ERR_VOICE_IGNORE_ADDED_S                                   = 620,
    ERR_VOICE_IGNORE_REMOVED_S                                 = 621,
    ERR_VOICE_IGNORE_AMBIGUOUS                                 = 622,
    ERR_VOICE_IGNORE_DELETED                                   = 623,
    ERR_UNKNOWN_MACRO_OPTION_S                                 = 624,
    ERR_NOT_DURING_ARENA_MATCH                                 = 625,
    ERR_PLAYER_SILENCED                                        = 626,
    ERR_PLAYER_UNSILENCED                                      = 627,
    ERR_COMSAT_DISCONNECT                                      = 628,
    ERR_COMSAT_RECONNECT_ATTEMPT                               = 629,
    ERR_COMSAT_CONNECT_FAIL                                    = 630,
    ERR_DANCE_CREATE_DUPLICATE                                 = 631,
    ERR_DANCE_SAVE_FAILED                                      = 632,
    ERR_DANCE_DELETE_FAILED                                    = 633,
    ERR_MAIL_INVALID_ATTACHMENT_SLOT                           = 634,
    ERR_MAIL_TOO_MANY_ATTACHMENTS                              = 635,
    ERR_MAIL_INVALID_ATTACHMENT                                = 636,
    ERR_MAIL_ATTACHMENT_EXPIRED                                = 637,
    ERR_VOICE_CHAT_PARENTAL_DISABLE_ALL                        = 638,
    ERR_VOICE_CHAT_PARENTAL_DISABLE_MIC                        = 639,
    ERR_PROFANE_CHAT_NAME                                      = 640,
    ERR_PLAYER_SILENCED_ECHO                                   = 641,
    ERR_PLAYER_UNSILENCED_ECHO                                 = 642,
    ERR_VOICESESSION_FULL                                      = 643,
    ERR_LOOT_CANT_LOOT_THAT                                    = 644,
    ERR_ARENA_EXPIRED_CAIS                                     = 645,
    ERR_GROUP_ACTION_THROTTLED                                 = 646,
    ERR_ALREADY_PICKPOCKETED                                   = 647,
    ERR_NAME_INVALID                                           = 648,
    ERR_NAME_NO_NAME                                           = 649,
    ERR_NAME_TOO_SHORT                                         = 650,
    ERR_NAME_TOO_LONG                                          = 651,
    ERR_NAME_MIXED_LANGUAGES                                   = 652,
    ERR_NAME_PROFANE                                           = 653,
    ERR_NAME_RESERVED                                          = 654,
    ERR_NAME_THREE_CONSECUTIVE                                 = 655,
    ERR_NAME_INVALID_SPACE                                     = 656,
    ERR_NAME_CONSECUTIVE_SPACES                                = 657,
    ERR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS             = 658,
    ERR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END      = 659,
    ERR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME                 = 660,
    ERR_REFER_A_FRIEND_NOT_REFERRED_BY                         = 661,
    ERR_REFER_A_FRIEND_TARGET_TOO_HIGH                         = 662,
    ERR_REFER_A_FRIEND_INSUFFICIENT_GRANTABLE_LEVELS           = 663,
    ERR_REFER_A_FRIEND_TOO_FAR                                 = 664,
    ERR_REFER_A_FRIEND_DIFFERENT_FACTION                       = 665,
    ERR_REFER_A_FRIEND_NOT_NOW                                 = 666,
    ERR_REFER_A_FRIEND_GRANT_LEVEL_MAX_I                       = 667,
    ERR_REFER_A_FRIEND_SUMMON_LEVEL_MAX_I                      = 668,
    ERR_REFER_A_FRIEND_SUMMON_COOLDOWN                         = 669,
    ERR_REFER_A_FRIEND_SUMMON_OFFLINE_S                        = 670,
    ERR_REFER_A_FRIEND_INSUF_EXPAN_LVL                         = 671,
    ERR_REFER_A_FRIEND_NOT_IN_LFG                              = 672,
    ERR_REFER_A_FRIEND_NO_XREALM                               = 673,
    ERR_NOT_SAME_ACCOUNT                                       = 674,
    ERR_BAD_ON_USE_ENCHANT                                     = 675,
    ERR_TRADE_SELF                                             = 676,
    ERR_TOO_MANY_SOCKETS                                       = 677,
    ERR_ITEM_MAX_LIMIT_CATEGORY_COUNT_EXCEEDED_IS              = 678,
    ERR_TRADE_TARGET_MAX_LIMIT_CATEGORY_COUNT_EXCEEDED_IS      = 679,
    ERR_ITEM_MAX_LIMIT_CATEGORY_SOCKETED_EXCEEDED_IS           = 680,
    ERR_ITEM_MAX_LIMIT_CATEGORY_EQUIPPED_EXCEEDED_IS           = 681,
    ERR_SHAPESHIFT_FORM_CANNOT_EQUIP                           = 682,
    ERR_ITEM_INVENTORY_FULL_SATCHEL                            = 683,
    ERR_SCALING_STAT_ITEM_LEVEL_EXCEEDED                       = 684,
    ERR_SCALING_STAT_ITEM_LEVEL_TOO_LOW                        = 685,
    ERR_PURCHASE_LEVEL_TOO_LOW                                 = 686,
    ERR_GROUP_SWAP_FAILED                                      = 687,
    ERR_INVITE_IN_COMBAT                                       = 688,
    ERR_INVALID_GLYPH_SLOT                                     = 689,
    ERR_GENERIC_NO_VALID_TARGETS                               = 690,
    ERR_CALENDAR_EVENT_ALERT_S                                 = 691,
    ERR_PET_LEARN_SPELL_S                                      = 692,
    ERR_PET_LEARN_ABILITY_S                                    = 693,
    ERR_PET_SPELL_UNLEARNED_S                                  = 694,
    ERR_INVITE_UNKNOWN_REALM                                   = 695,
    ERR_INVITE_NO_PARTY_SERVER                                 = 696,
    ERR_INVITE_PARTY_BUSY                                      = 697,
    ERR_PARTY_TARGET_AMBIGUOUS                                 = 698,
    ERR_PARTY_LFG_INVITE_RAID_LOCKED                           = 699,
    ERR_PARTY_LFG_BOOT_LIMIT                                   = 700,
    ERR_PARTY_LFG_BOOT_COOLDOWN_S                              = 701,
    ERR_PARTY_LFG_BOOT_NOT_ELIGIBLE_S                          = 702,
    ERR_PARTY_LFG_BOOT_IN_PROGRESS                             = 703,
    ERR_PARTY_LFG_BOOT_TOO_FEW_PLAYERS                         = 704,
    ERR_PARTY_LFG_BOOT_VOTE_SUCCEEDED                          = 705,
    ERR_PARTY_LFG_BOOT_VOTE_FAILED                             = 706,
    ERR_PARTY_LFG_BOOT_IN_COMBAT                               = 707,
    ERR_PARTY_LFG_BOOT_DUNGEON_COMPLETE                        = 708,
    ERR_PARTY_LFG_BOOT_LOOT_ROLLS                              = 709,
    ERR_PARTY_LFG_BOOT_VOTE_REGISTERED                         = 710,
    ERR_PARTY_PRIVATE_GROUP_ONLY                               = 711,
    ERR_PARTY_LFG_TELEPORT_IN_COMBAT                           = 712,
    ERR_RAID_DISALLOWED_BY_LEVEL                               = 713,
    ERR_RAID_DISALLOWED_BY_CROSS_REALM                         = 714,
    ERR_PARTY_ROLE_NOT_AVAILABLE                               = 715,
    ERR_JOIN_LFG_OBJECT_FAILED                                 = 716,
    ERR_LFG_REMOVED_LEVELUP                                    = 717,
    ERR_LFG_REMOVED_XP_TOGGLE                                  = 718,
    ERR_LFG_REMOVED_FACTION_CHANGE                             = 719,
    ERR_BATTLEGROUND_INFO_THROTTLED                            = 720,
    ERR_BATTLEGROUND_ALREADY_IN                                = 721,
    ERR_ARENA_TEAM_CHANGE_FAILED_QUEUED                        = 722,
    ERR_NOT_WHILE_FALLING                                      = 723,
    ERR_NOT_WHILE_FATIGUED                                     = 724,
    ERR_MAX_SOCKETS                                            = 725,
    ERR_MULTI_CAST_ACTION_TOTEM_S                              = 726,
    ERR_REMOVE_FROM_PVP_QUEUE_GRANT_LEVEL                      = 727,
    ERR_REMOVE_FROM_PVP_QUEUE_XP_GAIN                          = 728,
    ERR_BATTLEGROUND_JOIN_XP_GAIN                              = 729,
    ERR_RAID_DIFFICULTY_FAILED                                 = 730,
    ERR_RAID_DIFFICULTY_CHANGED_S                              = 731,
    ERR_RAID_LOCKOUT_CHANGED_S                                 = 732,
    ERR_PLAYER_DIFFICULTY_CHANGED_S                            = 733,
    ERR_GMRESPONSE_DB_ERROR                                    = 734,
    ERR_BATTLEGROUND_JOIN_RANGE_INDEX                          = 735,
    ERR_ARENA_JOIN_RANGE_INDEX                                 = 736,
    ERR_REMOVE_FROM_PVP_QUEUE_FACTION_CHANGE                   = 737,
    ERR_BATTLEGROUND_JOIN_FAILED                               = 738,
    ERR_BATTLEGROUND_INVITATION_DECLINED                       = 739,
    ERR_BATTLEGROUND_JOIN_TIMED_OUT                            = 740,
    ERR_BATTLEGROUND_DUPE_QUEUE                                = 741,
    ERR_MAIL_LIMITED_DURATION_ITEM                             = 742,
    ERR_YELL_RESTRICTED                                        = 743,
    ERR_LFG_ROLE_CHECK_FAILED                                  = 744,
    ERR_LFG_ROLE_CHECK_FAILED_TIMEOUT                          = 745,
    ERR_LFG_ROLE_CHECK_FAILED_NOT_VIABLE                       = 746,
    ERR_LFG_GROUP_FULL                                         = 747,
    ERR_LFG_NO_LFG_OBJECT                                      = 748,
    ERR_LFG_NO_SLOTS_PLAYER                                    = 749,
    ERR_LFG_NO_SLOTS_PARTY                                     = 750,
    ERR_LFG_MISMATCHED_SLOTS                                   = 751,
    ERR_LFG_MISMATCHED_SLOTS_LOCAL_XREALM                      = 752,
    ERR_LFG_PARTY_PLAYERS_FROM_DIFFERENT_REALMS                = 753,
    ERR_LFG_MEMBERS_NOT_PRESENT                                = 754,
    ERR_LFG_GET_INFO_TIMEOUT                                   = 755,
    ERR_LFG_INVALID_SLOT                                       = 756,
    ERR_LFG_DESERTER_PLAYER                                    = 757,
    ERR_LFG_DESERTER_PARTY                                     = 758,
    ERR_LFG_RANDOM_COOLDOWN_PLAYER                             = 759,
    ERR_LFG_RANDOM_COOLDOWN_PARTY                              = 760,
    ERR_LFG_TOO_MANY_MEMBERS                                   = 761,
    ERR_LFG_TOO_FEW_MEMBERS                                    = 762,
    ERR_LFG_PROPOSAL_FAILED                                    = 763,
    ERR_LFG_PROPOSAL_DECLINED_SELF                             = 764,
    ERR_LFG_PROPOSAL_DECLINED_PARTY                            = 765,
    ERR_LFG_NO_SLOTS_SELECTED                                  = 766,
    ERR_LFG_NO_ROLES_SELECTED                                  = 767,
    ERR_LFG_ROLE_CHECK_INITIATED                               = 768,
    ERR_LFG_PLAYER_DECLINED_ROLE_CHECK                         = 769,
    ERR_LFG_JOINED_QUEUE                                       = 770,
    ERR_LFG_JOINED_FLEX_QUEUE                                  = 771,
    ERR_LFG_JOINED_RF_QUEUE                                    = 772,
    ERR_LFG_JOINED_SCENARIO_QUEUE                              = 773,
    ERR_LFG_JOINED_LIST                                        = 774,
    ERR_LFG_LEFT_QUEUE                                         = 775,
    ERR_LFG_LEFT_LIST                                          = 776,
    ERR_LFG_ROLE_CHECK_ABORTED                                 = 777,
    ERR_LFG_CANT_USE_BATTLEGROUND                              = 778,
    ERR_LFG_CANT_USE_DUNGEONS                                  = 779,
    ERR_LFG_REASON_TOO_MANY_LFG                                = 780,
    ERR_INVALID_TELEPORT_LOCATION                              = 781,
    ERR_TOO_FAR_TO_INTERACT                                    = 782,
    ERR_BATTLEGROUND_PLAYERS_FROM_DIFFERENT_REALMS             = 783,
    ERR_DIFFICULTY_CHANGE_COOLDOWN_S                           = 784,
    ERR_DIFFICULTY_CHANGE_COMBAT_COOLDOWN_S                    = 785,
    ERR_DIFFICULTY_CHANGE_WORLDSTATE                           = 786,
    ERR_DIFFICULTY_CHANGE_ENCOUNTER                            = 787,
    ERR_DIFFICULTY_CHANGE_COMBAT                               = 788,
    ERR_DIFFICULTY_CHANGE_PLAYER_BUSY                          = 789,
    ERR_DIFFICULTY_CHANGE_ALREADY_STARTED                      = 790,
    ERR_DIFFICULTY_CHANGE_OTHER_HEROIC_S                       = 791,
    ERR_DIFFICULTY_CHANGE_HEROIC_INSTANCE_ALREADY_RUNNING      = 792,
    ERR_ARENA_TEAM_PARTY_SIZE                                  = 793,
    ERR_QUEST_FORCE_REMOVED_S                                  = 794,
    ERR_ATTACK_NO_ACTIONS                                      = 795,
    ERR_IN_RANDOM_BG                                           = 796,
    ERR_IN_NON_RANDOM_BG                                       = 797,
    ERR_AUCTION_ENOUGH_ITEMS                                   = 798,
    ERR_BN_FRIEND_SELF                                         = 799,
    ERR_BN_FRIEND_ALREADY                                      = 800,
    ERR_BN_FRIEND_BLOCKED                                      = 801,
    ERR_BN_FRIEND_LIST_FULL                                    = 802,
    ERR_BN_FRIEND_REQUEST_SENT                                 = 803,
    ERR_BN_BROADCAST_THROTTLE                                  = 804,
    ERR_BG_DEVELOPER_ONLY                                      = 805,
    ERR_CURRENCY_SPELL_SLOT_MISMATCH                           = 806,
    ERR_CURRENCY_NOT_TRADABLE                                  = 807,
    ERR_REQUIRES_EXPANSION_S                                   = 808,
    ERR_QUEST_FAILED_SPELL                                     = 809,
    ERR_TALENT_FAILED_NOT_ENOUGH_TALENTS_IN_PRIMARY_TREE       = 810,
    ERR_TALENT_FAILED_NO_PRIMARY_TREE_SELECTED                 = 811,
    ERR_TALENT_FAILED_UNKNOWN                                  = 812,
    ERR_REFORGE_SRC_STAT_NOT_FOUND                             = 813,
    ERR_REFORGE_INSUFFICIENT_SRC_STAT                          = 814,
    ERR_REFORGE_ALREADY_HAS_DST_STAT                           = 815,
    ERR_REFORGE_ITEM_TOO_LOW_LEVEL                             = 816,
    ERR_WARGAME_REQUEST_FAILURE                                = 817,
    ERR_RANK_REQUIRES_AUTHENTICATOR                            = 818,
    ERR_GUILD_BANK_VOUCHER_FAILED                              = 819,
    ERR_WARGAME_REQUEST_SENT                                   = 820,
    ERR_REQUIRES_ACHIEVEMENT_I                                 = 821,
    ERR_REFUND_RESULT_EXCEED_MAX_CURRENCY                      = 822,
    ERR_CANT_BUY_QUANTITY                                      = 823,
    ERR_ITEM_IS_BATTLE_PAY_LOCKED                              = 824,
    ERR_PARTY_ALREADY_IN_BATTLEGROUND_QUEUE                    = 825,
    ERR_PARTY_CONFIRMING_BATTLEGROUND_QUEUE                    = 826,
    ERR_BATTLEFIELD_TEAM_PARTY_SIZE                            = 827,
    ERR_INSUFF_TRACKED_CURRENCY_IS                             = 828,
    ERR_NOT_ON_TOURNAMENT_REALM                                = 829,
    ERR_GUILD_TRIAL_ACCOUNT                                    = 830,
    ERR_GUILD_UNDELETABLE_DUE_TO_LEVEL                         = 831,
    ERR_CANT_DO_THAT_IN_A_GROUP                                = 832,
    ERR_GUILD_LEADER_REPLACED                                  = 833,
    ERR_TRANSMOGRIFY_CANT_EQUIP                                = 834,
    ERR_TRANSMOGRIFY_INVALID_ITEM_TYPE                         = 835,
    ERR_TRANSMOGRIFY_NOT_SOULBOUND                             = 836,
    ERR_TRANSMOGRIFY_INVALID_SOURCE                            = 837,
    ERR_TRANSMOGRIFY_INVALID_DESTINATION                       = 838,
    ERR_TRANSMOGRIFY_MISMATCH                                  = 839,
    ERR_TRANSMOGRIFY_LEGENDARY                                 = 840,
    ERR_TRANSMOGRIFY_SAME_ITEM                                 = 841,
    ERR_TRANSMOGRIFY_SAME_APPEARANCE                           = 842,
    ERR_TRANSMOGRIFY_NOT_EQUIPPED                              = 843,
    ERR_VOID_DEPOSIT_FULL                                      = 844,
    ERR_VOID_WITHDRAW_FULL                                     = 845,
    ERR_VOID_STORAGE_WRAPPED                                   = 846,
    ERR_VOID_STORAGE_STACKABLE                                 = 847,
    ERR_VOID_STORAGE_UNBOUND                                   = 848,
    ERR_VOID_STORAGE_REPAIR                                    = 849,
    ERR_VOID_STORAGE_CHARGES                                   = 850,
    ERR_VOID_STORAGE_QUEST                                     = 851,
    ERR_VOID_STORAGE_CONJURED                                  = 852,
    ERR_VOID_STORAGE_MAIL                                      = 853,
    ERR_VOID_STORAGE_BAG                                       = 854,
    ERR_VOID_TRANSFER_STORAGE_FULL                             = 855,
    ERR_VOID_TRANSFER_INV_FULL                                 = 856,
    ERR_VOID_TRANSFER_INTERNAL_ERROR                           = 857,
    ERR_VOID_TRANSFER_ITEM_INVALID                             = 858,
    ERR_DIFFICULTY_DISABLED_IN_LFG                             = 859,
    ERR_VOID_STORAGE_UNIQUE                                    = 860,
    ERR_VOID_STORAGE_LOOT                                      = 861,
    ERR_VOID_STORAGE_HOLIDAY                                   = 862,
    ERR_VOID_STORAGE_DURATION                                  = 863,
    ERR_VOID_STORAGE_LOAD_FAILED                               = 864,
    ERR_PARENTAL_CONTROLS_CHAT_MUTED                           = 865,
    ERR_SOR_START_EXPERIENCE_INCOMPLETE                        = 866,
    ERR_SOR_INVALID_EMAIL                                      = 867,
    ERR_SOR_INVALID_COMMENT                                    = 868,
    ERR_CHALLENGE_MODE_RESET_COOLDOWN_S                        = 869,
    ERR_PET_JOURNAL_ALREADY_IN_LOADOUT                         = 870,
    ERR_REPORT_SUBMITTED_SUCCESSFULLY                          = 871,
    ERR_REPORT_SUBMISSION_FAILED                               = 872,
    ERR_SUGGESTION_SUBMITTED_SUCCESSFULLY                      = 873,
    ERR_BUG_SUBMITTED_SUCCESSFULLY                             = 874,
    ERR_CHALLENGE_MODE_ENABLED                                 = 875,
    ERR_CHALLENGE_MODE_DISABLED                                = 876,
    ERR_PETBATTLE_CREATE_FAILED                                = 877,
    ERR_PETBATTLE_NOT_HERE                                     = 878,
    ERR_PETBATTLE_NOT_HERE_ON_TRANSPORT                        = 879,
    ERR_PETBATTLE_NOT_HERE_UNEVEN_GROUND                       = 880,
    ERR_PETBATTLE_NOT_HERE_OBSTRUCTED                          = 881,
    ERR_PETBATTLE_NOT_WHILE_IN_COMBAT                          = 882,
    ERR_PETBATTLE_NOT_WHILE_DEAD                               = 883,
    ERR_PETBATTLE_NOT_WHILE_FLYING                             = 884,
    ERR_PETBATTLE_TARGET_INVALID                               = 885,
    ERR_PETBATTLE_TARGET_OUT_OF_RANGE                          = 886,
    ERR_PETBATTLE_TARGET_NOT_CAPTURABLE                        = 887,
    ERR_PETBATTLE_NOT_A_TRAINER                                = 888,
    ERR_PETBATTLE_DECLINED                                     = 889,
    ERR_PETBATTLE_IN_BATTLE                                    = 890,
    ERR_PETBATTLE_INVALID_LOADOUT                              = 891,
    ERR_PETBATTLE_ALL_PETS_DEAD                                = 892,
    ERR_PETBATTLE_NO_PETS_IN_SLOTS                             = 893,
    ERR_PETBATTLE_NO_ACCOUNT_LOCK                              = 894,
    ERR_PETBATTLE_WILD_PET_TAPPED                              = 895,
    ERR_PETBATTLE_NOT_WHILE_IN_MATCHED_BATTLE                  = 896,
    ERR_CANT_HAVE_MORE_PETS_OF_THAT_TYPE                       = 897,
    ERR_CANT_HAVE_MORE_PETS                                    = 898,
    ERR_PVP_MAP_NOT_FOUND                                      = 899,
    ERR_PVP_MAP_NOT_SET                                        = 900,
    ERR_PETBATTLE_QUEUE_QUEUED                                 = 901,
    ERR_PETBATTLE_QUEUE_ALREADY_QUEUED                         = 902,
    ERR_PETBATTLE_QUEUE_JOIN_FAILED                            = 903,
    ERR_PETBATTLE_QUEUE_JOURNAL_LOCK                           = 904,
    ERR_PETBATTLE_QUEUE_REMOVED                                = 905,
    ERR_PETBATTLE_QUEUE_PROPOSAL_DECLINED                      = 906,
    ERR_PETBATTLE_QUEUE_PROPOSAL_TIMEOUT                       = 907,
    ERR_PETBATTLE_QUEUE_OPPONENT_DECLINED                      = 908,
    ERR_PETBATTLE_QUEUE_REQUEUED_INTERNAL                      = 909,
    ERR_PETBATTLE_QUEUE_REQUEUED_REMOVED                       = 910,
    ERR_PETBATTLE_QUEUE_SLOT_LOCKED                            = 911,
    ERR_PETBATTLE_QUEUE_SLOT_EMPTY                             = 912,
    ERR_PETBATTLE_QUEUE_SLOT_NO_TRACKER                        = 913,
    ERR_PETBATTLE_QUEUE_SLOT_NO_SPECIES                        = 914,
    ERR_PETBATTLE_QUEUE_SLOT_CANT_BATTLE                       = 915,
    ERR_PETBATTLE_QUEUE_SLOT_REVOKED                           = 916,
    ERR_PETBATTLE_QUEUE_SLOT_DEAD                              = 917,
    ERR_PETBATTLE_QUEUE_SLOT_NO_PET                            = 918,
    ERR_PETBATTLE_QUEUE_NOT_WHILE_NEUTRAL                      = 919,
    ERR_PETBATTLE_GAME_TIME_LIMIT_WARNING                      = 920,
    ERR_PETBATTLE_GAME_ROUNDS_LIMIT_WARNING                    = 921,
    ERR_ITEM_UPGRADE_ITEM_TOO_LOW_LEVEL                        = 922,
    ERR_ITEM_UPGRADE_NO_PATH                                   = 923,
    ERR_ITEM_UPGRADE_NO_MORE_UPGRADES                          = 924,
    ERR_BONUS_ROLL_EMPTY                                       = 925,
    ERR_CHALLENGE_MODE_FULL                                    = 926,
    ERR_BATTLETAG_FRIEND_NOT_FOUND                             = 927,
    ERR_BATTLETAG_FRIEND_NOT_VALID                             = 928,
    ERR_BATTLETAG_FRIEND_NOT_ALLOWED                           = 929,
    ERR_BATTLETAG_FRIEND_THROTTLED                             = 930,
    ERR_BATTLETAG_FRIEND_SUCCESS                               = 931,
    ERR_PET_TOO_HIGH_LEVEL_TO_UNCAGE                           = 932,
    ERR_PETBATTLE_INTERNAL                                     = 933,
    ERR_CANT_CAGE_PET_YET                                      = 934,
    ERR_NO_LOOT_IN_CHALLENGE_MODE                              = 935,
    ERR_QUEST_PET_BATTLE_VICTORIES_PVP_II                      = 936,
    ERR_ROLE_CHECK_ALREADY_IN_PROGRESS                         = 937,
    ERR_RECRUIT_A_FRIEND_ACCOUNT_LIMIT                         = 938,
    ERR_RECRUIT_A_FRIEND_FAILED                                = 939,
};

#endif
