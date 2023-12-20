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
#include "DBCStores.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "SpellMgr.h"
#include "Log.h"
#include "Opcodes.h"
#include "Spell.h"
#include "Totem.h"
#include "TemporarySummon.h"
#include "SpellAuras.h"
#include "CreatureAI.h"
#include "ScriptMgr.h"
#include "GameObjectAI.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "DBCStores.h"
#include "InstanceScript.h"
#include "Battleground.h"

void WorldSession::HandleUseItemOpcode(WorldPacket& recvPacket)
{
    /// @todo add targets.read() check
    Player* pUser = _player;
    Unit* mover = _player->m_mover;

    // ignore for remote control state
    if (mover != pUser)
        return;

    GetPlayer()->ResetEmoteStateIfNeed();

    uint8 bagIndex, slot;
    uint8 castCount = 0;
    uint8 castFlags = 0;
    uint32 spellId = 0;
    uint32 glyphIndex = 0;
    uint32 targetMask = 0;
    uint32 targetStringLength = 0;
    float elevation = 0.0f;
    float missileSpeed = 0.0f;
    ObjectGuid itemGuid = 0;
    ObjectGuid targetGuid = 0;
    ObjectGuid itemTargetGuid = 0;
    ObjectGuid destTransportGuid = 0;
    ObjectGuid srcTransportGuid = 0;
    Position srcPos;
    Position destPos;
    std::string targetString;

    // Movement data
    MovementInfo movementInfo;
    ObjectGuid movementTransportGuid = 0;
    ObjectGuid movementGuid = 0;
    bool hasTransport = false;
    bool hasTransportTime2 = false;
    bool hasTransportTime3 = false;
    bool hasFallData = false;
    bool hasFallDirection = false;
    bool hasTimestamp = false;
    bool hasSplineElevation = false;
    bool hasPitch = false;
    bool hasOrientation = false;
    bool hasUnkMovementField = false;
    uint32 unkMovementLoopCounter = 0;
    Unit* caster = mover;

    recvPacket >> slot >> bagIndex;

    bool hasElevation = !recvPacket.ReadBit();
    itemGuid[6] = recvPacket.ReadBit();
    bool hasTargetString = !recvPacket.ReadBit();
    itemGuid[1] = recvPacket.ReadBit();
    bool hasCastFlags = !recvPacket.ReadBit();
    bool hasDestLocation = recvPacket.ReadBit();
    itemGuid[2] = recvPacket.ReadBit();
    itemGuid[7] = recvPacket.ReadBit();
    itemGuid[0] = recvPacket.ReadBit();
    bool hasTargetMask = !recvPacket.ReadBit();
    bool hasMissileSpeed = !recvPacket.ReadBit();
    bool hasMovement = recvPacket.ReadBit();
    bool hasCastCount = !recvPacket.ReadBit();
    bool hasSpellId = !recvPacket.ReadBit();
    recvPacket.ReadBit();
    bool hasGlyphIndex = !recvPacket.ReadBit();
    recvPacket.ReadBit();
    itemGuid[4] = recvPacket.ReadBit();
    bool hasSrcLocation = recvPacket.ReadBit();
    itemGuid[3] = recvPacket.ReadBit();
    itemGuid[5] = recvPacket.ReadBit();
    uint8 researchDataCount = recvPacket.ReadBits(2);

    for (uint8 i = 0; i < researchDataCount; ++i)
        recvPacket.ReadBits(2);

    if (hasMovement)
    {
        hasPitch = !recvPacket.ReadBit();
        hasTransport = recvPacket.ReadBit();
        recvPacket.ReadBit();

        if (hasTransport)
        {
            movementTransportGuid[7] = recvPacket.ReadBit();
            movementTransportGuid[2] = recvPacket.ReadBit();
            movementTransportGuid[4] = recvPacket.ReadBit();
            movementTransportGuid[5] = recvPacket.ReadBit();
            movementTransportGuid[6] = recvPacket.ReadBit();
            movementTransportGuid[0] = recvPacket.ReadBit();
            movementTransportGuid[1] = recvPacket.ReadBit();
            hasTransportTime3 = recvPacket.ReadBit();
            movementTransportGuid[4] = recvPacket.ReadBit();
            hasTransportTime2 = recvPacket.ReadBit();
        }

        movementGuid[6] = recvPacket.ReadBit();
        movementGuid[2] = recvPacket.ReadBit();
        movementGuid[1] = recvPacket.ReadBit();
        unkMovementLoopCounter = recvPacket.ReadBits(22);
        recvPacket.ReadBit();
        bool hasMovementFlags2 = !recvPacket.ReadBit();
        hasFallData = recvPacket.ReadBit();
        movementGuid[5] = recvPacket.ReadBit();
        hasSplineElevation = !recvPacket.ReadBit();
        recvPacket.ReadBit();
        movementGuid[7] = recvPacket.ReadBit();
        movementGuid[0] = recvPacket.ReadBit();

        if (hasFallData)
            hasFallDirection = recvPacket.ReadBit();

        hasOrientation = !recvPacket.ReadBit();
        movementGuid[4] = recvPacket.ReadBit();
        movementGuid[3] = recvPacket.ReadBit();
        hasTimestamp = !recvPacket.ReadBit();
        hasUnkMovementField = !recvPacket.ReadBit();
        bool hasMovementFlags = !recvPacket.ReadBit();

        if (hasMovementFlags2)
            movementInfo.flags2 = recvPacket.ReadBits(13);

        if (hasMovementFlags)
            movementInfo.flags = recvPacket.ReadBits(30);
    }

    if (hasSrcLocation)
    {
        srcTransportGuid[3] = recvPacket.ReadBit();
        srcTransportGuid[1] = recvPacket.ReadBit();
        srcTransportGuid[7] = recvPacket.ReadBit();
        srcTransportGuid[4] = recvPacket.ReadBit();
        srcTransportGuid[2] = recvPacket.ReadBit();
        srcTransportGuid[0] = recvPacket.ReadBit();
        srcTransportGuid[6] = recvPacket.ReadBit();
        srcTransportGuid[5] = recvPacket.ReadBit();
    }

    if (hasDestLocation)
    {
        destTransportGuid[2] = recvPacket.ReadBit();
        destTransportGuid[4] = recvPacket.ReadBit();
        destTransportGuid[1] = recvPacket.ReadBit();
        destTransportGuid[7] = recvPacket.ReadBit();
        destTransportGuid[6] = recvPacket.ReadBit();
        destTransportGuid[0] = recvPacket.ReadBit();
        destTransportGuid[3] = recvPacket.ReadBit();
        destTransportGuid[5] = recvPacket.ReadBit();
    }

    if (hasTargetString)
        targetStringLength = recvPacket.ReadBits(7);

    targetGuid[1] = recvPacket.ReadBit();
    targetGuid[0] = recvPacket.ReadBit();
    targetGuid[5] = recvPacket.ReadBit();
    targetGuid[3] = recvPacket.ReadBit();
    targetGuid[6] = recvPacket.ReadBit();
    targetGuid[4] = recvPacket.ReadBit();
    targetGuid[7] = recvPacket.ReadBit();
    targetGuid[2] = recvPacket.ReadBit();

    itemTargetGuid[4] = recvPacket.ReadBit();
    itemTargetGuid[5] = recvPacket.ReadBit();
    itemTargetGuid[0] = recvPacket.ReadBit();
    itemTargetGuid[1] = recvPacket.ReadBit();
    itemTargetGuid[3] = recvPacket.ReadBit();
    itemTargetGuid[7] = recvPacket.ReadBit();
    itemTargetGuid[6] = recvPacket.ReadBit();
    itemTargetGuid[2] = recvPacket.ReadBit();

    if (hasCastFlags)
        castFlags = recvPacket.ReadBits(5);

    if (hasTargetMask)
        targetMask = recvPacket.ReadBits(20);

    recvPacket.ReadByteSeq(itemGuid[0]);
    recvPacket.ReadByteSeq(itemGuid[5]);
    recvPacket.ReadByteSeq(itemGuid[6]);
    recvPacket.ReadByteSeq(itemGuid[3]);
    recvPacket.ReadByteSeq(itemGuid[4]);
    recvPacket.ReadByteSeq(itemGuid[2]);
    recvPacket.ReadByteSeq(itemGuid[1]);

    for (uint8 i = 0; i < researchDataCount; ++i)
    {
        recvPacket.read_skip<uint32>();
        recvPacket.read_skip<uint32>();
    }

    recvPacket.ReadByteSeq(itemGuid[7]);

    if (hasMovement)
    {
        for (uint8 i = 0; i != unkMovementLoopCounter; i++)
            recvPacket.read_skip<uint32>();

        if (hasTransport)
        {
            recvPacket >> movementInfo.transport.pos.m_positionY;
            recvPacket >> movementInfo.transport.pos.m_positionZ;
            recvPacket.ReadByteSeq(movementTransportGuid[1]);

            if (hasTransportTime3)
                recvPacket >> movementInfo.transport.time3;

            recvPacket.ReadByteSeq(movementTransportGuid[7]);
            recvPacket.ReadByteSeq(movementTransportGuid[5]);
            recvPacket.ReadByteSeq(movementTransportGuid[2]);
            recvPacket.ReadByteSeq(movementTransportGuid[4]);
            recvPacket >> movementInfo.transport.pos.m_positionX;
            movementInfo.transport.pos.SetOrientation(recvPacket.read<float>());
            recvPacket.ReadByteSeq(movementTransportGuid[0]);
            recvPacket >> movementInfo.transport.seat;
            recvPacket >> movementInfo.transport.time;
            recvPacket.ReadByteSeq(movementTransportGuid[6]);
            recvPacket.ReadByteSeq(movementTransportGuid[3]);

            if (hasTransportTime2)
                recvPacket >> movementInfo.transport.time2;
        }

        if (hasFallData)
        {
            recvPacket >> movementInfo.jump.zspeed;

            if (hasFallDirection)
            {
                recvPacket >> movementInfo.jump.sinAngle;
                recvPacket >> movementInfo.jump.cosAngle;
                recvPacket >> movementInfo.jump.xyspeed;
            }

            recvPacket >> movementInfo.jump.fallTime;
        }

        recvPacket.ReadByteSeq(movementGuid[3]);
        recvPacket.ReadByteSeq(movementGuid[7]);
        recvPacket.ReadByteSeq(movementGuid[6]);
        recvPacket.ReadByteSeq(movementGuid[1]);
        recvPacket >> movementInfo.pos.m_positionY;

        if (hasSplineElevation)
            recvPacket >> movementInfo.splineElevation;

        if (hasUnkMovementField)
            recvPacket.read_skip<uint32>();

        if (hasOrientation)
            movementInfo.pos.SetOrientation(recvPacket.read<float>());

        recvPacket.ReadByteSeq(movementGuid[2]);
        recvPacket >> movementInfo.pos.m_positionZ;

        if (hasTimestamp)
            recvPacket >> movementInfo.time;

        recvPacket >> movementInfo.pos.m_positionX;
        recvPacket.ReadByteSeq(movementGuid[5]);
        recvPacket.ReadByteSeq(movementGuid[0]);

        if (hasPitch)
            movementInfo.pitch = G3D::wrap(recvPacket.read<float>(), float(-M_PI), float(M_PI));

        recvPacket.ReadByteSeq(movementGuid[4]);
    }

    if (hasDestLocation)
    {
        float x, y, z;

        recvPacket.ReadByteSeq(destTransportGuid[7]);
        recvPacket >> x;
        recvPacket.ReadByteSeq(destTransportGuid[0]);
        recvPacket.ReadByteSeq(destTransportGuid[6]);
        recvPacket.ReadByteSeq(destTransportGuid[1]);
        recvPacket.ReadByteSeq(destTransportGuid[3]);
        recvPacket >> y;
        recvPacket.ReadByteSeq(destTransportGuid[5]);
        recvPacket >> z;
        recvPacket.ReadByteSeq(destTransportGuid[4]);
        recvPacket.ReadByteSeq(destTransportGuid[2]);

        destPos.Relocate(x, y, z);
    }
    else
    {
        destTransportGuid = caster->GetTransGUID();

        if (destTransportGuid)
            destPos.Relocate(caster->GetTransOffsetX(), caster->GetTransOffsetY(), caster->GetTransOffsetZ(), caster->GetTransOffsetO());
        else
            destPos.Relocate(caster);
    }

    recvPacket.ReadByteSeq(itemTargetGuid[6]);
    recvPacket.ReadByteSeq(itemTargetGuid[7]);
    recvPacket.ReadByteSeq(itemTargetGuid[2]);
    recvPacket.ReadByteSeq(itemTargetGuid[0]);
    recvPacket.ReadByteSeq(itemTargetGuid[3]);
    recvPacket.ReadByteSeq(itemTargetGuid[4]);
    recvPacket.ReadByteSeq(itemTargetGuid[1]);
    recvPacket.ReadByteSeq(itemTargetGuid[5]);

    if (hasSrcLocation)
    {
        float x, y, z;

        recvPacket.ReadByteSeq(srcTransportGuid[7]);
        recvPacket >> x;
        recvPacket.ReadByteSeq(srcTransportGuid[1]);
        recvPacket.ReadByteSeq(srcTransportGuid[5]);
        recvPacket.ReadByteSeq(srcTransportGuid[4]);
        recvPacket >> z;
        recvPacket.ReadByteSeq(srcTransportGuid[6]);
        recvPacket.ReadByteSeq(srcTransportGuid[0]);
        recvPacket.ReadByteSeq(srcTransportGuid[3]);
        recvPacket >> y;
        recvPacket.ReadByteSeq(srcTransportGuid[2]);

        srcPos.Relocate(x, y, z);
    }
    else
    {
        srcTransportGuid = caster->GetTransGUID();
        if (srcTransportGuid)
            srcPos.Relocate(caster->GetTransOffsetX(), caster->GetTransOffsetY(), caster->GetTransOffsetZ(), caster->GetTransOffsetO());
        else
            srcPos.Relocate(caster);
    }

    if (hasSpellId)
        recvPacket >> spellId;

    recvPacket.ReadByteSeq(targetGuid[1]);
    recvPacket.ReadByteSeq(targetGuid[4]);
    recvPacket.ReadByteSeq(targetGuid[3]);
    recvPacket.ReadByteSeq(targetGuid[6]);
    recvPacket.ReadByteSeq(targetGuid[2]);
    recvPacket.ReadByteSeq(targetGuid[0]);
    recvPacket.ReadByteSeq(targetGuid[7]);
    recvPacket.ReadByteSeq(targetGuid[5]);

    if (hasTargetString)
        targetString = recvPacket.ReadString(targetStringLength);

    if (hasElevation)
        recvPacket >> elevation;

    if (hasGlyphIndex)
        recvPacket >> glyphIndex;

    if (hasMissileSpeed)
        recvPacket >> missileSpeed;

    if (hasCastCount)
        recvPacket >> castCount;

    if (glyphIndex >= MAX_GLYPH_SLOT_INDEX)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    Item* pItem = pUser->GetUseableItemByPos(bagIndex, slot);
    if (!pItem)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    if (pItem->GetGUID() != itemGuid)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    TC_LOG_DEBUG("network", "WORLD: CMSG_USE_ITEM packet, bagIndex: %u, slot: %u, castCount: %u, spellId: %u, Item: %u, glyphIndex: %u, data length = %i", bagIndex, slot, castCount, spellId, pItem->GetEntry(), glyphIndex, (uint32)recvPacket.size());

    ItemTemplate const* proto = pItem->GetTemplate();
    if (!proto)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, pItem, NULL);
        return;
    }

    // some item classes can be used only in equipped state
    if (proto->InventoryType != INVTYPE_NON_EQUIP && !pItem->IsEquipped())
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, pItem, NULL);
        return;
    }

    InventoryResult msg = pUser->CanUseItem(pItem);
    if (msg != EQUIP_ERR_OK)
    {
        pUser->SendEquipError(msg, pItem, NULL);
        return;
    }

    Battleground const* bg = pUser->GetBattlegorund();
    bool arenaOrRatedBg = bg && (bg->IsArena() || bg->IsRatedBG());

    // only allow conjured consumable, bandage, poisons (all should have the 2^21 item flag set in DB)
    if (proto->Class == ITEM_CLASS_CONSUMABLE && !(proto->Flags & ITEM_PROTO_FLAG_USEABLE_IN_ARENA) && arenaOrRatedBg)
    {
        pUser->SendEquipError(EQUIP_ERR_NOT_DURING_ARENA_MATCH, pItem, NULL);
        return;
    }

    // don't allow items banned in arena
    if (proto->Flags & ITEM_PROTO_FLAG_NOT_USEABLE_IN_ARENA && arenaOrRatedBg)
    {
        pUser->SendEquipError(EQUIP_ERR_NOT_DURING_ARENA_MATCH, pItem, NULL);
        return;
    }

    if (pUser->IsInCombat())
    {
        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(proto->Spells[i].SpellId))
            {
                if (!spellInfo->CanBeUsedInCombat())
                {
                    pUser->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, pItem, NULL);
                    return;
                }
            }
        }
    }

    // check also  BIND_ON_ACQUIRE and BIND_QUEST for .additem or .additemset case by GM (not binded at adding to inventory)
    if (pItem->GetTemplate()->Bonding == BIND_ON_USE || pItem->GetTemplate()->Bonding == BIND_ON_ACQUIRE || pItem->GetTemplate()->Bonding == BIND_QUEST)
    {
        if (!pItem->IsSoulBound())
        {
            pItem->SetState(ITEM_CHANGED, pUser);
            pItem->SetBinding(true);
        }
    }

    SpellCastTargets targets(caster, targetMask, targetGuid, itemTargetGuid, srcTransportGuid, destTransportGuid, srcPos, destPos, elevation, missileSpeed, targetString);

    // Burden of Eternity, Yeah just for one case
    if (pItem->GetEntry() == 103982)
    {
        WorldPacket data(SMSG_SCRIPT_CAST);
        data << uint32(147678);
        SendPacket(&data);
    }

    // Note: If script stop casting it must send appropriate data to client to prevent stuck item in gray state.
    if (!sScriptMgr->OnItemUse(pUser, pItem, targets))
    {
        // no script or script not process request by self
        pUser->CastItemUseSpell(pItem, targets, castCount, glyphIndex);
    }
}

