UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 21423;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21423;
INSERT INTO `smart_scripts` VALUES
(21423, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 30000, 45000, 11, 13443, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Gore-Scythe Ravager - In Combat - Cast Rend');
