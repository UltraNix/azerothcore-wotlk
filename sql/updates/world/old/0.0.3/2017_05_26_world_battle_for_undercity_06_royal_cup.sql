-- A Royal Coup
SET @OGUID := 218979;
SET @PORTAL_STORMWIND := 193207;

DELETE FROM `gameobject` WHERE `id`=@PORTAL_STORMWIND AND `guid`=@OGUID;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,@PORTAL_STORMWIND,1,1,128,1921.699951,-4147.27,40.625,4.68743,0,0,0.715875,-0.698228,120,100,1);

UPDATE `gameobject_template` SET `AiName`='', `ScriptName`='go_battle_for_undercity_portals' WHERE `entry`=@PORTAL_STORMWIND;

DELETE FROM `spell_scripts` WHERE `id`=59065;
INSERT INTO `spell_scripts` VALUES
(59065,0,0,15,60898,0,0,0,0,0,0);

DELETE FROM `spell_target_position` WHERE `id`=60898;
INSERT INTO `spell_target_position` VALUES
(60898,0,0,-8448.6035,341.9446,120.8860,5.4145);
