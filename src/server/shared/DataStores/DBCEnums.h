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

#ifndef DBCENUMS_H
#define DBCENUMS_H

enum LevelLimit
{
    // Client expected level limitation, like as used in DBC item max levels for "until max player level"
    // use as default max player level, must be fit max level for used client
    // also see MAX_LEVEL and STRONG_MAX_LEVEL define
    DEFAULT_MAX_LEVEL = 90,

    // client supported max level for player/pets/etc. Avoid overflow or client stability affected.
    // also see GT_MAX_LEVEL define
    MAX_LEVEL = 100,

    // Server side limitation. Base at used code requirements.
    // also see MAX_LEVEL and GT_MAX_LEVEL define
    STRONG_MAX_LEVEL = 255,
};

enum BattlegroundBracketId                                  // bracketId for level ranges
{
    BG_BRACKET_ID_FIRST          = 0,
    BG_BRACKET_ID_LAST           = 16
};

// must be max value in PvPDificulty slot+1
#define MAX_BATTLEGROUND_BRACKETS  17

enum AreaTeams
{
    AREATEAM_NONE  = 0,
    AREATEAM_ALLY  = 2,
    AREATEAM_HORDE = 4,
    AREATEAM_ANY   = 6
};

enum AchievementFaction
{
    ACHIEVEMENT_FACTION_HORDE           = 0,
    ACHIEVEMENT_FACTION_ALLIANCE        = 1,
    ACHIEVEMENT_FACTION_ANY             = -1
};

enum AchievementFlags
{
    ACHIEVEMENT_FLAG_COUNTER               = 0x00000001,    // Just count statistic (never stop and complete)
    ACHIEVEMENT_FLAG_HIDDEN                = 0x00000002,    // Not sent to client - internal use only
    ACHIEVEMENT_FLAG_PLAY_NO_VISUAL        = 0x00000004,    // Client does not play achievement earned visual
    ACHIEVEMENT_FLAG_SUMM                  = 0x00000008,    // Use summ criteria value from all requirements (and calculate max value)
    ACHIEVEMENT_FLAG_MAX_USED              = 0x00000010,    // Show max criteria (and calculate max value ??)
    ACHIEVEMENT_FLAG_REQ_COUNT             = 0x00000020,    // Use not zero req count (and calculate max value)
    ACHIEVEMENT_FLAG_AVERAGE               = 0x00000040,    // Show as average value (value / time_in_days) depend from other flag (by def use last criteria value)
    ACHIEVEMENT_FLAG_BAR                   = 0x00000080,    // Show as progress bar (value / max vale) depend from other flag (by def use last criteria value)
    ACHIEVEMENT_FLAG_REALM_FIRST_REACH     = 0x00000100,    //
    ACHIEVEMENT_FLAG_REALM_FIRST_KILL      = 0x00000200,    //
    ACHIEVEMENT_FLAG_UNK3                  = 0x00000400,    // ACHIEVEMENT_FLAG_HIDE_NAME_IN_TIE
    ACHIEVEMENT_FLAG_REALM_FIRST_GUILD     = 0x00000800,    // first guild on realm done something
    ACHIEVEMENT_FLAG_SHOW_IN_GUILD_NEWS    = 0x00001000,    // Shows in guild news
    ACHIEVEMENT_FLAG_SHOW_IN_GUILD_HEADER  = 0x00002000,    // Shows in guild news header
    ACHIEVEMENT_FLAG_GUILD                 = 0x00004000,    //
    ACHIEVEMENT_FLAG_SHOW_GUILD_MEMBERS    = 0x00008000,    //
    ACHIEVEMENT_FLAG_SHOW_CRITERIA_MEMBERS = 0x00010000,    //
    ACHIEVEMENT_FLAG_ACCOUNT               = 0x00020000,    // achievement linked to account
};

enum AchievementCriteriaLimits
{
    MAX_CRITERIA_REQUIREMENTS          = 2,
    MAX_ADDITIONAL_CRITERIA_CONDITIONS = 3
};

enum AchievementCriteriaCondition
{
    ACHIEVEMENT_CRITERIA_CONDITION_NONE            = 0,
    ACHIEVEMENT_CRITERIA_CONDITION_NO_DEATH        = 1,    // reset progress on death
    ACHIEVEMENT_CRITERIA_CONDITION_UNK2            = 2,    // only used in "Complete a daily quest every day for five consecutive days"
    ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP          = 3,    // requires you to be on specific map, reset at change
    ACHIEVEMENT_CRITERIA_CONDITION_NO_LOSE         = 4,    // only used in "Win 10 arenas without losing"
    ACHIEVEMENT_CRITERIA_CONDITION_UNK5            = 5,    // Have spell?
    ACHIEVEMENT_CRITERIA_CONDITION_UNK8            = 8,
    ACHIEVEMENT_CRITERIA_CONDITION_NO_SPELL_HIT    = 9,    // requires the player not to be hit by specific spell
    ACHIEVEMENT_CRITERIA_CONDITION_NOT_IN_GROUP    = 10,   // requires the player not to be in group
    ACHIEVEMENT_CRITERIA_CONDITION_UNK13           = 13    // unk
};

