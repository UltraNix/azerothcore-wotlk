UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 1200;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24782;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 24782;
INSERT INTO `smart_scripts` VALUES
(24782, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 28, 8909, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

UPDATE `smart_scripts` SET `link` = 2 WHERE `entryorguid` = 1200 AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1200 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(1200, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 36, 24782, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
