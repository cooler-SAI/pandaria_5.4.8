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

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_barov_journal
go_ethereum_prison
go_ethereum_stasis
go_sacred_fire_of_life
go_shrine_of_the_birds
go_southfury_moonstone
go_field_repair_bot_74A
go_orb_of_command
go_resonite_cask
go_tablet_of_madness
go_tablet_of_the_seven
go_tele_to_dalaran_crystal
go_tele_to_violet_stand
go_scourge_cage
go_jotunheim_cage
go_table_theka
go_soulwell
go_bashir_crystalforge
go_ethereal_teleport_pad
go_soulwell
go_dragonflayer_cage
go_tadpole_cage
go_amberpine_outhouse
go_hive_pod
go_gjalerbron_cage
go_large_gjalerbron_cage
go_veil_skith_cage
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObjectAI.h"
#include "Spell.h"
#include "Player.h"
#include "WorldSession.h"

/*######
## go_cat_figurine
######*/

enum CatFigurine
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

class go_cat_figurine : public GameObjectScript
{
public:
    go_cat_figurine() : GameObjectScript("go_cat_figurine") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        player->CastSpell(player, SPELL_SUMMON_GHOST_SABER, true);
        return false;
    }
};

/*######
## go_barov_journal
######*/

class go_barov_journal : public GameObjectScript
{
public:
    go_barov_journal() : GameObjectScript("go_barov_journal") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_TAILORING) && player->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !player->HasSpell(26086))
            player->CastSpell(player, 26095, false);

        return true;
    }
};

/*######
## go_field_repair_bot_74A
######*/

class go_field_repair_bot_74A : public GameObjectScript
{
public:
    go_field_repair_bot_74A() : GameObjectScript("go_field_repair_bot_74A") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_ENGINEERING) && player->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !player->HasSpell(22704))
            player->CastSpell(player, 22864, false);

        return true;
    }
};

/*######
## go_gilded_brazier (Paladin First Trail quest (9678))
######*/

enum GildedBrazier
{
    NPC_STILLBLADE  = 17716,
};

class go_gilded_brazier : public GameObjectScript
{
public:
    go_gilded_brazier() : GameObjectScript("go_gilded_brazier") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        {
            if (player->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* Stillblade = player->SummonCreature(NPC_STILLBLADE, 8106.11f, -7542.06f, 151.775f, 3.02598f, TEMPSUMMON_DEAD_DESPAWN, 60000))
                    Stillblade->AI()->AttackStart(player);
            }
        }
        return true;
    }
};

/*######
## go_orb_of_command
######*/

class go_orb_of_command : public GameObjectScript
{
public:
    go_orb_of_command() : GameObjectScript("go_orb_of_command") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(7761))
            player->CastSpell(player, 23460, true);

        return true;
    }
};

/*######
## go_tablet_of_madness
######*/

class go_tablet_of_madness : public GameObjectScript
{
public:
    go_tablet_of_madness() : GameObjectScript("go_tablet_of_madness") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_ALCHEMY) && player->GetSkillValue(SKILL_ALCHEMY) >= 300 && !player->HasSpell(24266))
            player->CastSpell(player, 24267, false);

        return true;
    }
};

/*######
## go_tablet_of_the_seven
######*/

class go_tablet_of_the_seven : public GameObjectScript
{
public:
    go_tablet_of_the_seven() : GameObjectScript("go_tablet_of_the_seven") { }

    /// @todo use gossip option ("Transcript the Tablet") instead, if Trinity adds support.
    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
            return true;

        if (player->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 15065, false);

        return true;
    }
};

/*#####
## go_jump_a_tron
######*/

class go_jump_a_tron : public GameObjectScript
{
public:
    go_jump_a_tron() : GameObjectScript("go_jump_a_tron") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestStatus(10111) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 33382, true);

        return true;
    }
};

/*######
## go_ethereum_prison
######*/

enum EthereumPrison
{
    SPELL_REP_LC        = 39456,
    SPELL_REP_SHAT      = 39457,
    SPELL_REP_CE        = 39460,
    SPELL_REP_CON       = 39474,
    SPELL_REP_KT        = 39475,
    SPELL_REP_SPOR      = 39476
};

const uint32 NpcPrisonEntry[] =
{
    22810, 22811, 22812, 22813, 22814, 22815,               //good guys
    20783, 20784, 20785, 20786, 20788, 20789, 20790         //bad guys
};

class go_ethereum_prison : public GameObjectScript
{
public:
    go_ethereum_prison() : GameObjectScript("go_ethereum_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        int Random = rand() % (sizeof(NpcPrisonEntry) / sizeof(uint32));

        if (Creature* creature = player->SummonCreature(NpcPrisonEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
        {
            if (!creature->IsHostileTo(player))
            {
                if (FactionTemplateEntry const* pFaction = creature->GetFactionTemplateEntry())
                {
                    uint32 Spell = 0;

                    switch (pFaction->faction)
                    {
                        case 1011: Spell = SPELL_REP_LC; break;
                        case 935: Spell = SPELL_REP_SHAT; break;
                        case 942: Spell = SPELL_REP_CE; break;
                        case 933: Spell = SPELL_REP_CON; break;
                        case 989: Spell = SPELL_REP_KT; break;
                        case 970: Spell = SPELL_REP_SPOR; break;
                    }

                    if (Spell)
                        creature->CastSpell(player, Spell, false);
                    else
                        TC_LOG_ERROR("scripts", "go_ethereum_prison summoned Creature (entry %u) but faction (%u) are not expected by script.", creature->GetEntry(), creature->GetFaction());
                }
            }
        }

        return false;
    }
};

/*######
## go_ethereum_stasis
######*/

const uint32 NpcStasisEntry[] =
{
    22825, 20888, 22827, 22826, 22828
};

class go_ethereum_stasis : public GameObjectScript
{
public:
    go_ethereum_stasis() : GameObjectScript("go_ethereum_stasis") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        int Random = rand() % (sizeof(NpcStasisEntry) / sizeof(uint32));

        player->SummonCreature(NpcStasisEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return false;
    }
};

/*######
## go_resonite_cask
######*/

enum ResoniteCask
{
    NPC_GOGGEROC    = 11920
};

class go_resonite_cask : public GameObjectScript
{
public:
    go_resonite_cask() : GameObjectScript("go_resonite_cask") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            go->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

        return false;
    }
};

/*######
## go_sacred_fire_of_life
######*/

enum SacredFireOfLife
{
    NPC_ARIKARA     = 10882
};

class go_sacred_fire_of_life : public GameObjectScript
{
public:
    go_sacred_fire_of_life() : GameObjectScript("go_sacred_fire_of_life") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            player->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return true;
    }
};

