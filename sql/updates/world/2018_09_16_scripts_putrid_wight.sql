UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23992;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23992;
INSERT INTO `smart_scripts` VALUES
(23992, 0, 0, 0, 0, 0, 100, 0, 13000, 16000, 15000, 18000, 11, 43505, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Putrid Wight - IC - Cast Blight'),
(23992, 0, 1, 0, 0, 0, 100, 0, 10000, 16000, 15000, 18000, 11, 8078, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Putrid Wight - IC - Cast Thunderclap');
