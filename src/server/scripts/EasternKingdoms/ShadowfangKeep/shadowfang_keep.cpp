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

#include "ScriptPCH.h"
#include "LFGMgr.h"
#include "Group.h"
#include "shadowfang_keep.h"

#define GOSSIP_SENDER_SHADOWFANG_PORT 33

Position shadowfang_keep_locs[] = 
{
    { -224.482f, 2199.782f, 79.761f, 0.376793f },
    { -254.083f, 2283.067f, 74.9995f, 2.481768f },
    { -249.633f, 2261.914f, 100.890f, 4.975412f },
    { -166.63f, 2180.783f, 129.255f, 5.929675f },
};

enum Hummel
{
    FACTION_HOSTILE                  = 14,
    NPC_CRAZED_APOTHECARY            = 36568,
    NPC_VIAL_BUNNY                   = 36530,

    SAY_AGGRO_1                      = 0,
    SAY_AGGRO_2                      = 1,
    SAY_AGGRO_3                      = 2,
    SAY_CALL_BAXTER                  = 3,
    SAY_CALL_FRYE                    = 4,
    SAY_DEATH                        = 5,

    SPELL_ALLURING_PERFUME           = 68589,
    SPELL_ALLURING_PERFUME_SPRAY     = 68607,
    SPELL_IRRESISTIBLE_COLOGNE       = 68946,
    SPELL_IRRESISTIBLE_COLOGNE_SPRAY = 68948,

    SPELL_TABLE_APPEAR               = 69216,
    SPELL_SUMMON_TABLE               = 69218,
    SPELL_CHAIN_REACTION             = 68821,
    SPELL_UNSTABLE_REACTION          = 68957,

    // frye
    SPELL_THROW_PERFUME              = 68799,
    SPELL_THROW_COLOGNE              = 68841,
    SPELL_ALLURING_PERFUME_SPILL     = 68798,
    SPELL_IRRESISTIBLE_COLOGNE_SPILL = 68614,
};

enum Action
{
    START_INTRO,
    START_FIGHT,
    APOTHECARY_DIED,
    SPAWN_CRAZED
};

enum Phase
{
    PHASE_NORMAL,
    PHASE_INTRO
};

enum Talks
{
    TALK_INTRO      = 0,
    TALK_SPECIAL_1  = 1,
    TALK_SPECIAL_2  = 2,
    TALK_SPECIAL_3  = 3,
    TALK_SPECIAL_4  = 4,
    TALK_SPECIAL_5  = 5,
    TALK_SPECIAL_6  = 6,
    TALK_SPECIAL_7  = 7,
    TALK_SPECIAL_8  = 8,
    TALK_SPECIAL_9  = 9,
    TALK_SPECIAL_10 = 10,
    TALK_SPECIAL_11 = 11,
    TALK_SPECIAL_12 = 12,
    TALK_SPECIAL_13 = 13,
    TALK_SPECIAL_14 = 14,
    TALK_SPECIAL_15 = 15,
    TALK_SPECIAL_16 = 16,
    TALK_SPECIAL_17 = 17,
};

enum Actions
{
    ACTION_INTRO      = 0,
    ACTION_SPECIAL_1  = 1,
    ACTION_SPECIAL_2  = 2,
    ACTION_SPECIAL_3  = 3,
    ACTION_PREGODFREY = 4,
};

enum Events
{
    EVENT_INTRO_JUMP = 1,
    EVENT_SPECIAL_1  = 2,
    EVENT_SPECIAL_2  = 3,
    EVENT_SPECIAL_3  = 4,
    EVENT_SPECIAL_4  = 5,
    EVENT_SPECIAL_5  = 6,
    EVENT_SPECIAL_6  = 7,
    EVENT_SPECIAL_7  = 8,
    EVENT_SPECIAL_8  = 9,
    EVENT_SPECIAL_9  = 10,
    EVENT_SPECIAL_10 = 11,
    EVENT_SPECIAL_11 = 12,
    EVENT_SPECIAL_12 = 13,
    EVENT_SPECIAL_13 = 14,
    EVENT_SPECIAL_14 = 15,
    EVENT_SPECIAL_15 = 16,
    EVENT_SPECIAL_16 = 17,
    EVENT_SPECIAL_17 = 18,
    EVENT_SPECIAL_18 = 19,
    EVENT_SPECIAL_19 = 20,
    EVENT_SPECIAL_20 = 21,
};

static Position Loc[]=
{
    // spawn points
    {-215.776443f, 2242.365479f, 79.769257f, 0.0f},
    {-169.500702f, 2219.286377f, 80.613045f, 0.0f},
    {-200.056641f, 2152.635010f, 79.763107f, 0.0f},
    {-238.448242f, 2165.165283f, 89.582985f, 0.0f},
    // moveto points
    {-210.784164f, 2219.004150f, 79.761803f, 0.0f},
    {-198.453400f, 2208.410889f, 79.762474f, 0.0f},
    {-208.469910f, 2167.971924f, 79.764969f, 0.0f},
    {-228.251511f, 2187.282471f, 79.762840f, 0.0f}
};