enum AchievementCriteriaAdditionalCondition
{
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_DRUNK_VALUE          = 1,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_UNK2                        = 2,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ITEM_LEVEL                  = 3,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_CREATURE_ENTRY       = 4,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_MUST_BE_PLAYER       = 5,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_MUST_BE_DEAD         = 6,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_MUST_BE_ENEMY        = 7,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_HAS_AURA             = 8,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_HAS_AURA             = 10,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_HAS_AURA_TYPE        = 11,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ITEM_QUALITY_MIN            = 14,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ITEM_QUALITY_EQUALS         = 15,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_UNK16                       = 16,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_AREA_OR_ZONE         = 17,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_AREA_OR_ZONE         = 18,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_INSTANCE_DIFFICULTY         = 20, // For pre pandaria content
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_CREATURE_YIELDS_XP   = 21, // NYI
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ARENA_TYPE                  = 24,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_RACE                 = 25,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_CLASS                = 26,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_RACE                 = 27,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_CLASS                = 28,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_MAX_GROUP_MEMBERS           = 29,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_CREATURE_TYPE        = 30,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_MAP                  = 32,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ITEM_CLASS                  = 33, // NYI
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_PET_BATTLE_FULL_TEAM_25     = 34,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_COMPLETE_QUEST_NOT_IN_GROUP = 35,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_MIN_PERSONAL_RATING         = 37, // NYI (when implementing don't forget about ACHIEVEMENT_CRITERIA_CONDITION_NO_LOSE)
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TITLE_BIT_INDEX             = 38,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SOURCE_LEVEL                = 39,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_LEVEL                = 40,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_ZONE                 = 41,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_HEALTH_PERCENT_BELOW = 46,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_UNK55                       = 55,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_MIN_ACHIEVEMENT_POINTS      = 56,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_REQUIRES_LFG_GROUP          = 58,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_UNK60                       = 60,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_REQUIRES_GUILD_GROUP        = 61,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_GUILD_REPUTATION            = 62,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_RATED_BATTLEGROUND          = 63,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_PROJECT_RARITY              = 65,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_PROJECT_RACE                = 66,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_WORLD_STATE                 = 67,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_MAP_DIFFICULTY              = 68, // For acutual content
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_TARGET_MIN_LEVEL            = 70,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_MODIFIER_TREE               = 73,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_BATTLE_PET_FAMILY           = 78,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_BATTLE_PET_HEALTH_PCT       = 79,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_AT_LEAST_N_GUILD_MEMBERS    = 80,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_NEED_CHALLENGE_MEDAL        = 83,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_PET_BATTLE_AGAINST_TAMER    = 81,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_BATTLE_PET_QUALITY          = 89,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_PET_BATTLE_PVP              = 90,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_BATTLE_PET_SPECIES          = 91,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_ITEM_CLASS_SUBCLASS         = 96,
    ACHIEVEMENT_CRITERIA_ADDITIONAL_CONDITION_SEASON_CURRENCY             = 121,
};

enum AchievementCriteriaFlags
{
    ACHIEVEMENT_CRITERIA_FLAG_SHOW_PROGRESS_BAR = 0x00000001,         // Show progress as bar
    ACHIEVEMENT_CRITERIA_FLAG_HIDDEN            = 0x00000002,         // Not show criteria in client
    ACHIEVEMENT_CRITERIA_FLAG_UNK3              = 0x00000004,         // BG related??
    ACHIEVEMENT_CRITERIA_FLAG_UNK4              = 0x00000008,         //
    ACHIEVEMENT_CRITERIA_FLAG_UNK5              = 0x00000010,         // not used
    ACHIEVEMENT_CRITERIA_FLAG_MONEY_COUNTER     = 0x00000020          // Displays counter as money
};

enum CriteriaStartTypes
{
    CRITERIA_START_TYPE_DAILY_QUEST         = 2,    // Not implemented, used only for "Complete a daily quest every day for five consecutive days"
    CRITERIA_START_TYPE_BATTLEGROUND        = 3,    // Resets when player enters battleground and progress counts only for this battleground
    CRITERIA_START_TYPE_SPELL_CASTER        = 7,    // Timer is started by casting a spell with entry in StartAsset
    CRITERIA_START_TYPE_SPELL_TARGET        = 8,    // Timer is started by being target of spell with entry in StartAsset
    CRITERIA_START_TYPE_QUEST               = 9,    // Started by accepting quest with entry in StartAsset. Can be timed or not.
    CRITERIA_START_TYPE_CREATURE            = 10,   // Timer is started by killing creature with entry in StartAsset
    CRITERIA_START_TYPE_ITEM                = 12,   // Timer is started by using item with entry in StartAsset
    CRITERIA_START_TYPE_EVENT               = 13,   // Timer is started by internal event with id in StartAsset

    CRITERIA_START_TYPE_MAX                 = 15
};

enum CriteriaResetTypes
{
    CRITERIA_RESET_TYPE_LEAVE_BATTLEGORUND  = 3,
    CRITERIA_RESET_TYPE_SPELL_HIT           = 9,
    CRITERIA_RESET_TYPE_LOSE_PET_BATTLE     = 11,

    CRITERIA_RESET_TYPE_MAX                 = 14
};

