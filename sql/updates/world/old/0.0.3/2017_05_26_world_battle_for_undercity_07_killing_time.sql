-- The Killing Time
SET @OGUID := 218980;
SET @PORTAL_UNDERCITY := 193955;

DELETE FROM `spell_area` WHERE `spell` IN (60943) AND `area` IN (1519);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60943, 1519, 13371, 0, 0, 1101, 2, 1, 2, 0);

DELETE FROM `gameobject` WHERE `id`=@PORTAL_UNDERCITY AND `guid`=@OGUID;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,@PORTAL_UNDERCITY,0,1,128,-8450.3486,330.2014,121.3297,4.68743,0,0,0.715875,-0.698228,120,100,1);

UPDATE `gameobject_template` SET `AiName`='', `ScriptName`='go_battle_for_undercity_portals' WHERE `entry`=@PORTAL_UNDERCITY;

DELETE FROM `spell_scripts` WHERE `id`=60940;
INSERT INTO `spell_scripts` VALUES
(60940,0,0,15,60941,0,0,0,0,0,0);

DELETE FROM `spell_target_position` WHERE `id`=60941;
INSERT INTO `spell_target_position` VALUES
(60941,0,0,1803.1524,769.4466,43.1631,4.0204);
