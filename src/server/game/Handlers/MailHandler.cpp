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

#include "DatabaseEnv.h"
#include "Mail.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Language.h"
#include "DBCStores.h"
#include "Item.h"
#include "AccountMgr.h"
#include "GuildMgr.h"
#include "AuctionHouseMgr.h"
#include "Chat.h"
#include "WordFilterMgr.h"
#include "Realm.h"

void WorldSession::HandleSendMail(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint64 money, COD;
    std::string receiverName, subject, body;
    uint32 bodyLength, subjectLength, receiverLength;
    uint32 unk1, unk2;
    uint8 itemCount;

    recvData >> unk1 >> unk2;                       // both unknown
    recvData >> COD >> money;                       // money and cod

    mailbox[0] = recvData.ReadBit();
    mailbox[6] = recvData.ReadBit();
    mailbox[4] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();
    bodyLength = recvData.ReadBits(11);
    mailbox[3] = recvData.ReadBit();
    receiverLength = recvData.ReadBits(9);
    mailbox[7] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();
    itemCount = recvData.ReadBits(5);               // attached items count

    if (itemCount > MAX_MAIL_ITEMS)                 // client limit
    {
        GetPlayer()->SendMailResult(0, MAIL_SEND, MAIL_ERR_TOO_MANY_ATTACHMENTS);
        recvData.rfinish();                         // set to end to avoid warnings spam
        return;
    }

    ObjectGuid itemGuids[MAX_MAIL_ITEMS];
    for (uint8 i = 0; i < itemCount; ++i)
    {
        itemGuids[i][1] = recvData.ReadBit();
        itemGuids[i][7] = recvData.ReadBit();
        itemGuids[i][2] = recvData.ReadBit();
        itemGuids[i][5] = recvData.ReadBit();
        itemGuids[i][0] = recvData.ReadBit();
        itemGuids[i][6] = recvData.ReadBit();
        itemGuids[i][3] = recvData.ReadBit();
        itemGuids[i][4] = recvData.ReadBit();
    }

    subjectLength = recvData.ReadBits(9);
    mailbox[2] = recvData.ReadBit();

    for (uint8 i = 0; i < itemCount; ++i)
    {
        recvData.read_skip<uint8>();                // item slot in mail, not used
        recvData.ReadByteSeq(itemGuids[i][3]);
        recvData.ReadByteSeq(itemGuids[i][0]);
        recvData.ReadByteSeq(itemGuids[i][2]);
        recvData.ReadByteSeq(itemGuids[i][1]);
        recvData.ReadByteSeq(itemGuids[i][6]);
        recvData.ReadByteSeq(itemGuids[i][5]);
        recvData.ReadByteSeq(itemGuids[i][7]);
        recvData.ReadByteSeq(itemGuids[i][4]);
    }

    recvData.ReadByteSeq(mailbox[1]);
    body = recvData.ReadString(bodyLength);
    recvData.ReadByteSeq(mailbox[0]);
    subject = recvData.ReadString(subjectLength);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[5]);
    recvData.ReadByteSeq(mailbox[7]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[4]);
    receiverName = recvData.ReadString(receiverLength);

    // packet read complete, now do check

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(0, MAIL_SEND, MAIL_ERR_SILENT);
                return;
            }

    if (receiverName.empty())
        return;

    Player* player = _player;

    if (player->GetLevel() < sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ))
    {
        SendNotification(GetTrinityString(LANG_MAIL_SENDER_REQ), sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ));
        return;
    }

    // check msg to bad word
    if (sWorld->getBoolConfig(CONFIG_WORD_FILTER_ENABLE))
    {
        std::string badWord = sWordFilterMgr->FindBadWord(subject, true);

        if (badWord.empty())
            badWord = sWordFilterMgr->FindBadWord(body, true);

        if (!badWord.empty())
        {
            SendNotification(LANG_WORD_FILTER_FOUND_BAD_WORD_IN_MAIL, badWord.c_str());
            // send packet
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_MAIL_ATTACHMENT_INVALID);
            return;
        }
    }

    uint64 receiverGuid = 0;
    if (normalizePlayerName(receiverName))
        receiverGuid = sObjectMgr->GetPlayerGUIDByName(receiverName);

    if (!receiverGuid)
    {
        TC_LOG_INFO("network", "Player %u is sending mail to %s (GUID: not existed!) with subject %s "
            "and body %s includes %u items, " UI64FMTD " copper and " UI64FMTD " COD copper with unk1 = %u, unk2 = %u",
            player->GetGUIDLow(), receiverName.c_str(), subject.c_str(), body.c_str(),
            itemCount, money, COD, unk1, unk2);
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_RECIPIENT_NOT_FOUND);
        return;
    }

    TC_LOG_INFO("network", "Player %u is sending mail to %s (GUID: %u) with subject %s and body %s "
        "includes %u items, " UI64FMTD " copper and " UI64FMTD " COD copper with unk1 = %u, unk2 = %u",
        player->GetGUIDLow(), receiverName.c_str(), GUID_LOPART(receiverGuid), subject.c_str(),
        body.c_str(), itemCount, money, COD, unk1, unk2);

    if (player->GetGUID() == receiverGuid)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_CANNOT_SEND_TO_SELF);
        return;
    }

    uint32 cost = itemCount ? 30 * itemCount : 30;  // price hardcoded in client

    uint64 reqmoney = cost + money;

    if (!player->HasEnoughMoney(reqmoney) && !player->IsGameMaster())
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_NOT_ENOUGH_MONEY);
        return;
    }

    Player* receiver = ObjectAccessor::FindPlayer(receiverGuid);

    uint32 receiverTeam = 0;
    /*
    uint8 mailsCount = 0;                                  //do not allow to send to one player more than 100 mails
    */
    uint8 receiverLevel = 0;
    uint32 receiverAccountId = 0;

    if (receiver)
    {
        receiverTeam = receiver->GetTeam();
        /*
        mailsCount = receiver->GetMailSize();
        */
        receiverLevel = receiver->GetLevel();
        receiverAccountId = receiver->GetSession()->GetAccountId();
    }
    else
    {
        receiverTeam = sObjectMgr->GetPlayerTeamByGUID(receiverGuid);

        /*
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MAIL_COUNT);
        stmt->setUInt32(0, GUID_LOPART(receiverGuid));

        PreparedQueryResult result = CharacterDatabase.Query(stmt);
        if (result)
        {
            Field* fields = result->Fetch();
            mailsCount = fields[0].GetUInt64();
        }
        */

        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_LEVEL);
        stmt->setUInt32(0, GUID_LOPART(receiverGuid));

        PreparedQueryResult result = CharacterDatabase.Query(stmt);
        if (result)
        {
            Field* fields = result->Fetch();
            receiverLevel = fields[0].GetUInt8();
        }

        receiverAccountId = sObjectMgr->GetPlayerAccountIdByGUID(receiverGuid);
    }

    // do not allow to have more than 100 mails in mailbox.. mails count is in opcode uint8!!! - so max can be 255..
    /*
    if (mailsCount > 100)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_RECIPIENT_CAP_REACHED);
        return;
    }
    */

    // test the receiver's Faction... or all items are account bound
    bool accountBound = itemCount ? true : false;
    for (uint8 i = 0; i < itemCount; ++i)
    {
        if (Item* item = player->GetItemByGuid(itemGuids[i]))
        {
            ItemTemplate const* itemProto = item->GetTemplate();
            if (!itemProto || !(itemProto->Flags & ITEM_PROTO_FLAG_BIND_TO_ACCOUNT))
            {
                accountBound = false;
                break;
            }
        }
    }

    if (!accountBound && player->GetTeam() != receiverTeam &&  !sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_MAIL) &&
        GetAccountId() != receiverAccountId && GetSecurity() == SEC_PLAYER)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_NOT_YOUR_TEAM);
        return;
    }

    if (receiverLevel < sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ))
    {
        SendNotification(GetTrinityString(LANG_MAIL_RECEIVER_REQ), sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ));
        return;
    }

    if (!ChatHandler::ValidatePipeSequence(subject) || !ChatHandler::ValidatePipeSequence(body))
        return;

    Item* items[MAX_MAIL_ITEMS];

    for (uint8 i = 0; i < itemCount; ++i)
    {
        if (!itemGuids[i])
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_MAIL_ATTACHMENT_INVALID);
            return;
        }

        Item* item = player->GetItemByGuid(itemGuids[i]);

        // prevent sending bag with items (cheat: can be placed in bag after adding equipped empty bag to mail)
        if (!item)
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_MAIL_ATTACHMENT_INVALID);
            return;
        }

        if (!item->CanBeTraded(true))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_MAIL_BOUND_ITEM);
            return;
        }

        if (item->IsBoundAccountWide() && item->IsSoulBound() && player->GetSession()->GetAccountId() != receiverAccountId)
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_NOT_SAME_ACCOUNT);
            return;
        }

        if (item->GetTemplate()->Flags & ITEM_PROTO_FLAG_CONJURED || item->GetUInt32Value(ITEM_FIELD_EXPIRATION))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_MAIL_BOUND_ITEM);
            return;
        }

        if (COD && item->HasFlag(ITEM_FIELD_DYNAMIC_FLAGS, ITEM_FLAG_WRAPPED))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_CANT_SEND_WRAPPED_COD);
            return;
        }

        if (item->IsNotEmptyBag())
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_DESTROY_NONEMPTY_BAG);
            return;
        }

        items[i] = item;
    }

    player->SendMailResult(0, MAIL_SEND, MAIL_OK);

    player->ModifyMoney(-int64(reqmoney));
    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL, cost);

    bool needItemDelay = false;

    MailDraft draft(subject, body);

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    if (itemCount > 0 || money > 0)
    {
        bool log = GetSecurity() > SEC_PLAYER && sWorld->getBoolConfig(CONFIG_GM_LOG_TRADE);
        if (itemCount > 0)
        {
            for (uint8 i = 0; i < itemCount; ++i)
            {
                Item* item = items[i];
                if (log)
                {
                    sLog->outCommand(GetAccountId(), "GM %s (GUID: %u) (Account: %u) mail item: %s (Entry: %u Count: %u) "
                        "to player: %s (GUID: %u) (Account: %u)", GetPlayerName().c_str(), GetGuidLow(), GetAccountId(),
                        item->GetTemplate()->Name1.c_str(), item->GetEntry(), item->GetCount(),
                        receiverName.c_str(), GUID_LOPART(receiverGuid), receiverAccountId);
                }

                if (uint32 enchantmentId = item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                {
                    item->SetUInt32Value(ITEM_FIELD_ENCHANTMENT + TEMP_ENCHANTMENT_SLOT * MAX_ENCHANTMENT_OFFSET + ENCHANTMENT_ID_OFFSET, 0);
                    item->SetUInt32Value(ITEM_FIELD_ENCHANTMENT + TEMP_ENCHANTMENT_SLOT * MAX_ENCHANTMENT_OFFSET + ENCHANTMENT_DURATION_OFFSET, 0);
                    item->SetUInt32Value(ITEM_FIELD_ENCHANTMENT + TEMP_ENCHANTMENT_SLOT * MAX_ENCHANTMENT_OFFSET + ENCHANTMENT_CHARGES_OFFSET, 0);
                }

                item->SetNotRefundable(GetPlayer()); // makes the item no longer refundable
                player->MoveItemFromInventory(items[i]->GetBagSlot(), item->GetSlot(), true);

                item->DeleteFromInventoryDB(trans);     // deletes item from character's inventory
                item->SetOwnerGUID(receiverGuid);
                item->SaveToDB(trans);                  // recursive and not have transaction guard into self, item not in inventory and can be save standalone
                draft.AddItem(item);
            }

            // if item send to character at another account, then apply item delivery delay
            needItemDelay = player->GetSession()->GetAccountId() != receiverAccountId;
        }

        if (log && money > 0)
        {
            sLog->outCommand(GetAccountId(), "GM %s (GUID: %u) (Account: %u) mail money: " UI64FMTD " to player: %s (GUID: %u) (Account: %u)",
                GetPlayerName().c_str(), GetGuidLow(), GetAccountId(), money, receiverName.c_str(), GUID_LOPART(receiverGuid), receiverAccountId);
        }
    }

    // If theres is an item, there is a one hour delivery delay if sent to another account's character.
    uint32 deliver_delay = needItemDelay ? sWorld->getIntConfig(CONFIG_MAIL_DELIVERY_DELAY) : 0;

    // Mail sent between guild members arrives instantly if they have the guild perk "Guild Mail"
    if (Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId()))
        if (guild->GetLevel() >= 17 && guild->IsMember(receiverGuid))
            deliver_delay = 0;

    // will delete item or place to receiver mail list
    draft
        .AddMoney(money)
        .AddCOD(COD)
        .SendMailTo(trans, MailReceiver(receiver, GUID_LOPART(receiverGuid)), MailSender(player), body.empty() ? MAIL_CHECK_MASK_COPIED : MAIL_CHECK_MASK_HAS_BODY, deliver_delay);

    player->SaveInventoryAndGoldToDB(trans);
    CharacterDatabase.CommitTransaction(trans);
}