void WorldSession::HandleOpenItemOpcode(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_OPEN_ITEM packet, data length = %i", (uint32)recvPacket.size());

    Player* pUser = _player;

    // ignore for remote control state
    if (pUser->m_mover != pUser)
        return;

    uint8 bagIndex, slot;

    recvPacket >> bagIndex >> slot;

    TC_LOG_INFO("network", "bagIndex: %u, slot: %u", bagIndex, slot);

    Item* item = pUser->GetItemByPos(bagIndex, slot);
    if (!item)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    ItemTemplate const* proto = item->GetTemplate();
    if (!proto)
    {
        pUser->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, item, NULL);
        return;
    }

    // Verify that the bag is an actual bag or wrapped item that can be used "normally"
    if (!(proto->Flags & ITEM_FLAG_HAS_LOOT) && !item->HasFlag(ITEM_FIELD_DYNAMIC_FLAGS, ITEM_FLAG_WRAPPED))
    {
        pUser->SendEquipError(EQUIP_ERR_CLIENT_LOCKED_OUT, item, NULL);
        TC_LOG_ERROR("network", "Possible hacking attempt: Player %s [guid: %u] tried to open item [guid: %u, entry: %u] which is not openable!",
                pUser->GetName().c_str(), pUser->GetGUIDLow(), item->GetGUIDLow(), proto->ItemId);
        return;
    }

    // locked item
    uint32 lockId = proto->LockID;
    if (lockId)
    {
        LockEntry const* lockInfo = sLockStore.LookupEntry(lockId);

        if (!lockInfo)
        {
            pUser->SendEquipError(EQUIP_ERR_ITEM_LOCKED, item, NULL);
            TC_LOG_ERROR("network", "WORLD::OpenItem: item [guid = %u] has an unknown lockId: %u!", item->GetGUIDLow(), lockId);
            return;
        }

        // was not unlocked yet
        if (item->IsLocked())
        {
            pUser->SendEquipError(EQUIP_ERR_ITEM_LOCKED, item, NULL);
            return;
        }
    }

    if (item->HasFlag(ITEM_FIELD_DYNAMIC_FLAGS, ITEM_FLAG_WRAPPED))// wrapped?
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_GIFT_BY_ITEM);

        stmt->setUInt32(0, item->GetGUIDLow());

        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (result)
        {
            Field* fields = result->Fetch();
            uint32 entry = fields[0].GetUInt32();
            uint32 flags = fields[1].GetUInt32();

            item->SetUInt64Value(ITEM_FIELD_GIFT_CREATOR, 0);
            item->SetEntry(entry);
            item->SetUInt32Value(ITEM_FIELD_DYNAMIC_FLAGS, flags);
            item->SetState(ITEM_CHANGED, pUser);
        }
        else
        {
            TC_LOG_ERROR("network", "Wrapped item %u don't have record in character_gifts table and will deleted", item->GetGUIDLow());
            pUser->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
            return;
        }

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GIFT);

        stmt->setUInt32(0, item->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
    }
    else
        pUser->SendLoot(item->GetGUID(), LOOT_CORPSE);
}

