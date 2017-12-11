SET @OGUID:= 1984354;

DELETE FROM `gameobject` WHERE `guid` IN (@OGUID, @OGUID + 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID, 194821, 603, 1, 1, 1632.1, -306.561, 417.321, 4.69494, 0, 0, 0.261511, -0.965201, 604800, 0, 1, 0),
(@OGUID+1, 194822, 603, 2, 1, 1632.1, -306.561, 417.321, 4.69494, 0, 0, 0.261511, -0.965201, 604800, 0, 1, 0);