//called when mail is read
void WorldSession::HandleMailMarkAsRead(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;

    recvData >> mailId;

    mailbox[0] = recvData.ReadBit();
    mailbox[2] = recvData.ReadBit();
    mailbox[3] = recvData.ReadBit();
    recvData.ReadBit();
    mailbox[4] = recvData.ReadBit();
    mailbox[6] = recvData.ReadBit();
    mailbox[7] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();

    recvData.ReadByteSeq(mailbox[1]);
    recvData.ReadByteSeq(mailbox[7]);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[5]);
    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[4]);
    recvData.ReadByteSeq(mailbox[0]);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
                return;// Mail interactions on client don't get locked up when this action is performed, thus no result packet is needed

    if (Mail* mail = _player->GetMail(mailId))
    {
        if (_player->unReadMails)
            --_player->unReadMails;

        mail->checked |= MAIL_CHECK_MASK_READ;
        mail->state = MAIL_STATE_CHANGED;

        _player->m_mailsUpdated = true;
    }
}

//called when client deletes mail
void WorldSession::HandleMailDelete(WorldPacket& recvData)
{
    uint32 mailId;

    recvData >> mailId;
    recvData.read_skip<uint32>();       // mailTemplateId

    if (Mail* mail = _player->GetMail(mailId))
    {
        // delete shouldn't show up for COD mails
        if (mail->COD)
        {
            _player->SendMailResult(mailId, MAIL_DELETED, MAIL_ERR_INTERNAL_ERROR);
            return;
        }

        mail->state = MAIL_STATE_DELETED;
    }

    _player->m_mailsUpdated = true;
    _player->SendMailResult(mailId, MAIL_DELETED, MAIL_OK);
}

