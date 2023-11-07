-- Gil(3504)
SET @NPC := 6183;
SET @PATH := @NPC * 10;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,0,0, '');

-- Justin(1368)
-- -------------------------------------------Justin, Brandon, and Roman-----------------------------------------------------
UPDATE `creature` SET `movement_type` = 0 WHERE `guid` in (6350,92307,6348);
UPDATE `creature_addon` SET `path_id` = 0,`bytes2` = 1 WHERE `guid` in (6350,92307,6348);
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` in (1368,1370,1371);

DELETE FROM `smart_scripts` WHERE `entryorguid` in (1368,1370,1371,136800,137000,137001);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(1368,0,0,0,38,0,100,0,1,0,0,0,0,29,0,75,0,0,0,0,10,79817,1370,0,0,0,0,0,0,'Justin - On Data Set 1 0 - Set Follow'),
(1368,0,1,0,38,0,100,0,1,2,0,0,0,69,0,0,0,0,0,0,1,0,0,0,0,-8582.03,633.634,96.3386,5.0381,'Justin - On Data Set 1 2 - Move to POS'),
(1368,0,2,0,38,0,100,0,1,4,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,5.0381,'Justin - On Data Set 1 4 - Set Orientation'),
(1368,0,3,0,38,0,100,0,1,3,0,0,0,69,0,0,0,0,0,0,1,0,0,0,0,-8675.673,909.057,96.338,3.768,'Justin - On Data Set 1 3 - Move to POS'),
(1368,0,4,0,38,0,100,0,1,5,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,3.768,'Justin - On Data Set 1 5 - Set Orientation'),
(1368,0,5,0,1,0,100,0,30000,30000,80000,160000,0,80,136800,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Justin - OOC - Run Script'),

(1371,0,0,0,38,0,100,0,1,0,0,0,0,29,0,285,0,0,0,0,10,79817,1370,0,0,0,0,0,0,'Roman - On Data Set 1 0 - Set Follow'),
(1371,0,1,0,38,0,100,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Roman - On Data Set 1 1 - Say Random 0'),
(1371,0,2,0,38,0,100,0,1,2,0,0,0,69,0,0,0,0,0,0,1,0,0,0,0,-8583.88,633.127,96.3386,5.0381,'Roman - On Data Set 1 2 - Move to POS'),
(1371,0,3,0,38,0,100,0,1,4,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,5.0381,'Roman - On Data Set 1 4 - Set Orientation'),
(1371,0,4,0,38,0,100,0,1,3,0,0,0,69,0,0,0,0,0,0,1,0,0,0,0,-8673.55,912.143,96.338,2.282,'Roman - On Data Set 1 3 - Move to POS'),
(1371,0,5,0,38,0,100,0,1,5,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,2.282,'Roman - On Data Set 1 5 - Set Orientation'),

(1370,0,0,1,1,0,100,1,25000,25000,0,0,0,53,0,1370,1,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - OOC (No Repeat) - Start Waypoint'),
(1370,0,1,2,61,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - Linked - Set Data 1 0 \'Justin\''),
(1370,0,2,0,61,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - Linked - Set Data 1 0 \'Roman\''),
(1370,0,3,0,40,0,100,0,1,1370,0,0,0,80,137000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Waypoint 1 Reached - Run Script'),
(1370,0,4,0,40,0,100,0,32,1370,0,0,0,80,137001,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Waypoint 32 Reached - Run Script'),
(1370,0,5,0,38,0,100,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Data Set 1 1 - Say Random 0'),

(136800,9,0,0,0,0,100,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Justin - On Script - Say Random 0'),
(136800,9,1,0,0,0,100,0,4000,8000,0,0,0,45,1,1,0,0,0,0,10,79817,1370,0,0,0,0,0,0,'Justin - On Script - Set Data 1 1 \'Brandon\''),
(136800,9,2,0,0,0,100,0,6000,9000,0,0,0,45,1,1,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Justin - On Script - Set Data 1 1 \'Roman\''),

-- Starting Dock
(137000,9,0,0,0,0,100,0,0,0,0,0,0,54,4520000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Script - Pause Waypoint'),
(137000,9,1,0,0,0,100,0,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0.2961,'Brandon - On Script - Set Orientation'),
(137000,9,2,0,0,0,100,0,0,0,0,0,0,45,1,2,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 2 \'Roman\''),
(137000,9,3,0,0,0,100,0,0,0,0,0,0,45,1,2,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 2 \'Justin\''),
(137000,9,4,0,0,0,100,0,3000,3000,0,0,0,45,1,4,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 4 \'Roman\''),
(137000,9,5,0,0,0,100,0,0,0,0,0,0,45,1,4,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 4 \'Justin\''),
(137000,9,6,0,0,0,100,0,3600000,4500000,0,0,0,65,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Script - Resume Waypoint'),
(137000,9,7,0,0,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 0 \'Justin\''),
(137000,9,8,0,0,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 0 \'Roman\''),

-- Second Dock
(137001,9,0,0,0,0,100,0,0,0,0,0,0,54,4520000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Script - Pause Waypoint'),
(137001,9,1,0,0,0,100,0,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,2.282,'Brandon - On Script - Set Orientation'),
(137001,9,2,0,0,0,100,0,0,0,0,0,0,45,1,3,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 3 \'Roman\''),
(137001,9,3,0,0,0,100,0,0,0,0,0,0,45,1,3,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 3 \'Justin\''),
(137001,9,4,0,0,0,100,0,3000,3000,0,0,0,45,1,5,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 5 \'Roman\''),
(137001,9,5,0,0,0,100,0,0,0,0,0,0,45,1,5,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 5 \'Justin\''),
(137001,9,6,0,0,0,100,0,3600000,4500000,0,0,0,65,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Brandon - On Script - Resume Waypoint'),
(137001,9,7,0,0,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79815,1368,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 0 \'Justin\''),
(137001,9,8,0,0,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,79816,1371,0,0,0,0,0,0,'Brandon - On Script - Set Data 1 0 \'Roman\'');

DELETE FROM `creature_text` WHERE `CreatureID` in (1368,1370,1371);
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`,`TextRange`,`comment`) VALUES
(1368,0,0,'And so the knights stood before the charging Horde and held their ground as a thousand berserk orcs came through the valley.',12,7,100,1,0,0,150,0,'Justin - Talk'),
(1368,0,1,'And that\'s how Lothar killed thirty six orcs with his bare hands!',12,7,100,1,0,0,149,0,'Justin - Talk'),
(1368,0,2,'And then the rabbit just bit his head off... I swear.',12,7,100,1,0,0,155,0,'Justin - Talk'),
(1368,0,3,'They say he can turn into a raven sometimes.',12,7,100,1,0,0,151,0,'Justin - Talk'),
(1368,0,4,'You know there are crocolisks in the Canals. They were brought from the swamp as pets, but got thrown in the canals.',12,7,100,1,0,0,156,0,'Justin - Talk'),
(1368,0,5,'You know why orc eyes glow red? It\'s because they drink blood!',12,7,100,1,0,0,152,0,'Justin - Talk'),
(1368,0,6,'I swear, people have actually seen them. Pandaren really do exist!',12,7,100,1,0,0,154,0,'Justin - Talk'),
(1368,0,7,'There is no spoon.',12,7,100,1,0,0,153,0,'Justin - Talk'),