/*######
## go_shrine_of_the_birds
######*/

enum ShrineOfTheBirds
{
    NPC_HAWK_GUARD      = 22992,
    NPC_EAGLE_GUARD     = 22993,
    NPC_FALCON_GUARD    = 22994,
    GO_SHRINE_HAWK      = 185551,
    GO_SHRINE_EAGLE     = 185547,
    GO_SHRINE_FALCON    = 185553
};

class go_shrine_of_the_birds : public GameObjectScript
{
public:
    go_shrine_of_the_birds() : GameObjectScript("go_shrine_of_the_birds") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        uint32 BirdEntry = 0;

        float fX, fY, fZ;
        go->GetClosePoint(fX, fY, fZ, go->GetObjectSize(), INTERACTION_DISTANCE);

        switch (go->GetEntry())
        {
            case GO_SHRINE_HAWK:
                BirdEntry = NPC_HAWK_GUARD;
                break;
            case GO_SHRINE_EAGLE:
                BirdEntry = NPC_EAGLE_GUARD;
                break;
            case GO_SHRINE_FALCON:
                BirdEntry = NPC_FALCON_GUARD;
                break;
        }

        if (BirdEntry)
            player->SummonCreature(BirdEntry, fX, fY, fZ, go->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

        return false;
    }
};

/*######
## go_southfury_moonstone
######*/

enum Southfury
{
    NPC_RIZZLE                  = 23002,
    SPELL_BLACKJACK             = 39865, //stuns player
    SPELL_SUMMON_RIZZLE         = 39866
};

class go_southfury_moonstone : public GameObjectScript
{
public:
    go_southfury_moonstone() : GameObjectScript("go_southfury_moonstone") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        //implicitTarget=48 not implemented as of writing this code, and manual summon may be just ok for our purpose
        //player->CastSpell(player, SPELL_SUMMON_RIZZLE, false);

        if (Creature* creature = player->SummonCreature(NPC_RIZZLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
            creature->CastSpell(player, SPELL_BLACKJACK, false);

        return false;
    }
};

/*######
## go_tele_to_dalaran_crystal
######*/

enum DalaranCrystal
{
    QUEST_LEARN_LEAVE_RETURN    = 12790,
    QUEST_TELE_CRYSTAL_FLAG     = 12845
};

#define GO_TELE_TO_DALARAN_CRYSTAL_FAILED   "This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once."

class go_tele_to_dalaran_crystal : public GameObjectScript
{
public:
    go_tele_to_dalaran_crystal() : GameObjectScript("go_tele_to_dalaran_crystal") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(QUEST_TELE_CRYSTAL_FLAG))
            return false;

        player->GetSession()->SendNotification(GO_TELE_TO_DALARAN_CRYSTAL_FAILED);

        return true;
    }
};

/*######
## go_tele_to_violet_stand
######*/

class go_tele_to_violet_stand : public GameObjectScript
{
public:
    go_tele_to_violet_stand() : GameObjectScript("go_tele_to_violet_stand") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(QUEST_LEARN_LEAVE_RETURN) || player->GetQuestStatus(QUEST_LEARN_LEAVE_RETURN) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }
};

/*######
## go_fel_crystalforge
######*/

#define GOSSIP_FEL_CRYSTALFORGE_TEXT 31000
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN 31001
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Beast for the cost of 10 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Beast for the cost of 50 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN "Use the fel crystalforge to make another purchase."

enum FelCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_BEAST   = 40964,
    SPELL_CREATE_5_FLASK_OF_BEAST   = 40965,
};

class go_fel_crystalforge : public GameObjectScript
{
public:
    go_fel_crystalforge() : GameObjectScript("go_fel_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_TEXT, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_TEXT, go->GetGUID());
                break;
        }
        return true;
    }
};

/*######
## go_bashir_crystalforge
######*/

#define GOSSIP_BASHIR_CRYSTALFORGE_TEXT 31100
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN 31101
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Sorcerer for the cost of 10 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Sorcerer for the cost of 50 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN "Use the bashir crystalforge to make another purchase."

enum BashirCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_SORCERER   = 40968,
    SPELL_CREATE_5_FLASK_OF_SORCERER   = 40970,
};

class go_bashir_crystalforge : public GameObjectScript
{
public:
    go_bashir_crystalforge() : GameObjectScript("go_bashir_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_TEXT, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_TEXT, go->GetGUID());
                break;
        }
        return true;
    }
};

/*######
## matrix_punchograph
######*/

enum MatrixPunchograph
{
    ITEM_WHITE_PUNCH_CARD = 9279,
    ITEM_YELLOW_PUNCH_CARD = 9280,
    ITEM_BLUE_PUNCH_CARD = 9282,
    ITEM_RED_PUNCH_CARD = 9281,
    ITEM_PRISMATIC_PUNCH_CARD = 9316,
    SPELL_YELLOW_PUNCH_CARD = 11512,
    SPELL_BLUE_PUNCH_CARD = 11525,
    SPELL_RED_PUNCH_CARD = 11528,
    SPELL_PRISMATIC_PUNCH_CARD = 11545,
    MATRIX_PUNCHOGRAPH_3005_A = 142345,
    MATRIX_PUNCHOGRAPH_3005_B = 142475,
    MATRIX_PUNCHOGRAPH_3005_C = 142476,
    MATRIX_PUNCHOGRAPH_3005_D = 142696,
};

