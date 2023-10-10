#include "ScriptPCH.h"

enum mount_spell
{
    MOUNT_SPELL_MASTER_RIDING = 90265,
    MOUNT_SPELL_JOURNEYMAN_RIDING = 33392,
    MOUNT_SPELL_COLD_WEATHER_RIDING = 54197,
    MOUNT_SPELL_FLIGHT_MASTER_LICENSE = 90267,
    MOUNT_SPELL_TIGER_RIDING = 828,
    MOUNT_SPELL_CLOUD_SERPENT = 130487,
    MOUNT_SPELL_WISDOM_OF_FOUR_WINDS = 115913,
    MOUNT_SPELL_ARTISAN_RIDING = 34091,
    MOUNT_SPELL_EXPERT_RIDING = 34090,
    MOUNT_SPELL_APPRENTICE_RIDING = 33388
};

enum item_id
{
    REINS_OF_THE_WHITE_POLAR_BEAR = 43962,
    ILLUSIONARY_BAG = 54444,
    TOME_OF_CLEAR_MIND = 79249
};

uint32 paladin_glyphs[] =
{
    115936,
    55113,
    55125,
    55109,
    59428,
    58242,
    59427,
    55114,
    55118,
    63865,
    55003,
    55123,
    63867,
    63869,
    55117,
    55111,
    147850,
    63871,
    55110,
    58243,
    63868,
    147973,
    115932,
    55121,
    63870,
    55124,
    55115,
    59429,
    119478,
    55122,
    58247,
    55119,
    115935,
    93467,
    58246,
    122029,
    58244,
    55120,
    58245,
    55116,
    55112,
    115924,
    147851,
    63866
};

uint32 shaman_glyphs[] =
{
    148100,
    58260,
    55540,
    55561,
    55562,
    63925,
    148084,
    55538,
    55542,
    63927,
    101051,
    101051,
    148080,
    55537,
    58261,
    63903,
    148083,
    148079,
    55554,
    55553,
    58264,
    148082,
    55545,
    55560,
    55559,
    148081,
    55547,
    55539,
    55544,
    55551,
    59287,
    58263,
    63902,
    63904,
    55558,
    58265,
    55535,
    55546,
    63929,
    55552,
    147855,
    62133,
    148106,
    55541,
    147854,
    63926,
    55548
};

uint32 warrior_glyphs[] =
{
    58278,
    148107,
    58276,
    58280,
    94375,
    58398,
    58392,
    58403,
    58389,
    58279,
    58390,
    58399,
    68163,
    58395,
    58407,
    58409,
    58406,
    63951,
    123780,
    147858,
    58394,
    148114,
    63945,
    148113,
    58391,
    63950,
    147859,
    58397,
    63949,
    122014,
    58404,
    58281,
    148108,
    63952,
    112792,
    58400,
    89814,
    94373,
    58405,
    58277,
    58402,
    63948,
    58408,
    112793
};

uint32 hunter_glyphs[] =
{
    87839,
    63858,
    58234,
    63857,
    56885,
    56883,
    126703,
    58186,
    56872,
    63856,
    56879,
    56871,
    56889,
    58188,
    87835,
    148477,
    56887,
    56882,
    56884,
    87805,
    58229,
    63854,
    56878,
    126798,
    56877,
    56880,
    87922,
    56870,
    56874,
    148482,
    56886,
    124417,
    56876,
    58232,
    56873,
    126699,
    87813,
    56869,
    63855,
    124415,
    56881,
    63741,
    56875
};

uint32 rogue_glyphs[] =
{
    57142,
    58258,
    57298,
    91300,
    57140,
    57293,
    63899,
    63901,
    57141,
    63897,
    58254,
    57148,
    57149,
    57297,
    57146,
    57109,
    63898,
    58259,
    57299,
    89759,
    57144,
    63878,
    57303,
    58257,
    57147,
    63880,
    57302,
    148077,
    57300,
    57304,
    63879,
    57145,
    148075,
    57296,
    57150,
    58255,
    57295,
    58256
};

uint32 monk_glyphs[] =
{
    125894,
    125903,
    123392,
    125679,
    125874,
    124971,
    125672,
    123404,
    123024,
    125161,
    120478,
    125661,
    125670,
    125756,
    120481,
    120480,
    125152,
    124147,
    125155,
    124990,
    123406,
    125675,
    123762,
    125654,
    123390,
    125739,
    120197,
    119725,
    125677,
    120484,
    123395,
    123400,
    125932,
    125170,
    132006
};

uint32 druid_glyphs[] =
{
    63740,
    94391,
    63739,
    54870,
    58159,
    58140,
    58161,
    59218,
    63715,
    63717,
    54859,
    54863,
    54876,
    54877,
    54866,
    54867,
    54868,
    54875,
    94387,
    94384,
    147969,
    54856,
    54874,
    54858,
    62161,
    95213,
    54854,
    54872,
    94389,
    147968,
    54869,
    54873,
    54857,
    58163,
    131151,
    67599,
    54860,
    63718,
    54864,
    62134,
    54865,
    63714,
    58158
};

uint32 mage_glyphs[] =
{
    87805,
    89748,
    58240,
    58239,
    56596,
    56601,
    58237,
    56589,
    63862,
    89927,
    147970,
    56600,
    56592,
    58235,
    63859,
    87839,
    63860,
    61206,
    56542,
    63863,
    87835,
    56597,
    147971,
    56602,
    56591,
    56593,
    56547,
    62127,
    56599,
    87837,
    56546,
    87922,
    58238,
    98396,
    147972,
    56594,
    87813,
    63864,
    70938,
    56544,
    56587,
    58241,
    62353
};