(1370,0,0,'My father says that\'s just a story.',12,7,100,1,0,0,168,0,'Brandon - Talk'),
(1370,0,1,'Can you imagine?',12,7,100,1,0,0,169,0,'Brandon - Talk'),
(1370,0,2,'Oh c\'mon, that\'s not true.',12,7,100,1,0,0,166,0,'Brandon - Talk'),
(1370,0,3,'Oh yeah, I heard about that.',12,7,100,1,0,0,158,0,'Brandon - Talk'),
(1370,0,4,'Really?',12,7,100,1,0,0,147,0,'Brandon - Talk'),
(1370,0,5,'Sounds kinda like one of Billy\'s fish stories to me.',12,7,100,1,0,0,170,0,'Brandon - Talk'),
(1370,0,6,'That\'s neat.',12,7,100,1,0,0,167,0,'Brandon - Talk'),
(1370,0,7,'Wow.',12,7,100,1,0,0,157,0,'Brandon - Talk'),

(1371,0,0,'Eww... that\'s not a fish!',12,7,100,1,0,0,173,0,'Roman - Talk'),
(1371,0,1,'I don\'t think there\'s any fish in these canals.',12,7,100,1,0,0,177,0,'Roman - Talk'),
(1371,0,2,'I got worm guts on my shoes.',12,7,100,1,0,0,174,0,'Roman - Talk'),
(1371,0,3,'I hope that was a fish!',12,7,100,1,0,0,176,0,'Roman - Talk'),
(1371,0,4,'I think I see something.',12,7,100,1,0,0,172,0,'Roman - Talk'),
(1371,0,5,'Something smells funny.',12,7,100,1,0,0,175,0,'Roman - Talk'),
(1371,0,6,'Worm goes on the hook, hook goes in the water. Fish is in the water, our fish.',12,7,100,1,0,0,178,0,'Roman - Talk'),
(1371,0,7,'I thought I heard something.',12,7,100,1,0,0,171,0,'Roman - Talk');

