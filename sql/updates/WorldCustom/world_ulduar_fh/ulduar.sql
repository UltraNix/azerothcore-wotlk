DELETE FROM `smart_scripts` WHERE `entryorguid` = 34069;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(34069, 0, 0, 0, 0, 0, 100, 0, 3000, 8000, 12000, 20000, 11, 64697, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Earthquake'),
(34069, 0, 1, 0, 0, 0, 100, 0, 3000, 5000, 6000, 10000, 11, 64698, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Pyroblast'),
(34069, 0, 2, 0, 0, 0, 100, 1, 3000, 5000, 6000, 10000, 11, 64705, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Only once per spawn - cast Unquenchable Flames');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (64705, 64706);
INSERT INTO `spell_script_names` VALUES
(64705, "spell_unquenchable_flames"),
(64706, "spell_unquenchable_flames");

DELETE FROM `smart_scripts` WHERE `entryorguid` = 34164;
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_mechagnome_battletank" WHERE `entry` = 34164;

DELETE FROM `waypoint_data` WHERE `id` = 136453 * 10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(136453 * 10, 1, 24.9023, 156.816, 432.789),
(136453 * 10, 2, -180.333, 155.328, 432.789),
(136453 * 10, 3, -112.650, 154.530, 432.789);

DELETE FROM `creature_addon` WHERE `guid` = 136453;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(136453, 136453 * 10, 0, 0, 1, 0, "");

UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = 136453;

DELETE FROM `creature_template_addon` WHERE `entry` IN (34147, 34148);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(34147, 0, 0, 0, 1, 0, '64616'),
(34148, 0, 0, 0, 1, 0, '64616');

DELETE FROM `creature_template_addon` WHERE `entry` = 34194;
UPDATE `creature_template` SET `ScriptName` = "npc_superheated_winds" WHERE `entry` = 34194;

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=1;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 1, 0, 5176, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=1;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 1, 0, 0, 592.50330, -98.551980, 391.60040),
(33287, 1, 0, 1, 592.21530, -99.816540, 391.80870),
(33287, 1, 0, 2, 591.46530, -109.81650, 391.80870),
(33287, 1, 0, 3, 589.21530, -119.31650, 391.80870),
(33287, 1, 0, 4, 581.21530, -128.31650, 391.80870),
(33287, 1, 0, 5, 574.92730, -133.58110, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=2;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 2, 0, 2375, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=2;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 2, 0, 0, 574.92730, -133.58110, 391.51710),
(33287, 2, 0, 1, 575.80900, -133.45180, 391.70690),
(33287, 2, 0, 2, 584.30900, -128.95180, 391.70690);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=3;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 3, 0, 4106, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=3;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 3, 0, 0, 584.30900, -128.95180, 391.70690),
(33287, 3, 0, 1, 593.52340, -130.30840, 391.70690),
(33287, 3, 0, 2, 592.52340, -116.05840, 391.70690),
(33287, 3, 0, 3, 591.77340, -107.05840, 391.70690),
(33287, 3, 0, 4, 592.35630, -99.294380, 391.51710);

-- 25

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=4;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 4, 0, 6570, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=4;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 4, 0, 0, 592.50330, -98.551980, 391.60040),
(33287, 4, 0, 1, 591.03580, -99.607860, 391.80870),
(33287, 4, 0, 2, 583.03580, -101.60790, 391.80870),
(33287, 4, 0, 3, 574.28580, -110.60790, 391.80870),
(33287, 4, 0, 4, 564.78580, -129.35790, 391.80870),
(33287, 4, 0, 5, 561.56820, -137.66370, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=5;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 5, 0, 2111, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=5;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 5, 0, 0, 561.56820, -137.66370, 391.51710),
(33287, 5, 0, 1, 562.96840, -136.93030, 391.76710),
(33287, 5, 0, 2, 566.46840, -132.68030, 391.76710),
(33287, 5, 0, 3, 571.71840, -130.93030, 391.76710),
(33287, 5, 0, 4, 574.86850, -133.69690, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=6;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 6, 0, 2435, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=6;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 6, 0, 0, 574.86850, -133.69690, 391.51710),
(33287, 6, 0, 1, 575.80470, -133.00260, 391.76710),
(33287, 6, 0, 2, 584.30470, -129.50260, 391.76710),
(33287, 6, 0, 3, 590.30470, -128.75260, 391.76710),
(33287, 6, 0, 4, 592.24080, -131.30820, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=7;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 7, 0, 2689, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=7;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 7, 0, 0, 592.24080, -131.30820, 391.51710),
(33287, 7, 0, 1, 593.93800, -130.91290, 391.59870),
(33287, 7, 0, 2, 602.93800, -128.66290, 391.59870),
(33287, 7, 0, 3, 607.93800, -131.66290, 391.34870),
(33287, 7, 0, 4, 609.63510, -136.01760, 391.18030);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=8;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 8, 0, 5106, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=8;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 8, 0, 0, 609.63510, -136.01760, 391.18030),
(33287, 8, 0, 1, 607.93800, -130.71680, 391.34870),
(33287, 8, 0, 2, 603.43800, -117.46680, 391.34870),
(33287, 8, 0, 3, 596.93800, -107.21680, 391.59870),
(33287, 8, 0, 4, 592.24090, -99.416020, 391.51710);

-- Engineer East

-- 10

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=9;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 9, 0, 5703, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=9;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 9, 0, 0, 589.53280, -95.322810, 391.60040),
(33287, 9, 0, 1, 588.59990, -96.915040, 391.80870),
(33287, 9, 0, 2, 580.34990, -102.41500, 391.80870),
(33287, 9, 0, 3, 574.09990, -108.91500, 391.80870),
(33287, 9, 0, 4, 569.59990, -118.66500, 391.80870),
(33287, 9, 0, 5, 568.66690, -132.50730, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=10;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 10, 0, 2551, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=10;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 10, 0, 0, 568.66690, -132.50730, 391.51710),
(33287, 10, 0, 1, 570.50920, -131.02470, 391.76710),
(33287, 10, 0, 2, 579.25920, -126.52470, 391.76710),
(33287, 10, 0, 3, 586.35140, -130.54220, 391.51710);


DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=11;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 11, 0, 4375, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=11;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 11, 0, 0, 586.35140, -130.54220, 391.51710),
(33287, 11, 0, 1, 586.98820, -127.71770, 391.76710),
(33287, 11, 0, 2, 590.73820, -116.71770, 391.76710),
(33287, 11, 0, 3, 590.73820, -105.96770, 391.76710),
(33287, 11, 0, 4, 589.12480, -96.393230, 391.51710);

-- 25

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=12;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 12, 0, 6953, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=12;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 12, 0, 0, 589.53280, -95.322810, 391.60040),
(33287, 12, 0, 1, 587.84770, -95.547740, 391.80870),
(33287, 12, 0, 2, 579.59770, -100.29770, 391.80870),
(33287, 12, 0, 3, 573.59770, -107.04770, 391.80870),
(33287, 12, 0, 4, 569.09770, -115.04770, 391.80870),
(33287, 12, 0, 5, 559.59770, -131.29770, 391.80870),
(33287, 12, 0, 6, 557.16260, -138.27270, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=13;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 13, 0, 1853, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=13;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 13, 0, 0, 557.16260, -138.27270, 391.51710),
(33287, 13, 0, 1, 558.27150, -136.16690, 391.76710),
(33287, 13, 0, 2, 565.27150, -132.66690, 391.76710),
(33287, 13, 0, 3, 569.88050, -133.56110, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=14;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 14, 0, 2155, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=14;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 14, 0, 0, 569.88050, -133.56110, 391.51710),
(33287, 14, 0, 1, 574.97390, -132.21020, 391.76710),
(33287, 14, 0, 2, 580.22390, -130.71020, 391.76710),
(33287, 14, 0, 3, 586.56720, -131.85940, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=15;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 15, 0, 5040, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=15;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 15, 0, 0, 586.56720, -131.85940, 391.51710),
(33287, 15, 0, 1, 589.26450, -129.92940, 391.76710),
(33287, 15, 0, 2, 599.51450, -129.67940, 391.76710),
(33287, 15, 0, 3, 603.96190, -133.99950, 391.51710);

-- Engineer West

