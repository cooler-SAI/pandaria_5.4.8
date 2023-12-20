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

#include "AccountMgr.h"
#include "ArenaTeam.h"
#include "Battleground.h"
#include "BattlePayMgr.h"
#include "CalendarMgr.h"
#include "Chat.h"
#include "Common.h"
#include "DatabaseEnv.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "LFGMgr.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Pet.h"
#include "PlayerDump.h"
#include "Player.h"
#include "Realm.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "SocialMgr.h"
#include "SystemConfig.h"
#include "UpdateMask.h"
#include "Util.h"
#include "QueryHolder.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ServiceMgr.h"
#include "ServiceBoost.h"

#ifdef ELUNA
#include "HookMgr.h"
#endif
class LoginQueryHolder : public CharacterDatabaseQueryHolder
{
private:
    uint32 m_accountId;
    uint64 m_guid;
public:
    LoginQueryHolder(uint32 accountId, uint64 guid)
        : m_accountId(accountId), m_guid(guid) { }
    uint64 GetGuid() const { return m_guid; }
    uint32 GetAccountId() const { return m_accountId; }
    bool Initialize();
};

bool LoginQueryHolder::Initialize()
{
    SetSize(MAX_PLAYER_LOGIN_QUERY);

    bool res = true;
    uint32 lowGuid = GUID_LOPART(m_guid);

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_FROM, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_INSTANCE);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BOUND_INSTANCES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_AURAS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_AURAS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SPELL);
    stmt->setUInt32(0, lowGuid);
    stmt->setUInt32(1, m_accountId);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SPELLS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_QUESTSTATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_QUEST_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_QUEST_OBJECTIVE_STATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_QUEST_OBJECTIVE_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_DAILYQUESTSTATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_DAILY_QUEST_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_WEEKLYQUESTSTATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_WEEKLY_QUEST_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_MONTHLYQUESTSTATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_MONTHLY_QUEST_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SEASONALQUESTSTATUS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SEASONAL_QUEST_STATUS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_REPUTATION);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_REPUTATION, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_INVENTORY);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_INVENTORY, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_VOID_STORAGE);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_VOID_STORAGE, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_ACTIONS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_ACTIONS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_MAILCOUNT);
    stmt->setUInt32(0, lowGuid);
    stmt->setUInt64(1, uint64(time(NULL)));
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_MAIL_COUNT, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_MAILDATE);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_MAIL_DATE, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SOCIALLIST);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SOCIAL_LIST, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_HOMEBIND);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_HOME_BIND, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SPELLCOOLDOWNS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SPELL_COOLDOWNS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SPELL_CHARGES);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SPELL_CHARGES, stmt);

    if (sWorld->getBoolConfig(CONFIG_DECLINED_NAMES_USED))
    {
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_DECLINEDNAMES);
        stmt->setUInt32(0, lowGuid);
        res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_DECLINED_NAMES, stmt);
    }

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GUILD_MEMBER);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_GUILD, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_ACHIEVEMENTS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_ACHIEVEMENTS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_CRITERIAPROGRESS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_CRITERIA_PROGRESS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_EQUIPMENTSETS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_EQUIPMENT_SETS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_CUF_PROFILES);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_CUF_PROFILES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_BGDATA);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BG_DATA, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_GLYPHS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_GLYPHS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_TALENTS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_TALENTS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_ACCOUNT_DATA);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_ACCOUNT_DATA, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SKILLS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SKILLS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_RANDOMBG);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_RANDOM_BG, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_WEEKENDBG);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_WEEKEND_BG, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_BANNED);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BANNED, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_QUESTSTATUSREW);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_QUEST_STATUS_REW, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_INSTANCELOCKTIMES);
    stmt->setUInt32(0, m_accountId);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_INSTANCE_LOCK_TIMES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_CURRENCY);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_CURRENCY, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BATTLE_PETS);
    stmt->setUInt32(0, m_accountId);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BATTLE_PETS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BATTLE_PET_SLOTS);
    stmt->setUInt32(0, m_accountId);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BATTLE_PET_SLOTS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CURRENT_PET_ID);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_CURRENT_PET_ID, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_AURA_EFFECTS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_AURA_EFFECT, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_RESEARCH_DIGSITES);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_RESEARCH_DIGSITES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_RESEARCH_HISTORY);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_RESEARCH_HISTORY, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_RESEARCH_PROJECTS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_RESEARCH_PROJECTS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_LOOTLOCKOUTS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOOTLOCKOUTS, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_SERVICES);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_SERVICES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_COMPLETED_CHALLENGES);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_COMPLETED_CHALLENGES, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BONUS_ROLL);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BONUS_ROLL, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_DESERTER_INFO);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_DESERTER_INFO, stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BATTLEGROUND_STATS);
    stmt->setUInt32(0, lowGuid);
    res &= SetPreparedQuery(PLAYER_LOGIN_QUERY_LOAD_BATTLGEROUND_STATS, stmt);

    return res;
}

void WorldSession::HandleCharEnum(PreparedQueryResult result)
{
    uint32 charCount = 0;
    ByteBuffer bitBuffer;
    ByteBuffer dataBuffer;

    if (HasBoost() && !GetBoost()->GetCurrentAction())
        sBattlePayMgr->SendBattlePayDistributionUpdate(this, BATTLE_PAY_SERVICE_BOOST, CHARACTER_BOOST_ALLOW);

    // Sended before SMSG_CHAR_ENUM
    // must be procceded before BuildEnumData, because of unsetting bosted character guid
    if (GetBoost()->GetCurrentAction() == CHARACTER_BOOST_APPLIED)
        GetBoost()->HandleCharacterBoost();

    if (result)
    {
        _legitCharacters.clear();

        charCount = uint32(result->GetRowCount());
        bitBuffer.reserve(24 * charCount / 8);
        dataBuffer.reserve(charCount * 381);

        bitBuffer.WriteBits(0, 21); // factionChangeRestrictions - raceId / mask loop
        bitBuffer.WriteBits(charCount, 16);

        do
        {
            uint32 guidLow = (*result)[0].GetUInt32();

            TC_LOG_INFO("network", "Loading char guid %u from account %u.", guidLow, GetAccountId());

            Player::BuildEnumData(result, &dataBuffer, &bitBuffer, GetBoost()->IsBoosting(guidLow));

            // Do not allow banned characters to log in
            if (!(*result)[20].GetUInt32())
                _legitCharacters.insert(guidLow);

            if (!sWorld->HasCharacterNameData(guidLow)) // This can happen if characters are inserted into the database manually. Core hasn't loaded name data yet.
                sWorld->AddCharacterNameData(guidLow, (*result)[1].GetString(), (*result)[4].GetUInt8(), (*result)[2].GetUInt8(), (*result)[3].GetUInt8(), (*result)[7].GetUInt8());
        }
        while (result->NextRow());

        bitBuffer.WriteBit(1); // Sucess
        bitBuffer.FlushBits();
    }
    else
    {
        bitBuffer.WriteBits(0, 21);
        bitBuffer.WriteBits(0, 16);
        bitBuffer.WriteBit(1); // Success
        bitBuffer.FlushBits();
    }

    WorldPacket data(SMSG_CHAR_ENUM, 7 + bitBuffer.size() + dataBuffer.size());

    data.append(bitBuffer);

    if (charCount)
        data.append(dataBuffer);

    SendPacket(&data);

    // Sended after SMSG_CHAR_ENUM
    if (GetBoost()->GetCurrentAction() == CHARACTER_BOOST_ITEMS)
        GetBoost()->HandleCharacterBoost();
}


void WorldSession::HandleCharEnumOpcode(WorldPacket & /*recvData*/)
{
    // remove expired bans
    //PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_EXPIRED_BANS);
    //CharacterDatabase.Execute(stmt);
    CharacterDatabasePreparedStatement* stmt;

    /// get all the data necessary for loading all characters (along with their pets) on the account

    if (sWorld->getBoolConfig(CONFIG_DECLINED_NAMES_USED))
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ENUM_DECLINED_NAME);
    else
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ENUM);

    stmt->setUInt32(0, GetAccountId());

    //_charEnumCallback = CharacterDatabase.AsyncQuery(stmt);
    _queryProcessor.AddCallback(CharacterDatabase.AsyncQuery(stmt).WithPreparedCallback(std::bind(&WorldSession::HandleCharEnum, this, std::placeholders::_1)));
}

