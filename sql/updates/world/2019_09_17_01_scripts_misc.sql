UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 21909;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21909;
INSERT INTO `smart_scripts` VALUES
(21909, 0, 0, 0, 29, 0, 100, 0, 1, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

UPDATE `creature` SET `spawntimesecs` = 10 WHERE `id` = 21909;