void WorldSession::HandleGameObjectUseOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;

    guid[6] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[7]);

    TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_GAMEOBJ_USE Message [guid=%u]", GUID_LOPART(guid));

    GetPlayer()->ResetEmoteStateIfNeed();

    if (GameObject* obj = GetPlayer()->GetMap()->GetGameObject(guid))
    {
        // ignore for remote control state
        if (_player->m_mover != _player)
            if (!(_player->IsOnVehicle(_player->m_mover) || _player->IsMounted()) && !obj->GetGOInfo()->IsUsableMounted())
                return;

        obj->Use(_player);
    }
}

void WorldSession::HandleGameobjectReportUse(WorldPacket& recvPacket)
{
    ObjectGuid guid;

    guid[4] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[4]);

    TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_GAMEOBJ_REPORT_USE Message [in game guid: %u]", GUID_LOPART(guid));

    // ignore for remote control state
    if (_player->m_mover != _player)
        return;

    GameObject* go = GetPlayer()->GetMap()->GetGameObject(guid);
    if (!go)
        return;

    if (!go->IsAtInteractDistance(_player))
        return;

    // only for backward compatibility
    if (go->AI()->GossipHello(_player))
        return;

    if (go->AI()->OnReportUse(_player))
        return;

    // only for backward compatibility
    if (sScriptMgr->OnGossipHello(_player, go))
        return;

    if (sScriptMgr->OnReportUse(_player, go))
        return;

    _player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT, go->GetEntry());
}