void WorldSession::HandleCharCreateOpcode(WorldPacket& recvData)
{
    uint8 hairStyle, face, facialHair, hairColor, race_, class_, skin, gender, outfitId;

    recvData >> outfitId >> hairStyle >> class_ >> skin;
    recvData >> face >> race_ >> facialHair >> gender >> hairColor;

    uint32 nameLength = recvData.ReadBits(6);
    uint8 unk = recvData.ReadBit();
    std::string name = recvData.ReadString(nameLength);

    if (unk)
        recvData.read_skip<uint32>();

    WorldPacket data(SMSG_CHAR_CREATE, 1);                  // returned with diff.values in all cases

    if (GetSecurity() == SEC_PLAYER)
    {
        if (uint32 mask = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_DISABLED))
        {
            bool disabled = false;

            uint32 team = Player::TeamForRace(race_);
            switch (team)
            {
            case ALLIANCE:
                disabled = mask & (1 << 0);
                break;
            case HORDE:
                disabled = mask & (1 << 1);
                break;
            }

            if (disabled)
            {
                data << uint8(CHAR_CREATE_DISABLED);
                SendPacket(&data);
                return;
            }
        }
    }

    ChrClassesEntry const* classEntry = sChrClassesStore.LookupEntry(class_);
    if (!classEntry)
    {
        data << uint8(CHAR_CREATE_FAILED);
        SendPacket(&data);
        TC_LOG_ERROR("network", "Class (%u) not found in DBC while creating new char for account (ID: %u): wrong DBC files or cheater?", class_, GetAccountId());
        return;
    }

    ChrRacesEntry const* raceEntry = sChrRacesStore.LookupEntry(race_);
    if (!raceEntry)
    {
        data << uint8(CHAR_CREATE_FAILED);
        SendPacket(&data);
        TC_LOG_ERROR("network", "Race (%u) not found in DBC while creating new char for account (ID: %u): wrong DBC files or cheater?", race_, GetAccountId());
        return;
    }
    /*
    // prevent character creating Expansion race without Expansion account
    if (raceEntry->expansion > Expansion())
    {
    data << uint8(CHAR_CREATE_EXPANSION);
    TC_LOG_ERROR("network", "Expansion %u account:[%d] tried to Create character with expansion %u race (%u)", Expansion(), GetAccountId(), raceEntry->expansion, race_);
    SendPacket(&data);
    return;
    }

    // prevent character creating Expansion class without Expansion account
    if (classEntry->expansion > Expansion())
    {
    data << uint8(CHAR_CREATE_EXPANSION_CLASS);
    TC_LOG_ERROR("network", "Expansion %u account:[%d] tried to Create character with expansion %u class (%u)", Expansion(), GetAccountId(), classEntry->expansion, class_);
    SendPacket(&data);
    return;
    }*/

    if (GetSecurity() == SEC_PLAYER)
    {
        uint32 raceMaskDisabled = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_DISABLED_RACEMASK);
        if ((1 << (race_ - 1)) & raceMaskDisabled)
        {
            data << uint8(CHAR_CREATE_DISABLED);
            SendPacket(&data);
            return;
        }

        uint32 classMaskDisabled = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_DISABLED_CLASSMASK);
        if ((1 << (class_ - 1)) & classMaskDisabled)
        {
            data << uint8(CHAR_CREATE_DISABLED);
            SendPacket(&data);
            return;
        }
    }

    // prevent character creating with invalid name
    if (!normalizePlayerName(name))
    {
        data << uint8(CHAR_NAME_NO_NAME);
        SendPacket(&data);
        TC_LOG_ERROR("network", "Account:[%d] but tried to Create character with empty [name] ", GetAccountId());
        return;
    }

    // check name limitations
    uint8 res = ObjectMgr::CheckPlayerName(name, true);
    if (res != CHAR_NAME_SUCCESS)
    {
        data << uint8(res);
        SendPacket(&data);
        return;
    }

    if (GetSecurity() == SEC_PLAYER && sObjectMgr->IsReservedName(name))
    {
        data << uint8(CHAR_NAME_RESERVED);
        SendPacket(&data);
        return;
    }

    if (class_ == CLASS_DEATH_KNIGHT && GetSecurity() == SEC_PLAYER)
    {
        // speedup check for heroic class disabled case
        uint32 heroic_free_slots = sWorld->getIntConfig(CONFIG_HEROIC_CHARACTERS_PER_REALM);
        if (heroic_free_slots == 0)
        {
            data << uint8(CHAR_CREATE_UNIQUE_CLASS_LIMIT);
            SendPacket(&data);
            return;
        }

        // speedup check for heroic class disabled case
        uint32 req_level_for_heroic = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_MIN_LEVEL_FOR_HEROIC_CHARACTER);
        if (req_level_for_heroic > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        {
            data << uint8(CHAR_CREATE_LEVEL_REQUIREMENT);
            SendPacket(&data);
            return;
        }
    }

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHECK_NAME);
    stmt->setString(0, name);

    CharacterCreateInfo* createInfo = new CharacterCreateInfo(name, race_, class_, gender, skin, face, hairStyle, hairColor, facialHair, outfitId, recvData);
    _queryProcessor.AddCallback(CharacterDatabase.AsyncQuery(stmt)
        .WithChainingPreparedCallback([this, createInfo](QueryCallback& queryCallback, PreparedQueryResult result)
    {
        
        if (result)
        {
            WorldPacket data(SMSG_CHAR_CREATE, 1);
            data << uint8(CHAR_CREATE_NAME_IN_USE);
            SendPacket(&data);
            delete createInfo;
            return;
        }


        LoginDatabasePreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_SUM_REALM_CHARACTERS);
        stmt->setUInt32(0, GetAccountId());
        queryCallback.SetNextQuery(LoginDatabase.AsyncQuery(stmt));
 
    })
        .WithChainingPreparedCallback([this, createInfo](QueryCallback& queryCallback, PreparedQueryResult result)
    {

        uint16 acctCharCount = 0;
        if (result)
        {
            Field* fields = result->Fetch();
            // SELECT SUM(x) is MYSQL_TYPE_NEWDECIMAL - needs to be read as string
            const char* ch = fields[0].GetCString();
            if (ch)
                acctCharCount = atoi(ch);
        }

        if (acctCharCount >= sWorld->getIntConfig(CONFIG_CHARACTERS_PER_ACCOUNT))
        {
            WorldPacket data(SMSG_CHAR_CREATE, 1);
            data << uint8(CHAR_CREATE_ACCOUNT_LIMIT);
            SendPacket(&data);
            delete createInfo;
            return;
        }

        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_SUM_CHARS);
        stmt->setUInt32(0, GetAccountId());
        queryCallback.SetNextQuery(CharacterDatabase.AsyncQuery(stmt));

    })
        .WithChainingPreparedCallback([this, createInfo](QueryCallback& queryCallback, PreparedQueryResult result)
    {

        if (result)
        {
            Field* fields = result->Fetch();
            createInfo->CharCount = uint8(fields[0].GetUInt64()); // SQL's COUNT() returns uint64 but it will always be less than uint8.Max

            if (createInfo->CharCount >= sWorld->getIntConfig(CONFIG_CHARACTERS_PER_REALM))
            {
                WorldPacket data(SMSG_CHAR_CREATE, 1);
                data << uint8(CHAR_CREATE_SERVER_LIMIT);
                SendPacket(&data);
                delete createInfo;
                return;
            }
        }

        bool allowTwoSideAccounts = !sWorld->IsPvPRealm() || sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_ACCOUNTS) || GetSecurity() > SEC_PLAYER;
        uint32 skipCinematics = sWorld->getIntConfig(CONFIG_SKIP_CINEMATICS);


        std::function<void(PreparedQueryResult)> finalizeCharacterCreation = [this, createInfo](PreparedQueryResult result)
        {

            bool haveSameRace = false;
            uint32 heroicReqLevel = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_MIN_LEVEL_FOR_HEROIC_CHARACTER);
            bool hasHeroicReqLevel = (heroicReqLevel == 0);
            bool allowTwoSideAccounts = !sWorld->IsPvPRealm() || sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_ACCOUNTS) || GetSecurity() > SEC_PLAYER;
            uint32 skipCinematics = sWorld->getIntConfig(CONFIG_SKIP_CINEMATICS);
            bool checkHeroicReqs = createInfo->Class == CLASS_DEATH_KNIGHT;

            if (result)
            {
                uint32 team = Player::TeamForRace(createInfo->Race);
                uint32 freeHeroicSlots = sWorld->getIntConfig(CONFIG_HEROIC_CHARACTERS_PER_REALM);

                Field* field = result->Fetch();
                uint8 accRace  = field[1].GetUInt8();

                if (checkHeroicReqs)
                {
                    uint8 accClass = field[2].GetUInt8();
                    if (accClass == CLASS_DEATH_KNIGHT)
                    {
                        if (freeHeroicSlots > 0)
                            --freeHeroicSlots;

                        if (freeHeroicSlots == 0)
                        {
                            WorldPacket data(SMSG_CHAR_CREATE, 1);
                            data << uint8(CHAR_CREATE_UNIQUE_CLASS_LIMIT);
                            SendPacket(&data);
                            delete createInfo;
                            return;
                        }
                    }

                    if (!hasHeroicReqLevel)
                    {
                        uint8 accLevel = field[0].GetUInt8();
                        if (accLevel >= heroicReqLevel)
                            hasHeroicReqLevel = true;
                    }
                }

                // need to check team only for first character
                /// @todo what to if account already has characters of both races?
                if (!allowTwoSideAccounts)
                {
                    uint32 accTeam = 0;
                    if (accRace > 0)
                        accTeam = Player::TeamForRace(accRace);

                    if (accTeam != team)
                    {
                        WorldPacket data(SMSG_CHAR_CREATE, 1);
                        data << uint8(CHAR_CREATE_PVP_TEAMS_VIOLATION);
                        SendPacket(&data);
                        delete createInfo;
                        return;
                    }
                }

                // search same race for cinematic or same class if need
                /// @todo check if cinematic already shown? (already logged in?; cinematic field)
                while ((skipCinematics == 1 && !haveSameRace) || createInfo->Class == CLASS_DEATH_KNIGHT)
                {
                    if (!result->NextRow())
                        break;

                    field = result->Fetch();
                    accRace = field[1].GetUInt8();

                    if (!haveSameRace)
                        haveSameRace = createInfo->Race == accRace;

                    if (checkHeroicReqs)
                    {
                        uint8 acc_class = field[2].GetUInt8();
                        if (acc_class == CLASS_DEATH_KNIGHT)
                        {
                            if (freeHeroicSlots > 0)
                                --freeHeroicSlots;

                            if (freeHeroicSlots == 0)
                            {
                                WorldPacket data(SMSG_CHAR_CREATE, 1);
                                data << uint8(CHAR_CREATE_UNIQUE_CLASS_LIMIT);
                                SendPacket(&data);
                                delete createInfo;
                                return;
                            }
                        }

                        if (!hasHeroicReqLevel)
                        {
                            uint8 acc_level = field[0].GetUInt8();
                            if (acc_level >= heroicReqLevel)
                                hasHeroicReqLevel = true;
                        }
                    }
                }
            }

            if (checkHeroicReqs && !hasHeroicReqLevel)
            {
                WorldPacket data(SMSG_CHAR_CREATE, 1);
                data << uint8(CHAR_CREATE_LEVEL_REQUIREMENT);
                SendPacket(&data);
                delete createInfo;
                return;
            }

            if (createInfo->Data.rpos() < createInfo->Data.wpos())
            {
                uint8 unk;
                createInfo->Data >> unk;
                TC_LOG_DEBUG("network", "Character creation %s (account %u) has unhandled tail data: [%u]", createInfo->Name.c_str(), GetAccountId(), unk);
            }

            Player newChar(this);
            newChar.GetMotionMaster()->Initialize();
            if (!newChar.Create(sObjectMgr->GenerateLowGuid(HIGHGUID_PLAYER), createInfo))
            {
                // Player not create (race/class/etc problem?)
                newChar.CleanupsBeforeDelete();

                WorldPacket data(SMSG_CHAR_CREATE, 1);
                data << uint8(CHAR_CREATE_ERROR);
                SendPacket(&data);
                delete createInfo;
                 return;
            }
            SetPlayer(&newChar);

            if ((haveSameRace && skipCinematics == 1) || skipCinematics == 2)
                newChar.setCinematic(1);                          // not show intro

            newChar.SetAtLoginFlag(AT_LOGIN_FIRST);               // First login

            // Player created, save it now
            newChar.SaveToDB(true);

            createInfo->CharCount += 1;

            LoginDatabaseTransaction trans = LoginDatabase.BeginTransaction();

            LoginDatabasePreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_REALM_CHARACTERS_BY_REALM);
            stmt->setUInt32(0, GetAccountId());
            stmt->setUInt32(1, realm.Id.Realm);
            trans->Append(stmt);

            stmt = LoginDatabase.GetPreparedStatement(LOGIN_INS_REALM_CHARACTERS);
            stmt->setUInt32(0, createInfo->CharCount);
            stmt->setUInt32(1, GetAccountId());
            stmt->setUInt32(2, realm.Id.Realm);
            trans->Append(stmt);

            LoginDatabase.CommitTransaction(trans);

            WorldPacket data(SMSG_CHAR_CREATE, 1);
            data << uint8(CHAR_CREATE_SUCCESS);
            SendPacket(&data);

            std::string IP_str = GetRemoteAddress();
            TC_LOG_INFO("entities.player.character", "Account: %d (IP: %s) Create Character:[%s] (GUID: %u)", GetAccountId(), IP_str.c_str(), createInfo->Name.c_str(), newChar.GetGUIDLow());
            sScriptMgr->OnPlayerCreate(&newChar);
            sWorld->AddCharacterNameData(newChar.GetGUIDLow(), newChar.GetName(), newChar.GetGender(), newChar.GetRace(), newChar.GetClass(), newChar.GetLevel());

            newChar.CleanupsBeforeDelete();
            delete createInfo;
            SetPlayer(nullptr);

        };

        if (allowTwoSideAccounts && !skipCinematics && createInfo->Class != CLASS_DEATH_KNIGHT)
        {
            finalizeCharacterCreation(PreparedQueryResult(nullptr));
            return;
        }

        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_CREATE_INFO);
        stmt->setUInt32(0, GetAccountId());
        stmt->setUInt32(1, (skipCinematics == 1 || createInfo->Class == CLASS_DEATH_KNIGHT) ? 10 : 1);
        queryCallback.WithPreparedCallback(std::move(finalizeCharacterCreation)).SetNextQuery(CharacterDatabase.AsyncQuery(stmt));

    }));


}


