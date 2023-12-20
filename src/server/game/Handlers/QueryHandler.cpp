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

#include "Common.h"
#include "Language.h"
#include "DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "UpdateMask.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "MapManager.h"
#include "Config.h"
#include "Group.h"
#include "Realm.h"

void WorldSession::SendNameQueryOpcode(ObjectGuid guid)
{
    ObjectGuid guid2 = 0;
    ObjectGuid guid3 = guid;

    Player* player = ObjectAccessor::FindPlayer(guid);
    CharacterNameData const* nameData = sWorld->GetCharacterNameData(GUID_LOPART(guid));

    WorldPacket data(SMSG_NAME_QUERY_RESPONSE, 500);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[1]);

    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[2]);

    data << uint8(!nameData);

    if (nameData)
    {
        data << uint32(realm.Id.Realm); // realmIdSecond
        data << uint32(1); // AccID
        data << uint8(nameData->m_class);
        data << uint8(nameData->m_race);
        data << uint8(nameData->m_level);
        data << uint8(nameData->m_gender);
    }

    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[3]);

    if (!nameData)
    {
        SendPacket(&data);
        return;
    }

    data.WriteBit(guid2[2]);
    data.WriteBit(guid2[7]);
    data.WriteBit(guid3[7]);
    data.WriteBit(guid3[2]);
    data.WriteBit(guid3[0]);
    data.WriteBit(0); //isDeleted ? Wod ?
    data.WriteBit(guid2[4]);
    data.WriteBit(guid3[5]);
    data.WriteBit(guid2[1]);
    data.WriteBit(guid2[3]);
    data.WriteBit(guid2[0]);

    DeclinedName const* names = nameData->m_declinedName;
    for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
        data.WriteBits(names ? names->name[i].size() : 0, 7);

    data.WriteBit(guid3[6]);
    data.WriteBit(guid3[3]);
    data.WriteBit(guid2[5]);
    data.WriteBit(guid3[1]);
    data.WriteBit(guid3[4]);
    data.WriteBits(nameData->m_name.size(), 6);
    data.WriteBit(guid2[6]);

    data.FlushBits();

    data.WriteByteSeq(guid3[6]);
    data.WriteByteSeq(guid3[0]);
    data.WriteString(nameData->m_name);
    data.WriteByteSeq(guid2[5]);
    data.WriteByteSeq(guid2[2]);
    data.WriteByteSeq(guid3[3]);
    data.WriteByteSeq(guid2[4]);
    data.WriteByteSeq(guid2[3]);
    data.WriteByteSeq(guid3[4]);
    data.WriteByteSeq(guid3[2]);
    data.WriteByteSeq(guid2[7]);

    if (names)
        for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
            data.WriteString(names->name[i]);

    data.WriteByteSeq(guid2[6]);
    data.WriteByteSeq(guid3[7]);
    data.WriteByteSeq(guid3[1]);
    data.WriteByteSeq(guid2[1]);
    data.WriteByteSeq(guid3[5]);
    data.WriteByteSeq(guid2[0]);

    SendPacket(&data);
}

void WorldSession::HandleNameQueryOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;

    uint8 bit14, bit1C;
    uint32 unk, unk1;

    guid[4] = recvData.ReadBit();
    bit14 = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    bit1C = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[4]);

    // virtual and native realm Addresses

    if (bit14)
        recvData >> unk;

    if (bit1C)
        recvData >> unk1;

    // This is disable by default to prevent lots of console spam
    // TC_LOG_INFO("network", "HandleNameQueryOpcode %u", guid);

    SendNameQueryOpcode(guid);
}

void WorldSession::SendRealmNameQueryOpcode(uint32 realmId)
{
    RealmNameMap::const_iterator iter = realmNameStore.find(realmId);

    bool found = iter != realmNameStore.end();
    std::string realmName = found ? iter->second : "";

    WorldPacket data(SMSG_REALM_NAME_QUERY_RESPONSE);
    data << uint8(!found);
    data << uint32(realmId);

    if (found)
    {
        data.WriteBits(realmName.length(), 8);
        data.WriteBit(realmId == realm.Id.Realm);
        data.WriteBits(realmName.length(), 8);
        data.FlushBits();

        data.WriteString(realmName);
        data.WriteString(realmName);
    }

    SendPacket(&data);
}

