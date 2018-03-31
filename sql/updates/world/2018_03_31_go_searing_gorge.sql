DELETE FROM `pool_template` WHERE `entry` = 11639;
INSERT INTO `pool_template` VALUES
(11639, 1, 'Searing Gorge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = 11639;
INSERT INTO `pool_gameobject` VALUES
(58117, 11639, 0, ''),
(9535, 11639, 0, ''),
(7234, 11639, 0, ''),
(5850, 11639, 0, '');
