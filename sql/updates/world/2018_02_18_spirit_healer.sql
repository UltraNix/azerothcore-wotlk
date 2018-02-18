-- Remove previous spawn with incremental guid
DELETE FROM `creature` WHERE `id` = 6491 AND `position_x` = -1315.88 AND `position_y` = -3184.42;
-- Add new with fixed guid
SET @CGUID = 1954837;
DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` (guid, id, map, position_x, position_y, position_z, orientation) VALUES
(@CGUID, 6491, 0, -1315.88, -3184.42, 37.28, 5.56);