enum AchievementCriteriaTypes
{
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE                 = 0,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_BG                        = 1,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ARCHAEOLOGY_PROJECTS = 3,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL                   = 5,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL             = 7,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT          = 8,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT          = 9,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY    = 10, // you have to complete a daily quest x times in a row
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE       = 11,
    ACHIEVEMENT_CRITERIA_TYPE_CURRENCY                      = 12,
    ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE                   = 13,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST          = 14,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND         = 15,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP                  = 16,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH                         = 17,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON              = 18,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID                 = 19,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE            = 20,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_CHALLENGE_MODE_GUILD = 22,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER              = 23,
    ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING            = 24,
    ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM                   = 26,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST                = 27,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET               = 28,
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL                    = 29,
    ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE          = 30,
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA        = 31,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA                     = 32,
    ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA                    = 33,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL                   = 34,
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL                = 35,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM                      = 36,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA               = 37,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING           = 38,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_PERSONAL_RATING       = 39,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL             = 40,
    ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM                      = 41,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM                     = 42,
    ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA                  = 43,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_RANK                      = 44,
    ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT                 = 45,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION               = 46,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION       = 47,
    ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP             = 48,
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM               = 49,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT             = 50, /// @todo itemlevel is mentioned in text but not present in dbc
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT            = 51,
    ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS                      = 52,
    ACHIEVEMENT_CRITERIA_TYPE_HK_RACE                       = 53,
    ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE                      = 54,
    ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE                  = 55,
    ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS             = 56, /// @todo in some cases map not present, and in some cases need do without die
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM                    = 57,
    ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_VENDORS            = 59,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS        = 60,
    ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS       = 61,
    ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD       = 62,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TRAVELLING     = 63,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER          = 65,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL           = 66,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY                    = 67,
    ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT                = 68,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2              = 69,
    ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL              = 70,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_CHALLENGE_DUNGEON         = 71,
    ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT            = 72,
    /// @todo 73: Achievements 1515, 1241, 1103 (Name: Mal'Ganis)
    ACHIEVEMENT_CRITERIA_TYPE_ON_LOGIN                      = 74,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS        = 75,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL                      = 76,
    ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL                     = 77,
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE            = 78,
    ACHIEVEMENT_CRITERIA_TYPE_COOK_RECIPES_GUILD            = 79,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS       = 80,
    ACHIEVEMENT_CRITERIA_TYPE_PET_BATTLE_ACHIEVEMENT_POINTS = 81,
    ACHIEVEMENT_CRITERIA_TYPE_CREATE_AUCTION                = 82,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_BID           = 83,
    ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS                  = 84,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD          = 85,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED      = 86,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION       = 87,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION       = 88,
    ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS                = 89,
    ACHIEVEMENT_CRITERIA_TYPE_GATHER_ITEM                   = 90,
    ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM             = 91,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED                     = 93,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED                    = 94,
    ACHIEVEMENT_CRITERIA_TYPE_COLLECT_BATTLE_PET            = 96,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_DEALT             = 101,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_RECEIVED          = 102,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_DAMAGE_RECEIVED         = 103,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEAL_CASTED           = 104,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_HEALING_RECEIVED        = 105,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALING_RECEIVED      = 106,
    ACHIEVEMENT_CRITERIA_TYPE_QUEST_ABANDONED               = 107,
    ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN            = 108,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE                     = 109,
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2                   = 110, /// @todo target entry is missing
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE              = 112,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL           = 113,
    ACHIEVEMENT_CRITERIA_TYPE_ACCEPTED_SUMMONINGS           = 114,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_ACHIEVEMENT_POINTS       = 115,
    ACHIEVEMENT_CRITERIA_TYPE_USE_LFD_TO_GROUP_WITH_PLAYERS = 119,
    ACHIEVEMENT_CRITERIA_TYPE_SPENT_GOLD_GUILD_REPAIRS      = 124,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_GUILD_LEVEL             = 125,
    ACHIEVEMENT_CRITERIA_TYPE_CRAFT_ITEMS_GUILD             = 126,
    ACHIEVEMENT_CRITERIA_TYPE_CATCH_FROM_POOL               = 127,
    ACHIEVEMENT_CRITERIA_TYPE_BUY_GUILD_BANK_SLOTS          = 128,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_GUILD_ACHIEVEMENT_POINTS = 129,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_BATTLEGROUND        = 130,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_BG_RATING               = 132,
    ACHIEVEMENT_CRITERIA_TYPE_BUY_GUILD_TABARD              = 133,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_GUILD         = 134,
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILLS_GUILD         = 135,
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE_GUILD      = 136,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_GUILD_CHALLENGE_TYPE = 138,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_GUILD_CHALLENGE      = 139,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_SCENARIO             = 151,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_SPECIFIC_SCENARIO    = 152,
    ACHIEVEMENT_CRITERIA_TYPE_COLLECT_BATTLE_PET_SPECIES    = 155,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_BATTLE_PET_COUNT          = 156,
    ACHIEVEMENT_CRITERIA_TYPE_CAPTURE_BATTLE_PET            = 157,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_PET_BATTLE                = 158,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_BATTLE_PET_LEVEL        = 160,
    ACHIEVEMENT_CRITERIA_TYPE_CAPTURE_BATTLE_PET2           = 161,  // I dunno why where are two criterias, but this realted only to achievements "capture in zone" but zone is still checked in modifier, and in sniffs it's counter is accumulative
};

enum CriteriaTreeOperator
{
    CRITERIA_TREE_OPERATOR_SINGLE                   = 0,
    CRITERIA_TREE_OPERATOR_SINGLE_NOT_COMPLETED     = 1,
    CRITERIA_TREE_OPERATOR_ALL                      = 4,
    CRITERIA_TREE_OPERAROR_SUM_CHILDREN             = 5,
    CRITERIA_TREE_OPERATOR_MAX_CHILD                = 6,
    CRITERIA_TREE_OPERATOR_COUNT_DIRECT_CHILDREN    = 7,
    CRITERIA_TREE_OPERATOR_ANY                      = 8,
};

