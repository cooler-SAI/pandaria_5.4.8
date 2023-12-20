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

#ifndef TRINITYCORE_GAMEOBJECT_H
#define TRINITYCORE_GAMEOBJECT_H

#include "Common.h"
#include "SharedDefines.h"
#include "Unit.h"
#include "Object.h"
#include "GridObject.h"
#include "LootMgr.h"
#include "DBCStores.h"

class GameObjectAI;
class Group;
class Transport;
enum SpellTargetCheckTypes : uint8;

#define MAX_GAMEOBJECT_QUEST_ITEMS 6

// from `gameobject_template`
struct GameObjectTemplate
{
    uint32  entry;
    uint32  type;
    uint32  displayId;
    std::string name;
    std::string IconName;
    std::string castBarCaption;
    std::string unk1;
    float   size;
    uint32  questItems[MAX_GAMEOBJECT_QUEST_ITEMS];
    int32   unkInt32;
    union                                                   // different GO types have different data field
    {
        //0 GAMEOBJECT_TYPE_DOOR
        struct
        {
            uint32 startOpen;                               //0 used client side to determine GO_ACTIVATED means open/closed
            uint32 lockId;                                  //1 -> Lock.dbc
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
            uint32 noDamageImmune;                          //3 break opening whenever you recieve damage?
            uint32 openTextID;                              //4 can be used to replace castBarCaption?
            uint32 closeTextID;                             //5
            uint32 ignoredByPathing;                        //6
            uint32 conditionID1;                            // 7 conditionID1, References: PlayerCondition, NoValue = 0
            uint32 DoorisOpaque;                            // 8 Door is Opaque (Disable portal on close), enum { false, true, }; Default: true
            uint32 GiganticAOI;                             // 9 Gigantic AOI, enum { false, true, }; Default: false
            uint32 InfiniteAOI;                             // 10 Infinite AOI, enum { false, true, }; Default: false
        } door;
        //1 GAMEOBJECT_TYPE_BUTTON
        struct
        {
            uint32 startOpen;                               //0
            uint32 lockId;                                  //1 -> Lock.dbc
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
            uint32 linkedTrap;                              //3
            uint32 noDamageImmune;                          //4 isBattlegroundObject
            uint32 GiganticAOI;                                   //5
            uint32 openTextID;                              //6 can be used to replace castBarCaption?
            uint32 closeTextID;                             //7
            uint32 losOK;                                   //8
        } button;
        //2 GAMEOBJECT_TYPE_QUESTGIVER
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 questList;                               //1
            uint32 pageMaterial;                            //2
            uint32 gossipID;                                //3
            uint32 customAnim;                              //4
            uint32 noDamageImmune;                          //5
            uint32 openTextID;                              //6 can be used to replace castBarCaption?
            uint32 losOK;                                   //7
            uint32 allowMounted;                            //8 Is usable while on mount/vehicle. (0/1)
            uint32 GiganticAOI;                             //9
        } questgiver;
        //3 GAMEOBJECT_TYPE_CHEST
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 lootId;                                  //1
            uint32 chestRestockTime;                        //2
            uint32 consumable;                              //3
            uint32 minSuccessOpens;                         //4 Deprecated, pre 3.0 was used for mining nodes but since WotLK all mining nodes are usable once and grant all loot with a single use
            uint32 maxSuccessOpens;                         //5 Deprecated, pre 3.0 was used for mining nodes but since WotLK all mining nodes are usable once and grant all loot with a single use
            uint32 eventId;                                 //6 lootedEvent
            uint32 linkedTrapId;                            //7
            uint32 questId;                                 //8 not used currently but store quest required for GO activation for player
            uint32 level;                                   //9
            uint32 losOK;                                   //10
            uint32 leaveLoot;                               //11
            uint32 notInCombat;                             //12
            uint32 logLoot;                                 //13
            uint32 openTextID;                              //14 can be used to replace castBarCaption?
            uint32 groupLootRules;                          //15
            uint32 floatingTooltip;                         //16
            uint32 conditionID1;                            //17 conditionID1, References: PlayerCondition, NoValue = 0
            uint32 xpLevel;                                 //18
            uint32 unk19;                                   //19
            uint32 unk20;                                   //20
            uint32 unk21;                                   //21
            uint32 unk22;                                   //22
            uint32 trivialSkillLow;                         // 23
            uint32 trivialSkillHigh;                        // 24
            uint32 DungeonEncounter;                        // 25 Dungeon Encounter, References: DungeonEncounter, NoValue = 0
            uint32 spell;                                   // 26 spell, References: Spell, NoValue = 0
            uint32 GiganticAOI;                             // 27 Gigantic AOI, enum { false, true, }; Default: false
            uint32 LargeAOI;                                // 28 Large AOI, enum { false, true, }; Default: false
            uint32 SpawnVignette;                           // 29 Spawn Vignette, References: vignette, NoValue = 0
            uint32 chestPersonalLoot;                       // 30 chest Personal Loot, References: Treasure, NoValue = 0
            uint32 turnpersonallootsecurityoff;             // 31 turn personal loot security off, enum { false, true, }; Default: false
            uint32 ChestProperties;                         // 32 Chest Properties, References: ChestProperties, NoValue = 0
        } chest;
        //4 GAMEOBJECT_TYPE_BINDER - empty
        //5 GAMEOBJECT_TYPE_GENERIC
        struct
        {
            uint32 floatingTooltip;                         //0
            uint32 highlight;                               //1
            uint32 serverOnly;                              //2
            uint32 GiganticAOI;                             //3
            uint32 floatOnWater;                            //4
            int32 questID;                                  //5
            uint32 conditionID1;                            // 6 conditionID1, References: PlayerCondition, NoValue = 0
            uint32 LargeAOI;                                // 7 Large AOI, enum { false, true, }; Default: false
            uint32 UseGarrisonOwnerGuildColors;             // 8 Use Garrison Owner Guild Colors, enum { false, true, }; Default: false
        } _generic;
        //6 GAMEOBJECT_TYPE_TRAP
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 level;                                   //1
            uint32 radius;                                  //2 radius for trap activation
            uint32 spellId;                                 //3
            uint32 type;                                    //4 0 trap with no despawn after cast. 1 trap despawns after cast. 2 bomb casts on spawn.
            uint32 cooldown;                                //5 time in secs
            int32 autoCloseTime;                            //6
            uint32 startDelay;                              //7
            uint32 serverOnly;                              //8
            uint32 stealthed;                               //9
            uint32 GiganticAOI;                             //10
            uint32 invisible;                               //11
            uint32 openTextID;                              //12 can be used to replace castBarCaption?
            uint32 closeTextID;                             //13
            uint32 ignoreTotems;                            //14
        } trap;
        //7 GAMEOBJECT_TYPE_CHAIR
        struct
        {
            uint32 slots;                                   //0
            uint32 height;                                  //1
            uint32 onlyCreatorUse;                          //2
            uint32 triggeredEvent;                          //3
        } chair;
        //8 GAMEOBJECT_TYPE_SPELL_FOCUS
        struct
        {
            uint32 focusId;                                 //0
            uint32 dist;                                    //1
            uint32 linkedTrapId;                            //2
            uint32 serverOnly;                              //3
            uint32 questID;                                 //4
            uint32 GiganticAOI;                             //5
            uint32 floatingTooltip;                         //6
        } spellFocus;
        //9 GAMEOBJECT_TYPE_TEXT
        struct
        {
            uint32 pageID;                                  //0
            uint32 language;                                //1
            uint32 pageMaterial;                            //2
            uint32 allowMounted;                            //3 Is usable while on mount/vehicle. (0/1)
        } text;
        //10 GAMEOBJECT_TYPE_GOOBER
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            int32 questId;                                  //1
            uint32 eventId;                                 //2
            uint32 autoCloseTime;                           //3
            uint32 customAnim;                              //4
            uint32 consumable;                              //5
            uint32 cooldown;                                //6
            uint32 pageId;                                  //7
            uint32 language;                                //8
            uint32 pageMaterial;                            //9
            uint32 spellId;                                 //10
            uint32 noDamageImmune;                          //11
            uint32 linkedTrapId;                            //12
            uint32 GiganticAOI;                             //13
            uint32 openTextID;                              //14 can be used to replace castBarCaption?
            uint32 closeTextID;                             //15
            uint32 losOK;                                   //16 isBattlegroundObject
            uint32 allowMounted;                            //17 Is usable while on mount/vehicle. (0/1)
            uint32 floatingTooltip;                         //18
            uint32 gossipID;                                //19
            uint32 WorldStateSetsState;                     //20
            uint32 floatOnWater;                            //21 floatOnWater, enum { false, true, }; Default: false
            uint32 conditionID1;                            //22 conditionID1, References: PlayerCondition, NoValue = 0
            uint32 playerCast;                              //23 playerCast, enum { false, true, }; Default: false
            uint32 SpawnVignette;                           //24 Spawn Vignette, References: vignette, NoValue = 0
        } goober;
        //11 GAMEOBJECT_TYPE_TRANSPORT
        struct
        {
            uint32 pause;                                   //0
            uint32 startOpen;                               //1
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
            uint32 pause1EventID;                           //3
            uint32 pause2EventID;                           //4
        } transport;
        //12 GAMEOBJECT_TYPE_AREADAMAGE
        struct
        {
            uint32 lockId;                                  //0
            uint32 radius;                                  //1
            uint32 damageMin;                               //2
            uint32 damageMax;                               //3
            uint32 damageSchool;                            //4
            uint32 autoCloseTime;                           //5 secs till autoclose = autoCloseTime / 0x10000
            uint32 openTextID;                              //6
            uint32 closeTextID;                             //7
        } areadamage;
        //13 GAMEOBJECT_TYPE_CAMERA
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 cinematicId;                             //1
            uint32 eventID;                                 //2
            uint32 openTextID;                              //3 can be used to replace castBarCaption?
        } camera;
        //14 GAMEOBJECT_TYPE_MAPOBJECT - empty
        //15 GAMEOBJECT_TYPE_MO_TRANSPORT
        struct
        {
            uint32 taxiPathId;                              //0
            uint32 moveSpeed;                               //1
            uint32 accelRate;                               //2
            uint32 startEventID;                            //3
            uint32 stopEventID;                             //4
            uint32 transportPhysics;                        //5
            uint32 mapID;                                   //6
            uint32 worldState1;                             //7
            uint32 canBeStopped;                            //8
            uint32 InitStopped;                             //9 Init Stopped, enum { false, true, }; Default: false
            uint32 TrueInfiniteAOI;                         //10 True Infinite AOI (programmer only!), enum { false, true, }; Default: false
        } moTransport;
        //16 GAMEOBJECT_TYPE_DUELFLAG - empty
        //17 GAMEOBJECT_TYPE_FISHINGNODE - empty
        //18 GAMEOBJECT_TYPE_SUMMONING_RITUAL
        struct
        {
            uint32 reqParticipants;                         //0
            uint32 spellId;                                 //1
            uint32 animSpell;                               //2
            uint32 ritualPersistent;                        //3
            uint32 casterTargetSpell;                       //4
            uint32 casterTargetSpellTargets;                //5
            uint32 castersGrouped;                          //6
            uint32 ritualNoTargetCheck;                     //7
        } summoningRitual;
        //19 GAMEOBJECT_TYPE_MAILBOX - empty
        //20 GAMEOBJECT_TYPE_DONOTUSE - empty
        //21 GAMEOBJECT_TYPE_GUARDPOST
        struct
        {
            uint32 creatureID;                              //0
            uint32 charges;                                 //1
        } guardpost;
        //22 GAMEOBJECT_TYPE_SPELLCASTER
        struct
        {
            uint32 spellId;                                 //0
            uint32 charges;                                 //1
            uint32 partyOnly;                               //2
            uint32 allowMounted;                            //3 Is usable while on mount/vehicle. (0/1)
            uint32 GiganticAOI;                             //4
        } spellcaster;
        //23 GAMEOBJECT_TYPE_MEETINGSTONE
        struct
        {
            uint32 minLevel;                                //0
            uint32 maxLevel;                                //1
            uint32 areaID;                                  //2
        } meetingstone;
        //24 GAMEOBJECT_TYPE_FLAGSTAND
        struct
        {
            uint32 lockId;                                  //0
            uint32 pickupSpell;                             //1
            uint32 radius;                                  //2
            uint32 returnAura;                              //3
            uint32 returnSpell;                             //4
            uint32 noDamageImmune;                          //5
            uint32 openTextID;                              //6
            uint32 losOK;                                   //7
            uint32 conditionID1;                            // 8 conditionID1, References: PlayerCondition, NoValue = 0
            uint32 playerCast;                              // 9 playerCast, enum { false, true, }; Default: false
            uint32 GiganticAOI;                             // 10 Gigantic AOI, enum { false, true, }; Default: false
            uint32 InfiniteAOI;                             // 11 Infinite AOI, enum { false, true, }; Default: false
            uint32 cooldown;                                // 12 cooldown, int, Min value: 0, Max value: 2147483647, Default value: 3000
        } flagstand;
        //25 GAMEOBJECT_TYPE_FISHINGHOLE
        struct
        {
            uint32 radius;                                  //0 how close bobber must land for sending loot
            uint32 lootId;                                  //1
            uint32 minSuccessOpens;                         //2
            uint32 maxSuccessOpens;                         //3
            uint32 lockId;                                  //4 -> Lock.dbc; possibly 1628 for all?
        } fishinghole;
        //26 GAMEOBJECT_TYPE_FLAGDROP
        struct
        {
            uint32 lockId;                                  //0
            uint32 eventID;                                 //1
            uint32 pickupSpell;                             //2
            uint32 noDamageImmune;                          //3
            uint32 openTextID;                              //4
            uint32 playerCast;                              // 5 playerCast, enum { false, true, }; Default: false
            uint32 ExpireDuration;                          // 6 Expire Duration, int, Min value: 0, Max value: 60000, Default value: 10000
            uint32 GiganticAOI;                             // 7 Gigantic AOI, enum { false, true, }; Default: false
            uint32 InfiniteAOI;                             // 8 Infinite AOI, enum { false, true, }; Default: false
            uint32 cooldown;                                // 9 cooldown, int, Min value: 0, Max value: 2147483647, Default value: 3000
        } flagdrop;
        //27 GAMEOBJECT_TYPE_MINI_GAME
        struct
        {
            uint32 gameType;                                //0
        } miniGame;
        //29 GAMEOBJECT_TYPE_CAPTURE_POINT
        struct
        {
            uint32 radius;                                  //0
            uint32 spell;                                   //1
            uint32 worldState1;                             //2
            uint32 worldstate2;                             //3
            uint32 winEventID1;                             //4
            uint32 winEventID2;                             //5
            uint32 contestedEventID1;                       //6
            uint32 contestedEventID2;                       //7
            uint32 progressEventID1;                        //8
            uint32 progressEventID2;                        //9
            uint32 neutralEventID1;                         //10
            uint32 neutralEventID2;                         //11
            uint32 neutralPercent;                          //12
            uint32 worldstate3;                             //13
            uint32 minSuperiority;                          //14
            uint32 maxSuperiority;                          //15
            uint32 minTime;                                 //16
            uint32 maxTime;                                 //17
            uint32 GiganticAOI;                             //18
            uint32 highlight;                               //19
            uint32 startingValue;                           //20
            uint32 unidirectional;                          //21
        } capturePoint;
        //30 GAMEOBJECT_TYPE_AURA_GENERATOR
        struct
        {
            uint32 startOpen;                               //0
            uint32 radius;                                  //1
            uint32 auraID1;                                 //2
            uint32 conditionID1;                            //3
            uint32 auraID2;                                 //4
            uint32 conditionID2;                            //5
            uint32 serverOnly;                              //6
        } auraGenerator;
        //31 GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY
        struct
        {
            uint32 mapID;                                   //0
            uint32 difficulty;                              //1
            uint32 DifficultyHeroic;                        // 2 Difficulty Heroic, References: animationdata, NoValue = 0
            uint32 DifficultyEpic;                          // 3 Difficulty Epic, References: animationdata, NoValue = 0
            uint32 DifficultyLegendary;                     // 4 Difficulty Legendary, References: animationdata, NoValue = 0
            uint32 HeroicAttachment;                        // 5 Heroic Attachment, References: gameobjectdisplayinfo, NoValue = 0
            uint32 ChallengeAttachment;                     // 6 Challenge Attachment, References: gameobjectdisplayinfo, NoValue = 0
            uint32 DifficultyAnimations;                    // 7 Difficulty Animations, References: GameObjectDiffAnim, NoValue = 0
            uint32 LargeAOI;                                // 8 Large AOI, enum { false, true, }; Default: false
            uint32 GiganticAOI;                             // 9 Gigantic AOI, enum { false, true, }; Default: false
            uint32 Legacy;                                  // 10 Legacy, enum { false, true, }; Default: false
        } dungeonDifficulty;
        //32 GAMEOBJECT_TYPE_BARBER_CHAIR
        struct
        {
            uint32 chairheight;                             //0
            uint32 heightOffset;                            //1
        } barberChair;
        //33 GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING
        struct
        {
            uint32 intactNumHits;                           //0
            uint32 creditProxyCreature;                     //1
            uint32 state1Name;                              //2
            uint32 intactEvent;                             //3
            uint32 damagedDisplayId;                        //4
            uint32 damagedNumHits;                          //5
            uint32 empty3;                                  //6
            uint32 empty4;                                  //7
            uint32 empty5;                                  //8
            uint32 damagedEvent;                            //9
            uint32 destroyedDisplayId;                      //10
            uint32 empty7;                                  //11
            uint32 empty8;                                  //12
            uint32 empty9;                                  //13
            uint32 destroyedEvent;                          //14
            uint32 empty10;                                 //15
            uint32 debuildingTimeSecs;                      //16
            uint32 empty11;                                 //17
            uint32 destructibleData;                        //18
            uint32 rebuildingEvent;                         //19
            uint32 empty12;                                 //20
            uint32 empty13;                                 //21
            uint32 damageEvent;                             //22
            uint32 empty14;                                 //23
        } building;
        //34 GAMEOBJECT_TYPE_GUILDBANK - empty
        //35 GAMEOBJECT_TYPE_TRAPDOOR
        struct
        {
            uint32 whenToPause;                             // 0
            uint32 startOpen;                               // 1
            uint32 autoClose;                               // 2
        } trapDoor;
        // GAMEOBJECT_TYPE_FLAGSTAND_2
        struct
        {
            uint32 lockId;                                  // 0
            uint32 pickupSpell;                             // 1
            uint32 data2;                                   // 2
            uint32 data3;                                   // 3
            uint32 data4;                                   // 4
            uint32 data5;                                   // 5
            uint32 data6;                                   // 6
            uint32 data7;                                   // 7
            uint32 data8;                                   // 8
            uint32 summonedGoAfterRemoveAura;               // 9
        } flagstand2;

        // not use for specific field access (only for output with loop by all filed), also this determinate max union size
        struct
        {
            uint32 data[MAX_GAMEOBJECT_DATA];
        } raw;
    };

    std::string AIName;
    uint32 ScriptId;

    // helpers
    bool IsDespawnAtAction() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:  return chest.consumable;
            case GAMEOBJECT_TYPE_GOOBER: return goober.consumable;
            default: return false;
        }
    }

    bool IsUsableMounted() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.allowMounted;
            case GAMEOBJECT_TYPE_TEXT: return text.allowMounted;
            case GAMEOBJECT_TYPE_GOOBER: return goober.allowMounted;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spellcaster.allowMounted;
            default: return false;
        }
    }

    uint32 GetLockId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.lockId;
            case GAMEOBJECT_TYPE_BUTTON:     return button.lockId;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.lockId;
            case GAMEOBJECT_TYPE_CHEST:      return chest.lockId;
            case GAMEOBJECT_TYPE_TRAP:       return trap.lockId;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.lockId;
            case GAMEOBJECT_TYPE_AREADAMAGE: return areadamage.lockId;
            case GAMEOBJECT_TYPE_CAMERA:     return camera.lockId;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.lockId;
            case GAMEOBJECT_TYPE_FLAGSTAND_2: return flagstand2.lockId;
            case GAMEOBJECT_TYPE_FISHINGHOLE:return fishinghole.lockId;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.lockId;
            default: return 0;
        }
    }

    bool GetDespawnPossibility() const                      // despawn at targeting of cast?
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.noDamageImmune;
            case GAMEOBJECT_TYPE_BUTTON:     return button.noDamageImmune;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.noDamageImmune;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.noDamageImmune;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.noDamageImmune;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.noDamageImmune;
            default: return true;
        }
    }

    uint32 GetCharges() const                               // despawn at uses amount
    {
        switch (type)
        {
            //case GAMEOBJECT_TYPE_TRAP:        return trap.charges;
            case GAMEOBJECT_TYPE_GUARDPOST:   return guardpost.charges;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spellcaster.charges;
            default: return 0;
        }
    }

    uint32 GetLinkedGameObjectEntry() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:       return chest.linkedTrapId;
            case GAMEOBJECT_TYPE_SPELL_FOCUS: return spellFocus.linkedTrapId;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.linkedTrapId;
            default: return 0;
        }
    }

    uint32 GetAutoCloseTime() const
    {
        uint32 autoCloseTime = 0;
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:          autoCloseTime = door.autoCloseTime; break;
            case GAMEOBJECT_TYPE_BUTTON:        autoCloseTime = button.autoCloseTime; break;
            case GAMEOBJECT_TYPE_TRAP:          autoCloseTime = trap.autoCloseTime; break;
            case GAMEOBJECT_TYPE_GOOBER:        autoCloseTime = goober.autoCloseTime; break;
            case GAMEOBJECT_TYPE_TRANSPORT:     autoCloseTime = transport.autoCloseTime; break;
            case GAMEOBJECT_TYPE_AREADAMAGE:    autoCloseTime = areadamage.autoCloseTime; break;
            default: break;
        }
        return autoCloseTime / IN_MILLISECONDS;              // prior to 3.0.3, conversion was / 0x10000;
    }

    uint32 GetLootId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:       return chest.lootId;
            case GAMEOBJECT_TYPE_FISHINGHOLE: return fishinghole.lootId;
            default: return 0;
        }
    }

    uint32 GetGossipMenuId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_QUESTGIVER:    return questgiver.gossipID;
            case GAMEOBJECT_TYPE_GOOBER:        return goober.gossipID;
            default: return 0;
        }
    }

    uint32 GetEventScriptId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_GOOBER:        return goober.eventId;
            case GAMEOBJECT_TYPE_CHEST:         return chest.eventId;
            case GAMEOBJECT_TYPE_CAMERA:        return camera.eventID;
            default: return 0;
        }
    }

    uint32 GetCooldown() const                              // Cooldown preventing goober and traps to cast spell
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_TRAP:        return trap.cooldown;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.cooldown;
            default: return 0;
        }
    }

    bool HasLargeAOI() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:                 return chest.LargeAOI;
            case GAMEOBJECT_TYPE_GENERIC:               return _generic.LargeAOI;
            case GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY:    return dungeonDifficulty.LargeAOI;
            default: return false;
        }
    }

    bool HasGiganticAOI() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:                  return door.GiganticAOI;
            case GAMEOBJECT_TYPE_BUTTON:                return button.GiganticAOI;
            case GAMEOBJECT_TYPE_QUESTGIVER:            return questgiver.GiganticAOI;
            case GAMEOBJECT_TYPE_CHEST:                 return chest.GiganticAOI;
            case GAMEOBJECT_TYPE_GENERIC:               return _generic.GiganticAOI;
            case GAMEOBJECT_TYPE_TRAP:                  return trap.GiganticAOI;
            case GAMEOBJECT_TYPE_SPELL_FOCUS:           return spellFocus.GiganticAOI;
            case GAMEOBJECT_TYPE_GOOBER:                return goober.GiganticAOI;
            case GAMEOBJECT_TYPE_SPELLCASTER:           return spellcaster.GiganticAOI;
            case GAMEOBJECT_TYPE_FLAGSTAND:             return flagstand.GiganticAOI;
            case GAMEOBJECT_TYPE_FLAGDROP:              return flagdrop.GiganticAOI;
            case GAMEOBJECT_TYPE_CAPTURE_POINT:         return capturePoint.GiganticAOI;
            case GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY:    return dungeonDifficulty.GiganticAOI;
            default: return false;
        }
    }

    bool HasInfiniteAOI() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:                  return door.InfiniteAOI;
            case GAMEOBJECT_TYPE_FLAGSTAND:             return flagstand.InfiniteAOI;
            case GAMEOBJECT_TYPE_FLAGDROP:              return flagdrop.InfiniteAOI;
            default: return false;
        }
    }

    bool HasTrueInfiniteAOI() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_MO_TRANSPORT:          return moTransport.TrueInfiniteAOI;
            default: return false;
        }
    }

    bool IsServerOnly() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_GENERIC:       return _generic.serverOnly;
            case GAMEOBJECT_TYPE_TRAP:          return trap.serverOnly;
            case GAMEOBJECT_TYPE_SPELL_FOCUS:   return spellFocus.serverOnly;
            case GAMEOBJECT_TYPE_AURA_GENERATOR:return auraGenerator.serverOnly;
            default: return false;
        }
    }

    uint32 GetTrackingQuestId() const
    {
        uint32 playerConditionID = 0;
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:
                playerConditionID = chest.conditionID1;
                break;
            case GAMEOBJECT_TYPE_GOOBER:
                playerConditionID = goober.conditionID1;
                break;
            // Maybe somes others gameobject types can have tracking quest
            default:
                break;
        }

        if (!playerConditionID)
            return 0;

        auto playerCondition = sPlayerConditionStore.LookupEntry(playerConditionID);
        if (!playerCondition || !(playerCondition->PrevQuestLogic & PrevQuestLogicFlags::TrackingQuest))
            return 0;

        return playerCondition->PrevQuestID[0];
    }

    uint32 GetVignetteId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:  return chest.SpawnVignette;
            case GAMEOBJECT_TYPE_GOOBER: return goober.SpawnVignette;
            default: return 0;
        }
    }
};

