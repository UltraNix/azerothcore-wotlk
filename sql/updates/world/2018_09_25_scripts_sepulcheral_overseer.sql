UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23993;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23993;
INSERT INTO `smart_scripts` VALUES
(23993, 0, 0, 0, 0, 0, 100, 0, 10000, 12000, 10000, 15000, 11, 22744, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sepulcheral Overseer - Combat - Cast Chains'),
(23993, 0, 1, 0, 0, 0, 100, 0, 5000, 8000, 5000, 8000, 11, 12737, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sepulcheral Overseer - Combat  - Cast Frostbolt');