class go_matrix_punchograph : public GameObjectScript
{
public:
    go_matrix_punchograph() : GameObjectScript("go_matrix_punchograph") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case MATRIX_PUNCHOGRAPH_3005_A:
                if (player->HasItemCount(ITEM_WHITE_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_WHITE_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_YELLOW_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_B:
                if (player->HasItemCount(ITEM_YELLOW_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_YELLOW_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_BLUE_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_C:
                if (player->HasItemCount(ITEM_BLUE_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_BLUE_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_RED_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_D:
                if (player->HasItemCount(ITEM_RED_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_RED_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_PRISMATIC_PUNCH_CARD, true);
                }
                break;
            default:
                break;
        }
        return false;
    }
};

/*######
## go_scourge_cage
######*/

enum ScourgeCage
{
    NPC_SCOURGE_PRISONER = 25610
};

class go_scourge_cage : public GameObjectScript
{
public:
    go_scourge_cage() : GameObjectScript("go_scourge_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (Creature* pNearestPrisoner = go->FindNearestCreature(NPC_SCOURGE_PRISONER, 5.0f, true))
        {
            player->KilledMonsterCredit(NPC_SCOURGE_PRISONER, pNearestPrisoner->GetGUID());
            pNearestPrisoner->DisappearAndDie();
        }

        return true;
    }
};

/*######
## go_arcane_prison
######*/

enum ArcanePrison
{
    QUEST_PRISON_BREAK                  = 11587,
    SPELL_ARCANE_PRISONER_KILL_CREDIT   = 45456
};

class go_arcane_prison : public GameObjectScript
{
public:
    go_arcane_prison() : GameObjectScript("go_arcane_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->GetQuestStatus(QUEST_PRISON_BREAK) == QUEST_STATUS_INCOMPLETE)
        {
            go->SummonCreature(25318, 3485.089844f, 6115.7422188f, 70.966812f, 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
            player->CastSpell(player, SPELL_ARCANE_PRISONER_KILL_CREDIT, true);
            return true;
        }
        return false;
    }
};

/*######
## go_blood_filled_orb
######*/

enum BloodFilledOrb
{
    NPC_ZELEMAR     = 17830

};

class go_blood_filled_orb : public GameObjectScript
{
public:
    go_blood_filled_orb() : GameObjectScript("go_blood_filled_orb") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            player->SummonCreature(NPC_ZELEMAR, -369.746f, 166.759f, -21.50f, 5.235f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return true;
    }
};

/*######
## go_jotunheim_cage
######*/

enum JotunheimCage
{
    NPC_EBON_BLADE_PRISONER_HUMAN   = 30186,
    NPC_EBON_BLADE_PRISONER_NE      = 30194,
    NPC_EBON_BLADE_PRISONER_TROLL   = 30196,
    NPC_EBON_BLADE_PRISONER_ORC     = 30195,

    SPELL_SUMMON_BLADE_KNIGHT_H     = 56207,
    SPELL_SUMMON_BLADE_KNIGHT_NE    = 56209,
    SPELL_SUMMON_BLADE_KNIGHT_ORC   = 56212,
    SPELL_SUMMON_BLADE_KNIGHT_TROLL = 56214
};

class go_jotunheim_cage : public GameObjectScript
{
public:
    go_jotunheim_cage() : GameObjectScript("go_jotunheim_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        Creature* pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_HUMAN, 5.0f, true);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_TROLL, 5.0f, true);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_ORC, 5.0f, true);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_NE, 5.0f, true);
            }
        }
        if (!pPrisoner || !pPrisoner->IsAlive())
            return false;

        pPrisoner->DisappearAndDie();
        player->KilledMonsterCredit(NPC_EBON_BLADE_PRISONER_HUMAN, 0);
        switch (pPrisoner->GetEntry())
        {
            case NPC_EBON_BLADE_PRISONER_HUMAN:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_H, true);
                break;
            case NPC_EBON_BLADE_PRISONER_NE:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_NE, true);
                break;
            case NPC_EBON_BLADE_PRISONER_TROLL:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_TROLL, true);
                break;
            case NPC_EBON_BLADE_PRISONER_ORC:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_ORC, true);
                break;
        }
        return true;
    }
};

enum TableTheka
{
    GOSSIP_TABLE_THEKA = 1653,

    QUEST_SPIDER_GOLD = 2936
};

class go_table_theka : public GameObjectScript
{
public:
    go_table_theka() : GameObjectScript("go_table_theka") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->GetQuestStatus(QUEST_SPIDER_GOLD) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SPIDER_GOLD);

        player->SEND_GOSSIP_MENU(GOSSIP_TABLE_THEKA, go->GetGUID());

        return true;
    }
};

/*######
## go_inconspicuous_landmark
######*/

enum InconspicuousLandmark
{
    SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB    = 11462,
    ITEM_CUERGOS_KEY                                 = 9275,
};

class go_inconspicuous_landmark : public GameObjectScript
{
public:
    go_inconspicuous_landmark() : GameObjectScript("go_inconspicuous_landmark") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasItemCount(ITEM_CUERGOS_KEY))
            return false;

        player->CastSpell(player, SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB, true);

        return true;
    }
};

/*######
## go_ethereal_teleport_pad
######*/

enum EtherealTeleportPad
{
    NPC_IMAGE_WIND_TRADER               = 20518,
    ITEM_TELEPORTER_POWER_PACK          = 28969,
};

class go_ethereal_teleport_pad : public GameObjectScript
{
public:
    go_ethereal_teleport_pad() : GameObjectScript("go_ethereal_teleport_pad") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player->HasItemCount(ITEM_TELEPORTER_POWER_PACK))
            return false;

        go->SummonCreature(NPC_IMAGE_WIND_TRADER, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);

        return true;
    }
};

/*######
## go_soulwell
######*/

class go_soulwell : public GameObjectScript
{
    public:
        go_soulwell() : GameObjectScript("go_soulwell") { }

        struct go_soulwellAI : public GameObjectAI
        {
            go_soulwellAI(GameObject* go) : GameObjectAI(go)
            {
            }