enum CriteriaTreeFlags
{
    CRITERIA_TREE_FLAG_PROGRESS_BAR         = 0x0001,
    CRITERIA_TREE_FLAG_PROGRESS_IS_DATE     = 0x0004,
    CRITERIA_TREE_FLAG_SHOW_CURRENCY_ICON   = 0x0008,
    CRITERIA_TREE_FLAG_ALLIANCE_ONLY        = 0x0200,
    CRITERIA_TREE_FLAG_HORDE_ONLY           = 0x0400,
    CRITERIA_TREE_FLAG_SHOW_REQUIRED_COUNT  = 0x0800
};

enum ModifierTreeOperator
{
    MODIFIER_TREE_OPERATOR_SINGLE   = 2,
    MODIFIER_TREE_OPERATOR_NOT      = 3,
    MODIFIER_TREE_OPERATOR_ALL      = 4,
    MODIFIER_TREE_OPERATOR_ANY      = 8,
};

#define ACHIEVEMENT_CRITERIA_TYPE_TOTAL 163

enum AreaFlags
{
    AREA_FLAG_SNOW             = 0x00000001,                // snow (only Dun Morogh, Naxxramas, Razorfen Downs and Winterspring)
    AREA_FLAG_UNK1             = 0x00000002,                // Razorfen Downs, Naxxramas and Acherus: The Ebon Hold (3.3.5a)
    AREA_FLAG_UNK2             = 0x00000004,                // Only used for areas on map 571 (development before)
    AREA_FLAG_SLAVE_CAPITAL    = 0x00000008,                // city and city subsones
    AREA_FLAG_UNK3             = 0x00000010,                // can't find common meaning
    AREA_FLAG_SLAVE_CAPITAL2   = 0x00000020,                // slave capital city flag?
    AREA_FLAG_ALLOW_DUELS      = 0x00000040,                // allow to duel here
    AREA_FLAG_ARENA            = 0x00000080,                // arena, both instanced and world arenas
    AREA_FLAG_CAPITAL          = 0x00000100,                // main capital city flag
    AREA_FLAG_CITY             = 0x00000200,                // only for one zone named "City" (where it located?)
    AREA_FLAG_OUTLAND          = 0x00000400,                // expansion zones? (only Eye of the Storm not have this flag, but have 0x00004000 flag)
    AREA_FLAG_SANCTUARY        = 0x00000800,                // sanctuary area (PvP disabled)
    AREA_FLAG_NEED_FLY         = 0x00001000,                // Respawn alive at the graveyard without corpse
    AREA_FLAG_UNUSED1          = 0x00002000,                // Unused in 3.3.5a
    AREA_FLAG_OUTLAND2         = 0x00004000,                // expansion zones? (only Circle of Blood Arena not have this flag, but have 0x00000400 flag)
    AREA_FLAG_OUTDOOR_PVP      = 0x00008000,                // pvp objective area? (Death's Door also has this flag although it's no pvp object area)
    AREA_FLAG_ARENA_INSTANCE   = 0x00010000,                // used by instanced arenas only
    AREA_FLAG_UNUSED2          = 0x00020000,                // Unused in 3.3.5a
    AREA_FLAG_CONTESTED_AREA   = 0x00040000,                // On PvP servers these areas are considered contested, even though the zone it is contained in is a Horde/Alliance territory.
    AREA_FLAG_UNK6             = 0x00080000,                // Valgarde and Acherus: The Ebon Hold
    AREA_FLAG_LOWLEVEL         = 0x00100000,                // used for some starting areas with area_level <= 15
    AREA_FLAG_TOWN             = 0x00200000,                // small towns with Inn
    AREA_FLAG_UNK7             = 0x00400000,                // Warsong Hold, Acherus: The Ebon Hold, New Agamand Inn, Vengeance Landing Inn, Sunreaver Pavilion (Something to do with team?)
    AREA_FLAG_UNK8             = 0x00800000,                // Valgarde, Acherus: The Ebon Hold, Westguard Inn, Silver Covenant Pavilion (Something to do with team?)
    AREA_FLAG_WINTERGRASP      = 0x01000000,                // Wintergrasp and it's subzones
    AREA_FLAG_INSIDE           = 0x02000000,                // used for determinating spell related inside/outside questions in Map::IsOutdoors
    AREA_FLAG_OUTSIDE          = 0x04000000,                // used for determinating spell related inside/outside questions in Map::IsOutdoors
    AREA_FLAG_WINTERGRASP_2    = 0x08000000,                // Can Hearth And Resurrect From Area
    AREA_FLAG_NO_FLY_ZONE      = 0x20000000,                // Marks zones where you cannot fly
    AREA_FLAG_UNK9             = 0x40000000,
};

enum Difficulty
{
    REGULAR_DIFFICULTY           = 0,

    DUNGEON_DIFFICULTY_NORMAL    = 1,
    DUNGEON_DIFFICULTY_HEROIC    = 2,
    DUNGEON_DIFFICULTY_CHALLENGE = 8,

    RAID_DIFFICULTY_10MAN_NORMAL = 3,
    RAID_DIFFICULTY_25MAN_NORMAL = 4,
    RAID_DIFFICULTY_10MAN_HEROIC = 5,
    RAID_DIFFICULTY_25MAN_HEROIC = 6,
    RAID_DIFFICULTY_25MAN_LFR    = 7,
    RAID_DIFFICULTY_1025MAN_FLEX = 14, // This is from the new Raid Flex system. Only Siege of Ogrimmar (Map 1136) has it.

    RAID_DIFFICULTY_40MAN        = 9,  // Seems used for: 1) Guild group checking - 10 / 40 (ex. : Guild achievs in BG's); 2) Raids - maps 169, 409, 469, 531.

    SCENARIO_DIFFICULTY_NORMAL   = 12,
    SCENARIO_DIFFICULTY_HEROIC   = 11,

