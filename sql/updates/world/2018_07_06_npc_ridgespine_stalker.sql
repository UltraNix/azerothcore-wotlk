UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 20714;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 20714;
INSERT INTO `smart_scripts` VALUES
(20714, 0, 0, 0, 0, 0, 100, 0, 10000, 20000, 20000, 25000, 11, 744, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ridgespine Stalker - In Combat - Cast Poison'),
(20714, 0, 1, 0, 1, 0, 100, 1, 1000, 2000, 0, 0, 11, 22766, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ridgespine Stalker - Out Of Combat - Cast Sneak');
