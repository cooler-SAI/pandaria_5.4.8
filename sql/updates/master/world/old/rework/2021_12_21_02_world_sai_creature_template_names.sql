UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (SELECT `entryorguid` FROM `smart_scripts`);