#define GOSSIP_ITEM_START "Begin the battle."

void SetInCombat(Creature* self)
{
    self->AI()->DoZoneInCombat(self, 150.0f);

    if (!self->IsInCombat())
        self->AI()->EnterEvadeMode();
}

class npc_apothecary_hummel : public CreatureScript
{
    public:
        npc_apothecary_hummel() : CreatureScript("npc_apothecary_hummel") { }

        bool OnGossipHello(Player* player, Creature* creature) override
        {
            if (creature->IsQuestGiver())
                player->PrepareQuestMenu(creature->GetGUID());

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_START, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                creature->AI()->DoAction(START_INTRO);

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        struct npc_apothecary_hummelAI : public ScriptedAI
        {
            npc_apothecary_hummelAI(Creature* creature) : ScriptedAI(creature), _summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            void Reset() override
            {
                me->RestoreFaction();
                me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                _phase = PHASE_NORMAL;
                _step = 0;
                _deadCount = 0;
                _stepTimer = 1500;
                _aggroTimer = 5000;
                _sprayTimer = urand(4000, 7000);
                _chainReactionTimer = urand(10000, 25000);
                _firstCrazed = false;

                me->SetCorpseDelay(900); // delay despawn while still fighting baxter or frye
                _summons.DespawnAll();

                if (!instance)
                    return;

                instance->SetData(DATA_CROWN, NOT_STARTED);

                if (Creature* baxter = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_BAXTER)))
                {
                    if (baxter->IsAlive())
                        baxter->AI()->EnterEvadeMode();
                    else
                        baxter->Respawn();
                }

                if (Creature* frye = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FRYE)))
                {
                    if (frye->IsAlive())
                        frye->AI()->EnterEvadeMode();
                    else
                        frye->Respawn();
                }
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case START_INTRO:
                    {
                        if (Creature* baxter = ObjectAccessor::GetCreature(*me, instance? instance->GetData64(DATA_BAXTER) : 0))
                            baxter->AI()->DoAction(START_INTRO);
                        if (Creature* frye = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_FRYE) : 0))
                            frye->AI()->DoAction(START_INTRO);

                        _phase = PHASE_INTRO;
                        me->SetReactState(REACT_PASSIVE);
                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        SetInCombat(me);
                        break;
                    }
                    case START_FIGHT:
                    {
                        _phase = PHASE_NORMAL;
                        me->SetFaction(FACTION_HOSTILE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        SetInCombat(me);
                        instance->SetData(DATA_CROWN, IN_PROGRESS);
                        break;
                    }
                    case APOTHECARY_DIED:
                    {
                        ++_deadCount;
                        if (_deadCount > 2) // all 3 apothecarys dead, set lootable
                        {
                            _summons.DespawnAll();
                            me->SetCorpseDelay(300); // set delay
                            me->setDeathState(JUST_DIED); // update delay
                            instance->SetData(DATA_CROWN, DONE);
                            me->SetFlag(OBJECT_FIELD_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);

                            instance->DoFinishLFGDungeon(288);
                        }
                        else
                        {
                            if (me->HasFlag(OBJECT_FIELD_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE))
                                me->RemoveFlag(OBJECT_FIELD_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                        }
                        break;
                    }
                    case SPAWN_CRAZED:
                    {
                        uint8 i = urand(0, 3);
                        if (Creature* crazed = me->SummonCreature(NPC_CRAZED_APOTHECARY, Loc[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3*IN_MILLISECONDS))
                        {
                            crazed->SetFaction(FACTION_HOSTILE);
                            crazed->SetReactState(REACT_PASSIVE);
                            crazed->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            crazed->GetMotionMaster()->MovePoint(1, Loc[i + 4]);
                        }

                        if (!_firstCrazed)
                            _firstCrazed = true;
                        break;
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (_phase == PHASE_INTRO)
                {
                    if (_stepTimer <= diff)
                    {
                        ++_step;
                        switch (_step)
                        {
                            case 1:
                            {
                                Talk(SAY_AGGRO_1);
                                _stepTimer = 4000;
                                break;
                            }
                            case 2:
                            {
                                Talk(SAY_AGGRO_2);
                                _stepTimer = 5500;
                                break;
                            }
                            case 3:
                            {
                                Talk(SAY_AGGRO_3);
                                _stepTimer = 1000;
                                break;
                            }
                            case 4:
                            {
                                DoAction(START_FIGHT);
                                break;
                            }
                        }
                    }
                    else
                        _stepTimer -= diff;
                }
                else // PHASE_NORMAL
                {
                    if (!UpdateVictim())
                        return;

                    if (_aggroTimer <= diff)
                    {
                        SetInCombat(me);
                        _aggroTimer = 5000;
                    }
                    else
                        _aggroTimer -= diff;

                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    if (_chainReactionTimer <= diff)
                    {
                        DoCast(me, SPELL_TABLE_APPEAR, true);
                        DoCast(me, SPELL_SUMMON_TABLE, true);
                        DoCast(SPELL_CHAIN_REACTION);
                        _chainReactionTimer = urand(15000, 25000);
                    }
                    else
                        _chainReactionTimer -= diff;

                    if (_sprayTimer <= diff)
                    {
                        DoCastVictim(SPELL_ALLURING_PERFUME_SPRAY);
                        _sprayTimer = urand(8000, 15000);
                    }
                    else
                        _sprayTimer -= diff;

                    DoMeleeAttackIfReady();
                }
            }

            void JustSummoned(Creature* summon) override
            {
                _summons.Summon(summon);
            }

            void JustDied(Unit* /*killer*/) override
            {
                DoAction(APOTHECARY_DIED);
                Talk(SAY_DEATH);
            }

        private:
            InstanceScript* instance;
            SummonList _summons;
            uint8 _deadCount;
            uint8 _phase;
            uint8 _step;
            uint32 _aggroTimer;
            uint32 _stepTimer;
            uint32 _sprayTimer;
            uint32 _chainReactionTimer;
            bool _firstCrazed;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_apothecary_hummelAI>(creature);
        }
};

class npc_apothecary_baxter : public CreatureScript
{
    public:
        npc_apothecary_baxter() : CreatureScript("npc_apothecary_baxter") { }

        struct npc_apothecary_baxterAI : public ScriptedAI
        {
            npc_apothecary_baxterAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            void Reset() override
            {
                me->RestoreFaction();
                _aggroTimer = 5000;
                _waitTimer = 20000;
                _sprayTimer = urand(4000, 7000);
                _chainReactionTimer = urand (10000, 25000);
                _phase = PHASE_NORMAL;

                if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                {
                    if (hummel->IsAlive())
                        hummel->AI()->EnterEvadeMode();
                    else
                        hummel->Respawn();
                }
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case START_INTRO:
                    {
                        _phase = PHASE_INTRO;
                        break;
                    }
                    case START_FIGHT:
                    {
                        if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                            hummel->AI()->Talk(SAY_CALL_BAXTER);

                        _phase = PHASE_NORMAL;
                        me->SetFaction(FACTION_HOSTILE);
                        SetInCombat(me);
                        break;
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (_phase == PHASE_INTRO)
                {
                    if (_waitTimer <= diff)
                    {
                        DoAction(START_FIGHT);
                    }
                    else
                        _waitTimer -= diff;
                }
                else // PHASE_NORMAL
                {
                    if (!UpdateVictim())
                        return;

                    if (_aggroTimer <= diff)
                    {
                        SetInCombat(me);
                        _aggroTimer = 5000;
                    }
                    else
                        _aggroTimer -= diff;

                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    if (_chainReactionTimer <= diff)
                    {
                        DoCast(me, SPELL_TABLE_APPEAR, true);
                        DoCast(me, SPELL_SUMMON_TABLE, true);
                        DoCast(SPELL_CHAIN_REACTION);
                        _chainReactionTimer = urand(15000, 25000);
                    }
                    else
                        _chainReactionTimer -= diff;

                    if (_sprayTimer <= diff)
                    {
                        DoCastVictim(SPELL_IRRESISTIBLE_COLOGNE_SPRAY);
                        _sprayTimer = urand(8000, 15000);
                    }
                    else
                        _sprayTimer -= diff;

                    DoMeleeAttackIfReady();
                }
            }

            void JustDied(Unit* /*killer*/) override
            {
                if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                    hummel->AI()->DoAction(APOTHECARY_DIED);
            }

        private:
            InstanceScript* instance;
            uint32 _chainReactionTimer;
            uint32 _sprayTimer;
            uint32 _aggroTimer;
            uint32 _waitTimer;
            uint8 _phase;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_apothecary_baxterAI>(creature);
        }
};

class npc_apothecary_frye : public CreatureScript
{
    public:
        npc_apothecary_frye() : CreatureScript("npc_apothecary_frye") { }

        struct npc_apothecary_fryeAI : public ScriptedAI
        {
            npc_apothecary_fryeAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            void Reset() override
            {
                me->RestoreFaction();
                _aggroTimer = 5000;
                _waitTimer = 28000;
                _throwTimer = urand(2000, 4000);
                _targetSwitchTimer = urand(1000, 2000);
                _phase = PHASE_NORMAL;

                if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                {
                    if (hummel->IsAlive())
                        hummel->AI()->EnterEvadeMode();
                    else
                        hummel->Respawn();
                }
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case START_INTRO:
                    {
                        _phase = PHASE_INTRO;
                        break;
                    }
                    case START_FIGHT:
                    {
                        if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                            hummel->AI()->Talk(SAY_CALL_FRYE);

                        _phase = PHASE_NORMAL;
                        me->SetFaction(FACTION_HOSTILE);
                        SetInCombat(me);
                        break;
                    }
                }
            }

            void SummonBunny(Unit* target, bool perfume)
            {
                if (!target)
                    return;

                if (Creature* bunny = me->SummonCreature(NPC_VIAL_BUNNY, *target, TEMPSUMMON_TIMED_DESPAWN, 25*IN_MILLISECONDS))
                {
                    bunny->SetFaction(FACTION_HOSTILE);
                    bunny->SetReactState(REACT_PASSIVE);
                    bunny->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE |UNIT_FLAG_NOT_SELECTABLE);
                    bunny->CastSpell(bunny, perfume ? SPELL_ALLURING_PERFUME_SPILL : SPELL_IRRESISTIBLE_COLOGNE_SPILL, true, NULL, NULL, me->GetGUID());
                }
            }

            void SpellHitTarget(Unit* target, const SpellInfo* spell) override
            {
                switch (spell->Id)
                {
                    case SPELL_THROW_PERFUME:
                        SummonBunny(target, true);
                        break;
                    case SPELL_THROW_COLOGNE:
                        SummonBunny(target, false);
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (_phase == PHASE_INTRO)
                {
                    if (_waitTimer <= diff)
                    {
                        DoAction(START_FIGHT);
                    }
                    else
                        _waitTimer -= diff;
                }
                else // PHASE_NORMAL
                {
                    if (!UpdateVictim())
                        return;

                    if (_throwTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, urand(0, 1) ? SPELL_THROW_PERFUME : SPELL_THROW_COLOGNE);
                        _throwTimer = urand(5000, 7500);
                    }
                    else
                        _throwTimer -= diff;

                    if (_targetSwitchTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
                        {
                            me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                            me->AddThreat(target, 9999999.9f);
                        }
                        _targetSwitchTimer = urand(5000, 10000);
                    }
                    else
                        _targetSwitchTimer -= diff;

                    if (_aggroTimer <= diff)
                    {
                        SetInCombat(me);
                        _aggroTimer = 5000;
                    }
                    else
                        _aggroTimer -= diff;

                    DoMeleeAttackIfReady();
                }
            }

            void JustDied(Unit* /*killer*/) override
            {
                if (Creature* hummel = ObjectAccessor::GetCreature(*me, instance ? instance->GetData64(DATA_HUMMEL) : 0))
                    hummel->AI()->DoAction(APOTHECARY_DIED);
            }

        private:
            InstanceScript* instance;
            uint32 _targetSwitchTimer;
            uint32 _throwTimer;
            uint32 _aggroTimer;
            uint32 _waitTimer;
            uint8 _phase;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_apothecary_fryeAI>(creature);
        }
};

