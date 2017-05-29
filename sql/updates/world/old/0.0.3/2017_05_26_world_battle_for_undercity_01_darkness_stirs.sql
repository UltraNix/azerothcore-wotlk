SET @OGUID := 218965;

DELETE FROM `gameobject` WHERE `id`=193197;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,193197,571,1,2,4879.06,1487.72,209.964,1.47438,0,0,0.672211,0.74036,300,100,1);