void WorldSession::HandleRealmNameQueryOpcode(WorldPacket& recvPacket)
{
    uint32 realmId;
    recvPacket >> realmId;
    SendRealmNameQueryOpcode(realmId);
}

void WorldSession::HandleQueryTimeOpcode(WorldPacket & /*recvData*/)
{
    SendQueryTimeResponse();
}

void WorldSession::SendQueryTimeResponse()
{
    WorldPacket data(SMSG_QUERY_TIME_RESPONSE, 4+4);
    data << uint32(time(NULL));
    data << uint32(sWorld->GetNextDailyQuestsResetTime() - time(NULL));
    SendPacket(&data);
}

void WorldSession::SendServerWorldInfo()
{
    Map* map = GetPlayer()->GetMap();
    bool IsInInstance = map->IsRaidOrHeroicDungeon();                                               // Check being in raid / heroic dungeon map.
    uint32 InstanceGroupSize = IsInInstance ? map->ToInstanceMap()->GetPlayersCountExceptGMs() : 0; // Check if we need to send the instance group size - for Flex Raids.
    uint32 difficultyNumberToDisplay = 0;                                                           // Number to display in minimap text.

    switch (map->GetDifficulty())
    {
        case DUNGEON_DIFFICULTY_HEROIC:
            difficultyNumberToDisplay = 5;
            break;
        case RAID_DIFFICULTY_10MAN_NORMAL:
        case RAID_DIFFICULTY_10MAN_HEROIC:
            difficultyNumberToDisplay = 10;
            break;
        case RAID_DIFFICULTY_25MAN_NORMAL:
        case RAID_DIFFICULTY_25MAN_HEROIC:
        case RAID_DIFFICULTY_25MAN_LFR:
            difficultyNumberToDisplay = 25;
            break;
        case RAID_DIFFICULTY_40MAN:
            difficultyNumberToDisplay = 40;
            break;
        case SCENARIO_DIFFICULTY_HEROIC:
            difficultyNumberToDisplay = 3;
            break;
        case RAID_DIFFICULTY_1025MAN_FLEX:
            if (InstanceGroupSize < 10)
                InstanceGroupSize = 10;
            difficultyNumberToDisplay = InstanceGroupSize;
            break;
        case REGULAR_DIFFICULTY:
        case DUNGEON_DIFFICULTY_NORMAL:
        case DUNGEON_DIFFICULTY_CHALLENGE:
        case SCENARIO_DIFFICULTY_NORMAL:
        default:
            break;
    }

    WorldPacket data(SMSG_WORLD_SERVER_INFO);

    // Bitfields have wrong order
    data.WriteBit(IsInInstance);                                    // In Instance
    data.WriteBit(0);                                               // HasRestrictedLevel
    data.WriteBit(0);                                               // HasRestrictedMoney
    data.WriteBit(0);                                               // HasGroupSize

    //if (unk1)
    //    data << uint32(0);

    data << uint8(0);                                               // IsOnTournamentRealm
    data << uint32(sWorld->GetNextWeeklyQuestsResetTime() - WEEK);  // LastWeeklyReset (not instance reset)
    data << uint32(map->GetDifficulty());

    //if (unk2)
    //    data << uint32(0);
    if (IsInInstance)
        data << uint32(difficultyNumberToDisplay);
    //if (unk3)
    //    data << uint32(0);

    SendPacket(&data);
}