class npc_crazed_apothecary : public CreatureScript
{
    public:
        npc_crazed_apothecary() : CreatureScript("npc_crazed_apothecary") { }

        struct npc_crazed_apothecaryAI : public ScriptedAI
        {
            npc_crazed_apothecaryAI(Creature* creature) : ScriptedAI(creature) { }

            void MovementInform(uint32 type, uint32 /*pointId*/) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                DoZoneInCombat(me, 150.0f);

                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                {
                    _explodeTimer = urand (2500, 5000);
                    me->GetMotionMaster()->MoveFollow(target, 0.0f, float(2*M_PI*rand_norm()));
                }
                else
                    me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (_explodeTimer <= diff)
                {
                    DoCast(me, SPELL_UNSTABLE_REACTION);
                }
                else
                    _explodeTimer -= diff;
            }

        private:
            uint32 _explodeTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_crazed_apothecaryAI>(creature);
        }
};

struct shadowfang_follower_typeAI : public ScriptedAI
{
    shadowfang_follower_typeAI(Creature* creature) : ScriptedAI(creature) { }

    EventMap nonCombatEvents;
    InstanceScript* instance;
    bool Intro;

    void InitializeAI() override
    {
        instance = me->GetInstanceScript();
        me->setActive(true);
        Intro = false;
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!Intro && who && who->GetTypeId() == TYPEID_PLAYER && me->GetPositionZ() < 82.47f && me->GetPositionZ() > 79.23f)
        {
            Intro = true;
            Talk(TALK_INTRO);
        }

