-- Base guid for new custom spawns
SET @CGUID = 303304;
-- One new entry to creature_template
SET @ENTRY = 98001;

SET @HORDE_DRUM = 10861;
SET @ALLIANCE_BELL = 6594;
SET @ORGRI_SPAWN = @CGUID;
SET @STORMWIND_SPAWN = @ORGRI_SPAWN + 1;

DELETE FROM `game_event` WHERE `eventEntry` = 73;
INSERT INTO `game_event` VALUES 
(73, '2010-01-01 02:00:00', '2025-01-01 02:00:00', 60, 1, 0, 0, 'Hourly Bells', 0);

DELETE FROM `creature_template` WHERE `entry` = @ENTRY AND `modelid1` = 10045;
INSERT INTO `creature_template` VALUES 
(@ENTRY, 0, 0, 0, 0, 0, 10045, 0, 0, 0, 'Hourly Bells Event Trigger', '', '', 0, 80, 80, 2, 35, 0, 1, 2, 1, 1, 622, 786, 0, 642, 13, 0, 0, 1, 2, 2048, 8, 0, 0, 0, 0, 0, 545, 709, 103, 7, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 25, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650854271, 130, '', 12340);

DELETE FROM `smart_scripts` WHERE `entryorguid` = -@ORGRI_SPAWN;
DELETE FROM `smart_scripts` WHERE `entryorguid` = -@STORMWIND_SPAWN;
INSERT INTO `smart_scripts` VALUES
(-@ORGRI_SPAWN, 0, 0, 0, 1, 0, 100, 0, 1000, 1000, 0, 0, 4, @HORDE_DRUM, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-@STORMWIND_SPAWN, 0, 0, 0, 1, 0, 100, 0, 1000, 1000, 5000, 5000, 4, @ALLIANCE_BELL, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `game_event_creature` WHERE `guid` IN (@ORGRI_SPAWN, @STORMWIND_SPAWN);
INSERT INTO `game_event_creature` VALUES
(73, @ORGRI_SPAWN),
(73, @STORMWIND_SPAWN);

DELETE FROM `creature` WHERE `guid` = @ORGRI_SPAWN AND `id` = @ENTRY;
DELETE FROM `creature` WHERE `guid` = @STORMWIND_SPAWN AND `id` = @ENTRY;
INSERT INTO `creature` VALUES
(@ORGRI_SPAWN, @ENTRY, 1, 1, 1, 0, 0, 1632.47, -4370, 29.61, 3.34, 10, 0, 0, 0, 0, 0, 0, 0, 0),
(@STORMWIND_SPAWN, @ENTRY, 0, 1, 1, 0, 0, -8823.719, 629.86, 122.21, 3.34, 10, 0, 0, 0, 0, 0, 0, 0, 0);
