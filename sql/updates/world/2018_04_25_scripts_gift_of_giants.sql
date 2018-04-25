UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 26260;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 26260;
INSERT INTO `smart_scripts` VALUES
(26260, 0, 0, 0, 19, 0, 100, 0, 11982, 0, 0, 0, 11, 47012, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Kurun - On Quest Raining Down Destruction Taken - Cast Gift of the Giants');