void WorldSession::HandleMailReturnToSender(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;

    recvData >> mailId;

    mailbox[2] = recvData.ReadBit();
    mailbox[0] = recvData.ReadBit();
    mailbox[4] = recvData.ReadBit();
    mailbox[6] = recvData.ReadBit();
    mailbox[3] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();
    mailbox[7] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();

    recvData.ReadByteSeq(mailbox[5]);
    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[0]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[1]);
    recvData.ReadByteSeq(mailbox[4]);
    recvData.ReadByteSeq(mailbox[7]);

    // mailbox isn't mailbox, this is guid of player to return mail, why?
    // TODO: Need to find mailbox near the player
    /*
    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (!IsPremium() || mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_ERR_SILENT);
                return;
            }
    */

    Player* player = _player;
    Mail* m = player->GetMail(mailId);
    if (m->stationery == MAIL_STATIONERY_GM)
    {
        player->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_ERR_RECIPIENT_NOT_FOUND);
        return;
    }

    if (!m || m->state == MAIL_STATE_DELETED || m->deliver_time > time(NULL))
    {
        player->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_ERR_INTERNAL_ERROR);
        return;
    }
    //we can return mail now, so firstly delete the old one
    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_MAIL_BY_ID);
    stmt->setUInt32(0, mailId);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_MAIL_ITEM_BY_ID);
    stmt->setUInt32(0, mailId);
    trans->Append(stmt);

    player->RemoveMail(mailId);

    // only return mail if the player exists (and delete if not existing)
    if (m->messageType == MAIL_NORMAL && m->sender)
    {
        MailDraft draft(m->subject, m->body);
        if (m->mailTemplateId)
            draft = MailDraft(m->mailTemplateId, false);     // items already included

        if (m->HasItems())
        {
            for (MailItemInfoVec::iterator itr2 = m->items.begin(); itr2 != m->items.end(); ++itr2)
            {
                if (Item* const item = player->GetMItem(itr2->item_guid))
                    draft.AddItem(item);
                player->RemoveMItem(itr2->item_guid);
            }
        }
        draft.AddMoney(m->money).SendReturnToSender(GetAccountId(), m->receiver, m->sender, trans);
    }

    CharacterDatabase.CommitTransaction(trans);

    delete m;                                               //we can deallocate old mail
    player->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_OK);
}

