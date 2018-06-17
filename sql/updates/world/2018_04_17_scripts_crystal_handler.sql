DELETE FROM `smart_scripts` WHERE `entryorguid` = 26627 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(26627, 0, 3, 0, 25, 0, 100, 0, 0, 0, 0, 0, 53, 0, 26627, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Crystal Handler - On Reset - Start WP');
DELETE FROM `waypoints` WHERE `entry` = 26627;
INSERT INTO `waypoints` VALUES
(26627, 1, -353.87, -735.48, 28.58, ''),
(26627, 2, -358.40, -755.01, 28.58, ''),
(26627, 3, -379.36, -756.60, 28.58, '');