void WorldSession::HandleCastSpellOpcode(WorldPacket& recvPacket)
{
    // ignore for remote control state (for player case)
    Unit* mover = _player->m_mover;
    if (mover != _player && mover->GetTypeId() == TYPEID_PLAYER)
    {
        recvPacket.rfinish(); // prevent spam at ignore packet
        return;
    }

    GetPlayer()->ResetEmoteStateIfNeed();

    uint8 castCount = 0;
    uint8 castFlags = 0;
    uint32 spellId = 0;
    uint32 glyphIndex = 0;
    uint32 targetMask = 0;
    uint32 targetStringLength = 0;
    float elevation = 0.0f;
    float missileSpeed = 0.0f;
    ObjectGuid targetGuid = 0;
    ObjectGuid itemTargetGuid = 0;
    ObjectGuid destTransportGuid = 0;
    ObjectGuid srcTransportGuid = 0;
    Position srcPos;
    Position destPos;
    std::string targetString;

    // Movement data
    MovementInfo movementInfo;
    ObjectGuid movementTransportGuid = 0;
    ObjectGuid movementGuid = 0;
    bool hasTransport = false;
    bool hasTransportTime2 = false;
    bool hasTransportTime3 = false;
    bool hasFallData = false;
    bool hasFallDirection = false;
    bool hasTimestamp = false;
    bool hasSplineElevation = false;
    bool hasPitch = false;
    bool hasOrientation = false;
    bool hasUnkMovementField = false;
    uint32 unkMovementLoopCounter = 0;
    Unit* caster = mover;

    recvPacket.ReadBit(); // Fake bit
    bool hasTargetString = !recvPacket.ReadBit();
    recvPacket.ReadBit(); // Fake Bit
    bool hasCastCount = !recvPacket.ReadBit();
    bool hasSrcLocation = recvPacket.ReadBit();
    bool hasDestLocation = recvPacket.ReadBit();
    bool hasSpellId = !recvPacket.ReadBit();
    uint8 researchDataCount = recvPacket.ReadBits(2);
    bool hasTargetMask = !recvPacket.ReadBit();
    bool hasMissileSpeed = !recvPacket.ReadBit();

    std::vector<SpellResearchInfo> researchInfoVector;
    researchInfoVector.reserve(researchDataCount);
    for (uint8 i = 0; i < researchDataCount; ++i)
        researchInfoVector.emplace_back(uint8(recvPacket.ReadBits(2)), 0, 0);

    bool hasGlyphIndex = !recvPacket.ReadBit();
    bool hasMovement = recvPacket.ReadBit();
    bool hasElevation = !recvPacket.ReadBit();
    bool hasCastFlags = !recvPacket.ReadBit();

    targetGuid[5] = recvPacket.ReadBit();
    targetGuid[4] = recvPacket.ReadBit();
    targetGuid[2] = recvPacket.ReadBit();
    targetGuid[7] = recvPacket.ReadBit();
    targetGuid[1] = recvPacket.ReadBit();
    targetGuid[6] = recvPacket.ReadBit();
    targetGuid[3] = recvPacket.ReadBit();
    targetGuid[0] = recvPacket.ReadBit();

    if (hasDestLocation)
    {
        destTransportGuid[1] = recvPacket.ReadBit();
        destTransportGuid[3] = recvPacket.ReadBit();
        destTransportGuid[5] = recvPacket.ReadBit();
        destTransportGuid[0] = recvPacket.ReadBit();
        destTransportGuid[2] = recvPacket.ReadBit();
        destTransportGuid[6] = recvPacket.ReadBit();
        destTransportGuid[7] = recvPacket.ReadBit();
        destTransportGuid[4] = recvPacket.ReadBit();
    }

    if (hasMovement)
    {
        unkMovementLoopCounter = recvPacket.ReadBits(22);
        recvPacket.ReadBit();
        movementGuid[4] = recvPacket.ReadBit();
        hasTransport = recvPacket.ReadBit();

        if (hasTransport)
        {
            hasTransportTime2 = recvPacket.ReadBit();
            movementTransportGuid[7] = recvPacket.ReadBit();
            movementTransportGuid[4] = recvPacket.ReadBit();
            movementTransportGuid[1] = recvPacket.ReadBit();
            movementTransportGuid[0] = recvPacket.ReadBit();
            movementTransportGuid[6] = recvPacket.ReadBit();
            movementTransportGuid[3] = recvPacket.ReadBit();
            movementTransportGuid[5] = recvPacket.ReadBit();
            hasTransportTime3 = recvPacket.ReadBit();
            movementTransportGuid[2] = recvPacket.ReadBit();
        }

        recvPacket.ReadBit();
        movementGuid[7] = recvPacket.ReadBit();
        hasOrientation = !recvPacket.ReadBit();
        movementGuid[6] = recvPacket.ReadBit();
        hasSplineElevation = !recvPacket.ReadBit();
        hasPitch = !recvPacket.ReadBit();
        movementGuid[0] = recvPacket.ReadBit();
        recvPacket.ReadBit();
        bool hasMovementFlags = !recvPacket.ReadBit();
        hasTimestamp = !recvPacket.ReadBit();
        hasUnkMovementField = !recvPacket.ReadBit();

        if (hasMovementFlags)
            movementInfo.flags = recvPacket.ReadBits(30);

        movementGuid[1] = recvPacket.ReadBit();
        movementGuid[3] = recvPacket.ReadBit();
        movementGuid[2] = recvPacket.ReadBit();
        movementGuid[5] = recvPacket.ReadBit();
        hasFallData = recvPacket.ReadBit();

        if (hasFallData)
            hasFallDirection = recvPacket.ReadBit();

        bool hasMovementFlags2 = !recvPacket.ReadBit();

        if (hasMovementFlags2)
            movementInfo.flags2 = recvPacket.ReadBits(13);
    }

    itemTargetGuid[1] = recvPacket.ReadBit();
    itemTargetGuid[0] = recvPacket.ReadBit();
    itemTargetGuid[7] = recvPacket.ReadBit();
    itemTargetGuid[4] = recvPacket.ReadBit();
    itemTargetGuid[6] = recvPacket.ReadBit();
    itemTargetGuid[5] = recvPacket.ReadBit();
    itemTargetGuid[3] = recvPacket.ReadBit();
    itemTargetGuid[2] = recvPacket.ReadBit();

    if (hasSrcLocation)
    {
        srcTransportGuid[4] = recvPacket.ReadBit();
        srcTransportGuid[5] = recvPacket.ReadBit();
        srcTransportGuid[3] = recvPacket.ReadBit();
        srcTransportGuid[0] = recvPacket.ReadBit();
        srcTransportGuid[7] = recvPacket.ReadBit();
        srcTransportGuid[1] = recvPacket.ReadBit();
        srcTransportGuid[6] = recvPacket.ReadBit();
        srcTransportGuid[2] = recvPacket.ReadBit();
    }

    if (hasTargetMask)
        targetMask = recvPacket.ReadBits(20);

    if (hasCastFlags)
        castFlags = recvPacket.ReadBits(5);

    if (hasTargetString)
        targetStringLength = recvPacket.ReadBits(7);

    for (uint8 i = 0; i < researchDataCount; ++i)
    {
        researchInfoVector[i].count = recvPacket.read<uint32>();
        researchInfoVector[i].itemId = recvPacket.read<uint32>();
    }

    if (hasMovement)
    {
        recvPacket >> movementInfo.pos.m_positionX;
        recvPacket.ReadByteSeq(movementGuid[0]);

        if (hasTransport)
        {
            recvPacket.ReadByteSeq(movementTransportGuid[2]);
            recvPacket >> movementInfo.transport.seat;
            recvPacket.ReadByteSeq(movementTransportGuid[3]);
            recvPacket.ReadByteSeq(movementTransportGuid[7]);
            recvPacket >> movementInfo.transport.pos.m_positionX;
            recvPacket.ReadByteSeq(movementTransportGuid[5]);

            if (hasTransportTime3)
                recvPacket >> movementInfo.transport.time3;

            recvPacket >> movementInfo.transport.pos.m_positionZ;
            recvPacket >> movementInfo.transport.pos.m_positionY;

            recvPacket.ReadByteSeq(movementTransportGuid[6]);
            recvPacket.ReadByteSeq(movementTransportGuid[1]);
            movementInfo.transport.pos.SetOrientation(recvPacket.read<float>());

            recvPacket.ReadByteSeq(movementTransportGuid[4]);

            if (hasTransportTime2)
                recvPacket >> movementInfo.transport.time2;

            recvPacket.ReadByteSeq(movementTransportGuid[0]);
            recvPacket >> movementInfo.transport.time;

        }

        recvPacket.ReadByteSeq(movementGuid[5]);

        if (hasFallData)
        {
            recvPacket >> movementInfo.jump.fallTime;
            recvPacket >> movementInfo.jump.zspeed;

            if (hasFallDirection)
            {
                recvPacket >> movementInfo.jump.sinAngle;
                recvPacket >> movementInfo.jump.xyspeed;
                recvPacket >> movementInfo.jump.cosAngle;
            }
        }

        if (hasSplineElevation)
            recvPacket >> movementInfo.splineElevation;

        recvPacket.ReadByteSeq(movementGuid[6]);

        if (hasUnkMovementField)
            recvPacket.read_skip<uint32>();

        recvPacket.ReadByteSeq(movementGuid[4]);

        if (hasOrientation)
            movementInfo.pos.SetOrientation(recvPacket.read<float>());

        if (hasTimestamp)
            recvPacket >> movementInfo.time;

        recvPacket.ReadByteSeq(movementGuid[1]);

        if (hasPitch)
            movementInfo.pitch = G3D::wrap(recvPacket.read<float>(), float(-M_PI), float(M_PI));

        recvPacket.ReadByteSeq(movementGuid[3]);

        for (uint8 i = 0; i != unkMovementLoopCounter; i++)
            recvPacket.read_skip<uint32>();

        recvPacket >> movementInfo.pos.m_positionY;
        recvPacket.ReadByteSeq(movementGuid[7]);
        recvPacket >> movementInfo.pos.m_positionZ;
        recvPacket.ReadByteSeq(movementGuid[2]);
    }

    recvPacket.ReadByteSeq(itemTargetGuid[4]);
    recvPacket.ReadByteSeq(itemTargetGuid[2]);
    recvPacket.ReadByteSeq(itemTargetGuid[1]);
    recvPacket.ReadByteSeq(itemTargetGuid[5]);
    recvPacket.ReadByteSeq(itemTargetGuid[7]);
    recvPacket.ReadByteSeq(itemTargetGuid[3]);
    recvPacket.ReadByteSeq(itemTargetGuid[6]);
    recvPacket.ReadByteSeq(itemTargetGuid[0]);

    if (hasDestLocation)
    {
        float x, y, z;
        recvPacket.ReadByteSeq(destTransportGuid[2]);
        recvPacket >> x;
        recvPacket.ReadByteSeq(destTransportGuid[4]);
        recvPacket.ReadByteSeq(destTransportGuid[1]);
        recvPacket.ReadByteSeq(destTransportGuid[0]);
        recvPacket.ReadByteSeq(destTransportGuid[3]);
        recvPacket >> y;
        recvPacket.ReadByteSeq(destTransportGuid[7]);
        recvPacket >> z;
        recvPacket.ReadByteSeq(destTransportGuid[5]);
        recvPacket.ReadByteSeq(destTransportGuid[6]);
        destPos.Relocate(x, y, z);
    }
    else
    {
        destTransportGuid = caster->GetTransGUID();
        if (destTransportGuid)
            destPos.Relocate(caster->GetTransOffsetX(), caster->GetTransOffsetY(), caster->GetTransOffsetZ(), caster->GetTransOffsetO());
        else
            destPos.Relocate(caster);
    }

    recvPacket.ReadByteSeq(targetGuid[3]);
    recvPacket.ReadByteSeq(targetGuid[4]);
    recvPacket.ReadByteSeq(targetGuid[7]);
    recvPacket.ReadByteSeq(targetGuid[6]);
    recvPacket.ReadByteSeq(targetGuid[2]);
    recvPacket.ReadByteSeq(targetGuid[0]);
    recvPacket.ReadByteSeq(targetGuid[1]);
    recvPacket.ReadByteSeq(targetGuid[5]);

    if (hasSrcLocation)
    {
        float x, y, z;
        recvPacket >> y;
        recvPacket.ReadByteSeq(srcTransportGuid[5]);
        recvPacket.ReadByteSeq(srcTransportGuid[1]);
        recvPacket.ReadByteSeq(srcTransportGuid[7]);
        recvPacket.ReadByteSeq(srcTransportGuid[6]);
        recvPacket >> x;
        recvPacket.ReadByteSeq(srcTransportGuid[3]);
        recvPacket.ReadByteSeq(srcTransportGuid[2]);
        recvPacket.ReadByteSeq(srcTransportGuid[0]);
        recvPacket.ReadByteSeq(srcTransportGuid[4]);
        recvPacket >> z;
        srcPos.Relocate(x, y, z);
    }
    else
    {
        srcTransportGuid = caster->GetTransGUID();
        if (srcTransportGuid)
            srcPos.Relocate(caster->GetTransOffsetX(), caster->GetTransOffsetY(), caster->GetTransOffsetZ(), caster->GetTransOffsetO());
        else
            srcPos.Relocate(caster);
    }

    if (hasTargetString)
        targetString = recvPacket.ReadString(targetStringLength);

    if (hasMissileSpeed)
        recvPacket >> missileSpeed;

    if (hasElevation)
        recvPacket >> elevation;

    if (hasCastCount)
        recvPacket >> castCount;

    if (hasSpellId)
        recvPacket >> spellId;

    if (hasGlyphIndex)
        recvPacket >> glyphIndex;

    TC_LOG_DEBUG("network", "WORLD: got cast spell packet, castCount: %u, spellId: %u, castFlags: %u, data length = %u", castCount, spellId, castFlags, (uint32)recvPacket.size());

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
    {
        TC_LOG_ERROR("network", "WORLD: unknown spell id %u", spellId);
        recvPacket.rfinish(); // prevent spam at ignore packet
        return;
    }

    if (spellInfo->IsPassive())
    {
        recvPacket.rfinish(); // prevent spam at ignore packet
        return;
    }

    if (caster->GetTypeId() == TYPEID_PLAYER &&  caster->GetMap()->IsDungeon() && caster->GetMap()->IsChallengeDungeon() &&
        caster->GetInstanceScript() && caster->GetInstanceScript()->IsChallengeModeStarted() &&
        (spellInfo->Id == 63645 || spellInfo->Id == 63644 || spellInfo->Targets & TARGET_FLAG_GLYPH_SLOT))
    {
        caster->ToPlayer()->SendGameError(GameError::ERR_NOT_IN_COMBAT);
        recvPacket.rfinish(); // prevent spam at ignore packet
        return;
    }

    if (caster->GetTypeId() == TYPEID_UNIT && !caster->ToCreature()->HasSpell(spellId))
    {
        // If the vehicle creature does not have the spell but it allows the passenger to cast own spells
        // change caster to player and let him cast
        if (!_player->IsOnVehicle(caster) || spellInfo->CheckVehicle(_player) != SPELL_CAST_OK)
        {
            recvPacket.rfinish(); // prevent spam at ignore packet
            return;
        }

        caster = _player;
    }

    // client provided targets
    SpellCastTargets targets(caster, targetMask, targetGuid, itemTargetGuid, srcTransportGuid, destTransportGuid, srcPos, destPos, elevation, missileSpeed, targetString);

    // not have spell in spellbook
    if (caster->GetTypeId() == TYPEID_PLAYER && !caster->ToPlayer()->HasActiveSpell(spellId) && !spellInfo->IsRaidMarker() &&
        spellId != 101603 && // Hack for Throw Totem, Echo of Baine
        spellId != 119393 && // Hack for Siege Explosive, General Pa'valak
        spellId != 123039 && // Hack for Player Throw Barrel, Commander Vo'jak
        !spellInfo->IsAbilityOfSkillType(SKILL_ARCHAEOLOGY))
    {
        // allow casting of unknown spells for special lock cases
        bool allow = false;
        if (GameObject* go = targets.GetGOTarget())
            if (go->GetSpellForLock(caster->ToPlayer()) == spellInfo)
                allow = true;

        for (auto&& it : caster->GetAuraEffectsByType(SPELL_AURA_BONUS_ROLL_TRIGGER))
            if (spellId == it->GetSpellEffectInfo().TriggerSpell)
                allow = true;

        //cheater? kick? ban?
        if (!allow)
            return;
    }

    // Override spell Id, client send base spell and not the overrided id
    for (auto&& overrideId : spellInfo->OverrideSpellList)
    {
        if (_player->HasSpell(overrideId))
        {
            if (SpellInfo const* overrideInfo = sSpellMgr->GetSpellInfo(overrideId))
            {
                spellInfo = overrideInfo;
                spellId = overrideId;
            }
            break;
        }
    }

    Unit::AuraEffectList swaps = mover->GetAuraEffectsByType(SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS);
    Unit::AuraEffectList const& swaps2 = mover->GetAuraEffectsByType(SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS_2);
    if (!swaps2.empty())
        swaps.insert(swaps.end(), swaps2.begin(), swaps2.end());

    for (auto&& itr : swaps)
    {
        if (itr->IsAffectingSpell(spellInfo))
        {
            if (SpellInfo const* newInfo = sSpellMgr->GetSpellInfo(itr->GetAmount()))
            {
                spellInfo = newInfo;
                spellId = newInfo->Id;
                break;
            }
        }
    }

    // Client is resending autoshot cast opcode when other spell is casted during shoot rotation
    // Skip it to prevent "interrupt" message
    if (spellInfo->IsAutoRepeatRangedSpell() && caster->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL)
        && caster->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL)->m_spellInfo == spellInfo)
        return;

    // can't use our own spells when we're in possession of another unit,
    if (_player->isPossessing())
        return;

    // auto-selection buff level base at target level (in spellInfo)
    if (targets.GetUnitTarget())
    {
        SpellInfo const* actualSpellInfo = spellInfo->GetAuraRankForLevel(targets.GetUnitTarget()->GetLevel());

        // if rank not found then function return NULL but in explicit cast case original spell can be casted and later failed with appropriate error message
        if (actualSpellInfo)
            spellInfo = actualSpellInfo;
    }

    Spell* spell = new Spell(caster, spellInfo, TRIGGERED_NONE, 0, false);
    spell->m_cast_count = castCount;                       // set count of casts
    spell->m_glyphIndex = glyphIndex;

    if (castFlags & 0x8) // Archaeology
    {
        SpellResearchData* researchData = new SpellResearchData();
        memset(researchData, 0, sizeof(SpellResearchData*));
        for (auto&& research : researchInfoVector)
        {
            switch (research.type)
            {
                case 1: // Keystones
                    researchData->KeystoneItemId = research.itemId;       // Item id
                    researchData->KeystoneCount = research.count;         // Item count
                    break;
                case 2: // Fragments
                    researchData->FragmentCurrencyId = research.itemId;   // Currency id
                    researchData->FragmentCount = research.count;         // Currency count
                    break;
            }
        }

        spell->m_researchData = researchData;
    }

    spell->prepare(&targets);
}

