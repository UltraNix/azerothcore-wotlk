UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24344;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 24344;
INSERT INTO `smart_scripts` VALUES
(24344, 0, 0, 0, 1, 0, 100, 1, 10000, 10000, 10000, 10000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Despawn 10 sec OOC');
