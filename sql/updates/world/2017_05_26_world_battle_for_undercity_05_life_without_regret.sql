-- A Life Without Regret
SET @OGUID := 218977;
SET @PORTAL_UNDERCITY := 193425;

DELETE FROM `spell_area` WHERE `spell` IN (60943) AND `area` IN (1637);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60943, 1637, 13266, 0, 0, 690, 2, 1, 2, 0),
(60943, 1637, 13370, 0, 0, 1101, 2, 1, 2, 0);

DELETE FROM `gameobject` WHERE `id`=@PORTAL_UNDERCITY;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,@PORTAL_UNDERCITY,1,1,64,1929.1,-4145.26,40.75,4.68743,0,0,0.715875,-0.698228,120,100,1),
(@OGUID+1,@PORTAL_UNDERCITY,1,1,64,1911.5,-4145.26,40.75,4.68743,0,0,0.715875,-0.698228,120,100,1);

UPDATE `gameobject_template` SET `AiName`='', `ScriptName`='go_battle_for_undercity_portals' WHERE `entry`=@PORTAL_UNDERCITY;

DELETE FROM `spell_scripts` WHERE `id`=59439;
INSERT INTO `spell_scripts` VALUES
(59439,0,0,15,59448,0,0,0,0,0,0);

DELETE FROM `spell_target_position` WHERE `id`=59448;
INSERT INTO `spell_target_position` VALUES
(59448,0,0,1969.3867,242.1369,38.2355,3.6167);