DELETE FROM `waypoint_scripts` WHERE `id` >= 285 and `id` <= 307;
DELETE FROM `waypoint_data` WHERE `id` in (798150,798160,798170);

DELETE FROM `waypoints` WHERE `entry` = 1370;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`point_comment`) VALUES
(1370,1,-8580.51,635.108,96.3386,0,0,'Brandon'),
(1370,2,-8582.773,635.572,96.338,0,0,'Brandon'),
(1370,3,-8593.052,656.774,98.221,0,0,'Brandon'),
(1370,4,-8597.947,657.882,98.377,0,0,'Brandon'),
(1370,5,-8620.59,654.378,99.1946,0,0,'Brandon'),
(1370,6,-8631.83,655.639,100.63,0,0,'Brandon'),
(1370,7,-8639.43,656.589,101.082,0,0,'Brandon'),
(1370,8,-8654.11,660.351,100.865,0,0,'Brandon'),
(1370,9,-8662.717,666.586,100.377,0,0,'Brandon'),
(1370,10,-8669.76,678.045,99.3877,0,0,'Brandon'),
(1370,11,-8671.771,683.623,98.876,0,0,'Brandon'),
(1370,12,-8683.28,695.683,97.8567,0,0,'Brandon'),
(1370,13,-8691.63,704.794,97.1053,0,0,'Brandon'),
(1370,14,-8698.59,714.268,97.0168,0,0,'Brandon'),
(1370,15,-8711.9,732.893,97.8112,0,0,'Brandon'),
(1370,16,-8722.22,747.857,98.0333,0,0,'Brandon'),
(1370,17,-8733.64,764.22,97.9501,0,0,'Brandon'),
(1370,18,-8728.06,775.333,98.0319,0,0,'Brandon'),
(1370,19,-8717.02,792.913,97.1566,0,0,'Brandon'),
(1370,20,-8717.01,798.201,97.1855,0,0,'Brandon'),
(1370,21,-8726.35,812.836,97.0629,0,0,'Brandon'),
(1370,22,-8727.39,831.585,96.2625,0,0,'Brandon'),
(1370,23,-8718.147,846.137,96.43,0,0,'Brandon'),
(1370,24,-8712.475,853.661,96.86,0,0,'Brandon'),
(1370,25,-8709.601,858.748,96.993,0,0,'Brandon'),
(1370,26,-8705.86,860.48,97.0867,0,0,'Brandon'),
(1370,27,-8692.29,871.475,97.0226,0,0,'Brandon'),
(1370,28,-8682.01,878.208,97.0173,0,0,'Brandon'),
(1370,29,-8658.599,900.099,97.549,0,0,'Brandon'),
(1370,30,-8663.312,909.099,96.958,0,0,'Brandon'),
(1370,31,-8667.227,911.786,96.338,0,0,'Brandon'),
(1370,32,-8674.834,911.015,96.338,0,0,'Brandon'),
(1370,33,-8667.227,911.786,96.338,0,0,'Brandon'),
(1370,34,-8663.312,909.099,96.958,0,0,'Brandon'),
(1370,35,-8658.599,900.099,97.549,0,0,'Brandon'),
(1370,36,-8682.01,878.208,97.0173,0,0,'Brandon'),
(1370,37,-8692.29,871.475,97.0226,0,0,'Brandon'),
(1370,38,-8705.86,860.48,97.0867,0,0,'Brandon'),
(1370,39,-8709.601,858.748,96.993,0,0,'Brandon'),
(1370,40,-8712.475,853.661,96.86,0,0,'Brandon'),
(1370,41,-8718.147,846.137,96.43,0,0,'Brandon'),
(1370,42,-8727.39,831.585,96.2625,0,0,'Brandon'),
(1370,43,-8726.35,812.836,97.0629,0,0,'Brandon'),
(1370,44,-8717.01,798.201,97.1855,0,0,'Brandon'),
(1370,45,-8717.02,792.913,97.1566,0,0,'Brandon'),
(1370,46,-8728.06,775.333,98.0319,0,0,'Brandon'),
(1370,47,-8733.64,764.22,97.9501,0,0,'Brandon'),
(1370,48,-8722.22,747.857,98.0333,0,0,'Brandon'),
(1370,49,-8711.9,732.893,97.8112,0,0,'Brandon'),
(1370,50,-8698.59,714.268,97.0168,0,0,'Brandon'),
(1370,51,-8691.63,704.794,97.1053,0,0,'Brandon'),
(1370,52,-8683.28,695.683,97.8567,0,0,'Brandon'),
(1370,53,-8671.771,683.623,98.876,0,0,'Brandon'),
(1370,54,-8669.76,678.045,99.3877,0,0,'Brandon'),
(1370,55,-8662.717,666.586,100.377,0,0,'Brandon'),
(1370,56,-8654.11,660.351,100.865,0,0,'Brandon'),
(1370,57,-8639.43,656.589,101.082,0,0,'Brandon'),
(1370,58,-8631.83,655.639,100.63,0,0,'Brandon'),
(1370,59,-8620.59,654.378,99.1946,0,0,'Brandon'),
(1370,60,-8597.947,657.882,98.377,0,0,'Brandon'),
(1370,61,-8593.052,656.774,98.221,0,0,'Brandon'),
(1370,62,-8582.773,635.572,96.338,0,0,'Brandon');

