UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 6508;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 6508;
INSERT INTO `smart_scripts` VALUES
(6508, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 11, 14108, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Venomhide Ravasaur - On Respawn - Cast \'Venomhide Poison\'');
