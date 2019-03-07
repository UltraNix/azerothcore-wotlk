-- DB/Quest: Morbent Fel - Unholy shield should be dispelled always
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 1200;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1200;
INSERT INTO `smart_scripts` VALUES
(1200, 0, 0, 0, 8, 0, 100, 0, 8913, 0, 0, 0, 28, 8909, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1200, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 8909, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
