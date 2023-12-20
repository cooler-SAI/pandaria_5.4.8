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
#include "TicketMgr.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Language.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Chat.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"

inline float GetAge(uint64 t) { return float(time(NULL) - t) / DAY; }

TicketMgr::TicketMgr() : _feedbackSystemStatus(false), _gmTicketSystemStatus(false),
_lastGmTicketId(0), _lastBugId(0), _lastChange(0), _openGmTicketCount(0), _openBugTicketCount(0) { }

TicketMgr::~TicketMgr()
{
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        delete itr->second;

    for (BugTicketList::const_iterator itr = _bugTicketList.begin(); itr != _bugTicketList.end(); ++itr)
        delete itr->second;
}

TicketMgr* TicketMgr::instance()
{
    static TicketMgr instance;
    return &instance;
}

void TicketMgr::Initialize()
{
    SetFeedBackSystemStatus(sWorld->getBoolConfig(CONFIG_TICKETS_FEEDBACK_SYSTEM_ENABLED));
    SetGmTicketSystemStatus(sWorld->getBoolConfig(CONFIG_TICKETS_GM_ENABLED));
}

void TicketMgr::LoadGmTickets()
{
    uint32 oldMSTime = getMSTime();

    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        delete itr->second;

    _gmTicketList.clear();

    _lastGmTicketId = 0;
    _openGmTicketCount = 0;

    //PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GM_TICKETS);
    QueryResult result = CharacterDatabase.Query("SELECT ticketId, guid, name, message, createTime, mapId, posX, posY, posZ, lastModifiedTime, closedBy, assignedTo, comment, response, completed, escalated, viewed, haveTicket FROM gm_tickets");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 GM tickets. DB table `gm_ticket` is empty!");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();
        GmTicket* ticket = new GmTicket();
        ticket->LoadFromDB(fields);

        if (!ticket->IsClosed())
            ++_openGmTicketCount;

        uint32 id = ticket->GetTicketId();
        if (_lastGmTicketId < id)
            _lastGmTicketId = id;

        _gmTicketList[id] = ticket;
        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u GM tickets in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void TicketMgr::LoadBugTickets()
{
    uint32 oldMSTime = getMSTime();

    for (BugTicketList::const_iterator itr = _bugTicketList.begin(); itr != _bugTicketList.end(); ++itr)
        delete itr->second;

    _bugTicketList.clear();

    _lastBugId = 0;
    _openBugTicketCount = 0;

    //PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GM_BUGS);
    QueryResult result = CharacterDatabase.Query("SELECT ticketId, playerGuid, bugNote, ticketCreateTime, mapId, posX, posY, posZ, orientation, closedBy, assignedTo, comment FROM ticket_bug");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 ticket bugs. DB table `ticket_bug` is empty!");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();
        BugTicket* bug = new BugTicket();
        bug->LoadFromDB(fields);

        if (!bug->IsClosed())
            ++_openBugTicketCount;

        uint32 id = bug->GetTicketId();
        if (_lastBugId < id)
            _lastBugId = id;

        _bugTicketList[id] = bug;
        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u ticket bugs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void TicketMgr::AddTicket(GmTicket* ticket)
{
    _gmTicketList[ticket->GetTicketId()] = ticket;
    if (!ticket->IsClosed())
        ++_openGmTicketCount;

    CharacterDatabaseTransaction trans = CharacterDatabaseTransaction(nullptr);
    ticket->SaveToDB(trans);
}

void TicketMgr::AddTicket(BugTicket* ticket)
{
    _bugTicketList[ticket->GetTicketId()] = ticket;
    if (!ticket->IsClosed())
        ++_openBugTicketCount;

    CharacterDatabaseTransaction trans = CharacterDatabaseTransaction(nullptr);
    ticket->SaveToDB(trans);
}

template<> uint32 TicketMgr::GetOpenTicketCount<GmTicket>() const
{
    return _openGmTicketCount;
}

template<> uint32 TicketMgr::GetOpenTicketCount<BugTicket>() const
{
    return _openBugTicketCount;
}

template<> GmTicket* TicketMgr::GetTicket<GmTicket>(uint32 ticketId)
{
    GmTicketList::const_iterator itr = _gmTicketList.find(ticketId);
    if (itr != _gmTicketList.end())
        return itr->second;

    return NULL;
}

template<> BugTicket* TicketMgr::GetTicket<BugTicket>(uint32 bugId)
{
    BugTicketList::const_iterator itr = _bugTicketList.find(bugId);
    if (itr != _bugTicketList.end())
        return itr->second;

    return NULL;
}

template<> void TicketMgr::RemoveTicket<GmTicket>(uint32 ticketId)
{
    if (GmTicket* ticket = GetTicket<GmTicket>(ticketId))
    {
        ticket->DeleteFromDB();
        _gmTicketList.erase(ticketId);
        delete ticket;
    }
}

template<> void TicketMgr::RemoveTicket<BugTicket>(uint32 ticketId)
{
    if (BugTicket* ticket = GetTicket<BugTicket>(ticketId))
    {
        ticket->DeleteFromDB();
        _bugTicketList.erase(ticketId);
        delete ticket;
    }
}

template<> void TicketMgr::CloseTicket<GmTicket>(uint32 ticketId, int64 closedBy)
{
    if (GmTicket* ticket = GetTicket<GmTicket>(ticketId))
    {
        CharacterDatabaseTransaction trans = CharacterDatabaseTransaction(nullptr);
        ticket->SetClosedBy(closedBy);
        if (closedBy)
            --_openGmTicketCount;

        ticket->SaveToDB(trans);
    }
}

template<> void TicketMgr::CloseTicket<BugTicket>(uint32 ticketId, int64 closedBy)
{
    if (BugTicket* ticket = GetTicket<BugTicket>(ticketId))
    {
        CharacterDatabaseTransaction trans = CharacterDatabaseTransaction(nullptr);
        ticket->SetClosedBy(closedBy);
        if (closedBy)
            --_openBugTicketCount;

        ticket->SaveToDB(trans);
    }
}

template<> void TicketMgr::ResetTickets<GmTicket>()
{
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        delete itr->second;

    _gmTicketList.clear();

    _lastGmTicketId = 0;

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_ALL_GM_TICKETS);
    CharacterDatabase.Execute(stmt);
}

template<> void TicketMgr::ResetTickets<BugTicket>()
{
    for (BugTicketList::const_iterator itr = _bugTicketList.begin(); itr != _bugTicketList.end(); ++itr)
        delete itr->second;

    _bugTicketList.clear();

    _lastBugId = 0;

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_ALL_GM_BUGS);
    CharacterDatabase.Execute(stmt);
}

