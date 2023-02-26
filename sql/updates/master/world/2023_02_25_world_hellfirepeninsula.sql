-- Remove script for Naladu gossip already exist
UPDATE `creature_template` SET `AIName`='', `ScriptName`= '' WHERE `entry`=19361;

-- Gossip text & Options for Tracy Proudwell
UPDATE `creature_template` SET `gossip_menu_id`=7892 WHERE `entry`=18266;
DELETE FROM `gossip_menu` WHERE `entry` IN (8544);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (8544,10689);
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (7892,8544);
INSERT INTO `gossip_menu_option` (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text) VALUES
(7892,0,1, 'I have marks to redeem!',3,128,0,0,0,0, ''),
(7892,1,0, 'I heard that your dog Fei Fei took Klatu''s prayer beads...',1,1,8544,0,0,0, ''),
(8544,0,0, '<back>',1,1,7892,0,0,0, '');
-- Add Conditions for Budd Nedreck gossip option
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=7892;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15,7892,1,0,0,9,0,10916,0,0,0,0,0, '', 'Gossip Option - Show Option if Quest 10916 is taken');

-- Commander Danath Trollbane SAI
SET @ENTRY := 16819;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`= '' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,50,0,100,0,10254,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Commander Danath Trollbane - On Quest Rewarded - Say 0"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,11,6245,0,0,0,0,0,7,0,0,0,0,0,0,0,"Commander Danath Trollbane - On Quest Rewarded - Cast Force Target - Salute");

-- Creature text for Commander Danath Trollbane
DELETE FROM `creature_text` WHERE `entry`=16819;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(16819,0,0, 'Welcome to Honor Hold, $N.  It''s good to have you.',12,0,100,66,0,0, 'Commander Danath Trollbane');

-- Gossip text & Options for Force Commander Danath Trollbane
DELETE FROM `gossip_menu` WHERE `entry` IN (8043,8044,8049,8051);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (8043,9933),(8044,9932),(8049,9941),(8051,8772);
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (7352,8044);
INSERT INTO `gossip_menu_option` (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text) VALUES
(7352,0,0, 'Tell me of the Sons of Lothar.',1,1,8044,0,0,0, ''),
(7352,1,0, 'Tell me of the Hellfire orcs.',1,1,8049,0,0,0, ''),
(7352,2,0, 'Tell me of your homeland.',1,1,8051,0,0,0, ''),
(8044,0,0, '<more>',1,1,8043,0,0,0, '');

-- Add Conditions for Force Commander Danath Trollbane gossip text
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=14 AND `SourceGroup`=7352;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(14,7352,9938,0,0,8,0,10254,0,0,0,1,0, '', 'Gossip Text - Show Text if Quest 10254 is not rewarded'),
(14,7352,9939,0,0,8,0,10254,0,0,0,0,0, '', 'Gossip Text - Show Text if Quest 10254 is rewarded'),
(14,7352,9939,0,1,8,0,10937,0,0,0,1,0, '', 'Gossip Text - Show Text if Quest 10937 is not rewarded'),
(14,7352,9944,0,0,8,0,10937,0,0,0,0,0, '', 'Gossip Text - Show Text if Quest 10937 is rewarded');

-- Add Conditions for Force Commander Danath Trollbane gossip options
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=7352;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15,7352,0,0,0,8,0,10254,0,0,0,0,0, '', 'Gossip Option - Show Option if Quest 10254 is rewarded'),
(15,7352,1,0,0,8,0,10254,0,0,0,0,0, '', 'Gossip Option - Show Option if Quest 10254 is rewarded'),
(15,7352,2,0,0,8,0,10141,0,0,0,0,0, '', 'Gossip Option - Show Option if Quest 10141 is rewarded');

--
UPDATE `conditions` SET `ConditionTypeOrReference`=28, `Comment`="Show gossip option 0 if player has quest Arelion's Secret completed OR" WHERE `SourceGroup`=8081 AND `ElseGroup`=0;
DELETE FROM `conditions` WHERE `SourceGroup`=8081 AND `ElseGroup`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 8081, 0, 0, 1, 8, 0, 10286, 0, 0, 0, 0, 0, "", "Show gossip option 0 if player has quest Arelion's Secret rewarded");


DELETE FROM `creature` WHERE `id`=19461;
DELETE FROM `script_waypoint` WHERE `entry`=17077 AND `pointid` IN (51, 52);
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(17077, 51, 519.146, 3886.7, 190.128, 10000, 'RYGA_WALK'),
(17077, 52, 519.146, 3886.7, 190.128, 1000, 'RYGA_RETURN');

-- The Exorcism of Colonel Jules
UPDATE `creature_template` SET `ScriptName`= 'npc_barada' WHERE `entry`= 22431;
UPDATE `creature_template` SET `ScriptName`= 'npc_colonel_jules' WHERE `entry`= 22432;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 8539;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`) VALUES
(8539, 1, 0, 'I am ready, Anchorite.  Let us begin the exorcism.', 20396, 1, 3);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=8539;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`, `ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,8539,0,0,9,10935,0,0,0,'','Show gossip menu if player accept Exorcism of Colonel Jules');

