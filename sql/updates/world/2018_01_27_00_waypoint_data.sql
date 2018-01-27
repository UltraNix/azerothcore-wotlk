UPDATE `smart_scripts` SET `action_param6` = 2 WHERE `entryorguid` = 3678 AND `id` = 3;
UPDATE `creature` SET `MovementType` = 0 WHERE `id` = 598;

SET @CREATURE_GUID_1:= 79144;
SET @PATH_1:= @CREATURE_GUID_1 * 10;
SET @CREATURE_GUID_2:= 79139;
DELETE FROM waypoint_data WHERE id = @PATH_1;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@PATH_1, 1, -57.967438, -382.376862, 54.014786),
(@PATH_1, 2, -60.452011, -399.169037, 53.688614),
(@PATH_1, 3, -57.967438, -382.376862, 54.014786),
(@PATH_1, 4, -69.397911, -381.792450, 54.005939),
(@PATH_1, 5, -82.954185, -375.775146, 56.341492),
(@PATH_1, 6, -69.397911, -381.792450, 54.005939),
(@PATH_1, 7, -57.967438, -382.376862, 54.014786),
(@PATH_1, 8, -35.692150, -375.112122, 58.051712),
(@PATH_1, 9, -35.692150, -375.112122, 58.051712);
DELETE FROM creature_formations WHERE leaderGUID = @CREATURE_GUID_1;
INSERT INTO creature_formations (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@CREATURE_GUID_1, @CREATURE_GUID_1, 0, 0, 515, 0, 0),
(@CREATURE_GUID_1, @CREATURE_GUID_2, 3, 270, 515, 0, 0);
DELETE FROM `creature_addon` WHERE `guid` = @CREATURE_GUID_1;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@CREATURE_GUID_1, @PATH_1);
UPDATE creature SET MovementType = 2 WHERE guid = @CREATURE_GUID_1;
--
SET @CREATURE_GUID_3:= 79189;
SET @PATH_2:= @CREATURE_GUID_3 * 10;
SET @CREATURE_GUID_4:= 79188;
DELETE FROM waypoint_data WHERE id = @PATH_2;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@PATH_2, 1, -97.594650, -376.458679, 58.367489),
(@PATH_2, 2, -109.185532, -386.382385, 56.897598),
(@PATH_2, 3, -102.876831, -393.972992, 57.659710),
(@PATH_2, 4, -109.185532, -386.382385, 56.897598),
(@PATH_2, 5, -117.696587, -396.771942, 57.091595),
(@PATH_2, 6, -123.603600, -388.587433, 59.025040),
(@PATH_2, 7, -113.446922, -379.915680, 57.987675),
(@PATH_2, 8, -97.594650, -376.458679, 58.367489);
DELETE FROM creature_formations WHERE leaderGUID = @CREATURE_GUID_3;
INSERT INTO creature_formations (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@CREATURE_GUID_3, @CREATURE_GUID_3, 0, 0, 515, 0, 0),
(@CREATURE_GUID_3, @CREATURE_GUID_4, 3, 270, 515, 0, 0);
DELETE FROM `creature_addon` WHERE `guid` = @CREATURE_GUID_3;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@CREATURE_GUID_3, @PATH_2);
UPDATE creature SET MovementType = 2 WHERE guid = @CREATURE_GUID_3;
--
SET @CREATURE_GUID_5:= 79277;
SET @PATH_4:= @CREATURE_GUID_5 * 10;
SET @CREATURE_GUID_6:= 79152;
SET @CREATURE_GUID_7:= 79151;
DELETE FROM waypoint_data WHERE id = @PATH_4;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@PATH_4, 1, -121.880173 , -400.558350, 57.912922),
(@PATH_4, 2, -122.662300, -414.746826, 58.295795),
(@PATH_4, 3, -135.558487, -410.078094, 58.172352),
(@PATH_4, 4, -147.662796, -401.373871, 57.017208),
(@PATH_4, 5, -132.559555, -401.740570, 58.479496),
(@PATH_4, 6, -121.880173 , -400.558350, 57.912922);
DELETE FROM creature_formations WHERE leaderGUID = @CREATURE_GUID_5;
INSERT INTO creature_formations (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@CREATURE_GUID_5, @CREATURE_GUID_5, 0, 0, 515, 0, 0),
(@CREATURE_GUID_5, @CREATURE_GUID_6, 2, 270, 515, 0, 0),
(@CREATURE_GUID_5, @CREATURE_GUID_7, 2, 90, 515, 0, 0);
DELETE FROM `creature_addon` WHERE `guid` = @CREATURE_GUID_5;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@CREATURE_GUID_5, @PATH_4);
UPDATE creature SET MovementType = 2 WHERE guid = @CREATURE_GUID_5;
--
SET @CREATURE_GUID_8:= 79373;
SET @PATH_5:= @CREATURE_GUID_8 * 10;
SET @CREATURE_GUID_9:= 79374;
DELETE FROM waypoint_data WHERE id = @PATH_5;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@PATH_5, 1, -171.653275, -402.306885, 57.254311),
(@PATH_5, 2, -180.578018, -415.738983, 54.732433),
(@PATH_5, 3, -171.653275, -402.306885, 57.254311),
(@PATH_5, 4, -161.673584, -399.217133, 56.525677),
(@PATH_5, 5, -151.441879, -400.836670, 56.755630),
(@PATH_5, 6, -161.673584, -399.217133, 56.525677),
(@PATH_5, 7, -171.653275, -402.306885, 57.254311);

DELETE FROM creature_formations WHERE leaderGUID = @CREATURE_GUID_8;
INSERT INTO creature_formations (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@CREATURE_GUID_8, @CREATURE_GUID_8, 0, 0, 515, 0, 0),
(@CREATURE_GUID_8, @CREATURE_GUID_9, 3, 270, 515, 0, 0);
DELETE FROM `creature_addon` WHERE `guid` = @CREATURE_GUID_8;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@CREATURE_GUID_8, @PATH_5);
UPDATE creature SET MovementType = 2 WHERE guid = @CREATURE_GUID_8;