        ScriptedAI::MoveInLineOfSight(who);
    }

};

// Commander Belmont 47293
class npc_commander_belmont : public CreatureScript
{
    public:
        npc_commander_belmont() : CreatureScript("npc_commander_belmont") { }

        struct npc_commander_belmontAI : public shadowfang_follower_typeAI
        {
            npc_commander_belmontAI(Creature* creature) : shadowfang_follower_typeAI(creature) { }

            void DoAction(int32 actionId) override 
            {
                switch (actionId)
                {
                    case NPC_ASHBURY:
                        nonCombatEvents.ScheduleEvent(EVENT_INTRO_JUMP, 2 * IN_MILLISECONDS);
                        break;
                    case NPC_SILVERLAINE:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_6, 1.5 * IN_MILLISECONDS);
                        break;
                    case NPC_SPRINGVALE:
                    {
                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PastSpringvalePath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_11, me->GetSplineDuration());
                        break;
                    }
                    case NPC_VALDEN:
                    {
                        if (me->GetPositionZ() > 151.0f)
                            break;

                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PastWaldenPath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_14, me->GetSplineDuration() + 2.5 * IN_MILLISECONDS);
                        break;
                    }
                    case ACTION_SPECIAL_1:
                        Talk(TALK_SPECIAL_6);
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_9, 6.5 * IN_MILLISECONDS);
                        break;
                    case ACTION_SPECIAL_2:
                        Talk(TALK_SPECIAL_9);
                        break;
                    case ACTION_PREGODFREY:
                    {
                        me->SetVisible(true);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PreGodfreyPath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_17, me->GetSplineDuration());
                        break;
                    }
                    case ACTION_SPECIAL_3:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_19, 4 * IN_MILLISECONDS);
                        break;
                }
            }

            void MovementInform(uint32 type, uint32 pointId) override
            {
                if (pointId == EVENT_JUMP)
                {
                    me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                    nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_1, 4 * IN_MILLISECONDS);
                }

                if (type != POINT_MOTION_TYPE)
                    return;

                if (pointId == 0)
                    nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_16, 2.5 * IN_MILLISECONDS);
            }

            void UpdateAI(uint32 diff) override
            {
                nonCombatEvents.Update(diff);

                while (uint32 eventId = nonCombatEvents.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO_JUMP:
                            me->GetMotionMaster()->MoveJump(AshberyJumpPos, 20.0f, 20.0f, EVENT_JUMP);
                            break;
                        case EVENT_SPECIAL_1:
                            Talk(TALK_SPECIAL_1);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_2, 10 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_2:
                            Talk(TALK_SPECIAL_2);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_3, 1.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_3:
                        {
                            Movement::MoveSplineInit init(me);
                            for (auto itr : PastAshberyPath)
                                init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                            init.SetSmooth();
                            init.SetUncompressed();
                            init.Launch();
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_4, me->GetSplineDuration());
                            break;
                        }
                        case EVENT_SPECIAL_4:
                            Talk(TALK_SPECIAL_3);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_5, 3.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_5:
                            Talk(TALK_SPECIAL_4);

                            if (instance)
                            {
                                instance->SetBossState(DATA_ASHBURY, DONE);
                                instance->SaveToDB();
                            }
                            break;
                        case EVENT_SPECIAL_6:
                            Talk(TALK_SPECIAL_5);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_7, 5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_7:
                            if (Creature* Kromush = me->FindNearestCreature(NPC_CROMUSH, 30.0f, true))
                                Kromush->AI()->DoAction(ACTION_INTRO);

                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_8, 2.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_8:
                            Talk(TALK_SPECIAL_6);
                            break;
                        case EVENT_SPECIAL_9:
                            Talk(TALK_SPECIAL_7);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_10, 3 * IN_MILLISECONDS);

                            if (Creature* Kromush = me->FindNearestCreature(NPC_CROMUSH, 30.0f, true))
                                Kromush->AI()->DoAction(ACTION_SPECIAL_1);
                            break;
                        case EVENT_SPECIAL_10:
                            Talk(TALK_SPECIAL_8);
                            break;
                        case EVENT_SPECIAL_11:
                            Talk(TALK_SPECIAL_10);
                            me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_12, 3 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_12:
                            Talk(TALK_SPECIAL_11);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_13, 6 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_13:
                            me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                            break;
                        case EVENT_SPECIAL_14:
                            Talk(TALK_SPECIAL_12);

                            if (Creature* Kromush = me->FindNearestCreature(NPC_CROMUSH, 30.0f, true))
                                Kromush->AI()->DoAction(ACTION_SPECIAL_2);

                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_15, 15 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_15:
                            Talk(TALK_SPECIAL_13);
                            me->GetMotionMaster()->MovePoint(0, WaldenExitPos);
                            break;
                        case EVENT_SPECIAL_16:
                            me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));

                            if (instance)
                            {
                                instance->SetBossState(DATA_VALDEN, DONE);
                                instance->SaveToDB();
                            }
                            break;
                        case EVENT_SPECIAL_17:
                            Talk(TALK_SPECIAL_14);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_18, 8 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_18:
                            Talk(TALK_SPECIAL_15);

                            if (Creature* Kromush = me->FindNearestCreature(NPC_CROMUSH, 10.0f, true))
                                Kromush->AI()->DoAction(ACTION_SPECIAL_3);
                            break;
                        case EVENT_SPECIAL_19:
                            Talk(TALK_SPECIAL_16);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_20, 8 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_20:
                            Talk(TALK_SPECIAL_17);
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_commander_belmontAI(creature);
        }
};

