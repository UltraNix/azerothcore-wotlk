SET @CGUID = 501511;
DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` VALUES
(@CGUID, 8924, 0, 1, 1, 0, 0,  -7365.01, -1006.1, 176.902, 2.89516, 108000, 5, 0, 11042, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14229;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14229;
INSERT INTO `smart_scripts` VALUES
(14229, 0, 0, 0, 0, 0, 100, 0, 9000, 12000, 9000, 12000, 11, 7947, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Toxin');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14228;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14228;
INSERT INTO `smart_scripts` VALUES
(14228, 0, 0, 0, 0, 0, 100, 0, 9000, 12000, 9000, 12000, 11, 3150, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Rabbies');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14227;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14227;
INSERT INTO `smart_scripts` VALUES
(14227, 0, 0, 0, 0, 0, 100, 0, 9000, 12000, 15000, 18000, 11, 11020, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Petrify');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14226;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14226;
INSERT INTO `smart_scripts` VALUES
(14226, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 13730, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'On Aggro - Cast Demo Shout'),
(14226, 0, 1, 0, 0, 0, 100, 0, 9000, 12000, 9000, 12000, 11, 22859, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Cleave');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14226;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14226;
INSERT INTO `smart_scripts` VALUES
(14226, 0, 0, 0, 2, 0, 100, 0, 0, 25, 0, 0, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Aggro - Cast Enrage'),
(14226, 0, 1, 0, 0, 0, 100, 0, 9000, 12000, 9000, 12000, 11, 35913, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast Fel Fireball');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 4380;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4380;
INSERT INTO `smart_scripts` VALUES
(4380, 0, 0, 0, 0, 0, 100, 0, 0, 1000, 5900, 14200, 11, 744, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast \'Poison\' (No Repeat)'),
(4380, 0, 1, 0, 0, 0, 100, 0, 5000, 11000, 22000, 33000, 11, 43134, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'In Combat - Cast \'Summon Spiderlings\' (No Repeat)');

DELETE FROM `creature` WHERE `guid` = 501512;
INSERT INTO `creature` VALUES 
(501512, 14231, 1, 1, 1, 0, 0,  -2799.72, -3129.45, 28.7032, 4.41743, 27000, 5, 0, 1525, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `guid` = 501513;
INSERT INTO `creature` VALUES 
(501513, 14237, 1, 1, 1, 0, 0,  -4207.99, -2911.04, 44.9497, 2.051, 180000, 5, 0, 2508, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `guid` = 501514;
INSERT INTO `creature` VALUES 
(501514, 14233, 1, 1, 1, 0, 0, -4158.55, -3446.35, 28.5577, 1.14702, 38000, 5, 0, 1653, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `guid` = 501515;
INSERT INTO `creature` VALUES 
(501515, 14235, 1, 1, 1, 0, 0, -4042.09, -3753.6, 43.2492, 6.26622, 108000, 5, 0, 5620, 0, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry` = 10817;
INSERT INTO `creature_text` VALUES
(10817, 0, 0, 'Ooooooooh...', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 1, 0, 'To the plaguelands went old Duggan, ta\' send them Scourge back inta\' th\' groun\'.', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 2, 0, 'Where th\' scent of death is on th\' wind and everythin\' is mostly brown.', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 3, 0, 'An\' when he did arrive there, what\'d his dwarf eyes see?', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 4, 0, 'A hundred crates of barley there ta\' be makin\' inta\' mead!', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 5, 0, 'But tha\' mead was cursed with th\' plague o\' death, and now old Duggan, too.', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 6, 0, 'An\' surrounded by the Lich King\'s beasts, what could old Duggan do?', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 7, 0, 'But though I feel the plague within, my hopes \'ave not yet sunk.', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 8, 0, 'If\'n I\'m gonna be Scourge anyway, I might as well be drunk!', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer'),
(10817, 9, 0, 'Ah ken see very well through this haze, but I\'d know tha\' smell anywhere! Die ye foul ogre!', 12, 0, 100, 0, 0, 0, 0, 'Duggan Wildhammer');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 10817;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (10817, 1081700);
INSERT INTO `smart_scripts` VALUES
(10817, 0, 0, 0, 1, 0, 100, 0, 5000, 45000, 60000, 60000, 80, 1081700, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(10817, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,  ''),
(1081700, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 7, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(1081700, 9, 8, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
