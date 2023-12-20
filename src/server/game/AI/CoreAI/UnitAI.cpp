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

#include "UnitAI.h"
#include "Player.h"
#include "Creature.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "Spell.h"
#include "CreatureAIImpl.h"
#include "Player.h"

void UnitAI::AttackStart(Unit* victim)
{
    if (victim && me->Attack(victim, true))
        me->GetMotionMaster()->MoveChase(victim);
}

void UnitAI::AttackStartCaster(Unit* victim, float dist)
{
    if (victim && me->Attack(victim, false))
        me->GetMotionMaster()->MoveChase(victim, dist, 0.0f);
}

void UnitAI::DoMeleeAttackIfReady(bool ignoreLos)
{
    if (me->HasUnitState(UNIT_STATE_CASTING))
        return;

    Unit* victim = me->GetVictim();
    //Make sure our attack is ready and we aren't currently casting before checking distance
    if (me->isAttackReady() && me->IsWithinMeleeRange(victim))
    {
        me->AttackerStateUpdate(victim, ignoreLos);
        me->resetAttackTimer();
    }

    if (me->HasOffhandWeapon() && me->isAttackReady(OFF_ATTACK) && me->IsWithinMeleeRange(victim))
    {
        me->AttackerStateUpdate(victim, ignoreLos, OFF_ATTACK);
        me->resetAttackTimer(OFF_ATTACK);
    }
}

bool UnitAI::DoSpellAttackIfReady(uint32 spell)
{
    if (me->HasUnitState(UNIT_STATE_CASTING) || !me->isAttackReady())
        return true;

    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell))
    {
        if (me->IsWithinCombatRange(me->GetVictim(), spellInfo->GetMaxRange(false)))
        {
            me->CastSpell(me->GetVictim(), spell, false);
            me->resetAttackTimer();
            return true;
        }
    }

    return false;
}

Unit* UnitAI::SelectTarget(SelectAggroTarget targetType, uint32 position, float dist, bool playerOnly, int32 aura)
{
    return SelectTarget(targetType, position, DefaultTargetSelector(me, dist, playerOnly, aura));
}

void UnitAI::SelectTargetList(std::list<Unit*>& targetList, uint32 num, SelectAggroTarget targetType, float dist, bool playerOnly, int32 aura)
{
    SelectTargetList(targetList, DefaultTargetSelector(me, dist, playerOnly, aura), num, targetType);
}

float UnitAI::DoGetSpellMaxRange(uint32 spellId, bool positive)
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    return spellInfo ? spellInfo->GetMaxRange(positive) : 0;
}

void UnitAI::DoAddAuraToAllHostilePlayers(uint32 spellid)
{
    if (me->IsInCombat())
    {
        ThreatContainer::StorageType threatlist = me->getThreatManager().getThreatList();
        for (ThreatContainer::StorageType::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
            if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                if (unit->GetTypeId() == TYPEID_PLAYER)
                    me->AddAura(spellid, unit);
        }
    }
}

void UnitAI::DoCastToAllHostilePlayers(uint32 spellid, bool triggered)
{
    if (me->IsInCombat())
    {
        ThreatContainer::StorageType threatlist = me->getThreatManager().getThreatList();
        for (ThreatContainer::StorageType::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
            if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                if (unit->GetTypeId() == TYPEID_PLAYER)
                    me->CastSpell(unit, spellid, triggered);
        }
    }
}

void UnitAI::DoCast(uint32 spellId)
{
    Unit* target = NULL;

    switch (AISpellInfo[spellId].target)
    {
        default:
        case AITARGET_SELF:
            target = me;
            break;
        case AITARGET_VICTIM:
            target = me->GetVictim();
            break;
        case AITARGET_ENEMY:
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
            {
                bool playerOnly = spellInfo->AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_PLAYERS;
                target = SelectTarget(SELECT_TARGET_RANDOM, 0, spellInfo->GetMaxRange(false), playerOnly);
            }
            break;
        }
        case AITARGET_ALLY:
            target = me;
            break;
        case AITARGET_BUFF:
            target = me;
            break;
        case AITARGET_DEBUFF:
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
            {
                bool playerOnly = spellInfo->AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_PLAYERS;
                float range = spellInfo->GetMaxRange(false);

                DefaultTargetSelector targetSelector(me, range, playerOnly, -(int32)spellId);
                if (!spellInfo->HasAuraInterruptFlag(AURA_INTERRUPT_FLAG_NOT_VICTIM)
                    && targetSelector(me->GetVictim()))
                    target = me->GetVictim();
                else
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0, targetSelector);
            }
            break;
        }
    }

    if (target)
        me->CastSpell(target, spellId, false);
}