//called when player takes item attached in mail
void WorldSession::HandleMailTakeItem(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    uint32 itemId;

    recvData >> mailId;
    recvData >> itemId;

    mailbox[6] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();
    mailbox[2] = recvData.ReadBit();
    mailbox[3] = recvData.ReadBit();
    mailbox[0] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();
    mailbox[4] = recvData.ReadBit();
    mailbox[7] = recvData.ReadBit();

    recvData.ReadByteSeq(mailbox[0]);
    recvData.ReadByteSeq(mailbox[1]);
    recvData.ReadByteSeq(mailbox[4]);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[5]);
    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[7]);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_SILENT);
                return;
            }

    Player* player = _player;

    Mail* m = player->GetMail(mailId);
    if (!m || m->state == MAIL_STATE_DELETED || m->deliver_time > time(NULL))
    {
        player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_INTERNAL_ERROR);
        return;
    }

    // prevent cheating with skip client money check
    if (!player->HasEnoughMoney(uint64(m->COD)))
    {
        player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_NOT_ENOUGH_MONEY);
        return;
    }

    Item* it = player->GetMItem(itemId);

    ItemPosCountVec dest;
    uint8 msg = _player->CanStoreItem(NULL_BAG, NULL_SLOT, dest, it, false);
    if (msg == EQUIP_ERR_OK)
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
        m->RemoveItem(itemId);
        m->removedItems.push_back(itemId);

        if (m->COD > 0)                                     //if there is COD, take COD money from player and send them to sender by mail
        {
            uint64 sender_guid = MAKE_NEW_GUID(m->sender, 0, HIGHGUID_PLAYER);
            Player* receiver = ObjectAccessor::FindPlayer(sender_guid);

            uint32 sender_accId = 0;

            if (GetSecurity() > SEC_PLAYER && sWorld->getBoolConfig(CONFIG_GM_LOG_TRADE))
            {
                std::string sender_name;
                if (receiver)
                {
                    sender_accId = receiver->GetSession()->GetAccountId();
                    sender_name = receiver->GetName();
                }
                else
                {
                    // can be calculated early
                    sender_accId = sObjectMgr->GetPlayerAccountIdByGUID(sender_guid);

                    if (!sObjectMgr->GetPlayerNameByGUID(sender_guid, sender_name))
                        sender_name = sObjectMgr->GetTrinityStringForDBCLocale(LANG_UNKNOWN);
                }
                sLog->outCommand(GetAccountId(), "GM %s (Account: %u) receiver mail item: %s (Entry: %u Count: %u) and send COD money: " UI64FMTD " to player: %s (Account: %u)",
                    GetPlayerName().c_str(), GetAccountId(), it->GetTemplate()->Name1.c_str(), it->GetEntry(), it->GetCount(), m->COD, sender_name.c_str(), sender_accId);
            }
            else if (!receiver)
                sender_accId = sObjectMgr->GetPlayerAccountIdByGUID(sender_guid);

            // check player existence
            if (receiver || sender_accId)
            {
                MailDraft(m->subject, "")
                    .AddMoney(m->COD)
                    .SendMailTo(trans, MailReceiver(receiver, m->sender), MailSender(MAIL_NORMAL, m->receiver), MAIL_CHECK_MASK_COD_PAYMENT);
            }

            player->ModifyMoney(-int32(m->COD));
        }
        m->COD = 0;
        m->state = MAIL_STATE_CHANGED;
        player->m_mailsUpdated = true;
        player->RemoveMItem(it->GetGUIDLow());

        uint32 count = it->GetCount();                      // save counts before store and possible merge with deleting
        it->SetState(ITEM_UNCHANGED);                       // need to set this state, otherwise item cannot be removed later, if neccessary

        player->MoveItemToInventory(dest, it, true);

        player->SaveInventoryAndGoldToDB(trans);
        player->_SaveMail(trans);
        CharacterDatabase.CommitTransaction(trans);

        player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_OK, 0, itemId, count);
    }
    else
        player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_EQUIP_ERROR, msg);
}

