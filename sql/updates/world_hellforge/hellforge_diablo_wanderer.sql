SET @ENTRY := 262000;
DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + 2;
INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,2147483648,0,0,0,'The Wanderer','',NULL,0,83,83,2,21,0,1.1,1.14286,1,3,496,674,0,783,14,2000,0,2,0,2080,8,0,0,0,0,0,365,529,98,7,76,15990,0,0,0,0,0,200,100,0,0,0,0,0,0,0,0,0,0,0,1002755,1457838,'',0,3,1,375,600,1,0,0,0,0,0,0,0,0,1,617299839,2097153,'npc_hellforge_diablo_wanderer',12340),
(@ENTRY + 1,0,0,0,0,0,22669,0,0,0,'Soul Stone',NULL,NULL,0,80,80,0,35,0,0.1,0.1,0.3,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_diablo_wanderer_soulstone',12340),
(@ENTRY + 2,0,0,0,0,0,25900,0,0,0,'Tyrael', 'Archangel of Justice',NULL,0,80,80,0,35,3,1,1.14286,10,0,100000,200000,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,1,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_dalaran_tyrael',12340);

SET @CGUID := 600003;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID AND @CGUID + 1;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID + 0, @ENTRY, 249, 8, 1, 0, 0, -10.9161, -213.238, -87.7776, 3.137, 604800, 0, 0, 13945, 4258, 0, 0, 0, 0),
(@CGUID + 1, @ENTRY + 2, 571, 1, 1, 0, 0, 5731.52, 513.75, 647.45, 0.5, 604800, 0, 0, 13945, 4258, 0, 0, 0, 0);

SET @ENTRY := 1120000;
DELETE FROM `npc_text` WHERE `ID` BETWEEN @ENTRY AND @ENTRY + 3;
INSERT INTO `npc_text`(`ID`, `text0_0`) VALUES 
(@ENTRY, 'You are not prepared.'),
(@ENTRY + 1, 'Hurry up heroes, I have found him!'),
(@ENTRY + 2, 'You will find hell entrance in dwarf caves below searing gorge. I\'ll wait there for you. Prepare for hardest fight...'),
(@ENTRY + 3, 'Hurry up mortal, find me in Searing Gorge dungeons!');

UPDATE `creature_questender` SET `id` = 300003 WHERE `quest` = 31006;
UPDATE `quest_template` SET `NextQuestIdChain` = 0 WHERE `Id` = 31006;

SET @GO_GUID := 281000;
DELETE FROM `gameobject` WHERE `guid` IN (@GO_GUID, @GO_GUID + 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@GO_GUID,400601, 249, 8, 1, -163.07, -163.25, -59.01, 4.27, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0),
(@GO_GUID + 1, 195682, 249, 8, 1, -188.86, -199.30, -68.10, 6.0, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0);

DELETE FROM `access_requirement` WHERE `mapId` = 249 AND `difficulty` = 3;
INSERT INTO `access_requirement` VALUES 
(249, 3, 80, 0, 0, 0, 0, 31006, 31006, 0, 'You must complete the quest "Visit in Hell" before entering the Hellforge.', 'Onyxia\'s Lair - Hellforge');