uint32 warlock_glyphs[] =
{
    56286,
    63930,
    63933,
    63932,
    58273,
    63937,
    56291,
    56299,
    63943,
    56270,
    56289,
    56293,
    56268,
    135560,
    56288,
    56285,
    56301,
    58275,
    58271,
    56283,
    56282,
    56302,
    56271,
    56294,
    63941,
    56297,
    58274,
    70948,
    56292,
    58267,
    56284,
    56290,
    63938,
    58272
};

uint32 priest_glyphs[] =
{
    58251,
    63874,
    56179,
    58248,
    56183,
    56171,
    56163,
    56178,
    58252,
    56177,
    63876,
    126695,
    56166,
    56168,
    112660,
    126684,
    56167,
    56172,
    148071,
    56175,
    63875,
    112637,
    56165,
    56164,
    56174,
    112635,
    56180,
    56182,
    56170,
    107905,
    148073,
    126134,
    126797,
    56176,
    58249,
    63873,
    112636,
    63872,
    63877,
    58250,
    56162,
    147975,
    56169,
    56181,
    112661,
    58253
};

uint32 deathknight_glyphs[] =
{
    58711,
    58705,
    58722,
    58719,
    53428,
    63953,
    58710,
    63954,
    96281,
    59337,
    63958,
    59313,
    58713,
    58709,
    58721,
    147849,
    58723,
    58716,
    58725,
    58720,
    58708,
    58718,
    59333,
    59312,
    58706,
    59328,
    147845,
    147848,
    59311,
    147965,
    58724,
    147846,
    58715,
    58726,
    58707,
    63961,
    147963
};

uint32 getSize(uint32 size)
{
    return (size / sizeof(uint32));
}

class player_start_spells : public PlayerScript
{
public: player_start_spells() : PlayerScript("player_start_spells") { }

      void OnLogin(Player* player) override
      {
          // if (player->HasAtLoginFlag(AT_LOGIN_FIRST))
          // {
              switch (player->GetClass())
              {
              case CLASS_PALADIN: for (uint8 x = 0; x < getSize(sizeof(paladin_glyphs)); x++) player->LearnSpell(paladin_glyphs[x], false); break;
              case CLASS_SHAMAN: for (uint8 x = 0; x < getSize(sizeof(shaman_glyphs)); x++) player->LearnSpell(shaman_glyphs[x], false); break;
              case CLASS_WARRIOR: for (uint8 x = 0; x < getSize(sizeof(warrior_glyphs)); x++) player->LearnSpell(warrior_glyphs[x], false); break;
              case CLASS_HUNTER: for (uint8 x = 0; x < getSize(sizeof(hunter_glyphs)); x++) player->LearnSpell(hunter_glyphs[x], false); break;
              case CLASS_ROGUE: for (uint8 x = 0; x < getSize(sizeof(rogue_glyphs)); x++) player->LearnSpell(rogue_glyphs[x], false); break;
              case CLASS_MONK: for (uint8 x = 0; x < getSize(sizeof(monk_glyphs)); x++) player->LearnSpell(monk_glyphs[x], false); break;
              case CLASS_DRUID: for (uint8 x = 0; x < getSize(sizeof(druid_glyphs)); x++) player->LearnSpell(druid_glyphs[x], false); break;
              case CLASS_MAGE: for (uint8 x = 0; x < getSize(sizeof(mage_glyphs)); x++) player->LearnSpell(mage_glyphs[x], false); break;
              case CLASS_WARLOCK: for (uint8 x = 0; x < getSize(sizeof(warlock_glyphs)); x++) player->LearnSpell(warlock_glyphs[x], false); break;
              case CLASS_PRIEST: for (uint8 x = 0; x < getSize(sizeof(priest_glyphs)); x++) player->LearnSpell(priest_glyphs[x], false); break;
              case CLASS_DEATH_KNIGHT: for (uint8 x = 0; x < getSize(sizeof(deathknight_glyphs)); x++) player->LearnSpell(deathknight_glyphs[x], false); break;
              }

              player->LearnSpell(MOUNT_SPELL_MASTER_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_JOURNEYMAN_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_COLD_WEATHER_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_FLIGHT_MASTER_LICENSE, false);
              player->LearnSpell(MOUNT_SPELL_TIGER_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_CLOUD_SERPENT, false);
              player->LearnSpell(MOUNT_SPELL_WISDOM_OF_FOUR_WINDS, false);
              player->LearnSpell(MOUNT_SPELL_ARTISAN_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_EXPERT_RIDING, false);
              player->LearnSpell(MOUNT_SPELL_APPRENTICE_RIDING, false);

              player->AddItem(REINS_OF_THE_WHITE_POLAR_BEAR, 1); //Ground
              player->AddItem(ILLUSIONARY_BAG, 4); //
              player->AddItem(TOME_OF_CLEAR_MIND, 200); //
              player->GetMaxSkillValueForLevel();
              player->SaveToDB();
              player->RemoveAtLoginFlag(AT_LOGIN_FIRST);



          //}
      }
};

void AddSC_player_start_spells()
{
    new player_start_spells();
}