            /// Due to the fact that this GameObject triggers CMSG_GAMEOBJECT_USE
            /// _and_ CMSG_GAMEOBJECT_REPORT_USE, this GossipHello hook is called
            /// twice. The script's handling is fine as it won't remove two charges
            /// on the well. We have to find how to segregate REPORT_USE and USE.
            bool GossipHello(Player* player) override
            {
                Unit* owner = go->GetOwner();
                if (!owner || owner->GetTypeId() != TYPEID_PLAYER || !player->IsInSameRaidWith(owner->ToPlayer()))
                    return true;
                return false;
            }
        };

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new go_soulwellAI(go);
        }
};

/*######
## Quest 11255: Prisoners of Wyrmskull
## go_dragonflayer_cage
######*/

enum PrisonersOfWyrmskull
{
    QUEST_PRISONERS_OF_WYRMSKULL                  = 11255,
    NPC_PRISONER_PRIEST                           = 24086,
    NPC_PRISONER_MAGE                             = 24088,
    NPC_PRISONER_WARRIOR                          = 24089,
    NPC_PRISONER_PALADIN                          = 24090
};

class go_dragonflayer_cage : public GameObjectScript
{
public:
    go_dragonflayer_cage() : GameObjectScript("go_dragonflayer_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_PRISONERS_OF_WYRMSKULL) != QUEST_STATUS_INCOMPLETE)
            return true;

        Creature* pPrisoner = go->FindNearestCreature(NPC_PRISONER_PRIEST, 2.0f);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_PRISONER_MAGE, 2.0f);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_PRISONER_WARRIOR, 2.0f);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_PRISONER_PALADIN, 2.0f);
            }
        }

        if (!pPrisoner || !pPrisoner->IsAlive())
            return true;

        Quest const* qInfo = sObjectMgr->GetQuestTemplate(QUEST_PRISONERS_OF_WYRMSKULL);
        if (qInfo)
        {
            /// @todo prisoner should help player for a short period of time
            player->KilledMonsterCredit(qInfo->GetQuestObjectiveXIndex(0)->ObjectId);
            pPrisoner->DisappearAndDie();
        }
        return true;
    }
};

/*######
## Quest 11560: Oh Noes, the Tadpoles!
## go_tadpole_cage
######*/

enum Tadpoles
{
    QUEST_OH_NOES_THE_TADPOLES                    = 11560,
    NPC_WINTERFIN_TADPOLE                         = 25201
};

class go_tadpole_cage : public GameObjectScript
{
public:
    go_tadpole_cage() : GameObjectScript("go_tadpole_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* pTadpole = go->FindNearestCreature(NPC_WINTERFIN_TADPOLE, 1.0f);
            if (pTadpole)
            {
                pTadpole->DisappearAndDie();
                player->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE, 0);
                //FIX: Summon minion tadpole
            }
        }
        return true;
    }
};

/*######
## go_amberpine_outhouse
######*/

#define GOSSIP_USE_OUTHOUSE "Use the outhouse."
#define GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND "Quest item Anderhol's Slider Cider not found."

enum AmberpineOuthouse
{
    ITEM_ANDERHOLS_SLIDER_CIDER     = 37247,
    NPC_OUTHOUSE_BUNNY              = 27326,
    QUEST_DOING_YOUR_DUTY           = 12227,
    SPELL_INDISPOSED                = 53017,
    SPELL_INDISPOSED_III            = 48341,
    SPELL_CREATE_AMBERSEEDS         = 48330,
    GOSSIP_OUTHOUSE_INUSE           = 12775,
    GOSSIP_OUTHOUSE_VACANT          = 12779
};

class go_amberpine_outhouse : public GameObjectScript
{
public:
    go_amberpine_outhouse() : GameObjectScript("go_amberpine_outhouse") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        QuestStatus status = player->GetQuestStatus(QUEST_DOING_YOUR_DUTY);
        if (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE || status == QUEST_STATUS_REWARDED)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_USE_OUTHOUSE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_VACANT, go->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_INUSE, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF +1)
        {
            player->CLOSE_GOSSIP_MENU();
            Creature* target = GetClosestCreatureWithEntry(player, NPC_OUTHOUSE_BUNNY, 3.0f);
            if (target)
            {
                target->AI()->SetData(1, player->GetGender());
                go->CastSpell(target, SPELL_INDISPOSED_III);
            }
            go->CastSpell(player, SPELL_INDISPOSED);
            if (player->HasItemCount(ITEM_ANDERHOLS_SLIDER_CIDER))
                go->CastSpell(player, SPELL_CREATE_AMBERSEEDS);
            return true;
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification(GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND);
            return false;
        }
    }
};

/*######
## Quest 1126: Hive in the Tower
## go_hive_pod
######*/

enum Hives
{
    QUEST_HIVE_IN_THE_TOWER                       = 9544,
    NPC_HIVE_AMBUSHER                             = 13301
};

class go_hive_pod : public GameObjectScript
{
public:
    go_hive_pod() : GameObjectScript("go_hive_pod") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        player->SendLoot(go->GetGUID(), LOOT_CORPSE);
        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX()+1, go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX(), go->GetPositionY()+1, go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        return true;
    }
};

class go_massive_seaforium_charge : public GameObjectScript
{
    public:
        go_massive_seaforium_charge() : GameObjectScript("go_massive_seaforium_charge") { }

        void OnLootStateChanged(GameObject* go, uint32 state, Unit* /*unit*/)
        {
            if (state == GO_ACTIVATED)
            {
                if (Unit* owner = go->GetOwner())
                    if (Player* achiever = owner->ToPlayer())
                        if (GameObject* wall = go->FindNearestGameObjectOfType(GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING, 15.0f))
                        {
                            if (wall->GetDestructibleState() == GO_DESTRUCTIBLE_DESTROYED)
                                return;

                            TeamId allowed = TEAM_NEUTRAL;
                            switch (wall->GetEntry())
                            {
                                case 195699: case 195698: case 195700: // A gates
                                    allowed = TEAM_HORDE;
                                    break;
                                case 195494: case 195496: case 195495: // H gates
                                    allowed = TEAM_ALLIANCE;
                                    break;
                            }
                            if (achiever->GetTeamId() == allowed)
                                achiever->CastSpell(achiever, go->GetEntry() == 195331 ? 68367 : 68366, true);
                        }

                go->ForcedDespawn();
            }
        }
};