/// Only _static_ data is sent in this packet !!!
void WorldSession::HandleCreatureQueryOpcode(WorldPacket& recvData)
{
    uint32 entry;
    recvData >> entry;

    WorldPacket data(SMSG_CREATURE_QUERY_RESPONSE, 500);

    CreatureTemplate const* creatureInfo = sObjectMgr->GetCreatureTemplate(entry);

    data << uint32(entry);
    data.WriteBit(creatureInfo != 0); // Has data

    if (creatureInfo)
    {
        std::string Name, FemaleName, Title;
        Name = creatureInfo->Name;
        FemaleName = creatureInfo->FemaleName;
        Title = creatureInfo->SubName;

        uint8 qItemsSize = 0;

        for (int i = 0; i < MAX_CREATURE_QUEST_ITEMS; i++)
            if (creatureInfo->questItems[i] != 0)
                qItemsSize++;

        LocaleConstant locale = GetSessionDbLocaleIndex();

        if (locale >= 0)
        {
            if (CreatureLocale const* creatureLocale = sObjectMgr->GetCreatureLocale(entry))
            {
                ObjectMgr::GetLocaleString(creatureLocale->Name, locale, Name);
                ObjectMgr::GetLocaleString(creatureLocale->FemaleName, locale, FemaleName);
                ObjectMgr::GetLocaleString(creatureLocale->Title, locale, Title);
            }
        }

        TC_LOG_DEBUG("network", "WORLD: CMSG_CREATURE_QUERY '%s' - Entry: %u.", creatureInfo->Name.c_str(), entry);

        data.WriteBits(Title.length() ? Title.length() + 1 : 0, 11);
        data.WriteBits(qItemsSize, 22);                       // Quest items
        data.WriteBits(0, 11);

        for (int i = 0; i < 4; i++)
        {            
            data.WriteBits(i == 0 ? Name.length() + 1 : 0, 11);
            data.WriteBits(0, 11);
        }

        data.WriteBit(creatureInfo->RacialLeader);
        data.WriteBits(creatureInfo->IconName.length() + 1, 6);
        data.FlushBits();

        data << uint32(creatureInfo->KillCredit[0]);                  // New in 3.1, kill credit
        data << uint32(creatureInfo->Modelid4);                       // Modelid4
        data << uint32(creatureInfo->Modelid2);                       // Modelid2
        data << uint32(creatureInfo->expansion);                      // Expansion Required
        data << uint32(creatureInfo->type);                           // CreatureType.dbc
        data << float(creatureInfo->ModHealth);                       // Hp modifier
        data << uint32(creatureInfo->type_flags);                     // Flags
        data << uint32(creatureInfo->type_flags2);                    // Flags2
        data << uint32(creatureInfo->rank);                           // Creature Rank (elite, boss, etc)
        data << uint32(creatureInfo->movementId);                     // CreatureMovementInfo.dbc
        data << Name;

        if (Title != "")
            data << Title;                                            // Subname

        data << uint32(creatureInfo->Modelid1);                       // Modelid1
        data << uint32(creatureInfo->Modelid3);                       // Modelid3

        if (creatureInfo->IconName != "")
            data << creatureInfo->IconName;                           // "Directions" for guard, string for Icons 2.3.0

        for (uint32 i = 0; i < MAX_CREATURE_QUEST_ITEMS; ++i)
            if (creatureInfo->questItems[i] != 0)
                data << uint32(creatureInfo->questItems[i]);          // ItemId[6], quest drop

        data << uint32(creatureInfo->KillCredit[1]);                  // New in 3.1, kill credit
        data << float(creatureInfo->ModMana);                         // Mana modifier
        data << uint32(creatureInfo->family);                         // CreatureFamily.dbc

        TC_LOG_DEBUG("network", "WORLD: Sent SMSG_CREATURE_QUERY_RESPONSE");
    }
    else
    {
        data.FlushBits();
        TC_LOG_DEBUG("network", "WORLD: CMSG_CREATURE_QUERY - NO CREATURE INFO! (ENTRY: %u)", entry);
    }

    SendPacket(&data);
}