void WorldSession::HandleMailTakeMoney(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint64 money;
    uint32 mailId;

    recvData >> mailId;
    recvData >> money;

    mailbox[7] = recvData.ReadBit();
    mailbox[6] = recvData.ReadBit();
    mailbox[3] = recvData.ReadBit();
    mailbox[2] = recvData.ReadBit();
    mailbox[4] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();
    mailbox[0] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();

    recvData.ReadByteSeq(mailbox[7]);
    recvData.ReadByteSeq(mailbox[1]);
    recvData.ReadByteSeq(mailbox[4]);
    recvData.ReadByteSeq(mailbox[0]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[5]);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(mailId, MAIL_MONEY_TAKEN, MAIL_ERR_SILENT);
                return;
            }

    Player* player = _player;

    Mail* m = player->GetMail(mailId);
    if ((!m || m->state == MAIL_STATE_DELETED || m->deliver_time > time(NULL)) ||
        (money > 0 && m->money != money))
    {
        player->SendMailResult(mailId, MAIL_MONEY_TAKEN, MAIL_ERR_INTERNAL_ERROR);
        return;
    }

    if (!player->ModifyMoney(m->money, false))
    {
        player->SendMailResult(mailId, MAIL_MONEY_TAKEN, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_TOO_MUCH_GOLD);
        return;
    }

    if (m->stationery == MAIL_STATIONERY_AUCTION)
    {
        Tokenizer tok(m->subject, ':');
        std::ostringstream attachments;
        if (tok.size() == 5)
        {
            attachments << tok[0] << ":" << tok[4];
        }

        uint32 guid = 0;
        Tokenizer tok2(m->body, ':');
        if (tok.size() == 5)
        {
            uint32 subjID = atol(tok[2]);
            switch (subjID)
            {
                case AUCTION_SUCCESSFUL:    // Money from another player.
                    if (tok2.size() == 5)
                        guid = strtoul(tok2[0], NULL, 16);
                    else
                        attachments << " Unexpected mail body \"" << m->body << '\"';
                    break;
                case AUCTION_OUTBIDDED:     // Returned money. Owner not changed.
                    guid = _player->GetGUIDLow();
                    break;
                default:
                    attachments << " Unexpected mail header " << subjID;
                    break;
            }
        }
    }


    m->money = 0;
    m->state = MAIL_STATE_CHANGED;
    player->m_mailsUpdated = true;

    player->SendMailResult(mailId, MAIL_MONEY_TAKEN, MAIL_OK);

    // save money and mail to prevent cheating
    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
    player->SaveGoldToDB(trans);
    player->_SaveMail(trans);
    CharacterDatabase.CommitTransaction(trans);
}