DELETE FROM `creature_text` WHERE `entry` IN(22431, 22432);
-- Barada
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(22431, 0, 0, 'It is time. The rite of exorcism will now commence...', 12, 0, 100, 0, 0, 0, 20400, 0, 'Barada'),
(22431, 1, 0, 'Prepare yourself. Do not allow the ritual to be interrupted or we may lose our patient...', 12, 0, 100, 0, 0, 0, 20401, 0, 'Barada'),
(22431, 2, 0, 'Back foul beings of darkness! You have no power here!', 12, 0, 100, 0, 0, 0, 20404, 0, 'Barada'),
(22431, 3, 0, 'I... must not... falter', 12, 0, 100, 0, 0, 0, 20407, 0, 'Barada'),
(22431, 4, 0, 'The Light is my guide... it is my sustenance!', 12, 0, 100, 0, 0, 0, 20408, 0, 'Barada'),
(22431, 5, 0, 'The power of light compells you! Back to your pit!', 12, 0, 100, 0, 0, 0, 20405, 0, 'Barada'),
(22431, 6, 0, 'Be cleansed with Light, human! Let not the demonic corruption overwhelm you.', 12, 0, 100, 0, 0, 0, 20403, 0, 'Barada'),
(22431, 7, 0, 'Back! I cast you back... corruptor of faith! Author of pain! Do not return, or suffer the same fate as you did here today!', 12, 0, 100, 0, 0, 0, 20419, 0, 'Barada'),

-- Colonel Jules
(22432, 0, 0, 'Keep away. The fool is mine.', 12, 0, 100, 0, 0, 0, 20402, 0, 'Colonel Jules'),
(22432, 1, 0, 'Ah! Cease the incantations, Anchorite! Cease, or I will show you such pain that your pathetic people have never imagined!', 12, 0, 100, 0, 0, 0, 20414, 0, 'Colonel Jules'),
(22432, 2, 0, 'This is fruitless, draenei! You and your little helper cannot wrest control of this pathetic human. He is mine!', 12, 0, 100, 0, 0, 0, 20416, 0, 'Colonel Jules'),
(22432, 3, 0, 'I see your ancestors, Anchorite! They writhe and scream in the darkness... they are with us!', 12, 0, 100, 0, 0, 0, 20415, 0, 'Colonel Jules'),
(22432, 4, 0, 'I will tear your soul into morsels and slow roast them over demon fire.', 12, 0, 100, 0, 0, 0, 20417, 0, 'Colonel Jules');

-- Aura for the flying skulls
DELETE FROM `creature_template_addon` WHERE `entry` = 22507;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(22507, 0, 0, 0, 1, 0, '39303');

--
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|64 WHERE `entry` IN (22506, 22507);

UPDATE `quest_template_addon` SET `PrevQuestID`=0 WHERE `ID`=10935;
UPDATE `quest_template_addon` SET `ExclusiveGroup`=-10909, `NextQuestID`=10935 WHERE `ID` IN (10909, 10916);

