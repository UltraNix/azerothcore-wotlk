-- Bile Golem
SET @CGUID = 152317;
DELETE FROM `waypoint_data` WHERE `id` = @CGUID * 10;
INSERT INTO `waypoint_data` VALUES
(@CGUID*10, 1, 2493.34, 1365.07, 130.95, 0, 2000, 0, 0, 100, 0),
(@CGUID*10, 2, 2478.40, 1394.64, 130.03, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 3, 2454.99, 1426.17, 130.93, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 4, 2439.34, 1424.98, 130.74, 0, 2000, 0, 0, 100, 0),
(@CGUID*10, 5, 2454.99, 1426.17, 130.93, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 6, 2478.40, 1394.64, 130.03, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 7, 2493.34, 1365.07, 130.95, 0, 0, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = @CGUID;
INSERT INTO `creature_addon` VALUES
(@CGUID, @CGUID*10, 0, 0, 0, 0, '');

-- Patchwork Construct
SET @CGUID = 152316;
DELETE FROM `waypoint_data` WHERE `id` = @CGUID * 10;
INSERT INTO `waypoint_data` VALUES
(@CGUID*10, 1, 2543.11, 1250.86, 126.20, 0, 2000, 0, 0, 100, 0),
(@CGUID*10, 2, 2531.22, 1279.75, 128.09, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 3, 2522.34, 1298.12, 130.78, 0, 2000, 0, 0, 100, 0),
(@CGUID*10, 4, 2531.22, 1279.75, 128.09, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 5, 2543.11, 1250.86, 126.20, 0, 0, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = @CGUID;
INSERT INTO `creature_addon` VALUES
(@CGUID, @CGUID*10, 0, 0, 0, 0, '');

-- Crypt Fiend
SET @CGUID = 152315;
DELETE FROM `waypoint_data` WHERE `id` = @CGUID * 10;
INSERT INTO `waypoint_data` VALUES
(@CGUID*10, 1, 2555.04, 1236.93, 125.70, 0, 3000, 0, 0, 100, 0),
(@CGUID*10, 2, 2551.18, 1250.92, 125.46, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 3, 2532.10, 1255.33, 127.98, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 4, 2525.39, 1267.12, 128.44, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 5, 2535.82, 1281.89, 128.22, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 6, 2530.92, 1291.77, 130.48, 0, 3000, 0, 0, 100, 0),
(@CGUID*10, 7, 2535.82, 1281.89, 128.22, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 8, 2525.39, 1267.12, 128.44, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 9, 2551.18, 1250.92, 125.46, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 10, 2555.04, 1236.93, 125.70, 0, 3000, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = @CGUID;
INSERT INTO `creature_addon` VALUES
(@CGUID, @CGUID*10, 0, 0, 0, 0, '');

-- Crypt Fiend 2
SET @CGUID = 152318;
DELETE FROM `waypoint_data` WHERE `id` = @CGUID * 10;
INSERT INTO `waypoint_data` VALUES
(@CGUID*10, 1, 2474.90, 1399.08, 130.32, 0, 3000, 0, 0, 100, 0),
(@CGUID*10, 2, 2477.57, 1378.18, 129.28, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 3, 2483.25, 1366.12, 129.93, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 4, 2496.84, 1370.99, 131.14, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 5, 2488.36, 1390.16, 130.53, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 6, 2474.90, 1399.08, 130.32, 0, 0, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = @CGUID;
INSERT INTO `creature_addon` VALUES
(@CGUID, @CGUID*10, 0, 0, 0, 0, '');

DELETE FROM `creature` WHERE `guid` = 153439;
