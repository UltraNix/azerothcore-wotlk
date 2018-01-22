
SET @GO_HORSEMEN_CHEST_10:= 181366;
SET @GO_HORSEMEN_CHEST_25:= 193426;
SET @O_GUID:= 250000;


DELETE FROM `gameobject` WHERE `id` IN (@GO_HORSEMEN_CHEST_10, @GO_HORSEMEN_CHEST_25);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@O_GUID + 0, @GO_HORSEMEN_CHEST_10, 533, 1, 1, 2514.8, -2944.9, 245.55, 5.51, 0, 0, 1, 0, 604800, 0, 1, 0),
(@O_GUID + 1, @GO_HORSEMEN_CHEST_25, 533, 2, 1, 2514.8, -2944.9, 245.55, 5.51, 0, 0, 1, 0, 604800, 0, 1, 0);
