UPDATE `creature` SET `position_x` = '2267.88', `position_y` = '-60.4341', `position_z` = '424.23' WHERE `creature`.`guid` = 137519;
UPDATE `creature` SET `position_x` = '2265.61', `position_y` = '-56.7263', `position_z` = '424.24' WHERE `creature`.`guid` = 137523;
UPDATE `creature` SET `position_x` = '2258.11', `position_y` = '-62.4593', `position_z` = '423.26', `orientation` = '2.62499' WHERE `creature`.`guid` = 137527;

SET @GUID := (SELECT MAX(guid) from creature) +100; 
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@GUID+1, 33525, 603, 3, 1, 1988, 0, 2261.19, -54.3171, 424.02, 2.6424, 604800, 0, 0, 260660, 20405, 0, 0, 0, 0),
(@GUID+2, 33526, 603, 3, 1, 28685, 0, 2270.55, -53.4002, 424.87, 2.5992, 604800, 0, 0, 260660, 0, 0, 0, 0, 0),
(@GUID+3, 33527, 603, 3, 1, 28679, 0, 2264.28, -48.5906, 424.85, 2.7681, 604800, 0, 0, 195495, 20405, 0, 0, 0, 0),
(@GUID+4, 33526, 603, 3, 1, 28685, 0, 2285.04, 34.2192, 427.15, 4.9845, 604800, 0, 0, 260660, 0, 0, 0, 0, 0),
(@GUID+5, 33525, 603, 3, 1, 1988, 0, 2291.42, 35.6187, 428.15, 4.9216, 604800, 0, 0, 260660, 20405, 0, 0, 0, 0),
(@GUID+6, 33527, 603, 3, 1, 28679, 0, 2291.29, 45.0692, 427.82, 4.6357, 604800, 0, 0, 195495, 20405, 0, 0, 0, 0),
(@GUID+7, 33527, 603, 3, 1, 28679, 0, 2375.39, 3.8380, 423.30, 3.2134, 604800, 0, 0, 195495, 20405, 0, 0, 0, 0),
(@GUID+8, 33526, 603, 3, 1, 28685, 0, 2368.61, 6.8480, 423.14, 3.1191, 604800, 0, 0, 260660, 0, 0, 0, 0, 0),
(@GUID+9, 33525, 603, 3, 1, 1988, 0, 2369.56, -2.1220, 422.97, 2.9856, 604800, 0, 0, 260660, 20405, 0, 0, 0, 0),
(@GUID+10, 33527, 603, 3, 1, 28679, 0, 2336.19, -208.5458, 438.90, 1.4313, 604800, 0, 0, 195495, 20405, 0, 0, 0, 0),
(@GUID+11, 33525, 603, 3, 1, 1988, 0, 2336.95, -200.1120, 438.41, 1.4549, 604800, 0, 0, 260660, 20405, 0, 0, 0, 0),
(@GUID+12, 33526, 603, 3, 1, 28685, 0, 2317.50, -191.7622, 439.67, 1.2389, 604800, 0, 0, 260660, 0, 0, 0, 0, 0);


DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136272;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136272', '136272', '0', '0', '0', '0', 64644);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136272;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136272', '1', '1864.06', '-226.83', '412.99', '0', '0', '0', '0', '100', '0'),
('136272', '2', '1869.26', '-208.806', '412.99', '0', '0', '0', '0', '100', '0'),
('136272', '3', '1864.06', '-226.83', '412.99', '0', '0', '0', '0', '100', '0'),
('136272', '4', '1864.24', '-310.396', '412.99', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136278;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136278;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136278', '136278', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136278;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136278', '1', '1872.41', '-226.350', '412.99', '0', '0', '0', '0', '100', '0'),
('136278', '2', '1875.46', '-208.806', '412.99', '0', '0', '0', '0', '100', '0'),
('136278', '3', '1872.41', '-226.686', '412.99', '0', '0', '0', '0', '100', '0'),
('136278', '4', '1869.02', '-310.396', '412.99', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136279;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136279;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136279', '136279', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136279;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136279', '1', '1866.12', '-226.350', '412.99', '0', '0', '0', '0', '100', '0'),
('136279', '2', '1869.26', '-208.806', '412.99', '0', '0', '0', '0', '100', '0'),
('136279', '3', '1866.12', '-226.686', '412.99', '0', '0', '0', '0', '100', '0'),
('136279', '4', '1864.24', '-310.396', '412.99', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136280;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136280;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136280', '136280', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136280;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136280', '1', '1857.85', '-226.350', '412.99', '0', '0', '0', '0', '100', '0'),
('136280', '2', '1861.61', '-208.806', '412.99', '0', '0', '0', '0', '100', '0'),
('136280', '3', '1857.85', '-226.686', '412.99', '0', '0', '0', '0', '100', '0'),
('136280', '4', '1858.57', '-310.396', '412.99', '0', '0', '0', '0', '100', '0');

