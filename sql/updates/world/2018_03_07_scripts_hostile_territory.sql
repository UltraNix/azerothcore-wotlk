SET @PATH = 27661;
UPDATE `creature_template` SET `AIName` = "SmartAI", `InhabitType` = 7, `speed_run` = 2 WHERE `entry` = @PATH;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 27662;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@PATH, 27662);
INSERT INTO `smart_scripts` VALUES
(@PATH, 0, 0, 1, 73, 0, 100, 0, 0, 0, 0, 0, 53, 1, @PATH, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - On SpellClick - Start WP'),
(@PATH, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, ''),
(@PATH, 0, 2, 0, 40, 0, 100, 0, 20, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - On WP Reached - Despawn'),
(27662, 0, 0, 0, 38, 0, 100, 0, 5, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `conditions` WHERE `SourceEntry` = 27661 AND `SourceTypeOrReferenceId` = 22;
INSERT INTO `conditions` VALUES
(22, 1, 27661, 0, 0, 28, 0, 12325, 0, 0, 0, 0, 0, '', '');
delete from creature_text where entry = 27662;
INSERT INTO `creature_text` VALUES
(27662, 0, 0, 'For the Alliance', 12, 0, 100, 0, 0, 0, 0, '');
DELETE FROM `waypoints` WHERE `entry` = @PATH;
INSERT INTO `waypoints` VALUES
(@PATH, 1, 3711.501, -698.566, 217.48779, ''),
(@PATH, 2, 3713.352, -719.048, 223.89778, ''),
(@PATH, 3, 3717.124, -741.356, 226.23726, ''),
(@PATH, 4, 3722.107, -770.046, 227.57614, ''),
(@PATH, 5, 3725.378, -794.482, 226.96625, ''),
(@PATH, 6, 3724.942, -811.955, 226.12540, ''),
(@PATH, 7, 3725.161, -864.323, 223.04434, ''),
(@PATH, 8, 3732.180, -933.780, 217.90073, ''),
(@PATH, 9, 3741.147, -961.385, 207.71948, ''),
(@PATH, 10, 3747.726, -1001.604, 198.03416,''),
(@PATH, 11, 3750.246, -1053.181, 188.76338,''),
(@PATH, 12, 3745.739, -1122.459, 179.82402,''),
(@PATH, 13, 3733.376, -1208.311, 168.72272,''),
(@PATH, 14, 3724.186, -1259.654, 162.89609,''),
(@PATH, 15, 3724.320, -1309.483, 161.15540,''),
(@PATH, 16, 3749.958, -1349.553, 163.32146,''),
(@PATH, 17, 3776.409, -1367.893, 164.39795,''),
(@PATH, 18, 3797.248, -1379.551, 162.05998,''),
(@PATH, 19, 3825.438, -1398.684, 148.31615,''),
(@PATH, 20, 3837.146, -1407.664, 143.99194,'');
