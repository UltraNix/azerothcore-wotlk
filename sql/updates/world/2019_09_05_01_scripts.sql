UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 10639;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 10639;
INSERT INTO `smart_scripts`  VALUES
(10639, 0, 0, 0, 0, 0, 100, 0, 1000, 4000, 10000, 15000, 11, 8876, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rorgish Jowl - In Combat - Cast \'Thrash\' (Phase 1) (No Repeat) (Normal Dungeon)'),
(10639, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 6813, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rorgish Jowl - Reset - Apply Aura Coat of Thistlefur');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 10640;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 10640;
INSERT INTO `smart_scripts`  VALUES
(10640, 0, 0, 0, 2, 0, 100, 0, 0, 50, 15000, 180000, 11, 12160, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Oakpaw - Between 0-50% Health - Cast \'Rejuvenation\' (Phase 1) (No Repeat) (Normal Dungeon)'),
(10640, 0, 1, 0, 0, 0, 100, 0, 3000, 6000, 15000, 18000, 11, 6817, 0, 0, 0, 0, 0, 5, 20, 0, 0, 0, 0, 0, 0, 'Oakpaw - IC - Cast Agility'),
(10640, 0, 2, 0, 0, 0, 100, 0, 9000, 14000, 15000, 18000, 11, 6818, 0, 0, 0, 0, 0, 5, 20, 0, 0, 0, 0, 0, 0, 'Oakpaw - IC - Cast Intelect'),
(10640, 0, 3, 0, 0, 0, 100, 0, 0, 50, 15000, 18000, 11, 6819, 0, 0, 0, 0, 0, 5, 20, 0, 0, 0, 0, 0, 0, 'Oakpaw - IC - Cast Stamina');

DELETE FROM `creature` WHERE `id` IN (11447,11497, 11498);
INSERT INTO `creature` VALUES 
(500345, 11447, 1, 1, 1, 0, 0, -3799.62, 1063.83, 132.806, 1.20424, 21600, 5, 0, 60000, 0, 0, 0, 0, 0),
(500346, 11497, 1, 1, 1, 0, 0, -3731.22, 1061.32, 132.345, 1.7815, 21600, 5, 0, 73000, 24340, 0, 0, 0, 0),
(500347, 11498, 1, 1, 1, 0, 0, -3690.96, 1077.14, 131.969, 2.65172, 21600, 5, 0, 57000, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (11447,11497,11498);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (11447,11497,11498);
SET @ENTRY = 11447;
SET @SPELL1 = 21749;
SET @SPELL2 = 31689;
SET @SPELL3 = 24648;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 4000, 7000, 10000, 15000, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 8000, 12000, 20000, 25000, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 2, 0, 0, 0, 100, 0, 2000, 5000, 15000, 20000, 11, @SPELL3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 11497;
SET @SPELL1 = 16033;
SET @SPELL2 = 22951;
SET @SPELL3 = 22937;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 4000, 7000, 10000, 15000, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 8000, 12000, 20000, 25000, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 2, 0, 0, 0, 100, 0, 2000, 5000, 15000, 20000, 11, @SPELL3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 11498;
SET @SPELL1 = 15496;
SET @SPELL2 = 11428;
SET @SPELL3 = 15708;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 4000, 7000, 10000, 15000, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 8000, 12000, 20000, 25000, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 2, 0, 0, 0, 100, 0, 2000, 5000, 15000, 20000, 11, @SPELL3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 2754;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2754;
INSERT INTO `smart_scripts` VALUES 
(2754, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 11671, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'The Evalcharr - In Combat - Cast Fireball'),
(2754, 0, 1, 0, 0, 0, 100, 0, 8000, 10000, 11000, 14000, 11, 33333, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'The Evalcharr - In Combat - Cast Lightning Breath');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 2751;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2751;
INSERT INTO `smart_scripts` VALUES 
(2751, 0, 0, 0, 0, 0, 100, 0, 3000, 6000, 22000, 25000, 11, 9576, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Lockdown');


DELETE FROM `creature_text` WHERE `entry` = 8296;
INSERT INTO `creature_text` VALUES
(8296, 0, 0, 'I\ll crush you!', 14, 0, 100, 0, 0, 0, 0, 'Mojo the Twisted '),
(8296, 0, 1, 'Me smash! You die!', 14, 0, 100, 0, 0, 0, 0, 'Mojo the Twisted '),
(8296, 0, 2, 'Raaar!!! Me smash !', 14, 0, 100, 0, 0, 0, 0, 'Mojo the Twisted ');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 8296 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES 
(8296, 0, 2, 0, 0, 0, 100, 0, 0, 3000, 9000, 14000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mojo the Twisted - IC - Say 0');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 12431;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 12431;
INSERT INTO `smart_scripts` VALUES 
(12431, 0, 0, 0, 0, 0, 100, 0, 0, 40, 5000, 14700, 11, 13445, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Rend');
