UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24029;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 24029;
INSERT INTO `smart_scripts` VALUES
(24029, 0, 0, 0, 0, 0, 100, 0, 3000, 6000, 5000, 8000, 11, 9672, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Wyrmcaller Vile - IC - Cast Frostbolt'),
(24029, 0, 1, 0, 0, 0, 100, 0, 10000, 16000, 15000, 18000, 11, 15532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Wyrmcaller Vile - IC - Cast FrostNova');
