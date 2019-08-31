SET @ENTRY := 262000;
DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + 1;
INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,2147483648,0,0,0,'The Wanderer','',NULL,0,83,83,2,21,0,1.1,1.14286,1,3,496,674,0,783,14,2000,0,2,0,2080,8,0,0,0,0,0,365,529,98,6,76,15990,0,0,0,0,0,200,100,0,0,0,0,0,0,0,0,0,0,0,1002755,1457838,'',0,3,1,375,600,1,0,0,0,0,0,0,0,0,1,617299839,2097153,'npc_hellforge_diablo_wanderer',12340),
(@ENTRY + 1,0,0,0,0,0,22669,0,0,0,'Soul Stone',NULL,NULL,0,80,80,0,35,0,0.1,0.1,0.3,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_diablo_wanderer_soulstone',12340);

SET @CGUID := 600003;

DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID + 0, @ENTRY, 249, 8, 1, 0, 0, -10.9161, -213.238, -87.7776, 3.137, 300, 0, 0, 13945, 4258, 0, 0, 0, 0);