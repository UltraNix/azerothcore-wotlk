DELETE FROM `creature_template` WHERE `entry` = 80004;
INSERT INTO `creature_template` VALUES
(80004, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'Majordomo Summoner Trigger', '', '', 0, 0, 0, 0, 35, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 130, 'npc_majordomo_summoner', 0); 

DELETE FROM `creature` WHERE `guid` = 303303;
INSERT INTO `creature` VALUES
(303303, 80004, 409, 1, 1, 0, 0, 847.103, -816.153, -229.775, 4.34, 10, 0, 0, 0, 0, 0, 0, 0, 0);