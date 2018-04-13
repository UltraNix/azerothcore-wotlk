DELETE FROM `pool_template` WHERE `entry` IN (60004,60005,60006);
INSERT INTO `pool_template` VALUES
(60004, 1, 'Gold Silver'),
(60005, 1, 'Gold Silver'),
(60006, 1, 'Gold Silver');

DELETE FROM `pool_gameobject` WHERE `guid` IN (5854, 34036, 65255,63511, 63520, 65233, 65226);
INSERT INTO `pool_gameobject` VALUES
(5854,60004, 0, ''),
(34036,60004, 0, ''),
(65255,60004, 0, ''),
(63511,60005, 0, ''),
(63520,60005, 0, ''),
(65233,60005, 0, ''),
(65226, 3477, 1, 'Spawn Point 278');
