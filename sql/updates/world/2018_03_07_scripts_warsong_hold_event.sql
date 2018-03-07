DELETE FROM `creature_template` WHERE `entry` = 80001;
INSERT INTO `creature_template` VALUES
(80001, 0, 0, 0, 0, 0, 16480, 13069, 0, 0, 'Warsong Hold Event Trigger', NULL, NULL, 0, 70, 70, 1, 35, 0, 1.125, 1.14286, 1, 0, 252, 357, 0, 304, 1, 2000, 2000, 1, 33555200, 2048, 0, 0, 0, 0, 0, 0, 215, 320, 44, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 265, 1, 0, 130, '', 0);

SET @TRIGGER_ENTRY = 80001;
SET @TRIGGER_GUID = 160512;
SET @CAPTAIN_ENTRY = 25446;
SET @CAPTAIN_GUID = 125432;
SET @NERUBAR = 25451;
SET @MARKSMAN = 25244;
SET @ITHRIX = 25453;
SET @EVENT_TIME = 10000;

DELETE FROM `creature_template_addon` WHERE `entry` IN (@NERUBAR, @ITHRIX);
INSERT INTO `creature_template_addon` VALUES
(@NERUBAR, 0, 0, 33554432, 2, 0, ''),
(@ITHRIX, 0, 0, 33554432, 2, 0, '');
UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` IN (@NERUBAR, @ITHRIX);

DELETE FROM `creature` WHERE `guid` = @TRIGGER_GUID;
INSERT INTO `creature` VALUES
(@TRIGGER_GUID, @TRIGGER_ENTRY, 571, 1, 1, 0, 0, 2729.41, 6093.94, 74.81, 1.66, 1800, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `smart_scripts` WHERE `entryorguid` = @CAPTAIN_ENTRY AND `id` IN (4,5,6);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@TRIGGER_ENTRY, @TRIGGER_ENTRY*100);
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ITHRIX AND `id` IN (3,4,5);
INSERT INTO `smart_scripts` VALUES
(@CAPTAIN_ENTRY, 0, 4, 0, 38, 0, 100, 0, 4, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 18, 20, 0, 0, 0, 0, 0, 0, 'Warsong Captain - On data set 4 1 - Say line 0'),
(@CAPTAIN_ENTRY, 0, 5, 0, 38, 0, 100, 0, 4, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 18, 20, 0, 0, 0, 0, 0, 0, 'Warsong Captain - On data set 4 2 - Say line 1'),
(@CAPTAIN_ENTRY, 0, 6, 0, 38, 0, 100, 0, 4, 3, 0, 0, 1, 2, 0, 0, 0, 0, 0, 18, 20, 0, 0, 0, 0, 0, 0, 'Warsong Captain - On data set 4 3 - Say line 2'),
(@ITHRIX, 0, 3, 5, 6, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, @TRIGGER_GUID, @TRIGGER_ENTRY, 0, 0, 0, 0, 0, 'Ithrix - On Death - Set Data 1 1 On Trigger'),
(@ITHRIX, 0, 4, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 20, 0, 0, 0, 0, 0, 'Ithrix - On just Summoned - Start Attack'),
(@ITHRIX, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 45593, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ithrix - On Death - Cast Ithrix Carapace'),
(@TRIGGER_ENTRY, 0, 0, 0, 1, 0, 100, 1, @EVENT_TIME, @EVENT_TIME, @EVENT_TIME, @EVENT_TIME, 80, @TRIGGER_ENTRY*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - OOC - Start Script'),
(@TRIGGER_ENTRY, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Data Set - Despawn'),
(@TRIGGER_ENTRY*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 1, 0, 0, 0, 0, 10, @CAPTAIN_GUID, @CAPTAIN_ENTRY, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Set Data 4 1'),
(@TRIGGER_ENTRY*100, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 2000, 2000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 2, 0, 0, 0, 0, 10, @CAPTAIN_GUID, @CAPTAIN_ENTRY, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Set Data 4 2'),
(@TRIGGER_ENTRY*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 107, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 1'),
(@TRIGGER_ENTRY*100, 9, 4, 0, 0, 0, 100, 0, 30000, 30000, 30000, 30000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 5, 0, 0, 0, 100, 0, 30000, 30000, 30000, 30000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 3, 0, 0, 0, 0, 10, @CAPTAIN_GUID, @CAPTAIN_ENTRY, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Set Data 4 3'),
(@TRIGGER_ENTRY*100, 9, 7, 0, 0, 0, 100, 0, 60000, 60000, 60000, 60000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 8, 0, 0, 0, 100, 0, 30000, 30000, 30000, 30000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 3, 0, 0, 0, 0, 10, @CAPTAIN_GUID, @CAPTAIN_ENTRY, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Set Data 4 3'),
(@TRIGGER_ENTRY*100, 9, 10, 0, 0, 0, 100, 0, 60000, 60000, 60000, 60000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Group Summon 2'),
(@TRIGGER_ENTRY*100, 9, 11, 0, 0, 0, 100, 0, 30000, 30000, 30000, 30000, 12, @ITHRIX, 3, 300000, 0, 0, 0, 8, 0, 0, 0, 2709.61, 6083.32, 83.48, 0, 'Warsong Event Trigger - On Script - Summon Ithix');

DELETE FROM `waypoints` WHERE `entry` = @NERUBAR;
INSERT INTO `waypoints` VALUES
(@NERUBAR, 1, 2715.91, 6087.54, 77.61, ''),
(@NERUBAR, 2, 2726.40, 6090.61, 76.24, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` = @NERUBAR AND `id` > 1;
INSERT INTO `smart_scripts` VALUES
(@NERUBAR, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, @NERUBAR, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nerubar - On Just Summoned - start WP'),
(@NERUBAR, 0, 3, 0, 40, 0, 100, 0, 1, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nerubar - On WP 1 Reached - Set Home pos'),
(@NERUBAR, 0, 4, 0, 40, 0, 100, 0, 2, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 20, 0, 0, 0, 0, 0, 'Nerubar - On WP 2 Reached - Start Attack');
-- (@NERUBAR, 0, 5, 0, 40, 0, 100, 0, 2, 0, 0, 0, 91, 33554432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `creature_text` WHERE `entry` IN (@CAPTAIN_ENTRY, @TRIGGER_ENTRY);
INSERT INTO `creature_text` VALUES
(@CAPTAIN_ENTRY, 0, 0, 'Our fortress is under attack!', 12, 0, 100, 0, 0, 0, 0, ''),
(@CAPTAIN_ENTRY, 1, 0, 'Group up warriors of the Horde!', 12, 0, 100, 0, 0, 0, 0, ''),
(@CAPTAIN_ENTRY, 2, 0, 'Stay ready, they won`t give up so easily!', 12, 0, 100, 0, 0, 0, 0, ''),
(@CAPTAIN_ENTRY, 2, 1, 'When the White Frost comes, do not eat the yellow snow.', 12, 0, 100, 0, 0, 0, 0, ''),
(@CAPTAIN_ENTRY, 2, 2, 'Heal your wounds, while we have the time!', 12, 0, 100, 0, 0, 0, 0, '');

DELETE FROM `creature_summon_groups` WHERE `summonerId` = @TRIGGER_ENTRY;
INSERT INTO `creature_summon_groups` VALUES 
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2724.14, 6098.44, 75.04, 3.60, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2726.10, 6091.77, 73.46, 3.60, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2728.33, 6085.85, 73.41, 3.61, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2735.93, 6088.02, 75.66, 3.47, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2732.03, 6093.07, 75.20, 3.65, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2726.85, 6098.56, 75.54, 3.79, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2721.75, 6104.93, 75.80, 3.83, 3, 300000),
(@TRIGGER_ENTRY, 0, 1, @MARKSMAN, 2722.61, 6079.25, 70.88, 2.94, 3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2625.81, 6052.00, 128.78, 0.35,3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2638.3, 6060.87, 116.28, 0.35, 3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2643.18, 6041.77, 118.57, 0.35,3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2628.81, 6052.00, 128.78, 0.35,3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2625.81, 6050.00, 128.78, 0.35,3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2627.81, 6052.00, 128.78, 0.35,3, 300000),
(@TRIGGER_ENTRY, 0, 2, @NERUBAR,2625.81, 6052.00, 128.78, 0.35,3, 300000);