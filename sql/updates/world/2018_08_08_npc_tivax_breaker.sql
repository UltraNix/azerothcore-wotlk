DELETE FROM `pool_template` WHERE `entry` = 60007;
INSERT INTO `pool_template` VALUES
(60007, 1, 'Tivax the Breaker');

DELETE FROM `pool_creature` WHERE `guid` IN (109685, 109693);
INSERT INTO `pool_creature` VALUES
(109685, 60007, 0, 'Tivax the Breaker'),
(109693, 60007, 0, 'Tivax the Breaker');