void UnitAI::DoCast(Unit* victim, uint32 spellId, bool triggered)
{
    if (!victim || (me->HasUnitState(UNIT_STATE_CASTING) && !triggered))
        return;

    me->CastSpell(victim, spellId, triggered);
}

void UnitAI::DoCast(SelectAggroTarget targetType, uint32 spellId, bool triggered, uint32 position, float dist, bool playerOnly, int32 aura)
{
    Unit * target = SelectTarget(targetType, position, DefaultTargetSelector(me, dist, playerOnly, aura));

    if (!target)
    {
        if (position)
            target = SelectTarget(targetType, 0, DefaultTargetSelector(me, dist, playerOnly, aura));
        else if (dist > 0.0f)
            target = SelectTarget(targetType, position, DefaultTargetSelector(me, 0.0f, playerOnly, aura));
    }

    if (target)
        me->CastSpell(target, spellId, triggered);
}

void UnitAI::DoCastSelf(uint32 spellId, bool triggered)
{
    if (!triggered && me->HasUnitState(UNIT_STATE_CASTING))
        return;

    me->CastSpell(me, spellId, triggered);
}

void UnitAI::DoCastVictim(uint32 spellId, bool triggered)
{
    if (!me->GetVictim() || (me->HasUnitState(UNIT_STATE_CASTING) && !triggered))
        return;

    me->CastSpell(me->GetVictim(), spellId, triggered);
}

void UnitAI::DoCastAOE(uint32 spellId, bool triggered)
{
    if (!triggered && me->HasUnitState(UNIT_STATE_CASTING))
        return;

    me->CastSpell((Unit*)NULL, spellId, triggered);
}

#define UPDATE_TARGET(a) {if (AIInfo->target<a) AIInfo->target=a;}

void UnitAI::FillAISpellInfo()
{
    AISpellInfo = new AISpellInfoType[sSpellMgr->GetSpellInfoStoreSize()];

    AISpellInfoType* AIInfo = AISpellInfo;
    const SpellInfo* spellInfo;

    for (uint32 i = 0; i < sSpellMgr->GetSpellInfoStoreSize(); ++i, ++AIInfo)
    {
        spellInfo = sSpellMgr->GetSpellInfo(i);
        if (!spellInfo)
            continue;

        if (spellInfo->Attributes & SPELL_ATTR0_CASTABLE_WHILE_DEAD)
            AIInfo->condition = AICOND_DIE;
        else if (spellInfo->IsPassive() || spellInfo->GetDuration() == -1)
            AIInfo->condition = AICOND_AGGRO;
        else
            AIInfo->condition = AICOND_COMBAT;

        if (AIInfo->cooldown < spellInfo->RecoveryTime)
            AIInfo->cooldown = spellInfo->RecoveryTime;

        if (!spellInfo->GetMaxRange(false))
            UPDATE_TARGET(AITARGET_SELF)
        else
        {
            for (uint32 j = 0; j < MAX_SPELL_EFFECTS; ++j)
            {
                uint32 targetType = spellInfo->Effects[j].TargetA.GetTarget();

                if (targetType == TARGET_UNIT_TARGET_ENEMY
                    || targetType == TARGET_DEST_TARGET_ENEMY)
                    UPDATE_TARGET(AITARGET_VICTIM)
                else if (targetType == TARGET_UNIT_DEST_AREA_ENEMY)
                    UPDATE_TARGET(AITARGET_ENEMY)

                if (spellInfo->Effects[j].Effect == SPELL_EFFECT_APPLY_AURA)
                {
                    if (targetType == TARGET_UNIT_TARGET_ENEMY)
                        UPDATE_TARGET(AITARGET_DEBUFF)
                    else if (spellInfo->IsPositive())
                        UPDATE_TARGET(AITARGET_BUFF)
                }
            }
        }
        AIInfo->realCooldown = spellInfo->RecoveryTime + spellInfo->StartRecoveryTime;
        AIInfo->maxRange = spellInfo->GetMaxRange(false) * 3 / 4;
    }
}

SpellTargetSelector::SpellTargetSelector(Unit* caster, uint32 spellId) :
    _caster(caster), _spellInfo(sSpellMgr->GetSpellForDifficultyFromSpell(sSpellMgr->GetSpellInfo(spellId), caster))
{
    ASSERT(_spellInfo);
}

