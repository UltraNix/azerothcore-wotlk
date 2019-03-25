UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 510;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 510;
INSERT INTO `smart_scripts` VALUES
(510, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