void WorldSession::HandleCancelCastOpcode(WorldPacket& recvPacket)
{
    uint32 spellId = 0;
    uint8 counter = 0;

    bool hasCounter = !recvPacket.ReadBit();
    bool hasSpellId = !recvPacket.ReadBit();

    if (hasSpellId)
        recvPacket >> spellId;

    if (hasCounter)
        recvPacket >> counter;

    if (_player->IsNonMeleeSpellCasted(false))
        _player->InterruptNonMeleeSpells(false, spellId, false);
}

void WorldSession::HandleCancelAuraOpcode(WorldPacket& recvPacket)
{
    uint32 spellId;
    recvPacket >> spellId;

    ObjectGuid guid;

    recvPacket.ReadBit(); // Fake Bit
    guid[6] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[6]);

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
        return;

    // not allow remove spells with attr SPELL_ATTR0_CANT_CANCEL
    if (spellInfo->Attributes & SPELL_ATTR0_CANT_CANCEL)
        return;

    // channeled spell case (it currently casted then)
    if (spellInfo->IsChanneled())
    {
        if (Spell* curSpell = _player->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
            if (curSpell->m_spellInfo->Id == spellId)
                _player->InterruptSpell(CURRENT_CHANNELED_SPELL);
        return;
    }

    // non channeled case:
    // don't allow remove non positive spells
    // don't allow cancelling passive auras (some of them are visible)
    if (spellInfo->IsPassive())
        return;

    if (!spellInfo->IsPositive())
    {
        Aura* aura = _player->GetAura(spellId);
        if (!aura || (aura->GetEffectMask() & spellInfo->NegativeEffectMask))
            return;
    }

    // maybe should only remove one buff when there are multiple?
    _player->RemoveOwnedAura(spellId, 0, 0, AURA_REMOVE_BY_CANCEL);
}

