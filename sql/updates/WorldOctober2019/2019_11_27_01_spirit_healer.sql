SET @CGUID:= 17663;

DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelId`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`) VALUES
(@CGUID, 6491, 571, 1, 1, 0, 0, 4105.36, -4818.6, 76.074, 0.149361, 7200, 0);