    MAX_DUNGEON_DIFFICULTY       = DUNGEON_DIFFICULTY_CHALLENGE + 1,
    MAX_RAID_DIFFICULTY          = RAID_DIFFICULTY_1025MAN_FLEX + 1,
    MAX_SCENARIO_DIFFICULTY      = SCENARIO_DIFFICULTY_NORMAL + 1,
    MAX_DIFFICULTY               = RAID_DIFFICULTY_1025MAN_FLEX + 1,

    MAX_CREATURE_DIFFICULTY      = RAID_DIFFICULTY_1025MAN_FLEX + 11, // Spawns in battlegrounds
};

// Used for DB creature_template selections and other stuff.
// Creatures for Dungeons are template selected entry(5N), difficulty_entry_1(5H), difficulty_entry_2(5C).
// Creatures for Raids are template selected entry (10N), difficulty_entry_1(25N), difficulty_entry_2(10H), difficulty_entry_3(25H), difficulty_entry_4 (LFR), difficulty_entry_5 (Flex).
// Creatures for Scenarios are template selected entry(3N), difficulty_entry_1(3H).
#define MAX_TEMPLATE_DIFFICULTY    RAID_DIFFICULTY_25MAN_HEROIC // Actually it's 6, because we have 6 raid types.

enum SpawnMask
{
    SPAWNMASK_CONTINENT             = (1 << REGULAR_DIFFICULTY), // any maps without spawn modes

    SPAWNMASK_DUNGEON_NORMAL        = (1 << DUNGEON_DIFFICULTY_NORMAL),
    SPAWNMASK_DUNGEON_HEROIC        = (1 << DUNGEON_DIFFICULTY_HEROIC),
    SPAWNMASK_DUNGEON_CHALLENGE     = (1 << DUNGEON_DIFFICULTY_CHALLENGE),
    SPAWNMASK_DUNGEON_ALL           = (SPAWNMASK_DUNGEON_NORMAL | SPAWNMASK_DUNGEON_HEROIC | SPAWNMASK_DUNGEON_CHALLENGE),

    SPAWNMASK_RAID_10MAN_NORMAL     = (1 << RAID_DIFFICULTY_10MAN_NORMAL),
    SPAWNMASK_RAID_25MAN_NORMAL     = (1 << RAID_DIFFICULTY_25MAN_NORMAL),
    SPAWNMASK_RAID_10MAN_FLEX       = (1 << RAID_DIFFICULTY_1025MAN_FLEX),
    SPAWNMASK_RAID_25MAN_LFR        = (1 << RAID_DIFFICULTY_25MAN_LFR),
    SPAWNMASK_RAID_NORMAL_ALL       = (SPAWNMASK_RAID_10MAN_NORMAL | SPAWNMASK_RAID_25MAN_NORMAL | SPAWNMASK_RAID_10MAN_FLEX | SPAWNMASK_RAID_25MAN_LFR),

    SPAWNMASK_RAID_10MAN_HEROIC     = (1 << RAID_DIFFICULTY_10MAN_HEROIC),
    SPAWNMASK_RAID_25MAN_HEROIC     = (1 << RAID_DIFFICULTY_25MAN_HEROIC),
    SPAWNMASK_RAID_HEROIC_ALL       = (SPAWNMASK_RAID_10MAN_HEROIC | SPAWNMASK_RAID_25MAN_HEROIC),

    SPAWNMASK_RAID_ALL              = (SPAWNMASK_RAID_NORMAL_ALL | SPAWNMASK_RAID_HEROIC_ALL),

    SPAWNMASK_SCENARIO_NORMAL       = (1 << SCENARIO_DIFFICULTY_NORMAL),
    SPAWNMASK_SCENARIO_HEROIC       = (1 << SCENARIO_DIFFICULTY_HEROIC),
    SPAWNMASK_SCENARIO_ALL          = (SPAWNMASK_SCENARIO_NORMAL | SPAWNMASK_SCENARIO_HEROIC)
};

enum FactionTemplateFlags
{
    FACTION_TEMPLATE_FLAG_PVP               = 0x00000800,   // flagged for PvP
    FACTION_TEMPLATE_FLAG_CONTESTED_GUARD   = 0x00001000,   // faction will attack players that were involved in PvP combats
    FACTION_TEMPLATE_FLAG_HOSTILE_BY_DEFAULT= 0x00002000
};

enum FactionMasks
{
    FACTION_MASK_PLAYER   = 1,                              // any player
    FACTION_MASK_ALLIANCE = 2,                              // player or creature from alliance team
    FACTION_MASK_HORDE    = 4,                              // player or creature from horde team
    FACTION_MASK_MONSTER  = 8                               // aggressive creature from monster team
    // if none flags set then non-aggressive creature
};

enum MapTypes                                               // Lua_IsInInstance
{
    MAP_COMMON          = 0,                                // none
    MAP_INSTANCE        = 1,                                // party
    MAP_RAID            = 2,                                // raid
    MAP_BATTLEGROUND    = 3,                                // pvp
    MAP_ARENA           = 4,                                // arena
    MAP_SCENARIO        = 5                                 // scenario
};

enum AbilytyLearnType
{
    ABILITY_LEARNED_ON_GET_PROFESSION_SKILL     = 1,
    ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL  = 2
};