void WorldSession::HandleCancelModSpeedNoControlAuras(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    recvPacket.ReadGuidMask(guid, 3, 2, 5, 0, 7, 1, 6, 4);
    recvPacket.ReadGuidBytes(guid, 6, 7, 3, 5, 0, 4, 1, 2);

    if (!GetPlayer()->HasAuraType(SPELL_AURA_MOD_SPEED_NO_CONTROL))
    {
        // Already handled.
        m_firstCancelModSpeedNoContorlAurasPacket = TimeValue::zero();
        m_lastCancelModSpeedNoContorlAurasPacket = TimeValue::zero();
        return;
    }

    auto now = TimeValue::Now();

    if (m_firstCancelModSpeedNoContorlAurasPacket == TimeValue::zero())
        m_firstCancelModSpeedNoContorlAurasPacket = now;
    else
    {
        if (now - m_lastCancelModSpeedNoContorlAurasPacket > Milliseconds(300)) // Okay, reset
            m_firstCancelModSpeedNoContorlAurasPacket = now;
        else if (now - m_firstCancelModSpeedNoContorlAurasPacket > Milliseconds(250))
        {
            m_firstCancelModSpeedNoContorlAurasPacket = TimeValue::zero();
            // TODO: May be mover?
            GetPlayer()->RemoveAurasByType(SPELL_AURA_MOD_SPEED_NO_CONTROL);
        }
    }

    m_lastCancelModSpeedNoContorlAurasPacket = now;
}

void WorldSession::HandlePetCancelAuraOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    uint32 spellId = recvPacket.read<uint32>();
    recvPacket.ReadGuidMask(guid, 0, 3, 1, 4, 6, 2, 7, 5);
    recvPacket.ReadGuidBytes(guid, 0, 5, 3, 4, 7, 2, 6, 1);

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
    {
        TC_LOG_ERROR("network", "WORLD: unknown PET spell id %u", spellId);
        return;
    }

    Creature* pet=ObjectAccessor::GetCreatureOrPetOrVehicle(*_player, guid);

    if (!pet)
    {
        TC_LOG_ERROR("network", "HandlePetCancelAura: Attempt to cancel an aura for non-existant pet %u by player '%s'", uint32(GUID_LOPART(guid)), GetPlayer()->GetName().c_str());
        return;
    }

    if (pet != GetPlayer()->GetGuardianPet() && pet != GetPlayer()->GetCharm())
    {
        TC_LOG_ERROR("network", "HandlePetCancelAura: Pet %u is not a pet of player '%s'", uint32(GUID_LOPART(guid)), GetPlayer()->GetName().c_str());
        return;
    }

    if (!pet->IsAlive())
    {
        pet->SendPetActionFeedback(FEEDBACK_PET_DEAD);
        return;
    }

    pet->RemoveOwnedAura(spellId, 0, 0, AURA_REMOVE_BY_CANCEL);

    pet->AddCreatureSpellCooldown(spellId);
}

void WorldSession::HandleCancelGrowthAuraOpcode(WorldPacket& /*recvPacket*/) { }

void WorldSession::HandleCancelAutoRepeatSpellOpcode(WorldPacket& /*recvPacket*/)
{
    // may be better send SMSG_CANCEL_AUTO_REPEAT?
    // cancel and prepare for deleting
    _player->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
}

void WorldSession::HandleCancelChanneling(WorldPacket& recvData)
{
    recvData.read_skip<uint32>();                          // spellid, not used

    // ignore for remote control state (for player case)
    Unit* mover = _player->m_mover;
    if (mover != _player && mover->GetTypeId() == TYPEID_PLAYER)
        return;

    mover->InterruptSpell(CURRENT_CHANNELED_SPELL);
}

void WorldSession::HandleTotemDestroyed(WorldPacket& recvPacket)
{
    // ignore for remote control state
    if (_player->m_mover != _player)
        return;

    ObjectGuid guid;
    uint8 slotId;

    recvPacket >> slotId;

    guid[4] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[7]);

    ++slotId;
    if (slotId >= SUMMON_SLOT_MAX_TOTEM)
        return;

    if (!_player->m_SummonSlot[slotId])
        return;

    Creature* summon = GetPlayer()->GetMap()->GetCreature(_player->m_SummonSlot[slotId]);
    if (summon && summon->IsSummon() && (!guid || summon->GetGUID() == guid))
        summon->ToTempSummon()->UnSummon();
}

void WorldSession::HandleSelfResOpcode(WorldPacket& /*recvData*/)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_SELF_RES");                  // empty opcode

    if (_player->HasAuraType(SPELL_AURA_PREVENT_RESURRECTION))
        return; // silent return, client should display error by itself and not send this opcode

    if (_player->GetUInt32Value(PLAYER_FIELD_SELF_RES_SPELL))
    {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(_player->GetUInt32Value(PLAYER_FIELD_SELF_RES_SPELL));
        if (spellInfo)
            _player->CastSpell(_player, spellInfo, false, 0);

        _player->SetUInt32Value(PLAYER_FIELD_SELF_RES_SPELL, 0);
    }
}

void WorldSession::HandleSpellClick(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_SPELLCLICK");

    ObjectGuid guid;

    guid[7] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();

    uint8 unk = recvData.ReadBit();

    guid[1] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[0]);

    // this will get something not in world. crash
    Creature* unit = ObjectAccessor::GetCreatureOrPetOrVehicle(*_player, guid);

    if (!unit)
        return;

    /// @todo Unit::SetCharmedBy: 28782 is not in world but 0 is trying to charm it! -> crash
    if (!unit->IsInWorld())
        return;

    _player->TalkedToCreature(unit->GetEntry(), unit->GetGUID());
    unit->HandleSpellClick(_player);
}

