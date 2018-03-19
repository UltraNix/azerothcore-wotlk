UPDATE `smart_scripts` SET `link` = 32 WHERE `entryorguid` = 26814 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26814 AND `id` = 32;
INSERT INTO `smart_scripts` VALUES 
(26814, 0, 32, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Harrison Jones - On Respawn - Set NPC flags');
UPDATE `smart_scripts` SET `action_param1` = 3 WHERE `entryorguid` = 2681400 AND `id` = 4;
UPDATE `smart_scripts` SET `event_param1` = 25, `comment` = "Harrison Jones - On WP 25 reached - Pause WP movement 6 seconds" WHERE `entryorguid` = 26814 AND `id` = 26;
UPDATE `smart_scripts` SET `comment` = "Harrison Jones - On WP 25 reached - Say line" WHERE `entryorguid` = 26814 AND `id` = 27;
UPDATE `smart_scripts` SET `event_param1` = 25, `comment` = "Harrison Jones - On WP 25 resumed - Set run" WHERE `entryorguid` = 26814 AND `id` = 28;
UPDATE `smart_scripts` SET `comment` = "Harrison Jones - On WP 25 resumed - Quest credit" WHERE `entryorguid` = 26814 AND `id` = 29;
UPDATE `smart_scripts` SET `event_param1` = 29, `comment` = "Harrison Jones - On WP 29 reached - Despawn" WHERE `entryorguid` = 26814 AND `id` = 30;

DELETE FROM `waypoints` WHERE `entry` = 268140 AND `pointid` BETWEEN 9 AND 29;
INSERT INTO `waypoints` VALUES
(268140, 9, 4781.12, -4849.69, 25.4412, 'Harrison Jones'),
(268140, 10, 4773.05, -4844.91, 25.45, 'Harrison Jones'),
(268140, 11, 4761.5, -4853.98, 25.0099, 'Harrison Jones'),
(268140, 12, 4719.89, -4857.75, 26.1367, 'Harrison Jones'),
(268140, 13, 4717.54, -4857.71, 25.59, 'Harrison Jones'),
(268140, 14, 4716.05, -4857.60, 24.93, 'Harrison Jones'),
(268140, 15, 4714.20, -4857.51, 24.72, 'Harrison Jones'),
(268140, 16, 4693.85, -4858.84, 32.4999, 'Harrison Jones'),
(268140, 17, 4680.42, -4861.25, 35.5674, 'Harrison Jones'),
(268140, 18, 4673.97, -4864.33, 35.5674, 'Harrison Jones'),
(268140, 19, 4662.38, -4882.54, 35.5876, 'Harrison Jones'),
(268140, 20, 4658.19, -4895.92, 36.1955, 'Harrison Jones'),
(268140, 21, 4656.81, -4915.52, 43.7827, 'Harrison Jones'),
(268140, 22, 4659.83, -4928.78, 47.8299, 'Harrison Jones'),
(268140, 23, 4664.12, -4942.44, 48.0028, 'Harrison Jones'),
(268140, 24, 4666.97, -4951.51, 48.1059, 'Harrison Jones'),
(268140, 25, 4675.69, -4970.23, 47.6443, 'Harrison Jones'),
(268140, 26, 4681.64, -4973.98, 46.7499, 'Harrison Jones'),
(268140, 27, 4707.98, -4997.29, 40.704, 'Harrison Jones'),
(268140, 28, 4712.89, -5002.18, 39.1201, 'Harrison Jones'),
(268140, 29, 4739.86, -5031.48, 31.1823, 'Harrison Jones');

UPDATE `waypoints` SET `position_x` = 4813.03, `position_y` = -4799.38, `position_z` = 25.48 WHERE `entry` = 268140 AND `pointid` = 5;
