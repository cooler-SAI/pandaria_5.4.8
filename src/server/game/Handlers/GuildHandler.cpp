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
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "Log.h"
#include "Opcodes.h"
#include "Guild.h"
#include "GossipDef.h"
#include "SocialMgr.h"
#include "Group.h"

 // Cleanup bad characters
void cleanStr(std::string &str) {
    str.erase(remove(str.begin(), str.end(), '|'), str.end());
}


void WorldSession::HandleGuildQueryOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guildGuid;
    ObjectGuid playerGuid;

    playerGuid[7] = recvPacket.ReadBit();
    playerGuid[3] = recvPacket.ReadBit();
    playerGuid[4] = recvPacket.ReadBit();
    guildGuid[3] = recvPacket.ReadBit();
    guildGuid[4] = recvPacket.ReadBit();
    playerGuid[2] = recvPacket.ReadBit();
    playerGuid[6] = recvPacket.ReadBit();
    guildGuid[2] = recvPacket.ReadBit();
    guildGuid[5] = recvPacket.ReadBit();
    playerGuid[1] = recvPacket.ReadBit();
    playerGuid[5] = recvPacket.ReadBit();
    guildGuid[7] = recvPacket.ReadBit();
    playerGuid[0] = recvPacket.ReadBit();
    guildGuid[1] = recvPacket.ReadBit();
    guildGuid[6] = recvPacket.ReadBit();
    guildGuid[0] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(playerGuid[7]);
    recvPacket.ReadByteSeq(guildGuid[2]);
    recvPacket.ReadByteSeq(guildGuid[4]);
    recvPacket.ReadByteSeq(guildGuid[7]);
    recvPacket.ReadByteSeq(playerGuid[6]);
    recvPacket.ReadByteSeq(playerGuid[0]);
    recvPacket.ReadByteSeq(guildGuid[6]);
    recvPacket.ReadByteSeq(guildGuid[0]);
    recvPacket.ReadByteSeq(guildGuid[3]);
    recvPacket.ReadByteSeq(playerGuid[2]);
    recvPacket.ReadByteSeq(guildGuid[5]);
    recvPacket.ReadByteSeq(playerGuid[3]);
    recvPacket.ReadByteSeq(guildGuid[1]);
    recvPacket.ReadByteSeq(playerGuid[4]);
    recvPacket.ReadByteSeq(playerGuid[1]);
    recvPacket.ReadByteSeq(playerGuid[5]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_QUERY [%s]: Guild: %u Target: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(guildGuid), GUID_LOPART(playerGuid));

    if (Guild* guild = sGuildMgr->GetGuildByGuid(guildGuid))
        if (guild->IsMember(playerGuid))
            guild->HandleQuery(this);
}

void WorldSession::HandleGuildInviteOpcode(WorldPacket& recvPacket)
{
    uint32 nameLength = recvPacket.ReadBits(9);
    std::string invitedName = recvPacket.ReadString(nameLength);


    TC_LOG_DEBUG("guild", "CMSG_GUILD_INVITE [%s]: Invited: %s", GetPlayerInfo().c_str(), invitedName.c_str());
    if (normalizePlayerName(invitedName))
        if (Guild* guild = GetPlayer()->GetGuild())
            guild->HandleInviteMember(this, invitedName);
}

void WorldSession::HandleGuildRemoveOpcode(WorldPacket& recvPacket)
{
    ObjectGuid playerGuid;

    playerGuid[7] = recvPacket.ReadBit();
    playerGuid[3] = recvPacket.ReadBit();
    playerGuid[4] = recvPacket.ReadBit();
    playerGuid[2] = recvPacket.ReadBit();
    playerGuid[5] = recvPacket.ReadBit();
    playerGuid[6] = recvPacket.ReadBit();
    playerGuid[1] = recvPacket.ReadBit();
    playerGuid[0] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(playerGuid[0]);
    recvPacket.ReadByteSeq(playerGuid[2]);
    recvPacket.ReadByteSeq(playerGuid[5]);
    recvPacket.ReadByteSeq(playerGuid[6]);
    recvPacket.ReadByteSeq(playerGuid[7]);
    recvPacket.ReadByteSeq(playerGuid[1]);
    recvPacket.ReadByteSeq(playerGuid[4]);
    recvPacket.ReadByteSeq(playerGuid[3]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_REMOVE [%s]: Target: %u", GetPlayerInfo().c_str(), GUID_LOPART(playerGuid));

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleRemoveMember(this, playerGuid);
}

void WorldSession::HandleGuildAcceptOpcode(WorldPacket& /*recvPacket*/)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_ACCEPT [%s]", GetPlayerInfo().c_str());

    if (!GetPlayer()->GetGuildId())
        if (Guild* guild = sGuildMgr->GetGuildById(GetPlayer()->GetGuildIdInvited()))
            guild->HandleAcceptMember(this);
}

