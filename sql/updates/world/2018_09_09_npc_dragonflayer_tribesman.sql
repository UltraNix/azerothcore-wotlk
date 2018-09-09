UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23651;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23651;
INSERT INTO `smart_scripts` VALUES
(23651, 0, 0, 0, 0, 0, 80, 0, 9000, 9000, 6000, 7000, 11, 15496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Tribesman - Combat - Cast Cleave'),
(23651, 0, 1, 0, 2, 0, 100, 0, 0, 50, 0, 0, 11, 48193, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Tribesman - Combat (0-50%) - Cast Enrage');
