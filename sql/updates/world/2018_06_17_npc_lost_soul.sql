DELETE FROM `pool_template` WHERE `entry` = 11646;
INSERT INTO `pool_template` VALUES
(11646, 1, 'Lost Soul - Tirisfal Glades');
DELETE FROM `pool_creature` WHERE `pool_entry` = 11646;
INSERT INTO `pool_creature` VALUES
(44863, 11646, 0, 'Lost Soul - Tirisfal Glades'),
(44864, 11646, 0, 'Lost Soul - Tirisfal Glades');