-- 10

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=16;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 16, 0, 5932, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=16;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 16, 0, 0, 594.30190, -94.381840, 391.60040),
(33287, 16, 0, 1, 592.85390, -95.531520, 391.80870),
(33287, 16, 0, 2, 583.85390, -102.03150, 391.80870),
(33287, 16, 0, 3, 576.85390, -107.28150, 391.80870),
(33287, 16, 0, 4, 573.10390, -118.28150, 391.80870),
(33287, 16, 0, 5, 572.40590, -132.18120, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=17;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 17, 0, 2337, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=17;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 17, 0, 0, 572.40590, -132.18120, 391.51710),
(33287, 17, 0, 1, 573.77820, -131.55440, 391.76710),
(33287, 17, 0, 2, 583.77820, -128.05440, 391.76710),
(33287, 17, 0, 3, 590.15060, -129.92770, 391.51710);


DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=18;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 18, 0, 4440, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=18;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 18, 0, 0, 590.15060, -129.92770, 391.51710),
(33287, 18, 0, 1, 590.66970, -128.37400, 391.76710),
(33287, 18, 0, 2, 592.66970, -113.37400, 391.76710),
(33287, 18, 0, 3, 594.66970, -100.12400, 391.76710),
(33287, 18, 0, 4, 594.18870, -94.820260, 391.51710);

-- 25

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=19;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 19, 0, 6906, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=19;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 19, 0, 0, 594.30190, -94.381840, 391.60040),
(33287, 19, 0, 1, 593.02330, -94.994300, 391.80870),
(33287, 19, 0, 2, 586.02330, -99.744300, 391.80870),
(33287, 19, 0, 3, 577.02330, -105.74430, 391.80870),
(33287, 19, 0, 4, 572.52330, -114.49430, 391.80870),
(33287, 19, 0, 5, 566.52330, -124.49430, 391.80870),
(33287, 19, 0, 6, 560.74480, -136.10680, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=20;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 20, 0, 1623, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=20;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 20, 0, 0, 560.74480, -136.10680, 391.51710),
(33287, 20, 0, 1, 561.80880, -135.08010, 391.76710),
(33287, 20, 0, 2, 566.30880, -131.33010, 391.76710),
(33287, 20, 0, 3, 571.87280, -131.55340, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=21;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 21, 0, 2427, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=21;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 21, 0, 0, 571.87280, -131.55340, 391.51710),
(33287, 21, 0, 1, 574.20680, -131.91800, 391.76710),
(33287, 21, 0, 2, 582.70680, -128.66800, 391.76710),
(33287, 21, 0, 3, 590.54090, -129.78250, 391.51710);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=22;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 22, 0, 2123, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=22;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 22, 0, 0, 590.54090, -129.78250, 391.51710),
(33287, 22, 0, 1, 593.33170, -129.52560, 392.16520),
(33287, 22, 0, 2, 601.08170, -128.77560, 391.66520),
(33287, 22, 0, 3, 606.12250, -132.76870, 391.31340);

DELETE FROM `script_spline_chain_meta` WHERE `entry`=33287 AND `chainId`=23;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(33287, 23, 0, 5082, 0);

DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=33287 AND `chainId`=23;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(33287, 23, 0, 0, 606.12250, -132.76870, 391.31340),
(33287, 23, 0, 1, 606.97240, -130.52870, 391.41520),
(33287, 23, 0, 2, 603.72240, -119.77870, 391.41520),
(33287, 23, 0, 3, 597.97240, -108.77870, 391.66520),
(33287, 23, 0, 4, 595.47240, -101.52870, 391.66520),
(33287, 23, 0, 5, 594.32230, -94.788800, 391.51710);

DELETE FROM `vehicle_template_accessory` WHERE entry IN (34146, 34150, 34151);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 34137;
UPDATE `creature_template` SET `AIname` = "", `ScriptName` = "npc_white_jormungar_ulduar" WHERE `entry` = 34137;

-- Ward of Life
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (34275,34276);
-- Writhin Lasher
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (33387,34277);
-- Razorscale
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (33186,33724);
-- Hodir
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (32845,32846);
-- Freya
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (32906,33360);
-- Detonating Lasher
UPDATE `creature_template` SET `speed_run`=2.01 WHERE `entry` IN (32918,33399);
-- Leviathan MK 2
UPDATE `creature_template` SET `speed_run`=2.01 WHERE `entry` IN (33432,34106);
-- Emergency Fire Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (34147,34148);
-- Bomb Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (33836,34218);
-- Assault Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (34057,34115);
-- General Vezax
UPDATE `creature_template` SET `speed_run`=2.34 WHERE `entry` IN (33271,33449);
-- Saronite Animus
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (33524,34152);
-- Guardian of Yogg-Saron
UPDATE `creature_template` SET `speed_run`=1.71 WHERE `entry` IN (33136,33968);
-- Immortal Guardian
UPDATE `creature_template` SET `speed_run`=2.20 WHERE `entry` IN (33988,33989);
-- Algalon the Observer
UPDATE `creature_template` SET `speed_run`=2.18 WHERE `entry` IN (32871,33070);
-- Dark Matter
UPDATE `creature_template` SET `speed_run`=0.78 WHERE `entry` IN (33089,34221);
-- Unleashed Dark matter
UPDATE `creature_template` SET `speed_run`=1.45 WHERE `entry` IN (34097,34222);

DELETE FROM `spell_script_names` WHERE `spell_id` = 64397;
INSERT INTO `spell_script_names` VALUES
(64397, "spell_summon_swarming_defender_auriaya");

-- Allow parry-hasten for every creature except Kologarn
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~8 WHERE `entry` IN
(22515,
24921,
32780,
32845,
32857,
32865,
32867,
32879,
32892,
32906,
32913,
32914,
32915,
32922,
32923,
32924,
32925,
32927,
33054,
33059,
33060,
33062,
33063,
33089,
33109,
33113,
33118,
33121,
33134,
33140,
33141,
33186,
33213,
33214,
33235,
33236,
33237,
33241,
33242,
33244,
33264,
33271,
33282,
33293,
33350,
33354,
33355,
33378,
33430,
33431,
33432,
33515,
33525,
33526,
33527,
33528,
33571,
33575,
33576,
33579,
33620,
33622,
33624,
33626,
33627,
33629,
33661,
33662,
33669,
33672,
33686,
33696,
33699,
33701,
33721,
33722,
33725,
33754,
33755,
33772,
33774,
33775,
33779,
33818,
33819,
33820,
33822,
33823,
33824,
33874,
33956,
33957,
34014,
34054,
34069,
34085,
34086,
34096,
34133,
34134,
34135,
34146,
34150,
34151,
34164,
34183,
34190,
34191,
34192,
34193,
34196,
34197,
34198,
34199,
34234,
34267,
34269,
34271,
34273,
32846,
33694,
33147,
33693,
33360,
33392,
33393,
33391,
33692,
34045,
34221,
34003,
33190,
33191,
34332,
33724,
34113,
34105,
33449,
33885,
33729,
33737,
33732,
33731,
34106,
34175,
33735,
33734,
33741,
33733,
33700,
33723,
33757,
33758,
33773,
33827,
33829,
33830,
33828,
33832,
33831,
34166,
34185,
34186,
34201,
34139,
34141,
34142,
34165,
34214,
34229,
34217,
34216,
34220,
34245,
34226,
34236,
34237,
34235,
34268,
34270,
34272,
34274,
32871,
33070);

UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 8 WHERE `entry` IN (32930, 33909);