void WorldSession::HandleCharDeleteOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;

    guid[1] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[5]);

    TC_LOG_DEBUG("network", "Character (Guid: %u) deleted", GUID_LOPART(guid));

    // can't delete loaded character
    if (ObjectAccessor::FindPlayer(guid))
        return;

    uint32 accountId = 0;
    uint8 level = 0;
    std::string name;

    // is guild leader
    if (sGuildMgr->GetGuildByLeader(guid))
    {
        WorldPacket data(SMSG_CHAR_DELETE, 1);
        data << uint8(CHAR_DELETE_FAILED_GUILD_LEADER);
        SendPacket(&data);
        return;
    }

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_DATA_BY_GUID);
    stmt->setUInt32(0, GUID_LOPART(guid));

    if (PreparedQueryResult result = CharacterDatabase.Query(stmt))
    {
        Field* fields = result->Fetch();
        accountId = fields[0].GetUInt32();
        name = fields[1].GetString();
        level = fields[2].GetUInt8();
    }

    // prevent deleting other players' characters using cheating tools
    if (accountId != GetAccountId())
        return;

    std::string hwid;
    if (QueryResult result = LoginDatabase.PQuery("SELECT project_hwid FROM account WHERE id = '%u'", GetAccountId()))
    {
        Field* fields = result->Fetch();
        hwid = fields[0].GetString();
    }

    std::string IP_str = GetRemoteAddress();
    TC_LOG_INFO("entities.player.character", "Account: %d, IP: %s deleted character: %s, GUID: %u, Level: %u HWID: %s", accountId, IP_str.c_str(), name.c_str(), GUID_LOPART(guid), level, hwid.c_str());
    sScriptMgr->OnPlayerDelete(guid);

    if (sLog->ShouldLog("entities.player.dump", LOG_LEVEL_INFO)) // optimize GetPlayerDump call
    {
        std::string dump;
        if (PlayerDumpWriter().GetDump(GUID_LOPART(guid), dump))
            sLog->outCharDump(dump.c_str(), accountId, GUID_LOPART(guid), name.c_str());
    }

    //sGuildFinderMgr->RemoveAllMembershipRequestsFromPlayer(guid);
    sCalendarMgr->RemoveAllPlayerEventsAndInvites(guid);
    Player::DeleteFromDB(guid, accountId);

    WorldPacket data(SMSG_CHAR_DELETE, 1);
    data << uint8(CHAR_DELETE_SUCCESS);
    SendPacket(&data);
}

void WorldSession::HandlePlayerLoginOpcode(WorldPacket& recvData)
{
    if (PlayerLoading() || GetPlayer() != NULL)
    {
        TC_LOG_ERROR("network", "Player tries to login again, AccountId = %d", GetAccountId());
        return;
    }

    m_playerLoading = true;
    ObjectGuid playerGuid;
    float unk = 0;

    TC_LOG_DEBUG("network", "WORLD: Recvd Player Logon Message");

    recvData >> unk;

    playerGuid[1] = recvData.ReadBit();
    playerGuid[4] = recvData.ReadBit();
    playerGuid[7] = recvData.ReadBit();
    playerGuid[3] = recvData.ReadBit();
    playerGuid[2] = recvData.ReadBit();
    playerGuid[6] = recvData.ReadBit();
    playerGuid[5] = recvData.ReadBit();
    playerGuid[0] = recvData.ReadBit();

    recvData.ReadByteSeq(playerGuid[5]);
    recvData.ReadByteSeq(playerGuid[1]);
    recvData.ReadByteSeq(playerGuid[0]);
    recvData.ReadByteSeq(playerGuid[6]);
    recvData.ReadByteSeq(playerGuid[2]);
    recvData.ReadByteSeq(playerGuid[4]);
    recvData.ReadByteSeq(playerGuid[7]);
    recvData.ReadByteSeq(playerGuid[3]);

    //WorldObject* player = ObjectAccessor::GetWorldObject(*GetPlayer(), playerGuid);
    TC_LOG_DEBUG("network", "Character (Guid: %u) logging in", GUID_LOPART(playerGuid));

    if (!IsLegitCharacterForAccount(GUID_LOPART(playerGuid)))
    {
        TC_LOG_ERROR("network", "Account (%u) can't login with that character (%u).", GetAccountId(), GUID_LOPART(playerGuid));
        KickPlayer();
        return;
    }

    std::shared_ptr<LoginQueryHolder> holder = std::make_shared<LoginQueryHolder>(GetAccountId(), playerGuid);
    if (!holder->Initialize())
    {
        m_playerLoading = false;
        return;
    }

    AddQueryHolderCallback(CharacterDatabase.DelayQueryHolder(holder)).AfterComplete([this](SQLQueryHolderBase const& holder)
    {
        HandlePlayerLogin(static_cast<LoginQueryHolder const&>(holder));
    });    
}

void WorldSession::HandleLoadScreenOpcode(WorldPacket& recvPacket)
{
    TC_LOG_INFO("general", "WORLD: Recvd CMSG_LOAD_SCREEN");
    uint32 mapID = recvPacket.read<uint32>();
    bool loading = recvPacket.ReadBit();

    if (!loading)
        sWorld->SendRaidQueueInfo(GetPlayer());
}

void WorldSession::HandlePlayerLogin(LoginQueryHolder const& holder)
{
    uint64 playerGuid = holder.GetGuid();

    Player* pCurrChar = new Player(this);
    // for send server info and strings (config)
    ChatHandler chH = ChatHandler(pCurrChar->GetSession());

    // "GetAccountId() == db stored account id" checked in LoadFromDB (prevent login not own character using cheating tools)
    if (!pCurrChar->LoadFromDB(GUID_LOPART(playerGuid), holder))
    {
        SetPlayer(NULL);
        KickPlayer();                                       // disconnect client, player no set to session and it will not deleted or saved at kick
        delete pCurrChar;                                   // delete it manually
        m_playerLoading = false;
        return;
    }

    pCurrChar->GetMotionMaster()->Initialize();

    WorldPacket data(SMSG_LOGIN_VERIFY_WORLD, 4 + 4 + 4 + 4 + 4);
    data << pCurrChar->GetPositionX();
    data << pCurrChar->GetOrientation();
    data << pCurrChar->GetPositionY();
    data << pCurrChar->GetMapId();
    data << pCurrChar->GetPositionZ();
    SendPacket(&data);

    // load player specific part before send times
    LoadAccountData(holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_ACCOUNT_DATA), PER_CHARACTER_CACHE_MASK);
    SendAccountDataTimes(PER_CHARACTER_CACHE_MASK);

    bool feedbackSystem = sWorld->getBoolConfig(CONFIG_TICKETS_FEEDBACK_SYSTEM_ENABLED);
    bool excessiveWarning = false;

    data.Initialize(SMSG_FEATURE_SYSTEM_STATUS, 4 + 4 + 4 + 1 + 4 + 2 + 4 + 4 + 4 + 4 + 4 + 4 + 4);
    data << uint32(0);                  // Scroll of Resurrection per day?
    data << uint32(0);                  // Scroll of Resurrection current
    data << uint32(0);
    data << uint8(2);
    data << uint32(0);

    data.WriteBit(0);
    data.WriteBit(sBattlePayMgr->IsStoreEnabled()); // ingame shop status (0 - "The Shop is temporarily unavailable.")
    data.WriteBit(0);
    data.WriteBit(0);                   // Recruit a Friend button
    data.WriteBit(0);                   // server supports voice chat
    data.WriteBit(true);                // show ingame shop icon
    data.WriteBit(0);                   // Scroll of Resurrection button
    data.WriteBit(excessiveWarning);    // excessive play time warning
    data.WriteBit(0);                   // ingame shop parental control (1 - "Feature has been disabled by Parental Controls.")
    data.WriteBit(feedbackSystem);      // feedback system (bug, suggestion and report systems)
    data.FlushBits();

    if (excessiveWarning)
    {
        data << uint32(0);              // excessive play time warning after period(in seconds)
        data << uint32(0);
        data << uint32(0);
    }

    if (feedbackSystem)
    {
        data << uint32(0);
        data << uint32(1);
        data << uint32(10);
        data << uint32(60000);
    }

    SendPacket(&data);

    // Send MOTD
    {
        data.Initialize(SMSG_MOTD, 50);                     // new in 2.0.1
        data.WriteBits(0, 4);

        uint32 linecount=0;
        std::string str_motd = sWorld->GetMotd();
        std::string::size_type pos, nextpos;
        ByteBuffer stringBuffer;

        pos = 0;
        while ((nextpos= str_motd.find('@', pos)) != std::string::npos)
        {
            if (nextpos != pos)
            {
                std::string string = str_motd.substr(pos, nextpos-pos);
                data.WriteBits(strlen(string.c_str()), 7);
                stringBuffer.WriteString(string);
                ++linecount;
            }
            pos = nextpos + 1;
        }

        if (pos<str_motd.length())
        {
            std::string string = str_motd.substr(pos);
            data.WriteBits(strlen(string.c_str()), 7);
            stringBuffer.WriteString(string);
            ++linecount;
        }


        data.PutBits(0, linecount, 4);
        data.FlushBits();
        data.append(stringBuffer);

        SendPacket(&data);
        TC_LOG_DEBUG("network", "WORLD: Sent motd (SMSG_MOTD)");

        // send server info
        if (sWorld->getIntConfig(CONFIG_ENABLE_SINFO_LOGIN) == 1)
            chH.PSendSysMessage(_FULLVERSION);

        TC_LOG_DEBUG("network", "WORLD: Sent server info");
    }

    data.Initialize(SMSG_PVP_SEASON, 4 + 4);
    data << uint32(sWorld->getIntConfig(CONFIG_ARENA_SEASON_ID) - 1); // Old season
    data << uint32(sWorld->getIntConfig(CONFIG_ARENA_SEASON_ID));     // Current season
    SendPacket(&data);

    SendTimezoneInformation();

    HotfixData const& hotfix = sObjectMgr->GetHotfixData();

    data.Initialize(SMSG_HOTFIX_INFO);
    data.WriteBits(hotfix.size(), 20);
    data.FlushBits();

    for (uint32 i = 0; i < hotfix.size(); ++i)
    {
        data << uint32(hotfix[i].Timestamp);
        data << uint32(hotfix[i].Entry);
        data << uint32(hotfix[i].Type);
    }

    SendPacket(&data);

    pCurrChar->SendInitialPacketsBeforeAddToMap();

    //Show cinematic at the first time that player login
    if (!pCurrChar->getCinematic())
    {
        pCurrChar->setCinematic(1);

        if (ChrClassesEntry const* cEntry = sChrClassesStore.LookupEntry(pCurrChar->GetClass()))
        {
            if (cEntry->CinematicSequence)
                pCurrChar->SendCinematicStart(cEntry->CinematicSequence);
            else if (ChrRacesEntry const* rEntry = sChrRacesStore.LookupEntry(pCurrChar->GetRace()))
                pCurrChar->SendCinematicStart(rEntry->CinematicSequence);

            // send new char string if not empty
            if (!sWorld->GetNewCharString().empty())
                chH.PSendSysMessage("%s", sWorld->GetNewCharString().c_str());
        }
    }

    if (!pCurrChar->GetMap()->AddPlayerToMap(pCurrChar) || !pCurrChar->CheckInstanceLoginValid())
    {
        AreaTriggerStruct const* at = sObjectMgr->GetGoBackTrigger(pCurrChar->GetMapId());
        if (at)
            pCurrChar->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, pCurrChar->GetOrientation());
        else
            pCurrChar->TeleportTo(pCurrChar->m_homebindMapId, pCurrChar->m_homebindX, pCurrChar->m_homebindY, pCurrChar->m_homebindZ, pCurrChar->GetOrientation());
    }

    sObjectAccessor->AddObject(pCurrChar);
    //TC_LOG_DEBUG("Player %s added to Map.", pCurrChar->GetName().c_str());

    if (pCurrChar->GetGuildId() != 0)
    {
        Guild* guild = sGuildMgr->GetGuildById(pCurrChar->GetGuildId());
        ASSERT(guild);
        guild->SendLoginInfo(this);
    }

    pCurrChar->SendInitialPacketsAfterAddToMap();

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_ONLINE);
    stmt->setUInt32(0, pCurrChar->GetGUIDLow());
    CharacterDatabase.Execute(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_LAST_LOGIN);
    stmt->setUInt32(0, pCurrChar->GetGUIDLow());
    CharacterDatabase.Execute(stmt);

    LoginDatabasePreparedStatement *lstmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_ACCOUNT_ONLINE);
    lstmt->setUInt32(0, GetAccountId());
    LoginDatabase.Execute(lstmt);

    pCurrChar->SetInGameTime(getMSTime());

    if (Group* group = pCurrChar->GetOriginalGroup())
    {
        group->SendUpdate();
        group->ResetMaxEnchantingLevel();
    }

    // announce group about member online (must be after add to player list to receive announce to self)
    if (Group* group = pCurrChar->GetGroup())
    {
        //pCurrChar->groupInfo.group->SendInit(this); // useless
        group->SendUpdate();
        group->ResetMaxEnchantingLevel();
    }

    // friend status
    sSocialMgr->SendFriendStatus(pCurrChar, FRIEND_ONLINE, pCurrChar->GetGUIDLow(), true);

    // Place character in world (and load zone) before some object loading
    pCurrChar->LoadCorpse();

    // setting Ghost+speed if dead
    if (pCurrChar->m_deathState != ALIVE)
    {
        // not blizz like, we must correctly save and load player instead...
        if (pCurrChar->GetRace() == RACE_NIGHTELF)
            pCurrChar->CastSpell(pCurrChar, 20584, true, 0);// auras SPELL_AURA_INCREASE_SPEED(+speed in wisp form), SPELL_AURA_INCREASE_SWIM_SPEED(+swim speed in wisp form), SPELL_AURA_TRANSFORM (to wisp form)
        pCurrChar->CastSpell(pCurrChar, 8326, true, 0);     // auras SPELL_AURA_GHOST, SPELL_AURA_INCREASE_SPEED(why?), SPELL_AURA_INCREASE_SWIM_SPEED(why?)

        pCurrChar->SetWaterWalking(true);
    }

    pCurrChar->ContinueTaxiFlight();

    // reset for all pets before pet loading
    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS))
        Pet::resetTalentsForAllPetsOf(pCurrChar);

    // Load pet if any (if player not alive and in taxi flight or another then pet will remember as temporary unsummoned)
    pCurrChar->LoadPet();

    // Set FFA PvP for non GM in non-rest mode
    if (sWorld->IsFFAPvPRealm() && !pCurrChar->IsGameMaster() && !pCurrChar->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_RESTING))
        pCurrChar->SetByteFlag(UNIT_FIELD_SHAPESHIFT_FORM, 1, UNIT_BYTE2_FLAG_FFA_PVP);

    if (pCurrChar->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_CONTESTED_PVP))
        pCurrChar->SetContestedPvP();

    // Apply at_login requests
    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_RESET_SPELLS))
    {
        pCurrChar->ResetSpells();
        SendNotification(LANG_RESET_SPELLS);
    }

    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_RESET_TALENTS))
    {
        pCurrChar->ResetTalents(true);
        pCurrChar->SendTalentsInfoData();              // original talents send already in to SendInitialPacketsBeforeAddToMap, resend reset state
        SendNotification(LANG_RESET_TALENTS);
    }