enum ItemEnchantmentType
{
    ITEM_ENCHANTMENT_TYPE_NONE             = 0,
    ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL     = 1,
    ITEM_ENCHANTMENT_TYPE_DAMAGE           = 2,
    ITEM_ENCHANTMENT_TYPE_EQUIP_SPELL      = 3,
    ITEM_ENCHANTMENT_TYPE_RESISTANCE       = 4,
    ITEM_ENCHANTMENT_TYPE_STAT             = 5,
    ITEM_ENCHANTMENT_TYPE_TOTEM            = 6,
    ITEM_ENCHANTMENT_TYPE_USE_SPELL        = 7,
    ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET = 8
};

enum ItemExtendedCostFlags
{
    ITEM_EXT_COST_FLAG_REQUIRE_GUILD                = 0x01,
    ITEM_EXT_COST_CURRENCY_REQ_IS_SEASON_EARNED_1   = 0x02,
    ITEM_EXT_COST_CURRENCY_REQ_IS_SEASON_EARNED_2   = 0x04,
    ITEM_EXT_COST_CURRENCY_REQ_IS_SEASON_EARNED_3   = 0x08,
    ITEM_EXT_COST_CURRENCY_REQ_IS_SEASON_EARNED_4   = 0x10,
    ITEM_EXT_COST_CURRENCY_REQ_IS_SEASON_EARNED_5   = 0x20,
};

enum ItemLimitCategoryMode
{
    ITEM_LIMIT_CATEGORY_MODE_HAVE       = 0,                      // limit applied to amount items in inventory/bank
    ITEM_LIMIT_CATEGORY_MODE_EQUIP      = 1                       // limit applied to amount equipped items (including used gems)
};

enum MountFlags
{
    MOUNT_FLAG_CAN_PITCH                = 0x4,                    // client checks MOVEMENTFLAG2_FULL_SPEED_PITCHING
    MOUNT_FLAG_CAN_SWIM                 = 0x8,                    // client checks MOVEMENTFLAG_SWIMMING
};

enum SpellCategoryFlags
{
    SPELL_CATEGORY_FLAG_COOLDOWN_SCALES_WITH_WEAPON_SPEED   = 0x01, // unused
    SPELL_CATEGORY_FLAG_COOLDOWN_STARTS_ON_EVENT            = 0x04,
    SPELL_CATEGORY_FLAG_COOLDOWN_EXPIRES_AT_MIDNIGHT        = 0x08
};

enum TotemCategoryType
{
    TOTEM_CATEGORY_TYPE_KNIFE           = 1,
    TOTEM_CATEGORY_TYPE_TOTEM           = 2,
    TOTEM_CATEGORY_TYPE_ROD             = 3,
    TOTEM_CATEGORY_TYPE_PICK            = 21,
    TOTEM_CATEGORY_TYPE_STONE           = 22,
    TOTEM_CATEGORY_TYPE_HAMMER          = 23,
    TOTEM_CATEGORY_TYPE_SPANNER         = 24
};

// SummonProperties.dbc, col 1
enum SummonPropGroup
{
    SUMMON_PROP_GROUP_UNKNOWN1       = 0,                   // 1160 spells in 3.0.3
    SUMMON_PROP_GROUP_UNKNOWN2       = 1,                   // 861 spells in 3.0.3
    SUMMON_PROP_GROUP_PETS           = 2,                   // 52 spells in 3.0.3, pets mostly
    SUMMON_PROP_GROUP_CONTROLLABLE   = 3,                   // 13 spells in 3.0.3, mostly controllable
    SUMMON_PROP_GROUP_UNKNOWN3       = 4                    // 86 spells in 3.0.3, taxi/mounts
};

// SummonProperties.dbc, col 3
enum SummonPropType
{
    SUMMON_PROP_TYPE_UNKNOWN         = 0,                   // different summons, 1330 spells in 3.0.3
    SUMMON_PROP_TYPE_SUMMON          = 1,                   // generic summons, 49 spells in 3.0.3
    SUMMON_PROP_TYPE_GUARDIAN        = 2,                   // summon guardian, 393 spells in 3.0.3
    SUMMON_PROP_TYPE_ARMY            = 3,                   // summon army, 5 spells in 3.0.3
    SUMMON_PROP_TYPE_TOTEM           = 4,                   // summon totem, 169 spells in 3.0.3
    SUMMON_PROP_TYPE_CRITTER         = 5,                   // critter/minipet, 195 spells in 3.0.3
    SUMMON_PROP_TYPE_DK              = 6,                   // summon DRW/Ghoul, 2 spells in 3.0.3
    SUMMON_PROP_TYPE_BOMB            = 7,                   // summon bot/bomb, 4 spells in 3.0.3
    SUMMON_PROP_TYPE_PHASING         = 8,                   // something todo with DK prequest line, 2 spells in 3.0.3
    SUMMON_PROP_TYPE_SIEGE_VEH       = 9,                   // summon different vehicles, 14 spells in 3.0.3
    SUMMON_PROP_TYPE_DRAKE_VEH       = 10,                  // summon drake (vehicle), 3 spells
    SUMMON_PROP_TYPE_LIGHTWELL       = 11,                  // summon lightwell, 6 spells in 3.0.3
    SUMMON_PROP_TYPE_JEEVES          = 12,                  // summon Jeeves, 1 spell in 3.3.5a
    SUMMON_PROP_TYPE_LASHTAIL        = 13                   // Lashtail Hatchling, 1 spell in 4.2.2
};