// Packleader Ivar 47006
class npc_packleader_ivar : public CreatureScript
{
    public:
        npc_packleader_ivar() : CreatureScript("npc_packleader_ivar") { }

        struct npc_packleader_ivarAI : public shadowfang_follower_typeAI
        {
            npc_packleader_ivarAI(Creature* creature) : shadowfang_follower_typeAI(creature) { }

            void DoAction(int32 actionId) override
            {
                switch (actionId)
                {
                    case NPC_ASHBURY:
                        nonCombatEvents.ScheduleEvent(EVENT_INTRO_JUMP, 2 * IN_MILLISECONDS);
                        break;
                    case NPC_SILVERLAINE:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_6, 1.5 * IN_MILLISECONDS);
                        break;
                    case NPC_SPRINGVALE:
                    {
                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PastSpringvalePath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_7, me->GetSplineDuration());
                        break;
                        break;
                    }
                    case NPC_VALDEN:
                    {
                        if (me->GetPositionZ() > 151.0f)
                            break;

                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PastWaldenPath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_8, me->GetSplineDuration() + 2.5 * IN_MILLISECONDS);
                        break;
                    }
                    case ACTION_PREGODFREY:
                    {
                        me->SetVisible(true);
                        Movement::MoveSplineInit init(me);
                        for (auto itr : PreGodfreyPath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetSmooth();
                        init.SetUncompressed();
                        init.Launch();
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_12, me->GetSplineDuration());
                        break;
                    }
                }
            }

            void MovementInform(uint32 type, uint32 pointId) override
            {
                switch (pointId)
                {
                    case EVENT_JUMP:
                        me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_1, 4 * IN_MILLISECONDS);
                        break;
                    case EVENT_JUMP + 1:
                        me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                        break;
                }

                if (type != POINT_MOTION_TYPE)
                    return;

                if (pointId == 0)
                {
                    Talk(TALK_SPECIAL_9);
                    nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_11, 2 * IN_MILLISECONDS);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                nonCombatEvents.Update(diff);

                while (uint32 eventId = nonCombatEvents.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO_JUMP:
                            me->GetMotionMaster()->MoveJump(AshberyJumpPos, 20.0f, 20.0f, EVENT_JUMP);
                            break;
                        case EVENT_SPECIAL_1:
                            Talk(TALK_SPECIAL_1);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_2, 4 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_2:
                            Talk(TALK_SPECIAL_2);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_3, 6.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_3:
                            Talk(TALK_SPECIAL_3);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_4, 10 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_4:
                        {
                            Talk(TALK_SPECIAL_4);

                            Movement::MoveSplineInit init(me);
                            for (auto itr : PastAshberyPath)
                                init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                            init.SetSmooth();
                            init.SetUncompressed();
                            init.Launch();
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_5, me->GetSplineDuration());
                            break;
                        }
                        case EVENT_SPECIAL_5:
                            Talk(TALK_SPECIAL_5);

                            if (instance)
                            {
                                instance->SetBossState(DATA_ASHBURY, DONE);
                                instance->SaveToDB();
                            }
                            break;
                        case EVENT_SPECIAL_6:
                            me->GetMotionMaster()->MoveJump(SilverlainaTablePos, 15.0f, 10.0f, EVENT_JUMP + 1);
                            break;
                        case EVENT_SPECIAL_7:
                            Talk(TALK_SPECIAL_6);
                            me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                            me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            break;
                        case EVENT_SPECIAL_8:
                            Talk(TALK_SPECIAL_7);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_9, 4.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_9:
                            Talk(TALK_SPECIAL_8);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_10, 6 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_10:
                            me->GetMotionMaster()->MovePoint(0, WaldenExitPos);
                            break;
                        case EVENT_SPECIAL_11:
                            me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));

                            if (instance)
                            {
                                instance->SetBossState(DATA_VALDEN, DONE);
                                instance->SaveToDB();
                            }
                            break;
                        case EVENT_SPECIAL_12:
                            Talk(TALK_SPECIAL_10);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_13, 5.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_13:
                            Talk(TALK_SPECIAL_11);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_14, 5.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_14:
                            Talk(TALK_SPECIAL_12);
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_packleader_ivarAI(creature);
        }
};

