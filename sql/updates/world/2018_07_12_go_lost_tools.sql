SET @OGUID = 269405;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID AND @OGUID + 3;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES 
(@OGUID, 179908, 0, 1, 1, 471.03, -3579.82, 119.07, 0.61, 0, 0, 0.996195, 0.087156, 2, 100, 1, 0),
(@OGUID+1, 179908, 0, 1, 1, 332.49, -4132.03, 119.77, 4.74, 0, 0, 0.996195, 0.087156, 2, 100, 1, 0),
(@OGUID+2, 179908, 0, 1, 1, 223.55, -4327.31, 117.65, 0, 0, 0, 0.996195, 0.087156, 2, 100, 1, 0),
(@OGUID+3, 179908, 0, 1, 1, 116.08, -4399.14, 120.45, 0, 0, 0, 0.996195, 0.087156, 2, 100, 1, 0);