/*######
## go_gjalerbron_cage
######*/

enum OfKeysAndCages
{
    QUEST_ALLIANCE_OF_KEYS_AND_CAGES    = 11231,
    QUEST_HORDE_OF_KEYS_AND_CAGES       = 11265,
    NPC_GJALERBRON_PRISONER             = 24035,
    SAY_FREE                            = 0,
};

class go_gjalerbron_cage : public GameObjectScript
{
    public:
        go_gjalerbron_cage() : GameObjectScript("go_gjalerbron_cage") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            go->UseDoorOrButton();
            if ((player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(QUEST_ALLIANCE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE) ||
                (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(QUEST_HORDE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE))
            {
                if (Creature* prisoner = go->FindNearestCreature(NPC_GJALERBRON_PRISONER, 5.0f))
                {
                    player->KilledMonsterCredit(NPC_GJALERBRON_PRISONER, 0);

                    prisoner->AI()->Talk(SAY_FREE);
                    prisoner->DespawnOrUnsummon(6000);
                }
            }
            return true;
        }
};

/*########
## go_large_gjalerbron_cage
#####*/

class go_large_gjalerbron_cage : public GameObjectScript
{
    public:
        go_large_gjalerbron_cage() : GameObjectScript("go_large_gjalerbron_cage") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            go->UseDoorOrButton();
            if ((player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(QUEST_ALLIANCE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE) ||
                (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(QUEST_HORDE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE))
            {
                std::list<Creature*> prisonerList;
                GetCreatureListWithEntryInGrid(prisonerList, go, NPC_GJALERBRON_PRISONER, INTERACTION_DISTANCE);
                for (std::list<Creature*>::const_iterator itr = prisonerList.begin(); itr != prisonerList.end(); ++itr)
                {
                    player->KilledMonsterCredit(NPC_GJALERBRON_PRISONER, (*itr)->GetGUID());
                    (*itr)->DespawnOrUnsummon(6000);
                    (*itr)->AI()->Talk(SAY_FREE);
                }
            }
            return false;
        }
};

/*########
#### go_veil_skith_cage
#####*/

enum MissingFriends
{
   QUEST_MISSING_FRIENDS    = 10852,
   NPC_CAPTIVE_CHILD        = 22314,
   SAY_FREE_0               = 0,
};

class go_veil_skith_cage : public GameObjectScript
{
    public:
       go_veil_skith_cage() : GameObjectScript("go_veil_skith_cage") { }

       bool OnGossipHello(Player* player, GameObject* go) override
       {
           go->UseDoorOrButton();
           if (player->GetQuestStatus(QUEST_MISSING_FRIENDS) == QUEST_STATUS_INCOMPLETE)
           {
               std::list<Creature*> childrenList;
               GetCreatureListWithEntryInGrid(childrenList, go, NPC_CAPTIVE_CHILD, INTERACTION_DISTANCE);
               for (std::list<Creature*>::const_iterator itr = childrenList.begin(); itr != childrenList.end(); ++itr)
               {
                   player->KilledMonsterCredit(NPC_CAPTIVE_CHILD, (*itr)->GetGUID());
                   (*itr)->DespawnOrUnsummon(5000);
                   (*itr)->GetMotionMaster()->MovePoint(1, go->GetPositionX()+5, go->GetPositionY(), go->GetPositionZ());
                   (*itr)->AI()->Talk(SAY_FREE_0);
                   (*itr)->GetMotionMaster()->Clear();
               }
           }
           return false;
       }
};

/*######
## go_frostblade_shrine
######*/

enum TheCleansing
{
   QUEST_THE_CLEANSING_HORDE      = 11317,
   QUEST_THE_CLEANSING_ALLIANCE   = 11322,
   SPELL_CLEANSING_SOUL           = 43351,
   SPELL_RECENT_MEDITATION        = 61720,
};

class go_frostblade_shrine : public GameObjectScript
{
public:
    go_frostblade_shrine() : GameObjectScript("go_frostblade_shrine") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton(10);
        if (!player->HasAura(SPELL_RECENT_MEDITATION))
            if (player->GetQuestStatus(QUEST_THE_CLEANSING_HORDE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_THE_CLEANSING_ALLIANCE) == QUEST_STATUS_INCOMPLETE)
            {
                player->CastSpell(player, SPELL_CLEANSING_SOUL);
                player->SetStandState(UNIT_STAND_STATE_SIT);
            }
            return true;
    }
};

/*######
## go_midsummer_bonfire
######*/

enum MidsummerBonfire
{
    STAMP_OUT_BONFIRE_QUEST_COMPLETE    = 45458,
};

class go_midsummer_bonfire : public GameObjectScript
{
public:
    go_midsummer_bonfire() : GameObjectScript("go_midsummer_bonfire") { }

    bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 /*action*/) override
    {
        player->CastSpell(player, STAMP_OUT_BONFIRE_QUEST_COMPLETE, true);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }
};