/// Only _static_ data is sent in this packet !!!
void WorldSession::HandleGameObjectQueryOpcode(WorldPacket& recvData)
{
    uint32 entry;
    ObjectGuid guid;

    recvData >> entry;

    guid[5] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[0]);

    const GameObjectTemplate* info = sObjectMgr->GetGameObjectTemplate(entry);

    WorldPacket data (SMSG_GAMEOBJECT_QUERY_RESPONSE, 150);
    data.WriteBit(info != NULL);
    data << uint32(entry);

    size_t pos = data.wpos();
    data << uint32(0);

    if (info)
    {
        std::string Name;
        std::string IconName;
        std::string CastBarCaption;

        Name = info->name;
        IconName = info->IconName;
        CastBarCaption = info->castBarCaption;

        int loc_idx = GetSessionDbLocaleIndex();
        if (loc_idx >= 0)
        {
            if (GameObjectLocale const* gl = sObjectMgr->GetGameObjectLocale(entry))
            {
                ObjectMgr::GetLocaleStringOld(gl->Name, loc_idx, Name);
                ObjectMgr::GetLocaleStringOld(gl->CastBarCaption, loc_idx, CastBarCaption);
            }
        }

        TC_LOG_DEBUG("network", "WORLD: CMSG_GAMEOBJECT_QUERY '%s' - Entry: %u. ", info->name.c_str(), entry);

        data << uint32(info->type);
        data << uint32(info->displayId);
        data << Name;
        data << uint8(0) << uint8(0) << uint8(0);           // name2, name3, name4
        data << IconName;                                   // 2.0.3, string. Icon name to use instead of default icon for go's (ex: "Attack" makes sword)
        data << CastBarCaption;                             // 2.0.3, string. Text will appear in Cast Bar when using GO (ex: "Collecting")
        data << info->unk1;                                 // 2.0.3, string

        data.append(info->raw.data, MAX_GAMEOBJECT_DATA);
        data << float(info->size);                          // go size

        data << uint8(MAX_GAMEOBJECT_QUEST_ITEMS);

        for (uint32 i = 0; i < MAX_GAMEOBJECT_QUEST_ITEMS; ++i)
            data << uint32(info->questItems[i]);            // itemId[6], quest drop

        data << int32(info->unkInt32);                      // 4.x, unknown

        data.put(pos, uint32(data.wpos() - (pos + 4)));
        TC_LOG_DEBUG("network", "WORLD: Sent SMSG_GAMEOBJECT_QUERY_RESPONSE");
    }
    else
    {
        TC_LOG_DEBUG("network", "WORLD: CMSG_GAMEOBJECT_QUERY - Missing gameobject info for (GUID: %u, ENTRY: %u)",
            GUID_LOPART((uint64)guid), entry);
        TC_LOG_DEBUG("network", "WORLD: Sent SMSG_GAMEOBJECT_QUERY_RESPONSE");
    }

    SendPacket(&data);
}

void WorldSession::HandleCorpseQueryOpcode(WorldPacket& /*recvData*/)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_CORPSE_QUERY");

    Corpse* corpse = GetPlayer()->GetCorpse();

    if (!corpse)
    {
        WorldPacket data(SMSG_CORPSE_QUERY, 1);
        data.WriteBits(0, 9); // Not found + guid stream
        for (int i = 0; i < 5; i++)
            data << uint32(0);
        SendPacket(&data);
        return;
    }

    uint32 mapId = corpse->GetMapId();
    float x = corpse->GetPositionX();
    float y = corpse->GetPositionY();
    float z = corpse->GetPositionZ();
    uint32 corpseMapId = mapId;

    // if corpse at different map
    if (mapId != _player->GetMapId())
    {
        // search entrance map for proper show entrance
        if (MapEntry const* corpseMapEntry = sMapStore.LookupEntry(mapId))
        {
            if (corpseMapEntry->IsDungeon() && corpseMapEntry->entrance_map >= 0)
            {
                // if corpse map have entrance
                if (Map const* entranceMap = sMapMgr->CreateBaseMap(corpseMapEntry->entrance_map))
                {
                    mapId = corpseMapEntry->entrance_map;
                    x = corpseMapEntry->entrance_x;
                    y = corpseMapEntry->entrance_y;
                    z = entranceMap->GetHeight(GetPlayer()->GetPhaseMask(), x, y, MAX_HEIGHT);
                }
            }
        }
    }

    _player->SendCorpseReclaimDelay();

    ObjectGuid corpseGuid = 0; // need correct condition, guid shouldn't always be sent to player (corpse->GetGUID())

    WorldPacket data(SMSG_CORPSE_QUERY, 9 + 1 + (4 * 5));
    data.WriteBit(corpseGuid[0]);
    data.WriteBit(corpseGuid[3]);
    data.WriteBit(corpseGuid[2]);
    data.WriteBit(1); // Corpse Found
    data.WriteBit(corpseGuid[5]);
    data.WriteBit(corpseGuid[4]);
    data.WriteBit(corpseGuid[1]);
    data.WriteBit(corpseGuid[7]);
    data.WriteBit(corpseGuid[6]);

    data.WriteByteSeq(corpseGuid[5]);
    data << float(z);
    data.WriteByteSeq(corpseGuid[1]);
    data << uint32(mapId);
    data.WriteByteSeq(corpseGuid[6]);
    data.WriteByteSeq(corpseGuid[4]);
    data << float(x);
    data.WriteByteSeq(corpseGuid[3]);
    data.WriteByteSeq(corpseGuid[7]);
    data.WriteByteSeq(corpseGuid[2]);
    data.WriteByteSeq(corpseGuid[0]);
    data << int32(corpseMapId);
    data << float(y);
    SendPacket(&data);
}