// SummonProperties.dbc, col 5
enum SummonPropFlags
{
    SUMMON_PROP_FLAG_NONE            = 0x00000000,          // 1342 spells in 3.0.3
    SUMMON_PROP_FLAG_UNK1            = 0x00000001,          // 75 spells in 3.0.3, something unfriendly
    SUMMON_PROP_FLAG_UNK2            = 0x00000002,          // 616 spells in 3.0.3, something friendly
    SUMMON_PROP_FLAG_UNK3            = 0x00000004,          // 22 spells in 3.0.3, no idea...
    SUMMON_PROP_FLAG_UNK4            = 0x00000008,          // 49 spells in 3.0.3, some mounts
    SUMMON_PROP_FLAG_PERSONAL_SPAWN  = 0x00000010,          // Personal Spawn (creature visible only by summoner)
    SUMMON_PROP_FLAG_UNK6            = 0x00000020,          // 0 spells in 3.3.5, unused
    SUMMON_PROP_FLAG_UNK7            = 0x00000040,          // 12 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK8            = 0x00000080,          // 4 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK9            = 0x00000100,          // 51 spells in 3.0.3, no idea, many quest related
    SUMMON_PROP_FLAG_UNK10           = 0x00000200,          // 51 spells in 3.0.3, something defensive
    SUMMON_PROP_FLAG_UNK11           = 0x00000400,          // 3 spells, requires something near?
    SUMMON_PROP_FLAG_UNK12           = 0x00000800,          // 30 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK13           = 0x00001000,          // Lightwell, Jeeves, Gnomish Alarm-o-bot, Build vehicles(wintergrasp)
    SUMMON_PROP_FLAG_UNK14           = 0x00002000,          // Guides, player follows
    SUMMON_PROP_FLAG_UNK15           = 0x00004000,          // Force of Nature, Shadowfiend, Feral Spirit, Summon Water Elemental
    SUMMON_PROP_FLAG_UNK16           = 0x00008000,          // Light/Dark Bullet, Soul/Fiery Consumption, Twisted Visage, Twilight Whelp. Phase related?
    SUMMON_PROP_FLAG_UNK17           = 0x00010000,
    SUMMON_PROP_FLAG_UNK18           = 0x00020000,
    SUMMON_PROP_FLAG_UNK19           = 0x00040000,
    SUMMON_PROP_FLAG_UNK20           = 0x00080000,
    SUMMON_PROP_FLAG_UNK21           = 0x00100000           // Totems
};

enum VehicleSeatFlags
{
    VEHICLE_SEAT_FLAG_HAS_LOWER_ANIM_FOR_ENTER                         = 0x00000001,
    VEHICLE_SEAT_FLAG_HAS_LOWER_ANIM_FOR_RIDE                          = 0x00000002,
    VEHICLE_SEAT_FLAG_UNK3                                             = 0x00000004,
    VEHICLE_SEAT_FLAG_SHOULD_USE_VEH_SEAT_EXIT_ANIM_ON_VOLUNTARY_EXIT  = 0x00000008,
    VEHICLE_SEAT_FLAG_UNK5                                             = 0x00000010,
    VEHICLE_SEAT_FLAG_UNK6                                             = 0x00000020,
    VEHICLE_SEAT_FLAG_UNK7                                             = 0x00000040,
    VEHICLE_SEAT_FLAG_UNK8                                             = 0x00000080,
    VEHICLE_SEAT_FLAG_UNK9                                             = 0x00000100,
    VEHICLE_SEAT_FLAG_HIDE_PASSENGER                                   = 0x00000200, // Passenger is hidden
    VEHICLE_SEAT_FLAG_ALLOW_TURNING                                    = 0x00000400, // needed for CGCamera__SyncFreeLookFacing
    VEHICLE_SEAT_FLAG_CAN_CONTROL                                      = 0x00000800, // Lua_UnitInVehicleControlSeat
    VEHICLE_SEAT_FLAG_CAN_CAST_MOUNT_SPELL                             = 0x00001000, // Can cast spells with SPELL_AURA_MOUNTED from seat (possibly 4.x only, 0 seats on 3.3.5a)
    VEHICLE_SEAT_FLAG_UNCONTROLLED                                     = 0x00002000, // can override !& VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT
    VEHICLE_SEAT_FLAG_CAN_ATTACK                                       = 0x00004000, // Can attack, cast spells and use items from vehicle
    VEHICLE_SEAT_FLAG_SHOULD_USE_VEH_SEAT_EXIT_ANIM_ON_FORCED_EXIT     = 0x00008000,
    VEHICLE_SEAT_FLAG_UNK17                                            = 0x00010000,
    VEHICLE_SEAT_FLAG_UNK18                                            = 0x00020000, // Needs research and support (28 vehicles): Allow entering vehicles while keeping specific permanent(?) auras that impose visuals (states like beeing under freeze/stun mechanic, emote state animations).
    VEHICLE_SEAT_FLAG_HAS_VEH_EXIT_ANIM_VOLUNTARY_EXIT                 = 0x00040000,
    VEHICLE_SEAT_FLAG_HAS_VEH_EXIT_ANIM_FORCED_EXIT                    = 0x00080000,
    VEHICLE_SEAT_FLAG_PASSENGER_NOT_SELECTABLE                         = 0x00100000,
    VEHICLE_SEAT_FLAG_UNK22                                            = 0x00200000,
    VEHICLE_SEAT_FLAG_REC_HAS_VEHICLE_ENTER_ANIM                       = 0x00400000,
    VEHICLE_SEAT_FLAG_IS_USING_VEHICLE_CONTROLS                        = 0x00800000, // Lua_IsUsingVehicleControls
    VEHICLE_SEAT_FLAG_ENABLE_VEHICLE_ZOOM                              = 0x01000000,
    VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT                                = 0x02000000, // Lua_CanExitVehicle - can enter and exit at free will
    VEHICLE_SEAT_FLAG_CAN_SWITCH                                       = 0x04000000, // Lua_CanSwitchVehicleSeats
    VEHICLE_SEAT_FLAG_HAS_START_WARITING_FOR_VEH_TRANSITION_ANIM_ENTER = 0x08000000,
    VEHICLE_SEAT_FLAG_HAS_START_WARITING_FOR_VEH_TRANSITION_ANIM_EXIT  = 0x10000000,
    VEHICLE_SEAT_FLAG_CAN_CAST                                         = 0x20000000, // Lua_UnitHasVehicleUI
    VEHICLE_SEAT_FLAG_UNK2                                             = 0x40000000, // checked in conjunction with 0x800 in CastSpell2
    VEHICLE_SEAT_FLAG_ALLOWS_INTERACTION                               = 0x80000000
};