--
UPDATE `conditions` SET `ConditionTypeOrReference`=28, `Comment`="Show gossip option 0 if player has quest Arelion's Secret completed OR" WHERE `SourceGroup`=8081 AND `ElseGroup`=0;
DELETE FROM `conditions` WHERE `SourceGroup`=8081 AND `ElseGroup`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 8081, 0, 0, 1, 8, 0, 10286, 0, 0, 0, 0, 0, "", "Show gossip option 0 if player has quest Arelion's Secret rewarded");

ALTER TABLE `waypoints` 
ADD COLUMN `orientation` float NULL DEFAULT NULL AFTER `position_z`,
ADD COLUMN `delay` int UNSIGNED NOT NULL DEFAULT 0 AFTER `orientation`;


-- Ancestral Spirit Wolf SAI (Source: Sniffs & https://www.youtube.com/watch?v=xFF8DOSeMcg)
SET @ID := 17077;
UPDATE `creature_template` SET `speed_walk` = 1.6, `speed_run` = 1, `unit_flags` = 768, `AIName` = "SmartAI", `ScriptName` = "" WHERE `entry` = @ID;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ID AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` BETWEEN @ID*100+0 AND @ID*100+3 AND `source_type` = 9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ID,0,0,0,54,0,100,0,0,0,0,0,0,80,@ID*100+0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Just Summoned - Run Script"),
(@ID,0,1,0,40,0,100,0,9,0,0,0,0,80,@ID*100+1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Waypoint 9 Reached - Run Script"),
(@ID,0,2,0,40,0,100,0,68,0,0,0,0,80,@ID*100+2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Waypoint 68 Reached - Run Script"),
(@ID,0,3,0,40,0,100,0,73,0,0,0,0,80,@ID*100+3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Waypoint 73 Reached - Run Script"),
-- Hacky follow movement prevention
(@ID*100+0,9,0,0,0,0,100,0,0,0,0,0,0,69,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Move To Self"),
(@ID*100+0,9,1,0,0,0,100,0,0,0,0,0,0,11,29938,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Cast 'Guided by the Spirits'"),
(@ID*100+0,9,2,0,0,0,100,0,0,0,0,0,0,11,30011,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Cast 'Quest - Ancestral Spirit Wolf Self Snare'"),
(@ID*100+0,9,3,0,0,0,100,0,5000,5000,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Say Line 0"),
(@ID*100+0,9,4,0,0,0,100,0,4000,4000,0,0,0,53,0,17077,0,0,0,2,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Start Waypoint"),

(@ID*100+1,9,0,0,0,0,100,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Say Line 1"),
-- Something happens here, he changes speed somehow
(@ID*100+2,9,0,0,0,0,100,0,0,0,0,0,0,4,1018,0,1,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Play Sound 1018"),
-- May be different
(@ID*100+3,9,0,0,0,0,100,0,0,0,0,0,0,41,60000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Delayed Despawn"),
(@ID*100+3,9,1,0,0,0,100,0,0,0,0,0,0,45,0,1,0,0,0,0,19,17123,0,0,0,0,0,0,0,"Ancestral Spirit Wolf - On Script - Set Data 0 1 (Earthcaller Ryga)");

-- Earthcaller Ryga SAI
SET @ID := 17123;
UPDATE `creature_template` SET `speed_walk` = 1, `AIName` = "SmartAI" WHERE `entry` = @ID;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ID AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` BETWEEN @ID*100+0 AND @ID*100+2 AND `source_type` = 9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ID,0,0,0,63,0,100,0,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Just Created - Set Event Phase 1"),
(@ID,0,1,0,38,1,100,0,0,1,0,0,0,80,@ID*100+0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Data Set 0 1 - Run Script (Phase 1)"),
(@ID,0,2,0,40,0,100,0,2,0,0,0,0,80,@ID*100+1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Waypoint 2 Reached - Run Script"),
(@ID,0,3,0,40,0,100,0,4,0,0,0,0,80,@ID*100+2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Waypoint 4 Reached - Run Script"),

(@ID*100+0,9,0,0,0,0,100,0,0,0,0,0,0,53,0,17123,0,0,0,2,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Start Waypoint"),
(@ID*100+0,9,1,0,0,0,100,0,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Set Event Phase 2"),

(@ID*100+1,9,0,0,0,0,100,0,1000,1000,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Say Line 0"),
(@ID*100+1,9,1,0,0,0,100,0,0,0,0,0,0,90,8,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Set Flag Standstate Kneel"),
(@ID*100+1,9,2,0,0,0,100,0,10000,10000,0,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Remove Flag Standstate Kneel"),

(@ID*100+2,9,0,0,0,0,100,0,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,"Earthcaller Ryga - On Script - Set Event Phase 1");

DELETE FROM `script_waypoint` WHERE `entry` = 17077;
DELETE FROM `waypoints` WHERE `entry` IN (17077,17123);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`point_comment`) VALUES
(17077,1,-19.435663,3803.981,93.55267,0,0,"Ancestral Spirit Wolf"),
(17077,2,-18.685663,3801.731,94.30267,0,0,"Ancestral Spirit Wolf"),
(17077,3,-17.185663,3800.981,95.30267,0,0,"Ancestral Spirit Wolf"),
(17077,4,-15.185663,3801.981,96.05267,0,0,"Ancestral Spirit Wolf"),
(17077,5,-14.435663,3803.731,96.05267,0,0,"Ancestral Spirit Wolf"),
(17077,6,-14.435663,3804.981,95.80267,0,0,"Ancestral Spirit Wolf"),
(17077,7,-15.435663,3805.981,94.80267,0,0,"Ancestral Spirit Wolf"),
(17077,8,-16.935663,3806.481,94.05267,0,0,"Ancestral Spirit Wolf"),
(17077,9,-17.14388,3805.7651,93.82591,0,6000,"Ancestral Spirit Wolf"), --

(17077,10,-18.672201,3822.212,89.946106,0,0,"Ancestral Spirit Wolf"),
(17077,11,-15.436849,3839.5933,86.010345,0,0,"Ancestral Spirit Wolf"),
(17077,12,-13.511067,3869.3118,83.18117,0,0,"Ancestral Spirit Wolf"),
(17077,13,-10.554254,3882.9075,83.18117,0,0,"Ancestral Spirit Wolf"),
(17077,14,-3.270291,3897.9458,85.43117,0,0,"Ancestral Spirit Wolf"),
(17077,15,5.854601,3906.4575,86.36614,0,0,"Ancestral Spirit Wolf"),
(17077,16,21.961697,3917.6707,85.24114,0,0,"Ancestral Spirit Wolf"),
(17077,17,40.73991,3927.2727,84.03038,0,0,"Ancestral Spirit Wolf"),
(17077,18,60.198025,3935.109,81.423935,0,0,"Ancestral Spirit Wolf"),
(17077,19,88.06445,3943.124,77.16091,0,0,"Ancestral Spirit Wolf"),
(17077,20,116.48167,3942.2288,77.71034,0,0,"Ancestral Spirit Wolf"),
(17077,21,140.60602,3938.9385,81.55002,0,0,"Ancestral Spirit Wolf"),
(17077,22,171.98372,3938.8472,79.65354,0,0,"Ancestral Spirit Wolf"),
(17077,23,192.11057,3941.6697,76.27854,0,0,"Ancestral Spirit Wolf"),
(17077,24,210.7275,3945.3862,74.492744,0,0,"Ancestral Spirit Wolf"),
(17077,25,229.317,3953.9805,73.117744,0,0,"Ancestral Spirit Wolf"),
(17077,26,240.94531,3959.795,75.06353,0,0,"Ancestral Spirit Wolf"),
(17077,27,252.27155,3963.4895,76.93853,0,0,"Ancestral Spirit Wolf"),
(17077,28,273.8889,3978.8838,85.78987,0,0,"Ancestral Spirit Wolf"),
(17077,29,290.13867,3990.5635,91.66487,0,0,"Ancestral Spirit Wolf"),
(17077,30,320.1014,4005.4385,98.469826,0,0,"Ancestral Spirit Wolf"),
(17077,31,338.62778,4002.79,104.993286,0,0,"Ancestral Spirit Wolf"),
(17077,32,343.4465,3997.1423,109.36144,0,0,"Ancestral Spirit Wolf"),
(17077,33,348.71088,3984.7383,115.98644,0,0,"Ancestral Spirit Wolf"),
(17077,34,361.33035,3961.4485,123.48554,0,0,"Ancestral Spirit Wolf"),
(17077,35,356.76953,3949.619,126.98554,0,0,"Ancestral Spirit Wolf"),
(17077,36,346.75836,3922.0083,133.68163,0,0,"Ancestral Spirit Wolf"),
(17077,37,347.1215,3899.5994,137.84831,0,0,"Ancestral Spirit Wolf"),
(17077,38,347.1963,3880.4836,142.84831,0,0,"Ancestral Spirit Wolf"),
(17077,39,337.12424,3856.1204,149.44649,0,0,"Ancestral Spirit Wolf"),
(17077,40,331.16196,3842.576,153.38467,0,0,"Ancestral Spirit Wolf"),
(17077,41,320.0521,3829.007,159.86176,0,0,"Ancestral Spirit Wolf"),
(17077,42,313.16516,3826.182,160.61176,0,0,"Ancestral Spirit Wolf"),
(17077,43,303.0879,3819.6777,163.98676,0,0,"Ancestral Spirit Wolf"),
(17077,44,297.51276,3816.4011,165.62602,0,0,"Ancestral Spirit Wolf"),
(17077,45,290.74023,3806.499,169.62602,0,0,"Ancestral Spirit Wolf"),
(17077,46,285.93805,3794.88,174.97627,0,0,"Ancestral Spirit Wolf"),
(17077,47,292.22098,3781.1619,181.85127,0,0,"Ancestral Spirit Wolf"),
(17077,48,296.92133,3770.8481,185.10127,0,0,"Ancestral Spirit Wolf"),
(17077,49,311.4395,3753.1104,184.11917,0,0,"Ancestral Spirit Wolf"),
(17077,50,321.36182,3741.0325,184.36917,0,0,"Ancestral Spirit Wolf"),
(17077,51,332.90778,3728.5825,184.65353,0,0,"Ancestral Spirit Wolf"),
(17077,52,337.21378,3720.4072,184.01471,0,0,"Ancestral Spirit Wolf"),
(17077,53,344.8604,3715.015,184.01471,0,0,"Ancestral Spirit Wolf"),
(17077,54,358.15982,3716.5864,184.01471,0,0,"Ancestral Spirit Wolf"),
(17077,55,366.21744,3719.898,184.01471,0,0,"Ancestral Spirit Wolf"),
(17077,56,374.8206,3724.2727,184.15353,0,0,"Ancestral Spirit Wolf"),
(17077,57,403.90103,3737.9128,180.65353,0,0,"Ancestral Spirit Wolf"),
(17077,58,421.35953,3750.1697,184.40353,0,0,"Ancestral Spirit Wolf"),
(17077,59,448.62393,3768.8801,186.51082,0,0,"Ancestral Spirit Wolf"),
(17077,60,462.85294,3776.5051,186.38582,0,0,"Ancestral Spirit Wolf"),
(17077,61,472.87814,3791.1094,187.16379,0,0,"Ancestral Spirit Wolf"),
(17077,62,484.18484,3809.1467,188.67741,0,0,"Ancestral Spirit Wolf"),
(17077,63,495.23938,3826.8103,191.55241,0,0,"Ancestral Spirit Wolf"),
(17077,64,498.87946,3837.6038,193.37997,0,0,"Ancestral Spirit Wolf"),
(17077,65,500.95297,3849.591,194.49019,0,0,"Ancestral Spirit Wolf"),
(17077,66,505.95724,3862.4604,194.36519,0,0,"Ancestral Spirit Wolf"),
(17077,67,511.11978,3869.2805,192.93457,0,0,"Ancestral Spirit Wolf"),
(17077,68,518.094,3877.0725,191.80957,0,0,"Ancestral Spirit Wolf"), --
(17077,69,521.2715,3882.2812,190.93457,0,0,"Ancestral Spirit Wolf"),
(17077,70,526.9002,3885.513,190.05957,0,0,"Ancestral Spirit Wolf"),
(17077,71,527.0562,3891.684,189.05957,0,0,"Ancestral Spirit Wolf"),
(17077,72,521.69653,3890.5703,189.55957,0,0,"Ancestral Spirit Wolf"),
(17077,73,520.24036,3885.3213,190.43457,0,0,"Ancestral Spirit Wolf"), --

(17123,1,509.49414,3881.9792,191.55957,0,0,"Earthcaller Ryga"),
(17123,2,517.92773,3883.6355,190.68457,0,11000,"Earthcaller Ryga"), --
(17123,3,505.5433,3882.0378,191.3179,0,0,"Earthcaller Ryga"),
(17123,4,504.59192,3882.131,192.18457,5.79449319839477539,1,"Earthcaller Ryga");

UPDATE `creature_text` SET `Sound` = 9036 WHERE `CreatureID` = 17077 AND `GroupID` = 1;
UPDATE `creature_text` SET `comment` = "Ancestral Spirit Wolf" WHERE `CreatureID` = 17077;
UPDATE `creature_text` SET `comment` = "Earthcaller Ryga" WHERE `CreatureID` = 17123;

DELETE FROM `creature_template_movement` WHERE `CreatureId` = 17123;
INSERT INTO `creature_template_movement` (`CreatureId`,`Ground`,`Swim`,`Flight`,`Rooted`,`Chase`,`Random`,`InteractionPauseTimer`) VALUES
(17123,1,1,0,0,0,0,0);






-- Scripts/Outland: Migrate Shattrath City NPCs to SAI (#20596) 
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` IN (25967,23483,23484);

DELETE FROM `gossip_menu` WHERE `MenuID` = 8752 AND `TextID` = 11085;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`, `VerifiedBuild`) VALUES
(8752,11085,0);

DELETE FROM `gossip_menu_option` WHERE `MenuID` IN (8751,8752);
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextID`, `OptionType`, `OptionNpcFlag`, `VerifiedBuild`) VALUES
(8751, 0, 1, 'I have marks to redeem.', 21915, 3, 128, 0),
(8752, 0, 1, 'I have marks to redeem.', 21915, 3, 128, 0);

DELETE FROM `smart_scripts` WHERE (source_type = 0 AND entryorguid = 25967);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(25967, 0, 0, 0, 62, 0, 100, 0, 9205, 0, 0, 0, 11, 37778, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Zephyr - On Gossip Option 0 Selected - Cast \'Quest - Teleport: Caverns of Time\'');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (14,15) AND `SourceGroup` IN (8751,8752,9205);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 9205, 0, 0, 0, 5, 0, 989, 192, 0, 0, 0, 0, '', 'Show gossip menu 9205 option id 0 if player is Revered or Exalted with faction Keepers of Time.'),
(14, 8751, 11085, 0, 1, 5, 0, 932, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 text id 11085 if player is Exalted with faction The Aldor.'),
(14, 8751, 11085, 0, 1, 5, 0, 935, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 text id 11085 if player is Exalted with faction The Sha\'tar.'),
(14, 8751, 11085, 0, 1, 5, 0, 942, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 text id 11085 if player is Exalted with faction Cenarion Expedition.'),
(14, 8752, 11085, 0, 1, 5, 0, 934, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 text id 11085 if player is Exalted with faction The Scryers.'),
(14, 8752, 11085, 0, 1, 5, 0, 935, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 text id 11085 if player is Exalted with faction The Sha\'tar.'),
(14, 8752, 11085, 0, 1, 5, 0, 942, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 text id 11085 if player is Exalted with faction Cenarion Expedition.'),
(15, 8751, 0, 0, 1, 5, 0, 932, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 option id 0 if player is Exalted with faction The Aldor.'),
(15, 8751, 0, 0, 1, 5, 0, 935, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 option id 0 if player is Exalted with faction The Sha\'tar.'),
(15, 8751, 0, 0, 1, 5, 0, 942, 128, 0, 0, 0, 0, '', 'Show gossip menu 8751 option id 0 if player is Exalted with faction Cenarion Expedition.'),
(15, 8752, 0, 0, 1, 5, 0, 934, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 option id 0 if player is Exalted with faction The Scryers.'),
(15, 8752, 0, 0, 1, 5, 0, 935, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 option id 0 if player is Exalted with faction The Sha\'tar.'),
(15, 8752, 0, 0, 1, 5, 0, 942, 128, 0, 0, 0, 0, '', 'Show gossip menu 8752 option id 0 if player is Exalted with faction Cenarion Expedition.');