// From `gameobject_template_addon`
struct GameObjectTemplateAddon
{
    uint32  entry;
    uint32  faction;
    uint32  flags;
    uint32  mingold;
    uint32  maxgold;
    uint8   maxDuplicates;
};

// Benchmarked: Faster than std::map (insert/find)
typedef std::unordered_map<uint32, GameObjectTemplate> GameObjectTemplateContainer;
typedef std::unordered_map<uint32, GameObjectTemplateAddon> GameObjectTemplateAddonContainer;

class OPvPCapturePoint;
struct TransportAnimation;

union GameObjectValue
{
    //6 GAMEOBJECT_TYPE_TRAP
    struct
    {
        SpellTargetCheckTypes TargetSearcherCheckType;
    } Trap;
    //11 GAMEOBJECT_TYPE_TRANSPORT
    struct
    {
        uint32 PathProgress;
        TransportAnimation const* AnimationInfo;
        uint32 CurrentSeg;
    } Transport;
    //25 GAMEOBJECT_TYPE_FISHINGHOLE
    struct
    {
        uint32 MaxOpens;
    } FishingHole;
    //29 GAMEOBJECT_TYPE_CAPTURE_POINT
    struct
    {
        OPvPCapturePoint *OPvPObj;
    } CapturePoint;
    //33 GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING
    struct
    {
        uint32 Health;
        uint32 MaxHealth;
    } Building;
};