// hack fix
void WorldSession::HandleNpcTextQueryOpcode(WorldPacket& recvData)
{
    uint32 textID;
    ObjectGuid guid;

    recvData >> textID;

    TC_LOG_DEBUG("network", "WORLD: CMSG_NPC_TEXT_QUERY ID '%u'", textID);

    guid[4] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[6]);

    GossipText const* pGossip = sObjectMgr->GetGossipText(textID);

    WorldPacket data(SMSG_NPC_TEXT_UPDATE, 1 + 4 + 64);
    data << textID;
    data << uint32(64);                                 // size (8 * 4) * 2

    data << float(pGossip ? pGossip->Options[0].Probability : 0);
    for (int i = 0; i < MAX_GOSSIP_TEXT_OPTIONS - 1; i++)
        data << float(0);

    //data << textID;    // should be a broadcast id   
    data << pGossip->Options[0].BroadcastTextID;
                        
    for (int i = 0; i < MAX_GOSSIP_TEXT_OPTIONS - 1; i++)
        data << uint32(0);

    data.WriteBit(1);                                   // has data
    data.FlushBits();

    SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_NPC_TEXT_UPDATE");
}

/// Only _static_ data is sent in this packet !!!
void WorldSession::HandlePageTextQueryOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_PAGE_TEXT_QUERY");

    uint32 pageID;
    ObjectGuid guid;

    recvData >> pageID;

    guid[2] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[2]);

    while (pageID)
    {
        WorldPacket data(SMSG_PAGE_TEXT_QUERY_RESPONSE);

        PageText const* pageText = sObjectMgr->GetPageText(pageID);

        data.WriteBit(pageText != NULL);

        if (pageText)
        {
            std::string Text = pageText->Text;
            int loc_idx = GetSessionDbLocaleIndex();
            if (loc_idx >= 0)
                if (PageTextLocale const* player = sObjectMgr->GetPageTextLocale(pageID))
                    ObjectMgr::GetLocaleStringOld(player->Text, loc_idx, Text);

            data.WriteBits(Text.size(), 12);

            data.FlushBits();

            data << uint32(pageText->NextPage);
            data << uint32(pageID);

            data.WriteString(Text);
            data << uint32(pageID);
        }
        else
        {
            data.FlushBits();
            data << uint32(0);
        }

        pageID = pageText ? pageText->NextPage : 0;

        SendPacket(&data);

        TC_LOG_DEBUG("network", "WORLD: Sent SMSG_PAGE_TEXT_QUERY_RESPONSE");
    }
}

void WorldSession::HandleCorpseMapPositionQuery(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Recv CMSG_CORPSE_MAP_POSITION_QUERY");

    ObjectGuid corpseGuid;
    recvData.ReadGuidMask(corpseGuid, 7, 6, 3, 0, 4, 1, 5, 2);
    recvData.ReadGuidBytes(corpseGuid, 1, 6, 0, 5, 3, 2, 4, 7);

    WorldPacket data(SMSG_CORPSE_MAP_POSITION_QUERY_RESPONSE, 4+4+4+4);
    data << float(0);
    data << float(0);
    data << float(0);
    data << float(0);
    SendPacket(&data);
}

