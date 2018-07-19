-- Plagueborn Horror
DELETE FROM `creature_addon` WHERE `guid` = 202236;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(202236, 368793, 0, 0, 1, 0, '');
DELETE FROM `waypoint_data` WHERE `id` = 368793;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `action`, `action_chance`, `wpguid`) VALUES 
(368793, 1, 770.268, 84.9432, 512.584, 2.99149, 0, 0, 100, 0),
(368793, 2, 835.758, 134.736, 509.439, 3.9803, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` = 201981;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (201981, 368790, 0, 0, 1, 0, '');
DELETE FROM `waypoint_data` WHERE `id` = 368790;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `action`, `action_chance`, `wpguid`) VALUES 
(368790, 1, 824.849, 97.2298, 509.565, 4.95185, 0, 0, 100, 0),
(368790, 2, 836.37, 98.6893, 510.137, 0.1083, 0, 0, 100, 0),
(368790, 3, 845.729, 88.1699, 510.406, 5.44979, 0, 0, 100, 0),
(368790, 4, 836.37, 98.6893, 510.137, 0.1083, 0, 0, 100, 0),
(368790, 5, 824.849, 97.2298, 509.565, 4.95185, 0, 0, 100, 0),
(368790, 6, 793.219, 49.6387, 497.959, 1.07356, 0, 0, 100, 0);