struct GameObjectLocale
{
    StringVector Name;
    StringVector CastBarCaption;
};

// `gameobject_addon` table
struct GameObjectAddon
{
    ::InvisibilityType InvisibilityType;
    uint32 InvisibilityValue;
};

typedef std::unordered_map<uint32, GameObjectAddon> GameObjectAddonContainer;

// client side GO show states
enum GOState
{
    GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
    GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
    GO_STATE_ACTIVE_ALTERNATIVE = 2,                        // show in world as used in alt way and not reset (closed door open by cannon fire)
    GO_STATE_PREPARE_TRANSPORT  = 24                        // reset transport to startpoint after endpoint
};

// from `gameobject`
struct GameObjectData
{
    explicit GameObjectData() : dbData(true) { }
    uint32 id;                                              // entry in gamobject_template
    uint16 mapid;
    uint32 phaseMask;
    float posX;
    float posY;
    float posZ;
    float orientation;
    G3D::Quat rotation;
    int32  spawntimesecs;
    uint32 animprogress;
    GOState go_state;
    uint16 spawnMask;
    uint8 artKit;
    uint32 ScriptId;
    bool dbData;
    uint32 gameEventId = 0;
};

// For containers:  [GO_NOT_READY]->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED->GO_READY        -> ...
// For bobber:      GO_NOT_READY  ->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED-><deleted>
// For door(closed):[GO_NOT_READY]->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED->GO_READY(close) -> ...
// For door(open):  [GO_NOT_READY]->GO_READY (open) ->GO_ACTIVATED (close)->GO_JUST_DEACTIVATED->GO_READY(open)  -> ...
enum LootState
{
    GO_NOT_READY = 0,
    GO_READY,                                               // can be ready but despawned, and then not possible activate until spawn
    GO_ACTIVATED,
    GO_JUST_DEACTIVATED
};