UPDATE `creature_template` SET `dmg_multiplier` = 4 WHERE `entry` IN (33236, 34113, 33572, 34247);
UPDATE `creature_template` SET `dmg_multiplier` = 13.5 WHERE `entry` IN (34164, 34165);
UPDATE `creature_template` SET `dmg_multiplier` = 19.42 WHERE `entry` = 33113;
UPDATE `creature_template` SET `dmg_multiplier` = 23.07 WHERE `entry` = 34003;
UPDATE `creature_template` SET `dmg_multiplier` = 3.43 WHERE `entry` = 33388;
UPDATE `creature_template` SET `dmg_multiplier` = 41.30 WHERE `entry` = 33850;
UPDATE `creature_template` SET `dmg_multiplier` = 35.33 WHERE `entry` = 33851;
UPDATE `creature_template` SET `dmg_multiplier` = 15.56 WHERE `entry` = 33724;
UPDATE `creature_template` SET `dmg_multiplier` = 11.30 WHERE `entry` = 34069;
UPDATE `creature_template` SET `dmg_multiplier` = 14.44 WHERE `entry` = 34185;
UPDATE `creature_template` SET `dmg_multiplier` = 14.56 WHERE `entry` = 34201;
UPDATE `creature_template` SET `dmg_multiplier` = 16.63 WHERE `entry` = 33190;
UPDATE `creature_template` SET `dmg_multiplier` = 14.67 WHERE `entry` = 34237;
UPDATE `creature_template` SET `dmg_multiplier` = 8.68 WHERE `entry` = 34190;
UPDATE `creature_template` SET `dmg_multiplier` = 10.75 WHERE `entry` = 34229;
UPDATE `creature_template` SET `dmg_multiplier` = 14.26 WHERE `entry` = 33692;
UPDATE `creature_template` SET `dmg_multiplier` = 14 WHERE `entry` = 33909;
UPDATE `creature_template` SET `dmg_multiplier` = 8.61 WHERE `entry` = 33722;
UPDATE `creature_template` SET `dmg_multiplier` = 8.61 WHERE `entry` = 33723;
UPDATE `creature_template` SET `dmg_multiplier` = 14.5 WHERE `entry` = 34139;
UPDATE `creature_template` SET `dmg_multiplier` = 8 WHERE `entry` = 33755;
UPDATE `creature_template` SET `dmg_multiplier` = 16 WHERE `entry` = 33148;
UPDATE `creature_template` SET `dmg_multiplier` = 2.30 WHERE `entry` = 32877;
UPDATE `creature_template` SET `dmg_multiplier` = 2.81 WHERE `entry` = 33155;
UPDATE `creature_template` SET `dmg_multiplier` = 7.50 WHERE `entry` = 32876;
UPDATE `creature_template` SET `dmg_multiplier` = 11.56 WHERE `entry` = 33158;
UPDATE `creature_template` SET `dmg_multiplier` = 1.42 WHERE `entry` = 32865;
UPDATE `creature_template` SET `dmg_multiplier` = 1.32 WHERE `entry` = 33147;
UPDATE `creature_template` SET `dmg_multiplier` = 9 WHERE `entry` = 33430;
UPDATE `creature_template` SET `dmg_multiplier` = 15 WHERE `entry` = 33732;
UPDATE `creature_template` SET `dmg_multiplier` = 17.69 WHERE `entry` = 33401;
UPDATE `creature_template` SET `dmg_multiplier` = 17.69 WHERE `entry` = 33400;
UPDATE `creature_template` SET `dmg_multiplier` = 9, `baseattacktime` = 1500 WHERE `entry` = 33391;
UPDATE `creature_template` SET `dmg_multiplier` = 5.18 WHERE `entry` = 34183;
UPDATE `creature_template` SET `dmg_multiplier` = 12.23 WHERE `entry` = 34214;
UPDATE `creature_template` SET `dmg_multiplier` = 8 WHERE `entry` = 34184;
UPDATE `creature_template` SET `dmg_multiplier` = 15.77 WHERE `entry` = 34219;
UPDATE `creature_template` SET `dmg_multiplier` = 23.88 WHERE `entry` = 34057;
UPDATE `creature_template` SET `dmg_multiplier` = 59.13 WHERE `entry` = 34115;
UPDATE `creature_template` SET `dmg_multiplier` = 8.25 WHERE `entry` = 33772;
UPDATE `creature_template` SET `dmg_multiplier` = 29.02 WHERE `entry` = 33839;
UPDATE `creature_template` SET `dmg_multiplier` = 4.27 WHERE `entry` = 33824;
UPDATE `creature_template` SET `dmg_multiplier` = 10.02 WHERE `entry` = 33831;
UPDATE `creature_template` SET `dmg_multiplier` = 60.76 WHERE `entry` = 33806;
UPDATE `creature_template` SET `dmg_multiplier` = 62.62 WHERE `entry` = 33815;
UPDATE `creature_template` SET `dmg_multiplier` = 10.77 WHERE `entry` = 34152;
UPDATE `creature_template` SET `dmg_multiplier` = 7.67 WHERE `entry` = 33136;
UPDATE `creature_template` SET `dmg_multiplier` = 11.16 WHERE `entry` = 33988;
UPDATE `creature_template` SET `dmg_multiplier` = 15.74 WHERE `entry` = 33989;
UPDATE `creature_template` SET `dmg_multiplier` = 7.66 WHERE `entry` = 28235;
UPDATE `creature_template` SET `dmg_multiplier` = 7.45 WHERE `entry` = 31874;
UPDATE `creature_template` SET `dmg_multiplier` = 4.04 WHERE `entry` = 34097;
UPDATE `creature_template` SET `dmg_multiplier` = 7 WHERE `entry` = 34222;
UPDATE `creature_template` SET `dmg_multiplier` = 8 WHERE `entry` = 33360;

UPDATE `creature_template` SET `baseattacktime`=1500 WHERE `entry` IN (34197,34226);
UPDATE `creature_template` SET `baseattacktime` = 1000 WHERE `entry` IN (34034, 34169, 33824, 33831);

-- Ward of Life
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (34275,34276);
-- Writhin Lasher
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (33387,34277);
-- Razorscale
UPDATE `creature_template` SET `speed_run`=2.56 WHERE `entry` IN (33186,33724);
-- Hodir
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (32845,32846);
-- Freya
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (32906,33360);
-- Detonating Lasher
UPDATE `creature_template` SET `speed_run`=2.01 WHERE `entry` IN (32918,33399);
-- Leviathan MK 2
UPDATE `creature_template` SET `speed_run`=2.01 WHERE `entry` IN (33432,34106);
-- Emergency Fire Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (34147,34148);
-- Bomb Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (33836,34218);
-- Assault Bot
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (34057,34115);
-- General Vezax
UPDATE `creature_template` SET `speed_run`=2.34 WHERE `entry` IN (33271,33449);
-- Saronite Animus
UPDATE `creature_template` SET `speed_run`=1.44 WHERE `entry` IN (33524,34152);
-- Guardian of Yogg-Saron
UPDATE `creature_template` SET `speed_run`=1.71 WHERE `entry` IN (33136,33968);
-- Immortal Guardian
UPDATE `creature_template` SET `speed_run`=2.20 WHERE `entry` IN (33988,33989);
-- Algalon the Observer
UPDATE `creature_template` SET `speed_run`=2.18 WHERE `entry` IN (32871,33070);
-- Dark Matter
UPDATE `creature_template` SET `speed_run`=0.78 WHERE `entry` IN (33089,34221);
-- Unleashed Dark matter
UPDATE `creature_template` SET `speed_run`=1.45 WHERE `entry` IN (34097,34222);