template<> void TicketMgr::ShowList<GmTicket>(ChatHandler& handler, bool onlineOnly) const
{
    handler.SendSysMessage(onlineOnly ? LANG_COMMAND_TICKETSHOWONLINELIST : LANG_COMMAND_TICKETSHOWLIST);
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        if (!itr->second->IsClosed() && !itr->second->IsCompleted())
            if (!onlineOnly || itr->second->GetPlayer())
                handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

template<> void TicketMgr::ShowList<GmTicket>(ChatHandler& handler) const
{
    handler.SendSysMessage(LANG_COMMAND_TICKETSHOWLIST);
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        if (!itr->second->IsClosed() && !itr->second->IsCompleted())
            handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

template<> void TicketMgr::ShowList<BugTicket>(ChatHandler& handler) const
{
    handler.SendSysMessage(LANG_COMMAND_TICKETSHOWLIST);
    for (BugTicketList::const_iterator itr = _bugTicketList.begin(); itr != _bugTicketList.end(); ++itr)
        if (!itr->second->IsClosed())
            handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

template<> void TicketMgr::ShowClosedList<GmTicket>(ChatHandler& handler) const
{
    handler.SendSysMessage(LANG_COMMAND_TICKETSHOWCLOSEDLIST);
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        if (itr->second->IsClosed())
            handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

template<> void TicketMgr::ShowClosedList<BugTicket>(ChatHandler& handler) const
{
    handler.SendSysMessage(LANG_COMMAND_TICKETSHOWCLOSEDLIST);
    for (BugTicketList::const_iterator itr = _bugTicketList.begin(); itr != _bugTicketList.end(); ++itr)
        if (itr->second->IsClosed())
            handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

void TicketMgr::ShowGmEscalatedList(ChatHandler& handler) const
{
    handler.SendSysMessage(LANG_COMMAND_TICKETSHOWESCALATEDLIST);
    for (GmTicketList::const_iterator itr = _gmTicketList.begin(); itr != _gmTicketList.end(); ++itr)
        if (!itr->second->IsClosed() && itr->second->GetEscalatedStatus() == TICKET_IN_ESCALATION_QUEUE)
            handler.SendSysMessage(itr->second->FormatMessageString(handler).c_str());
}

/// @ response Packets

void TicketMgr::SendGmTicket(WorldSession* session, GmTicket* ticket) const
{
    uint32 size = ticket ? (3 + 4 + 1 + 1 + 1 + 4 + ticket->GetMessage().size() + 4 + 4 + 4 + 4) : 1 + 4;
    WorldPacket data(SMSG_GM_TICKET_GET_TICKET, size);

    if (ticket)
    {
        GMTicketEscalationStatus escaledstatus = ticket->GetEscalatedStatus();
        bool viewed = ticket->GetViewed() ? GMTICKET_OPENEDBYGM_STATUS_OPENED : GMTICKET_OPENEDBYGM_STATUS_NOT_OPENED;
        float OldestTicketTime = sTicketMgr->GetOldestOpenTicket() ? GetAge(sTicketMgr->GetOldestOpenTicket()->GetLastModifiedTime()) : 0.0f;

        data.WriteBit(1);                                   // Initilize
        data.WriteBits(ticket->GetMessage().size(), 11);
        data.WriteBits(0, 10);                              // waitTimeOverrideMessage size
        data.FlushBits();
        data << uint32(ticket->GetTicketId());
        data << uint8(std::min(escaledstatus, TICKET_IN_ESCALATION_QUEUE));
        data << uint8(viewed);
        data << uint8(1);                                   // Unk
        data << uint32(ticket->GetMapId());
        data.WriteString(ticket->GetMessage());
        data << uint32(0);                                  // Unk
        data << uint32(OldestTicketTime);
        data << uint32(GetAge(sTicketMgr->GetLastChange()));
        data << uint32(GMTICKET_STATUS_HASTEXT);
    }
    else
    {
        data.WriteBit(0);
        data.FlushBits();
        data << uint32(GMTICKET_STATUS_DEFAULT);
    }

    session->SendPacket(&data);
}

void TicketMgr::SendGmResponsee(WorldSession* session, GmTicket* ticket) const
{
    if (ticket)
    {
        WorldPacket data(SMSG_GM_TICKET_RESPONSE, 1 + ticket->GetMessage().size() + ticket->GetResponse().size() + 4 + 4);
        data.WriteBit(0);                                       // Has message ???
        data.WriteBit(0);                                       // Has response ???

        data.WriteBits(ticket->GetMessage().size(), 11);
        data.WriteBits(ticket->GetResponse().size(), 14);
        data.FlushBits();

        data.WriteString(ticket->GetMessage());
        data.WriteString(ticket->GetResponse());

        data << uint32(ticket->GetTicketId());
        data << uint32(1);                                      // Response ID

        session->SendPacket(&data);
    }
}

void TicketMgr::SendGmTicketUpdate(Opcodes opcode, GMTicketResponse response, Player* player) const
{
    if (player && player->IsInWorld())
    {
        WorldPacket data(opcode, 4);
        data << uint32(response);
        player->GetSession()-> SendPacket(&data);
    }
}