class Unit;
class GameObjectModel;

// 5 sec for bobber catch
#define FISHING_BOBBER_READY_TIME 5

class GameObject : public WorldObject, public GridObject<GameObject>, public MapObject
{
    public:
        explicit GameObject();
        ~GameObject();

        void BuildValuesUpdate(uint8 updatetype, ByteBuffer* data, Player* target) const;

        void AddToWorld();
        void RemoveFromWorld();
        void CleanupsBeforeDelete(bool finalCleanup = true);

        bool Create(uint32 guidlow, uint32 name_id, Map* map, uint32 phaseMask, float x, float y, float z, float ang, G3D::Quat const& rotation, uint32 animprogress, GOState go_state, uint32 artKit = 0);
        void Update(uint32 p_time);
        static GameObject* GetGameObject(WorldObject& object, uint64 guid);
        GameObjectTemplate const* GetGOInfo() const { return m_goInfo; }
        GameObjectTemplateAddon const* GetTemplateAddon() const { return m_goTemplateAddon; }
        GameObjectData const* GetGOData() const { return m_goData; }
        GameObjectValue const* GetGOValue() const { return &m_goValue; }

        bool IsTransport() const;
        bool IsDynTransport() const;
        bool IsDestructibleBuilding() const;

        uint32 GetDBTableGUIDLow() const { return m_DBTableGuid; }