SET @CGUID:= 303313;
DELETE FROM `creature` WHERE `guid` IN (@CGUID, @CGUID + 1);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID, 34151, 603, 3, 1, 27823, 0, 1873.17, -287.697, 412.299, 4.66511, 604800, 0, 0, 12600, 0, 0, 0, 0, 0),
(@CGUID + 1, 33571, 603, 2, 1, 0, 0, 235.717, 356.3, 414.051, 4.71893, 604800, 0, 0, 5342, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET dmgschool = 2 WHERE `entry` IN (33838, 33839);

DELETE FROM `creature_addon` WHERE `guid` IN
(136560,
136561,
136562,
136563,
136564,
136565,
136566,
136567,
136568,
136569,
136570,
136571,
136572,
136573,
136574,
136575,
136578,
136579,
136580,
136581,
136582,
136583,
136584,
136585,
154204,
154205,
154206,
154207);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(136560, 0, 0, 0, 1, 0, '18950'),
(136561, 0, 0, 0, 1, 0, '18950'),
(136562, 0, 0, 0, 1, 0, '18950'),
(136563, 0, 0, 0, 1, 0, '18950'),
(136564, 0, 0, 0, 1, 0, '18950'),
(136565, 0, 0, 0, 1, 0, '18950'),
(136566, 0, 0, 0, 1, 0, '18950'),
(136567, 0, 0, 0, 1, 0, '18950'),
(136568, 0, 0, 0, 1, 0, '18950'),
(136569, 0, 0, 0, 1, 0, '18950'),
(136570, 0, 0, 0, 1, 0, '18950'),
(136571, 0, 0, 0, 1, 0, '18950'),
(136572, 0, 0, 0, 1, 0, '18950'),
(136573, 0, 0, 0, 1, 0, '18950'),
(136574, 0, 0, 0, 1, 0, '18950'),
(136575, 0, 0, 0, 1, 0, '18950'),
(136578, 0, 0, 0, 1, 0, '18950'),
(136579, 0, 0, 0, 1, 0, '18950'),
(136580, 0, 0, 0, 1, 0, '18950'),
(136581, 0, 0, 0, 1, 0, '18950'),
(136582, 0, 0, 0, 1, 0, '18950'),
(136583, 0, 0, 0, 1, 0, '18950'),
(136584, 0, 0, 0, 1, 0, '18950'),
(136585, 0, 0, 0, 1, 0, '18950'),
(154204, 0, 0, 0, 1, 0, '18950'),
(154205, 0, 0, 0, 1, 0, '18950'),
(154206, 0, 0, 0, 1, 0, '18950'),
(154207, 0, 0, 0, 1, 0, '18950');

DELETE FROM `creature_addon` WHERE `guid` IN
(136533,
136534,
136535,
136536,
136586,
136587,
136588,
136589,
136591,
136592);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(136533, 0, 0, 0, 1, 27, '18950'),
(136534, 0, 0, 0, 1, 27, '18950'),
(136535, 0, 0, 0, 1, 0, '18950'),
(136536, 0, 0, 0, 1, 0, '18950'),
(136586, 0, 0, 0, 1, 27, '18950'),
(136587, 0, 0, 0, 1, 27, '18950'),
(136588, 0, 0, 0, 1, 0, '18950'),
(136589, 0, 0, 0, 1, 0, '18950'),
(136591, 0, 0, 0, 1, 27, '18950'),
(136592, 0, 0, 0, 1, 27, '18950');

UPDATE `creature_template` SET `InhabitType` = 1 WHERE `entry` IN (34097, 34222);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 33838;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(33838, 0, 0, 0, 0, 0, 100, 0, 500, 500, 60000, 60000, 11, 63778, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Fire Shield'),
(33838, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 15000, 15000, 11, 38064, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Blast Wave');

UPDATE `creature_template` SET `mindmg` = 6000, `maxdmg` = 8800, `dmg_multiplier` = 1 WHERE `entry` = 33838;

SET @ALGALON_BASE_HEALTH_MOD:= 2500;

UPDATE `creature_template` SET `Health_mod` = @ALGALON_BASE_HEALTH_MOD + (@ALGALON_BASE_HEALTH_MOD * 0.2) WHERE `entry` = 33070;

SET @PATH1:= 152322 * 10;
UPDATE `creature` SET `position_x` = 2823.914, `position_y` = 2651.755, `position_z` = 371.97 WHERE `guid` = 152322;

DELETE FROM `waypoint_data` WHERE `id` = @PATH1;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH1, 1, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH1, 2, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH1, 3, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH1, 4, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH1, 5, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH1, 6, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH1, 7, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH1, 8, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH1, 9, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH1, 10, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH1, 11, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH1, 12, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH1, 13, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH1, 14, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH1, 15, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH1, 16, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH1, 17, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH1, 18, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH1, 19, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH1, 20, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH1, 21, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH1, 22, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH1, 23, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH1, 24, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH1, 25, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH1, 26, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH1, 27, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH1, 28, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH1, 29, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH1, 30, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH1, 31, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH1, 32, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH1, 33, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH1, 34, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH1, 35, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH1, 36, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH1, 37, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH1, 38, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH1, 39, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH1, 40, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH1, 41, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH1, 42, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH1, 43, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH1, 44, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH1, 45, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH1, 46, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH1, 47, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH1, 48, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH1, 49, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH1, 50, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH1, 51, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH1, 52, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH1, 53, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH1, 54, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH1, 55, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH1, 56, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH1, 57, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH1, 58, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH1, 59, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH1, 60, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH1, 61, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH1, 62, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH1, 63, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH1, 64, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH1, 65, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH1, 66, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH1, 67, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH1, 68, 2823.914307, 2651.755371, 371.979401, 1); -- end


SET @PATH2:= 152335 * 10;
UPDATE `creature` SET `position_x` = 2819.395, `position_y` = 2647.018, `position_z` = 371.979 WHERE `guid` = 152335;

DELETE FROM `waypoint_data` WHERE `id` = @PATH2;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH2, 1, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH2, 2, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH2, 3, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH2, 4, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH2, 5, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH2, 6, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH2, 7, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH2, 8, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH2, 9, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH2, 10, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH2, 11, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH2, 12, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH2, 13, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH2, 14, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH2, 15, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH2, 16, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH2, 17, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH2, 18, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH2, 19, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH2, 20, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH2, 21, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH2, 22, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH2, 23, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH2, 24, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH2, 25, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH2, 26, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH2, 27, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH2, 28, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH2, 29, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH2, 30, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH2, 31, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH2, 32, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH2, 33, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH2, 34, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH2, 35, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH2, 36, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH2, 37, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH2, 38, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH2, 39, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH2, 40, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH2, 41, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH2, 42, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH2, 43, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH2, 44, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH2, 45, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH2, 46, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH2, 47, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH2, 48, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH2, 49, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH2, 50, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH2, 51, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH2, 52, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH2, 53, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH2, 54, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH2, 55, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH2, 56, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH2, 57, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH2, 58, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH2, 59, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH2, 60, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH2, 61, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH2, 62, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH2, 63, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH2, 64, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH2, 65, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH2, 66, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH2, 67, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH2, 68, 2819.395752, 2647.018555, 371.979431, 1); -- end

SET @PATH3:= 152336 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH3;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH3, 1, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH3, 2, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH3, 3, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH3, 4, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH3, 5, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH3, 6, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH3, 7, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH3, 8, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH3, 9, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH3, 10, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH3, 11, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH3, 12, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH3, 13, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH3, 14, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH3, 15, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH3, 16, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH3, 17, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH3, 18, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH3, 19, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH3, 20, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH3, 21, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH3, 22, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH3, 23, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH3, 24, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH3, 25, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH3, 26, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH3, 27, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH3, 28, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH3, 29, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH3, 30, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH3, 31, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH3, 32, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH3, 33, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH3, 34, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH3, 35, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH3, 36, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH3, 37, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH3, 38, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH3, 39, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH3, 40, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH3, 41, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH3, 42, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH3, 43, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH3, 44, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH3, 45, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH3, 46, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH3, 47, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH3, 48, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH3, 49, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH3, 50, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH3, 51, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH3, 52, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH3, 53, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH3, 54, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH3, 55, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH3, 56, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH3, 57, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH3, 58, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH3, 59, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH3, 60, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH3, 61, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH3, 62, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH3, 63, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH3, 64, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH3, 65, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH3, 66, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH3, 67, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH3, 68, 2786.713135, 2676.620117, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2784.029, `position_y` = 2670.957, `position_z` = 371.979 WHERE `guid` = 152323;
SET @PATH4:= 152323 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH4;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH4, 1, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH4, 2, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH4, 3, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH4, 4, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH4, 5, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH4, 6, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH4, 7,  2664.108887, 2647.853760, 371.979401, 1),
(@PATH4, 8,  2653.782471, 2635.072998, 371.979401, 1),
(@PATH4, 9,  2644.909912, 2621.341309, 371.979401, 1),
(@PATH4, 10,  2638.812744, 2608.165283, 371.979401, 1),
(@PATH4, 11,  2634.720215, 2590.382080, 371.979401, 1),
(@PATH4, 12,  2632.512939, 2570.073486, 371.979401, 1),
(@PATH4, 13,  2634.399414, 2549.973389, 371.979401, 1),
(@PATH4, 14,  2639.209961, 2528.639893, 371.979401, 1),
(@PATH4, 15,  2644.946777, 2517.133789, 371.979401, 1),
(@PATH4, 16,  2655.515869, 2500.761963, 371.979401, 1),
(@PATH4, 17,  2664.791992, 2490.151367, 371.979401, 1),
(@PATH4, 18,  2677.747314, 2480.133789, 371.979401, 1),
(@PATH4, 19,  2689.421143, 2472.844727, 371.979401, 1),
(@PATH4, 20,  2699.613770, 2467.697266, 371.979401, 1),
(@PATH4, 21,  2721.503418, 2462.295654, 371.979401, 1),
(@PATH4, 22,  2736.943359, 2459.809326, 371.979401, 1),
(@PATH4, 23,  2751.850342, 2460.841064, 371.979401, 1),
(@PATH4, 24,  2768.876465, 2463.794434, 371.979401, 1),
(@PATH4, 25,  2783.744873, 2467.658936, 371.979401, 1),
(@PATH4, 26,  2798.720215, 2476.635010, 371.979401, 1),
(@PATH4, 27,  2812.800781, 2486.838623, 371.979401, 1),
(@PATH4, 28,  2819.430908, 2492.777100, 371.979401, 1),
(@PATH4, 29,  2824.456055, 2499.575195, 371.979401, 1),
(@PATH4, 30,  2830.443359, 2495.646973, 371.979401, 1),
(@PATH4, 31,  2825.116699, 2488.251709, 371.979401, 1),
(@PATH4, 32,  2816.045654, 2480.737061, 371.979401, 1),
(@PATH4, 33,  2801.901611, 2471.089844, 371.979401, 1),
(@PATH4, 34,  2786.069824, 2461.972168, 371.979401, 1),
(@PATH4, 35,  2769.232910, 2457.481689, 371.979401, 1),
(@PATH4, 36,  2751.812256, 2454.458008, 371.979401, 1),
(@PATH4, 37,  2737.169922, 2453.573730, 371.979401, 1),
(@PATH4, 38,  2719.959229, 2456.308350, 371.979401, 1),
(@PATH4, 39,  2696.059326, 2462.327393, 371.979401, 1),
(@PATH4, 40,  2685.987061, 2467.614990, 371.979401, 1),
(@PATH4, 41,  2674.336670, 2475.428467, 371.979401, 1),
(@PATH4, 42,  2660.173340, 2486.269775, 371.979401, 1),
(@PATH4, 43,  2650.387939, 2497.161621, 371.979401, 1),
(@PATH4, 44,  2639.180908, 2513.970459, 371.979401, 1),
(@PATH4, 45,  2633.337646, 2525.953857, 371.979401, 1),
(@PATH4, 46,  2628.113037, 2548.929199, 371.979401, 1),
(@PATH4, 47,  2625.548584, 2570.737305, 371.979401, 1),
(@PATH4, 48,  2628.306396, 2591.702637, 371.979401, 1),
(@PATH4, 49,  2632.582764, 2609.958740, 371.979401, 1),
(@PATH4, 50,  2639.201172, 2625.132324, 371.979401, 1),
(@PATH4, 51,  2648.320557, 2638.936768, 371.979401, 1),
(@PATH4, 52,  2661.020264, 2653.529297, 371.979401, 1),
(@PATH4, 53,  2678.046631, 2665.775391, 371.979401, 1),
(@PATH4, 54,  2696.759521, 2676.764404, 371.979401, 1),
(@PATH4, 55,  2715.479492, 2681.816406, 371.979401, 1),
(@PATH4, 56,  2729.585693, 2684.134766, 371.979401, 1),
(@PATH4, 57,  2746.470459, 2685.045654, 371.979401, 1),
(@PATH4, 58,  2765.565918, 2682.073242, 371.979401, 1),
(@PATH4, 59,  2786.713135, 2676.620117, 371.979401, 1),
(@PATH4, 60,  2797.291016, 2670.866699, 371.979401, 1),
(@PATH4, 61,  2810.964355, 2661.586426, 371.979401, 1),
(@PATH4, 62,  2823.914307, 2651.755371, 371.979401, 1),
(@PATH4, 63,  2829.996338, 2642.607422, 371.979431, 1),
(@PATH4, 64,  2824.764648, 2638.736816, 371.979431, 1),
(@PATH4, 65,  2819.395752, 2647.018555, 371.979431, 1),
(@PATH4, 66,  2808.215332, 2656.130127, 371.979401, 1),
(@PATH4, 67,  2794.131592, 2665.513428, 371.979401, 1),
(@PATH4, 68,  2784.029297, 2670.957275, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2746.470, `position_y` = 2685.045, `position_z` = 371.979 WHERE `guid` = 152321;
SET @PATH5:= 152321 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH5;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH5, 1, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH5, 2, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH5, 3, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH5, 4, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH5, 5, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH5, 6, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH5, 7, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH5, 8, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH5, 9, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH5, 10, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH5, 11, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH5, 12, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH5, 13, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH5, 14, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH5, 15, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH5, 16, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH5, 17, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH5, 18, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH5, 19, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH5, 20, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH5, 21, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH5, 22, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH5, 23, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH5, 24, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH5, 25, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH5, 26, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH5, 27, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH5, 28, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH5, 29, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH5, 30, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH5, 31, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH5, 32, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH5, 33, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH5, 34, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH5, 35, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH5, 36, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH5, 37, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH5, 38, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH5, 39, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH5, 40, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH5, 41, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH5, 42, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH5, 43, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH5, 44, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH5, 45, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH5, 46, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH5, 47, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH5, 48, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH5, 49, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH5, 50, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH5, 51, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH5, 52, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH5, 53, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH5, 54, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH5, 55, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH5, 56, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH5, 57, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH5, 58, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH5, 59, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH5, 60, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH5, 61, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH5, 62, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH5, 63, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH5, 64, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH5, 65, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH5, 66, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH5, 67, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH5, 68, 2746.470459, 2685.045654, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2745.600, `position_y` = 2679.047, `position_z` = 371.979 WHERE `guid` = 152334;
SET @PATH6:= 152334 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH6;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH6, 1, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH6, 2, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH6, 3, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH6, 4, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH6, 5, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH6, 6, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH6, 7, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH6, 8, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH6, 9, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH6, 10, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH6, 11, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH6, 12, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH6, 13, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH6, 14, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH6, 15, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH6, 16, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH6, 17, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH6, 18, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH6, 19, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH6, 20, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH6, 21, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH6, 22, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH6, 23, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH6, 24, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH6, 25, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH6, 26, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH6, 27, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH6, 28, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH6, 29, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH6, 30, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH6, 31, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH6, 32, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH6, 33, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH6, 34, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH6, 35, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH6, 36, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH6, 37, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH6, 38, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH6, 39, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH6, 40, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH6, 41, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH6, 42, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH6, 43, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH6, 44, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH6, 45, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH6, 46, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH6, 47, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH6, 48, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH6, 49, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH6, 50, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH6, 51, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH6, 52, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH6, 53, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH6, 54, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH6, 55, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH6, 56, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH6, 57, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH6, 58, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH6, 59, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH6, 60, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH6, 61, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH6, 62, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH6, 63, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH6, 64, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH6, 65, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH6, 66, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH6, 67, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH6, 68, 2745.600586, 2679.047607, 371.979401, 1); -- end

