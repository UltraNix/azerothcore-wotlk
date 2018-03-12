SET @PATH = 21685;
DELETE FROM `waypoints` WHERE `entry` = 21685;
INSERT INTO `waypoints` VALUES
(@PATH, 1, -3600.154, 1894.135, 47.24176, 'Oronok Torn-heart'),
(@PATH, 2, -3610.689, 1890.555, 47.24176, 'Oronok Torn-heart'),
(@PATH, 3, -3615.855, 1885.910, 47.34468, 'Oronok Torn-heart'),
(@PATH, 4, -3620.050, 1881.791, 47.86613, 'Oronok Torn-heart'),
(@PATH, 5, -3624.356, 1874.866, 49.59057, 'Oronok Torn-heart'),
(@PATH, 6, -3630.805, 1869.931, 52.32270, 'Oronok Torn-heart'),
(@PATH, 7, -3638.263, 1864.359, 54.12692, 'Oronok Torn-heart'),
(@PATH, 8, -3638.566, 1859.119, 53.88737, 'Oronok Torn-heart'),
(@PATH, 9, -3642.486, 1852.048, 56.55240, 'Oronok Torn-heart');

UPDATE `smart_scripts` SET `event_param1` = 9, `comment` = "Oronok Torn-heart - On Reached WP9 - Set Home Position"  WHERE `entryorguid` = 21685 AND `id` = 6;
UPDATE `smart_scripts` SET `comment` = "Oronok Torn-heart - On Reached WP9 - Set Unit Flags" WHERE `entryorguid` = 21685 AND `id` = 7;
UPDATE `smart_scripts` SET `comment` = "Oronok Torn-heart - On Reached WP9 - Set Faction" WHERE `entryorguid` = 21685 AND `id` = 8;
UPDATE `smart_scripts` SET `comment` = "Oronok Torn-heart - On Reached WP9 - Set Aggresive" WHERE `entryorguid` = 21685 AND `id` = 9;
UPDATE `smart_scripts` SET `comment` = "Oronok Torn-heart - On Reached WP9 - Set Data on Cyrukh the Firelord <The Dirge of Karabor>" WHERE `entryorguid` = 21685 AND `id` = 10;

SET @PATH = 21687;
DELETE FROM `waypoints` WHERE `entry` = @PATH;
INSERT INTO `waypoints` VALUES
(@PATH, 1, -3597.448, 1896.617, 47.24054, 'Gromtor, Son of Oronok'),
(@PATH, 2, -3602.094, 1891.431, 47.24054, 'Gromtor, Son of Oronok'),
(@PATH, 3, -3609.828, 1888.738, 47.24054, 'Gromtor, Son of Oronok'),
(@PATH, 4, -3613.944, 1883.033, 47.29341, 'Gromtor, Son of Oronok'),
(@PATH, 5, -3619.001, 1875.996, 47.81740, 'Gromtor, Son of Oronok'),
(@PATH, 6, -3622.003, 1871.056, 48.48785, 'Gromtor, Son of Oronok'),
(@PATH, 7, -3631.009, 1866.851, 51.91560, 'Gromtor, Son of Oronok'),
(@PATH, 8, -3634.564, 1860.821, 52.48026, 'Gromtor, Son of Oronok'),
(@PATH, 9, -3641.825, 1857.032, 55.30927, 'Gromtor, Son of Oronok');

UPDATE `smart_scripts` SET `event_param1` = 9, `comment` = "Gromtor, Son of Oronok - On Reached WP9 - Set Home Position" WHERE `entryorguid` = 21687 AND `id` = 1;
UPDATE `smart_scripts` SET `comment` = "Gromtor, Son of Oronok - On Reached WP9 - Set Unit Flags" WHERE `entryorguid` = 21687 AND `id` = 2;
UPDATE `smart_scripts` SET `comment` = "Gromtor, Son of Oronok - On Reached WP9 - Set Faction" WHERE `entryorguid` = 21687 AND `id` = 3;
UPDATE `smart_scripts` SET `comment` = "Gromtor, Son of Oronok - On Reached WP9 - Set Aggresive" WHERE `entryorguid` = 21687 AND `id` = 4;


SET @PATH = 21686;
DELETE FROM `waypoints` WHERE `entry` = @PATH;
INSERT INTO `waypoints` VALUES
(@PATH, 1, -3602.366, 1896.522, 47.24055, 'Borak, Son of Oronok'),
(@PATH, 2, -3604.533, 1895.627, 47.24055, 'Borak, Son of Oronok'),
(@PATH, 3, -3610.827, 1892.648, 47.24055, 'Borak, Son of Oronok'),
(@PATH, 4, -3618.559, 1887.337, 47.54847, 'Borak, Son of Oronok'),
(@PATH, 5, -3624.719, 1885.588, 49.00593, 'Borak, Son of Oronok'),
(@PATH, 6, -3627.542, 1877.306, 51.58440, 'Borak, Son of Oronok'),
(@PATH, 7, -3633.807, 1873.102, 53.98977, 'Borak, Son of Oronok'),
(@PATH, 8, -3640.212, 1868.054, 55.01543, 'Borak, Son of Oronok'),
(@PATH, 9, -3643.217, 1860.473, 55.87585, 'Borak, Son of Oronok'),
(@PATH, 10, -3644.647, 1856.673, 56.37634, 'Borak, Son of Oronok');

UPDATE `smart_scripts` SET `event_param1` = 10, `comment` = "Borak, Son of Oronok - On Reached WP10 - Set Home Position" WHERE `entryorguid` = 21686 AND `id` = 1;
UPDATE `smart_scripts` SET `comment` = "Borak, Son of Oronok - On Reached WP10 - Set Faction" WHERE `entryorguid` = 21686 AND `id` = 2;
UPDATE `smart_scripts` SET `comment` = "Borak, Son of Oronok - On Reached WP10 - Set Unit Flags" WHERE `entryorguid` = 21686 AND `id` = 3;
UPDATE `smart_scripts` SET `comment` = "Borak, Son of Oronok - On Reached WP10 - Set Aggresive" WHERE `entryorguid` = 21686 AND `id` = 4;