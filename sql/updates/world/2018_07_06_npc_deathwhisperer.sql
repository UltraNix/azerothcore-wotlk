UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 19299;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19299;
INSERT INTO `smart_scripts` VALUES
(19299, 0, 0, 0, 0, 0, 100, 0, 5000, 15000, 45000, 60000, 11, 17687, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Deathwhisperer - In Combat - Cast Flurry');
