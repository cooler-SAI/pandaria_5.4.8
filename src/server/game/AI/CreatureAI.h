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

#ifndef TRINITY_CREATUREAI_H
#define TRINITY_CREATUREAI_H

#include "Creature.h"
#include "Optional.h"
#include "UnitAI.h"
#include "Common.h"

class WorldObject;
class Unit;
class Creature;
class Player;
class PlayerAI;
class SpellInfo;

#define TIME_INTERVAL_LOOK   5000
#define VISIBILITY_RANGE    10000

//Spell targets used by SelectSpell
enum SelectTargetType
{
    SELECT_TARGET_DONTCARE = 0,                             //All target types allowed

    SELECT_TARGET_SELF,                                     //Only Self casting

    SELECT_TARGET_SINGLE_ENEMY,                             //Only Single Enemy
    SELECT_TARGET_AOE_ENEMY,                                //Only AoE Enemy
    SELECT_TARGET_ANY_ENEMY,                                //AoE or Single Enemy

    SELECT_TARGET_SINGLE_FRIEND,                            //Only Single Friend
    SELECT_TARGET_AOE_FRIEND,                               //Only AoE Friend
    SELECT_TARGET_ANY_FRIEND                                //AoE or Single Friend
};

//Spell Effects used by SelectSpell
enum SelectEffect
{
    SELECT_EFFECT_DONTCARE = 0,                             //All spell effects allowed
    SELECT_EFFECT_DAMAGE,                                   //Spell does damage
    SELECT_EFFECT_HEALING,                                  //Spell does healing
    SELECT_EFFECT_AURA                                      //Spell applies an aura
};

enum SCEquip
{
    EQUIP_NO_CHANGE = -1,
    EQUIP_UNEQUIP   = 0
};

class CreatureAI : public UnitAI
{
    protected:
        Creature* const me;

        bool UpdateVictim();
        bool UpdateVictimWithGaze();

        void SetGazeOn(Unit* target);

        Creature* DoSummon(uint32 entry, Position const& pos, uint32 despawnTime = 30000, TempSummonType summonType = TEMPSUMMON_CORPSE_TIMED_DESPAWN);
        Creature* DoSummon(uint32 entry, WorldObject* obj, float radius = 5.0f, uint32 despawnTime = 30000, TempSummonType summonType = TEMPSUMMON_CORPSE_TIMED_DESPAWN);
        Creature* DoSummonFlyer(uint32 entry, WorldObject* obj, float flightZ, float radius = 5.0f, uint32 despawnTime = 30000, TempSummonType summonType = TEMPSUMMON_CORPSE_TIMED_DESPAWN);

    public:
        void Talk(uint8 id, WorldObject const* whisperTarget = nullptr);
        void TalkToMap(uint8 id, WorldObject const* whisperTarget = nullptr);

        explicit CreatureAI(Creature* creature) : UnitAI(creature), me(creature), m_MoveInLineOfSight_locked(false), m_canSeeEvenInPassiveMode(false)
        { }

        virtual ~CreatureAI() { }

        /// == Reactions At =================================

        // Called if IsVisible(Unit* who) is true at each who move, reaction at visibility zone enter
        void MoveInLineOfSight_Safe(Unit* who);

        bool CanSeeEvenInPassiveMode() { return m_canSeeEvenInPassiveMode; }
        void SetCanSeeEvenInPassiveMode(bool canSeeEvenInPassiveMode) { m_canSeeEvenInPassiveMode = canSeeEvenInPassiveMode; }
        
        // Called in Creature::Update when deathstate = DEAD. Inherited classes may maniuplate the ability to respawn based on scripted events.
        virtual bool CanRespawn() { return true; }

        // Called for reaction at stopping attack at no attackers or targets
        virtual void EnterEvadeMode();

        // Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
        virtual void EnterCombat(Unit* /*victim*/) { }

        // Called when the creature is killed
        virtual void JustDied(Unit* /*killer*/) { }

        // Called when the creature kills a unit
        virtual void KilledUnit(Unit* /*victim*/) { }