void WorldSession::HandleGuildDeclineOpcode(WorldPacket& /*recvPacket*/)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_DECLINE [%s]", GetPlayerInfo().c_str());

    GetPlayer()->SetGuildIdInvited(0);
    GetPlayer()->SetInGuild(0);

    if (GetPlayer()->GetLastGuildInviterGUID())
    {
        if (Player* inviter = ObjectAccessor::FindPlayer(GetPlayer()->GetLastGuildInviterGUID()))
            inviter->SendDeclineGuildInvitation(GetPlayer()->GetName());

        GetPlayer()->SetLastGuildInviterGUID(0);
    }
}

void WorldSession::HandleGuildRosterOpcode(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_ROSTER [%s]", GetPlayerInfo().c_str());
    recvPacket.rfinish();

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleRoster(this);
    else
        Guild::SendCommandResult(this, GUILD_COMMAND_ROSTER, ERR_GUILD_PLAYER_NOT_IN_GUILD);
}

void WorldSession::HandleGuildPromoteOpcode(WorldPacket& recvPacket)
{
    ObjectGuid targetGuid;

    targetGuid[6] = recvPacket.ReadBit();
    targetGuid[0] = recvPacket.ReadBit();
    targetGuid[4] = recvPacket.ReadBit();
    targetGuid[3] = recvPacket.ReadBit();
    targetGuid[1] = recvPacket.ReadBit();
    targetGuid[7] = recvPacket.ReadBit();
    targetGuid[2] = recvPacket.ReadBit();
    targetGuid[5] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(targetGuid[1]);
    recvPacket.ReadByteSeq(targetGuid[7]);
    recvPacket.ReadByteSeq(targetGuid[2]);
    recvPacket.ReadByteSeq(targetGuid[5]);
    recvPacket.ReadByteSeq(targetGuid[3]);
    recvPacket.ReadByteSeq(targetGuid[4]);
    recvPacket.ReadByteSeq(targetGuid[0]);
    recvPacket.ReadByteSeq(targetGuid[6]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_PROMOTE [%s]: Target: %u", GetPlayerInfo().c_str(), GUID_LOPART(targetGuid));

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleUpdateMemberRank(this, targetGuid, false);
}

void WorldSession::HandleGuildDemoteOpcode(WorldPacket& recvPacket)
{
    ObjectGuid targetGuid;

    targetGuid[3] = recvPacket.ReadBit();
    targetGuid[6] = recvPacket.ReadBit();
    targetGuid[0] = recvPacket.ReadBit();
    targetGuid[2] = recvPacket.ReadBit();
    targetGuid[7] = recvPacket.ReadBit();
    targetGuid[5] = recvPacket.ReadBit();
    targetGuid[4] = recvPacket.ReadBit();
    targetGuid[1] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(targetGuid[7]);
    recvPacket.ReadByteSeq(targetGuid[4]);
    recvPacket.ReadByteSeq(targetGuid[2]);
    recvPacket.ReadByteSeq(targetGuid[5]);
    recvPacket.ReadByteSeq(targetGuid[1]);
    recvPacket.ReadByteSeq(targetGuid[3]);
    recvPacket.ReadByteSeq(targetGuid[0]);
    recvPacket.ReadByteSeq(targetGuid[6]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_DEMOTE [%s]: Target: %u", GetPlayerInfo().c_str(), GUID_LOPART(targetGuid));

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleUpdateMemberRank(this, targetGuid, true);
}

void WorldSession::HandleGuildAssignRankOpcode(WorldPacket& recvPacket)
{
    ObjectGuid targetGuid;

    uint32 rankIndex;
    recvPacket >> rankIndex;

    targetGuid[2] = recvPacket.ReadBit();
    targetGuid[3] = recvPacket.ReadBit();
    targetGuid[1] = recvPacket.ReadBit();
    targetGuid[6] = recvPacket.ReadBit();
    targetGuid[0] = recvPacket.ReadBit();
    targetGuid[4] = recvPacket.ReadBit();
    targetGuid[7] = recvPacket.ReadBit();
    targetGuid[5] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(targetGuid[7]);
    recvPacket.ReadByteSeq(targetGuid[3]);
    recvPacket.ReadByteSeq(targetGuid[2]);
    recvPacket.ReadByteSeq(targetGuid[5]);
    recvPacket.ReadByteSeq(targetGuid[6]);
    recvPacket.ReadByteSeq(targetGuid[0]);
    recvPacket.ReadByteSeq(targetGuid[4]);
    recvPacket.ReadByteSeq(targetGuid[1]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_ASSIGN_MEMBER_RANK [%s]: Target: %u Rank: %u, Issuer: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(targetGuid), rankIndex, GUID_LOPART(_player->GetGUID()));

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetMemberRank(this, targetGuid, _player->GetGUID(), rankIndex);
}

void WorldSession::HandleGuildLeaveOpcode(WorldPacket& /*recvPacket*/)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_LEAVE [%s]", GetPlayerInfo().c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleLeaveMember(this);
}

void WorldSession::HandleGuildDisbandOpcode(WorldPacket& /*recvPacket*/)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_DISBAND [%s]", GetPlayerInfo().c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleDisband(this);
}