        // z_rot, y_rot, x_rot - rotation angles around z, y and x axes
        void SetWorldRotationAngles(float z_rot, float y_rot, float x_rot);
        void SetWorldRotation(G3D::Quat rotation);
        void SetParentRotation(G3D::Quat const& rotation);      // transforms(rotates) transport's path
        int64 GetPackedWorldRotation() const { return m_packedRotation; }
        G3D::Quat const& GetWorldRotation() const { return m_worldRotation; }
        void SetOrientation(float orientation) = delete;

        // overwrite WorldObject function for proper name localization
        std::string const& GetNameForLocaleIdx(LocaleConstant locale_idx) const;

        void SaveToDB();
        void SaveToDB(uint32 mapid, uint16 spawnMask, uint32 phaseMask);
        bool LoadFromDB(uint32 guid, Map* map) { return LoadGameObjectFromDB(guid, map, false); }
        bool LoadGameObjectFromDB(uint32 guid, Map* map, bool addToMap = true);
        void DeleteFromDB();

        void SetOwnerGUID(uint64 owner)
        {
            // Owner already found and different than expected owner - remove object from old owner
            if (owner && GetOwnerGUID() && GetOwnerGUID() != owner)
            {
                ASSERT(false);
            }
            m_spawnedByDefault = false;                     // all object with owner is despawned after delay
            SetUInt64Value(GAMEOBJECT_FIELD_CREATED_BY, owner);
        }
        uint64 GetOwnerGUID() const { return GetUInt64Value(GAMEOBJECT_FIELD_CREATED_BY); }
        Unit* GetOwner() const;