// High Warlord Cromush 47294
class npc_high_warlord_cromush : public CreatureScript
{
    public:
        npc_high_warlord_cromush() : CreatureScript("npc_high_warlord_cromush") { }

        struct npc_high_warlord_cromushAI : public ScriptedAI
        {
            npc_high_warlord_cromushAI(Creature* creature) : ScriptedAI(creature) { }

            EventMap nonCombatEvents;
            InstanceScript* instance;

            void InitializeAI() override
            {
                instance = me->GetInstanceScript();
                me->setActive(true);
            }

            void DoAction(int32 actionId) override
            {
                switch (actionId)
                {
                    case ACTION_INTRO:
                        me->SetVisible(true);
                        nonCombatEvents.ScheduleEvent(EVENT_INTRO_JUMP, 6.5 * IN_MILLISECONDS);
                        break;
                    case ACTION_SPECIAL_1:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_1, 5 * IN_MILLISECONDS);
                        break;
                    case ACTION_SPECIAL_2:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_5, 4.5 * IN_MILLISECONDS);
                        break;
                    case ACTION_SPECIAL_3:
                        nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_6, 5 * IN_MILLISECONDS);
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                nonCombatEvents.Update(diff);

                while (uint32 eventId = nonCombatEvents.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO_JUMP:
                            Talk(TALK_INTRO);

                            if (Creature* Belmont = me->FindNearestCreature(NPC_BELMONT, 30.0f, true))
                                Belmont->AI()->DoAction(ACTION_SPECIAL_1);
                            break;
                        case EVENT_SPECIAL_1:
                            Talk(TALK_SPECIAL_1);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_2, 4 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_2:
                            Talk(TALK_SPECIAL_2);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_3, 5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_3:
                            Talk(TALK_SPECIAL_3);
                            nonCombatEvents.ScheduleEvent(EVENT_SPECIAL_4, 3.5 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPECIAL_4:
                            if (Creature* Belmont = me->FindNearestCreature(NPC_BELMONT, 30.0f, true))
                                Belmont->AI()->DoAction(ACTION_SPECIAL_2);
                            break;
                        case EVENT_SPECIAL_5:
                            me->SetVisible(true);
                            Talk(TALK_SPECIAL_4);
                            break;
                        case EVENT_SPECIAL_6:
                            Talk(TALK_SPECIAL_5);

                            if (instance)
                                if (Creature* m_follower = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FOLLOWER)))
                                    m_follower->AI()->DoAction(ACTION_SPECIAL_3);
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_high_warlord_cromushAI(creature);
        }
};

