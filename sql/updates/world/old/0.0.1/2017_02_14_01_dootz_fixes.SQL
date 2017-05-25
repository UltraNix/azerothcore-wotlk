SET @GUID := (SELECT MAX(guid) from creature) +100; 

DELETE FROM `gameobject` WHERE guid = @GUID;
INSERT INTO `gameobject` (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state, VerifiedBuild)
VALUES (@GUID, 188448, 571, 1, 1, 3029.383301, 538.310791, 61.703758, 3.723384, 0, 0, 0, 1, 300, 100, 1, 0);

UPDATE `waypoints` SET `position_z` = `position_z` + 5 WHERE `entry` = 23344 AND `pointid` = 25;
UPDATE `waypoints` SET `position_z` = `position_z` + 3 WHERE `entry` = 23344 AND `pointid` = 24;
UPDATE `waypoints` SET `position_z` = `position_z` + 3 WHERE `entry` = 23344 AND `pointid` = 23;
UPDATE `waypoints` SET `position_z` = `position_z` + 3 WHERE `entry` = 23344 AND `pointid` = 22;

DELETE FROM `conditions` WHERE `SourceEntry` = 1090;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 1090, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0,'' ,'Sleep Rank 2 should not target players');

UPDATE `quest_template` SET `RequiredRaces` = 0 WHERE `id` = 364;