SET @PATH7:= 152337 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH7;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH7, 1, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH7, 2, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH7, 3, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH7, 4, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH7, 5, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH7, 6, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH7, 7, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH7, 8, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH7, 9, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH7, 10, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH7, 11, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH7, 12, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH7, 13, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH7, 14, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH7, 15, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH7, 16, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH7, 17, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH7, 18, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH7, 19, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH7, 20, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH7, 21, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH7, 22, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH7, 23, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH7, 24, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH7, 25, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH7, 26, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH7, 27, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH7, 28, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH7, 29, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH7, 30, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH7, 31, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH7, 32, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH7, 33, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH7, 34, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH7, 35, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH7, 36, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH7, 37, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH7, 38, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH7, 39, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH7, 40, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH7, 41, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH7, 42, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH7, 43, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH7, 44, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH7, 45, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH7, 46, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH7, 47, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH7, 48, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH7, 49, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH7, 50, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH7, 51, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH7, 52, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH7, 53, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH7, 54, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH7, 55, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH7, 56, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH7, 57, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH7, 58, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH7, 59, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH7, 60, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH7, 61, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH7, 62, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH7, 63, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH7, 64, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH7, 65, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH7, 66, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH7, 67, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH7, 68, 2696.759521, 2676.764404, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2699.423, `position_y` = 2670.932, `position_z` = 371.979 WHERE `guid` = 152324;
SET @PATH8:= 152324 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH8;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH8, 1, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH8, 2, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH8, 3, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH8, 4, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH8, 5, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH8, 6, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH8, 7, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH8, 8, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH8, 9, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH8, 10, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH8, 11, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH8, 12, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH8, 13, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH8, 14, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH8, 15, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH8, 16, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH8, 17, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH8, 18, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH8, 19, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH8, 20, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH8, 21, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH8, 22, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH8, 23, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH8, 24, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH8, 25, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH8, 26, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH8, 27, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH8, 28, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH8, 29, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH8, 30, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH8, 31, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH8, 32, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH8, 33, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH8, 34, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH8, 35, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH8, 36, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH8, 37, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH8, 38, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH8, 39, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH8, 40, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH8, 41, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH8, 42, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH8, 43, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH8, 44, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH8, 45, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH8, 46, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH8, 47, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH8, 48, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH8, 49, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH8, 50, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH8, 51, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH8, 52, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH8, 53, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH8, 54, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH8, 55, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH8, 56, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH8, 57, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH8, 58, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH8, 59, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH8, 60, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH8, 61, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH8, 62, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH8, 63, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH8, 64, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH8, 65, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH8, 66, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH8, 67, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH8, 68, 2699.423340, 2670.932617, 371.979401, 1); -- end