#ifdef ELUNA
    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_FIRST))
        sHookMgr->OnFirstLogin(pCurrChar);
#endif

    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_FIRST))
    {
        pCurrChar->RemoveAtLoginFlag(AT_LOGIN_FIRST);

        if (pCurrChar->GetClass() == CLASS_HUNTER)
        {
            static uint32 const HunterCreatePetSpells[MAX_RACES] =
            {
                0,      /* None */                          79597,  /* Human - Young Wolf */
                79598,  /* Orc - Young Boar */              79593,  /* Dwarf - Young Bear */
                79602,  /* Night Elf - Young Cat */         79600,  /* Undead - Young Widow */
                79603,  /* Tauren - Young Tallstrider */    0,      /* Gnome */
                79599,  /* Troll - Young Raptor */          79595,  /* Goblin - Young Crab */
                79594,  /* Blood Elf - Young Dragonhawk */  79601,  /* Draenei - Young Moth */
                0,      /* Fel Orc */                       0,      /* Naga */
                0,      /* Broken */                        0,      /* Skeleton */
                0,      /* Vrykul */                        0,      /* Tuskarr */
                0,      /* Forest Troll */                  0,      /* Taunka */
                0,      /* Northrend Skeleton */            0,      /* Ice Troll */
                79596,  /* Worgen - Young Mastiff */        0,      /* Gilnean */
                107924, /* Pandaren - Wise Turtle */        0,      /* Pandaren Alliance */
                0       /* Pandaren Horde*/
            };

            pCurrChar->CastSpell(pCurrChar, HunterCreatePetSpells[pCurrChar->GetRace()], true);
        }

        if (pCurrChar->GetRace() == RACE_UNDEAD_PLAYER && pCurrChar->GetClass() != CLASS_DEATH_KNIGHT)
            pCurrChar->CastSpell(pCurrChar, 73523, true); // Undead - Rigor Mortis

        if (pCurrChar->GetRace() == RACE_PANDAREN_NEUTRAL)
        {
            static uint32 const PandarenStartingQuestSpells[MAX_CLASSES] =
            {
                0,      /* None */         107922, /* Warrior */
                0,      /* Paladin */      107917, /* Hunter */
                107920, /* Rogue */        107919, /* Priest */
                0,      /* Death Knight */ 107921, /* Shaman */
                107916, /* Mage */         0,      /* Warlock */
                107915, /* Monk */         0       /* Druid */
            };

            pCurrChar->CastSpell(pCurrChar, 100750, true); // Launch Starting Quest
            pCurrChar->CastSpell(pCurrChar, PandarenStartingQuestSpells[pCurrChar->GetClass()], true);

            static uint32 const PandarenRemoveWeaponSpells[MAX_CLASSES] =
            {
                0,      /* None */         108059, /* Warrior */
                0,      /* Paladin */      108061, /* Hunter */
                108058, /* Rogue */        108057, /* Priest */
                0,      /* Death Knight */ 108056, /* Shaman */
                108055, /* Mage */         0,      /* Warlock */
                108060, /* Monk */         0       /* Druid */
            };

            pCurrChar->CastSpell(pCurrChar, PandarenRemoveWeaponSpells[pCurrChar->GetClass()], true);
        }
    }

    if (auto servicesResult = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_SERVICES))
    {
        do
        {
            Field* fields = servicesResult->Fetch();
            ServiceEntry s{ projectService(fields[1].GetUInt32()) };
            s.ID = fields[0].GetUInt32();
            s.Data1 = fields[2].GetUInt32();
            s.Data2 = fields[3].GetUInt32();
            s.Data3 = fields[4].GetUInt32();
            s.Data4 = fields[5].GetString();
            sServiceMgr->ExecuteService(pCurrChar, s);
        } while (servicesResult->NextRow());
    }

    // show time before shutdown if shutdown planned.
    if (sWorld->IsShuttingDown())
        sWorld->ShutdownMsg(true, pCurrChar);

    if (sWorld->getBoolConfig(CONFIG_ALL_TAXI_PATHS))
        pCurrChar->SetTaxiCheater(true);

    if (pCurrChar->IsGameMaster())
        SendNotification(LANG_GM_ON);

    std::string hwid;
    if (QueryResult result = LoginDatabase.PQuery("SELECT project_hwid FROM account WHERE id = '%u'", GetAccountId()))
    {
        Field* fields = result->Fetch();
        hwid = fields[0].GetString();
    }

    std::string IP_str = GetRemoteAddress();
    TC_LOG_INFO("entities.player.character", "Account: %d (IP: %s) Login Character:[%s] (GUID: %u) Level: %d HWID: %s",
        GetAccountId(), IP_str.c_str(), pCurrChar->GetName().c_str(), pCurrChar->GetGUIDLow(), pCurrChar->GetLevel(), hwid.c_str());

    if (!pCurrChar->IsStandState() && !pCurrChar->HasUnitState(UNIT_STATE_STUNNED))
        pCurrChar->SetStandState(UNIT_STAND_STATE_STAND);

    m_playerLoading = false;

    // Handle Login-Achievements (should be handled after loading)
    _player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_ON_LOGIN, 1);
    _player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL);

    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_LEARN_CLASS_SPELLS))
        pCurrChar->RemoveAtLoginFlag(AT_LOGIN_LEARN_CLASS_SPELLS, true);

    for (auto&& bonusRate : sWorld->GetBonusRates())
        if (bonusRate.second.IsActive())
            if (!bonusRate.second.GetActiveAnnouncement().empty())
                sWorld->SendServerMessage(SERVER_MSG_STRING, bonusRate.second.GetActiveAnnouncement().c_str(), pCurrChar);

    if (_player->IsPvP() && !_player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
        _player->StartPvPOffTimer();

    pCurrChar->UpdateValorOfTheAncients();
    pCurrChar->UpdatePromotionAuras();

    sScriptMgr->OnPlayerLogin(pCurrChar);

    if (pCurrChar->HasAtLoginFlag(AT_LOGIN_POST_AUTOTRANSFER))
    {
        pCurrChar->SendTransferMail();
        pCurrChar->RemoveAtLoginFlag(AT_LOGIN_POST_AUTOTRANSFER, true);
    }

}

void WorldSession::HandleSetFactionAtWar(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_SET_FACTION_ATWAR");

    uint8 FactionIndexID;

    recvData >> FactionIndexID;

    GetPlayer()->GetReputationMgr().SetAtWar(FactionIndexID);
}

void WorldSession::HandleSetFactionNotAtWar(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_SET_FACTION_NOTATWAR");

    uint8 FactionIndexID;

    recvData >> FactionIndexID;

    GetPlayer()->GetReputationMgr().SetNotAtWar(FactionIndexID);
}

//I think this function is never used :/ I dunno, but i guess this opcode not exists
void WorldSession::HandleSetFactionCheat(WorldPacket & /*recvData*/)
{
    TC_LOG_ERROR("network", "WORLD SESSION: HandleSetFactionCheat, not expected call, please report.");
    GetPlayer()->GetReputationMgr().SendStates();
}

void WorldSession::HandleTutorialFlag(WorldPacket& recvData)
{
    uint32 data;
    recvData >> data;

    uint8 index = uint8(data / 32);
    if (index >= MAX_ACCOUNT_TUTORIAL_VALUES)
        return;

    uint32 value = (data % 32);

    uint32 flag = GetTutorialInt(index);
    flag |= (1 << value);
    SetTutorialInt(index, flag);
}

void WorldSession::HandleTutorialClear(WorldPacket& /*recvData*/)
{
    for (uint8 i = 0; i < MAX_ACCOUNT_TUTORIAL_VALUES; ++i)
        SetTutorialInt(i, 0xFFFFFFFF);
}

void WorldSession::HandleTutorialReset(WorldPacket& /*recvData*/)
{
    for (uint8 i = 0; i < MAX_ACCOUNT_TUTORIAL_VALUES; ++i)
        SetTutorialInt(i, 0x00000000);
}

void WorldSession::HandleSetWatchedFactionOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_SET_WATCHED_FACTION");
    uint32 fact;
    recvData >> fact;
    GetPlayer()->SetUInt32Value(PLAYER_FIELD_WATCHED_FACTION_INDEX, fact);
}

void WorldSession::HandleSetFactionInactiveOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_SET_FACTION_INACTIVE");
    uint32 FactionIndex;
    uint8 Status;
    recvData >> FactionIndex >> Status;

    _player->GetReputationMgr().SetInactive(FactionIndex, Status);
}

void WorldSession::HandleRequestForcedReactionsOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_REQUEST_FORCED_REACTIONS");

    _player->GetReputationMgr().SendForceReactions();
}

void WorldSession::HandleShowingHelmOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "CMSG_SHOWING_HELM for %s", _player->GetName().c_str());
    recvData.read_skip<uint8>(); // unknown, bool?
    _player->ToggleFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM);
}

void WorldSession::HandleShowingCloakOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "CMSG_SHOWING_CLOAK for %s", _player->GetName().c_str());
    recvData.read_skip<uint8>(); // unknown, bool?
    _player->ToggleFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_HIDE_CLOAK);
}

void WorldSession::SendRenameResult(uint8 result, ObjectGuid guid, std::string name)
{
    uint32 nameSize = name.size();
    bool hasGuid = guid != 0;

    WorldPacket data(SMSG_CHAR_RENAME);

    data << uint8(result);
    data.WriteBit(nameSize == 0);
    if (nameSize)
        data.WriteBits(nameSize, 6);
    data.WriteBit(hasGuid);
    if (hasGuid)
        data.WriteGuidMask(guid, 6, 3, 4, 2, 0, 1, 7, 5);

    data.FlushBits();

    if (hasGuid)
        data.WriteGuidBytes(guid, 5, 0, 4, 2, 1, 3, 6, 7);
    if (nameSize)
        data.WriteString(name);

    SendPacket(&data);
}

void WorldSession::HandleCharRenameOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;

    guid[6] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    uint32 nameLen = recvData.ReadBits(6);            // Name size
    guid[1] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[5]);
    std::string newName = recvData.ReadString(nameLen);  // New Name
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[0]);

    // prevent character rename to invalid name
    if (!normalizePlayerName(newName))
    {
        SendRenameResult(CHAR_NAME_NO_NAME);
        return;
    }

    uint8 result = ObjectMgr::CheckPlayerName(newName, true);
    if (result != CHAR_NAME_SUCCESS)
    {
        SendRenameResult(result, guid, newName);
        return;
    }

    // check name limitations
    if (GetSecurity() == SEC_PLAYER && sObjectMgr->IsReservedName(newName))
    {
        SendRenameResult(CHAR_NAME_RESERVED);
        return;
    }

    CharacterDatabase.EscapeString(newName);

    // Ensure that the character belongs to the current account, that rename at login is enabled
    // and that there is no character with the desired new name
    //_charRenameCallback.SetParam(newName);

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_FREE_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    stmt->setUInt32(1, GetAccountId());
    stmt->setUInt16(2, AT_LOGIN_RENAME);
    stmt->setUInt16(3, AT_LOGIN_RENAME);
    stmt->setString(4, newName);
    //_charRenameCallback.SetFutureResult(CharacterDatabase.AsyncQuery(stmt));

    _queryProcessor.AddCallback(CharacterDatabase.AsyncQuery(stmt)
        .WithPreparedCallback(std::bind(&WorldSession::HandleChangePlayerNameOpcodeCallBack, this, std::placeholders::_1, newName )));

}

void WorldSession::HandleChangePlayerNameOpcodeCallBack(PreparedQueryResult result, std::string const& newName)
{
    if (!result)
    {
        SendRenameResult(CHAR_CREATE_ERROR);
        return;
    }

    Field* fields = result->Fetch();

    uint32 guidLow      = fields[0].GetUInt32();
    std::string oldName = fields[1].GetString();

    uint64 guid = MAKE_NEW_GUID(guidLow, 0, HIGHGUID_PLAYER);

    AtLoginFlags usedAtLoginFlags = AT_LOGIN_RENAME;

    CharacterDatabase.EscapeString(oldName);

    // Update name and at_login flag in the db
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_NAME);
    stmt->setString(0, newName);
    stmt->setUInt16(1, usedAtLoginFlags);
    stmt->setUInt32(2, GUID_LOPART(guid));
    CharacterDatabase.Execute(stmt);

    // Removed declined name from db
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_DECLINED_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    CharacterDatabase.Execute(stmt);

    TC_LOG_INFO("entities.player.character", "Account: %d (IP: %s) Character:[%s] (guid:%u) Changed name to: %s", GetAccountId(), GetRemoteAddress().c_str(), oldName.c_str(), guidLow, newName.c_str());

    sWorld->UpdateCharacterNameData(GUID_LOPART(guid), newName);

    SendRenameResult(RESPONSE_SUCCESS, guid, newName);

    sServiceMgr->ExecutedServices(guidLow, SERVICE_TYPE_RENAME, Format("Old Name: %s", oldName.c_str()), Format("New Name: %s", newName.c_str()));
}

void WorldSession::HandleSetPlayerDeclinedNames(WorldPacket& recvData)
{
    ObjectGuid guid;
    DeclinedName declinedname;
    uint32 nameLength[MAX_DECLINED_NAME_CASES];

    guid[0] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();

    for (uint32 i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
        nameLength[i] = recvData.ReadBits(7);

    for (uint32 i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
        declinedname.name[i] = recvData.ReadString(nameLength[i]);

    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[5]);

    // not accept declined names for unsupported languages
    std::string name;
    if (!sObjectMgr->GetPlayerNameByGUID(guid, name))
    {
        WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
        data.WriteBit(true);
        data.WriteBits(0, 8);
        data.FlushBits();
        data << uint32(1);
        SendPacket(&data);
        return;
    }

    std::wstring wname;
    if (!Utf8toWStr(name, wname))
    {
        WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
        data.WriteBit(true);
        data.WriteBits(0, 8);
        data.FlushBits();
        data << uint32(1);
        SendPacket(&data);
        return;
    }

    if (!isCyrillicCharacter(wname[0]))                      // name already stored as only single alphabet using
    {
        WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
        data.WriteBit(true);
        data.WriteBits(0, 8);
        data.FlushBits();
        data << uint32(1);
        SendPacket(&data);
        return;
    }

    for (int i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
    {
        if (!normalizePlayerName(declinedname.name[i]))
        {
            WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
            data.WriteBit(true);
            data.WriteBits(0, 8);
            data.FlushBits();
            data << uint32(1);
            SendPacket(&data);
            return;
        }
    }

    if (!ObjectMgr::CheckDeclinedNames(name, declinedname))
    {
        WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
        data.WriteBit(true);
        data.WriteBits(0, 8);
        data.FlushBits();
        data << uint32(1);
        SendPacket(&data);
        return;
    }

    for (int i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
        CharacterDatabase.EscapeString(declinedname.name[i]);

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_DECLINED_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_DECLINED_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));

    for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
        stmt->setString(i+1, declinedname.name[i]);

    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);

    WorldPacket data(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, 4 + 8);
    data.WriteBit(false);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[7]);
    data.FlushBits();
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[5]);
    data << uint32(0);                                      // OK
    SendPacket(&data);

    DeclinedName const* declinedName = new DeclinedName(declinedname);
    sWorld->UpdateCharacterNameData(guid, name, GENDER_NONE, RACE_NONE, declinedName);
}


void WorldSession::HandleAlterAppearance(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "CMSG_ALTER_APPEARANCE");

    uint32 Hair, Color, FacialHair, SkinColor;
    recvData >> SkinColor >> Color >> Hair >> FacialHair;

    BarberShopStyleEntry const* bs_hair = sBarberShopStyleStore.LookupEntry(Hair);

    if (!bs_hair || bs_hair->type != 0 || bs_hair->race != _player->GetRace() || bs_hair->gender != _player->GetGender())
        return;

    BarberShopStyleEntry const* bs_facialHair = sBarberShopStyleStore.LookupEntry(FacialHair);

    if (!bs_facialHair || bs_facialHair->type != 2 || bs_facialHair->race != _player->GetRace() || bs_facialHair->gender != _player->GetGender())
        return;

    BarberShopStyleEntry const* bs_skinColor = sBarberShopStyleStore.LookupEntry(SkinColor);

    if (bs_skinColor && (bs_skinColor->type != 3 || bs_skinColor->race != _player->GetRace() || bs_skinColor->gender != _player->GetGender()))
        return;

    GameObject* go = _player->FindNearestGameObjectOfType(GAMEOBJECT_TYPE_BARBER_CHAIR, 5.0f);
    if (!go)
    {
        SendBarberShopResult(BARBER_SHOP_NOT_SITTING);
        return;
    }

    if (_player->getStandState() != UNIT_STAND_STATE_SIT_LOW_CHAIR + go->GetGOInfo()->barberChair.chairheight)
    {
        SendBarberShopResult(BARBER_SHOP_NOT_SITTING);
        return;
    }

    uint32 cost = _player->GetBarberShopCost(bs_hair->hair_id, Color, bs_facialHair->hair_id, bs_skinColor);
    if (!_player->HasEnoughMoney((uint64)cost))
    {
        SendBarberShopResult(BARBER_SHOP_NOT_ENOUGH_MONEY);
        return;
    }

    SendBarberShopResult(BARBER_SHOP_SUCCESS);

    _player->ModifyMoney(-int64(cost));                     // it isn't free
    _player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER, cost);

    _player->SetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 2, uint8(bs_hair->hair_id));
    _player->SetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 3, uint8(Color));
    _player->SetByteValue(PLAYER_FIELD_REST_STATE, 0, uint8(bs_facialHair->hair_id));
    if (bs_skinColor)
        _player->SetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 0, uint8(bs_skinColor->hair_id));

    _player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP, 1);

    _player->SetStandState(0);                              // stand up
}

void WorldSession::SendBarberShopResult(BarberShopResult result)
{
    WorldPacket data(SMSG_BARBER_SHOP_RESULT, 4);
    data << uint32(result);
    SendPacket(&data);
}

void WorldSession::HandleRemoveGlyph(WorldPacket& recvData)
{
    uint32 slot;
    recvData >> slot;

    if (slot >= MAX_GLYPH_SLOT_INDEX)
    {
        TC_LOG_DEBUG("network", "Client sent wrong glyph slot number in opcode CMSG_REMOVE_GLYPH %u", slot);
        return;
    }

    if (uint32 glyph = _player->GetGlyph(_player->GetActiveSpec(), slot))
    {
        if (GlyphPropertiesEntry const* gp = sGlyphPropertiesStore.LookupEntry(glyph))
        {
            _player->SetGlyph(slot, 0);
            _player->SendTalentsInfoData();
        }
    }
}