        void SetSpellId(uint32 id)
        {
            m_spawnedByDefault = false;                     // all summoned object is despawned after delay
            m_spellId = id;
        }
        uint32 GetSpellId() const { return m_spellId;}

        void ForcedDespawn(uint32 msTimeToDespawn = 0);

        time_t GetRespawnTime() const { return m_respawnTime; }
        time_t GetRespawnTimeEx() const
        {
            time_t now = time(NULL);
            if (m_respawnTime > now)
                return m_respawnTime;
            else
                return now;
        }

        void SetRespawnTime(int32 respawn)
        {
            m_respawnTime = respawn > 0 ? time(NULL) + respawn : 0;
            m_respawnDelayTime = respawn > 0 ? respawn : 0;
        }
        void Respawn();
        bool isSpawned() const
        {
            return m_respawnDelayTime == 0 ||
                (m_respawnTime > 0 && !m_spawnedByDefault) ||
                (m_respawnTime == 0 && m_spawnedByDefault);
        }
        bool isSpawnedByDefault() const { return m_spawnedByDefault; }
        void SetSpawnedByDefault(bool b) { m_spawnedByDefault = b; }
        uint32 GetRespawnDelay() const { return m_respawnDelayTime; }
        void Refresh();
        void Delete();
        void getFishLoot(Loot* loot, Player* loot_owner);
        GOState GetGoState() const { return GOState(GetByteValue(GAMEOBJECT_FIELD_PERCENT_HEALTH, 0)); }
        void SetGoState(GOState state);
        GameobjectTypes GetGoType() const { return GameobjectTypes(GetByteValue(GAMEOBJECT_FIELD_PERCENT_HEALTH, 1)); }
        void SetGoType(GameobjectTypes type) { SetByteValue(GAMEOBJECT_FIELD_PERCENT_HEALTH, 1, type); }
        void SetGoHealth(uint8 health) { SetByteValue(GAMEOBJECT_FIELD_PERCENT_HEALTH, 3, health); }
        virtual uint32 GetTransportPeriod() const;
        uint8 GetGoArtKit() const { return GetByteValue(GAMEOBJECT_FIELD_STATE_SPELL_VISUAL_ID, 1); }
        void SetGoArtKit(uint8 artkit);
        uint8 GetGoAnimProgress() const { return GetByteValue(GAMEOBJECT_FIELD_STATE_SPELL_VISUAL_ID, 3); }
        void SetGoAnimProgress(uint8 animprogress) { SetByteValue(GAMEOBJECT_FIELD_STATE_SPELL_VISUAL_ID, 3, animprogress); }
        void SetGameobjectTransparence(uint8 transparency) { SetByteValue(GAMEOBJECT_FIELD_STATE_SPELL_VISUAL_ID, 0, transparency); }
        static void SetGoArtKit(uint8 artkit, GameObject* go, uint32 lowguid = 0);