UPDATE `creature` SET `position_x` = 2661.020, `position_y` = 2653.529, `position_z` = 371.979 WHERE `guid` = 152320;
SET @PATH9:= 152320 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH9;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH9, 1, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH9, 2, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH9, 3, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH9, 4, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH9, 5, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH9, 6, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH9, 7, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH9, 8, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH9, 9, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH9, 10, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH9, 11, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH9, 12, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH9, 13, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH9, 14, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH9, 15, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH9, 16, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH9, 17, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH9, 18, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH9, 19, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH9, 20, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH9, 21, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH9, 22, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH9, 23, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH9, 24, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH9, 25, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH9, 26, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH9, 27, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH9, 28, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH9, 29, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH9, 30, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH9, 31, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH9, 32, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH9, 33, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH9, 34, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH9, 35, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH9, 36, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH9, 37, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH9, 38, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH9, 39, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH9, 40, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH9, 41, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH9, 42, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH9, 43, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH9, 44, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH9, 45, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH9, 46, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH9, 47, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH9, 48, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH9, 49, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH9, 50, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH9, 51, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH9, 52, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH9, 53, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH9, 54, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH9, 55, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH9, 56, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH9, 57, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH9, 58, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH9, 59, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH9, 60, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH9, 61, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH9, 62, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH9, 63, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH9, 64, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH9, 65, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH9, 66, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH9, 67, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH9, 68, 2661.020264, 2653.529297, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2664.108, `position_y` = 2647.853, `position_z` = 371.979 WHERE `guid` = 152333;
SET @PATH10:= 152333 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH10;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH10, 1, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH10, 2, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH10, 3, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH10, 4, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH10, 5, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH10, 6, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH10, 7, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH10, 8, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH10, 9, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH10, 10, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH10, 11, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH10, 12, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH10, 13, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH10, 14, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH10, 15, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH10, 16, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH10, 17, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH10, 18, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH10, 19, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH10, 20, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH10, 21, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH10, 22, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH10, 23, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH10, 24, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH10, 25, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH10, 26, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH10, 27, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH10, 28, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH10, 29, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH10, 30, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH10, 31, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH10, 32, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH10, 33, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH10, 34, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH10, 35, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH10, 36, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH10, 37, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH10, 38, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH10, 39, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH10, 40, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH10, 41, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH10, 42, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH10, 43, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH10, 44, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH10, 45, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH10, 46, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH10, 47, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH10, 48, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH10, 49, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH10, 50, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH10, 51, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH10, 52, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH10, 53, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH10, 54, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH10, 55, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH10, 56, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH10, 57, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH10, 58, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH10, 59, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH10, 60, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH10, 61, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH10, 62, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH10, 63, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH10, 64, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH10, 65, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH10, 66, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH10, 67, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH10, 68, 2664.108887, 2647.853760, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2632.582, `position_y` = 2609.958, `position_z` = 371.979 WHERE `guid` = 152338;
SET @PATH11:= 152338 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH11;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH11, 1, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH11, 2, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH11, 3, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH11, 4, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH11, 5, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH11, 6, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH11, 7, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH11, 8, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH11, 9, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH11, 10, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH11, 11, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH11, 12, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH11, 13, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH11, 14, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH11, 15, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH11, 16, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH11, 17, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH11, 18, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH11, 19, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH11, 20, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH11, 21, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH11, 22, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH11, 23, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH11, 24, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH11, 25, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH11, 26, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH11, 27, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH11, 28, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH11, 29, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH11, 30, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH11, 31, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH11, 32, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH11, 33, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH11, 34, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH11, 35, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH11, 36, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH11, 37, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH11, 38, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH11, 39, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH11, 40, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH11, 41, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH11, 42, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH11, 43, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH11, 44, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH11, 45, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH11, 46, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH11, 47, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH11, 48, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH11, 49, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH11, 50, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH11, 51, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH11, 52, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH11, 53, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH11, 54, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH11, 55, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH11, 56, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH11, 57, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH11, 58, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH11, 59, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH11, 60, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH11, 61, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH11, 62, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH11, 63, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH11, 64, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH11, 65, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH11, 66, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH11, 67, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH11, 68, 2632.582764, 2609.958740, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2638.812, `position_y` = 2608.165, `position_z` = 371.979 WHERE `guid` = 152325;
SET @PATH12:= 152325 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH12;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH12, 1, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH12, 2, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH12, 3, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH12, 4, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH12, 5, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH12, 6, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH12, 7, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH12, 8, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH12, 9, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH12, 10, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH12, 11, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH12, 12, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH12, 13, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH12, 14, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH12, 15, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH12, 16, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH12, 17, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH12, 18, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH12, 19, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH12, 20, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH12, 21, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH12, 22, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH12, 23, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH12, 24, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH12, 25, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH12, 26, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH12, 27, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH12, 28, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH12, 29, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH12, 30, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH12, 31, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH12, 32, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH12, 33, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH12, 34, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH12, 35, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH12, 36, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH12, 37, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH12, 38, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH12, 39, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH12, 40, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH12, 41, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH12, 42, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH12, 43, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH12, 44, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH12, 45, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH12, 46, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH12, 47, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH12, 48, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH12, 49, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH12, 50, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH12, 51, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH12, 52, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH12, 53, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH12, 54, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH12, 55, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH12, 56, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH12, 57, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH12, 58, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH12, 59, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH12, 60, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH12, 61, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH12, 62, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH12, 63, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH12, 64, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH12, 65, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH12, 66, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH12, 67, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH12, 68, 2638.812744, 2608.165283, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2625.548, `position_y` = 2570.737, `position_z` = 371.979 WHERE `guid` = 152319;
SET @PATH13:= 152319 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH13;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH13, 1, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH13, 2, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH13, 3, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH13, 4, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH13, 5, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH13, 6, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH13, 7, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH13, 8, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH13, 9, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH13, 10, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH13, 11, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH13, 12, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH13, 13, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH13, 14, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH13, 15, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH13, 16, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH13, 17, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH13, 18, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH13, 19, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH13, 20, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH13, 21, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH13, 22, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH13, 23, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH13, 24, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH13, 25, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH13, 26, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH13, 27, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH13, 28, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH13, 29, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH13, 30, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH13, 31, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH13, 32, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH13, 33, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH13, 34, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH13, 35, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH13, 36, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH13, 37, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH13, 38, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH13, 39, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH13, 40, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH13, 41, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH13, 42, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH13, 43, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH13, 44, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH13, 45, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH13, 46, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH13, 47, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH13, 48, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH13, 49, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH13, 50, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH13, 51, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH13, 52, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH13, 53, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH13, 54, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH13, 55, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH13, 56, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH13, 57, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH13, 58, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH13, 59, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH13, 60, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH13, 61, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH13, 62, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH13, 63, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH13, 64, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH13, 65, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH13, 66, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH13, 67, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH13, 68, 2625.548584, 2570.737305, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2632.512, `position_y` = 2570.073, `position_z` = 371.979 WHERE `guid` = 152332;
SET @PATH14:= 152332 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH14;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH14, 1, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH14, 2, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH14, 3, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH14, 4, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH14, 5, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH14, 6, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH14, 7, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH14, 8, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH14, 9, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH14, 10, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH14, 11, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH14, 12, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH14, 13, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH14, 14, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH14, 15, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH14, 16, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH14, 17, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH14, 18, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH14, 19, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH14, 20, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH14, 21, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH14, 22, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH14, 23, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH14, 24, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH14, 25, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH14, 26, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH14, 27, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH14, 28, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH14, 29, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH14, 30, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH14, 31, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH14, 32, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH14, 33, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH14, 34, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH14, 35, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH14, 36, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH14, 37, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH14, 38, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH14, 39, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH14, 40, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH14, 41, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH14, 42, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH14, 43, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH14, 44, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH14, 45, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH14, 46, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH14, 47, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH14, 48, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH14, 49, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH14, 50, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH14, 51, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH14, 52, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH14, 53, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH14, 54, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH14, 55, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH14, 56, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH14, 57, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH14, 58, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH14, 59, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH14, 60, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH14, 61, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH14, 62, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH14, 63, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH14, 64, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH14, 65, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH14, 66, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH14, 67, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH14, 68, 2632.512939, 2570.073486, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2633.337, `position_y` = 2525.953, `position_z` = 371.979 WHERE `guid` = 152326;
SET @PATH15:= 152326 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH15;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH15, 1, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH15, 2, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH15, 3, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH15, 4, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH15, 5, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH15, 6, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH15, 7, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH15, 8, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH15, 9, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH15, 10, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH15, 11, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH15, 12, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH15, 13, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH15, 14, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH15, 15, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH15, 16, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH15, 17, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH15, 18, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH15, 19, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH15, 20, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH15, 21, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH15, 22, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH15, 23, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH15, 24, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH15, 25, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH15, 26, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH15, 27, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH15, 28, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH15, 29, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH15, 30, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH15, 31, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH15, 32, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH15, 33, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH15, 34, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH15, 35, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH15, 36, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH15, 37, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH15, 38, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH15, 39, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH15, 40, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH15, 41, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH15, 42, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH15, 43, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH15, 44, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH15, 45, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH15, 46, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH15, 47, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH15, 48, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH15, 49, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH15, 50, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH15, 51, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH15, 52, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH15, 53, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH15, 54, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH15, 55, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH15, 56, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH15, 57, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH15, 58, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH15, 59, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH15, 60, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH15, 61, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH15, 62, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH15, 63, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH15, 64, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH15, 65, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH15, 66, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH15, 67, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH15, 68, 2633.337646, 2525.953857, 371.979401, 1); -- end