// Sourcerous Skeleton 47140
class npc_sourcerous_skeleton : public CreatureScript
{
    public:
        npc_sourcerous_skeleton() : CreatureScript("npc_sourcerous_skeleton") { }

        enum iSpells
        {
            SPELL_FROSTBOLT   = 15497,
            SPELL_LIVING_BOMB = 91563,
        };

        enum iEvents
        {
            EVENT_FROSTBOLT   = 1,
            EVENT_LIVING_BOMG = 2,
        };

        struct npc_sourcerous_skeletonAI : public ScriptedAI
        {
            npc_sourcerous_skeletonAI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;
            InstanceScript* instance;

            void InitializeAI() override
            {
                instance = me->GetInstanceScript();
                me->setActive(true);
            }

            void EnterCombat(Unit* /*who*/) override
            {
                events.ScheduleEvent(EVENT_FROSTBOLT, urand(3 * IN_MILLISECONDS, 4 * IN_MILLISECONDS));

                if (IsHeroic())
                    events.ScheduleEvent(EVENT_LIVING_BOMG, 2 * IN_MILLISECONDS);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FROSTBOLT:
                            if (Unit* vict = me->GetVictim())
                                DoCast(vict, SPELL_FROSTBOLT);

                            events.ScheduleEvent(EVENT_FROSTBOLT, urand(3 * IN_MILLISECONDS, 4 * IN_MILLISECONDS));
                            break;
                        case EVENT_LIVING_BOMG:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_LIVING_BOMB);
                            else if (Unit* target = me->GetVictim())
                                DoCast(target, SPELL_LIVING_BOMB);

                            events.ScheduleEvent(EVENT_LIVING_BOMG, 10 * IN_MILLISECONDS);
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_sourcerous_skeletonAI(creature);
        }
};

// Stone Sleeper 3870
class npc_stone_sleeper : public CreatureScript
{
    public:
        npc_stone_sleeper() : CreatureScript("npc_stone_sleeper") { }

        enum iSpells
        {
            SPELL_FEAR = 30615,
        };

        enum iEvents
        {
            EVENT_FEAR = 1,
        };

        struct npc_stone_sleeperAI : public ScriptedAI
        {
            npc_stone_sleeperAI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;
            InstanceScript* instance;
            bool hasActivated;

            void InitializeAI() override
            {
                instance = me->GetInstanceScript();
                me->setActive(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                hasActivated = false;
                Reset();
            }

            void Reset() override
            {
                me->HandleEmoteStateCommand(EMOTE_STATE_SUBMERGED_NEW);
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/) override
            {
                me->HandleEmoteStateCommand(EMOTE_STATE_NONE);
                events.ScheduleEvent(EVENT_FEAR, urand(3 * IN_MILLISECONDS, 4 * IN_MILLISECONDS));
            }

            void DoAction(int32 actionId) override
            {
                if (actionId == START_INTRO && !hasActivated)
                {
                    hasActivated = true;
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                    DoZoneInCombat();
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    if (eventId == EVENT_FEAR)
                    {
                        events.ScheduleEvent(EVENT_FEAR, urand(8 * IN_MILLISECONDS, 11 * IN_MILLISECONDS));
                    }
                    break;
                }

                DoMeleeAttackIfReady();

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_stone_sleeperAI(creature);
        }
};

// Dread Scryer 47141
class npc_dread_scryer : public CreatureScript
{
    public:
        npc_dread_scryer() : CreatureScript("npc_dread_scryer") { }

        enum iSpells
        {
            SPELL_CONE_OF_COLD     = 12611,
            // Heroic
            SPELL_ENHACE_MAGIC     = 91624,
            SPELL_ARCANE_EXPLOSION = 91623,
            SPELL_ARCANE_BARRAGE   = 91622,
        };

        enum iEvents
        {
            EVENT_CONE_OF_COLD     = 1,
            EVENT_ENCH_MAGIC       = 2,
            EVENT_ARCANE_EXPLOSION = 3,
            EVENT_ARCANE_BARRAGE   = 4,
        };

        struct npc_dread_scryerAI : public ScriptedAI
        {
            npc_dread_scryerAI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;
            InstanceScript* instance;

            void InitializeAI() override
            {
                instance = me->GetInstanceScript();
                me->setActive(true);
                Reset();
            }

