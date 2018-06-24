UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 21071;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21071;
INSERT INTO `smart_scripts` VALUES
(21071, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Totem of Spirit - On Reset - Auto attack off'),
(21071, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Totem of Spirit - On Reset - Disable Combat Movement');