enum RareChests
{
    // Objects
    // Dread Wastes
    GO_WIND_REAVERS_DAGGER_OF_QUICK_STRIKES    = 213962,
    GO_MALIKS_STALWART_SPEAR                   = 213964,
    GO_AMBER_ENCASED_NECKLACE                  = 213966,
    GO_BLADE_OF_THE_PRIME                      = 213967,
    GO_SWARMING_CLEAVER_OF_KA_ROZ              = 213968,
    GO_DISSECTORS_STAFF_OF_MUTATION            = 213969,
    GO_BLOODSOAKED_CHITIN_FRAGMENT             = 213970,
    GO_SWARMKEEPERS_MEDALLION                  = 213971,
    GO_BLADE_OF_THE_POISONED_MIND              = 213972,
    // Krasarang Wilds
    GO_EQUIPMENT_LOCKER                        = 213651,
    GO_PANDAREN_FISHING_SPEAR                  = 213653,
    GO_BARREL_OF_BANANA_INFUSED_RUM            = 214439,
    GO_STACK_OF_PAPERS                         = 214403,
    GO_SAUROK_STONE_TABLET                     = 213750,
    // Jade Forest
    GO_ANCIENT_JINYU_STAFF                     = 213741,
    GO_ANCIENT_PANDAREN_MINING_PICK            = 213364,
    GO_HAMMER_OF_TEN_THUNDERS                  = 213742,
    GO_WODINS_MANTID_SHANKER                   = 213363,
    GO_ANCIENT_PANDAREN_TEA_POT                = 213366,
    GO_LUCKY_PANDAREN_COIN                     = 213368,
    GO_OFFERING_OF_REMEMBRANCE                 = 214338,
    GO_PANDAREN_RITUAL_STONE                   = 213748,
    GO_SHIPS_LOCKER                            = 213362,
    GO_STASH_OF_GEMS                           = 214337,
    GO_CHEST_OF_SUPLIES                        = 214339,
    // The Vieled Stair
    GO_FORGOTTEN_LOCKBOX                       = 214325,
    GO_THE_HAMMER_OF_FOLLY                     = 213845,
    // Townlong Steppes
    GO_YAUNGOL_FIRE_CARRIER                    = 213960,
    GO_ABANDONED_CRATE_OF_GOODS                = 213961,
    GO_AMBER_ENCASED_MOTH                      = 213844,
    GO_FRAGMENT_OF_DREAD                       = 213956,
    GO_HARDENED_SAP_OF_KRI_VESS                = 213959,
    GO_BAG_OF_WU_KAO_SUPPLIES                  = 214175,
    // Valley of the Four Winds
    GO_STAFF_OF_THE_HIDDEN_MASTER              = 213749,
    GO_CACHE_OF_PILFERED_GOODS                 = 213649,
    GO_BOAT_BUILDING_INSTRUCTIONS              = 214340,
    GO_VIRMEN_TREASURE_CHEST                   = 213650,
    // Kun-Lai Summit
    GO_HOZEN_WARRIOR_SPEAR                     = 213768,
    GO_STASH_OF_YAUNGOL_WEAPON                 = 213842,
    GO_SPRITES_CLOTH_CHEST                     = 213751,
    GO_TABLET_OF_REN_YUN                       = 213765,
    GO_ANCIENT_MOGU_TABLET                     = 214438,
    GO_HOZEN_TREASURE_CHEST                    = 213769,
    GO_LOST_ADVENTURERS_BELONGINGS             = 213774,
    GO_MO_MOS_TRASURE_CHEST                    = 214407,
    GO_RIKKTIKS_TINY_CHEST                     = 213793,
    GO_STATUE_OF_XUEN                          = 213771,
    GO_STOLEN_SPIRITE_TREASURE                 = 213770,
    GO_TERRACOTTA_HEAD                         = 213782,

    // Quests
    // Dread Wastes quests
    QUEST_WIND_REAVERS_DAGGER_OF_QUICK_STRIKES = 31666,
    QUEST_MALIKS_STALWART_SPEAR                = 31430,
    QUEST_AMBER_ENCASED_NECKLACE               = 31431,
    QUEST_BLADE_OF_THE_PRIME                   = 31433,
    QUEST_SWARMING_CLEAVER_OF_KA_ROZ           = 31434,
    QUEST_DISSECTORS_STAFF_OF_MUTATION         = 31435,
    QUEST_BLOODSOAKED_CHITIN_FRAGMENT          = 31436,
    QUEST_SWARMKEEPERS_MEDALLION               = 31437,
    QUEST_BLADE_OF_THE_POISONED_MIND           = 31438,
    // Krasarang Wilds quests
    QUEST_EQUIPMENT_LOCKER                     = 31410,
    QUEST_PANDAREN_FISHING_SPEAR               = 31409,
    QUEST_BARREL_OF_BANANA_INFUSED_RUM         = 31411,
    QUEST_STACK_OF_PAPERS                      = 31863,
    QUEST_SAUROK_STONE_TABLET                  = 31408,
    // Jade Forest
    QUEST_ANCIENT_JINYU_STAFF                  = 31402,
    QUEST_ANCIENT_PANDAREN_MINING_PICK         = 31399,
    QUEST_HAMMER_OF_TEN_THUNDERS               = 31403,
    QUEST_WODINS_MANTID_SHANKER                = 31397,
    QUEST_ANCIENT_PANDAREN_TEA_POT             = 31400,
    QUEST_LUCKY_PANDAREN_COIN                  = 31401,
    QUEST_OFFERING_OF_REMEMBRANCE              = 31865,
    QUEST_PANDAREN_RITUAL_STONE                = 31404,
    QUEST_SHIPS_LOCKER                         = 31396,
    QUEST_STASH_OF_GEMS                        = 31866,
    QUEST_CHEST_OF_SUPLIES                     = 31864,
    // The Vieled Stair
    QUEST_FORGOTTEN_LOCKBOX                    = 31867,
    QUEST_THE_HAMMER_OF_FOLLY                  = 31428,
    // Townlong Steppes
    QUEST_YAUNGOL_FIRE_CARRIER                 = 31425,
    QUEST_ABANDONED_CRATE_OF_GOODS             = 31427,
    QUEST_AMBER_ENCASED_MOTH                   = 31426,
    QUEST_FRAGMENT_OF_DREAD                    = 31423,
    QUEST_HARDENED_SAP_OF_KRI_VESS             = 31424,
    QUEST_BAG_OF_WU_KAO_SUPPLIES               = 31466,
    // Valley of the Four Winds
    QUEST_STAFF_OF_THE_HIDDEN_MASTER           = 31407,
    QUEST_CACHE_OF_PILFERED_GOODS              = 31406,
    QUEST_BOAT_BUILDING_INSTRUCTIONS           = 31869,
    QUEST_VIRMEN_TREASURE_CHEST                = 31405,
    // Kun-Lai Summit
    QUEST_HOZEN_WARRIOR_SPEAR                  = 31413,
    QUEST_STASH_OF_YAUNGOL_WEAPON              = 31421,
    QUEST_SPRITES_CLOTH_CHEST                  = 31412,
    QUEST_TABLET_OF_REN_YUN                    = 31417,
    QUEST_ANCIENT_MOGU_TABLET                  = 31420,
    QUEST_HOZEN_TREASURE_CHEST                 = 31414,
    QUEST_LOST_ADVENTURERS_BELONGINGS          = 31418,
    QUEST_MO_MOS_TRASURE_CHEST                 = 31868,
    QUEST_RIKKTIKS_TINY_CHEST                  = 31419,
    QUEST_STATUE_OF_XUEN                       = 31416,
    QUEST_STOLEN_SPIRITE_TREASURE              = 31415,
    QUEST_TERRACOTTA_HEAD                      = 31422,