//called when player lists his received mails
void WorldSession::HandleGetMailList(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    recvData.ReadGuidMask(mailbox, 6, 3, 7, 5, 4, 1, 2, 0);
    recvData.ReadGuidBytes(mailbox, 7, 1, 6, 5, 4, 2, 3, 0);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(0, MAIL_MADE_PERMANENT, MAIL_ERR_SILENT); // Incorrect mailAction, but we need to feed something to the client for it to unlock mail interactions
                return;
            }

    Player* player = _player;

    //load players mails, and mailed items
    if (!player->m_mailsLoaded)
        player->_LoadMail();

    // client can't work with packets > max int16 value
    const uint32 maxPacketSize = 32767;

    uint32 mailCount = 0;
    uint32 realCount = 0;                               // true mail count (includes any skipped mail)
    time_t cur_time = time(NULL);
    ByteBuffer mailData;

    WorldPacket data(SMSG_MAIL_LIST_RESULT, 200);       // guess size
    data << uint32(0);                                  // placeholder

    size_t mailCountPos = data.bitwpos();
    data.WriteBits(0, 18);                              // placeholder

    for (PlayerMails::iterator itr = player->GetMailBegin(); itr != player->GetMailEnd(); ++itr)
    {
        Mail* mail = *itr;

        // Only first 50 mails are displayed
        if (mailCount >= 50)
        {
            realCount += 1;
            continue;
        }

        // skip deleted or not delivered (deliver delay not expired) mails
        if (mail->state == MAIL_STATE_DELETED || cur_time < mail->deliver_time)
            continue;

        // skip mail with more than MAX_MAIL_ITEMS items (should not occur)
        uint8 itemCount = mail->items.size();
        if (itemCount > MAX_MAIL_ITEMS)
        {
            realCount += 1;
            continue;
        }

        // skip mail if the packet has become too large (should not occur)
        size_t nextMailSize = 6 + 1 + 8 + itemCount * (4 + 4 + 4 + 4 + 4 + MAX_INSPECTED_ENCHANTMENT_SLOT * (4 + 4 + 4) +
            4 + 4 + 4 + 4 + 1 + 4) + mail->body.size() + mail->subject.size() + 4 + 4 + 8 + 4 + 8 + 4 + 4 + 1 + 4;

        if (data.wpos() + nextMailSize > maxPacketSize)
        {
            realCount += 1;
            continue;
        }

        data.WriteBit(mail->messageType != MAIL_NORMAL ? 1 : 0);
        data.WriteBits(mail->subject.size(), 8);
        data.WriteBits(mail->body.size(), 13);
        data.WriteBit(0);
        data.WriteBit(0);

        size_t itemCountPos = data.bitwpos();
        data.WriteBits(0, 17);                          // placeholder

        data.WriteBit(1);                               // has guid

        ObjectGuid guid = mail->messageType == MAIL_NORMAL ? MAKE_NEW_GUID(mail->sender, 0, HIGHGUID_PLAYER) : 0;
        data.WriteGuidMask(guid, 2, 6, 7, 0, 5, 3, 1, 4);

        uint8 trueItemCount = 0;
        for (uint8 i = 0; i < itemCount; i++)
        {
            Item* item = player->GetMItem(mail->items[i].item_guid);
            if (!item)
                continue;

            data.WriteBit(!item->IsLocked()); // unlocked flag

            mailData << uint32(item->GetGUIDLow());

            item->BuildItemDynamicModifiersData(&mailData);

            mailData << uint32(item->GetUInt32Value(ITEM_FIELD_DURABILITY));
            mailData << uint32(item->GetItemSuffixFactor());

            for (uint8 j = 0; j < MAX_INSPECTED_ENCHANTMENT_SLOT; j++)
            {
                mailData << uint32(item->GetEnchantmentCharges((EnchantmentSlot)j));
                mailData << uint32(item->GetEnchantmentDuration((EnchantmentSlot)j));
                mailData << uint32(item->GetEnchantmentId((EnchantmentSlot)j));
            }

            mailData << int32(item->GetItemRandomPropertyId());
            mailData << int32(item->GetSpellCharges());
            mailData << uint32(item->GetUInt32Value(ITEM_FIELD_MAX_DURABILITY));
            mailData << uint32(item->GetCount());
            mailData << uint8(i);
            mailData << uint32(item->GetEntry());

            trueItemCount++;
        }

        data.PutBits(itemCountPos, trueItemCount, 17);

        mailData.WriteString(mail->body);
        mailData << uint32(mail->messageID);
        mailData.WriteGuidBytes(guid, 4, 0, 5, 3, 1, 7, 2, 6);
        mailData << uint32(mail->mailTemplateId);
        mailData << uint64(mail->COD);
        mailData.WriteString(mail->subject);
        mailData << uint32(mail->stationery);
        mailData << float(float(mail->expire_time - time(NULL)) / DAY);
        mailData << uint64(mail->money);
        mailData << uint32(mail->checked);

        if (mail->messageType != MAIL_NORMAL)
            mailData << uint32(mail->sender);

        mailData << uint8(mail->messageType);
        mailData << uint32(0);                          // unknown

        realCount++;
        mailCount++;
    }

    data.FlushBits();
    data.append(mailData);

    data.put<uint32>(0, realCount);
    data.PutBits(mailCountPos, mailCount, 18);

    SendPacket(&data);

    // recalculate m_nextMailDelivereTime and unReadMails
    _player->UpdateNextMailTimeAndUnreads();

}

