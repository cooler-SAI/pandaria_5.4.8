-- Albert Quarksprocket(19721)
DELETE FROM `creature_text` WHERE `CreatureID`=19271;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(19271, 0, 0, 'Thank you all for coming tonight.  Now put your hands together to welcome Shattrath\'s best, Perry Gatner!', 12, 0, 100, 21, 0, 0, 16383, 0, 'Albert Quarksprocket'),
(19271, 1, 0, 'Perry Gatner! What an act!  The cantina is open all night long, so please, stay and enjoy yourselves!', 12, 0, 100, 21, 0, 0, 16384, 0, 'Albert Quarksprocket');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000456,2000000457);
DELETE FROM `waypoint_data` WHERE `id`=65763;
DELETE FROM `waypoint_scripts` WHERE `id` IN (793,794,795,797,799);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (19271,1927100,1927101,1927102,1927103,1927104,1927105,1927106,1927107,1927108,1927109,1927110,1927111,1927112,1927113,1927114,1927115,1927116);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(19271, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 0, 53, 0, 19271, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Data 11 - Start WP'),
(19271, 0, 1, 2, 40, 0, 100, 0, 5, 19271, 0, 0, 0, 54, 13000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP5 - Pause WP'),
(19271, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1.8675, 'Albert Quarksprocket - On Reached WP5 - Set Orientation'),
(19271, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 5000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP5 - Say line 1'),
(19271, 0, 4, 0, 52, 0, 100, 0, 0, 19271, 0, 0, 0, 80, 1927104, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Text over line 1 - Run Script '),
(19271, 0, 5, 6, 40, 0, 100, 0, 10, 19271, 0, 0, 0, 54, 229000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP10 - Stop WP'),
(19271, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP10 - Set Orientation'),
(19271, 0, 7, 0, 38, 0, 100, 0, 2, 2, 0, 0, 0, 87, 1927102, 1927103, 1927113, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2.03774, 'Albert Quarksprocket - On Reached WP26 - Set Orientation'),
(19271, 0, 8, 9, 40, 0, 100, 0, 18, 19271, 0, 0, 0, 54, 15000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP18 - Pause WP'),
(19271, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1.8675, 'Albert Quarksprocket - On Reached WP18 - Set Orientation'),
(19271, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 14000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Reached WP18 - Say line 2'),
(19271, 0, 11, 0, 40, 0, 100, 0, 26, 19271, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 2.03774, 'Albert Quarksprocket - On Reached WP26 - Set Orientation'),
(19271, 0, 12, 0, 38, 0, 100, 0, 3, 3, 0, 0, 0, 87, 1927100, 1927101, 1927111, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Data set 3 3 - Run Random script'),
(19271, 0, 13, 0, 38, 0, 100, 0, 4, 4, 0, 0, 0, 87, 1927105, 1927106, 1927115, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Data set 4 4 - Run Random script'),
(19271, 0, 14, 0, 38, 0, 100, 0, 5, 5, 0, 0, 0, 87, 1927107, 1927108, 1927114, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Data set 5 5 - Run Random script'),
(19271, 0, 15, 0, 38, 0, 100, 0, 6, 6, 0, 0, 0, 87, 1927109, 1927110, 1927112, 1927116, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - On Data set 5 5 - Run Random script'),
(1927100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 15, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 1 - Say Line 15 (Perry Gatner'),
(1927100, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 16, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 1 - Say Line 16 (Perry Gatner'),
(1927101, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 29, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 2 - Say Line 29 (Perry Gatner'),
(1927101, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 30, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 2 - Say Line 30 (Perry Gatner'),
(1927102, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 9, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 3 - Say Line 15 (Perry Gatner'),
(1927102, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 3 - Say Line 16 (Perry Gatner'),
(1927103, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 31, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 3 - Say Line 31 (Perry Gatner'),
(1927103, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 32, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 3 - Say Line 32 (Perry Gatner'),
(1927104, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 4 - Set Orientation'),
(1927104, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 5, 21, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 4 - Play emote Oneshot_applause'),
(1927104, 9, 2, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 4 - Play emote Oneshot_point'),
(1927104, 9, 3, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 0, 5, 21, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 4 - Play emote Oneshot_applause'),
(1927104, 9, 4, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 4 - Set Data 1 1 on Perry Gatner'),
(1927105, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 5 - Say Line 1 (Perry Gatner'),
(1927105, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 5 - Say Line 2 (Perry Gatner'),
(1927106, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 33, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 6 - Say Line 33 (Perry Gatner'),
(1927106, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 34, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 6 - Say Line 34 (Perry Gatner'),
(1927107, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 24, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 7 - Say Line 24 (Perry Gatner'),
(1927107, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 25, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 7 - Say Line 25 (Perry Gatner'),
(1927108, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 35, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 8 - Say Line 35 (Perry Gatner'),
(1927108, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 36, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 8 - Say Line 36 (Perry Gatner'),
(1927109, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 18, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 9 - Say Line 24 (Perry Gatner'),
(1927109, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 19, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 9 - Say Line 25 (Perry Gatner'),
(1927110, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 37, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 10 - Say Line 35 (Perry Gatner'),
(1927110, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 38, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 10 - Say Line 36 (Perry Gatner'),
(1927111, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 39, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 11 - Say Line 39 (Perry Gatner'),
(1927111, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 40, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 11 - Say Line 40 (Perry Gatner'),
(1927112, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 41, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 12 - Say Line 41 (Perry Gatner'),
(1927112, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 42, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 12 - Say Line 42 (Perry Gatner'),
(1927113, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 43, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 13 - Say Line 42 (Perry Gatner'),
(1927113, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 44, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 13 - Say Line 43 (Perry Gatner'),
(1927114, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 45, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 14 - Say Line 44 (Perry Gatner'),
(1927114, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 46, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 14 - Say Line 45 (Perry Gatner'),
(1927115, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 47, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 15 - Say Line 47 (Perry Gatner'),
(1927115, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 48, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 15 - Say Line 48 (Perry Gatner'),
(1927116, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 47, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 16 - Say Line 49 (Perry Gatner'),
(1927116, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 0, 1, 48, 0, 0, 0, 0, 0, 19, 19228, 0, 0, 0, 0, 0, 0, 0, 'Albert Quarksprocket - - Script 16 - Say Line 50 (Perry Gatner');


-- Arelas Brightstar(35604)  Argent Peacekeeper(35589)
SET @GUID:=136684;
SET @EVENT_ID := 119;
DELETE FROM `creature` WHERE `id` IN (35587, 35589);
DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID+5;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawntimesecs_max`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `movement_type`, `npcflag`, `npcflag2`, `unit_flags`, `unit_flags2`, `dynamicflags`, `ScriptName`, `walk_mode`)  VALUES
(@GUID  , 35589, 571, 4395, 4564, 1, 1, 0, 0, 5667.981, 397.8138,  773.5132, 1.648981, 3600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0),
(@GUID+1, 35587, 571, 4395, 4564, 1, 1, 0, 0, 5652.083, 383.7329, 773.6105, 1.648981, 3600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0),
(@GUID+2, 35587, 571, 4395, 4564, 1, 1, 0, 0, 5657.443, 373.4184, 773.7465, 1.648981, 3600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0),
(@GUID+4, 35587, 571, 4395, 4564, 1, 1, 0, 0, 5885.933, 294.0366, 819.1774, 1.648981, 3600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0),
(@GUID+5, 35587, 571, 4395, 4564, 1, 1, 0, 0, 5897.746, 303.434, 819.722, 1.648981, 3600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0);

DELETE FROM `creature_text` WHERE `CreatureID` IN (35589, 35604);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(35589, 0, 0, "The Argent Crusade invites you to test your skills in honorable combat against other heroes of Azeroth at the Argent Tournament.", 12, 0, 100, 0, 0, 0, 35896, 0, "Jaeren Sunsworn"),
(35589, 1, 0, "The champions of the world's great nations have gathered at the Argent Tournament Grounds in northeastern Icecrown to face all challengers.", 12, 0, 100, 0, 0, 0, 35871, 0, "Jaeren Sunsworn"),
(35604, 0, 0, "The Argent Crusade invites you to test your skills in honorable combat against other heroes of Azeroth at the Argent Tournament.", 12, 0, 100, 0, 0, 0, 35896, 0, "Arelas Brightstar"),
(35604, 1, 0, "The champions of the world's great nations have gathered at the Argent Tournament Grounds in northeastern Icecrown to face all challengers.", 12, 0, 100, 0, 0, 0, 35871, 0, "Arelas Brightstar");

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (35604, 3560400, -(@GUID+1), -(@GUID+2), 35589, 3558900, -(@GUID+4), -(@GUID+5)) AND `source_type` IN (0, 9);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(35589, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On Respawn - Set Active"),
(35589, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 35589, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On Respawn - Start WP"),
(35589, 0, 2, 0, 40, 0, 100, 0, 3, 0, 0, 0, 4, 15852, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On WP 3 Reached - Play Sound"),
(35589, 0, 3, 0, 40, 0, 100, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On WP 4 Reached - Say Line 0"),
(35589, 0, 4, 0, 40, 0, 100, 0, 7, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On WP 7 Reached - Say Line 1"),
(35589, 0, 5, 0, 40, 0, 100, 0, 10, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jaeren Sunsworn - On WP 10 Reached - Despawn"),

(-(@GUID+1), 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Respawn - Set Active"),
(-(@GUID+1), 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 355870, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Respawn - Start WP"),
(-(@GUID+1), 0, 2, 0, 40, 0, 100, 0, 10, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On WP 10 Reached - Despawn"),

(-(@GUID+2), 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Repawn - Set Active"),
(-(@GUID+2), 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 355871, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Respawn - Start WP"),
(-(@GUID+2), 0, 2, 0, 40, 0, 100, 0, 9, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On WP 9 Reached - Despawn"),

(35604, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On Spawn - Run Script"),
(35604, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 35604, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On Script - Start WP"),
(35604, 0, 2, 0, 40, 0, 100, 0, 4, 0, 0, 0, 4, 15852, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On WP 4 Reached - Play Sound"),
(35604, 0, 3, 0, 40, 0, 100, 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On WP 5 Reached - Say Line 0"),
(35604, 0, 4, 0, 40, 0, 100, 0, 8, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On WP 8 Reached - Say Line 1"),
(35604, 0, 5, 0, 40, 0, 100, 0, 11, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Arelas Brightstar - On WP 11 Reached - Despawn"),

(-(@GUID+4), 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Respawn - Set Active"),
(-(@GUID+4), 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 355872, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - Respawn - Start WP"),
(-(@GUID+4), 0, 2, 0, 40, 0, 100, 0, 11, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On WP 11 Reached - Despawn"),

(-(@GUID+5), 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On Respawn - Set Active"),
(-(@GUID+5), 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 355873, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - Respawn - Start WP"),
(-(@GUID+5), 0, 2, 0, 40, 0, 100, 0, 11, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Argent Peacekeeper - On WP 11 Reached - Despawn");

DELETE FROM `waypoints` WHERE `entry` IN (35589, 355870, 355871, 35604, 355872, 355873);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(35589, 1, 5668.624, 398.5799, 773.5132, "Jaeren Sunsworn"),
(35589, 2, 5725.442, 462.7153, 760.0244, "Jaeren Sunsworn"),
(35589, 3, 5800.564, 554.6614, 684.1921, "Jaeren Sunsworn"),
(35589, 4, 5833.159, 581.8802, 660.4152, "Jaeren Sunsworn"),
(35589, 5, 5873.917, 632.1146, 656.0275, "Jaeren Sunsworn"),
(35589, 6, 5896.446, 645.3889, 650.6648, "Jaeren Sunsworn"),
(35589, 7, 5910.374, 640.4618, 651.1382, "Jaeren Sunsworn"),
(35589, 8, 5927.374, 649.6198, 652.4438, "Jaeren Sunsworn"),
(35589, 9, 6014.182, 686.1268, 688.915, "Jaeren Sunsworn"),
(35589, 10, 6125.206, 740.4827, 776.0795, "Jaeren Sunsworn"),

(355870, 1, 5652.657, 384.5521, 773.6105, "Argent Peacekeeper"),
(355870, 2, 5717.878, 458.8056, 759.9131, "Argent Peacekeeper"),
(355870, 3, 5793.838, 550.7361, 684.3297, "Argent Peacekeeper"),
(355870, 4, 5826.26, 579.3629, 660.3875, "Argent Peacekeeper"),
(355870, 5, 5867.21, 630.5712, 656.2776, "Argent Peacekeeper"),
(355870, 6, 5898.586, 653.1563, 650.4151, "Argent Peacekeeper"),
(355870, 7, 5904.815, 648.9323, 650.7219, "Argent Peacekeeper"),
(355870, 8, 5921.449, 650.5695, 651.4497, "Argent Peacekeeper"),
(355870, 9, 6010.338, 686.4653, 687.6164, "Argent Peacekeeper"),
(355870, 10, 6121.343, 741.9896, 774.5883, "Argent Peacekeeper"),

(355871, 1, 5724.933, 452.9427, 759.5792, "Argent Peacekeeper"),
(355871, 2, 5797.671, 546.9618, 684.3028, "Argent Peacekeeper"),
(355871, 3, 5832.412, 574.3489, 660.6373, "Argent Peacekeeper"),
(355871, 4, 5872.779, 625.3055, 656.5553, "Argent Peacekeeper"),
(355871, 5, 5891.741, 645.5243, 651.7482, "Argent Peacekeeper"),
(355871, 6, 5900.167, 641.132, 651.4435, "Argent Peacekeeper"),
(355871, 7, 5925.063, 644.234, 652.3946, "Argent Peacekeeper"),
(355871, 8, 6012.224, 683.0504, 687.5056, "Argent Peacekeeper"),
(355871, 9, 6122.473, 737.8837, 775.0331, "Argent Peacekeeper"),

(35604, 1, 5882.346, 359.5052, 805.5128, "Arelas Brightstar"),
(35604, 2, 5870.818, 419.1528, 757.9805, "Arelas Brightstar"),
(35604, 3, 5861.615, 536.6198, 711.2313, "Arelas Brightstar"),
(35604, 4, 5819.368, 565.809, 686.2836, "Arelas Brightstar"),
(35604, 5, 5781.409, 579.5052, 660.2855, "Arelas Brightstar"),
(35604, 6, 5746.75, 605.8246, 659.4515, "Arelas Brightstar"),
(35604, 7, 5714.218, 632.6528, 653.4815, "Arelas Brightstar"),
(35604, 8, 5698.607, 642.5156, 653.6841, "Arelas Brightstar"),
(35604, 9, 5671.431, 657.9653, 673.2984, "Arelas Brightstar"),
(35604, 10, 5635.497, 664.8281, 695.1312, "Arelas Brightstar"),
(35604, 11, 5547.962, 679.8489, 714.7421, "Arelas Brightstar"),

(355872, 1, 5878.808, 349.5903, 805.3762, "Argent Peacekeeper"),
(355872, 2, 5868.299, 406.6215, 761.7755, "Argent Peacekeeper"),
(355872, 3, 5860.884, 526.5018, 711.9791, "Argent Peacekeeper"),
(355872, 4, 5824.564, 558.4792, 688.1653, "Argent Peacekeeper"),
(355872, 5, 5783.678, 573.8768, 660.6657, "Argent Peacekeeper"),
(355872, 6, 5750.437, 598.283, 659.5815, "Argent Peacekeeper"),
(355872, 7, 5717.358, 625.8871, 653.6937, "Argent Peacekeeper"),
(355872, 8, 5702.417, 633.6945, 653.3049, "Argent Peacekeeper"),
(355872, 9, 5678.096, 652.0139, 673.4606, "Argent Peacekeeper"),
(355872, 10, 5642.127, 659.5851, 695.1612, "Argent Peacekeeper"),
(355872, 11, 5557.141, 672.7847, 714.9632, "Argent Peacekeeper"),

(355873, 1, 5889.772, 351.6806, 806.7754, "Argent Peacekeeper"),
(355873, 2, 5880.2, 411.908, 757.5697, "Argent Peacekeeper"),
(355873, 3, 5872.773, 531.5399, 711.2826, "Argent Peacekeeper"),
(355873, 4, 5830.26, 564.6406, 687.3849, "Argent Peacekeeper"),
(355873, 5, 5789.554, 577.5486, 659.9398, "Argent Peacekeeper"),
(355873, 6, 5755.877, 605.9844, 660.134, "Argent Peacekeeper"),
(355873, 7, 5720.882, 632.6962, 653.6631, "Argent Peacekeeper"),
(355873, 8, 5706.856, 640.7604, 654.0797, "Argent Peacekeeper"),
(355873, 9, 5679.256, 661.4375, 673.4254, "Argent Peacekeeper"),
(355873, 10, 5644.36, 668.2396, 695.0526, "Argent Peacekeeper"),
(355873, 11, 5557.845, 682.9636, 714.3047, "Argent Peacekeeper");

DELETE FROM `game_event` WHERE `eventEntry` IN (@EVENT_ID, @EVENT_ID+1);
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `description`) VALUES
(@EVENT_ID, '2011-03-22 00:00:00', '2020-03-22 00:00:00', 60, 5, 'Dalaran: Argent Tournament heralds Horde'),
(@EVENT_ID+1, '2011-03-22 01:00:00', '2020-03-22 00:00:00', 60, 5, 'Dalaran: Argent Tournament heralds Alliance');

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @GUID+0 AND @GUID+2 AND `eventEntry`=@EVENT_ID;
INSERT INTO `game_event_creature` SELECT @EVENT_ID, creature.guid FROM `creature` WHERE creature.guid BETWEEN @GUID+0 AND @GUID+2;
DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @GUID+3 AND @GUID+5 AND `eventEntry`=@EVENT_ID+1;
INSERT INTO `game_event_creature` SELECT @EVENT_ID+1, creature.guid FROM `creature` WHERE creature.guid BETWEEN @GUID+3 AND @GUID+5;

DELETE FROM `db_script_string` WHERE `entry` IN (2000000580,2000000581);
DELETE FROM `waypoint_data` WHERE `id`=75734;
DELETE FROM `waypoint_scripts` WHERE `id` IN (824,825,826);

-- Fenrick Barlowe(27842)
SET @ENTRY := 27842;
SET @SCRIPT1 := 2784201;
SET @SCRIPT2 := 2784202;
-- ================================
-- take random movement off of npc (smartAI will control pathing)
UPDATE `creature` SET `movement_type`=0 WHERE `guid`=87375;
-- * create text into the DB
DELETE FROM `creature_text` WHERE `CreatureID`=27842;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(27842, 0, 0, 'Bat gizzards again for the gnomes tonight...', 12, 1, 100, 1, 0, 0, 27129, 0, 'Fenrick Barlowe text'),
(27842, 0, 1, 'What do they expect, making the bats come in at that angle? Broken necks and gamey bat stew, that\'s what they get.', 12, 1, 100, 1, 0, 0, 27127, 0, 'Fenrick Barlowe text'),
(27842, 0, 2, '\'We like the trees, Fenrick. They provide cover.\' They won\'t let me chop them down, either.', 12, 1, 100, 1, 0, 0, 27126, 0, 'Fenrick Barlowe text'),
(27842, 0, 3, 'I wonder how many reinforcements need to suffer injury before they allow us to chop down these idiotic trees. They\'re costing us a fortune in bats. Maybe I\'ll rig a harness or two...', 12, 33, 100, 1, 0, 0, 27128, 0, 'Fenrick Barlowe text'),
(27842, 1, 0, 'Guards help!', 14, 0, 100, 0, 0, 0, 30163, 0, 'Common Horde Flight Master');

-- create path
-- point 8 reposition to face bat, do text - kneel for 10 seconds
-- point 5 do text - kneel for 10 seconds
DELETE FROM `waypoints` WHERE `entry`=27842;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `point_comment`) VALUES 
(27842, 1, 3246.2, -642.609, 165.239, NULL, 0, 'Fenrick Barlowe path'),
(27842, 2, 3240.42, -645.154, 165.399, NULL, 0, 'Fenrick Barlowe path'),
(27842, 3, 3245.75, -664.935, 166.789, NULL, 0, 'Fenrick Barlowe path'),
(27842, 4, 3250.1, -663.819, 166.789, NULL, 0, 'Fenrick Barlowe path'),
(27842, 5, 3254.69, -661.435, 167.188, NULL, 0, 'Fenrick Barlowe path - kneel here - do text'),
(27842, 6, 3252.36, -659.146, 167.118, NULL, 0, 'Fenrick Barlowe path'),
(27842, 7, 3252.63, -648.746, 165.904, NULL, 0, 'Fenrick Barlowe path'),
(27842, 8, 3249.21, -647.163, 165.7, NULL, 0, 'Fenrick Barlowe path - kneel here - do text');

-- set SAI to npc
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=27842;
-- create scripts for random text, emotes, and pathing
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=27842;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@SCRIPT1,@SCRIPT2);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(27842, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 0, 11, 14252, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Aggro - Summon Creature \'Enraged Felbat\' (No Repeat)'),
(27842, 0, 3, 0, 4, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Aggro - Say Line 1 (No Repeat)'),
(27842, 0, 4, 0, 11, 0, 100, 0, 0, 0, 0, 0, 0, 53, 0, 27842, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Respawn - Start Waypoint (No Repeat)'),
(27842, 0, 5, 0, 40, 0, 100, 0, 5, 27842, 0, 0, 0, 80, 2784201, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Waypoint 5 Reached - Run Script (No Repeat)'),
(27842, 0, 6, 0, 40, 0, 100, 0, 8, 27842, 0, 0, 0, 80, 2784202, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Waypoint 8 Reached - Run Script (No Repeat)'),
(2784201, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 54, 13000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Pause Waypoint'),
(2784201, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Say Line 0'),
(2784201, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Set Flag Standstate Kneel'),
(2784201, 9, 3, 0, 0, 0, 100, 0, 11000, 11000, 0, 0, 0, 91, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Remove Flag Standstate Kneel'),
(2784202, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 54, 14000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Pause Waypoint'),
(2784202, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Say Line 0'),
(2784202, 9, 2, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 10, 108509, 27787, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Set Orientation Closest Creature \'Venomspite Riding Bat\''),
(2784202, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Set Flag Standstate Kneel'),
(2784202, 9, 4, 0, 0, 0, 100, 0, 11000, 11000, 0, 0, 0, 91, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Fenrick Barlowe - On Script - Remove Flag Standstate Kneel');

-- need the following fix also
-- c27787 Venomspite Riding Bat
UPDATE `creature` SET `unit_flags`=`unit_flags`|570688256,`dynamicflags`=`dynamicflags`|32 WHERE `guid` IN (87328,87329);
DELETE FROM `creature_addon` WHERE `guid` IN (87328,87329);
INSERT INTO `creature_addon` (`guid`,`bytes2`,`auras`) VALUES
(87328,1, '29266 0 29266 1'),(87329,1, '29266 0 29266 1');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000074,2000000467,2000000468,2000000469);
DELETE FROM `waypoint_data` WHERE `id`=87375;
DELETE FROM `waypoint_scripts` WHERE `id` IN (818,819);

-- Shattrath Saul(19270)
SET @CGUID := 376098; -- Needs 13 consecutive guids
SET @ANNOUNCEVENT := 62; -- Event for Announces from Shattrath Saul
SET @CONCERTEVENT := 63; -- Event for Actual Concert

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+12 AND  `id` IN(23623,23625,23626,23624,23619,28206,23850,23853,23855,23845,23854,23830,23852);
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawntimesecs_max`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `movement_type`, `npcflag`, `npcflag2`, `unit_flags`, `unit_flags2`, `dynamicflags`, `ScriptName`, `walk_mode`)  VALUES
(@CGUID+0, 23850, 530, 3703, 3899, 1, 1, 0, 0, -1750.72, 5136.825, -36.17796, 2.111848, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23850 (Area: 3899 - Difficulty: 0)
(@CGUID+1, 23853, 530, 3703, 3899, 1, 1, 0, 0, -1749.081, 5137.796, -36.17796, 2.076942, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23853 (Area: 3899 - Difficulty: 0)
(@CGUID+2, 23855, 530, 3703, 3899, 1, 1, 0, 0, -1749.921, 5134.271, -36.17796, 2.042035, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23855 (Area: 3899 - Difficulty: 0)
(@CGUID+3, 23845, 530, 3703, 3899, 1, 1, 0, 0, -1745.396, 5136.415, -36.17797, 2.024582, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23845 (Area: 3899 - Difficulty: 0)
(@CGUID+4, 23854, 530, 3703, 3899, 1, 1, 0, 0, -1752.908, 5136.067, -36.17797, 2.042035, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23854 (Area: 3899 - Difficulty: 0)
(@CGUID+5, 23830, 530, 3703, 3899, 1, 1, 0, 0, -1750.518, 5136.135, -36.17796, 2.076942, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23830 (Area: 3899 - Difficulty: 0)
(@CGUID+6, 23852, 530, 3703, 3899, 1, 1, 0, 0, -1754.977, 5133.365, -36.17797, 1.937315, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), -- 23852 (Area: 3899 - Difficulty: 0)
(@CGUID+7, 23623, 530, 3703, 3899, 1, 1, 0, 0, -1749.92,5134.53,-36.2611,1.85192, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), 
(@CGUID+8, 23625, 530, 3703, 3899, 1, 1, 0, 0, -1749.28,5138.05,-36.2611,1.826, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), 
(@CGUID+9, 23626, 530, 3703, 3899, 1, 1, 0, 0, -1752.7,5136.19,-36.2612,1.80244, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), 
(@CGUID+10, 23624, 530, 3703, 3899, 1, 1, 0, 0, -1755.31,5133.44,-36.2612,1.77574, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), 
(@CGUID+11, 23619, 530, 3703, 3899, 1, 1, 0, 0, -1745.25,5136.43,-36.2613,1.99015, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0), 
(@CGUID+12, 28206, 530, 3703, 3899, 1, 1, 0, 0, -1749.92,5134.53,-36.2611,1.85192, 480, 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0); 

DELETE FROM `game_event` WHERE `eventEntry`IN (@CONCERTEVENT,@ANNOUNCEVENT);
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `holidayStage`, `description`, `world_event`, `announce`) VALUES 
(@CONCERTEVENT, '2010-09-07 21:00:00', '2030-10-10 01:00:00', 180, 6, 0, 0, 'L70 ETC Shattrath', 0, 2),
(@ANNOUNCEVENT, '2010-09-07 20:50:00', '2030-10-10 01:00:00', 180, 16, 0, 0, 'L70 ETC Shattrath Announce', 0, 2);

DELETE FROM `game_event_creature` WHERE `eventEntry`IN (@CONCERTEVENT,@ANNOUNCEVENT);
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES 
(@CONCERTEVENT, @CGUID+0),
(@CONCERTEVENT, @CGUID+1),
(@CONCERTEVENT, @CGUID+2),
(@CONCERTEVENT, @CGUID+3),
(@CONCERTEVENT, @CGUID+4),
(@CONCERTEVENT, @CGUID+5),
(@CONCERTEVENT, @CGUID+6),
(@CONCERTEVENT, @CGUID+7),
(@CONCERTEVENT, @CGUID+8),
(@CONCERTEVENT, @CGUID+9),
(@CONCERTEVENT, @CGUID+10),
(@CONCERTEVENT, @CGUID+11),
(@ANNOUNCEVENT, @CGUID+12);

DELETE FROM `smart_scripts` WHERE `entryorguid`=19270 AND `source_type`=0 AND `id`IN(1,2) AND `link`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(19270, 0, 1, 0, 68, 0, 100, 512, @ANNOUNCEVENT, 0, 0, 0, 0, 80, 1927001, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - On Event Start Run Timed action list'),
(19270, 0, 2, 0, 11, 0, 100, 512, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - On Spawn - Set Active');

DELETE FROM `smart_scripts` WHERE `entryorguid`=1927001 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(1927001, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - Script - Say'),
(1927001, 9, 1, 0, 0, 0, 100, 0, 120000, 120000, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - Script - Say'),
(1927001, 9, 2, 0, 0, 0, 100, 0, 120000, 120000, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - Script - Say'),
(1927001, 9, 3, 0, 0, 0, 100, 0, 120000, 120000, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shattrath Saul - Script - Say');

DELETE FROM `creature_text` WHERE `CreatureID`=19270 AND `GroupID` IN(1,2,3,4) AND `ID`=0;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(19270, 1, 0, "TAUREN CHIEFTAINS! Playing LIVE, in the WORLD'S END TAVERN! Be there, at the top of the hour! Banished from Shattrath? SNEAK BACK IN!", 14, 0, 100, 0, 0, 0, 28504, 2, 'Shattrath Saul'),
(19270, 2, 0, "Are you ready to rock? Then head over to the World's End Tavern! The Tauren Chieftains start their show at the top of the hour.", 14, 0, 100, 0, 0, 0, 28496, 2, 'Shattrath Saul'),
(19270, 3, 0, "Who? The Tauren Chieftains! What? A live performance! Where? The World's End Tavern! When? The top of the hour! BE THERE!", 14, 0, 100, 0, 0, 0, 28502, 2, 'Shattrath Saul'),
(19270, 4, 0, "Now, in Shattrath City: The Tauren Chieftains! Playing in the World's End Tavern at the top of the hour!", 14, 0, 100, 0, 0, 0, 28481, 2, 'Shattrath Saul');

UPDATE `smart_scripts` SET `action_param3`=1 WHERE  `entryorguid`=23830 AND `source_type`=0 AND `id`=0 AND `link`=0;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=23619 AND `source_type`=0 AND `id`=12 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23619 AND `source_type`=0 AND `id`IN(19,20,21) AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23623 AND `source_type`=0 AND `id`IN(20,21,22) AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23624 AND `source_type`=0 AND `id` IN(19,20) AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23626 AND `source_type`=0 AND `id`IN(20,21) AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23625 AND `source_type`=0 AND `id`IN(19,20) AND `link`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(23619, 0, 19, 0, 1, 0, 100, 1, 213000, 213000, 0, 0, 0, 28, 34126, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bergrisst - Out of Combat - Remove \'Spotlight\''),
(23619, 0, 20, 0, 1, 0, 100, 1, 27990, 27990, 0, 0, 0, 28, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bergrisst - Out of Combat - Remove Greater Invisibility'),
(23619, 0, 21, 0, 11, 0, 100, 1, 0, 0, 0, 0, 0, 11, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bergrisst - On Spawn - Cast Greater Invisibility'),
(23625, 0, 19, 0, 1, 0, 100, 1, 9900, 9900, 0, 0, 0, 28, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Samuro - Out of Combat - Remove Greater Invisibility'),
(23625, 0, 20, 0, 11, 0, 100, 1, 0, 0, 0, 0, 0, 11, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Samuro - On Spawn - Cast Greater Invisibility'),
(23623, 0, 20, 0, 1, 0, 100, 1, 23990, 23990, 0, 0, 0, 28, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chief Thunder-Skins - Out of Combat - Remove Greater Invisibility'),
(23623, 0, 21, 0, 11, 0, 100, 1, 0, 0, 0, 0, 0, 11, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chief Thunder-Skins - On Spawn - Cast Greater Invisibility'),
(23623, 0, 22, 0, 1, 0, 100, 1, 23990, 23990, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 19, 28206, 0, 0, 0, 0, 0, 0, 'Chief Thunder-Skins - Out of Combat - Despawn [DND] L70ETC Drums'),
(23624, 0, 19, 0, 1, 0, 100, 1, 12990, 12990, 0, 0, 0, 28, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mai\'Kyl - Out of Combat - Remove Greater Invisibility'),
(23624, 0, 20, 0, 11, 0, 100, 1, 0, 0, 0, 0, 0, 11, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mai\'Kyl - On Spawn - Cast Greater Invisibility'),
(23626, 0, 20, 0, 1, 0, 100, 1, 12990, 12990, 0, 0, 0, 28, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sig Nicious - Out of Combat - Remove Greater Invisibility'),
(23626, 0, 21, 0, 11, 0, 100, 1, 0, 0, 0, 0, 0, 11, 16380, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sig Nicious - On Spawn - Cast Greater Invisibility');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000460,2000000461);
DELETE FROM `waypoint_data` WHERE `id`=78337;
DELETE FROM `waypoint_scripts` WHERE `id` IN (7833701);

-- Sayge(14822)
DELETE FROM `gossip_menu` WHERE (`MenuID`,`TextID`) IN ((6186,7393));
INSERT INTO `gossip_menu` (`MenuID`,`TextID`,`VerifiedBuild`) VALUES
(6186,7393,0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 14 AND `SourceGroup` = 6186;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(14,6186,7339,0,0,1,0,23770,0,0,1,0,0,"","Group 0: Show gossip text 7339 if player does not have aura 'Sayge's Carnie Buff'"),
(14,6186,7393,0,0,1,0,23770,0,0,0,0,0,"","Group 0: Show gossip text 7393 if player does have aura 'Sayge's Carnie Buff'");

UPDATE `gossip_menu_option_action` SET `ActionMenuID` = 6208 WHERE `MenuID` = 6185 AND `OptionIndex` = 1;
UPDATE `gossip_menu_option_action` SET `ActionMenuID` = 6209 WHERE `MenuID` = 6185 AND `OptionIndex` = 2;
UPDATE `gossip_menu_option_action` SET `ActionMenuID` = 6210 WHERE `MenuID` = 6185 AND `OptionIndex` = 3;
UPDATE `gossip_menu_option_action` SET `ActionMenuID` = 6211 WHERE `MenuID` IN (6187,6208,6209,6210);
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID` = 10087 WHERE `MenuID` = 6210 AND `OptionIndex` = 0;
DELETE FROM `gossip_menu_option_action` WHERE `MenuID` = 6211;
INSERT INTO `gossip_menu_option_action` (`MenuID`,`OptionIndex`,`ActionMenuID`) VALUES
(6211,0,6212);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 6186;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,6186,0,0,0,1,0,23770,0,0,1,0,0,"","Group 0: Show Gossip Option 0 if player does not have aura 'Sayge's Carnie Buff'");

-- Sayge SAI
SET @ID := 14822;
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE `entry` = @ID;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ID AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ID,0,0,0,10,0,100,0,1,10,120000,120000,1,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - Within 0-10 Range Out of Combat LoS - Say Line 0"),

(@ID,0,1,14,62,0,100,0,6187,0,0,0,0,11,23768,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 0 Selected - Cast 'Sayge's Dark Fortune of Damage'"),
(@ID,0,2,14,62,0,100,0,6187,1,0,0,0,11,23769,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 1 Selected - Cast 'Sayge's Dark Fortune of Resistance'"),
(@ID,0,3,14,62,0,100,0,6187,2,0,0,0,11,23767,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 2 Selected - Cast 'Sayge's Dark Fortune of Armor'"),

(@ID,0,4,14,62,0,100,0,6208,0,0,0,0,11,23738,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 0 Selected - Cast 'Sayge's Dark Fortune of Spirit'"),
(@ID,0,5,14,62,0,100,0,6208,1,0,0,0,11,23766,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 1 Selected - Cast 'Sayge's Dark Fortune of Intelligence'"),
(@ID,0,6,14,62,0,100,0,6208,2,0,0,0,11,23769,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 2 Selected - Cast 'Sayge's Dark Fortune of Resistance'"),

(@ID,0,7,14,62,0,100,0,6209,0,0,0,0,11,23737,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 0 Selected - Cast 'Sayge's Dark Fortune of Stamina'"),
(@ID,0,8,14,62,0,100,0,6209,1,0,0,0,11,23735,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 1 Selected - Cast 'Sayge's Dark Fortune of Strength'"),
(@ID,0,9,14,62,0,100,0,6209,2,0,0,0,11,23736,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 2 Selected - Cast 'Sayge's Dark Fortune of Agility'"),

(@ID,0,10,14,62,0,100,0,6210,0,0,0,0,11,23766,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 0 Selected - Cast 'Sayge's Dark Fortune of Intelligence'"),
(@ID,0,11,14,62,0,100,0,6210,1,0,0,0,11,23738,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 1 Selected - Cast 'Sayge's Dark Fortune of Spirit'"),
(@ID,0,12,14,62,0,100,0,6210,2,0,0,0,11,23767,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 2 Selected - Cast 'Sayge's Dark Fortune of Armor'"),

(@ID,0,13,0,62,0,100,0,6211,0,0,0,0,11,23765,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Gossip Option 0 Selected - Cast 'Darkmoon Faire Fortune'"),
(@ID,0,14,0,61,0,100,0,0,0,0,0,0,11,23770,0,0,0,0,0,7,0,0,0,0,0,0,0,0,"Sayge - On Link - Cast 'Sayge's Carnie Buff'");

DELETE FROM `creature_text` WHERE `CreatureID` = @ID;
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`,`TextRange`,`comment`) VALUES
(@ID,0,0,"Come to me and see what the future holds for you!",12,0,100,0,0,0,10125,0,"Sayge"),
(@ID,0,1,"Come speak with me, and what once was cloudy shall become crystal clear.",12,0,100,0,0,0,10126,0,"Sayge"),
(@ID,0,2,"Fear not!  All fortunes can be discerned for those who know the way.",12,0,100,0,0,0,10127,0,"Sayge"),
(@ID,0,3,"The longer you wait, the less future you have for me to foretell.",12,0,100,0,0,0,10128,0,"Sayge");

DELETE FROM `db_script_string` WHERE `entry` IN (2000000158,2000000230,2000000237,2000000240);
DELETE FROM `waypoint_data` WHERE `id`=77840;
DELETE FROM `waypoint_scripts` WHERE `id` IN (536);

-- Allerian Defender(18999)
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` = '' WHERE `entry`=18999;
DELETE FROM `creature_text` WHERE `CreatureID` = 18999;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(18999, 0, 0, 'Hey, did you read the bounty on this wanted poster?', 12, 7, 100, 6, 0, 0, 16969, 0, 'Allerian Defender'),
(18999, 0, 1, 'The Bone Wastes!  I don\'t care what\'s being offered as a reward, I\'m not going into the Bone Wastes!', 12, 7, 100, 6, 0, 0, 16972, 0, 'Allerian Defender'),
(18999, 0, 2, 'This wanted poster says that they\'re offering gold to these so-called adventurers to go kill things.  Isn\'t that what we do?  I don\'t think I\'m being paid enough!', 12, 7, 100, 6, 0, 0, 16970, 0, 'Allerian Defender'),
(18999, 0, 3, 'You want to go do the bounty off of this wanted poster after the shift is over?', 12, 7, 100, 6, 0, 0, 16974, 0, 'Allerian Defender'),
(18999, 0, 4, 'This wanted poster has a bounty on bonelashers.  You think I should do that?', 12, 7, 100, 6, 0, 0, 16971, 0, 'Allerian Defender'),
(18999, 1, 0, 'Is that wanted poster all that you\'re going to talk about today?', 12, 7, 100, 1, 0, 0, 16976, 0, 'Allerian Defender'),
(18999, 1, 1, 'I\'m up to looking into that bounty after this shift.', 12, 7, 100, 1, 0, 0, 16977, 0, 'Allerian Defender'),
(18999, 1, 2, 'I could use the extra money.', 12, 7, 100, 1, 0, 0, 16979, 0, 'Allerian Defender'),
(18999, 1, 3, 'I don\'t know and I don\'t care.', 12, 7, 100, 1, 0, 0, 16975, 0, 'Allerian Defender'),
(18999, 1, 4, 'The bonelashers of the wastes are no laughing matter.  I hear they carry diseases!', 12, 7, 100, 1, 0, 0, 16978, 0, 'Allerian Defender');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (18999,1899900);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(18999, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 0, 11, 18396, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Allerian Defender - On Aggro - Cast \'Dismounting Blast\' (Phase 1) (No Repeat) (Dungeon)'),
(1899900, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4.64258, 'Allerian Defender - On Script - Set Orientation 5'),
(1899900, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Allerian Defender - On Script - Say Line 0'),
(1899900, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1.46608, 'Allerian Defender - On Script - Set Orientation 1'),
(1899900, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 10, 68291, 18999, 0, 0, 0, 0, 0, 0, 'Allerian Defender - On Script - Say Line 1');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000210,2000000211);
DELETE FROM `waypoint_data` WHERE `id` IN (74230,74231);
DELETE FROM `waypoint_scripts` WHERE `id` IN (530,531);

-- Silas Darkmoon(14823)
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` = '' WHERE `entry`=14823;
DELETE FROM `creature_text` WHERE `CreatureID` = 14823;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(14823, 0, 0, 'Everyone enjoying themselves so far?  That\'s great!  Welcome to the Darkmoon Faire, the greatest show on all of Azeroth!  Make sure that you speak with Yebb and his friends here while you\'re taking in Neblegear\'s Darkmoon Zoo Bizarre.', 12, 0, 100, 0, 0, 0, 10153, 0, 'Silas Darkmoon'),
(14823, 0, 1, 'Come one, come all.  Welcome to the Darkmoon Faire!  Don\'t be shy.  Step right up to Lhara and buy yourself an exotic artifact from far off lands.  If you\'re one of the lucky few who have found Darkmoon Cards, have a word with Professor Paleo.  Hungry?  Thirsty?  You\'re in luck!  Refreshments are available right here from Sylannia and Stamp.  I recommend the Darkmoon Special Reserve to wash down some Red Hot Wings.  And if the future is what you seek, then run, don\'t walk, to speak with Sayge.', 12, 0, 100, 0, 0, 0, 10154, 0, 'Silas Darkmoon'),
(14823, 0, 2, 'Welcome one and all to the Darkmoon Faire, the greatest event in all the world!  We have it all... delicious food, strong drink, exotic artifacts, fortunes read, amazing prizes and excitement without end!  Don\'t forget to turn in your Darkmoon Faire Prize Tickets to Gelvas Grimegate!  All it takes is five or more and you\'re on your way to the most wondrous prizes on all of Azeroth.  Everybody is a winner!', 12, 0, 100, 0, 0, 0, 10155, 0, 'Silas Darkmoon'),
(14823, 0, 3, 'Welcome one and all to the greatest show on all of Azeroth... the Darkmoon Faire!  Adventure and excitement await, don\'t be shy!  Mysteries and prizes for both the young and the old are here for the taking.  And be sure to speak with the professor about any Darkmoon Cards that you have come across during your travels!', 12, 0, 100, 0, 0, 0, 10156, 0, 'Silas Darkmoon'),
(14823, 0, 4, 'Greetings friends, and welcome to the greatest show on Azeroth!$B$BPlease, step right up and take in all we have to offer.  Ride the rides and see the sights!  Amaze at the wonders that the Darkmoon Faire has uncovered in this vast and mysterious world!  We have spared no expense in bringing you excitement that children of all ages will delight in!', 12, 0, 100, 0, 0, 0, 10157, 0, 'Silas Darkmoon'),
(14823, 0, 5, 'Come one, come all!  Welcome to the Darkmoon Faire!  Do you crave adventure?  Do you seek exotic and mysterious treasures?  Then look no further!  You, my friend, have come to the right place!  Dive right in and take part in all that the Faire has to offer!  We\'ll be at this location all week, so be sure to tell your friends and loved ones!', 12, 0, 100, 0, 0, 0, 10158, 0, 'Silas Darkmoon'),
(14823, 0, 6, 'We\'re back and better than ever!  It\'s the Darkmoon Faire friend, and it\'s your lucky day!  Sparing no expense, we\'ve gathered wonders and treats from around the world for your delight.  Whether you\'re young or old, rich or poor, the Darkmoon Faire has it all!  Be sure to turn in your Darkmoon Faire Prize Tickets to Gelvas Grimegate, and choose from several exotic and wondrous prizes!', 12, 0, 100, 0, 0, 0, 10160, 0, 'Silas Darkmoon'),
(14823, 1, 0, 'Come one, come all.  Welcome to the Darkmoon Faire!  Don\'t be shy.  Step right up to Lhara and buy yourself an exotic artifact from far off lands.  If you\'re one of the lucky few who have found Darkmoon Cards, have a word with Professor Paleo.  Hungry?  Thirsty?  You\'re in luck!  Refreshments are available right here from Sylannia and Stamp.  I recommend the Darkmoon Special Reserve to wash down some Red Hot Wings.  And if the future is what you seek, then run, don\'t walk, to speak with Sayge.', 12, 0, 100, 0, 0, 0, 10154, 0, 'Silas Darkmoon'),
(14823, 1, 1, 'Come one, come all!  Welcome to the Darkmoon Faire!  Do you crave adventure?  Do you seek exotic and mysterious treasures?  Then look no further!  You, my friend, have come to the right place!  Dive right in and take part in all that the Faire has to offer!  We\'ll be at this location all week, so be sure to tell your friends and loved ones!', 12, 0, 100, 0, 0, 0, 10158, 0, 'Silas Darkmoon'),
(14823, 1, 2, 'We\'re back and better than ever!  It\'s the Darkmoon Faire friend, and it\'s your lucky day!  Sparing no expense, we\'ve gathered wonders and treats from around the world for your delight.  Whether you\'re young or old, rich or poor, the Darkmoon Faire has it all!  Be sure to turn in your Darkmoon Faire Prize Tickets to Gelvas Grimegate, and choose from several exotic and wondrous prizes!', 12, 0, 100, 0, 0, 0, 10160, 0, 'Silas Darkmoon'),
(14823, 1, 3, 'Welcome one and all to the greatest show on all of Azeroth... the Darkmoon Faire!  Adventure and excitement await, don\'t be shy!  Mysteries and prizes for both the young and the old are here for the taking.  And be sure to speak with the professor about any Darkmoon Cards that you have come across during your travels!', 12, 0, 100, 0, 0, 0, 22541, 0, 'Silas Darkmoon'),
(14823, 1, 4, 'Greetings friends, and welcome to the greatest show on Azeroth!$B$BPlease, step right up and take in all we have to offer.  Ride the rides and see the sights!  Amaze at the wonders that the Darkmoon Faire has uncovered in this vast and mysterious world!  We have spared no expense in bringing you excitement that children of all ages will delight in!', 12, 0, 100, 0, 0, 0, 22542, 0, 'Silas Darkmoon'),
(14823, 1, 5, 'Everyone enjoying themselves so far?  That\'s great!  Welcome to the Darkmoon Faire, the greatest show in all of Outland!  Make sure that you speak with Yebb and his friends here while you\'re taking in Neblegear\'s Darkmoon Zoo Bizarre.', 12, 0, 100, 0, 0, 0, 22543, 0, 'Silas Darkmoon'),
(14823, 1, 6, 'Welcome one and all to the Darkmoon Faire, the greatest event in all the worlds!  We have it all... delicious food, strong drink, exotic artifacts, fortunes read, amazing prizes and excitement without end!  Don\'t forget to turn in your Darkmoon Faire Prize Tickets to Gelvas Grimegate!  All it takes is five or more and you\'re on your way to the most wondrous prizes in all of Outland.  Everybody is a winner!', 12, 0, 100, 0, 0, 0, 22544, 0, 'Silas Darkmoon');

DELETE FROM `smart_scripts` WHERE `entryorguid`=1482300 AND `source_type`=9 AND `id`=0 AND `link`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(1482300, 9, 0, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Silas Darkmoon - On Script - Say Line 0');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000198,2000000199,2000000232,2000000233);
DELETE FROM `waypoint_data` WHERE `id` IN (4974,303619);
DELETE FROM `waypoint_scripts` WHERE `id` IN (27,28);

-- Flik(14860)
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` = '' WHERE `entry`=14860;
DELETE FROM `creature_text` WHERE `CreatureID` = 14860;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(14860, 0, 0, 'Hey, someone help me catch this thing!', 12, 0, 100, 0, 0, 0, 10145, 0, 'Flik'),
(14860, 0, 1, 'It\'s getting away!', 12, 0, 100, 0, 0, 0, 10146, 0, 'Flik'),
(14860, 0, 2, 'Get back here!', 12, 0, 100, 0, 0, 0, 10147, 0, 'Flik'),
(14860, 0, 3, 'Frogs and leather balls for sale!', 12, 0, 100, 0, 0, 0, 10148, 0, 'Flik');

DELETE FROM `smart_scripts` WHERE `entryorguid`=14860 AND `source_type`=0 AND `id`=0 AND `link`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(14860, 0, 0, 0, 1, 0, 100, 0, 0, 240000, 180000, 240000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Flik - Out of Combat - Say Line 0');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000195,2000000231);
DELETE FROM `waypoint_data` WHERE `id` IN (80927,126119,303637);
DELETE FROM `waypoint_scripts` WHERE `id` IN (566,778);

-- Wretched Captive(16916)
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` = '' WHERE `entry`=16916;
DELETE FROM `creature_text` WHERE `CreatureID` = 16916;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(16916, 0, 0, 'Please!  I must feed on something soon... A mana crystal.... a shard... anything!  The pain is unbearable!', 12, 1, 100, 18, 0, 0, 12835, 0, 'Wretched Captive');

DELETE FROM `smart_scripts` WHERE `entryorguid`=16916 AND `source_type`=0 AND `id`=0 AND `link`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(16916, 0, 0, 0, 1, 0, 100, 0, 6000, 18000, 18000, 18000, 0, 5, 20, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Wretched Captive - OOC - Play Emote 20 \"Beg\"');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000218);
DELETE FROM `waypoint_data` WHERE `id` IN (68292);
DELETE FROM `waypoint_scripts` WHERE `id` IN (490);

-- Novice Ranger(16923)
DELETE FROM `creature_text` WHERE `CreatureID` IN (16916,16923,16924,18926,18929);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(16916, 0, 0, 'Please!  I must feed on something soon... A mana crystal.... a shard... anything!  The pain is unbearable!', 12, 1, 100, 18, 0, 0, 12835, 0, 'Wretched Captive'),
(16923, 0, 0, 'I might just have to go hunting for that Wretched beast now that there\'s a bounty on his head.', 12, 1, 100, 0, 0, 0, 12832, 0, 'Novice Ranger'),
(16924, 0, 0, 'Tell us!  Where does your leader hide?', 12, 1, 100, 0, 0, 0, 12833, 0, 'Sergeant Kan\'\'ren'),
(16924, 1, 0, 'You\'re not getting anything until you speak, scum!', 12, 1, 100, 0, 0, 0, 12834, 0, 'Sergeant Kan\'\'ren'),
(18926, 0, 0, 'Having trouble dealing with the Wretched? I\'ve got just what you need.', 12, 0, 100, 22, 0, 0, 16058, 0, 'Sleyin'),
(18926, 1, 0, 'Just don\'t ask me where I got it...', 12, 0, 100, 0, 0, 0, 16059, 0, 'Sleyin'),
(18926, 2, 0, 'Something must be done about these Wretched...', 12, 0, 100, 274, 0, 0, 16091, 0, 'Sleyin'),
(18926, 3, 0, 'Once they\'re dealt with we can dedicate more resources to the war effort.', 12, 0, 100, 0, 0, 0, 16092, 0, 'Sleyin'),
(18929, 0, 0, 'If only I had some wine to go with my cheese...', 12, 0, 100, 18, 0, 0, 16093, 0, 'Kyrenna'),
(18929, 1, 0, 'The hours would pass so much more sweetly.', 12, 0, 100, 0, 0, 0, 16096, 0, 'Kyrenna'),
(18929, 2, 0, 'Ooh what a dreadful job!', 12, 0, 100, 1, 0, 0, 16094, 0, 'Kyrenna'),
(18929, 3, 0, 'All day, surrounded by the stench of bad feet.', 12, 0, 100, 0, 0, 0, 16095, 0, 'Kyrenna'),
(18929, 4, 0, 'Why couldn\'t mother have chosen something else to dedicate herself to?', 12, 0, 100, 1, 0, 0, 16097, 0, 'Kyrenna'),
(18929, 5, 0, 'Cakes, pastries, even bread - anything but cheese!', 12, 0, 100, 0, 0, 0, 16098, 0, 'Kyrenna');

-- Novice Ranger SAI
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=16923;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (16923) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(16923,0,0,0,1,0,100,0,215000,225000,215000,225000,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Novice Ranger - OOC - Say text 0');

-- Wretched Captive SAI
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=16916;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (16916) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(16916,0,0,0,1,0,100,0,6000,18000,18000,18000,0,5,20,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Wretched Captive - OOC - Play Emote 20 "Beg"');

-- Sergeant Kan'ren SAI
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=16924;
DELETE FROM `smart_scripts` WHERE `entryorguid`=16924 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=169240 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1692400 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(16924,0,0,0,1,0,100,0,5000,255000,255000,255000,0,80,169240,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sergeant Kan''ren - OOC - Run script'),
(169240,9,0,0,0,0,100,0,0,0,0,0,0,53,0,16924,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sergeant Kan''ren - Script - Load path'),
(169240,9,1,0,0,0,100,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sergeant Kan''ren - Script - Say text 0'),
(169240,9,2,0,0,0,100,0,5000,5000,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,1.04719758,'Sergeant Kan''ren - Script - Set Orientation'),
(169240,9,3,0,0,0,100,0,0,0,0,0,0,1,0,0,0,0,0,0,19,16916,10,0,0,0,0,0,0,'Sergeant Kan''ren - Script - Wretched Captive Say text 0'),
(169240,9,4,0,0,0,100,0,6000,6000,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sergeant Kan''ren - Script - Say text 1');

-- SAI Path for Kan'ren
DELETE FROM `waypoints` WHERE `entry`=16924;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`point_comment`) VALUES
(16924,1,9513.46,-6840.1626,16.743443,0,0, 'Kan''ren'),
(16924,2,9514.46,-6839.1626,16.743443,0,0, 'Kan''ren'),
(16924,3,9514.46,-6837.6626,16.743443,0,0, 'Kan''ren'),
(16924,4,9513.21,-6836.9126,16.743443,0,0, 'Kan''ren'),
(16924,5,9512.21,-6837.6626,16.743443,0,0, 'Kan''ren'),
(16924,6,9511.96,-6839.1626,16.743443,0,0, 'Kan''ren'),
(16924,7,9512.21,-6840.1626,16.493443,0,0, 'Kan''ren');

-- Fix Kan'ren sheath
UPDATE `creature_addon` SET `bytes2`=1 WHERE `guid`=67447;

-- Sleyin SAI
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=18926;
DELETE FROM `smart_scripts` WHERE `entryorguid`=18926 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=189260 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1892900,1892901) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(18926,0,0,0,1,0,100,0,102000,102000,204000,204000,0,80,189260,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - OOC - Run script'),
(189260,9,0,0,0,0,100,0,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - Script - Set run off'),
(189260,9,1,0,0,0,100,0,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,0,9486.051,-6807.0537,16.575666,0,'Sleyin - Script - Move to'),
(189260,9,2,0,0,0,100,0,2000,2000,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - Script - Say text 0'),
(189260,9,3,0,0,0,100,0,6000,6000,0,0,0,69,0,0,0,0,0,0,8,0,0,0,0,9482.344,-6805.512,16.575666,0,'Sleyin - Script - Move to'),
(189260,9,4,0,0,0,100,0,2000,2000,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0.7504915595,'Sleyin - Script - Set Orientation'),
(189260,9,5,0,0,0,100,0,2000,2000,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - Script - Say text 1'),
(189260,9,6,0,0,0,100,0,92000,92000,0,0,0,69,0,0,0,0,0,0,8,0,0,0,0,9486.051,-6807.0537,16.575666,0,'Sleyin - Script - Move to'),
(189260,9,7,0,0,0,100,0,2000,2000,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - Script - Say text 0'),
(189260,9,8,0,0,0,100,0,6000,6000,0,0,0,69,0,0,0,0,0,0,8,0,0,0,0,9482.344,-6805.512,16.575666,0,'Sleyin - Script - Move to'),
(189260,9,9,0,0,0,100,0,2000,2000,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0.7504915595,'Sleyin - Script - Set Orientation'),
(189260,9,10,0,0,0,100,0,2000,2000,0,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Sleyin - Script - Say text 1');

-- Remove Sleyin path
UPDATE `creature` SET `movement_type`=0 WHERE `guid` IN (67449);
UPDATE `creature_addon` SET `path_id`=0,`bytes2`=1 WHERE `guid` IN (67449);
DELETE FROM `db_script_string` WHERE `entry` IN (2000000217,2000000219,2000000220);
DELETE FROM `waypoint_data` WHERE `id` IN(67443,67447,67449);
DELETE FROM `waypoint_scripts` WHERE `id` IN (486,487,488);

-- Kyrenna SAI
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=18929;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (18929) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (189290) AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1892900,1892902) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(18929,0,0,0,1,0,100,0,60000,60000,558000,558000,0,80,189290,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - OOC - Run script'),
(189290,9,0,0,0,0,100,0,0,0,0,0,0,53,0,189290,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Move path'),
(189290,9,1,0,0,0,100,0,7000,7000,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 0'),
(189290,9,2,0,0,0,100,0,8000,8000,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 1'),
(189290,9,3,0,0,0,100,0,8000,8000,0,0,0,53,0,189291,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Move path'),
(189290,9,4,0,0,0,100,0,6000,6000,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,2.51327419,'Kyrenna - Script - Set Orientation'),
(189290,9,5,0,0,0,100,0,204000,204000,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 2'),
(189290,9,6,0,0,0,100,0,7000,7000,0,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 3'),
(189290,9,7,0,0,0,100,0,201000,201000,0,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 4'),
(189290,9,8,0,0,0,100,0,7000,7000,0,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Kyrenna - Script - Say text 5');

-- SAI Path for Kyrenna
DELETE FROM `waypoints` WHERE `entry` IN (189290,189291);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`point_comment`) VALUES
(189290,1,9548.289,-6828.249,16.763393,0,0, 'Kyrenna'),
(189290,2,9551.43,-6836.5903,16.611946,0,0, 'Kyrenna'),
(189291,1,9548.289,-6828.249,16.763393,0,0, 'Kyrenna'),
(189291,2,9552.018,-6825.113,16.513393,0,0, 'Kyrenna');

--  Whirligig Wafflefry(25885)
UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry`=25885;
DELETE FROM `creature_text` WHERE `CreatureID` IN (25885);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(25885, 0, 0, 'Hey, harbinger, how\'s that research coming along? There might be an Ultra-Kinetic Waffle Iron in it for you if you\'re prompt with the results!', 12, 0, 100, 1, 0, 0, 25085, 0, 'Whirligig Wafflefry'),
(25885, 1, 0, 'Be the first on your block to own the incredible Electrostatic Maculation Blaster!', 12, 0, 100, 1, 0, 0, 25073, 0, 'Whirligig Wafflefry'),
(25885, 2, 0, 'Derived from cutting edge Shattered Sun Offensive military technology, it blasts away stubborn stains with ease!', 12, 0, 100, 1, 0, 0, 25074, 0, 'Whirligig Wafflefry'),
(25885, 3, 0, 'Wine stains, grass stains, even pet stains are no match for the Electrostatic Maculation Blaster!', 12, 0, 100, 1, 0, 0, 25075, 0, 'Whirligig Wafflefry'),
(25885, 4, 0, 'Don\'t wait! Order now and receive my Ultra-Kinetic Waffle Iron at no additional charge!', 12, 0, 100, 1, 0, 0, 25076, 0, 'Whirligig Wafflefry');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25885) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(25885, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - On Respawn - Set Sheath Ranged'),
(25885, 0, 1, 0, 1, 0, 100, 0, 30000, 30000, 300000, 300000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - Out of Combat - Say Line 0'),
(25885, 0, 2, 0, 1, 0, 100, 0, 82000, 82000, 300000, 300000, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - Out of Combat - Say Line 1'),
(25885, 0, 3, 0, 1, 0, 100, 0, 90000, 90000, 300000, 300000, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - Out of Combat - Say Line 2'),
(25885, 0, 4, 0, 1, 0, 100, 0, 98000, 98000, 300000, 300000, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - Out of Combat - Say Line 3'),
(25885, 0, 5, 0, 1, 0, 100, 0, 106000, 106000, 300000, 300000, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Whirligig Wafflefry - Out of Combat - Say Line 4');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000212,2000000213,2000000214,2000000215);
DELETE FROM `waypoint_data` WHERE `id` IN(100734);
DELETE FROM `waypoint_scripts` WHERE `id` IN (712,713,714,715);

-- Harbinger Haronem(19475)
UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry`=19475;
DELETE FROM `creature_text` WHERE `CreatureID` IN (19475);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(19475, 0, 0, 'It\'s coming along, Wafflefry. Haven\'t you got a product demonstration to do or something?', 12, 0, 100, 1, 0, 0, 25086, 0, 'Harbinger Haronem');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (19475) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(19475, 0, 0, 0, 1, 0, 100, 0, 6000, 6000, 6000, 6000, 0, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Harbinger Haronem - Out of Combat - Play Emote 1'),
(19475, 0, 1, 0, 1, 0, 100, 0, 39000, 39000, 300000, 300000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Harbinger Haronem - Out of Combat - Say Line 0');

DELETE FROM `db_script_string` WHERE `entry` IN (2000000216);
DELETE FROM `waypoint_data` WHERE `id` IN(72498);
DELETE FROM `waypoint_scripts` WHERE `id` IN (502);

-- Ol' Emma(3520)
UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry`=3520;
DELETE FROM `creature_text` WHERE `CreatureID` IN (3520);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(3520, 0, 0, 'Seems like a hundred times a day I walk all the way to the well to get more water. No respect for their elders I tell ya.', 12, 7, 100, 0, 0, 0, 1107, 0, 'Ol\' Emma'),
(3520, 0, 1, 'Jack and Jill my wrinkled patoot! I do all the water luggin\' \'round here.', 12, 7, 100, 0, 0, 0, 1110, 0, 'Ol\' Emma'),
(3520, 0, 2, 'Think I\'m starting to wear a rut in the paving stones.', 12, 7, 100, 0, 0, 0, 1111, 0, 'Ol\' Emma'),
(3520, 0, 3, 'One of these days I\'m gonna drown him in that blue robe. And all his brooms too.', 12, 0, 100, 0, 0, 0, 1109, 0, 'Ol\' Emma'),
(3520, 1, 0, 'O\'course I\'m talkin to myself. Only way to get decent conversation in this city.', 12, 7, 100, 0, 0, 0, 1108, 0, 'Ol\' Emma'),
(3520, 1, 1, 'As if I don\'t have better things to do in my old age than carry buckets of water.', 12, 7, 100, 0, 0, 0, 1106, 0, 'Ol\' Emma'),
(3520, 1, 2, 'Where\'s the water, Emma? Get the water, Emma? If\'n it weren\'t fer me, that lot wouldn\'t know what water looks like.', 12, 7, 100, 0, 0, 0, 1105, 0, 'Ol\' Emma'),
(3520, 1, 3, 'Deja vu.  For a moment, I thought I was back home... before the plague...', 12, 0, 100, 0, 0, 0, 1112, 0, 'Ol\' Emma');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3520) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(3520, 0, 0, 0, 1, 0, 100, 0, 0, 0, 180000, 180000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ol\' Emma - Out of Combat - Say Line 0 (No Repeat)'),
(3520, 0, 1, 0, 1, 0, 100, 0, 60000, 60000, 180000, 180000, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Ol\' Emma - Out of Combat - Say Line 1 (No Repeat)');

-- Pathing for Ol' Emma Entry: 3520 'TDB FORMAT' 
SET @NPC := 6312;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `movement_type`=2,`position_x`=-8774.427,`position_y`=666.4566,`position_z`=103.4139 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-8774.427,666.4566,103.4139,0,0,0,0,100,0),
(@PATH,2,-8768.528,658.816,103.7889,0,0,0,0,100,0),
(@PATH,3,-8762.686,650.0052,104.0538,0,0,0,0,100,0),
(@PATH,4,-8759.118,637.8125,103.4518,0,0,0,0,100,0),
(@PATH,5,-8759.073,625.3489,101.5838,0,0,0,0,100,0),
(@PATH,6,-8763.571,616.5469,98.81667,0,0,0,0,100,0),
(@PATH,7,-8778.382,602.059,97.40015,0,0,0,0,100,0),
(@PATH,8,-8793.395,591.9011,97.77479,0,0,0,0,100,0),
(@PATH,9,-8810.401,578.6962,95.51057,0,0,0,0,100,0),
(@PATH,10,-8819.727,566.627,94.551,0,0,0,0,100,0),
(@PATH,11,-8807.325,581.8958,96.47041,0,0,0,0,100,0),
(@PATH,12,-8790.901,593.7344,97.80921,0,0,0,0,100,0),
(@PATH,13,-8773.188,607.4774,97.40015,0,0,0,0,100,0),
(@PATH,14,-8768.804,606.7535,97.15015,0,0,0,0,100,0),
(@PATH,15,-8755.163,593.6875,97.39633,0,0,0,0,100,0),
(@PATH,16,-8738.802,576.6077,97.64633,0,0,0,0,100,0),
(@PATH,17,-8731.153,577.8646,97.54487,0,0,0,0,100,0),
(@PATH,18,-8723.391,587.1389,98.2635,0,0,0,0,100,0),
(@PATH,19,-8718.67,592.3906,98.71589,0,0,0,0,100,0),
(@PATH,20,-8711.368,594.5382,98.7635,0,0,0,0,100,0),
(@PATH,21,-8705.665,604.6858,99.39964,0,0,0,0,100,0),
(@PATH,22,-8703.114,614.6024,100.0256,0,0,0,0,100,0),
(@PATH,23,-8704.326,627.6702,100.4814,0,0,0,0,100,0),
(@PATH,24,-8707.979,641.7292,100.2435,0,0,0,0,100,0),
(@PATH,25,-8713.056,657.7674,99.38411,0,0,0,0,100,0),
(@PATH,26,-8719.231,670.2743,98.98618,0,0,0,0,100,0),
(@PATH,27,-8726.87,681.6077,98.98618,0,0,0,0,100,0),
(@PATH,28,-8731.857,692.6389,98.98618,0,0,0,0,100,0),
(@PATH,29,-8739.575,703.9722,98.72432,0,0,0,0,100,0),
(@PATH,30,-8742.363,713.5608,98.37359,0,0,0,0,100,0),
(@PATH,31,-8731.728,721.743,101.6664,0,0,0,0,100,0),
(@PATH,32,-8718.942,732.882,98.16624,0,0,0,0,100,0),
(@PATH,33,-8714.424,734.0295,97.8885,0,0,0,0,100,0),
(@PATH,34,-8705.797,722.9549,97.20751,0,0,0,0,100,0),
(@PATH,35,-8690.241,703.1736,97.38915,0,0,0,0,100,0),
(@PATH,36,-8681.62,692.1649,98.1385,0,0,0,0,100,0),
(@PATH,37,-8674.399,686.1632,98.62093,0,0,0,0,100,0),
(@PATH,38,-8668.17,676.7205,99.7635,0,0,0,0,100,0),
(@PATH,39,-8665.339,670.1424,100.1642,0,0,0,0,100,0),
(@PATH,40,-8661.473,669.2813,100.5469,0,0,0,0,100,0),
(@PATH,41,-8658.97,671.4159,101.7947,0,0,0,0,100,0),
(@PATH,42,-8654.989,675.8229,101.7945,0,0,0,0,100,0),
(@PATH,43,-8646.609,681.7969,102.1945,0,0,0,0,100,0),
(@PATH,44,-8640.983,678.503,101.7945,0,0,0,0,100,0),
(@PATH,45,-8640.929,675.0018,101.7945,0,0,0,0,100,0),
(@PATH,46,-8648.701,669.4844,108.1945,0,0,0,0,100,0),
(@PATH,47,-8650.832,669.8507,108.1945,0,0,0,0,100,0),
(@PATH,48,-8652.886,673.2604,108.1945,0,0,0,0,100,0),
(@PATH,49,-8656.448,676.9375,108.1945,0,0,0,0,100,0),
(@PATH,50,-8653.119,673.7007,108.1945,0,0,0,0,100,0),
(@PATH,51,-8650.457,670.2184,108.1945,0,0,0,0,100,0),
(@PATH,52,-8647.85,669.8229,108.1945,0,0,0,0,100,0),
(@PATH,53,-8640.595,674.8696,101.7945,0,0,0,0,100,0),
(@PATH,54,-8641.316,677.9182,101.7945,0,0,0,0,100,0),
(@PATH,55,-8646.123,681.2514,102.1945,0,0,0,0,100,0),
(@PATH,56,-8654.254,676.4114,101.7945,0,0,0,0,100,0),
(@PATH,57,-8658.893,671.2893,101.7945,0,0,0,0,100,0),
(@PATH,58,-8661.979,669.2715,100.5469,0,0,0,0,100,0),
(@PATH,59,-8666.408,672.7882,100.1719,0,0,0,0,100,0),
(@PATH,60,-8670.099,681.2952,99.22102,0,0,0,0,100,0),
(@PATH,61,-8679.127,690.8976,98.3885,0,0,0,0,100,0),
(@PATH,62,-8687.364,699.7917,97.42952,0,0,0,0,100,0),
(@PATH,63,-8692.518,705.8785,97.20751,0,0,0,0,100,0),
(@PATH,64,-8706.669,723.7153,97.35387,0,0,0,0,100,0),
(@PATH,65,-8715.255,734.1545,97.8885,0,0,0,0,100,0),
(@PATH,66,-8719.421,732.8547,98.29291,0,0,0,0,100,0),
(@PATH,67,-8730.271,723.8229,101.541,0,0,0,0,100,0),
(@PATH,68,-8742.438,713.7399,98.36062,0,0,0,0,100,0),
(@PATH,69,-8743.101,708.8125,98.6385,0,0,0,0,100,0),
(@PATH,70,-8739.368,703.1077,98.82808,0,0,0,0,100,0),
(@PATH,71,-8740.236,697.868,99.1405,0,0,0,0,100,0),
(@PATH,72,-8760.752,681.8984,101.7655,0,0,0,0,100,0),
(@PATH,73,-8773.578,671.4739,103.3547,0,0,0,0,100,0);

DELETE FROM `db_script_string` WHERE `entry` IN (2000000159,2000000160,2000000161,2000000162,2000000163);
DELETE FROM `waypoint_data` WHERE `id` IN (6312);
DELETE FROM `waypoint_scripts` WHERE `id` IN (121,122,123,124,125,126);

-- Gil(3504)
UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry`=3504;
DELETE FROM `creature_text` WHERE `CreatureID` IN (3504);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(3504, 0, 0, 'Is it true? Are there really crocolisks in the canals?', 12, 7, 100, 0, 0, 0, 1098, 0, 'Gil'),
(3504, 0, 1, 'My feet hurt.', 12, 7, 100, 0, 0, 0, 1099, 0, 'Gil'),
(3504, 0, 2, 'Are we there yet?', 12, 0, 100, 0, 0, 0, 2223, 0, 'Gil'),
(3504, 0, 3, 'Why are we goin\' this way?', 12, 0, 100, 0, 0, 0, 1093, 0, 'Gil'),
(3504, 1, 0, 'I wanna see the Mage Tower.', 12, 7, 100, 0, 0, 0, 1097, 0, 'Gil'),
(3504, 1, 1, 'Where we goin\'?', 12, 7, 100, 0, 0, 0, 1094, 0, 'Gil'),
(3504, 1, 2, 'Why do we always go the same way?', 12, 7, 100, 0, 0, 0, 1100, 0, 'Gil'),
(3504, 1, 3, 'I need to pee.', 12, 0, 100, 0, 0, 0, 1095, 0, 'Gil');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3504) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(3504, 0, 0, 0, 1, 0, 100, 0, 0, 0, 180000, 180000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gil - Out of Combat - Say Line 0 (No Repeat)'),
(3504, 0, 1, 0, 1, 0, 100, 0, 60000, 60000, 180000, 180000, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Gil - Out of Combat - Say Line 1 (No Repeat)');

SET @NPC := 6183;
SET @PATH := @NPC * 10;
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES 
(@PATH, 1, -8855.95, 739.398, 100.652, NULL, 0, 0, 0, 100, 0),
(@PATH, 2, -8860.36, 745.559, 100.085, NULL, 0, 0, 0, 100, 0),
(@PATH, 3, -8865.56, 753.535, 98.326, NULL, 0, 0, 0, 100, 0),
(@PATH, 4, -8869.9, 758.873, 96.9353, NULL, 0, 0, 0, 100, 0),
(@PATH, 5, -8878.35, 754.402, 96.3027, NULL, 0, 0, 0, 100, 0),
(@PATH, 6, -8883.2, 756.494, 95.8485, NULL, 0, 0, 0, 100, 0),
(@PATH, 7, -8907.3, 786.505, 88.0058, NULL, 0, 0, 0, 100, 0),
(@PATH, 8, -8908.63, 793.957, 87.3404, NULL, 0, 0, 0, 100, 0),
(@PATH, 9, -8900.88, 800.955, 87.5389, NULL, 0, 0, 0, 100, 0),
(@PATH, 10, -8901.43, 813.992, 88.9525, NULL, 0, 0, 0, 100, 0),
(@PATH, 11, -8900.03, 825.146, 92.236, NULL, 0, 0, 0, 100, 0),
(@PATH, 12, -8906.46, 839.66, 95.3395, NULL, 0, 0, 0, 100, 0),
(@PATH, 13, -8907.15, 845.876, 95.9848, NULL, 0, 0, 0, 100, 0),
(@PATH, 14, -8896.94, 860.678, 96.1597, NULL, 0, 0, 0, 100, 0),
(@PATH, 15, -8892.78, 870.821, 98.6202, NULL, 0, 0, 0, 100, 0),
(@PATH, 16, -8887.87, 887.383, 102.634, NULL, 0, 0, 0, 100, 0),
(@PATH, 17, -8889.57, 896.064, 105.604, NULL, 0, 0, 0, 100, 0),
(@PATH, 18, -8894.76, 912.748, 110.814, NULL, 0, 0, 0, 100, 0),
(@PATH, 19, -8902.53, 925.537, 114.604, NULL, 0, 0, 0, 100, 0),
(@PATH, 20, -8917.64, 947.938, 117.348, NULL, 0, 0, 0, 100, 0),
(@PATH, 21, -8963.84, 954.109, 117.362, NULL, 0, 0, 0, 100, 0),
(@PATH, 22, -8981.19, 967.551, 116.133, NULL, 0, 0, 0, 100, 0),
(@PATH, 23, -8998.68, 966.465, 116.284, NULL, 0, 0, 0, 100, 0),
(@PATH, 24, -9012.64, 955.765, 116.26, NULL, 0, 0, 0, 100, 0),
(@PATH, 25, -9009.48, 946.414, 116.608, NULL, 0, 0, 0, 100, 0),
(@PATH, 26, -9002.47, 941.176, 117.094, NULL, 0, 0, 0, 100, 0),
(@PATH, 27, -8999.71, 939.96, 117.094, NULL, 0, 0, 0, 100, 0),
(@PATH, 28, -8996.13, 943.31, 117.096, NULL, 3500, 0, 0, 100, 0),
(@PATH, 29, -8996.13, 943.31, 117.096, NULL, 7000, 0, 431, 100, 0),
(@PATH, 30, -8996.13, 943.31, 117.096, NULL, 500, 0, 0, 100, 0),
(@PATH, 31, -8998.96, 942.55, 117.096, NULL, 0, 0, 0, 100, 0),
(@PATH, 32, -9001.01, 941.637, 117.095, NULL, 0, 0, 0, 100, 0),
(@PATH, 33, -9009.89, 946.718, 116.464, NULL, 0, 0, 0, 100, 0),
(@PATH, 34, -9012.21, 950.13, 116.242, NULL, 0, 0, 0, 100, 0),
(@PATH, 35, -9005.23, 960.512, 116.267, NULL, 0, 0, 0, 100, 0),
(@PATH, 36, -8999.98, 964.521, 116.322, NULL, 0, 0, 0, 100, 0),
(@PATH, 37, -8986.65, 965.217, 116.016, NULL, 0, 0, 0, 100, 0),
(@PATH, 38, -8981.4, 964.721, 116.129, NULL, 0, 0, 0, 100, 0),
(@PATH, 39, -8960.67, 953.214, 117.363, NULL, 0, 0, 0, 100, 0),
(@PATH, 40, -8922.92, 947.023, 117.333, NULL, 0, 0, 0, 100, 0),
(@PATH, 41, -8902.79, 921.853, 114.007, NULL, 0, 0, 0, 100, 0),
(@PATH, 42, -8895.68, 910.132, 110.534, NULL, 0, 0, 0, 100, 0),
(@PATH, 43, -8878.5, 918.58, 107.991, NULL, 0, 0, 0, 100, 0),
(@PATH, 44, -8856.19, 931.686, 101.85, NULL, 0, 0, 0, 100, 0),
(@PATH, 45, -8849.38, 928.937, 102.078, NULL, 0, 0, 0, 100, 0),
(@PATH, 46, -8835.17, 939.024, 105.298, NULL, 0, 0, 0, 100, 0),
(@PATH, 47, -8819.22, 951.469, 100.84, NULL, 0, 0, 0, 100, 0),
(@PATH, 48, -8816.43, 951.832, 100.857, NULL, 0, 0, 0, 100, 0),
(@PATH, 49, -8804.28, 940.694, 101.241, NULL, 0, 0, 0, 100, 0),
(@PATH, 50, -8804.37, 937.806, 101.242, NULL, 0, 0, 0, 100, 0),
(@PATH, 51, -8779.31, 910.339, 100.177, NULL, 0, 0, 0, 100, 0),
(@PATH, 52, -8768.25, 893.856, 101.271, NULL, 0, 0, 0, 100, 0),
(@PATH, 53, -8739.04, 892.116, 101.339, NULL, 0, 0, 0, 100, 0),
(@PATH, 54, -8733.75, 887.049, 101.562, NULL, 0, 0, 0, 100, 0),
(@PATH, 55, -8725.05, 875.531, 102.709, NULL, 0, 0, 0, 100, 0),
(@PATH, 56, -8713.7, 862.039, 97.8111, NULL, 0, 0, 0, 100, 0),
(@PATH, 57, -8712.67, 855.316, 96.8819, NULL, 0, 0, 0, 100, 0),
(@PATH, 58, -8726.05, 836.042, 96.134, NULL, 0, 0, 0, 100, 0),
(@PATH, 59, -8727.49, 814.648, 96.9542, NULL, 0, 0, 0, 100, 0),
(@PATH, 60, -8718.58, 797.138, 96.962, NULL, 0, 0, 0, 100, 0),
(@PATH, 61, -8721.53, 784.142, 97.7308, NULL, 0, 0, 0, 100, 0),
(@PATH, 62, -8732.91, 768.156, 97.9981, NULL, 0, 0, 0, 100, 0),
(@PATH, 63, -8726.7, 749.858, 98.5581, NULL, 0, 0, 0, 100, 0),
(@PATH, 64, -8714.65, 731.375, 97.8164, NULL, 0, 0, 0, 100, 0),
(@PATH, 65, -8701.16, 715.943, 97.0168, NULL, 0, 0, 0, 100, 0),
(@PATH, 66, -8663.11, 742.302, 96.8254, NULL, 0, 0, 0, 100, 0),
(@PATH, 67, -8659.93, 763.661, 96.7207, NULL, 0, 0, 0, 100, 0),
(@PATH, 68, -8635.15, 785.343, 96.6526, NULL, 0, 0, 0, 100, 0),
(@PATH, 69, -8633.38, 785.986, 96.6516, NULL, 0, 0, 0, 100, 0),
(@PATH, 70, -8608.26, 761.696, 96.7263, NULL, 0, 0, 0, 100, 0),
(@PATH, 71, -8593.8, 756.391, 96.6814, NULL, 0, 0, 0, 100, 0),
(@PATH, 72, -8580.91, 739.047, 96.7163, NULL, 0, 0, 0, 100, 0),
(@PATH, 73, -8594.5, 719.299, 96.6514, NULL, 0, 0, 0, 100, 0),
(@PATH, 74, -8583.57, 698.392, 97.0168, NULL, 0, 0, 0, 100, 0),
(@PATH, 75, -8561.51, 672.146, 97.0168, NULL, 0, 0, 0, 100, 0),
(@PATH, 76, -8537.82, 690.445, 97.669, NULL, 0, 0, 0, 100, 0),
(@PATH, 77, -8529.69, 679.679, 100.253, NULL, 0, 0, 0, 100, 0),
(@PATH, 78, -8518.59, 662.906, 102.205, NULL, 0, 0, 0, 100, 0),
(@PATH, 79, -8511.66, 652.761, 100.292, NULL, 0, 0, 0, 100, 0),
(@PATH, 80, -8516.35, 644.956, 100.162, NULL, 0, 0, 0, 100, 0),
(@PATH, 81, -8556.13, 616.892, 102.187, NULL, 0, 0, 0, 100, 0),
(@PATH, 82, -8562.04, 616.435, 102.182, NULL, 0, 0, 0, 100, 0),
(@PATH, 83, -8583.73, 588.524, 103.595, NULL, 0, 0, 0, 100, 0),
(@PATH, 84, -8585.85, 561.536, 101.877, NULL, 0, 0, 0, 100, 0),
(@PATH, 85, -8577.26, 545.44, 101.779, NULL, 0, 0, 0, 100, 0),
(@PATH, 86, -8592.94, 533.367, 105.38, NULL, 0, 0, 0, 100, 0),
(@PATH, 87, -8610.02, 517.34, 104.15, NULL, 0, 0, 0, 100, 0),
(@PATH, 88, -8615.42, 517.274, 103.269, NULL, 0, 0, 0, 100, 0),
(@PATH, 89, -8656.06, 553.368, 96.9474, NULL, 0, 0, 0, 100, 0),
(@PATH, 90, -8671.7, 554.211, 97.1884, NULL, 0, 0, 0, 100, 0),
(@PATH, 91, -8710.99, 519.456, 97.3037, NULL, 0, 0, 0, 100, 0),
(@PATH, 92, -8715.38, 524.179, 97.904, NULL, 0, 0, 0, 100, 0),
(@PATH, 93, -8745.23, 554.602, 98.1147, NULL, 0, 0, 0, 100, 0),
(@PATH, 94, -8747.57, 565.115, 97.3972, NULL, 0, 0, 0, 100, 0),
(@PATH, 95, -8738.96, 574.03, 97.4159, NULL, 0, 0, 0, 100, 0),
(@PATH, 96, -8768.08, 610.107, 97.1626, NULL, 0, 0, 0, 100, 0),
(@PATH, 97, -8795.82, 587.829, 97.3799, NULL, 0, 0, 0, 100, 0),
(@PATH, 98, -8831.84, 627.737, 93.999, NULL, 0, 0, 0, 100, 0),
(@PATH, 99, -8853.68, 661.629, 97.0331, NULL, 0, 0, 0, 100, 0),
(@PATH, 100, -8826.11, 677.069, 97.6407, NULL, 0, 0, 0, 100, 0),
(@PATH, 101, -8847.53, 725.129, 97.341, NULL, 0, 0, 0, 100, 0);

DELETE FROM `db_script_string` WHERE `entry` IN (2000000188,2000000189,2000000191,2000000192,2000000193);
DELETE FROM `waypoint_data` WHERE `id` IN (6183);
DELETE FROM `waypoint_scripts` WHERE `id` IN (105,106,107,111,112,113,114,115);