            void Reset() override
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/) override
            {
                events.ScheduleEvent(EVENT_CONE_OF_COLD, urand(3 * IN_MILLISECONDS, 4 * IN_MILLISECONDS));

                if (IsHeroic())
                {
                    events.ScheduleEvent(EVENT_ARCANE_EXPLOSION, 8 * IN_MILLISECONDS);
                    events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(10 * IN_MILLISECONDS, 13.5 * IN_MILLISECONDS));
                    events.ScheduleEvent(EVENT_ENCH_MAGIC, 5 * IN_MILLISECONDS);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CONE_OF_COLD:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_CONE_OF_COLD);
                            else if (Unit* target = me->GetVictim())
                                DoCast(target, SPELL_CONE_OF_COLD);

                            events.ScheduleEvent(EVENT_CONE_OF_COLD, urand(6.5 * IN_MILLISECONDS, 11.5 * IN_MILLISECONDS));
                            break;
                        case EVENT_ARCANE_BARRAGE:
                            DoCastAOE(SPELL_ARCANE_BARRAGE);
                            events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(10 * IN_MILLISECONDS, 13.5 * IN_MILLISECONDS));
                            break;
                        case EVENT_ARCANE_EXPLOSION:
                            DoCast(me, SPELL_ARCANE_EXPLOSION);
                            events.ScheduleEvent(EVENT_ARCANE_EXPLOSION, 8 * IN_MILLISECONDS);
                            break;
                        case EVENT_ENCH_MAGIC:
                            DoCast(me, SPELL_ENHACE_MAGIC);
                            events.ScheduleEvent(EVENT_ENCH_MAGIC, 15 * IN_MILLISECONDS);
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_dread_scryerAI(creature);
        }
};
        
class npc_haunted_stable_hand_portal : public CreatureScript
{
    public:
        npc_haunted_stable_hand_portal() : CreatureScript("npc_haunted_stable_hand_portal") { }

        bool OnGossipHello(Player* player, Creature* creature) override
        {
            bool ru = player->GetSession()->GetSessionDbLocaleIndex() == LOCALE_ruRU;

            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(DATA_VALDEN) == DONE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ru ? "Отправиться в нижнюю обсерваторию." : "Teleport to Lower Observatory.", GOSSIP_SENDER_SHADOWFANG_PORT, 3);
                else if (instance->GetBossState(DATA_SPRINGVALE) == DONE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ru ? "Отправиться во внутренний двор." : "Teleport to The Courtyard.", GOSSIP_SENDER_SHADOWFANG_PORT, 2);
                else if (instance->GetBossState(DATA_SILVERLAINE) == DONE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ru ? "Отправиться в обеденный зал." : "Teleport to Dining Hall.", GOSSIP_SENDER_SHADOWFANG_PORT, 1);
                else if (instance->GetBossState(DATA_ASHBURY) == DONE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ru ? "Отправиться во внутренний двор." : "Teleport to The Courtyard.", GOSSIP_SENDER_SHADOWFANG_PORT, 0);
            }

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();

            if (action >= 4)
                return false;

            Position loc = shadowfang_keep_locs[action];
            if (!player->IsInCombat())
                player->NearTeleportTo(loc.GetPositionX(), loc.GetPositionY(), loc.GetPositionZ(), loc.GetOrientation(), false);
            return true;
        }
};

// AreaTriggers shadowfang keep 255
class AreaTrigger_at_shadowfang_keep : public AreaTriggerScript
{
    public:
        AreaTrigger_at_shadowfang_keep() : AreaTriggerScript("AreaTrigger_at_shadowfang_keep") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger) override
        {
            std::list<Creature*> m_GarguleList;
            GetCreatureListWithEntryInGrid(m_GarguleList, player, NPC_STONE_SLEEPER, 10.0f);

            if (!m_GarguleList.empty())
                for (auto m_gargule : m_GarguleList)
                    if (m_gargule->AI())
                        m_gargule->AI()->DoAction(START_INTRO);

            return false;
        }
};

// AreaTriggers shadowfang keep 6431
class AreaTrigger_at_shadowfang_keep_godfrey : public AreaTriggerScript
{
    public:
        AreaTrigger_at_shadowfang_keep_godfrey() : AreaTriggerScript("AreaTrigger_at_shadowfang_keep_godfrey") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger) override
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                // we can`t select this creature with findnearest cuz dist between this creature > then dist between creature at walden
                if (Creature* m_follower = ObjectAccessor::GetCreature(*player, instance->GetData64(DATA_FOLLOWER)))
                    m_follower->AI()->DoAction(ACTION_PREGODFREY);
            }

            return false;
        }
};

void AddSC_shadowfang_keep()
{
    new npc_apothecary_hummel();
    new npc_apothecary_baxter();
    new npc_apothecary_frye();
    new npc_crazed_apothecary();
    new npc_commander_belmont();
    new npc_packleader_ivar();
    new npc_high_warlord_cromush();
    new npc_sourcerous_skeleton();
    new npc_stone_sleeper();
    new npc_dread_scryer();
    new npc_haunted_stable_hand_portal();
    new AreaTrigger_at_shadowfang_keep();
    new AreaTrigger_at_shadowfang_keep_godfrey();
}