-- --------------------------------------------------End Justin, Brandon, and Roman------------------------------------------------
DELETE FROM `db_script_string` WHERE `entry` BETWEEN 2000000167 AND 2000000182;
DELETE FROM `waypoint_data` WHERE `id` IN (6348,6350,92307);
DELETE FROM `waypoint_scripts` WHERE `id` IN (127,128,129,130,131,132,133,134,135,136,137,138,139,140,601,602,603,604,605,606,607,608,609);

-- --------------------------------------------------------Karlee Chaddis(2330), Paige(2331), Gil(3504) and Fizzles(1419)----------------------------------------------------------------
UPDATE `creature` SET `movement_type` = 0 WHERE `guid` IN (6192,6196,6183);
UPDATE `creature_addon` SET `path_id` = 0 WHERE `guid` IN (6192,6196,6183);

DELETE FROM `waypoint_data` WHERE `id` IN (6192,6196,6183);
DELETE FROM `waypoint_scripts` WHERE `id` IN (117,118,119,120); 
DELETE FROM `db_script_string` WHERE `entry` IN (2000000184,2000000185,2000000186,2000000200);

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (2330,2331);

DELETE FROM `creature_text` WHERE `CreatureID` IN (3504,2330,2331);
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`,`TextRange`,`comment`) VALUES
(3504,0,0,'Is it true? Are there really crocolisks in the canals?',12,7,100,0,0,0,1098,0,'Gil'),
(3504,0,1,'My feet hurt.',12,7,100,0,0,0,1099,0,'Gil'),
(3504,0,2,'Are we there yet?',12,0,100,0,0,0,2223,0,'Gil'),
(3504,0,3,'Why are we goin\' this way?',12,0,100,0,0,0,1093,0,'Gil'),
(3504,0,4,'I wanna see the Mage Tower.',12,7,100,0,0,0,1097,0,'Gil'),
(3504,0,5,'Where we goin\'?',12,7,100,0,0,0,1094,0,'Gil'),
(3504,0,6,'Why do we always go the same way?',12,7,100,0,0,0,1100,0,'Gil'),
(3504,0,7,'I need to pee.',12,0,100,0,0,0,1095,0,'Gil'),
(3504,1,0,'Billy says Fizzles used to be a great wizard. But he got turned into a rabbit when one of his spells went bad.',12,0,100,0,0,0,1091,0,'Gil'),
(2330,0,0,'Hello, Charys. I have my list, could you get me all of that, especially the last ingredient.',12,7,100,0,0,0,587,0,'Karlee Chaddis'),
(2330,1,0,'Sure, Paige. Just be gentle.',12,7,100,0,0,0,589,0,'Karlee Chaddis'),
(2330,2,0,'Thanks, Charys. C\'mon Paige, sweetie.',12,0,100,0,0,0,590,0,'Karlee Chaddis'),
(2331,0,0,'Mommy? Can I pet Fizzles?',12,0,100,0,0,0,588,0,'Paige Chaddis');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3504,2330,2331,233000);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param5`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_param4`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(3504,0,0,0,1,0,100,0,60000,60000,180000,200000,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Gil - Out of Combat - Say Random 0 (No Repeat)'),
(3504,0,1,0,38,0,100,0,1,0,0,0,0,29,0,160,0,0,0,0,10,90439,2330,0,0,0,0,0,0,'Gil - On Data Set 1 0 - Set Follow'),
(3504,0,2,0,38,0,100,0,1,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Gil - On Data Set 1 1 - Say Line 1'),

(2331,0,0,0,38,0,100,0,1,0,0,0,0,29,0,200,0,0,0,0,10,90439,2330,0,0,0,0,0,0,'Paige Chaddis - On Data Set 1 0 - Set Follow'),
(2331,0,1,0,38,0,100,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Paige Chaddis - On Data Set 1 1 - Say Line 0'),

(2330,0,0,1,1,0,100,1,25000,25000,0,0,0,53,0,2330,1,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis - OOC (No Repeat) - Start Waypoint'),
(2330,0,1,2,61,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,90443,3504,0,0,0,0,0,0,'Karlee Chaddis - Linked - Set Data 1 0 \'Gil\''),
(2330,0,2,0,61,0,100,0,0,0,0,0,0,45,1,0,0,0,0,0,10,90440,2331,0,0,0,0,0,0,'Karlee Chaddis - Linked - Set Data 1 0 \'Paige Chaddis\''),
(2330,0,3,0,40,0,100,0,28,2330,0,0,0,80,233000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis - On Waypoint 28 Reached - Run Script'),

(233000,9,0,0,0,0,100,0,0,0,0,0,0,54,60000,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis - On Script - Pause Waypoint'),
(233000,9,1,0,0,0,100,0,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0,1.074,'Karlee Chaddis- On Script - Set Orientation'),
(233000,9,2,0,0,0,100,0,1000,1000,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis- On Script - Say Line 0'),
(233000,9,3,0,0,0,100,0,14000,14000,0,0,0,45,1,1,0,0,0,0,10,90440,2331,0,0,0,0,0,0,'Karlee Chaddis- On Script - Set Data 1 1 \'Paige Chaddis\''),
(233000,9,4,0,0,0,100,0,8000,8000,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis- On Script - Say Line 1'),
(233000,9,5,0,0,0,100,0,10000,10000,0,0,0,45,1,1,0,0,0,0,10,90443,3504,0,0,0,0,0,0,'Karlee Chaddis- On Script - Set Data 1 1 \'Gil\''),
(233000,9,6,0,0,0,100,0,20000,20000,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis- On Script - Say Line 2'),
(233000,9,7,0,0,0,100,0,4000,4000,0,0,0,5,3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,'Karlee Chaddis - On Script - Emote Wave');

DELETE FROM `waypoints` WHERE `entry` = 2330;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`point_comment`) VALUES
(2330,1,-8856.26,741.91,100.666,0,0,'Karlee Chaddis'),
(2330,2,-8860.26,747.938,99.9222,0,0,'Karlee Chaddis'),
(2330,3,-8866.15,756.326,97.8264,0,0,'Karlee Chaddis'),
(2330,4,-8870.51,760.372,96.7027,0,0,'Karlee Chaddis'),
(2330,5,-8879.54,756.138,96.2687,0,0,'Karlee Chaddis'),
(2330,6,-8883.45,758.191,95.4731,0,0,'Karlee Chaddis'),
(2330,7,-8907.48,788.261,87.7863,0,0,'Karlee Chaddis'),
(2330,8,-8906.29,794.423,87.3173,0,0,'Karlee Chaddis'),
(2330,9,-8899.1,801.189,87.6105,0,0,'Karlee Chaddis'),
(2330,10,-8899.88,815.041,89.3389,0,0,'Karlee Chaddis'),
(2330,11,-8899.09,826.687,92.5864,0,0,'Karlee Chaddis'),
(2330,12,-8905.65,841.38,95.4271,0,0,'Karlee Chaddis'),
(2330,13,-8905.3,845.868,95.7969,0,0,'Karlee Chaddis'),
(2330,14,-8898.15,863.912,96.2546,0,0,'Karlee Chaddis'),
(2330,15,-8893.39,873.065,98.9773,0,0,'Karlee Chaddis'),
(2330,16,-8888.58,889.208,102.944,0,0,'Karlee Chaddis'),
(2330,17,-8888.8,897.531,105.943,0,0,'Karlee Chaddis'),
(2330,18,-8896.33,913.303,110.988,0,0,'Karlee Chaddis'),
(2330,19,-8904.33,926.304,114.899,0,0,'Karlee Chaddis'),
(2330,20,-8919.41,948.481,117.337,0,0,'Karlee Chaddis'),
(2330,21,-8966.43,954.028,117.362,0,0,'Karlee Chaddis'),
(2330,22,-8982.42,966.381,116.043,0,0,'Karlee Chaddis'),
(2330,23,-8999.42,964.996,116.326,0,0,'Karlee Chaddis'),
(2330,24,-9012.36,953.626,116.256,0,0,'Karlee Chaddis'),
(2330,25,-9008.41,945.283,116.895,0,0,'Karlee Chaddis'),
(2330,26,-9000.86,940.914,117.094,0,0,'Karlee Chaddis'),
(2330,27,-8998.38,939.901,117.094,0,0,'Karlee Chaddis'),
(2330,28,-8996.34,945.169,117.097,0,0,'Karlee Chaddis'),
(2330,29,-8999.05,940.572,117.096,0,0,'Karlee Chaddis'),
(2330,30,-9002.62,941.706,117.095,0,0,'Karlee Chaddis'),
(2330,31,-9012.38,947.61,116.227,0,0,'Karlee Chaddis'),
(2330,32,-9012.45,951.694,116.246,0,0,'Karlee Chaddis'),
(2330,33,-9004.83,961.988,116.276,0,0,'Karlee Chaddis'),
(2330,34,-8998.64,965.802,116.292,0,0,'Karlee Chaddis'),
(2330,35,-8983.94,966.422,116.028,0,0,'Karlee Chaddis'),
(2330,36,-8980.01,965.284,116.256,0,0,'Karlee Chaddis'),
(2330,37,-8971.05,960.59,117.158,0,0,'Karlee Chaddis'),
(2330,38,-8957.87,953.377,117.299,0,0,'Karlee Chaddis'),
(2330,39,-8920.67,947.641,117.337,0,0,'Karlee Chaddis'),
(2330,40,-8908.711,932.625,116.370,0,0,'Karlee Chaddis'),
(2330,41,-8903.206,925.242,114.615,0,0,'Karlee Chaddis'),
(2330,42,-8899.662,918.715,112.635,0,0,'Karlee Chaddis'),
(2330,43,-8894.54,911.478,110.762,0,0,'Karlee Chaddis'),
(2330,44,-8877.53,920.808,107.603,0,0,'Karlee Chaddis'),
(2330,45,-8854.97,933.374,101.999,0,0,'Karlee Chaddis'),
(2330,46,-8848.88,930.711,102.495,0,0,'Karlee Chaddis'),
(2330,47,-8834.61,940.936,105.143,0,0,'Karlee Chaddis'),
(2330,48,-8818.28,953.205,100.678,0,0,'Karlee Chaddis'),
(2330,49,-8815.14,952.722,100.867,0,0,'Karlee Chaddis'),
(2330,50,-8804.01,942.261,101.241,0,0,'Karlee Chaddis'),
(2330,51,-8802.37,936.981,101.242,0,0,'Karlee Chaddis'),
(2330,52,-8777.24,909.299,100.262,0,0,'Karlee Chaddis'),
(2330,53,-8766.76,893.892,101.386,0,0,'Karlee Chaddis'),
(2330,54,-8737.03,892.761,101.221,0,0,'Karlee Chaddis'),
(2330,55,-8731.93,886.272,101.744,0,0,'Karlee Chaddis'),
(2330,56,-8723.13,875.04,102.678,0,0,'Karlee Chaddis'),
(2330,57,-8712.31,861.661,97.2752,0,0,'Karlee Chaddis'),
(2330,58,-8712.2,853.618,96.8655,0,0,'Karlee Chaddis'),
(2330,59,-8725.87,834.533,96.149,0,0,'Karlee Chaddis'),
(2330,60,-8726.58,813.587,97.0276,0,0,'Karlee Chaddis'),
(2330,61,-8717.15,795.784,97.0391,0,0,'Karlee Chaddis'),
(2330,62,-8721.79,782.622,97.8839,0,0,'Karlee Chaddis'),
(2330,63,-8732.2,766.047,98.0898,0,0,'Karlee Chaddis'),
(2330,64,-8724.93,751.443,98.2043,0,0,'Karlee Chaddis'),
(2330,65,-8713.3,732.548,97.8146,0,0,'Karlee Chaddis'),
(2330,66,-8699.05,715.705,97.0168,0,0,'Karlee Chaddis'),
(2330,67,-8661.63,744.699,96.6531,0,0,'Karlee Chaddis'),
(2330,68,-8660.26,765.872,96.6997,0,0,'Karlee Chaddis'),
(2330,69,-8634.36,787.361,96.6525,0,0,'Karlee Chaddis'),
(2330,70,-8632.43,787.372,96.6512,0,0,'Karlee Chaddis'),
(2330,71,-8606.16,761.17,96.7387,0,0,'Karlee Chaddis'),
(2330,72,-8592.08,756.77,96.651,0,0,'Karlee Chaddis'),
(2330,73,-8579.7,737.671,96.7114,0,0,'Karlee Chaddis'),
(2330,74,-8594.53,717.706,96.6514,0,0,'Karlee Chaddis'),
(2330,75,-8581.67,697.638,97.0168,0,0,'Karlee Chaddis'),
(2330,76,-8561.08,673.827,97.0168,0,0,'Karlee Chaddis'),
(2330,77,-8536.53,690.079,97.6665,0,0,'Karlee Chaddis'),
(2330,78,-8530.805,685.554,97.8444,0,0,'Karlee Chaddis'),
(2330,79,-8528.41,679.123,100.793,0,0,'Karlee Chaddis'),
(2330,80,-8517.6,662.84,102.123,0,0,'Karlee Chaddis'),
(2330,81,-8510.36,651.605,100.292,0,0,'Karlee Chaddis'),
(2330,82,-8516.68,643.439,100.134,0,0,'Karlee Chaddis'),
(2330,83,-8557.25,615.273,102.337,0,0,'Karlee Chaddis'),
(2330,84,-8563.65,615.408,102.278,0,0,'Karlee Chaddis'),
(2330,85,-8583.79,586.194,103.594,0,0,'Karlee Chaddis'),
(2330,86,-8584.4,560.743,101.871,0,0,'Karlee Chaddis'),
(2330,87,-8578.23,543.501,101.782,0,0,'Karlee Chaddis'),
(2330,88,-8593.35,530.953,105.659,0,0,'Karlee Chaddis'),
(2330,89,-8609.85,515.571,103.841,0,0,'Karlee Chaddis'),
(2330,90,-8616.86,517.629,103.218,0,0,'Karlee Chaddis'),
(2330,91,-8657.5,553.006,96.9502,0,0,'Karlee Chaddis'),
(2330,92,-8673.57,552.873,97.2864,0,0,'Karlee Chaddis'),
(2330,93,-8713.67,519.808,97.1597,0,0,'Karlee Chaddis'),
(2330,94,-8717.22,524.985,98.1892,0,0,'Karlee Chaddis'),
(2330,95,-8724.539,533.765,100.2637,0,0,'Karlee Chaddis'),
(2330,96,-8734.436,545.427,101.1412,0,0,'Karlee Chaddis'),
(2330,97,-8745.36,557.023,97.6718,0,0,'Karlee Chaddis'),
(2330,98,-8745,566.133,97.4006,0,0,'Karlee Chaddis'),
(2330,99,-8738.14,576.508,97.5043,0,0,'Karlee Chaddis'),
(2330,100,-8769.94,608.175,97.1405,0,0,'Karlee Chaddis'),
(2330,101,-8795.54,589.658,97.4546,0,0,'Karlee Chaddis'),
(2330,102,-8832.6,630.401,94.0918,0,0,'Karlee Chaddis'),
(2330,103,-8851.55,661.112,97.1319,0,0,'Karlee Chaddis'),
(2330,104,-8824.74,678.622,97.5366,0,0,'Karlee Chaddis'),
(2330,105,-8847.34,726.835,97.6974,0,0,'Karlee Chaddis');

-- Fizzles
DELETE FROM `creature` WHERE `guid` = 189122;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawntimesecs_max`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `movement_type`, `npcflag`, `npcflag2`, `unit_flags`, `unit_flags2`, `dynamicflags`, `ScriptName`, `walk_mode`) VALUES 
(189122, 1419, 0, 1519, 5154, 1, 1, 328, 0, -8994.19, 947.069, 118.348, 4.29351, 300, 0, 3, 0, 8, 0, 1, 0, 0, 0, 0, 0, '', 0);

-- --------------------------------------------------------Karlee Chaddis, Paige, Gil and Fizzles-------------------------------------------------------------------

DELETE FROM `waypoint_scripts` WHERE `id` NOT IN (SELECT `action` FROM `waypoint_data`);
DELETE FROM `db_script_string` WHERE `entry` NOT IN (SELECT `dataint` FROM `waypoint_scripts`);