        // Called when the creature summon successfully other creature
        virtual void JustSummoned(Creature* /*summon*/) { }
        virtual void IsSummonedBy(Unit* /*summoner*/) { }

        virtual void Unsummoned() { }

        virtual void SummonedCreatureDespawn(Creature* /*summon*/) { }
        virtual void SummonedCreatureDies(Creature* /*summon*/, Unit* /*killer*/) { }

        // Called when hit by a spell
        virtual void SpellHit(Unit* /*caster*/, SpellInfo const* /*spell*/) { }

        // Called when spell hits a target
        virtual void SpellHitTarget(Unit* /*target*/, SpellInfo const* /*spell*/) { }

        // Called after spell is casted
        virtual void SpellCasted(Spell const* spell) { }

        // Called when spellcast was interrupted for any reason
        virtual void CastInterrupted(SpellInfo const* /*spell*/) {}

        // Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
        virtual void AttackedBy(Unit* /*attacker*/) { }
        virtual bool IsEscorted() { return false; }

        // Called when creature is spawned or respawned (for reseting variables)
        virtual void JustRespawned() { Reset(); }

        // Called at waypoint reached or point movement finished
        virtual void MovementInform(uint32 /*type*/, uint32 /*id*/) { }

        void OnCharmed(bool apply);

        // Called at reaching home after evade
        virtual void JustReachedHome() { }

        void DoZoneInCombat(Creature* creature = NULL, float maxRangeToNearestTarget = 50.0f);

        void DoAttackerAreaInCombat(Unit* attacker, float range, Unit* pUnit = NULL);
        void DoAttackerGroupInCombat(Player* attacker);

        // Called at text emote receive from player
        virtual void ReceiveEmote(Player* /*player*/, uint32 /*emoteId*/) { }

        // Called when owner takes damage
        virtual void OwnerAttackedBy(Unit* /*attacker*/) { }

        // Called when owner attacks something
        virtual void OwnerAttacked(Unit* /*target*/) { }

        /// == Triggered Actions Requested ==================

        // Called when creature attack expected (if creature can and no have current victim)
        // Note: for reaction at hostile action must be called AttackedBy function.
        //virtual void AttackStart(Unit*) { }

        // Called at World update tick
        //virtual void UpdateAI(const uint32 /*diff*/) { }

        /// == State checks =================================

        // Is unit visible for MoveInLineOfSight
        //virtual bool IsVisible(Unit*) const { return false; }

        // called when the corpse of this creature gets removed
        virtual void CorpseRemoved(uint32& /*respawnDelay*/) { }

        // Called when victim entered water and creature can not enter water
        //virtual bool CanReachByRangeAttack(Unit*) { return false; }

        /// == Gossip system ================================

        // Called when the dialog status between a player and the creature is requested.
        // virtual Optional<QuestGiverStatus> GetDialogStatus(Player* player); TC master branch

        // Called when a player opens a gossip dialog with the creature.
        virtual bool OnGossipHello(Player* /*player*/) { return false; }

        // Called when a player selects a gossip item in the creature's gossip menu.
        virtual bool OnGossipSelect(Player* /*player*/, uint32 /*menuId*/, uint32 /*gossipListId*/) { return false; }

        // Called when a player selects a gossip with a code in the creature's gossip menu.
        virtual bool OnGossipSelectCode(Player* /*player*/, uint32 /*menuId*/, uint32 /*gossipListId*/, char const* /*code*/) { return false; }

        // Called when a player accepts a quest from the creature.
        virtual void OnQuestAccept(Player* /*player*/, Quest const* /*quest*/) { }

        // Called when a player completes a quest and is rewarded, opt is the selected item's index or 0
        virtual void OnQuestReward(Player* /*player*/, Quest const* /*quest*/, uint32 /*opt*/) { }

        /// == Waypoints system =============================

        // virtual void WaypointStarted(uint32 /*nodeId*/, uint32 /*pathId*/) { }
        // virtual void WaypointReached(uint32 /*nodeId*/, uint32 /*pathId*/) { }
        // virtual void WaypointPathEnded(uint32 /*nodeId*/, uint32 /*pathId*/) { }