void WorldSession::HandleGuildMOTDOpcode(WorldPacket& recvPacket)
{
    uint32 motdLength = recvPacket.ReadBits(10);
    std::string motd = recvPacket.ReadString(motdLength);
    TC_LOG_DEBUG("guild", "CMSG_GUILD_MOTD [%s]: MOTD: %s", GetPlayerInfo().c_str(), motd.c_str());

    // Check for overflow
    if (motd.length() > 128)
        return;

    // Cleanup bad characters
    cleanStr(motd);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetMOTD(this, motd);
}

void WorldSession::HandleGuildSetNoteOpcode(WorldPacket& recvPacket)
{
    ObjectGuid playerGuid;

    playerGuid[1]     = recvPacket.ReadBit();
    uint32 notelength = recvPacket.ReadBits(8);            // note size
    playerGuid[4]     = recvPacket.ReadBit();
    playerGuid[2]     = recvPacket.ReadBit();
    bool isPublic     = recvPacket.ReadBit();              // 0 == Officer, 1 == Public
    playerGuid[3]     = recvPacket.ReadBit();
    playerGuid[5]     = recvPacket.ReadBit();
    playerGuid[0]     = recvPacket.ReadBit();
    playerGuid[6]     = recvPacket.ReadBit();
    playerGuid[7]     = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(playerGuid[5]);
    recvPacket.ReadByteSeq(playerGuid[1]);
    recvPacket.ReadByteSeq(playerGuid[6]);
    std::string note = recvPacket.ReadString(notelength);  // note
    recvPacket.ReadByteSeq(playerGuid[0]);
    recvPacket.ReadByteSeq(playerGuid[7]);
    recvPacket.ReadByteSeq(playerGuid[4]);
    recvPacket.ReadByteSeq(playerGuid[3]);
    recvPacket.ReadByteSeq(playerGuid[2]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_SET_NOTE [%s]: Target: %u, Note: %s, Public: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(playerGuid), note.c_str(), isPublic);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetMemberNote(this, note, playerGuid, isPublic);
}

void WorldSession::HandleGuildQueryRanksOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guildGuid;

    guildGuid[0] = recvPacket.ReadBit();
    guildGuid[2] = recvPacket.ReadBit();
    guildGuid[5] = recvPacket.ReadBit();
    guildGuid[4] = recvPacket.ReadBit();
    guildGuid[3] = recvPacket.ReadBit();
    guildGuid[7] = recvPacket.ReadBit();
    guildGuid[6] = recvPacket.ReadBit();
    guildGuid[1] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guildGuid[6]);
    recvPacket.ReadByteSeq(guildGuid[0]);
    recvPacket.ReadByteSeq(guildGuid[1]);
    recvPacket.ReadByteSeq(guildGuid[7]);
    recvPacket.ReadByteSeq(guildGuid[3]);
    recvPacket.ReadByteSeq(guildGuid[2]);
    recvPacket.ReadByteSeq(guildGuid[5]);
    recvPacket.ReadByteSeq(guildGuid[4]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_QUERY_RANKS [%s]: Guild: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(guildGuid));

    if (Guild* guild = sGuildMgr->GetGuildByGuid(guildGuid))
        if (guild->IsMember(_player->GetGUID()))
            guild->SendGuildRankInfo(this);
}

void WorldSession::HandleGuildAddRankOpcode(WorldPacket& recvPacket)
{
    uint32 rankId;
    recvPacket >> rankId;

    uint32 length = recvPacket.ReadBits(7);
    std::string rankName = recvPacket.ReadString(length);

    // Check for overflow
    if (rankName.length() > 15)
        return;

    // Cleanup bad characters
    cleanStr(rankName);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_ADD_RANK [%s]: Rank: %s", GetPlayerInfo().c_str(), rankName.c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleAddNewRank(this, rankName);
}

void WorldSession::HandleGuildDelRankOpcode(WorldPacket& recvPacket)
{
    int32 rankIndex;
    recvPacket >> rankIndex;

    TC_LOG_DEBUG("guild", "CMSG_GUILD_DEL_RANK [%s]: Rank: %u", GetPlayerInfo().c_str(), rankIndex);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleRemoveRank(this, rankIndex);
}

void WorldSession::HandleGuildSwitchRank(WorldPacket& recvPacket)
{
    int32 rankIndex = recvPacket.read<int32>();
    bool up = recvPacket.ReadBit();

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSwitchRank(this, rankIndex, up);
}