void WorldSession::HandleMirrorImageDataRequest(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_GET_MIRROR_IMAGE_DATA");
    ObjectGuid guid;

    uint32 displayId;
    recvData >> displayId;

    guid[0] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[7]);

    // Get unit for which data is needed by client
    Unit* unit = ObjectAccessor::GetObjectInWorld(guid, (Unit*)NULL);
    if (!unit)
        return;

    if (!unit->HasAuraType(SPELL_AURA_CLONE_CASTER))
        return;

    // Get creator of the unit (SPELL_AURA_CLONE_CASTER does not stack)
    uint64 casterGuid = unit->GetAuraEffectsByType(SPELL_AURA_CLONE_CASTER).front()->GetCasterGUID();
    Unit* creator = ObjectAccessor::GetUnit(*GetPlayer(), casterGuid);
    Player* player = creator ? creator->ToPlayer() : nullptr;

    // Idk, but without response player will be invisible
    if (!player && IS_PLAYER_GUID(casterGuid))
        player = unit->ToPlayer();

    if (player && player->GetDisplayId() == player->GetNativeDisplayId())
    {
        WorldPacket data(SMSG_MIRROR_IMAGE_COMPONENTED_DATA, 8 + 4 + 8 * 1 + 8 + 11 * 4);
        Guild* guild = player->GetGuild();
        ObjectGuid guildGuid = guild ? guild->GetGUID() : 0;

        data.WriteBit(guid[4]);
        data.WriteBit(guildGuid[3]);
        data.WriteBit(guildGuid[6]);
        data.WriteBit(guid[0]);
        data.WriteBit(guildGuid[7]);
        data.WriteBit(guid[1]);
        data.WriteBit(guid[5]);
        data.WriteBit(guildGuid[2]);
        data.WriteBit(guildGuid[1]);
        data.WriteBit(guid[7]);
        data.WriteBit(guildGuid[4]);
        data.WriteBit(guildGuid[0]);
        data.WriteBit(guid[2]);
        data.WriteBit(guildGuid[5]);
        data.WriteBit(guid[3]);
        data.WriteBits(11, 22); // item slots count
        data.WriteBit(guid[6]);
        data.FlushBits();

        data << uint8(player->GetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 3)); // haircolor
        data << uint32(player->GetDisplayId());
        data << uint8(player->GetByteValue(PLAYER_FIELD_REST_STATE, 0));    // facial hair

        data.WriteByteSeq(guildGuid[6]);
        data.WriteByteSeq(guildGuid[4]);
        data.WriteByteSeq(guid[7]);
        data.WriteByteSeq(guildGuid[1]);
        data.WriteByteSeq(guid[3]);
        data << uint8(player->GetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 2)); // hair 
        data.WriteByteSeq(guid[2]);
        data.WriteByteSeq(guid[0]);
        data << uint8(player->GetRace());
        data << uint8(player->GetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 0)); // skin
        data.WriteByteSeq(guildGuid[7]);

        static EquipmentSlots const itemSlots[] =
        {
            EQUIPMENT_SLOT_HEAD,
            EQUIPMENT_SLOT_SHOULDERS,
            EQUIPMENT_SLOT_BODY,
            EQUIPMENT_SLOT_CHEST,
            EQUIPMENT_SLOT_WAIST,
            EQUIPMENT_SLOT_LEGS,
            EQUIPMENT_SLOT_FEET,
            EQUIPMENT_SLOT_WRISTS,
            EQUIPMENT_SLOT_HANDS,
            EQUIPMENT_SLOT_TABARD,
            EQUIPMENT_SLOT_BACK,
            EQUIPMENT_SLOT_END
        };

        // Display items in visible slots
        for (EquipmentSlots const* itr = &itemSlots[0]; *itr != EQUIPMENT_SLOT_END; ++itr)
        {
            if (*itr == EQUIPMENT_SLOT_HEAD && player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM))
                data << uint32(0);
            else if (*itr == EQUIPMENT_SLOT_BACK && player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_HIDE_CLOAK))
                data << uint32(0);
            else if (Item const* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, *itr))
            {
                if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(item->GetVisibleEntry()))
                    data << uint32(proto->DisplayInfoID);
                else
                    data << uint32(0);
            }
            else
                data << uint32(0);
        }

        data.WriteByteSeq(guid[4]);
        data << uint8(player->GetClass());
        data << uint8(player->GetGender());
        data << uint8(player->GetByteValue(PLAYER_FIELD_HAIR_COLOR_ID, 1)); // face
        data.WriteByteSeq(guid[5]);
        data.WriteByteSeq(guildGuid[3]);
        data.WriteByteSeq(guildGuid[2]);
        data.WriteByteSeq(guid[1]);
        data.WriteByteSeq(guildGuid[0]);
        data.WriteByteSeq(guildGuid[5]);
        data.WriteByteSeq(guid[6]);

        SendPacket(&data);
    }
    else
    {
        WorldPacket data(SMSG_MIRROR_IMAGE_CREATURE_DATA, 8 + 4);
        data.WriteBit(guid[0]);
        data.WriteBit(guid[1]);
        data.WriteBit(guid[3]);
        data.WriteBit(guid[5]);
        data.WriteBit(guid[7]);
        data.WriteBit(guid[6]);
        data.WriteBit(guid[4]);
        data.WriteBit(guid[2]);

        data.WriteByteSeq(guid[0]);
        data.WriteByteSeq(guid[3]);
        data.WriteByteSeq(guid[6]);
        data.WriteByteSeq(guid[5]);
        data.WriteByteSeq(guid[7]);

        if (creator && creator->GetDisplayId() != displayId)
            TC_LOG_ERROR("spells", "WorldSession::HandleMirrorImageDataRequest creator->GetDisplayId() != displayId %u %u", creator->GetDisplayId(), displayId);

        data << uint32(displayId);
        data.WriteByteSeq(guid[4]);
        data.WriteByteSeq(guid[2]);
        data.WriteByteSeq(guid[1]);

        SendPacket(&data);

        if (!creator && IS_PLAYER_GUID(casterGuid))
            TC_LOG_ERROR("spells", "Can't find player caster for SPELL_AURA_CLONE_CASTER");
    }
}

void WorldSession::HandleMissileTrajectoryCollision(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_MISSILE_TRAJECTORY_COLLISION");

    ObjectGuid casterGuid;

    float z = recvPacket.read<float>();
    uint8 castCount = recvPacket.read<uint8>();
    float y = recvPacket.read<float>();
    float x = recvPacket.read<float>();
    uint32 spellId = recvPacket.read<uint32>();;
    recvPacket.ReadGuidMask(casterGuid, 5, 0, 2, 6, 7, 3, 1, 4);
    recvPacket.ReadGuidBytes(casterGuid, 1, 5, 3, 2, 7, 0, 6, 4);

    Unit* caster = ObjectAccessor::GetUnit(*_player, casterGuid);
    if (!caster)
        return;

    Spell* spell = caster->FindCurrentSpellBySpellId(spellId);
    if (!spell || !spell->m_targets.HasDst())
        return;

    Position pos = *spell->m_targets.GetDstPos();
    pos.Relocate(x, y, z); // Position of missile hit
    spell->m_targets.ModDst(pos);

    WorldPacket data(SMSG_NOTIFY_MISSILE_TRAJECTORY_COLLISION, 20);
    data.WriteGuidMask(casterGuid, 2, 7, 3, 0, 5, 6, 4, 1);
    data.WriteGuidBytes(casterGuid, 6, 5, 4);
    data << float(y);
    data.WriteGuidBytes(casterGuid, 2, 0, 3, 7);
    data << uint8(castCount);
    data << float(x);
    data << float(z);
    data.WriteGuidBytes(casterGuid, 1);

    caster->SendMessageToSet(&data, true);
}

void WorldSession::HandleRequestCategoryCooldowns(WorldPacket& /*recvPacket*/)
{
    std::map<uint32, int32> categoryMods;
    Unit::AuraEffectList const& categoryCooldownAuras = _player->GetAuraEffectsByType(SPELL_AURA_MOD_SPELL_CATEGORY_COOLDOWN);
    for (Unit::AuraEffectList::const_iterator itr = categoryCooldownAuras.begin(); itr != categoryCooldownAuras.end(); ++itr)
    {
        std::map<uint32, int32>::iterator cItr = categoryMods.find((*itr)->GetMiscValue());
        if (cItr == categoryMods.end())
            categoryMods[(*itr)->GetMiscValue()] = (*itr)->GetAmount();
        else
            cItr->second += (*itr)->GetAmount();
    }

    WorldPacket data(SMSG_SPELL_CATEGORY_COOLDOWN, 11);
    data.WriteBits(categoryMods.size(), 21);
    data.FlushBits();

    for (std::map<uint32, int32>::const_iterator itr = categoryMods.begin(); itr != categoryMods.end(); ++itr)
    {
        data << int32(-itr->second);
        data << uint32(itr->first);
    }

    SendPacket(&data);
}

