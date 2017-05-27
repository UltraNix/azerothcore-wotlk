SET @OGUID := 218966;

DELETE FROM `gameobject` WHERE `id`=193196;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,193196,571,1,2,4842.06,1495.79,209.574,4.68743,0,0,0.715875,-0.698228,120,100,1);