void WorldSession::HandleGuildChangeInfoTextOpcode(WorldPacket& recvPacket)
{
    uint32 length = recvPacket.ReadBits(11);
    std::string info = recvPacket.ReadString(length);

    // Check for overflow
    if (info.length() > 500)
        return;

    // Cleanup bad characters
    cleanStr(info);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_INFO_TEXT [%s]: %s", GetPlayerInfo().c_str(), info.c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetInfo(this, info);
}

void WorldSession::HandleSaveGuildEmblemOpcode(WorldPacket& recvPacket)
{
    ObjectGuid vendorGuid;

    EmblemInfo emblemInfo;
    emblemInfo.ReadPacket(recvPacket);

    recvPacket.ReadGuidMask(vendorGuid, 0, 7, 4, 6, 5, 1, 2, 3);
    recvPacket.ReadGuidBytes(vendorGuid, 6, 2, 7, 5, 0, 4, 1, 3);

    TC_LOG_DEBUG("guild", "CMSG_SAVE_GUILD_EMBLEM [%s]: Guid: [" UI64FMTD"] Style: %d, Color: %d, BorderStyle: %d, BorderColor: %d, BackgroundColor: %d",
        GetPlayerInfo().c_str(), uint64(vendorGuid), emblemInfo.GetStyle(), emblemInfo.GetColor(), emblemInfo.GetBorderStyle(),
        emblemInfo.GetBorderColor(), emblemInfo.GetBackgroundColor());

    if (GetPlayer()->GetNPCIfCanInteractWith(vendorGuid, UNIT_NPC_FLAG_TABARDDESIGNER))
    {
        // Remove fake death
        if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
            GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        if (Guild* guild = GetPlayer()->GetGuild())
            guild->HandleSetEmblem(this, emblemInfo);
        else
            Guild::SendSaveEmblemResult(this, ERR_GUILDEMBLEM_NOGUILD); // "You are not part of a guild!";
    }
    else
        Guild::SendSaveEmblemResult(this, ERR_GUILDEMBLEM_INVALIDVENDOR); // "That's not an emblem vendor!"
}

void WorldSession::HandleGuildEventLogQueryOpcode(WorldPacket& /* recvPacket */)
{
    TC_LOG_DEBUG("guild", "MSG_GUILD_EVENT_LOG_QUERY [%s]", GetPlayerInfo().c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendEventLog(this);
}

void WorldSession::HandleGuildBankMoneyWithdrawn(WorldPacket& /* recvPacket */)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_MONEY_WITHDRAWN [%s]", GetPlayerInfo().c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendMoneyInfo(this);
}

void WorldSession::HandleGuildPermissions(WorldPacket& /* recvPacket */)
{
    // Null Packet
    TC_LOG_DEBUG("guild", "CMSG_GUILD_PERMISSIONS [%s]", GetPlayerInfo().c_str());

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendPermissions(this);
}

// Called when clicking on Guild bank gameobject
void WorldSession::HandleGuildBankerActivate(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    bool sendAllSlots;

    guid[3] = recvPacket.ReadBit();
    sendAllSlots = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[3]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANKER_ACTIVATE [%s]: Go: [" UI64FMTD "] AllSlots: %u", GetPlayerInfo().c_str(), (uint64)guid, sendAllSlots);

    auto go = GetPlayer()->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_GUILD_BANK);
    if (!go)
        return;

    Guild* ownerGuild = nullptr;
    if (go->GetOwner())
        if (Player* player = go->GetOwner()->ToPlayer())
            ownerGuild = player->GetGuild();

    Guild* const guild = GetPlayer()->GetGuild();
    if (ownerGuild && ownerGuild != guild) // player must be in same guild as summoner
    {
        Guild::SendCommandResult(this, GUILD_COMMAND_VIEW_TAB, ERR_GUILD_PERMISSIONS);
        return;
    }

    if (!guild)
    {
        Guild::SendCommandResult(this, GUILD_COMMAND_VIEW_TAB, ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    guild->SendBankList(this, 0, true, true);
}

// Called when opening guild bank tab only (first one)
void WorldSession::HandleGuildBankQueryTab(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    uint8 tabId;
    bool sendAllSlots;

    recvPacket >> tabId;

    guid[7] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    sendAllSlots = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[1]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_QUERY_TAB [%s]: Go: [" UI64FMTD "], TabId: %u, AllSlots: %u", GetPlayerInfo().c_str(), (uint64)guid, tabId, sendAllSlots);

    if (GetPlayer()->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_GUILD_BANK))
        if (Guild* guild = GetPlayer()->GetGuild())
            guild->SendBankList(this, tabId, true, false);
}