//used when player copies mail body to his inventory
void WorldSession::HandleMailCreateTextItem(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;

    recvData >> mailId;

    mailbox[4] = recvData.ReadBit();
    mailbox[1] = recvData.ReadBit();
    mailbox[6] = recvData.ReadBit();
    mailbox[2] = recvData.ReadBit();
    mailbox[5] = recvData.ReadBit();
    mailbox[3] = recvData.ReadBit();
    mailbox[0] = recvData.ReadBit();
    mailbox[7] = recvData.ReadBit();

    recvData.ReadByteSeq(mailbox[6]);
    recvData.ReadByteSeq(mailbox[5]);
    recvData.ReadByteSeq(mailbox[4]);
    recvData.ReadByteSeq(mailbox[3]);
    recvData.ReadByteSeq(mailbox[0]);
    recvData.ReadByteSeq(mailbox[7]);
    recvData.ReadByteSeq(mailbox[2]);
    recvData.ReadByteSeq(mailbox[1]);

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(mailbox, GAMEOBJECT_TYPE_MAILBOX))
        if (!GetPlayer()->GetNPCIfCanInteractWith(mailbox, UNIT_NPC_FLAG_MAILBOX))
            if (mailbox != GetPlayer()->GetGUID())  // for premium mail command
            {
                GetPlayer()->SendMailResult(mailId, MAIL_MADE_PERMANENT, MAIL_ERR_SILENT);
                return;
            }

    Player* player = _player;

    Mail* m = player->GetMail(mailId);
    if (!m || (m->body.empty() && !m->mailTemplateId) || m->state == MAIL_STATE_DELETED || m->deliver_time > time(NULL))
    {
        player->SendMailResult(mailId, MAIL_MADE_PERMANENT, MAIL_ERR_INTERNAL_ERROR);
        return;
    }

    Item* bodyItem = new Item;                              // This is not bag and then can be used new Item.
    if (!bodyItem->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_ITEM), MAIL_BODY_ITEM_TEMPLATE, player))
    {
        delete bodyItem;
        return;
    }

    // in mail template case we need create new item text
    if (m->mailTemplateId)
    {
        MailTemplateEntry const* mailTemplateEntry = sMailTemplateStore.LookupEntry(m->mailTemplateId);
        if (!mailTemplateEntry)
        {
            player->SendMailResult(mailId, MAIL_MADE_PERMANENT, MAIL_ERR_INTERNAL_ERROR);
            return;
        }

        bodyItem->SetText(mailTemplateEntry->content[GetSessionDbcLocale()]);
    }
    else
        bodyItem->SetText(m->body);

    bodyItem->SetUInt32Value(ITEM_FIELD_CREATOR, m->sender);
    bodyItem->SetFlag(ITEM_FIELD_DYNAMIC_FLAGS, ITEM_FLAG_MAIL_TEXT_MASK);

    TC_LOG_INFO("network", "HandleMailCreateTextItem mailid=%u", mailId);

    ItemPosCountVec dest;
    uint8 msg = _player->CanStoreItem(NULL_BAG, NULL_SLOT, dest, bodyItem, false);
    if (msg == EQUIP_ERR_OK)
    {
        m->checked = m->checked | MAIL_CHECK_MASK_COPIED;
        m->state = MAIL_STATE_CHANGED;
        player->m_mailsUpdated = true;

        player->StoreItem(dest, bodyItem, true);
        player->SendMailResult(mailId, MAIL_MADE_PERMANENT, MAIL_OK);
    }
    else
    {
        player->SendMailResult(mailId, MAIL_MADE_PERMANENT, MAIL_ERR_EQUIP_ERROR, msg);
        delete bodyItem;
    }
}