--
--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136273;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136273;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136273', '136273', '0', '0', '0', '0', 64644);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136273;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136273', '1', '1927.68', '-344.768', '420.92', '0', '0', '0', '0', '100', '0'),
('136273', '2', '1938.93', '-336.001', '423.06', '0', '0', '0', '0', '100', '0'),
('136273', '3', '1986.52', '-329.022', '425.26', '0', '0', '0', '0', '100', '0'),
('136273', '4', '1938.93', '-336.001', '423.06', '0', '0', '0', '0', '100', '0'),
('136273', '5', '1927.68', '-344.768', '420.92', '0', '0', '0', '0', '100', '0'),
('136273', '6', '1916.87', '-357.047', '419.79', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136276;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136276;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136276', '136276', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136276;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136276', '1', '1923.86', '-340.538', '420.67', '0', '0', '0', '0', '100', '0'),
('136276', '2', '1936.51', '-332.855', '423.27', '0', '0', '0', '0', '100', '0'),
('136276', '3', '1985.74', '-324.426', '425.73', '0', '0', '0', '0', '100', '0'),
('136276', '4', '1936.51', '-332.855', '423.27', '0', '0', '0', '0', '100', '0'),
('136276', '5', '1923.86', '-340.538', '420.67', '0', '0', '0', '0', '100', '0'),
('136276', '6', '1916.12', '-352.047', '418.57', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136277;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136277;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136277', '136277', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136277;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136277', '1', '1927.68', '-344.768', '420.92', '0', '0', '0', '0', '100', '0'),
('136277', '2', '1938.93', '-336.001', '423.06', '0', '0', '0', '0', '100', '0'),
('136277', '3', '1985.74', '-329.022', '425.26', '0', '0', '0', '0', '100', '0'),
('136277', '4', '1938.93', '-336.001', '423.06', '0', '0', '0', '0', '100', '0'),
('136277', '5', '1927.68', '-344.768', '420.92', '0', '0', '0', '0', '100', '0'),
('136277', '6', '1916.87', '-357.047', '419.79', '0', '0', '0', '0', '100', '0');

--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136275;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136275;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136275', '136275', '0', '0', '0', '0', NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136275;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136275', '1', '1930.98', '-348.421', '421.11', '0', '0', '0', '0', '100', '0'),
('136275', '2', '1942.70', '-340.902', '423.15', '0', '0', '0', '0', '100', '0'),
('136275', '3', '1985.74', '-333.625', '424.88', '0', '0', '0', '0', '100', '0'),
('136275', '4', '1942.70', '-340.902', '423.15', '0', '0', '0', '0', '100', '0'),
('136275', '5', '1930.98', '-348.421', '421.11', '0', '0', '0', '0', '100', '0'),
('136275', '6', '1914.13', '-357.047', '421.77', '0', '0', '0', '0', '100', '0');

--
--
UPDATE `creature` SET `MovementType` = '2' WHERE `creature`.`guid` = 136282;

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 136282;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('136282', '136282', '0', '0', '0', '0', 64644);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 136282;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
('136282', '1', '1841.72', '-362.713', '412.46', '0', '0', '0', '0', '100', '0'),
('136282', '2', '1853.23', '-375.055', '413.36', '0', '0', '0', '0', '100', '0'),
('136282', '3', '1873.04', '-373.526', '413.06', '0', '0', '0', '0', '100', '0'),
('136282', '4', '1887.19', '-352.453', '412.42', '0', '0', '0', '0', '100', '0'),
('136282', '5', '1870.98', '-334.917', '412.83', '0', '0', '0', '0', '100', '0'),
('136282', '6', '1852.43', '-340.344', '412.40', '0', '0', '0', '0', '100', '0'),
('136282', '7', '1844.83', '-355.548', '412.83', '0', '0', '0', '0', '100', '0'),
('136282', '8', '1819.62', '-357.744', '413.15', '0', '0', '0', '0', '100', '0');

UPDATE `creature_template` SET `Health_mod` = '1435' WHERE `creature_template`.`entry` = 33190;
UPDATE `creature_template` SET `Health_mod` = '14' WHERE `creature_template`.`entry` = 34005;