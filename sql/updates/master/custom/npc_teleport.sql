--
SET @ENTRY_ID:=900000,@TEXT_ID:=9000000,@GOSSIP_MENU:=900000,@TRINITYSTRING_ID:=900000;

DELETE FROM `creature_template` WHERE `entry`=@ENTRY_ID;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `VignetteID`, `TrackingQuestID`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES 
(@ENTRY_ID, 0, 0, 0, 0, 0, 0, 0, 47432, 0, 0, 0, 'Teleporter', '0', NULL, NULL, @GOSSIP_MENU, 90, 90, 0, 0, 35, 35, 1, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 'npc_teleport', 0);

DELETE FROM `creature_template_locale` WHERE `entry`=@ENTRY_ID;
INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `FemaleName`, `Title`, `VerifiedBuild`) VALUES 
(@ENTRY_ID, 'deDE', 'Teleporter', '', '', 0),
(@ENTRY_ID, 'zhTW', '傳頌者', '', '', 0),
(@ENTRY_ID, 'zhCN', '传送者', '', '', 0),
(@ENTRY_ID, 'ruRU', 'Телепорт', '', '', 0);


DELETE FROM `npc_text` WHERE `ID`=@TEXT_ID;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `EmoteDelay0_0`, `Emote0_0`, `EmoteDelay0_1`, `Emote0_1`, `EmoteDelay0_2`, `Emote0_2`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `EmoteDelay1_0`, `Emote1_0`, `EmoteDelay1_1`, `Emote1_1`, `EmoteDelay1_2`, `Emote1_2`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `EmoteDelay2_0`, `Emote2_0`, `EmoteDelay2_1`, `Emote2_1`, `EmoteDelay2_2`, `Emote2_2`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `EmoteDelay3_0`, `Emote3_0`, `EmoteDelay3_1`, `Emote3_1`, `EmoteDelay3_2`, `Emote3_2`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `EmoteDelay4_0`, `Emote4_0`, `EmoteDelay4_1`, `Emote4_1`, `EmoteDelay4_2`, `Emote4_2`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `EmoteDelay5_0`, `Emote5_0`, `EmoteDelay5_1`, `Emote5_1`, `EmoteDelay5_2`, `Emote5_2`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `EmoteDelay6_0`, `Emote6_0`, `EmoteDelay6_1`, `Emote6_1`, `EmoteDelay6_2`, `Emote6_2`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `EmoteDelay7_0`, `Emote7_0`, `EmoteDelay7_1`, `Emote7_1`, `EmoteDelay7_2`, `Emote7_2`, `VerifiedBuild`) VALUES 
(@TEXT_ID, 'Greetings, $n.Where would you like to be ported?', NULL, 0, 0, 0, 0, 1, 0, 2, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gossip_menu` WHERE `MenuID`=@GOSSIP_MENU;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`, `VerifiedBuild`) VALUES 
(@GOSSIP_MENU, @TEXT_ID, 0);

