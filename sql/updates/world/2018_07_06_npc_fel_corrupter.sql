UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 21300;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21300;
INSERT INTO `smart_scripts` VALUES
(21300, 0, 0, 0, 0, 0, 100, 0, 2000, 3000, 8000, 12000, 11, 9613, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Fel Corrupter - In Combat - Cast Shadow Bolt');