        void SetPhaseMask(uint32 newPhaseMask, bool update);
        void EnableCollision(bool enable);
        void UpdateCollision();

        void Use(Unit* user);

        LootState getLootState() const { return m_lootState; }
        // Note: unit is only used when s = GO_ACTIVATED
        void SetLootState(LootState s, Unit* unit = NULL);

        uint16 GetLootMode() { return m_LootMode; }
        bool HasLootMode(uint16 lootMode) { return m_LootMode & lootMode; }
        void SetLootMode(uint16 lootMode) { m_LootMode = lootMode; }
        void AddLootMode(uint16 lootMode) { m_LootMode |= lootMode; }
        void RemoveLootMode(uint16 lootMode) { m_LootMode &= ~lootMode; }
        void ResetLootMode() { m_LootMode = LOOT_MODE_DEFAULT; }

        void AddToSkillupList(uint32 PlayerGuidLow) { m_SkillupList.push_back(PlayerGuidLow); }
        bool IsInSkillupList(uint32 PlayerGuidLow) const
        {
            for (std::list<uint32>::const_iterator i = m_SkillupList.begin(); i != m_SkillupList.end(); ++i)
                if (*i == PlayerGuidLow)
                    return true;

            return false;
        }
        void ClearSkillupList() { m_SkillupList.clear(); }

        void AddUniqueUse(Player* player);
        void AddUse() { ++m_usetimes; }

        uint32 GetUseCount() const { return m_usetimes; }
        uint32 GetUniqueUseCount() const { return m_unique_users.size(); }

        void SaveRespawnTime();

        Loot        loot;

        Player* GetLootRecipient() const;
        Group* GetLootRecipientGroup() const;
        bool IsLootRecipientGroupMember(uint64 guid) const { return m_lootRecipientGroupMembers.empty() || m_lootRecipientGroupMembers.find(guid) != m_lootRecipientGroupMembers.end(); }
        void SetLootRecipient(Unit* unit);
        bool IsLootAllowedFor(Player const* player) const;
        bool HasLootRecipient() const { return m_lootRecipient || m_lootRecipientGroup; }
        uint32 m_groupLootTimer;                            // (msecs)timer used for group loot
        uint32 lootingGroupLowGUID;                         // used to find group which is looting

        bool hasQuest(uint32 quest_id) const;
        bool hasInvolvedQuest(uint32 quest_id) const;
        bool ActivateToQuest(Player* target) const;
        void UseDoorOrButton(uint32 time_to_restore = 0, bool alternative = false, Unit* user = NULL);
                                                            // 0 = use `gameobject`.`spawntimesecs`
        void ResetDoorOrButton();

        void TriggeringLinkedGameObject(uint32 trapEntry, Unit* target);

        bool IsNeverVisible() const override;

        bool IsAlwaysVisibleFor(WorldObject const* seer) const;
        bool IsInvisibleDueToDespawn() const;

        uint8 getLevelForTarget(WorldObject const* target) const
        {
            if (Unit* owner = GetOwner())
                return owner->GetLevelForTarget(target);

            return 1;
        }