DELETE FROM `gossip_menu_option` WHERE `MenuId`=@GOSSIP_MENU;
INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcflag`, `VerifiedBuild`) VALUES 
(@GOSSIP_MENU, 1, 0, 'Shrine of Seven Stars', 0, 1, 1, 0),
(@GOSSIP_MENU, 2, 0, 'Darnassus', 25942, 1, 1, 0),
(@GOSSIP_MENU, 3, 0, 'Exodar', 25943, 1, 1, 0),
(@GOSSIP_MENU, 4, 0, 'Ironforge', 25944, 1, 1, 0),
(@GOSSIP_MENU, 5, 0, 'Stormwind', 25947, 1, 1, 0),
(@GOSSIP_MENU, 6, 0, 'Shrine of Two Moons', 0, 1, 1, 0),
(@GOSSIP_MENU, 7, 0, 'Orgrimmar', 25945, 1, 1, 0),
(@GOSSIP_MENU, 8, 0, 'Silvermoon', 25946, 1, 1, 0),
(@GOSSIP_MENU, 9, 0, 'Thunder Bluff', 25948, 1, 1, 0),
(@GOSSIP_MENU, 10, 0, 'Undercity', 25949, 1, 1, 0),
(@GOSSIP_MENU, 11, 0, 'Dalaran', 0, 1, 1, 0),
(@GOSSIP_MENU, 12, 0, 'Shattrath', 0, 1, 1, 0);

DELETE FROM `gossip_menu_option_locale` WHERE `MenuId`=@GOSSIP_MENU;
INSERT INTO `gossip_menu_option_locale` (`MenuID`, `OptionID`, `Locale`, `OptionText`, `BoxText`) VALUES 
(@GOSSIP_MENU, 1, 'deDE', 'Schrein der Sieben Sterne', ''),
(@GOSSIP_MENU, 1, 'zhTW', '七星廟', ''),
(@GOSSIP_MENU, 1, 'zhCN', '七星殿', ''),
(@GOSSIP_MENU, 6, 'deDE', 'Schrein der Zwei Monde', ''),
(@GOSSIP_MENU, 6, 'zhTW', '雙月廟', ''),
(@GOSSIP_MENU, 6, 'zhCN', '双月殿', ''),
(@GOSSIP_MENU, 11, 'deDE', 'Dalaran', ''),
(@GOSSIP_MENU, 11, 'zhTW', '達拉然', ''),
(@GOSSIP_MENU, 11, 'zhCN', '达拉然', ''),
(@GOSSIP_MENU, 12, 'deDE', 'Shattrath', ''),
(@GOSSIP_MENU, 12, 'zhTW', '沙塔斯城', ''),
(@GOSSIP_MENU, 12, 'zhCN', '达拉然', '');

DELETE FROM `gossip_menu_option_action` WHERE `MenuId`=@GOSSIP_MENU;
INSERT INTO `gossip_menu_option_action` (`MenuId`, `OptionIndex`, `ActionMenuId`, `ActionPoiId`) VALUES 
(@GOSSIP_MENU, 1, 0, 0),
(@GOSSIP_MENU, 2, 0, 0),
(@GOSSIP_MENU, 3, 0, 0),
(@GOSSIP_MENU, 4, 0, 0),
(@GOSSIP_MENU, 5, 0, 0),
(@GOSSIP_MENU, 6, 0, 0),
(@GOSSIP_MENU, 7, 0, 0),
(@GOSSIP_MENU, 8, 0, 0),
(@GOSSIP_MENU, 9, 0, 0),
(@GOSSIP_MENU, 10, 0, 0),
(@GOSSIP_MENU, 11, 0, 0),
(@GOSSIP_MENU, 12, 0, 0);

DELETE FROM `gossip_menu_option_box` WHERE `MenuId`=@GOSSIP_MENU;
INSERT INTO `gossip_menu_option_box` (`MenuId`, `OptionIndex`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextId`) VALUES 
(@GOSSIP_MENU, 0, 0, 0, '', 0),
(@GOSSIP_MENU, 1, 0, 0, '', 0),
(@GOSSIP_MENU, 2, 0, 0, '', 0),
(@GOSSIP_MENU, 3, 0, 0, '', 0),
(@GOSSIP_MENU, 4, 0, 0, '', 0),
(@GOSSIP_MENU, 5, 0, 0, '', 0),
(@GOSSIP_MENU, 6, 0, 0, '', 0),
(@GOSSIP_MENU, 7, 0, 0, '', 0),
(@GOSSIP_MENU, 8, 0, 0, '', 0),
(@GOSSIP_MENU, 9, 0, 0, '', 0),
(@GOSSIP_MENU, 10, 0, 0, '', 0),
(@GOSSIP_MENU, 11, 0, 0, '', 0),
(@GOSSIP_MENU, 12, 0, 0, '', 0);