UPDATE `creature` SET `position_x` = 2664.791, `position_y` = 2490.151, `position_z` = 371.979 WHERE `guid` = 152331;
SET @PATH16:= 152331 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH16;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH16, 1, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH16, 2, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH16, 3, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH16, 4, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH16, 5, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH16, 6, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH16, 7, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH16, 8, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH16, 9, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH16, 10, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH16, 11, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH16, 12, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH16, 13, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH16, 14, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH16, 15, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH16, 16, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH16, 17, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH16, 18, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH16, 19, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH16, 20, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH16, 21, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH16, 22, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH16, 23, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH16, 24, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH16, 25, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH16, 26, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH16, 27, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH16, 28, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH16, 29, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH16, 30, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH16, 31, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH16, 32, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH16, 33, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH16, 34, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH16, 35, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH16, 36, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH16, 37, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH16, 38, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH16, 39, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH16, 40, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH16, 41, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH16, 42, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH16, 43, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH16, 44, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH16, 45, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH16, 46, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH16, 47, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH16, 48, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH16, 49, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH16, 50, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH16, 51, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH16, 52, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH16, 53, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH16, 54, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH16, 55, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH16, 56, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH16, 57, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH16, 58, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH16, 59, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH16, 60, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH16, 61, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH16, 62, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH16, 63, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH16, 64, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH16, 65, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH16, 66, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH16, 67, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH16, 68, 2664.791992, 2490.151367, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2696.059, `position_y` = 2462.327, `position_z` = 371.979 WHERE `guid` = 152327;
SET @PATH17:= 152327 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH17;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH17, 1, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH17, 2, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH17, 3, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH17, 4, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH17, 5, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH17, 6, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH17, 7, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH17, 8, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH17, 9, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH17, 10, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH17, 11, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH17, 12, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH17, 13, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH17, 14, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH17, 15, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH17, 16, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH17, 17, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH17, 18, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH17, 19, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH17, 20, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH17, 21, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH17, 22, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH17, 23, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH17, 24, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH17, 25, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH17, 26, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH17, 27, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH17, 28, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH17, 29, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH17, 30, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH17, 31, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH17, 32, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH17, 33, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH17, 34, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH17, 35, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH17, 36, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH17, 37, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH17, 38, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH17, 39, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH17, 40, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH17, 41, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH17, 42, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH17, 43, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH17, 44, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH17, 45, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH17, 46, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH17, 47, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH17, 48, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH17, 49, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH17, 50, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH17, 51, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH17, 52, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH17, 53, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH17, 54, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH17, 55, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH17, 56, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH17, 57, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH17, 58, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH17, 59, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH17, 60, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH17, 61, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH17, 62, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH17, 63, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH17, 64, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH17, 65, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH17, 66, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH17, 67, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH17, 68, 2696.059326, 2462.327393, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2736.943, `position_y` = 2459.809, `position_z` = 371.979 WHERE `guid` = 152330;
SET @PATH18:= 152330 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH18;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH18, 1, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH18, 2, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH18, 3, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH18, 4, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH18, 5, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH18, 6, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH18, 7, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH18, 8, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH18, 9, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH18, 10, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH18, 11, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH18, 12, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH18, 13, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH18, 14, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH18, 15, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH18, 16, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH18, 17, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH18, 18, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH18, 19, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH18, 20, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH18, 21, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH18, 22, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH18, 23, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH18, 24, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH18, 25, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH18, 26, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH18, 27, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH18, 28, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH18, 29, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH18, 30, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH18, 31, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH18, 32, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH18, 33, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH18, 34, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH18, 35, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH18, 36, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH18, 37, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH18, 38, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH18, 39, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH18, 40, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH18, 41, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH18, 42, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH18, 43, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH18, 44, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH18, 45, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH18, 46, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH18, 47, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH18, 48, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH18, 49, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH18, 50, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH18, 51, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH18, 52, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH18, 53, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH18, 54, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH18, 55, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH18, 56, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH18, 57, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH18, 58, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH18, 59, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH18, 60, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH18, 61, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH18, 62, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH18, 63, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH18, 64, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH18, 65, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH18, 66, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH18, 67, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH18, 68, 2736.943359, 2459.809326, 371.979401, 1); -- end


UPDATE `creature` SET `position_x` = 2786.069, `position_y` = 2461.972, `position_z` = 371.979 WHERE `guid` = 152328;
SET @PATH19:= 152328 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH19;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH19, 1, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH19, 2, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH19, 3, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH19, 4, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH19, 5, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH19, 6, 2819.430908, 2492.777100, 371.979401, 1),
(@PATH19, 7, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH19, 8, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH19, 9, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH19, 10, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH19, 11, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH19, 12, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH19, 13, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH19, 14, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH19, 15, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH19, 16, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH19, 17, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH19, 18, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH19, 19, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH19, 20, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH19, 21, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH19, 22, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH19, 23, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH19, 24, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH19, 25, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH19, 26, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH19, 27, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH19, 28, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH19, 29, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH19, 30, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH19, 31, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH19, 32, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH19, 33, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH19, 34, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH19, 35, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH19, 36, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH19, 37, 2819.261963, 2647.094727, 371.979401, 1),
(@PATH19, 38, 2824.805420, 2638.859131, 371.979279, 1),
(@PATH19, 39, 2830.047852, 2642.635986, 371.979279, 1),
(@PATH19, 40, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH19, 41, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH19, 42, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH19, 43, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH19, 44, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH19, 45, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH19, 46, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH19, 47, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH19, 48, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH19, 49, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH19, 50, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH19, 51, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH19, 52, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH19, 53, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH19, 54, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH19, 55, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH19, 56, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH19, 57, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH19, 58, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH19, 59, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH19, 60, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH19, 61, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH19, 62, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH19, 63, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH19, 64, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH19, 65, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH19, 66, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH19, 67, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH19, 68, 2786.069824, 2461.972168, 371.979401, 1); -- end

