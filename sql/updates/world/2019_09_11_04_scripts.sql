-- DB/NPC: Hraug - add imp
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 12776;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 12776;
INSERT INTO `smart_scripts` VALUES
(12776, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 688, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