void WorldSession::HandleCharCustomize(WorldPacket& recvData)
{
    ObjectGuid guid;
    uint8 gender, skin, face, hairStyle, hairColor, facialHair;

    recvData >> hairStyle >> gender >> skin >> facialHair >> face >> hairColor;
    recvData.ReadGuidMask(guid, 2, 6, 1, 0, 7, 5);
    uint32 namelen = recvData.ReadBits(6);               // Name size
    recvData.ReadGuidMask(guid, 4, 3);
    recvData.ReadGuidBytes(guid, 4);
    std::string newName = recvData.ReadString(namelen);  // New Name
    recvData.ReadGuidBytes(guid, 0, 2, 6, 5, 3, 1, 7);

    if (!IsLegitCharacterForAccount(GUID_LOPART(guid)))
    {
        TC_LOG_ERROR("network", "Account %u, IP: %s tried to customise character %u, but it does not belong to their account!",
            GetAccountId(), GetRemoteAddress().c_str(), GUID_LOPART(guid));
        recvData.rfinish();
        KickPlayer();
        return;
    }

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_AT_LOGIN);
    stmt->setUInt32(0, GUID_LOPART(guid));
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    Field* fields = result->Fetch();
    uint32 at_loginFlags = fields[0].GetUInt16();

    if (!(at_loginFlags & AT_LOGIN_CUSTOMIZE))
    {
        WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    // prevent character rename to invalid name
    if (!normalizePlayerName(newName))
    {
        WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
        data << uint8(CHAR_NAME_NO_NAME);
        SendPacket(&data);
        return;
    }

    uint8 res = ObjectMgr::CheckPlayerName(newName, true);
    if (res != CHAR_NAME_SUCCESS)
    {
        WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
        data << uint8(res);
        SendPacket(&data);
        return;
    }

    // check name limitations
    if (GetSecurity() == SEC_PLAYER && sObjectMgr->IsReservedName(newName))
    {
        WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
        data << uint8(CHAR_NAME_RESERVED);
        SendPacket(&data);
        return;
    }

    // character with this name already exist
    if (uint64 newguid = sObjectMgr->GetPlayerGUIDByName(newName))
    {
        if (newguid != guid)
        {
            WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1);
            data << uint8(CHAR_CREATE_NAME_IN_USE);
            SendPacket(&data);
            return;
        }
    }

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    result = CharacterDatabase.Query(stmt);

    AtLoginFlags usedAtLoginFlags = AT_LOGIN_CUSTOMIZE;
    std::string oldName;
    if (result)
    {
        oldName = result->Fetch()[0].GetString();
        TC_LOG_INFO("entities.player.character", "Account: %d (IP: %s), Character[%s] (guid:%u) Customized to: %s", GetAccountId(), GetRemoteAddress().c_str(), oldName.c_str(), GUID_LOPART(guid), newName.c_str());

        if (oldName != newName)
            usedAtLoginFlags = AtLoginFlags(usedAtLoginFlags | AT_LOGIN_RENAME);
    }

    CharacterDatabase.EscapeString(newName);
    CharacterDatabase.EscapeString(oldName);

    Player::Customize(guid, gender, skin, face, hairStyle, hairColor, facialHair);

    // Update name and at_login flag in the db
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_NAME);
    stmt->setString(0, newName);
    stmt->setUInt16(1, usedAtLoginFlags);
    stmt->setUInt32(2, GUID_LOPART(guid));
    CharacterDatabase.Execute(stmt);

    // Removed declined name from db
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_DECLINED_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    CharacterDatabase.Execute(stmt);

    sWorld->UpdateCharacterNameData(GUID_LOPART(guid), newName, gender, RACE_NONE);

    WorldPacket data(SMSG_CHAR_CUSTOMIZE, 1+8+(newName.size()+1)+6);

    data.WriteGuidMask(guid, 0, 7, 3, 2, 6, 5, 1, 5);
    data.WriteGuidBytes(guid, 1);
    data << uint8(RESPONSE_SUCCESS);
    data << uint8(facialHair);
    data << uint8(skin);
    data << uint8(gender);
    data << uint8(hairStyle);
    data << uint8(face);
    data << uint8(hairColor);
    data.WriteGuidBytes(guid, 7, 3, 5, 2, 6, 0, 4);
    data << newName;

    if (!RESPONSE_SUCCESS)
        data << newName;

    SendPacket(&data);

    sServiceMgr->ExecutedServices(guid, SERVICE_TYPE_CUSTOMIZE, Format("Old Name: %s", oldName.c_str()), Format("New Name: %s", newName.c_str()));
}

void WorldSession::HandleEquipmentSetSave(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "CMSG_EQUIPMENT_SET_SAVE");

    ObjectGuid setGuid;
    ObjectGuid itemGuid[EQUIPMENT_SLOT_END];
    uint32 index;
    EquipmentSet eqSet;
    uint8 iconNameLen, setNameLen;

    recvData >> index;

    if (index >= MAX_EQUIPMENT_SET_INDEX)                    // client set slots amount
        return;

    for (uint32 i = 0; i < EQUIPMENT_SLOT_END; ++i)
    {
        itemGuid[i][5] = recvData.ReadBit();
        itemGuid[i][0] = recvData.ReadBit();
        itemGuid[i][1] = recvData.ReadBit();
        itemGuid[i][4] = recvData.ReadBit();
        itemGuid[i][6] = recvData.ReadBit();
        itemGuid[i][3] = recvData.ReadBit();
        itemGuid[i][7] = recvData.ReadBit();
        itemGuid[i][2] = recvData.ReadBit();
    }

    setGuid[7] = recvData.ReadBit();
    setGuid[1] = recvData.ReadBit();
    setGuid[5] = recvData.ReadBit();
    setGuid[2] = recvData.ReadBit();
    setGuid[3] = recvData.ReadBit();
    setGuid[0] = recvData.ReadBit();

    setNameLen = recvData.ReadBits(8);
    setGuid[6] = recvData.ReadBit();
    iconNameLen = recvData.ReadBits(9);

    setGuid[4] = recvData.ReadBit();

    recvData.ReadByteSeq(setGuid[4]);
    recvData.ReadByteSeq(setGuid[0]);

    for (uint32 i = 0; i < EQUIPMENT_SLOT_END; ++i)
    {
        recvData.ReadByteSeq(itemGuid[i][1]);
        recvData.ReadByteSeq(itemGuid[i][0]);
        recvData.ReadByteSeq(itemGuid[i][7]);
        recvData.ReadByteSeq(itemGuid[i][3]);
        recvData.ReadByteSeq(itemGuid[i][6]);
        recvData.ReadByteSeq(itemGuid[i][2]);
        recvData.ReadByteSeq(itemGuid[i][4]);
        recvData.ReadByteSeq(itemGuid[i][5]);

        // equipment manager sends "1" (as raw GUID) for slots set to "ignore" (don't touch slot at equip set)
        if (itemGuid[i] == 1)
        {
            // ignored slots saved as bit mask because we have no free special values for Items[i]
            eqSet.IgnoreMask |= 1 << i;
            continue;
        }

        Item* item = _player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);

        if (!item && itemGuid[i])                               // cheating check 1
            return;

        if (item && item->GetGUID() != itemGuid[i])             // cheating check 2
            return;

        eqSet.Items[i] = GUID_LOPART(itemGuid[i]);
    }

    std::string iconName = recvData.ReadString(iconNameLen);

    recvData.ReadByteSeq(setGuid[7]);
    recvData.ReadByteSeq(setGuid[2]);

    std::string name = recvData.ReadString(setNameLen);

    recvData.ReadByteSeq(setGuid[6]);
    recvData.ReadByteSeq(setGuid[1]);
    recvData.ReadByteSeq(setGuid[5]);
    recvData.ReadByteSeq(setGuid[3]);

    eqSet.Guid = setGuid;
    eqSet.Name = name;
    eqSet.IconName = iconName;
    eqSet.state = EQUIPMENT_SET_NEW;

    _player->SetEquipmentSet(index, eqSet);
}

void WorldSession::HandleEquipmentSetDelete(WorldPacket &recvData)
{
    TC_LOG_DEBUG("network", "CMSG_EQUIPMENT_SET_DELETE");

    ObjectGuid setGuid;

    setGuid[4] = recvData.ReadBit();
    setGuid[2] = recvData.ReadBit();
    setGuid[6] = recvData.ReadBit();
    setGuid[0] = recvData.ReadBit();
    setGuid[5] = recvData.ReadBit();
    setGuid[1] = recvData.ReadBit();
    setGuid[7] = recvData.ReadBit();
    setGuid[3] = recvData.ReadBit();

    recvData.ReadByteSeq(setGuid[2]);
    recvData.ReadByteSeq(setGuid[0]);
    recvData.ReadByteSeq(setGuid[1]);
    recvData.ReadByteSeq(setGuid[6]);
    recvData.ReadByteSeq(setGuid[3]);
    recvData.ReadByteSeq(setGuid[4]);
    recvData.ReadByteSeq(setGuid[5]);
    recvData.ReadByteSeq(setGuid[7]);

    _player->DeleteEquipmentSet(setGuid);
}

void WorldSession::HandleEquipmentSetUse(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "CMSG_EQUIPMENT_SET_USE");

    uint8 srcbag[EQUIPMENT_SLOT_END];
    uint8 srcslot[EQUIPMENT_SLOT_END];

    ObjectGuid itemGuid[EQUIPMENT_SLOT_END];

    EquipmentSlots startSlot = _player->IsInCombat() ? EQUIPMENT_SLOT_MAINHAND : EQUIPMENT_SLOT_START;

    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
        recvData >> srcslot[i] >> srcbag[i];

    for (uint32 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
        recvData.ReadGuidMask(itemGuid[i], 3, 1, 7, 4, 5, 6, 0, 2);

    uint8 InvItemCounter = recvData.ReadBits(2);

    for (uint8 i = 0; i < InvItemCounter; i++)
    {
        recvData.ReadBit(); // Container Slot
        recvData.ReadBit(); // Slot
    }

    for (uint32 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        recvData.ReadGuidBytes(itemGuid[i], 4, 7, 0, 3, 2, 5, 1, 6);

        if (i < uint32(startSlot))
            continue;

        // check if item slot is set to "ignored" (raw value == 1), must not be unequipped then
        if (itemGuid[i] == 1)
            continue;

        Item* item = _player->GetItemByGuid(itemGuid[i]);

        uint16 dstpos = i | (INVENTORY_SLOT_BAG_0 << 8);

        if (!item)
        {
            Item* uItem = _player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
            if (!uItem)
                continue;

            ItemPosCountVec sDest;
            InventoryResult msg = _player->CanStoreItem(NULL_BAG, NULL_SLOT, sDest, uItem, false);
            if (msg == EQUIP_ERR_OK)
            {
                _player->RemoveItem(INVENTORY_SLOT_BAG_0, i, true);
                _player->StoreItem(sDest, uItem, true);
            }
            else
                _player->SendEquipError(msg, uItem, NULL);

            continue;
        }

        if (item->GetPos() == dstpos)
            continue;

        _player->SwapItem(item->GetPos(), dstpos);
    }

    for (uint8 i = 0; i < InvItemCounter; i++)
    {
        recvData.read_skip<uint8>();
        recvData.read_skip<uint8>();
    }

    uint8 Reason = 0;
    WorldPacket data(SMSG_USE_EQUIPMENT_SET_RESULT, 1);
    data << uint8(Reason);                                   // 4 - equipment swap failed - inventory is full
    SendPacket(&data);
}