UPDATE `creature` SET `position_x` = 2819.430, `position_y` = 2492.777, `position_z` = 371.979 WHERE `guid` = 152329;
SET @PATH20:= 152329 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @PATH20;
INSERT INTO waypoint_data (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@PATH20, 1, 2824.456055, 2499.575195, 371.979401, 1),
(@PATH20, 2, 2830.443359, 2495.646973, 371.979401, 1),
(@PATH20, 3, 2825.116699, 2488.251709, 371.979401, 1),
(@PATH20, 4, 2816.045654, 2480.737061, 371.979401, 1),
(@PATH20, 5, 2801.901611, 2471.089844, 371.979401, 1),
(@PATH20, 6, 2786.069824, 2461.972168, 371.979401, 1),
(@PATH20, 7, 2769.232910, 2457.481689, 371.979401, 1),
(@PATH20, 8, 2751.812256, 2454.458008, 371.979401, 1),
(@PATH20, 9, 2737.169922, 2453.573730, 371.979401, 1),
(@PATH20, 10, 2719.959229, 2456.308350, 371.979401, 1),
(@PATH20, 11, 2696.059326, 2462.327393, 371.979401, 1),
(@PATH20, 12, 2685.987061, 2467.614990, 371.979401, 1),
(@PATH20, 13, 2674.336670, 2475.428467, 371.979401, 1),
(@PATH20, 14, 2660.173340, 2486.269775, 371.979401, 1),
(@PATH20, 15, 2650.387939, 2497.161621, 371.979401, 1),
(@PATH20, 16, 2639.180908, 2513.970459, 371.979401, 1),
(@PATH20, 17, 2633.337646, 2525.953857, 371.979401, 1),
(@PATH20, 18, 2628.113037, 2548.929199, 371.979401, 1),
(@PATH20, 19, 2625.548584, 2570.737305, 371.979401, 1),
(@PATH20, 20, 2628.306396, 2591.702637, 371.979401, 1),
(@PATH20, 21, 2632.582764, 2609.958740, 371.979401, 1),
(@PATH20, 22, 2639.201172, 2625.132324, 371.979401, 1),
(@PATH20, 23, 2648.320557, 2638.936768, 371.979401, 1),
(@PATH20, 24, 2661.020264, 2653.529297, 371.979401, 1),
(@PATH20, 25, 2678.046631, 2665.775391, 371.979401, 1),
(@PATH20, 26, 2696.759521, 2676.764404, 371.979401, 1),
(@PATH20, 27, 2715.479492, 2681.816406, 371.979401, 1),
(@PATH20, 28, 2729.585693, 2684.134766, 371.979401, 1),
(@PATH20, 29, 2746.470459, 2685.045654, 371.979401, 1),
(@PATH20, 30, 2765.565918, 2682.073242, 371.979401, 1),
(@PATH20, 31, 2786.713135, 2676.620117, 371.979401, 1),
(@PATH20, 32, 2797.291016, 2670.866699, 371.979401, 1),
(@PATH20, 33, 2810.964355, 2661.586426, 371.979401, 1),
(@PATH20, 34, 2823.914307, 2651.755371, 371.979401, 1),
(@PATH20, 35, 2829.996338, 2642.607422, 371.979431, 1),
(@PATH20, 36, 2824.764648, 2638.736816, 371.979431, 1),
(@PATH20, 37, 2819.395752, 2647.018555, 371.979431, 1),
(@PATH20, 38, 2808.215332, 2656.130127, 371.979401, 1),
(@PATH20, 39, 2794.131592, 2665.513428, 371.979401, 1),
(@PATH20, 40, 2784.029297, 2670.957275, 371.979401, 1),
(@PATH20, 41, 2763.649414, 2675.890625, 371.979401, 1),
(@PATH20, 42, 2745.600586, 2679.047607, 371.979401, 1),
(@PATH20, 43, 2729.822754, 2677.810303, 371.979401, 1),
(@PATH20, 44, 2716.575928, 2675.310303, 371.979401, 1),
(@PATH20, 45, 2699.423340, 2670.932617, 371.979401, 1),
(@PATH20, 46, 2681.684326, 2660.331787, 371.979401, 1),
(@PATH20, 47, 2664.108887, 2647.853760, 371.979401, 1),
(@PATH20, 48, 2653.782471, 2635.072998, 371.979401, 1),
(@PATH20, 49, 2644.909912, 2621.341309, 371.979401, 1),
(@PATH20, 50, 2638.812744, 2608.165283, 371.979401, 1),
(@PATH20, 51, 2634.720215, 2590.382080, 371.979401, 1),
(@PATH20, 52, 2632.512939, 2570.073486, 371.979401, 1),
(@PATH20, 53, 2634.399414, 2549.973389, 371.979401, 1),
(@PATH20, 54, 2639.209961, 2528.639893, 371.979401, 1),
(@PATH20, 55, 2644.946777, 2517.133789, 371.979401, 1),
(@PATH20, 56, 2655.515869, 2500.761963, 371.979401, 1),
(@PATH20, 57, 2664.791992, 2490.151367, 371.979401, 1),
(@PATH20, 58, 2677.747314, 2480.133789, 371.979401, 1),
(@PATH20, 59, 2689.421143, 2472.844727, 371.979401, 1),
(@PATH20, 60, 2699.613770, 2467.697266, 371.979401, 1),
(@PATH20, 61, 2721.503418, 2462.295654, 371.979401, 1),
(@PATH20, 62, 2736.943359, 2459.809326, 371.979401, 1),
(@PATH20, 63, 2751.850342, 2460.841064, 371.979401, 1),
(@PATH20, 64, 2768.876465, 2463.794434, 371.979401, 1),
(@PATH20, 65, 2783.744873, 2467.658936, 371.979401, 1),
(@PATH20, 66, 2798.720215, 2476.635010, 371.979401, 1),
(@PATH20, 67, 2812.800781, 2486.838623, 371.979401, 1),
(@PATH20, 68, 2819.430908, 2492.777100, 371.979401, 1); -- end

DELETE FROM `creature_addon` WHERE `guid` IN
(152322,
152335,
152336,
152323,
152321,
152334,
152337,
152324,
152320,
152333,
152338,
152325,
152319,
152332,
152326,
152331,
152327,
152330,
152328,
152329);
INSERT INTO `creature_addon` (`guid`, `path_id`, `bytes2`) VALUES
(152322, 152322 * 10, 1),
(152335, 152335 * 10, 1),
(152336, 152336 * 10, 1),
(152323, 152323 * 10, 1),
(152321, 152321 * 10, 1),
(152334, 152334 * 10, 1),
(152337, 152337 * 10, 1),
(152324, 152324 * 10, 1),
(152320, 152320 * 10, 1),
(152333, 152333 * 10, 1),
(152338, 152338 * 10, 1),
(152325, 152325 * 10, 1),
(152319, 152319 * 10, 1),
(152332, 152332 * 10, 1),
(152326, 152326 * 10, 1),
(152331, 152331 * 10, 1),
(152327, 152327 * 10, 1),
(152330, 152330 * 10, 1),
(152328, 152328 * 10, 1),
(152329, 152329 * 10, 1);

UPDATE `creature_template` SET `HoverHeight` = 4 WHERE `entry` IN (33052, 33116);
DELETE FROM `disables` WHERE sourceType = 4 AND entry = 10279;

DELETE FROM `achievement_criteria_data` WHERE `criteria_id` = 10279;
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES 
(10279, 11, 0, 0, 'achievement_yogg_saron_alone_in_the_darkness'),
(10279, 12, 1, 0, '');


UPDATE `creature_template` SET `type_flags` = `type_flags` | 1048576 WHERE `entry` = 34362;