void WorldSession::HandleGuildBankDepositMoney(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    uint64 money;

    recvPacket >> money;
    guid[2] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[3]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_DEPOSIT_MONEY [%s]: Go: [" UI64FMTD "], money: " UI64FMTD,
        GetPlayerInfo().c_str(), (uint64)guid, money);

    if (GetPlayer()->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_GUILD_BANK))
        if (money && GetPlayer()->HasEnoughMoney(money))
            if (Guild* guild = GetPlayer()->GetGuild())
                guild->HandleMemberDepositMoney(this, money);
}

void WorldSession::HandleGuildBankWithdrawMoney(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    uint64 money;
    recvPacket >> money;

    guid[1] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[5]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_WITHDRAW_MONEY [%s]: Go: [" UI64FMTD "], money: " UI64FMTD,
        GetPlayerInfo().c_str(), (uint64)guid, money);

    if (money && GetPlayer()->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_GUILD_BANK))
        if (Guild* guild = GetPlayer()->GetGuild())
            guild->HandleMemberWithdrawMoney(this, money);
}

void WorldSession::HandleGuildBankSwapItems(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_SWAP_ITEMS [%s]", GetPlayerInfo().c_str());

    Guild* guild = GetPlayer()->GetGuild();
    if (!guild)
    {
        recvPacket.rfinish();                   // Prevent additional spam at rejected packet
        return;
    }

    ObjectGuid banker;
    uint32 stackCount, itemId, itemId2 = 0, bankItemCount = 0;
    uint8 bankSlot, bankTab, toSlot, containerSlot = NULL_BAG, containerItemSlot = NULL_SLOT, bankSlot2 = 0, bankTab2 = 0;
    bool hasContainerSlot, hasContainerItemSlot, hasItemId2, hasBankSlot2, hasBankTab2, hasBankItemCount, bankOnly, autoStore;

    recvPacket >> stackCount;
    recvPacket >> bankSlot;
    recvPacket >> toSlot;
    recvPacket >> itemId;
    recvPacket >> bankTab;

    banker[5] = recvPacket.ReadBit();
    hasBankTab2 = !recvPacket.ReadBit();
    banker[1] = recvPacket.ReadBit();
    hasContainerSlot = !recvPacket.ReadBit();
    autoStore = recvPacket.ReadBit();
    banker[0] = recvPacket.ReadBit();
    hasItemId2 = !recvPacket.ReadBit();
    hasBankSlot2 = !recvPacket.ReadBit();
    banker[2] = recvPacket.ReadBit();
    bankOnly = recvPacket.ReadBit();
    banker[4] = recvPacket.ReadBit();
    banker[7] = recvPacket.ReadBit();
    banker[3] = recvPacket.ReadBit();
    hasContainerItemSlot = !recvPacket.ReadBit();
    banker[6] = recvPacket.ReadBit();
    hasBankItemCount = !recvPacket.ReadBit();

    recvPacket.ReadByteSeq(banker[2]);
    recvPacket.ReadByteSeq(banker[6]);
    recvPacket.ReadByteSeq(banker[5]);
    recvPacket.ReadByteSeq(banker[4]);
    recvPacket.ReadByteSeq(banker[0]);
    recvPacket.ReadByteSeq(banker[3]);
    recvPacket.ReadByteSeq(banker[1]);
    recvPacket.ReadByteSeq(banker[7]);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(banker, GAMEOBJECT_TYPE_GUILD_BANK))
    {
        recvPacket.rfinish();                   // Prevent additional spam at rejected packet
        return;
    }

    if (hasItemId2)
        recvPacket >> itemId2;                  // source item id

    if (hasContainerSlot)
        recvPacket >> containerSlot;

    if (hasContainerItemSlot)
        recvPacket >> containerItemSlot;

    if (hasBankSlot2)
        recvPacket >> bankSlot2;                // source bank slot

    if (hasBankItemCount)
        recvPacket >> bankItemCount;

    if (hasBankTab2)
        recvPacket >> bankTab2;                 // source bank tab

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(banker, GAMEOBJECT_TYPE_GUILD_BANK))
    {
        recvPacket.rfinish();                   // Prevent additional spam at rejected packet
        return;
    }

    if (bankOnly)
        guild->SwapItems(GetPlayer(), bankTab2, bankSlot2, bankTab, bankSlot, stackCount);
    else
    {
        if (!Player::IsInventoryPos(containerSlot, containerItemSlot) && !(containerSlot == NULL_BAG && containerItemSlot == NULL_SLOT))
            GetPlayer()->SendEquipError(EQUIP_ERR_INTERNAL_BAG_ERROR, NULL);
        else
        {
            // What the fuck is this? Why client sends 255 for bag slot 0? Arrays start at -1? /s
            if (toSlot == 0 && containerItemSlot == 255)
                containerItemSlot = 0;
            guild->SwapItemsWithInventory(GetPlayer(), toSlot != 0, bankTab, bankSlot, containerSlot, containerItemSlot, stackCount);
        }
    }
}

