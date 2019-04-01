UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = 137675;
DELETE FROM `creature_addon` WHERE `guid` = 137675;
INSERT INTO `creature_addon` VALUES
(137675, 1376750, 0, 0, 1, 0, '');

DELETE FROM `waypoint_data` WHERE `id` = 1376750;
INSERT INTO `waypoint_data` VALUES
(1376750, 1, -1575.46, 177.92, -7.70, 0, 60000, 0, 0, 100, 0),
(1376750, 2, -1576.63, 180.62, -7.79, 0, 30000, 0, 0, 100, 0),
(1376750, 3, -1581.62, 177.85, -7.79, 0, 30000, 0, 0, 100, 0);
