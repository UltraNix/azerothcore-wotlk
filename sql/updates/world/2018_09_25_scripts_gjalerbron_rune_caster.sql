UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23990;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23990;
INSERT INTO `smart_scripts` VALUES
(23990, 0, 0, 0, 0, 0, 100, 0, 10000, 12000, 10000, 15000, 11, 34787, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Combat - Cast Frezzing circle'),
(23990, 0, 2, 0, 0, 0, 100, 0, 10000, 12000, 10000, 15000, 11, 43453, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Combat - Cast Rune Ward'),
(23990, 0, 1, 0, 0, 0, 100, 0, 5000, 8000, 5000, 8000, 11, 12737, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ' Combat  - Cast Frostbolt');