void WorldSession::HandleQuestNPCQuery(WorldPacket& recvData)
{
    std::map<uint32, std::vector<uint32>> quests;
    for (int i = 0; i < 50; ++i)
    {
        uint32 questId;
        recvData >> questId;

        /// @todo verify if we should only send completed quests questgivers
        if (sObjectMgr->GetQuestTemplate(questId) && _player->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
        {
            auto creatures = sObjectMgr->GetCreatureQuestInvolvedRelationReverseBounds(questId);
            for (auto it = creatures.first; it != creatures.second; ++it)
                quests[questId].push_back(it->second);

            auto gos = sObjectMgr->GetGOQuestInvolvedRelationReverseBounds(questId);
            for (auto it = gos.first; it != gos.second; ++it)
                quests[questId].push_back(it->second | 0x80000000); // GO mask
        }
    }

    uint32 count;
    recvData >> count;

    WorldPacket data(SMSG_QUEST_NPC_QUERY_RESPONSE, 3 + count * 14);
    data.WriteBits(quests.size(), 21);

    for (auto it = quests.begin(); it != quests.end(); ++it)
        data.WriteBits(it->second.size(), 22);

    data.FlushBits();

    for (auto it = quests.begin(); it != quests.end(); ++it)
    {
        data << uint32(it->first);
        for (const auto& entry : it->second)
            data << uint32(entry);
    }

    SendPacket(&data);
}

void WorldSession::HandleQuestPOIQuery(WorldPacket& recvData)
{
    uint32 count = recvData.ReadBits(22);

    if (count > MAX_QUEST_LOG_SIZE)
    {
        recvData.rfinish();
        return;
    }

    ByteBuffer poiData;

    WorldPacket data(SMSG_QUEST_POI_QUERY_RESPONSE, 4+(4+4)*count);
    data.WriteBits(count, 20);

    for (uint32 i = 0; i < count; ++i)
    {
        uint32 questId;
        recvData >> questId;

        bool questOk = false;

        uint16 questSlot = _player->FindQuestSlot(questId);

        if (questSlot != MAX_QUEST_LOG_SIZE)
            questOk =_player->GetQuestSlotQuestId(questSlot) == questId;

        if (questOk)
        {
            QuestPOIVector const* POI = sObjectMgr->GetQuestPOIVector(questId);

            if (POI)
            {
                data.WriteBits(POI->size(), 18);                // POI count bits

                for (QuestPOIVector::const_iterator itr = POI->begin(); itr != POI->end(); ++itr)
                {
                    data.WriteBits(itr->points.size(), 21);     // POI points count bits

                    poiData << uint32(itr->FloorId);            // floor id

                    for (std::vector<QuestPOIPoint>::const_iterator itr2 = itr->points.begin(); itr2 != itr->points.end(); ++itr2)
                    {
                        poiData << int32(itr2->x);              // POI point x
                        poiData << int32(itr2->y);              // POI point y
                    }

                    poiData << int32(itr->ObjectiveIndex);      // objective index
                    poiData << uint32(itr->Id);                 // POI index
                    poiData << uint32(0);                       // unknown (new 5.x.x)
                    poiData << uint32(0);                       // unknown (new 5.x.x)
                    poiData << uint32(itr->MapId);              // mapid
                    poiData << uint32(itr->points.size());      // POI points count
                    poiData << uint32(itr->AreaId);             // areaid
                    poiData << uint32(0);                       // unknown (new 5.x.x)
                    poiData << uint32(itr->Unk4);               // unknown
                    poiData << uint32(itr->Unk3);               // unknown
                }

                poiData << uint32(questId);                     // quest ID
                poiData << uint32(POI->size());                 // POI count
            }
            else
            {
                poiData << uint32(questId);
                poiData << uint32(0);

                data.WriteBits(0, 18);
            }
        }
        else
        {
            poiData << uint32(questId);
            poiData << uint32(0);

            data.WriteBits(0, 18);
        }
    }

    poiData << uint32(count);

    data.FlushBits();
    data.append(poiData);

    SendPacket(&data);
}

void WorldSession::HandleQueryCountdownTimer(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_QUERY_COUNTDOWN_TIMER");

    recvData.read_skip<uint32>();
}
