UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 8836;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 8836;
INSERT INTO `smart_scripts` VALUES
(8836, 0, 0, 0, 0, 0, 40, 0, 0, 20000, 30000, 60000, 11, 23060, 3, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Gnomish battle chicken - IC - Cast Battle Squawk'), 
(8836, 0, 1, 0, 0, 0, 30, 0, 0, 10000, 60000, 120000, 11, 13168, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gnomish battle chicken - IC - Cast Chicken Fury');