void WorldSession::HandleGuildBankBuyTab(WorldPacket& recvPacket)
{
    uint8 tabId;
    ObjectGuid guid;

    recvPacket >> tabId;
    guid[0] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[0]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_BUY_TAB [%s]: Go: [" UI64FMTD "], TabId: %u", GetPlayerInfo().c_str(), (uint64)guid, tabId);

    // Since Cata you can buy tabs from the guild constrol tab - no need to check for guid
    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleBuyBankTab(this, tabId);
}

void WorldSession::HandleGuildBankUpdateTab(WorldPacket& recvPacket)
{
    uint32 iconLen, nameLen;
    std::string name, icon;
    ObjectGuid guid;
    uint8 tabId;

    recvPacket >> tabId;
    guid[5] = recvPacket.ReadBit();
    iconLen = recvPacket.ReadBits(9);
    guid[1] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    nameLen = recvPacket.ReadBits(7);

    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[4]);
    icon = recvPacket.ReadString(iconLen);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[0]);
    name = recvPacket.ReadString(nameLen);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[6]);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_BANK_UPDATE_TAB [%s]: Go: [" UI64FMTD "], TabId: %u, Name: %s, Icon: %s",
        GetPlayerInfo().c_str(), (uint64)guid, tabId, name.c_str(), icon.c_str());

    // Check for overflow
    if (name.length() > 16 || icon.length() > 128)
        return;

    // Cleanup bad characters
    cleanStr(name);

    if (!name.empty() && !icon.empty())
        if (GetPlayer()->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_GUILD_BANK))
            if (Guild* guild = GetPlayer()->GetGuild())
                guild->HandleSetBankTabInfo(this, tabId, name, icon);
}

void WorldSession::HandleGuildBankLogQuery(WorldPacket& recvPacket)
{
    uint32 tabId;
    recvPacket >> tabId;

    TC_LOG_DEBUG("guild", "MSG_GUILD_BANK_LOG_QUERY [%s]: TabId: %u", GetPlayerInfo().c_str(), tabId);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendBankLog(this, tabId);
}

void WorldSession::HandleQueryGuildBankTabText(WorldPacket &recvPacket)
{
    uint32 tabId;
    recvPacket >> tabId;

    TC_LOG_DEBUG("guild", "MSG_QUERY_GUILD_BANK_TEXT [%s]: TabId: %u", GetPlayerInfo().c_str(), tabId);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendBankTabText(this, tabId);
}

void WorldSession::HandleGuildQueryXPOpcode(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_QUERY_GUILD_XP");

    ObjectGuid guildGuid;

    guildGuid[5] = recvPacket.ReadBit();
    guildGuid[6] = recvPacket.ReadBit();
    guildGuid[0] = recvPacket.ReadBit();
    guildGuid[1] = recvPacket.ReadBit();
    guildGuid[3] = recvPacket.ReadBit();
    guildGuid[7] = recvPacket.ReadBit();
    guildGuid[4] = recvPacket.ReadBit();
    guildGuid[2] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guildGuid[4]);
    recvPacket.ReadByteSeq(guildGuid[6]);
    recvPacket.ReadByteSeq(guildGuid[3]);
    recvPacket.ReadByteSeq(guildGuid[0]);
    recvPacket.ReadByteSeq(guildGuid[7]);
    recvPacket.ReadByteSeq(guildGuid[5]);
    recvPacket.ReadByteSeq(guildGuid[2]);
    recvPacket.ReadByteSeq(guildGuid[1]);

    TC_LOG_DEBUG("guild", "CMSG_QUERY_GUILD_XP [%s]: Guild: %u", GetPlayerInfo().c_str(), GUID_LOPART(guildGuid));

    if (Guild* guild = sGuildMgr->GetGuildByGuid(guildGuid))
        if (guild->IsMember(_player->GetGUID()))
            guild->SendGuildXP(this);
}

void WorldSession::HandleGuildSetRankPermissionsOpcode(WorldPacket& recvPacket)
{
    Guild* guild = GetPlayer()->GetGuild();
    if (!guild)
    {
        recvPacket.rfinish();
        return;
    }

    uint32 unk;         // Need sniffs. Generaly 1.
    uint32 rankIndex;
    uint32 oldRights;
    uint32 newRights;
    uint32 moneyPerDay;

    recvPacket >> unk;

    GuildBankRightsAndSlotsVec rightsAndSlots(GUILD_BANK_MAX_TABS);
    for (uint8 tabId = 0; tabId < GUILD_BANK_MAX_TABS; ++tabId)
    {
        uint32 bankRights;
        uint32 slots;

        recvPacket >> bankRights;
        recvPacket >> slots;

        rightsAndSlots[tabId] = GuildBankRightsAndSlots(tabId, uint8(bankRights), slots);
    }

    recvPacket >> moneyPerDay;
    recvPacket >> oldRights;
    recvPacket >> newRights;
    recvPacket >> rankIndex;

    uint32 nameLength = recvPacket.ReadBits(7);
    std::string rankName = recvPacket.ReadString(nameLength);

    TC_LOG_DEBUG("guild", "CMSG_GUILD_SET_RANK_PERMISSIONS [%s]: Rank: %s (%u)", GetPlayerInfo().c_str(), rankName.c_str(), rankIndex);

    guild->HandleSetRankInfo(this, rankIndex, rankName, newRights, moneyPerDay, rightsAndSlots);
}