bool SpellTargetSelector::operator()(Unit const* target) const
{
    if (!target)
        return false;

    if (_spellInfo->CheckTarget(_caster, target) != SPELL_CAST_OK)
        return false;

    // copypasta from Spell::CheckRange
    uint32 range_type = _spellInfo->RangeEntry ? _spellInfo->RangeEntry->type : 0;
    float max_range = _caster->GetSpellMaxRangeForTarget(target, _spellInfo);
    float min_range = _caster->GetSpellMinRangeForTarget(target, _spellInfo);


    if (target && target != _caster)
    {
        if (range_type == SPELL_RANGE_MELEE)
        {
            // Because of lag, we can not check too strictly here.
            if (!_caster->IsWithinMeleeRange(target, max_range))
                return false;
        }
        else if (!_caster->IsWithinCombatRange(target, max_range))
            return false;

        if (range_type == SPELL_RANGE_RANGED)
        {
            if (_caster->IsWithinMeleeRange(target))
                return false;
        }
        else if (min_range && _caster->IsWithinCombatRange(target, min_range)) // skip this check if min_range = 0
            return false;
    }

    return true;
}

bool NonTankTargetSelector::operator()(Unit const* target) const
{
    if (!target)
        return false;

    if (_playerOnly && target->GetTypeId() != TYPEID_PLAYER)
        return false;

    return target != _source->GetVictim();
}


// Range Group (meele in range group shouldn`ve execute)
bool CasterSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    switch (target->ToPlayer()->GetClass())
    {
        case CLASS_MAGE:
        case CLASS_PRIEST:
        case CLASS_WARLOCK:
        case CLASS_HUNTER:
            return _spellId ? !target->ToPlayer()->HasAura(_spellId) : true;
        case CLASS_MONK:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_MONK_MISTWEAVER && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_MONK_MISTWEAVER;
        case CLASS_DRUID:
            return _spellId ? (target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_BALANCE || target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_RESTORATION) && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_BALANCE || target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_RESTORATION;
        case CLASS_SHAMAN:
            return _spellId ? (target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_ELEMENTAL || target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_RESTORATION) && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_ELEMENTAL || target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_RESTORATION;
        case CLASS_PALADIN:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_PALADIN_HOLY && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_PALADIN_HOLY;
    }

    return false;
}

// Meele Group (caster in meele group shouldn`ve execute)
bool MeeleSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    switch (target->ToPlayer()->GetClass())
    {
        case CLASS_ROGUE:
            return _spellId ? !target->ToPlayer()->HasAura(_spellId) : true;
        case CLASS_WARRIOR:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() != SPEC_WARRIOR_PROTECTION && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() != SPEC_WARRIOR_PROTECTION;
        case CLASS_PALADIN:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_PALADIN_RETRIBUTION && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_PALADIN_RETRIBUTION;
            break;
        case CLASS_MONK:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_MONK_WINDWALKER && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_MONK_WINDWALKER;
        case CLASS_DRUID:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_FERAL && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_DRUID_FERAL;
        case CLASS_SHAMAN:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_ENHANCEMENT && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() == SPEC_SHAMAN_ENHANCEMENT;
        case CLASS_DEATH_KNIGHT:
            return _spellId ? target->ToPlayer()->GetTalentSpecialization() != SPEC_DEATH_KNIGHT_BLOOD && !target->ToPlayer()->HasAura(_spellId)
                : target->ToPlayer()->GetTalentSpecialization() != SPEC_DEATH_KNIGHT_BLOOD;
    }

    return false;
}

bool DpsSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    return _spellId ? target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_DPS && !target->ToPlayer()->HasAura(_spellId)
        : target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_DPS;
}

bool TankSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    return _spellId ? target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_TANK && !target->ToPlayer()->HasAura(_spellId)
        : target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_TANK;
}

bool HealerSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    return _spellId ? target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_HEALER && !target->ToPlayer()->HasAura(_spellId)
        : target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) == ROLES_HEALER;
}

bool NonTankSpecTargetSelector::operator()(WorldObject* target) const
{
    if (!target)
        return false;

    if (!target->ToPlayer())
        return false;

    // Prevent GM selection
    if (target->ToPlayer()->IsGameMaster())
        return false;

    return _spellId ? target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) != ROLES_TANK && !target->ToPlayer()->HasAura(_spellId)
        : target->ToPlayer()->GetRoleForGroup(target->ToPlayer()->GetTalentSpecialization()) != ROLES_TANK;
}
