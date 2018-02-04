-- Prince Keleseth
SET @CGUID = 126025;
DELETE FROM `waypoint_data` WHERE `id` = @CGUID * 10;
INSERT INTO `waypoint_data` VALUES
(@CGUID*10, 1, 193.12, 197.49, 40.91, 0.17, 3000, 0, 0, 100, 0),
(@CGUID*10, 2, 187.88, 204.27, 40.81, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 3, 186.68, 214.57, 40.81, 1.77, 3000, 0, 0, 100, 0),
(@CGUID*10, 4, 187.88, 204.27, 40.81, 0, 0, 0, 0, 100, 0),
(@CGUID*10, 5, 193.12, 197.49, 40.91, 0.17, 0, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = @CGUID;
INSERT INTO `creature_addon` VALUES
(@CGUID, @CGUID*10, 0, 0, 0, 0, '');

-- Weaver, Drakkari Gutripper, Flamewalker Protector - they are part of formation
UPDATE `creature` SET `MovementType` = 0 WHERE `guid` IN (239021, 127456, 127457, 56607, 56606);

-- King Jokkum
UPDATE `creature_template` SET `MovementType` = 0 WHERE `entry` = 30331;