void WorldSession::HandleGuildRequestPartyState(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_GUILD_REQUEST_PARTY_STATE");

    ObjectGuid guildGuid;

    guildGuid[1] = recvPacket.ReadBit();
    guildGuid[5] = recvPacket.ReadBit();
    guildGuid[7] = recvPacket.ReadBit();
    guildGuid[2] = recvPacket.ReadBit();
    guildGuid[6] = recvPacket.ReadBit();
    guildGuid[3] = recvPacket.ReadBit();
    guildGuid[0] = recvPacket.ReadBit();
    guildGuid[4] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guildGuid[2]);
    recvPacket.ReadByteSeq(guildGuid[5]);
    recvPacket.ReadByteSeq(guildGuid[4]);
    recvPacket.ReadByteSeq(guildGuid[6]);
    recvPacket.ReadByteSeq(guildGuid[1]);
    recvPacket.ReadByteSeq(guildGuid[0]);
    recvPacket.ReadByteSeq(guildGuid[7]);
    recvPacket.ReadByteSeq(guildGuid[3]);

    uint32 requiredMemberCount = 0;
    float xpMult = 0.0f;
    uint32 currentMemberCount = 0;
    bool isGuildGroup = false;
    if (Group* group = GetPlayer()->GetGroup())
        isGuildGroup = group->IsGuildGroup(GetPlayer()->GetGuildId(), GetPlayer(), &xpMult, &currentMemberCount, &requiredMemberCount);

    WorldPacket data(SMSG_GUILD_PARTY_STATE_RESPONSE, 13);

    data << uint32(requiredMemberCount);
    data << float(xpMult);
    data << uint32(currentMemberCount);
    data.WriteBit(isGuildGroup);
    data.FlushBits();

    SendPacket(&data);
}

void WorldSession::HandleGuildRequestMaxDailyXP(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    guid[0] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[0]);

    if (Guild* guild = sGuildMgr->GetGuildByGuid(guid))
    {
        if (guild->IsMember(_player->GetGUID()))
        {
            WorldPacket data(SMSG_GUILD_MAX_DAILY_XP, 8);
            data << uint64(sWorld->getIntConfig(CONFIG_GUILD_DAILY_XP_CAP));
            SendPacket(&data);
        }
    }
}

void WorldSession::HandleAutoDeclineGuildInvites(WorldPacket& recvPacket)
{
    uint8 enable = recvPacket.ReadBit();
    GetPlayer()->ApplyModFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_AUTO_DECLINE_GUILD, enable);
}

void WorldSession::HandleGuildRewardsQueryOpcode(WorldPacket& recvPacket)
{
    recvPacket.read_skip<uint32>(); // Unk

    if (sGuildMgr->GetGuildById(_player->GetGuildId()))
    {
        std::vector<GuildReward> const& rewards = sGuildMgr->GetGuildRewards();

        WorldPacket data(SMSG_GUILD_REWARDS_LIST, 3 + rewards.size() * (4 + 4 + 4 + 8 + 4 + 4));
        data.WriteBits(rewards.size(), 19);

        for (uint32 i = 0; i < rewards.size(); i++)
            data.WriteBits(rewards[i].Achievements.size(), 22);

        data.FlushBits();

        for (uint32 i = 0; i < rewards.size(); i++)
        {
            for (uint32 j = 0; j < rewards[i].Achievements.size(); j++)
                data << uint32(rewards[i].Achievements[j]);

            data << int32(rewards[i].Racemask);
            data << uint32(rewards[i].Entry);
            data << uint32(0); // minGuildLevel
            data << uint32(rewards[i].Standing);
            data << uint64(rewards[i].Price);
        }

        data << uint32(time(NULL));
        SendPacket(&data);
    }
}

void WorldSession::HandleGuildQueryNewsOpcode(WorldPacket& recvPacket)
{
    recvPacket.rfinish();

    TC_LOG_DEBUG("guild", "CMSG_GUILD_QUERY_NEWS [%s]", GetPlayerInfo().c_str());
    if (Guild* guild = GetPlayer()->GetGuild())
        guild->SendNewsUpdate(this);
}

