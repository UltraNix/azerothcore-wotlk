UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (18192, 18256);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (18256, 18192);
INSERT INTO `smart_scripts` VALUES
(18192, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 71, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Horde Halaa Guards - Reset - Load Equipment'),
(18256, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 71, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Halaa Guards - Reset - Load Equipment');