void WorldSession::HandleCharFactionOrRaceChange(WorldPacket& recvData)
{
    ObjectGuid guid;
    uint8 gender, skin, face, hairStyle, hairColor, facialHair, race = 0;

    recvData >> gender;
    recvData >> race;
    guid[3] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    bool hasSkinColor = recvData.ReadBit();
    bool hasFace = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    uint32 nameLength = recvData.ReadBits(6);
    bool hasFacialHair = recvData.ReadBit();
    bool hasHairStyle = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    bool hasHairColor = recvData.ReadBit();
    bool isFactionChange = recvData.ReadBit();
    guid[7] = recvData.ReadBit();

    recvData.ReadGuidBytes(guid, 2, 1, 4, 5, 0);
    std::string newName = recvData.ReadString(nameLength);
    recvData.ReadGuidBytes(guid, 6, 3, 7);

    if (hasHairColor)
        recvData >> hairColor;
    if (hasHairStyle)
        recvData >> hairStyle;
    if (hasSkinColor)
        recvData >> skin;
    if (hasFace)
        recvData >> face;
    if (hasFacialHair)
        recvData >> facialHair;

    if (!IsLegitCharacterForAccount(GUID_LOPART(guid)))
    {
        TC_LOG_ERROR("network", "Account %u, IP: %s tried to factionchange character %u, but it does not belong to their account!",
            GetAccountId(), GetRemoteAddress().c_str(), GUID_LOPART(guid));
        KickPlayer();
        return;
    }

    uint32 lowGuid = GUID_LOPART(guid);

    // get the players old (at this moment current) race
    CharacterNameData const* nameData = sWorld->GetCharacterNameData(lowGuid);
    if (!nameData)
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    uint8 oldRace = nameData->m_race;
    uint8 playerClass = nameData->m_class;
    uint8 level = nameData->m_level;
    std::string oldName = nameData->m_name;

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_AT_LOGIN_TITLES);
    stmt->setUInt32(0, lowGuid);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    Field* fields = result->Fetch();
    uint32 at_loginFlags = fields[0].GetUInt16();
    char const* knownTitlesStr = fields[1].GetCString();
    AtLoginFlags usedAtLoginFlags = isFactionChange ? AT_LOGIN_CHANGE_FACTION : AT_LOGIN_CHANGE_RACE;

    TeamId oldTeam = TEAM_ALLIANCE;
    // Search each faction is targeted
    switch (oldRace)
    {
        case RACE_ORC:
        case RACE_TAUREN:
        case RACE_UNDEAD_PLAYER:
        case RACE_TROLL:
        case RACE_BLOODELF:
        case RACE_GOBLIN:
        case RACE_PANDAREN_HORDE:
            oldTeam = TEAM_HORDE;
            break;
        default:
            break;
    }

    TeamId team = TEAM_ALLIANCE;
    // Search each faction is targeted
    switch (race)
    {
        case RACE_ORC:
        case RACE_TAUREN:
        case RACE_UNDEAD_PLAYER:
        case RACE_TROLL:
        case RACE_BLOODELF:
        case RACE_GOBLIN:
        case RACE_PANDAREN_HORDE:
            team = TEAM_HORDE;
            break;
        default:
            break;
    }

    // We need to correct race when it's pandaren
    // Because client always send neutral ID
    if (race == RACE_PANDAREN_NEUTRAL)
    {
        if (at_loginFlags & AT_LOGIN_CHANGE_RACE)
            team = oldTeam;
        else
            team = oldTeam == TEAM_ALLIANCE ? TEAM_HORDE : TEAM_ALLIANCE;

        if (oldTeam == team)
            race = oldTeam == TEAM_ALLIANCE ? RACE_PANDAREN_ALLIANCE : RACE_PANDAREN_HORDE;
        else
            race = oldTeam == TEAM_ALLIANCE ? RACE_PANDAREN_HORDE : RACE_PANDAREN_ALLIANCE;
    }

    if (!sObjectMgr->GetPlayerInfo(race, playerClass))
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    if (!(at_loginFlags & usedAtLoginFlags))
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_CREATE_ERROR);
        SendPacket(&data);
        return;
    }

    if (GetSecurity() == SEC_PLAYER)
    {
        uint32 raceMaskDisabled = sWorld->getIntConfig(CONFIG_CHARACTER_CREATING_DISABLED_RACEMASK);
        if ((1 << (race - 1)) & raceMaskDisabled)
        {
            WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
            data << uint8(CHAR_CREATE_ERROR);
            SendPacket(&data);
            return;
        }
    }

    // prevent character rename to invalid name
    if (!normalizePlayerName(newName))
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_NAME_NO_NAME);
        SendPacket(&data);
        return;
    }

    uint8 res = ObjectMgr::CheckPlayerName(newName, true);
    if (res != CHAR_NAME_SUCCESS)
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(res);
        SendPacket(&data);
        return;
    }

    // check name limitations
    if (GetSecurity() == SEC_PLAYER && sObjectMgr->IsReservedName(newName))
    {
        WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
        data << uint8(CHAR_NAME_RESERVED);
        SendPacket(&data);
        return;
    }

    // character with this name already exist
    if (uint64 newguid = sObjectMgr->GetPlayerGUIDByName(newName))
    {
        if (newguid != guid)
        {
            WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1);
            data << uint8(CHAR_CREATE_NAME_IN_USE);
            SendPacket(&data);
            return;
        }
    }

    // resurrect the character in case he's dead
    sObjectAccessor->ConvertCorpseForPlayer(guid);

    if (oldName != newName)
        usedAtLoginFlags = AtLoginFlags(usedAtLoginFlags | AT_LOGIN_RENAME);

    CharacterDatabase.EscapeString(newName);
    CharacterDatabase.EscapeString(oldName);

    Player::Customize(guid, gender, skin, face, hairStyle, hairColor, facialHair);

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    // Update name, race and at_login flag in the db
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_FACTION_OR_RACE);
    stmt->setString(0, newName);
    stmt->setUInt8(1, race);
    stmt->setUInt16(2, usedAtLoginFlags);
    stmt->setUInt32(3, GUID_LOPART(guid));
    trans->Append(stmt);

    // Removed declined name from db
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_DECLINED_NAME);
    stmt->setUInt32(0, GUID_LOPART(guid));
    trans->Append(stmt);

    sWorld->UpdateCharacterNameData(GUID_LOPART(guid), newName, gender, race);

    if (oldRace != race)
    {
        // Switch Languages
        // delete all languages first
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_SKILL_LANGUAGES);
        stmt->setUInt32(0, lowGuid);
        trans->Append(stmt);

        // Now add them back
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_SKILL_LANGUAGE);
        stmt->setUInt32(0, lowGuid);

        // Faction specific languages
        if (team == TEAM_HORDE)
            stmt->setUInt16(1, 109);
        else
            stmt->setUInt16(1, 98);

        trans->Append(stmt);

        // Race specific languages
        if (race != RACE_ORC && race != RACE_HUMAN)
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_SKILL_LANGUAGE);
            stmt->setUInt32(0, lowGuid);

            switch (race)
            {
                case RACE_DWARF:
                    stmt->setUInt16(1, 111);
                    break;
                case RACE_DRAENEI:
                    stmt->setUInt16(1, 759);
                    break;
                case RACE_GNOME:
                    stmt->setUInt16(1, 313);
                    break;
                case RACE_NIGHTELF:
                    stmt->setUInt16(1, 113);
                    break;
                case RACE_WORGEN:
                    stmt->setUInt16(1, 791);
                    break;
                case RACE_UNDEAD_PLAYER:
                    stmt->setUInt16(1, 673);
                    break;
                case RACE_TAUREN:
                    stmt->setUInt16(1, 115);
                    break;
                case RACE_TROLL:
                    stmt->setUInt16(1, 315);
                    break;
                case RACE_BLOODELF:
                    stmt->setUInt16(1, 137);
                    break;
                case RACE_GOBLIN:
                    stmt->setUInt16(1, 792);
                    break;
                case RACE_PANDAREN_NEUTRAL:
                    stmt->setUInt16(1, 905);
                    break;
                case RACE_PANDAREN_ALLIANCE:
                    stmt->setUInt16(1, 906);
                    break;
                case RACE_PANDAREN_HORDE:
                    stmt->setUInt16(1, 907);
                    break;
            }

            trans->Append(stmt);
        }

        if (isFactionChange)
        {
            // Delete all Flypaths
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_TAXI_PATH);
            stmt->setUInt32(0, lowGuid);
            trans->Append(stmt);

            if (level > 7)
            {
                // Update Taxi path
                // this doesn't seem to be 100% blizzlike... but it can't really be helped.
                std::ostringstream taximaskstream;
                uint32 numFullTaximasks = level / 7;
                if (numFullTaximasks > 11)
                    numFullTaximasks = 11;
                if (team == TEAM_ALLIANCE)
                {
                    if (playerClass != CLASS_DEATH_KNIGHT)
                    {
                        for (uint8 i = 0; i < numFullTaximasks; ++i)
                            taximaskstream << uint32(sAllianceTaxiNodesMask[i]) << ' ';
                    }
                    else
                    {
                        for (uint8 i = 0; i < numFullTaximasks; ++i)
                            taximaskstream << uint32(sAllianceTaxiNodesMask[i] | sDeathKnightTaxiNodesMask[i]) << ' ';
                    }
                }
                else
                {
                    if (playerClass != CLASS_DEATH_KNIGHT)
                    {
                        for (uint8 i = 0; i < numFullTaximasks; ++i)
                            taximaskstream << uint32(sHordeTaxiNodesMask[i]) << ' ';
                    }
                    else
                    {
                        for (uint8 i = 0; i < numFullTaximasks; ++i)
                            taximaskstream << uint32(sHordeTaxiNodesMask[i] | sDeathKnightTaxiNodesMask[i]) << ' ';
                    }
                }

                uint32 numEmptyTaximasks = 11 - numFullTaximasks;
                for (uint8 i = 0; i < numEmptyTaximasks; ++i)
                    taximaskstream << "0 ";
                taximaskstream << '0';
                std::string taximask = taximaskstream.str();

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_TAXIMASK);
                stmt->setString(0, taximask);
                stmt->setUInt32(1, lowGuid);
                trans->Append(stmt);
            }

            if (!sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_GUILD))
            {
                // Reset guild
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GUILD_MEMBER);

                stmt->setUInt32(0, lowGuid);

                PreparedQueryResult result = CharacterDatabase.Query(stmt);
                if (result)
                    if (Guild* guild = sGuildMgr->GetGuildById((result->Fetch()[0]).GetUInt32()))
                        guild->DeleteMember(MAKE_NEW_GUID(lowGuid, 0, HIGHGUID_PLAYER));
            }

            if (!sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_ADD_FRIEND))
            {
                // Delete Friend List
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_SOCIAL_BY_GUID);
                stmt->setUInt32(0, lowGuid);
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_SOCIAL_BY_FRIEND);
                stmt->setUInt32(0, lowGuid);
                trans->Append(stmt);
            }

            // Reset homebind and position
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_HOMEBIND);
            stmt->setUInt32(0, lowGuid);
            trans->Append(stmt);

            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_HOMEBIND);
            stmt->setUInt32(0, lowGuid);
            if (team == TEAM_ALLIANCE)
            {
                stmt->setUInt16(1, 0);
                stmt->setUInt16(2, 1519);
                stmt->setFloat (3, -8867.68f);
                stmt->setFloat (4, 673.373f);
                stmt->setFloat (5, 97.9034f);
                Player::SavePositionInDB(0, -8867.68f, 673.373f, 97.9034f, 5.3070f, 1519, lowGuid);
            }
            else
            {
                stmt->setUInt16(1, 1);
                stmt->setUInt16(2, 1637);
                stmt->setFloat (3, 1577.41f);
                stmt->setFloat (4, -4453.68f);
                stmt->setFloat (5, 15.6648f);
                Player::SavePositionInDB(1, 1577.41f, -4453.68f, 15.6648f, 1.8708f, 1637, lowGuid);
            }
            trans->Append(stmt);

            // Achievement conversion
            for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeAchievements.begin(); it != sObjectMgr->FactionChangeAchievements.end(); ++it)
            {
                uint32 achiev_alliance = it->first;
                uint32 achiev_horde = it->second;

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_ACHIEVEMENT_BY_ACHIEVEMENT);
                stmt->setUInt16(0, uint16(team == TEAM_ALLIANCE ? achiev_alliance : achiev_horde));
                stmt->setUInt32(1, lowGuid);
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_ACHIEVEMENT);
                stmt->setUInt16(0, uint16(team == TEAM_ALLIANCE ? achiev_alliance : achiev_horde));
                stmt->setUInt16(1, uint16(team == TEAM_ALLIANCE ? achiev_horde : achiev_alliance));
                stmt->setUInt32(2, lowGuid);
                trans->Append(stmt);
            }

            // Item conversion
            for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeItems.begin(); it != sObjectMgr->FactionChangeItems.end(); ++it)
            {
                uint32 item_alliance = it->first;
                uint32 item_horde = it->second;

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_INVENTORY_FACTION_CHANGE);
                stmt->setUInt32(0, (team == TEAM_ALLIANCE ? item_alliance : item_horde));
                stmt->setUInt32(1, (team == TEAM_ALLIANCE ? item_horde : item_alliance));
                stmt->setUInt32(2, guid);
                trans->Append(stmt);
            }

            // Delete all current quests
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_QUESTSTATUS);
            stmt->setUInt32(0, GUID_LOPART(guid));
            trans->Append(stmt);

            // Quest conversion
            for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeQuests.begin(); it != sObjectMgr->FactionChangeQuests.end(); ++it)
            {
                uint32 quest_alliance = it->first;
                uint32 quest_horde = it->second;

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_QUESTSTATUS_REWARDED_BY_QUEST);
                stmt->setUInt32(0, lowGuid);
                stmt->setUInt32(1, (team == TEAM_ALLIANCE ? quest_alliance : quest_horde));
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_QUESTSTATUS_REWARDED_FACTION_CHANGE);
                stmt->setUInt32(0, (team == TEAM_ALLIANCE ? quest_alliance : quest_horde));
                stmt->setUInt32(1, (team == TEAM_ALLIANCE ? quest_horde : quest_alliance));
                stmt->setUInt32(2, lowGuid);
                trans->Append(stmt);
            }

            // Mark all rewarded quests as "active" (will count for completed quests achievements)
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_QUESTSTATUS_REWARDED_ACTIVE);
            stmt->setUInt32(0, lowGuid);
            trans->Append(stmt);

            // Disable all old-faction specific quests
            {
                ObjectMgr::QuestMap const& questTemplates = sObjectMgr->GetQuestTemplates();
                for (ObjectMgr::QuestMap::const_iterator iter = questTemplates.begin(); iter != questTemplates.end(); ++iter)
                {
                    Quest const* quest = iter->second;
                    uint32 newRaceMask = (team == TEAM_ALLIANCE) ? RACEMASK_ALLIANCE : RACEMASK_HORDE;
                    if (!(quest->GetRequiredRaces() & newRaceMask))
                    {
                        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_QUESTSTATUS_REWARDED_ACTIVE_BY_QUEST);
                        stmt->setUInt32(0, lowGuid);
                        stmt->setUInt32(1, quest->GetQuestId());
                        trans->Append(stmt);
                    }
                }
            }

            // Spell conversion
            for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeSpells.begin(); it != sObjectMgr->FactionChangeSpells.end(); ++it)
            {
                uint32 spell_alliance = it->first;
                uint32 spell_horde = it->second;

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_SPELL_BY_SPELL);
                stmt->setUInt32(0, (team == TEAM_ALLIANCE ? spell_alliance : spell_horde));
                stmt->setUInt32(1, lowGuid);
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_SPELL_FACTION_CHANGE);
                stmt->setUInt32(0, (team == TEAM_ALLIANCE ? spell_alliance : spell_horde));
                stmt->setUInt32(1, (team == TEAM_ALLIANCE ? spell_horde : spell_alliance));
                stmt->setUInt32(2, lowGuid);
                trans->Append(stmt);
            }

            // Reputation conversion
            for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeReputation.begin(); it != sObjectMgr->FactionChangeReputation.end(); ++it)
            {
                uint32 reputation_alliance = it->first;
                uint32 reputation_horde = it->second;
                uint32 newReputation = (team == TEAM_ALLIANCE) ? reputation_alliance : reputation_horde;
                uint32 oldReputation = (team == TEAM_ALLIANCE) ? reputation_horde : reputation_alliance;

                // select old standing set in db
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_REP_BY_FACTION);
                stmt->setUInt32(0, oldReputation);
                stmt->setUInt32(1, lowGuid);
                PreparedQueryResult result = CharacterDatabase.Query(stmt);
                if (!result)
                    continue;

                Field* fields = result->Fetch();
                int32 oldDBRep = fields[0].GetInt32();
                FactionEntry const* factionEntry = sFactionStore.LookupEntry(oldReputation);

                // old base reputation
                int32 oldBaseRep = sObjectMgr->GetBaseReputationOf(factionEntry, oldRace, playerClass);

                // new base reputation
                int32 newBaseRep = sObjectMgr->GetBaseReputationOf(sFactionStore.LookupEntry(newReputation), race, playerClass);

                // final reputation shouldnt change
                int32 FinalRep = oldDBRep + oldBaseRep;
                int32 newDBRep = FinalRep - newBaseRep;

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_REP_BY_FACTION);
                stmt->setUInt32(0, newReputation);
                stmt->setUInt32(1, lowGuid);
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_REP_FACTION_CHANGE);
                stmt->setUInt16(0, uint16(newReputation));
                stmt->setInt32(1, newDBRep);
                stmt->setUInt16(2, uint16(oldReputation));
                stmt->setUInt32(3, lowGuid);
                trans->Append(stmt);
            }

            // Title conversion
            if (knownTitlesStr)
            {
                const uint32 ktcount = KNOWN_TITLES_SIZE * 2;
                uint32 knownTitles[ktcount];
                Tokenizer tokens(knownTitlesStr, ' ', ktcount);

                if (tokens.size() != ktcount)
                    return;

                for (uint32 index = 0; index < ktcount; ++index)
                    knownTitles[index] = atol(tokens[index]);

                for (std::map<uint32, uint32>::const_iterator it = sObjectMgr->FactionChangeTitles.begin(); it != sObjectMgr->FactionChangeTitles.end(); ++it)
                {
                    uint32 title_alliance = it->first;
                    uint32 title_horde = it->second;

                    CharTitlesEntry const* atitleInfo = sCharTitlesStore.LookupEntry(title_alliance);
                    CharTitlesEntry const* htitleInfo = sCharTitlesStore.LookupEntry(title_horde);
                    // new team
                    if (team == TEAM_ALLIANCE)
                    {
                        uint32 bitIndex = htitleInfo->bit_index;
                        uint32 index = bitIndex / 32;
                        uint32 old_flag = 1 << (bitIndex % 32);
                        uint32 new_flag = 1 << (atitleInfo->bit_index % 32);
                        if (knownTitles[index] & old_flag)
                        {
                            knownTitles[index] &= ~old_flag;
                            // use index of the new title
                            knownTitles[atitleInfo->bit_index / 32] |= new_flag;
                        }
                    }
                    else
                    {
                        uint32 bitIndex = atitleInfo->bit_index;
                        uint32 index = bitIndex / 32;
                        uint32 old_flag = 1 << (bitIndex % 32);
                        uint32 new_flag = 1 << (htitleInfo->bit_index % 32);
                        if (knownTitles[index] & old_flag)
                        {
                            knownTitles[index] &= ~old_flag;
                            // use index of the new title
                            knownTitles[htitleInfo->bit_index / 32] |= new_flag;
                        }
                    }

                    std::ostringstream ss;
                    for (uint32 index = 0; index < ktcount; ++index)
                        ss << knownTitles[index] << ' ';

                    stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_TITLES_FACTION_CHANGE);
                    stmt->setString(0, ss.str().c_str());
                    stmt->setUInt32(1, lowGuid);
                    trans->Append(stmt);

                    // unset any currently chosen title
                    stmt = CharacterDatabase.GetPreparedStatement(CHAR_RES_CHAR_TITLES_FACTION_CHANGE);
                    stmt->setUInt32(0, lowGuid);
                    trans->Append(stmt);
                }
            }
        }

        // Race specific quests and spells (after faction change, because quests get deleted there)
        if (playerClass != CLASS_DEATH_KNIGHT)
        {
            sServiceMgr->AddSpecificPlayerData(lowGuid, oldRace, race, playerClass, nullptr, true, true);

            stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_SKILLS_BOOST);
            stmt->setUInt32(0, lowGuid);

            if (PreparedQueryResult result = CharacterDatabase.Query(stmt))
            {
                do
                {
                    uint32 skillId = (*result)[0].GetUInt16();
                    auto info = GetSkillRaceClassInfo(skillId, race, playerClass);
                    if (!info)
                    {
                        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHARACTER_SKILL);
                        stmt->setUInt32(0, lowGuid);
                        stmt->setUInt16(1, skillId);
                        trans->Append(stmt);
                    }

                } while (result->NextRow());
            }
        }
    }

    CharacterDatabase.CommitTransaction(trans);

    WorldPacket data(SMSG_CHAR_FACTION_CHANGE_RESULT, 1 + 8 + (newName.size() + 1) + 1 + 1 + 1 + 1 + 1 + 1 + 1);
    data << uint8(RESPONSE_SUCCESS);
    data << uint64(guid);
    data << newName;
    data << uint8(gender);
    data << uint8(skin);
    data << uint8(face);
    data << uint8(hairStyle);
    data << uint8(hairColor);
    data << uint8(facialHair);
    data << uint8(race);
    SendPacket(&data);

    sServiceMgr->ExecutedServices(guid, SERVICE_TYPE_CHANGE_RACE, Format("Old Race: %u Old Name: %s", uint32(oldRace), oldName.c_str()), Format("New Race: %u New Name: %s", uint32(race), newName.c_str()));
}

