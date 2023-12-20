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

#ifndef TRINITYCORE_PET_H
#define TRINITYCORE_PET_H

#include "PetDefines.h"
#include "TemporarySummon.h"

#define PET_FOCUS_REGEN_INTERVAL 4 * IN_MILLISECONDS
#define HAPPINESS_LEVEL_SIZE        333000

struct PetSpell
{
    ActiveStates  active;
    PetSpellState state;
};

typedef std::unordered_map<uint32, PetSpell> PetSpellMap;
typedef std::vector<uint32> AutoSpellList;

class Player;

class Pet : public Guardian
{
    public:
        static const float BaseRunSpeedRate;
    public:
        explicit Pet(Player* owner, PetType type = MAX_PET_TYPE);
        virtual ~Pet();

        void AddToWorld() override;
        void RemoveFromWorld() override;

        void SetDisplayId(uint32 modelId) override;

        PetType getPetType() const { return m_petType; }
        void setPetType(PetType type) { m_petType = type; }
        bool isControlled() const { return (getPetType() == SUMMON_PET || getPetType() == HUNTER_PET) && !IsTemporary(); }
        bool isTemporarySummoned() const { return m_duration > 0; }

        bool IsPermanentPetFor(Player* owner) const;        // pet have tab in character windows and set UNIT_FIELD_PET_NUMBER

        bool Create(uint32 guidlow, Map* map, uint32 phaseMask, uint32 Entry, uint32 pet_number);
        bool CreateBaseAtCreature(Creature* creature);
        bool CreateBaseAtCreatureInfo(CreatureTemplate const* cinfo, Unit* owner);
        bool CreateBaseAtTamed(CreatureTemplate const* cinfo, Map* map, uint32 phaseMask);
        bool LoadPetFromDB(PetLoadMode mode, uint32 param, Position const* pos = nullptr);
        bool isBeingLoaded() const override { return m_loading;}
        void SavePetToDB(CharacterDatabaseTransaction trans = nullptr);
        void DeletePetFromDB() { Pet::DeleteFromDB(GetCharmInfo()->GetPetNumber()); }
        void Remove(PetRemoveMode mode, int32 flags = PET_REMOVE_FLAG_NONE);
        static void DeleteFromDB(uint32 guidlow);

        void setDeathState(DeathState s) override;                   // overwrite virtual Creature::setDeathState and Unit::setDeathState
        void Update(uint32 diff) override;                           // overwrite virtual Creature::Update and Unit::Update

        uint8 GetPetAutoSpellSize() const { return m_autospells.size(); }
        uint32 GetPetAutoSpellOnPos(uint8 pos) const
        {
            if (pos >= m_autospells.size())
                return 0;
            else
                return m_autospells[pos];
        }

        bool IsAutoCastEnabled(uint32 spellId) const;

        void GivePetLevel(uint8 level);
        void SynchronizeLevelWithOwner();
        bool HaveInDiet(ItemTemplate const* item) const;
        uint32 GetCurrentFoodBenefitLevel(uint32 itemlevel) const;
        void SetDuration(int32 dur) { m_duration = dur; }
        int32 GetDuration() const { return m_duration; }

        /*
        bool UpdateStats(Stats stat);
        bool UpdateAllStats();
        void UpdateResistances(uint32 school);
        void UpdateArmor();
        void UpdateMaxHealth();
        void UpdateMaxPower(Powers power);
        void UpdateAttackPowerAndDamage(bool ranged = false);
        void UpdateDamagePhysical(WeaponAttackType attType);
        */

        void ToggleAutocast(SpellInfo const* spellInfo, bool apply);

        bool HasSpell(uint32 spell) const override;

        void CastPetAuras(bool current);
        void CastPetAura(PetAura const* aura);
        bool IsPetAura(Aura const* aura);

        void _LoadAuras(uint32 timediff);
        void _SaveAuras(CharacterDatabaseTransaction trans);
        void _LoadSpells();
        void _SaveSpells(CharacterDatabaseTransaction trans);

        bool AddSpell(uint32 spellId, ActiveStates active = ACT_DECIDE);
        bool LearnSpell(uint32 spell_id);
        void learnSpellHighRank(uint32 spellid);
        void InitSpellsForLevel();
        bool UnlearnSpell(uint32 spellId, bool learnPrev, bool cleaActionBar = true);
        bool RemoveSpell(uint32 spell_id, bool learn_prev, bool clear_ab = true);
        void CleanupActionBar();
        virtual void ProhibitSpellSchool(SpellSchoolMask idSchoolMask, uint32 unTimeMs);

        PetSpellMap     m_spells;
        AutoSpellList   m_autospells;

        void InitPetCreateSpells();

        static void resetTalentsForAllPetsOf(Player* owner, Pet* online_pet = NULL);
        void InitTalentForLevel();

        uint8 GetMaxTalentPointsForLevel(uint8 level);

        uint32  m_usedTalentCount;

        uint64 GetAuraUpdateMaskForRaid() const { return m_auraRaidUpdateMask; }
        void SetAuraUpdateMaskForRaid(uint8 slot) { m_auraRaidUpdateMask |= (uint64(1) << slot); }
        void ResetAuraUpdateMaskForRaid() { m_auraRaidUpdateMask = 0; }

        DeclinedName const* GetDeclinedNames() const { return m_declinedname; }

        bool    m_removed;                                  // prevent overwrite pet state in DB at next Pet::Update if pet already removed(saved)

        Player* GetOwner() const;

        uint32 GetSpecializationId() const { return m_specialization; }
        void SetSpecializationId(uint32 id) { m_specialization = id; }
        void SetSpecialization(uint16 spec);
        void LearnSpecializationSpells(bool learn, bool clearActionBar = false);

        void UpdateMaxPower(Powers power) override;
        void SetObjectScale(float scale) override;

        bool IsTemporary() const { return m_temporary; }    // Stampede
        void SetTemporary() { m_temporary = true; }

    protected:
        PetType m_petType;
        int32   m_duration;                                 // time until unsummon (used mostly for summoned guardians and not used for controlled pets)
        uint64  m_auraRaidUpdateMask;
        bool    m_loading;
        bool    m_temporary = false;
        uint32  m_specialization = 0;

        DeclinedName *m_declinedname;

    private:
        void SaveToDB(uint32, uint16, uint32) override               // override of Creature::SaveToDB     - must not be called
        {
            ASSERT(false);
        }
        void DeleteFromDB()                                 // override of Creature::DeleteFromDB - must not be called
        {
            ASSERT(false);
        }
};
#endif