    // Spells
    SPELL_CHASTIFIED                           = 131924,
};

std::map<uint32, uint32> rareChestsMap =
{
    // Dread Wastes objects
    { GO_WIND_REAVERS_DAGGER_OF_QUICK_STRIKES,    QUEST_WIND_REAVERS_DAGGER_OF_QUICK_STRIKES },
    { GO_MALIKS_STALWART_SPEAR,                   QUEST_MALIKS_STALWART_SPEAR                },
    { GO_AMBER_ENCASED_NECKLACE,                  QUEST_AMBER_ENCASED_NECKLACE               },
    { GO_BLADE_OF_THE_PRIME,                      QUEST_BLADE_OF_THE_PRIME                   },
    { GO_SWARMING_CLEAVER_OF_KA_ROZ,              QUEST_SWARMING_CLEAVER_OF_KA_ROZ           },
    { GO_DISSECTORS_STAFF_OF_MUTATION,            QUEST_DISSECTORS_STAFF_OF_MUTATION         },
    { GO_BLOODSOAKED_CHITIN_FRAGMENT,             QUEST_BLOODSOAKED_CHITIN_FRAGMENT          },
    { GO_SWARMKEEPERS_MEDALLION,                  QUEST_SWARMKEEPERS_MEDALLION               },
    { GO_BLADE_OF_THE_POISONED_MIND,              QUEST_BLADE_OF_THE_POISONED_MIND           },
    // Krasarang Wilds objects
    { GO_EQUIPMENT_LOCKER,                        QUEST_EQUIPMENT_LOCKER                     },
    { GO_PANDAREN_FISHING_SPEAR,                  QUEST_PANDAREN_FISHING_SPEAR               },
    { GO_BARREL_OF_BANANA_INFUSED_RUM,            QUEST_BARREL_OF_BANANA_INFUSED_RUM         },
    { GO_STACK_OF_PAPERS,                         QUEST_STACK_OF_PAPERS                      },
    { GO_SAUROK_STONE_TABLET,                     QUEST_SAUROK_STONE_TABLET                  },
    // Jade Forest
    { GO_ANCIENT_JINYU_STAFF,                     QUEST_ANCIENT_JINYU_STAFF                  },
    { GO_ANCIENT_PANDAREN_MINING_PICK,            QUEST_ANCIENT_PANDAREN_MINING_PICK         },
    { GO_HAMMER_OF_TEN_THUNDERS,                  QUEST_HAMMER_OF_TEN_THUNDERS               },
    { GO_WODINS_MANTID_SHANKER,                   QUEST_WODINS_MANTID_SHANKER                },
    { GO_ANCIENT_PANDAREN_TEA_POT,                QUEST_ANCIENT_PANDAREN_TEA_POT             },
    { GO_LUCKY_PANDAREN_COIN,                     QUEST_LUCKY_PANDAREN_COIN                  },
    { GO_OFFERING_OF_REMEMBRANCE,                 QUEST_OFFERING_OF_REMEMBRANCE              },
    { GO_PANDAREN_RITUAL_STONE,                   QUEST_PANDAREN_RITUAL_STONE                },
    { GO_SHIPS_LOCKER,                            QUEST_SHIPS_LOCKER                         },
    { GO_STASH_OF_GEMS,                           QUEST_STASH_OF_GEMS                        },
    { GO_CHEST_OF_SUPLIES,                        QUEST_CHEST_OF_SUPLIES                     },
    // The Vieled Stair
    { GO_FORGOTTEN_LOCKBOX,                       QUEST_FORGOTTEN_LOCKBOX                    },
    { GO_THE_HAMMER_OF_FOLLY,                     QUEST_THE_HAMMER_OF_FOLLY                  },
    // Townlong Steppes
    { GO_YAUNGOL_FIRE_CARRIER,                    QUEST_YAUNGOL_FIRE_CARRIER                 },
    { GO_ABANDONED_CRATE_OF_GOODS,                QUEST_ABANDONED_CRATE_OF_GOODS             },
    { GO_AMBER_ENCASED_MOTH,                      QUEST_AMBER_ENCASED_MOTH                   },
    { GO_FRAGMENT_OF_DREAD,                       QUEST_FRAGMENT_OF_DREAD                    },
    { GO_HARDENED_SAP_OF_KRI_VESS,                QUEST_HARDENED_SAP_OF_KRI_VESS             },
    { GO_BAG_OF_WU_KAO_SUPPLIES,                  QUEST_BAG_OF_WU_KAO_SUPPLIES               },
    // Valley of the Four Winds
    { GO_STAFF_OF_THE_HIDDEN_MASTER,              QUEST_STAFF_OF_THE_HIDDEN_MASTER           },
    { GO_CACHE_OF_PILFERED_GOODS,                 QUEST_CACHE_OF_PILFERED_GOODS              },
    { GO_BOAT_BUILDING_INSTRUCTIONS,              QUEST_BOAT_BUILDING_INSTRUCTIONS           },
    { GO_VIRMEN_TREASURE_CHEST,                   QUEST_VIRMEN_TREASURE_CHEST                },
    // Kun-Lai Summit
    { GO_HOZEN_WARRIOR_SPEAR,                     QUEST_HOZEN_WARRIOR_SPEAR                  },
    { GO_STASH_OF_YAUNGOL_WEAPON,                 QUEST_STASH_OF_YAUNGOL_WEAPON              },
    { GO_SPRITES_CLOTH_CHEST,                     QUEST_SPRITES_CLOTH_CHEST                  },
    { GO_TABLET_OF_REN_YUN,                       QUEST_TABLET_OF_REN_YUN                    },
    { GO_ANCIENT_MOGU_TABLET,                     QUEST_ANCIENT_MOGU_TABLET                  },
    { GO_HOZEN_TREASURE_CHEST,                    QUEST_HOZEN_TREASURE_CHEST                 },
    { GO_LOST_ADVENTURERS_BELONGINGS,             QUEST_LOST_ADVENTURERS_BELONGINGS          },
    { GO_MO_MOS_TRASURE_CHEST,                    QUEST_MO_MOS_TRASURE_CHEST                 },
    { GO_RIKKTIKS_TINY_CHEST,                     QUEST_RIKKTIKS_TINY_CHEST                  },
    { GO_STATUE_OF_XUEN,                          QUEST_STATUE_OF_XUEN                       },
    { GO_STOLEN_SPIRITE_TREASURE,                 QUEST_STOLEN_SPIRITE_TREASURE              },
    { GO_TERRACOTTA_HEAD,                         QUEST_TERRACOTTA_HEAD                      },
};