void WorldSession::HandleRandomizeCharNameOpcode(WorldPacket& recvData)
{
    uint8 gender, race;

    recvData >> gender;
    recvData >> race;

    if (!Player::IsValidRace(race))
    {
        TC_LOG_ERROR("general", "Invalid race (%u) sent by accountId: %u", race, GetAccountId());
        return;
    }

    if (!Player::IsValidGender(gender))
    {
        TC_LOG_ERROR("general", "Invalid gender (%u) sent by accountId: %u", gender, GetAccountId());
        return;
    }

    std::string const* name = GetRandomCharacterName(race, gender);
    WorldPacket data(SMSG_RANDOMIZE_CHAR_NAME, 1 + name->size());
    data.WriteBit(true); // result
    data.WriteBits(name->size(), 6);
    data.FlushBits();
    data.WriteString(*name);
    SendPacket(&data);
}

void WorldSession::HandleReorderCharacters(WorldPacket& recvData)
{
    uint32 charactersCount = recvData.ReadBits(9);

    std::vector<ObjectGuid> guids(charactersCount);
    uint8 position;

    for (uint8 i = 0; i < charactersCount; ++i)
    {
        guids[i][4] = recvData.ReadBit();
        guids[i][2] = recvData.ReadBit();
        guids[i][7] = recvData.ReadBit();
        guids[i][6] = recvData.ReadBit();
        guids[i][0] = recvData.ReadBit();
        guids[i][5] = recvData.ReadBit();
        guids[i][3] = recvData.ReadBit();
        guids[i][1] = recvData.ReadBit();
    }

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
    for (uint8 i = 0; i < charactersCount; ++i)
    {
        recvData.ReadByteSeq(guids[i][1]);
        recvData.ReadByteSeq(guids[i][2]);
        recvData.ReadByteSeq(guids[i][7]);
        recvData.ReadByteSeq(guids[i][5]);
        recvData.ReadByteSeq(guids[i][4]);
        recvData.ReadByteSeq(guids[i][0]);
        recvData.ReadByteSeq(guids[i][3]);
        recvData.ReadByteSeq(guids[i][6]);
        recvData >> position;

        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_LIST_SLOT);
        stmt->setUInt8(0, position);
        stmt->setUInt32(1, GUID_LOPART(guids[i]));
        trans->Append(stmt);
    }

    CharacterDatabase.CommitTransaction(trans);
}

void WorldSession::HandleOpeningCinematic(WorldPacket& /*recvData*/)
{
    // Only players that has not yet gained any experience can use this
    if (_player->GetUInt32Value(PLAYER_FIELD_XP))
        return;

    if (ChrClassesEntry const* classEntry = sChrClassesStore.LookupEntry(_player->GetClass()))
    {
        if (classEntry->CinematicSequence)
            _player->SendCinematicStart(classEntry->CinematicSequence);
        else if (ChrRacesEntry const* raceEntry = sChrRacesStore.LookupEntry(_player->GetRace()))
            _player->SendCinematicStart(raceEntry->CinematicSequence);
    }
}
