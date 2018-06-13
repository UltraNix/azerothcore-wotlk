SET @PATH = 28061;
DELETE FROM `waypoints` WHERE `entry` = 28061 AND `pointid` < 31;
INSERT INTO `waypoints` VALUES
(@PATH, 0, 3704.983, -700.377, 217.08211, ''),
(@PATH, 1, 3711.725, -710.596, 216.75386, ''),
(@PATH, 2, 3726.972, -733.041, 220.60791, ''),
(@PATH, 3, 3738.352, -746.193, 222.51083, ''),
(@PATH, 4, 3771.197, -775.176, 226.59122, ''),
(@PATH, 5, 3803.130, -788.044, 230.27968, ''),
(@PATH, 6, 3830.261, -788.305, 236.57689, ''),
(@PATH, 7, 3839.163, -794.858, 239.18979, ''),
(@PATH, 8, 3845.318, -807.351, 240.24564, ''),
(@PATH, 9, 3850.293, -835.214, 239.76500, ''),
(@PATH, 10, 3844.617, -868.041, 234.03665, ''),
(@PATH, 11, 3827.246, -915.756, 220.84372, ''),
(@PATH, 12, 3807.438, -955.888, 208.10118, ''),
(@PATH, 13, 3780.358, -997.347, 190.66272, ''),
(@PATH, 14, 3763.207, -1026.016, 180.39380, ''),
(@PATH, 15, 3750.797, -1058.173, 174.71964, ''),
(@PATH, 16, 3735.921, -1108.374, 170.89232, ''),
(@PATH, 17, 3720.693, -1158.448, 166.77963, ''),
(@PATH, 18, 3705.434, -1208.509, 162.61487, ''),
(@PATH, 19, 3689.902, -1258.503, 158.69774, ''),
(@PATH, 20, 3675.131, -1303.966, 156.39055, ''),
(@PATH, 21, 3658.557, -1353.494, 161.65509, ''),
(@PATH, 22, 3642.552, -1403.188, 167.17909, ''),
(@PATH, 23, 3626.545, -1452.891, 172.62129, ''),
(@PATH, 24, 3604.671, -1499.053, 174.07661, ''),
(@PATH, 25, 3586.655, -1524.781, 172.24162, ''),
(@PATH, 26, 3544.98,  - 1617.79, 160.00, ''),
(@PATH, 27, 3526.12, -1630.440,  157.19800, ''),
(@PATH, 28, 3518.53, -1640.53, 158.09, ''),
(@PATH, 29, 3498.95, -1657.19, 162.00, ''),
(@PATH, 30, 3492.13, -1664.24, 162.55, '');

UPDATE `creature_text` SET `text` = "What in the name of Bronzebeard is goin' on here? Look at this place! I think..." WHERE `entry` = 28061 AND `groupid` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28063 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(28063, 0, 1, 0, 61, 0, 50, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Conquest Hold Windrager - Just Summoned - Say Line 0');

UPDATE `smart_scripts` SET `link` = 1, `comment` = "Conquest Hold Windrager - Just Summoned - Follow Summoner" WHERE `entryorguid` = 28063 AND `id` = 0;
DELETE FROM `creature_text` WHERE `entry` = 28063;
INSERT INTO `creature_text` VALUES
(28063, 0, 0, 'For the Horde', 14, 1, 100, 0, 0, 0, 0, 'Conquest Hold Windrager'),
(28063, 0, 1, "Lok'tar ogar", 14, 1, 100, 0, 0, 0, 0, 'Conquest Hold Windrager'),
(28063, 0, 2, "Lok-Narash. Gol'Kosh. Kagh!", 14, 1, 100, 0, 0, 0, 0, 'Conquest Hold Windrager');