        /// == Fields =======================================

        virtual void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) { }
        virtual void GetPassengerEnterPosition(Unit* passenger, int8 seatId, Position& pos) { }
        virtual void GetPassengerExitPosition(Unit* passenger, int8 seatId, Position& pos) { }
        virtual void BoardedVehicle(Vehicle* vehicle, int8 seatId, bool apply) { }
        virtual void GetVehicleExitPosition(Vehicle* vehicle, int8 seatId, Position& pos) { }

        virtual void OnSpellClick(Unit* /*clicker*/, bool& /*result*/) { }

        virtual bool CanSeeAlways(WorldObject const* /*obj*/) { return false; }

        // Called when a player is charmed by the creature
        // If a PlayerAI* is returned, that AI is placed on the player instead of the default charm AI
        // Object destruction is handled by Unit::RemoveCharmedBy
        virtual PlayerAI* GetAIForCharmedPlayer(Player* /*who*/) { return nullptr; }

        virtual SpellMissInfo SpellHitResult(Unit* /*attacker*/, SpellInfo const* /*spell*/, Spell const* spellInstance = NULL) { return SPELL_MISS_NONE; }

        // ONLY FOR PET AI
        virtual void SpellRequiresMovement(Unit* target, Spell* spell);
        virtual void OnPetCommand(CommandStates command) { (void)(command); /* Where our fucking UNUSED macro?...*/ }

    protected:
        virtual void MoveInLineOfSight(Unit* /*who*/);

        bool _EnterEvadeMode();

    private:
        bool m_MoveInLineOfSight_locked;
        bool m_canSeeEvenInPassiveMode;
};

enum Permitions
{
    PERMIT_BASE_NO                 = -1,
    PERMIT_BASE_IDLE               = 1,
    PERMIT_BASE_REACTIVE           = 100,
    PERMIT_BASE_PROACTIVE          = 200,
    PERMIT_BASE_FACTION_SPECIFIC   = 400,
    PERMIT_BASE_SPECIAL            = 800
};

#define VEHICLE_CONDITION_CHECK_TIME 1000
#define VEHICLE_DISMISS_TIME 5000

class VehicleAIBase
{
    public:
        explicit VehicleAIBase(Creature* c);
        virtual ~VehicleAIBase();

        void UpdateAI(uint32 const diff);
        void Reset();
        void MoveInLineOfSight(Unit*) { }
        void AttackStart(Unit*) { }
        void OnCharmed(bool apply);

    protected:
        Creature* m_vehicleBase;
        Vehicle* m_vehicle;
        bool m_IsVehicleInUse = false;

        void LoadConditions();
        void CheckConditions(uint32 const diff);
        ConditionList conditions;
        bool m_registered = false;
        uint32 m_ConditionsTimer = VEHICLE_CONDITION_CHECK_TIME;

        bool m_DoDismiss = false;
        uint32 m_DismissTimer = VEHICLE_DISMISS_TIME;

        friend class ConditionMgr;
};

class ChatHandler;

struct SummonablePremiumNpcAI : public CreatureAI
{
    SummonablePremiumNpcAI(Creature* creature, uint32 displayId = 0);

    void UpdateAI(uint32 diff) override { }

    // Just pass a Player* or ChatHandler* instead of this, it will implicitly use the appropriate constructor
    struct PlayerOrChatHandler
    {
        PlayerOrChatHandler(Player* player) : m_player(player) { }
        PlayerOrChatHandler(ChatHandler* handler);

        Player* operator->() const { return m_player; }
        operator Player*() const { return m_player; }

    private:
        Player* m_player;
    };

    static Creature* FindOrSpawn(PlayerOrChatHandler player, uint32 entry);
    static Creature* OpenGossip(PlayerOrChatHandler player, uint32 entry);
    static Creature* OpenGossip(PlayerOrChatHandler player, Creature* creature);
};

#endif
