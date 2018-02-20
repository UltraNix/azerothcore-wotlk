UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 3280;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 3280;
INSERT INTO `smart_scripts` VALUES
(3280, 0, 0, 0, 0, 0, 100, 0, 0, 0, 3400, 4700, 11, 57780, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Witchwing Windcaller - In Combat - Cast \'Lightning Bolt\''),
(3280, 0, 1, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Witchwing Windcaller - Between 0-15% Health - Flee For Assist (No Repeat)'),
(3280, 0, 2, 0, 0, 0, 100, 0, 6000, 8000, 22000, 24000, 11, 6728, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 'Witchwing Windcaller - In Combat - Cast \'Enveloping Winds\'');