void WorldSession::HandleGuildNewsUpdateStickyOpcode(WorldPacket& recvPacket)
{
    uint32 newsId;
    bool sticky;
    ObjectGuid guid;

    recvPacket >> newsId;

    guid[6] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    sticky = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[7]);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleNewsSetSticky(this, newsId, sticky);
}

void WorldSession::HandleGuildSetGuildMaster(WorldPacket& recvPacket)
{
    uint8 nameLength = recvPacket.ReadBits(9);
    std::string playerName = recvPacket.ReadString(nameLength);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetNewGuildMaster(this, playerName);
}

void WorldSession::HandleGuildReplaceGuildMaster(WorldPacket& /*recvPacket*/)
{
    std::string playerName = GetPlayer()->GetName();

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetNewGuildMaster(this, playerName, true);
}

void WorldSession::HandleGuildRequestChallengeUpdate(WorldPacket& recvPacket)
{
    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleRequestChallengeUpdate(this);
}

void WorldSession::HandleGuildBankTabNote(WorldPacket& recvData)
{
    uint32 tabId, noteLength;
    std::string note;

    recvData >> tabId;

    noteLength = recvData.ReadBits(14);
    recvData.FlushBits();

    note = recvData.ReadString(noteLength);

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetBankTabNote(this, tabId, note);
}

void WorldSession::HandleGuildSetAchievementTracking(WorldPacket& recvPacket)
{
    uint32 count = recvPacket.ReadBits(22);
    std::set<uint32> achievementIds;

    for (uint32 i = 0; i < count; ++i)
    {
        uint32 achievementId;
        recvPacket >> achievementId;
        achievementIds.insert(achievementId);
    }

    if (Guild* guild = GetPlayer()->GetGuild())
        guild->HandleSetAchievementTracking(this, achievementIds);
}

void WorldSession::HandleQueryGuildRecipes(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    recvPacket.ReadGuidMask(guid, 7, 4, 0, 3, 2, 5, 6, 1);
    recvPacket.ReadGuidBytes(guid, 1, 0, 6, 5, 2, 4, 7, 3);

    Guild* guild = sGuildMgr->GetGuildByGuid(guid);
    if (!guild)
        return;

    if (GetPlayer()->GetGuildId() != guild->GetId())
        return;

    guild->HandleQueryGuildRecipes(this);
}

void WorldSession::HandleQueryGuildMembersForRecipe(WorldPacket& recvPacket)
{
    uint32 spellId, skillValue, skillId;
    recvPacket >> spellId >> skillValue >> skillId;

    ObjectGuid guid;
    recvPacket.ReadGuidMask(guid, 6, 7, 3, 2, 5, 1, 0, 4);
    recvPacket.ReadGuidBytes(guid, 0, 3, 2, 5, 6, 7, 4, 1);

    Guild* guild = sGuildMgr->GetGuildByGuid(guid);
    if (!guild)
        return;

    if (GetPlayer()->GetGuildId() != guild->GetId())
        return;

    guild->HandleQueryGuildMembersForRecipe(this, spellId, skillId, skillValue);
}

void WorldSession::HandleQueryGuildMemberRecipes(WorldPacket& recvPacket)
{
    ObjectGuid guildGuid, memberGuid;

    uint32 skillId = recvPacket.read<uint32>();
    recvPacket.ReadGuidMask(guildGuid, 6, 7);
    recvPacket.ReadGuidMask(memberGuid, 3);
    recvPacket.ReadGuidMask(guildGuid, 1, 2, 4);
    recvPacket.ReadGuidMask(memberGuid, 4, 1);
    recvPacket.ReadGuidMask(guildGuid, 0, 3);
    recvPacket.ReadGuidMask(memberGuid, 5);
    recvPacket.ReadGuidMask(guildGuid, 5);
    recvPacket.ReadGuidMask(memberGuid, 0, 7, 6, 2);

    recvPacket.ReadGuidBytes(guildGuid, 6);
    recvPacket.ReadGuidBytes(memberGuid, 5, 4, 3, 2);
    recvPacket.ReadGuidBytes(guildGuid, 7);
    recvPacket.ReadGuidBytes(memberGuid, 6);
    recvPacket.ReadGuidBytes(guildGuid, 2);
    recvPacket.ReadGuidBytes(memberGuid, 0, 7);
    recvPacket.ReadGuidBytes(guildGuid, 1, 0, 5);
    recvPacket.ReadGuidBytes(memberGuid, 1);
    recvPacket.ReadGuidBytes(guildGuid, 4, 3);

    Guild* guild = sGuildMgr->GetGuildByGuid(guildGuid);
    if (!guild)
        return;

    if (GetPlayer()->GetGuildId() != guild->GetId())
        return;

    if (!guild->IsMember(memberGuid))
        return;

    guild->HandleQueryGuildMemberRecipes(this, memberGuid, skillId);
}
