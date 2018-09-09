UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23932;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23651;
INSERT INTO `smart_scripts` VALUES
(23932, 0, 0, 0, 4, 0, 80, 0, 0, 0, 0, 0, 11, 58747, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Yanis the Mystic - Aggro - Cast Intercept'),
(23932, 0, 1, 0, 0, 0, 100, 0, 5000, 8000, 10000, 15000, 11, 42870, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Yanis the Mystic - Combat  - Cast Throw Harpoon');