class go_pandaria_rare_chests : public GameObjectScript
{
    public:
        go_pandaria_rare_chests() : GameObjectScript("go_pandaria_rare_chests") { }

        bool OnReportUse(Player* player, GameObject* go) override
        {
            if (go->GetEntry() == GO_OFFERING_OF_REMEMBRANCE)
                go->CastSpell(player, SPELL_CHASTIFIED);

            auto itr = rareChestsMap.find(go->GetEntry());
            if (itr != rareChestsMap.end())
            {
                if (player->GetQuestStatus(itr->second) != QUEST_STATUS_REWARDED)
                {
                    if (Quest const* quest = sObjectMgr->GetQuestTemplate(itr->second))
                        player->RewardQuest(quest, 0, player, false);
                    if (GameObjectTemplate const* objectInfo = sObjectMgr->GetGameObjectTemplate(itr->first))
                        if (objectInfo->GetLockId() == 0)
                            player->SendLoot(go->GetGUID(), LOOT_CORPSE);
                }
                else
                {
                    player->SendGameError(GameError::ERR_LOOT_CANT_LOOT_THAT);
                    go->ForcedDespawn();
                }
            }

            return false;
        }
};

// Challenge Orb - 211674
class go_challenge_orb : public GameObjectScript
{
    public:
        go_challenge_orb() : GameObjectScript("go_challenge_orb") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            if (InstanceScript* instance = go->GetInstanceScript())
                if (instance->instance->IsChallengeDungeon() && !instance->IsChallengeModeStarted() && !instance->IsChallengeModeCompleted())
                    player->ADD_GOSSIP_ITEM_DB(13872, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 /*action*/) override
        {
            if (InstanceScript* instance = go->GetInstanceScript())
            {
                // Check difficulty or if Challenge is already started
                if (!instance->instance->IsChallengeDungeon() || instance->IsChallengeModeStarted())
                {
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                go->SetGoState(GO_STATE_ACTIVE);
                go->SetUInt32Value(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_NODESPAWN);
                instance->SetChallengeModeStarted();
                player->CLOSE_GOSSIP_MENU();
            }

            return true;
        }
};

// Memory Wine - 216625
class go_memory_wine : public GameObjectScript
{
    public:
        go_memory_wine() : GameObjectScript("go_memory_wine") { }

        bool OnReportUse(Player* player, GameObject* go) override
        {
            // go sends report use, but not send use
            go->Use(player);
            return true;
        }
};

// 209354, 221545 - Golden Lotus
struct go_golden_lotus : public GameObjectScript
{
    go_golden_lotus() : GameObjectScript("go_golden_lotus") { }

    enum { SPELL_LUCK_OF_THE_LOTUS = 130653, };

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit) override
    {
        if (state == GO_JUST_DEACTIVATED && unit && unit->GetTypeId() == TYPEID_PLAYER)
            unit->CastSpell(unit, SPELL_LUCK_OF_THE_LOTUS, true);
    }
};

class go_sota_seaforium_bomb : public GameObjectScript
{
    public:
        go_sota_seaforium_bomb() : GameObjectScript("go_sota_seaforium_bomb") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            // Disallow interaction if the player can't store the item
            ItemPosCountVec dest;
            InventoryResult result;
            if (player && (result = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 39213, 1)) != EQUIP_ERR_OK) // Massive Seaforium Charge
            {
                player->SendEquipError(result, NULL, NULL, 39213);
                return true;
            }
            return false;
        }
};

void AddSC_go_scripts()
{
    new go_cat_figurine();
    new go_barov_journal();
    new go_field_repair_bot_74A();
    new go_gilded_brazier();
    new go_orb_of_command();
    new go_shrine_of_the_birds();
    new go_southfury_moonstone();
    new go_tablet_of_madness();
    new go_tablet_of_the_seven();
    new go_jump_a_tron();
    new go_ethereum_prison();
    new go_ethereum_stasis();
    new go_resonite_cask();
    new go_sacred_fire_of_life();
    new go_tele_to_dalaran_crystal();
    new go_tele_to_violet_stand();
    new go_fel_crystalforge();
    new go_bashir_crystalforge();
    new go_matrix_punchograph();
    new go_scourge_cage();
    new go_arcane_prison();
    new go_blood_filled_orb();
    new go_jotunheim_cage();
    new go_table_theka();
    new go_inconspicuous_landmark();
    new go_ethereal_teleport_pad();
    new go_soulwell();
    new go_tadpole_cage();
    new go_dragonflayer_cage();
    new go_amberpine_outhouse();
    new go_hive_pod();
    new go_massive_seaforium_charge();
    new go_gjalerbron_cage();
    new go_large_gjalerbron_cage();
    new go_veil_skith_cage();
    new go_frostblade_shrine();
    new go_midsummer_bonfire();
    new go_pandaria_rare_chests();
    new go_challenge_orb();
    new go_memory_wine();
    new go_golden_lotus();
    new go_sota_seaforium_bomb();
}
