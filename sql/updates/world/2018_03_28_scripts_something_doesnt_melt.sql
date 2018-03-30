SET @GOBLIN = 26661;
SET @MACHINE = 26677;

DELETE FROM `creature_text` WHERE `entry` = @GOBLIN;
INSERT INTO `creature_text` VALUES
(@GOBLIN, 0, 0, 'The control components are working perfectly this time!', 12, 0, 100, 0, 0, 0, 0, ''),
(@GOBLIN, 1, 0, 'Who to test the bomb on? The Harpies? Ha ha... wait... what\'s that?', 12, 0, 100, 0, 0, 0, 0, ''),
(@GOBLIN, 2, 0, 'NO! My machine... my bombs! THAT\'S IT! Those Harpies are going DOWN!', 12, 0, 100, 0, 0, 0, 0, ''),
(@GOBLIN, 3, 0, 'Talk to Narf. Lets take care of those bird - brains once and for all.', 12, 0, 100, 0, 0, 0, 0, '');

UPDATE `creature` SET `MovementType` = 0 WHERE `guid` = 100815;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @MACHINE;
UPDATE `creature_template` SET `AIName` = "SmartAI", `InhabitType` = 7, `speed_walk` = 4 WHERE `entry` = @MACHINE;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@GOBLIN, @MACHINE, @GOBLIN*100);
INSERT INTO `smart_scripts` VALUES
(@GOBLIN, 0, 0, 0, 20, 0, 100, 0, 12047, 0, 0, 0, 80, @GOBLIN*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - On Quest Rewarded - Start Script'),
(@GOBLIN*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Remove npc flags'),
(@GOBLIN*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 100815, 26677, 0, 0, 0, 0, 0, 'Zivlix - Script - Set Data On Machine'),
(@GOBLIN*100, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Say line 0'),
(@GOBLIN*100, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4719.08, 547.26, 128.31, 5.8, 'Zivlix - Script - Move to Pos'),
(@GOBLIN*100, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Say line 1'),
(@GOBLIN*100, 9, 5, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Say line 2'),
(@GOBLIN*100, 9, 6, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Evade'),
(@GOBLIN*100, 9, 7, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Say line 3'),
(@GOBLIN*100, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zivlix - Script - Restore NPC flags'),
(@MACHINE, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 0, @MACHINE, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Flying machine - On Data Set - Start WP'),
(@MACHINE, 0, 1, 0, 40, 0, 100, 0, 22, @MACHINE, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Flying machine - On WP Reached - Despawn');

DELETE FROM `waypoints` WHERE `entry` = @MACHINE;
INSERT INTO `waypoints` VALUES
(@MACHINE, 1, 4705.099, 561.415, 124.76834, ''),
(@MACHINE, 2, 4701.870, 562.744, 124.54636, ''),
(@MACHINE, 3, 4695.454, 565.495, 124.07948, ''),
(@MACHINE, 4, 4689.048, 568.280, 123.61164, ''),
(@MACHINE, 5, 4688.750, 570.935, 124.07615, ''),
(@MACHINE, 6, 4693.898, 576.910, 126.16060, ''),
(@MACHINE, 7, 4700.463, 579.642, 126.82507, ''),
(@MACHINE, 8, 4705.939, 579.735, 127.06030, ''),
(@MACHINE, 9, 4712.849, 578.202, 127.47134, ''),
(@MACHINE, 10, 4719.284, 573.972, 128.65717, ''),
(@MACHINE, 11, 4723.077, 569.007, 129.91052, ''),
(@MACHINE, 12, 4727.906, 559.888, 131.67577, ''),
(@MACHINE, 13, 4730.174, 553.325, 132.54909, ''),
(@MACHINE, 14, 4731.967, 546.584, 133.09767, ''),
(@MACHINE, 15, 4734.342, 537.089, 133.51141, ''),
(@MACHINE, 16, 4736.701, 530.503, 133.76793, ''),
(@MACHINE, 17, 4739.980, 523.555, 133.91095, ''),
(@MACHINE, 18, 4745.902, 516.351, 133.86290, ''),
(@MACHINE, 19, 4752.923, 512.353, 133.61752, ''),
(@MACHINE, 20, 4760.559, 511.697, 133.49355, ''),
(@MACHINE, 21, 4764.944, 513.848, 133.56981, ''),
(@MACHINE, 22, 4770.740, 518.542, 133.90511, '');
