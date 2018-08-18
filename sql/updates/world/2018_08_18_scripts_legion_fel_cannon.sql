UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 22451;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 22451;
INSERT INTO `smart_scripts` VALUES
(22451, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Legion Fel Cannon MKII - On Reset - Disable Combat Movement'),
(22451, 0, 1, 0,  0, 0, 100, 0, 3000, 5000, 3000, 5000, 11, 36238, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Legion Fel Cannon MKII - In Combat - Cast Fel Cannon Blast');

UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 2 WHERE `entry` = 22451;