enum VehicleSeatFlagsB
{
    VEHICLE_SEAT_FLAG_B_NONE                     = 0x00000000,
    VEHICLE_SEAT_FLAG_B_USABLE_FORCED            = 0x00000002,
    VEHICLE_SEAT_FLAG_B_TARGETS_IN_RAIDUI        = 0x00000008,           // Lua_UnitTargetsVehicleInRaidUI
    VEHICLE_SEAT_FLAG_B_EJECTABLE                = 0x00000020,           // ejectable
    VEHICLE_SEAT_FLAG_B_USABLE_FORCED_2          = 0x00000040,
    VEHICLE_SEAT_FLAG_B_USABLE_FORCED_3          = 0x00000100,
    VEHICLE_SEAT_FLAG_B_USABLE_FORCED_4          = 0x02000000,
    VEHICLE_SEAT_FLAG_B_CAN_SWITCH               = 0x04000000,
    VEHICLE_SEAT_FLAG_B_VEHICLE_PLAYERFRAME_UI   = 0x80000000            // Lua_UnitHasVehiclePlayerFrameUI - actually checked for flagsb &~ 0x80000000
};

// CurrencyTypes.dbc
enum CurrencyTypes
{
    CURRENCY_TYPE_DALARAN_JEWELCRAFTERS_TOKEN     = 61,
    CURRENCY_TYPE_EPICUREAN_AWARD                 = 81,
    CURRENCY_TYPE_CHAMPIONS_SEAL                  = 241,
    CURRENCY_TYPE_ILLUSTRIOUS_JEWELCRAFTERS_TOKEN = 361,
    CURRENCY_TYPE_DWARF_ARCHAEOLOGY_FRAGMENT      = 384,
    CURRENCY_TYPE_TROLL_ARCHAEOLOGY_FRAGMENT      = 385,
    CURRENCY_TYPE_CONQUEST_POINTS                 = 390,
    CURRENCY_TYPE_TOL_BARAD_COMMENDATION          = 391,
    CURRENCY_TYPE_HONOR_POINTS                    = 392,
    CURRENCY_TYPE_FOSSIL_ARCHAEOLOGY_FRAGMENT     = 393,
    CURRENCY_TYPE_NIGHTELF_ARCHAEOLOGY_FRAGMENT   = 394,
    CURRENCY_TYPE_JUSTICE_POINTS                  = 395,
    CURRENCY_TYPE_VALOR_POINTS                    = 396,
    CURRENCY_TYPE_ORC_ARCHAEOLOGY_FRAGMENT        = 397,
    CURRENCY_TYPE_DRAENEI_ARCHAEOLOGY_FRAGMENT    = 398,
    CURRENCY_TYPE_VRYKUL_ARCHAEOLOGY_FRAGMENT     = 399,
    CURRENCY_TYPE_NERUBIAN_ARCHAEOLOGY_FRAGMENT   = 400,
    CURRENCY_TYPE_TOLVIR_ARCHAEOLOGY_FRAGMENT     = 401,
    CURRENCY_TYPE_IRONPAW_TOKEN                   = 402,
    CURRENCY_TYPE_MARK_OF_THE_WORLD_TREE          = 416,
    CURRENCY_TYPE_CONQUEST_META_ARENA             = 483,
    CURRENCY_TYPE_CONQUEST_META_RATED_BG          = 484,
    CURRENCY_TYPE_DARKMOON_PRIZE_TICKET           = 515,
    CURRENCY_TYPE_MOTE_OF_DARKNESS                = 614,
    CURRENCY_TYPE_ESSENCE_OF_CORRUPTED_DEATHWING  = 615,
    CURRENCY_TYPE_PANDAREN_ARCHAEOLOGY_FRAGMENT   = 676,
    CURRENCY_TYPE_MOGU_ARCHAEOLOGY_FRAGMENT       = 677,
    CURRENCY_TYPE_CONQUEST_META_RANDOG_BG         = 692,
    CURRENCY_TYPE_ELDER_CHARM_OF_GOOD_FORTUNE     = 697,
    CURRENCY_TYPE_LESSER_CHARM_OF_GOOD_FORTUNE    = 738,
    CURRENCY_TYPE_MOGU_RUNE_OF_FATE               = 752,
    CURRENCY_TYPE_MANTID_ARCHAEOLOGY_FRAGMENT     = 754,
    CURRENCY_TYPE_WARFORGED_SEAL                  = 776,
    CURRENCY_TYPE_TIMELESS_COIN                   = 777,
    CURRENCY_TYPE_BLOODY_COIN                     = 789,
};

enum ScenarioStepFlags
{
    SCENARIO_STEP_FLAG_BONUS_OBJECTIVE      = 0x1,
};

#endif
