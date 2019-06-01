SET @ENTRY = 23643;
SET @TIMER1 = 5000;
SET @TIMER2 = 10000;
SET @SPELL1 = 49948;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 50, 0, @TIMER1, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23644;
SET @TIMER1 = 4000;
SET @TIMER2 = 8000;
SET @TIMER3 = 12000;
SET @SPELL1 = 13445;
SET @SPELL2 = 37933;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER3, @TIMER2, @TIMER3, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23653;
SET @TIMER1 = 10000;
SET @TIMER2 = 15000;
SET @SPELL1 = 32908;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23654;
SET @TIMER1 = 10000;
SET @TIMER2 = 25000;
SET @SPELL1 = 48280;
SET @SPELL2 = 48281;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23655;
SET @TIMER1 = 6000;
SET @TIMER2 = 14000;
SET @SPELL1 = 43951;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23657;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 9053;
SET @SPELL2 = 11829;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23674;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 20828;
SET @SPELL2 = 20823;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23676;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 48376;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23688;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 51218;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23711;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 48374;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23739;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 12170;
SET @SPELL2 = 42476;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23740;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 29577;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23744;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 12734;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23796;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 15039;
SET @SPELL2 = 48599;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23842;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 6660;
SET @SPELL2 = 7164;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23844;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 6660;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23865;
SET @TIMER1 = 0;
SET @TIMER2 = 0;
SET @TIMER3 = 0;
SET @SPELL1 = 32064;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23871;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 15496;
SET @SPELL2 = 6533;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23919;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 43543;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 23940;
SET @TIMER1 = 10000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 8599;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24026;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 50075;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24050;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 12169;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24169;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 48245;
SET @SPELL2 = 48250;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24212;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 49643;
SET @SPELL2 = 49644;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24371;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 50086;
SET @SPELL2 = 50084;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24440;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 43803;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24485;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 49961;
SET @SPELL2 = 16583;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24540;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 9613;
SET @SPELL2 = 17173;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24547;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 64319;
SET @SPELL2 = 34298;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24635;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 43325;
SET @SPELL2 = 48193;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24638;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 43619;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24644;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 48286;
SET @SPELL2 = 48283;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24676;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 5915;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24789;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 16583;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24871;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 49841;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 24872;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 49843;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 26586;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 32019;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 26663;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 18651;
SET @SPELL2 = 36828;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 27330;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 50713;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 28034;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 6660;
SET @SPELL2 = 54484;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 28221;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 11918;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 28255;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 58579;
SET @SPELL2 = 57854;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 28257;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 54491;
SET @SPELL2 = 50661;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 29449;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 56038;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 29451;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 36789;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 29738;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 50689;
SET @SPELL2 = 50688;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, @TIMER1, @TIMER2, @TIMER2, @TIMER3, 11, @SPELL2, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 30205;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 60781;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 30206;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 35201;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 30333;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 54185;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 30544;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 50283;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

SET @ENTRY = 32488;
SET @TIMER1 = 5000;
SET @TIMER2 = 12000;
SET @TIMER3 = 18000;
SET @SPELL1 = 59130;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 0, @TIMER2, @TIMER1, @TIMER2, 11, @SPELL1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, '');