        GameObject* LookupFishingHoleAround(float range);

        void CastSpell(Unit* target, uint32 spell);
        void SendCustomAnim(uint32 anim);
        SpellInfo const* GetSpellForLock(Player const* player) const;
        bool IsAtInteractDistance(Player const* player, SpellInfo const* spell = nullptr) const;
        bool IsAtInteractDistance(Position const& pos, float radius) const;

        void ModifyHealth(int32 change, Unit* attackerOrHealer = NULL, uint32 spellId = 0);
        // sets GameObject type 33 destruction flags and optionally default health for that state
        void SetDestructibleState(GameObjectDestructibleState state, Player* eventInvoker = NULL, bool setHealth = false);
        GameObjectDestructibleState GetDestructibleState() const
        {
            if (HasFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_DESTROYED))
                return GO_DESTRUCTIBLE_DESTROYED;
            if (HasFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_DAMAGED))
                return GO_DESTRUCTIBLE_DAMAGED;
            return GO_DESTRUCTIBLE_INTACT;
        }

        void EventInform(uint32 eventId);

        virtual uint32 GetScriptId() const;
        GameObjectAI* AI() const { return m_AI; }

        std::string GetAIName() const;
        void SetDisplayId(uint32 displayid);
        uint32 GetDisplayId() const { return GetUInt32Value(GAMEOBJECT_FIELD_DISPLAY_ID); }

        uint32 GetFaction() const { return GetUInt32Value(GAMEOBJECT_FIELD_FACTION_TEMPLATE); }
        void SetFaction(uint32 faction) { SetUInt32Value(GAMEOBJECT_FIELD_FACTION_TEMPLATE, faction); }

        GameObjectModel* m_model;
        void GetRespawnPosition(float &x, float &y, float &z, float* ori = NULL) const;

        Transport* ToTransport() { if (GetGOInfo()->type == GAMEOBJECT_TYPE_TRANSPORT || GetGOInfo()->type == GAMEOBJECT_TYPE_MO_TRANSPORT) return reinterpret_cast<Transport*>(this); else return NULL; }
        Transport const* ToTransport() const { if (GetGOInfo()->type == GAMEOBJECT_TYPE_TRANSPORT || GetGOInfo()->type == GAMEOBJECT_TYPE_MO_TRANSPORT) return reinterpret_cast<Transport const*>(this); else return NULL; }

        float GetStationaryX() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionX(); return GetPositionX(); }
        float GetStationaryY() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionY(); return GetPositionY(); }
        float GetStationaryZ() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionZ(); return GetPositionZ(); }
        float GetStationaryO() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetOrientation(); return GetOrientation(); }
        void RelocateStationaryPosition(float x, float y, float z, float o) { m_stationaryPosition.Relocate(x, y, z, o); }

        uint16 GetAIAnimKitId() const override { return _animKitId; }
        void SetAnimKitId(uint16 animKitId, bool oneshot);

        void UpdateModelPosition();

        // Event handler
        EventProcessor m_Events;
        bool AIM_Initialize();
    protected:
        
        void UpdateModel();                                 // updates model in case displayId were changed
        uint32      m_spellId;
        time_t      m_respawnTime;                          // (secs) time of next respawn (or despawn if GO have owner()),
        uint32      m_respawnDelayTime;                     // (secs) if 0 then current GO state no dependent from timer
        LootState   m_lootState;
        bool        m_spawnedByDefault;
        time_t      m_cooldownTime;                         // used as internal reaction delay time store (not state change reaction).
        uint32      m_trapCooldownTime = 0;                 // higher resolution timer than time_t, used only for traps

        std::list<uint32> m_SkillupList;

        Player* m_ritualOwner;                              // used for GAMEOBJECT_TYPE_SUMMONING_RITUAL where GO is not summoned (no owner)
        std::set<uint64> m_unique_users;
        uint32 m_usetimes;

        typedef std::map<uint32, uint64> ChairSlotAndUser;
        ChairSlotAndUser ChairListSlots;

        uint32 m_DBTableGuid;                               ///< For new or temporary gameobjects is 0 for saved it is lowguid
        GameObjectTemplate const* m_goInfo;
        GameObjectTemplateAddon const* m_goTemplateAddon;
        GameObjectData const* m_goData;
        GameObjectValue m_goValue;

        int64 m_packedRotation;
        G3D::Quat m_worldRotation;
        Position m_stationaryPosition;

        uint64 m_lootRecipient;
        uint32 m_lootRecipientGroup;
        std::set<uint64> m_lootRecipientGroupMembers;
        uint16 m_LootMode;                                  // bitmask, default LOOT_MODE_DEFAULT, determines what loot will be lootable

    private:
        void RemoveFromOwner();
        void SwitchDoorOrButton(bool activate, bool alternative = false);
        void UpdatePackedRotation();

        //! Object distance/size - overridden from Object::_IsWithinDist. Needs to take in account proper GO size.
        bool _IsWithinDist(WorldObject const* obj, float dist2compare, bool /*is3D*/) const
        {
            //! Following check does check 3d distance
            return IsAtInteractDistance(obj->GetPosition(), dist2compare);
        }
        GameObjectAI* m_AI;
        uint16 _animKitId;
};

class ForcedGoDespawnDelayEvent : public BasicEvent
{
    public:
        ForcedGoDespawnDelayEvent(GameObject& owner) : BasicEvent(), m_owner(owner) { }
        bool Execute(uint64 e_time, uint32 p_time);

    private:
        GameObject& m_owner;
};

#endif