void WorldSession::SendTotemCreated(ObjectGuid TotemGUID, uint32 Duration, uint32 SpellID, uint8 Slot)
{
    WorldPacket data(SMSG_TOTEM_CREATED, 17);
    data.WriteBit(TotemGUID[6]);
    data.WriteBit(TotemGUID[1]);
    data.WriteBit(TotemGUID[2]);
    data.WriteBit(TotemGUID[5]);
    data.WriteBit(TotemGUID[3]);
    data.WriteBit(TotemGUID[4]);
    data.WriteBit(TotemGUID[7]);
    data.WriteBit(TotemGUID[0]);

    data << uint32(Duration);
    data << uint32(SpellID);

    data.WriteByteSeq(TotemGUID[3]);
    data.WriteByteSeq(TotemGUID[4]);
    data.WriteByteSeq(TotemGUID[5]);
    data.WriteByteSeq(TotemGUID[6]);
    data.WriteByteSeq(TotemGUID[0]);
    data.WriteByteSeq(TotemGUID[2]);

    data << uint8(Slot);

    data.WriteByteSeq(TotemGUID[1]);
    data.WriteByteSeq(TotemGUID[7]);
    _player->SendDirectMessage(&data);
}

std::string choiceStrings[5][2] =
{
    { "Choose your assignment for the day:",                                                       "Выберите свое сегодняшнее назначение:"                                             }, // both
    { "Aid the Kirin Tor against the Thunder King's forces.",                                      "Оказать помощь в борьбе с силами Властелина Грома."                                }, // both pve
    { "Aid the Kirin Tor against the Horde and Sunreaver forces. [This will flag you for PvP]",    "Оказать помощь в борьбе с Ордой и Похитителями Солнца. [Будет включен режим PvP.]" }, // alliance pvp (ru text possible not blizzlike)
    { "Aid the Kirin Tor against the Alliance and Kirin Tor forces. [This will flag you for PvP]", "Оказать помощь в борьбе с Альянсом и Кирин-Тором. [Будет включен режим PvP.]"      }, // horde pvp (eng text possible not blizzlike)
    { "PvE",                                                                                       "PvP"                                                                               }
};

enum Choice
{
    CHOICES_COUNT        = 2,
    ITEMS_COUNT          = 1,
    FACTIONS_COUNT       = 1,
    CURRENCIES_COUNT_PVE = 2,
    CURRENCIES_COUNT_PVP = 3,

    ART_PVE              = 839172,
    ART_PVP_ALLIANCE     = 841058,
    ART_PVP_HORDE        = 841057,

    CHOICE_PVE_HORDE     = 54,
    CHOICE_PVP_HORDE     = 55,
    CHOICE_PVE_ALLIANCE  = 64,
    CHOICE_PVP_ALLIANCE  = 65,

    QUEST_PVE_HORDE      = 32259,
    QUEST_PVP_HORDE      = 32258,
    QUEST_PVE_ALLIANCE   = 32260,
    QUEST_PVP_ALLIANCE   = 32261,

    QUEST_ITEM_HORDE     = 95623,
    QUEST_ITEM_ALLIANCE  = 95622,
};

// used only for isle of thunder and only with hardcoded values
void WorldSession::SendPlayerChoice(uint32 choiceId)
{
    bool horde = _player->GetTeam() == HORDE;
    bool ru = _player->GetSession()->GetSessionDbLocaleIndex() == LOCALE_ruRU;
    bool pve = false;

    WorldPacket data(SMSG_DISPLAY_PLAYER_CHOICE);
    data << uint32(choiceId);
    data.WriteBits(choiceStrings[0][ru].size(), 8);
    data.WriteBits(CHOICES_COUNT, 20);

    for (uint8 i = 0; i < CHOICES_COUNT; i++)
    {
        pve = i == 0;

        const Quest* quest = sObjectMgr->GetQuestTemplate(pve ? (horde ? QUEST_PVE_HORDE : QUEST_PVE_ALLIANCE) : (horde ? QUEST_PVP_HORDE : QUEST_PVP_ALLIANCE));

        data.WriteBit(quest ? true : false);
        if (!quest)
            continue;

        if (quest)
        {
            data.WriteBit(quest->GetRewardOrRequiredMoney() == 0); // has money
            data.WriteBits(pve ? CURRENCIES_COUNT_PVE : CURRENCIES_COUNT_PVP, 25);
            data.WriteBit(true); // unk

            for (uint8 j = 0; j < (pve ? CURRENCIES_COUNT_PVE : CURRENCIES_COUNT_PVP); j++)
            {
                data.WriteBit(true);  // unk
                data.WriteBit(false); // has currency id
                data.WriteBit(false); // has currency count
            }

            data.WriteBits(FACTIONS_COUNT, 25);
            data.WriteBit(true); // unk
            data.WriteBit(true); // unk
            data.WriteBits(ITEMS_COUNT, 25);
            data.WriteBit(true); // unk

            for (uint8 j = 0; j < FACTIONS_COUNT; j++)
            {
                data.WriteBit(true);  // unk
                data.WriteBit(quest->RewardFactionId[0] == 0); // has faction id
                data.WriteBit(quest->RewardFactionValueIdOverride[0] == 0); // has faction reputation count
            }

            data.WriteBits(0, 25); // unk
            data.WriteBit(true); // unk
            data.WriteBit(true); // unk

            for (uint8 j = 0; j < ITEMS_COUNT; j++)
            {
                data.WriteBit(false); // has item count
                data.WriteBit(false); // has item id
                data.WriteBit(false); // has item display id
            }
            data.WriteBit(true); // unk
        }
        data.WriteBits(choiceStrings[i == 0 ? 1 : (horde ? 3 : 2)][ru].size(), 11);
        data.WriteBits(choiceStrings[4][i].size(), 9);
    }

    data.FlushBits();

    for (uint8 i = 0; i < CHOICES_COUNT; i++)
    {
        pve = i == 0;

        const Quest* quest = sObjectMgr->GetQuestTemplate(pve ? (horde ? QUEST_PVE_HORDE : QUEST_PVE_ALLIANCE) : (horde ? QUEST_PVP_HORDE : QUEST_PVP_ALLIANCE));
        if (!quest)
            continue;

        if (quest)
        {
            for (uint8 j = 0; j < ITEMS_COUNT; j++)
            {
                auto item = sObjectMgr->GetItemTemplate(horde ? QUEST_ITEM_HORDE : QUEST_ITEM_ALLIANCE);

                data << uint32(item ? (pve ? 2 : 1) : 0);
                data << uint32(item ? item->DisplayInfoID : 0);
                data << uint32(item ? item->ItemId : 0);
            }
            for (uint8 j = 0; j < FACTIONS_COUNT; j++)
            {
                auto faction = sFactionStore.LookupEntry(quest->RewardFactionId[0]);

                data << uint32(faction ? (pve ? 2150 : 1250) : 0);
                data << uint32(faction ? faction->ID : 0);
            }
            for (uint8 j = 0; j < (pve ? CURRENCIES_COUNT_PVE : CURRENCIES_COUNT_PVP); j++)
            {
                uint32 currencry = 0;
                uint32 currencryCount = 0;
                switch (j)
                {
                    case 0: currencry = pve ? 396 : 392; currencryCount = pve ? 60 : 525; break;
                    case 1: currencry = pve ? 738 : 390; currencryCount = pve ? 30 :  50; break;
                    case 2: if (!pve) { currencry = 738; currencryCount = 19; }           break;
                }
                auto faction = sCurrencyTypesStore.LookupEntry(currencry);

                data << uint32(currencry);
                data << uint32(currencryCount);
            }
            data << uint64(quest->GetRewardOrRequiredMoney());
        }
        data.WriteString(choiceStrings[4][i]);
        data << uint32(pve ? ART_PVE : (horde ? ART_PVP_HORDE : ART_PVP_ALLIANCE));
        data.WriteString(choiceStrings[pve ? 1 : (horde ? 3 : 2)][ru]);
        data << uint32(pve ? (horde ? CHOICE_PVE_HORDE : CHOICE_PVE_ALLIANCE) : (horde ? CHOICE_PVP_HORDE : CHOICE_PVP_ALLIANCE));
    }

    data.WriteString(choiceStrings[0][ru]);

    _player->SendDirectMessage(&data);
}

void WorldSession::HandlePlayerChoiceResponse(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_CHOICE_RESPONSE");

    uint32 responseId = recvPacket.read<uint32>();
    uint32 choiceId   = recvPacket.read<uint32>();

    Player* player = GetPlayer();
    if (!player)
        return;

    switch (responseId)
    {
        case CHOICE_PVE_HORDE:
            player->CastSpell(player, 139047);
            break;
        case CHOICE_PVP_HORDE:
            player->CastSpell(player, 139048);
            player->UpdatePvP(true);
            break;
        case CHOICE_PVE_ALLIANCE:
            player->CastSpell(player, 139045);
            break;
        case CHOICE_PVP_ALLIANCE:
            player->CastSpell(player, 139046);
            player->UpdatePvP(true);
            break;
    }
}