/// @todo Fix me! ... this void has probably bad condition, but good data are sent
void WorldSession::HandleQueryNextMailTime(WorldPacket& /*recvData*/)
{
    WorldPacket data(SMSG_MAIL_QUERY_NEXT_TIME_RESULT);

    if (!_player->m_mailsLoaded)
        _player->_LoadMail();

    if (_player->unReadMails > 0)
    {
        ByteBuffer dataBuffer; 
        uint8 count = 0;
        time_t now = time(NULL);
        bool hasVirtualRealmAddress = false, hasNativeRealmAddress = false;

        size_t pos = data.bitwpos();
        data.WriteBits(count, 20);

        for (PlayerMails::iterator itr = _player->GetMailBegin(); itr != _player->GetMailEnd(); ++itr)
        {
            Mail* m = (*itr);
            // must be not checked yet
            if (m->checked & MAIL_CHECK_MASK_READ)
                continue;

            // and already delivered
            if (now < m->deliver_time)
                continue;

            ObjectGuid senderGuid = (m->messageType == MAIL_NORMAL) ? MAKE_NEW_GUID(m->sender, 0, HIGHGUID_PLAYER) : 0;

            data.WriteBit(senderGuid[3]);
            data.WriteBit(hasVirtualRealmAddress);
            data.WriteBit(senderGuid[2]);
            data.WriteBit(hasNativeRealmAddress);
            data.WriteBit(senderGuid[6]);
            data.WriteBit(senderGuid[1]);
            data.WriteBit(senderGuid[4]);
            data.WriteBit(senderGuid[0]);
            data.WriteBit(senderGuid[5]);
            data.WriteBit(senderGuid[7]);

            dataBuffer << uint32(m->messageType != MAIL_NORMAL ? m->sender : 0);  // non-player entries
            dataBuffer.WriteByteSeq(senderGuid[5]);
            dataBuffer.WriteByteSeq(senderGuid[4]);
            dataBuffer.WriteByteSeq(senderGuid[6]);
            dataBuffer.WriteByteSeq(senderGuid[1]);
            dataBuffer << uint8(m->messageType);
            dataBuffer.WriteByteSeq(senderGuid[0]);
            dataBuffer << float(m->deliver_time - now);
            if (hasNativeRealmAddress)
                dataBuffer << uint32(realm.Id.Realm);
            dataBuffer << uint32(m->stationery);
            dataBuffer.WriteByteSeq(senderGuid[3]);
            dataBuffer.WriteByteSeq(senderGuid[2]);
            if (hasVirtualRealmAddress)
                dataBuffer << uint32(realm.Id.Realm);
            dataBuffer.WriteByteSeq(senderGuid[7]);

            count++;
            if (count == 3)                                  // do not display more than 3 mails
                break;
        }

        data.FlushBits();
        data.PutBits(pos, count, 20);
        data.append(dataBuffer);

        data << float(0);
    }
    else
    {
        data.WriteBits(0, 20);
        data.FlushBits();
        data << float(-1);
    }

    SendPacket(&data);
}
