-- Herald of War

/* Orgrimmar, Undercity, Durotar, and Tirisfal Glades, Warsong Hold for Horde */
DELETE FROM `spell_area` WHERE `spell` IN (59062,60943) AND `area` IN (1637,1497,14,85,4129);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(59062, 1637, 12500, 13267, 0, 690, 2, 1, 64, 11),
(59062, 1497, 12500, 13267, 0, 690, 2, 1, 64, 11),
(59062, 14, 12500, 13267, 0, 690, 2, 1, 64, 11),
(59062, 85, 12500, 13267, 0, 690, 2, 1, 64, 11),
(60943, 4129, 13257, 13257, 0, 690, 2, 1, 2, 2);

/* Spawns */
SET @JAINA := 31418;
SET @THRALL := 31412;
SET @SYLVANAS := 31419;
SET @GUARD := 31417;
SET @PORTAL_STORMWIND := 31640;

SET @FORSAKEN_REFUGEE_1 := 31437;
SET @FORSAKEN_REFUGEE_2 := 31467;

SET @KAJA := 31423;	
SET @OLVIA := 31425;
SET @FELIKA := 31427;
SET @SANA := 31429;
SET @THATHUNG := 31430;
SET @RUNTHAK := 31431;
SET @GRYSHKA := 31433;

SET @PORTAL_ORGRIMMAR := 193206;

SET @TENT_1 := 193217;
SET @TENT_2 := 193218;
SET @TENT_3 := 193219;

SET @CGUID := 302171;
SET @OGUID := 218967;

DELETE FROM `gameobject` WHERE `id` IN (@PORTAL_ORGRIMMAR,@TENT_1,@TENT_2,@TENT_3);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,@PORTAL_ORGRIMMAR,571,1,1,2838.510742,6181.923340,84.682877,4.68743,0,0,0.715875,-0.698228,120,100,1),

(@OGUID+1,@TENT_1,1,1,192,1427.4,-4355.75,25.0687,-1.41372,0,0,0,1,300,255,1),
(@OGUID+2,@TENT_1,1,1,192,1428.25,-4422.29,25.1243,-2.9845,0,0,0,1,300,255,1),
(@OGUID+3,@TENT_1,1,1,192,1327.95,-4357.13,27.4334,-1.39626,0,0,0,1,300,255,1),
(@OGUID+4,@TENT_2,1,1,192,1438.4,-4363.5,25.8465,-1.46608,0,0,0,1,300,255,1),
(@OGUID+5,@TENT_2,1,1,192,1374.88,-4354.89,26.2083,2.60053,0,0,0,1,300,255,1),
(@OGUID+6,@TENT_2,1,1,192,1438.47,-4431.58,25.2354,0.034906,0,0,0,1,300,255,1),
(@OGUID+7,@TENT_3,1,1,192,1589.77,-4423.56,8.23726,1.93731,0,0,0,1,300,255,1),
(@OGUID+8,@TENT_3,1,1,192,1371.21,-4416.96,29.6913,3.14159,0,0,0,1,300,255,1),
(@OGUID+9,@TENT_3,1,1,192,1370.57,-4405.97,29.6971,3.05433,0,0,0,1,300,255,1);

UPDATE `gameobject_template` SET `AiName`='', `ScriptName`='go_battle_for_undercity_portals' WHERE `entry`=@PORTAL_ORGRIMMAR;

-- Portal Spells
DELETE FROM `spell_scripts` WHERE `id`=59064;
INSERT INTO `spell_scripts` VALUES
(59064,0,0,15,58419,0,0,0,0,0,0);

DELETE FROM `spell_target_position` WHERE `id`=58419;
INSERT INTO `spell_target_position` VALUES
(58419,0,1,1331.515,-4377.525,26.21,0.152);

-- Spawns
DELETE FROM `creature` WHERE `id` IN (@THRALL,@JAINA,@SYLVANAS);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`,`position_x`, `position_y`, `position_z`, `orientation`) VALUES
(@CGUID, @THRALL, 1, 1, 64, 1920.2, -4126.75, 43.125, 4.8185),
(@CGUID+1, @SYLVANAS, 1, 1, 64, 1920, -4129.52, 43.1409, 1.571),
(@CGUID+2, @JAINA, 1, 1, 64, 1921.699951, -4147.27, 40.625, 1.571);

DELETE FROM `creature` WHERE `id` IN (@GUARD,@FORSAKEN_REFUGEE_1,@FORSAKEN_REFUGEE_2,@KAJA,@OLVIA,@FELIKA,@SANA,@THATHUNG,@RUNTHAK,@GRYSHKA);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+3, @GUARD, 1, 1, 64, 0, 0, 1911.631, -4139.943, 40.625, 5.478109, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+4, @GUARD, 1, 1, 64, 0, 0, 1911.631, -4157.943, 40.625, 0.7853975, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+5, @GUARD, 1, 1, 64, 0, 0, 1930.631, -4157.943, 40.625, 2.3561925, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+6, @GUARD, 1, 1, 64, 0, 0, 1930.631, -4139.943, 40.625, 3.92699, 300, 0, 0, 25200, 0, 0, 0, 0, 0),

(@CGUID+7, @GUARD, 1, 1, 192, 0, 0, 1941.71, -4124.25, 43.543, 3.90954, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+8, @GUARD, 1, 1, 192, 0, 0, 1924.73, -4245.42, 41.9408, 6.24828, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+9, @GUARD, 1, 1, 192, 0, 0, 1927.04, -4123.48, 43.0489, 4.45059, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+10, @GUARD, 1, 1, 192, 0, 0, 1914.56, -4136.63, 40.4915, 4.69494, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+11, @GUARD, 1, 1, 192, 0, 0, 1931.52, -4244.78, 41.921, 2.98451, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+12, @GUARD, 1, 1, 192, 0, 0, 1944.36, -4146.45, 40.958, 3.26377, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+13, @GUARD, 1, 1, 192, 0, 0, 1919.36, -4176.05, 41.005, 0.05236, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+14, @GUARD, 1, 1, 192, 0, 0, 1910.21, -4169.48, 41.0084, 0.837758, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+15, @GUARD, 1, 1, 192, 0, 0, 1933.29, -4168.81, 41.0098, 2.37365, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+16, @GUARD, 1, 1, 192, 0, 0, 1944.79, -4168.14, 43.5445, 2.3911, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+17, @GUARD, 1, 1, 192, 0, 0, 1928.19, -4203.37, 42.0497, 4.69494, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+18, @GUARD, 1, 1, 192, 0, 0, 1926.54, -4135.56, 40.4858, 4.7822, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+19, @GUARD, 1, 1, 192, 0, 0, 1924.79, -4238.43, 42.0145, 5.20108, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+20, @GUARD, 1, 1, 192, 0, 0, 1898.44, -4128.35, 43.5265, 5.51524, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+21, @GUARD, 1, 1, 192, 0, 0, 1898.32, -4149.7, 40.9876, 0.10472, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+22, @GUARD, 1, 1, 192, 0, 0, 1951.96, -4145.71, 43.5485, 3.22886, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+23, @GUARD, 1, 1, 192, 0, 0, 1901.27, -4171.16, 43.5635, 0.994838, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+24, @GUARD, 1, 1, 192, 0, 0, 1912.25, -4124.2, 43.117, 4.97419, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+25, @GUARD, 1, 1, 192, 0, 0, 1930.46, -4238.26, 42.0164, 4.39823, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+26, @GUARD, 1, 1, 192, 0, 0, 1922.2, -4204.38, 42.0703, 4.92183, 300, 0, 0, 25200, 0, 0, 0, 0, 0),
(@CGUID+27, @GUARD, 1, 1, 192, 0, 0, 1927.48, -4175.91, 41.0052, 3.15905, 300, 0, 0, 25200, 0, 0, 0, 0, 0),

(@CGUID+28, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1430.77, -4422.73, 25.3187, 3.80482, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+29, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1501.08, -4399.95, 22.6577, 0.610865, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+30, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1346.63, -4348.61, 27.2941, 5.89921, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+31, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1511.79, -4433.06, 21.1091, 4.2586, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+32, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1438.44, -4432.79, 25.3187, 1.6057, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+33, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1492.76, -4396.73, 24.7758, 0.506145, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+34, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1439.46, -4430.56, 25.3187, 0.087266, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+35, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1510.11, -4399.52, 20.1228, 0.959931, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+36, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1370.87, -4415.52, 29.7207, 3.21141, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+37, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1341.92, -4340.45, 27.4999, 4.85202, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+38, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1437.46, -4430.24, 25.3187, 1.64061, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+39, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1373.46, -4354.62, 26.4516, 0.680678, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+40, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1429.84, -4355.29, 25.3187, 4.50295, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+41, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1422.9, -4403.13, 28.0279, 1.37881, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+42, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1418.51, -4354.17, 27.9913, 4.74729, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+43, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1444.13, -4431.9, 25.3187, 1.71042, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+44, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1429.54, -4420.9, 25.3187, 5.70723, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+45, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1507.59, -4433.21, 22.5193, 0.733038, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+46, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1434.89, -4359.25, 25.3187, 3.48839, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+47, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1509.96, -4429.22, 21.4358, 1.8326, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+48, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1588.52, -4423.32, 8.55745, 4.60385, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+49, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1293, -4425.1, 26.7719, 2.32129, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+50, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1438.97, -4368.84, 25.3187, 6.05629, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+51, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1421.35, -4385.14, 27.9797, 0.034907, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+52, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1506.25, -4390.73, 21.2549, 0.383972, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+53, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1590.13, -4427.63, 8.5698, 4.08407, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+54, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1501.9, -4437.72, 24.7493, 0.069813, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+55, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1329.38, -4358.21, 28.4718, 1.37259, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+56, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1341.65, -4420.3, 27.241, 2.15036, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+57, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1439.33, -4364.56, 25.3187, 0.20944, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+58, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1501.53, -4395.09, 22.5012, 0.139626, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+59, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1525.64, -4435.69, 16.5148, 0.872665, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+60, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1522.16, -4437.87, 18.1303, 0.523599, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+61, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1348.6, -4427.49, 27.5116, 4.18879, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+62, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1508.82, -4393.75, 20.5281, 4.20624, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+63, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1515.62, -4424.49, 19.6616, 3.64774, 300, 0, 0, 1395, 0, 0, 0, 0, 0),
(@CGUID+64, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1430.16, -4376.73, 25.2354, 4.83093, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+65, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1429.35, -4374.5, 25.2354, 4.82928, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+66, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1353.47, -4401.82, 29.0612, 5.72889, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+67, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1360.78, -4373.65, 26.1952, 0.305098, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+68, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1313.04, -4393.01, 26.2498, 1.65851, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+69, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1326.28, -4436.94, 26.3456, 0.590713, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+70, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1314.29, -4548.93, 22.5108, 1.77181, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+71, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1317.3, -4569.04, 23.2873, 1.75938, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+72, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1313.05, -4558.77, 22.4257, 1.78925, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+73, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1315.31, -4561.24, 22.8135, 1.76455, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+74, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1380.18, -4367.96, 26.0744, 6.03816, 300, 5, 0, 1395, 0, 1, 0, 0, 0),
(@CGUID+75, @FORSAKEN_REFUGEE_1, 1, 1, 192, 0, 0, 1377.94, -4368.01, 26.0744, 0.245054, 300, 5, 0, 1395, 0, 1, 0, 0, 0),

(@CGUID+76, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1513.18, -4439.38, 21.1171, 4.59022, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+77, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1427.52, -4357.11, 25.3187, 5.91667, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+78, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1507.22, -4401.21, 20.9239, 1.98968, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+79, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1434.66, -4426.87, 25.3187, 1.16687, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+80, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1342.5, -4416.78, 27.4217, 6.00393, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+81, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1421.8, -4387.9, 27.9717, 0.087266, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+82, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1326.16, -4358.72, 28.2629, 3.71755, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+83, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1348, -4422.53, 27.5683, 2.67035, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+84, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1338.15, -4424.22, 26.8887, 1.69297, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+85, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1406.44, -4378.1, 25.3187, 1.62316, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+86, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1289.4, -4421.72, 26.6863, 3.61283, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+87, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1451.82, -4410.37, 25.3187, 4.99164, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+88, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1428.1, -4425.13, 25.3187, 0.017453, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+89, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1503.74, -4385.62, 21.9836, 0.366519, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+90, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1349.98, -4347.57, 27.2651, 0.408181, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+91, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1290.51, -4427.42, 26.8743, 1.65806, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+92, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1591.92, -4421.75, 9.19134, 4.27606, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+93, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1327.41, -4355.25, 28.5793, 2.26893, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+94, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1348.2, -4342.35, 27.3154, 3.50811, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+95, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1370.66, -4405.43, 29.8003, 5.70723, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+96, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1442.68, -4382.87, 27.9692, 2.6529, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+97, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1514.34, -4393.1, 19.2682, 5.02655, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+98, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1372.42, -4417.69, 29.946, 4.7822, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+99, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1424.73, -4402.81, 27.8919, 1.51844, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+100, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1506.26, -4397.44, 21.1897, 4.49761, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+101, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1514.01, -4428.42, 20.2095, 0.091911, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+102, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1343.96, -4346.27, 27.32, 4.36332, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+103, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1449.22, -4431.79, 27.9594, 0.698132, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+104, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1446.99, -4432.07, 27.9606, 1.8326, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+105, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1286.08, -4424.82, 26.7458, 4.60767, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+106, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1425.41, -4355.51, 25.3187, 4.74729, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+107, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1374.79, -4356.54, 26.3583, 4.01426, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+108, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1438.46, -4362.51, 25.3187, 4.29351, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+109, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1337.31, -4418.02, 27.0777, 3.9619, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+110, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1445.43, -4401.04, 28.0069, 3.1765, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+111, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1370.44, -4407.64, 29.7393, 2.70993, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+112, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1561.95, -4431.2, 7.35178, 5.87336, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+113, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1498.22, -4401.02, 23.5843, 0.881843, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+114, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1511.44, -4414.09, 18.6863, 6.14799, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+115, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1450.26, -4420.44, 25.2354, 6.18302, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+116, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1433.52, -4400.56, 25.2354, 4.86987, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+117, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1432.46, -4389.99, 25.2354, 4.87346, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+118, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1315.09, -4454.26, 24.8666, 1.62166, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+119, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1314.06, -4473.25, 24.0767, 1.44838, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+120, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1313.39, -4473.52, 24.0781, 1.51996, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+121, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1312.37, -4543.88, 22.4689, 1.64263, 300, 5, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+122, @FORSAKEN_REFUGEE_2, 1, 1, 192, 0, 0, 1316.82, -4578.19, 23.3084, 1.94786, 300, 5, 0, 905, 0, 1, 0, 0, 0),

(@CGUID+123, @KAJA, 1, 1, 192, 0, 0, 1602.248047, -4401.540039, 9.562877, 0.690897, 300, 0, 0, 1003, 0, 0, 0, 0, 0),
(@CGUID+124, @OLVIA, 1, 1, 192, 0, 0, 1599.441772, -4398.734375, 8.556360, 0.690897, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+125, @FELIKA, 1, 1, 192, 0, 0, 1587.281372, -4404.345215, 5.904898, 0.690897, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+126, @SANA, 1, 1, 192, 0, 0, 1599.441772, -4398.734375, 8.556252, 0.690897, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+127, @THATHUNG, 1, 1, 192, 0, 0, 1599.441772, -4395.929199, 8.878401, 0.690897, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+128, @GRYSHKA, 1, 1, 192, 0, 0, 1597.570923, -4398.734375, 7.852654, 0.690897, 300, 0, 0, 905, 0, 0, 0, 0, 0),
(@CGUID+129, @RUNTHAK, 1, 1, 192, 0, 0, 1606.568726, -4390.496094, 10.212643, 3.710756, 300, 0, 0, 905, 0, 0, 0, 0, 0);

/* Update Phase masks in Orgrimmar */
UPDATE `creature` SET `phaseMask`=65 WHERE `id` IN (3296); -- Orgrimmar Guards

-- Update templates
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (@JAINA,@SYLVANAS,@GUARD);
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_thrall_pre_battle_undercity' WHERE `entry`=@THRALL;

UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `faction`=29, `unit_flags`=256 WHERE `entry`=@GUARD;

UPDATE `creature_template` SET `minlevel`=19, `maxlevel`=20 WHERE `entry` IN (@FORSAKEN_REFUGEE_1);
UPDATE `creature_template` SET `minlevel`=55, `maxlevel`=56 WHERE `entry` IN (@FORSAKEN_REFUGEE_2);

UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30, `faction`=35, `AiName`='' WHERE `entry` IN (@KAJA);
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30, `faction`=35 WHERE `entry` IN (@OLVIA,@FELIKA);
UPDATE `creature_template` SET `minlevel`=50, `maxlevel`=50, `faction`=35 WHERE `entry` IN (@SANA,@THATHUNG,@GRYSHKA);
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=35, `AiName`='', `ScriptName`='npc_runthak_pre_battle_undercity' WHERE `entry` IN (@RUNTHAK);

-- Areatrigger in Orgrimmar
DELETE FROM `areatrigger_scripts` WHERE `entry`=5279;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES 
(5279, 'AreaTrigger_at_orgrimmar');

-- /* EVENT */ --
-- Sai for Jaina
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@JAINA,@JAINA*100);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@JAINA, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on reset - set walk'),
(@JAINA, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on respawn - set visibility off'),
(@JAINA, 0, 2, 3, 38, 0, 100, 0, 0, 1, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on data 1 set - set visibility on'),
(@JAINA, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 55761, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on data 1 set - Cast spell Air Revenant Entrance'),
(@JAINA, 0, 4, 0, 38, 0, 100, 0, 0, 2, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1921, -4139.4, 40.6, 0, 'Jaina - on data 2 set - go to pos 1'),
(@JAINA, 0, 5, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, @JAINA*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on pos 1 - run script'),
(@JAINA, 0, 6, 0, 38, 0, 100, 0, 0, 3, 0, 0, 69, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1921.699951, -4147.27, 40.625, 0, 'Jaina - on data 3 set - go to pos 2'),
(@JAINA, 0, 7, 8, 34, 0, 100, 0, 0, 2, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @PORTAL_STORMWIND, 10, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on portal'),
(@JAINA, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @THRALL, 40, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on Thrall'),
(@JAINA, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @SYLVANAS, 40, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on Sylvanas'),
(@JAINA, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set visibility off'),

(@JAINA*100, 9, 0, 0, 1, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on run script - say 1'),
(@JAINA*100, 9, 1, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Jaina - on run script - say 3'),
(@JAINA*100, 9, 2, 0, 1, 0, 100, 0, 5000, 5000, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, @SYLVANAS, 30, 0, 0, 0, 0, 0, 'Jaina - on run script - set data 1 on Sylvanas');

-- Sai from Sylvanas
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SYLVANAS,@SYLVANAS*100);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@SYLVANAS, 0, 0, 2, 25, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on reset - set walk'),
(@SYLVANAS, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on reset - set kneel'),
(@SYLVANAS, 0, 2, 3, 38, 0, 100, 0, 0, 1, 0, 0, 91, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on data 1 set - stand up'),
(@SYLVANAS, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.57019, -4136.34131, 40.559574, 0, 'Sylvanas - on data 1 set - go to pos 1'),
(@SYLVANAS, 0, 4, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, @SYLVANAS*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on pos 1 - run script'),
(@SYLVANAS, 0, 5, 0, 38, 0, 100, 0, 0, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on data 2 set - evade'),

(@SYLVANAS*100, 9, 0, 0, 1, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on run script - say 1'),
(@SYLVANAS*100, 9, 1, 0, 1, 0, 100, 0, 12000, 12000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on run script - say 2'),
(@SYLVANAS*100, 9, 2, 0, 1, 0, 100, 0, 16000, 16000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 4'),
(@SYLVANAS*100, 9, 3, 0, 1, 0, 100, 0, 6000, 6000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 5'),
(@SYLVANAS*100, 9, 4, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 6'),
(@SYLVANAS*100, 9, 5, 0, 1, 0, 100, 0, 10000, 10000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 7'),
(@SYLVANAS*100, 9, 6, 0, 1, 0, 100, 0, 6000, 6000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, @JAINA, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 2'),
(@SYLVANAS*100, 9, 7, 0, 1, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @JAINA, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 3'),
(@SYLVANAS*100, 9, 8, 0, 1, 0, 100, 0, 14000, 14000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, @JAINA, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 4'),
(@SYLVANAS*100, 9, 9, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @JAINA, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 5'),
(@SYLVANAS*100, 9, 10, 0, 1, 0, 100, 0, 5000, 5000, 0, 0, 45, 0, 3, 0, 0, 0, 0, 19, @JAINA, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - set data 3 on Jaina');

-- Sai for guards
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-(@CGUID+3),-(@CGUID+4),-(@CGUID+5),-(@CGUID+6));
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(-(@CGUID+3), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1923.506, -4146.693, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+3), 0, 1, 0, 34, 0, 100, 0, 0, 1, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, @THRALL, 30, 0, 0, 0, 0, 0, 'Kor\'kron Elite - On pos 1 - set data 1 on Thrall'),
(-(@CGUID+4), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.756, -4151.193, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+5), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1923.506, -4151.193, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+6), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.756, -4146.693, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP');

-- Texts
DELETE FROM `creature_text` WHERE `entry` IN (@THRALL,@SYLVANAS,@JAINA,@KAJA,@OLVIA,@FELIKA,@SANA,@THATHUNG,@RUNTHAK,@GRYSHKA);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@THRALL, 0, 0, 'Kor\'kron, stand down!', 14, 0, 100, 5, 0, 16222, 'Thrall - WG_Thrall_HORIntro01'),
(@THRALL, 1, 0, 'Jaina...', 12, 0, 100, 0, 0, 16223, 'Thrall - WG_Thrall_HORIntro02'),
(@THRALL, 2, 0, 'Jaina, what happened at the Wrathgate. It was a betrayal from within...', 12, 0, 100, 378, 0, 16224, 'Thrall - WG_Thrall_HORIntro03'),
(@THRALL, 3, 0, 'The Horde has lost the Undercity.', 12, 0, 100, 1, 0, 16225, 'Thrall - WG_Thrall_HORIntro04'),
(@THRALL, 4, 0, 'We now prepare to lay siege to the city and bring in the perpetrators of the unforgivable crime to justice.', 12, 0, 100, 378, 0, 16226, 'Thrall - WG_Thrall_HORIntro05'),
(@THRALL, 5, 0, 'Know this, Jaina: War with the Alliance is not in our best interests. If we are forced into a conflict, the Lich King will destroy our divided forces in Northrend.', 12, 0, 100, 378, 0, 16227, 'Thrall - WG_Thrall_HORIntro06'),
(@THRALL, 6, 0, 'We will make this right, Jaina. Tell your king all that you have learned here.', 12, 0, 100, 378, 0, 16228, 'Thrall - WG_Thrall_HORIntro07'),
(@THRALL, 7, 0, 'Kor\'kron, prepare transport to the Undercity.', 12, 0, 100, 0, 0, 16229, 'Thrall - WG_Thrall_HORIntro08'),
(@SYLVANAS, 0, 0, 'Lady Proudmoore, the Warchief speaks the truth. This subterfuge was set in motion by Varimathras and Grand Apothecary Putress. It was not the Horde\'s doing.', 12, 0, 100, 5, 0, 16315, 'Sylvanas - WG_Sylvanas_HORIntro01'),
(@SYLVANAS, 1, 0, 'As the combined Horde and Alliance forces begain their assault upon the Wrathgate, an uprising broke out in the Undercity. Varimathras and hordes of his demonic bretheren attacked. Hundreds of my people were slain in the coup. I barely managed to escape with my life.', 12, 0, 100, 5, 0, 16316, 'Sylvanas - WG_Sylvanas_HORIntro02'),
(@JAINA, 0, 0, 'Thrall, what has happened? The King is preparing for war...', 12, 0, 100, 1, 0, 16129, 'Jaina - WG_Jaina_HORIntro01'),
(@JAINA, 1, 0, 'I will deliver this information to King Wrynn, Thrall, but...', 12, 0, 100, 378, 0, 16130, 'Jaina - WG_Jaina_HORIntro02'),
(@JAINA, 2, 0, 'Bolvar was like a brother to him. In the King\'s absence, Bolvar kept the Alliance united. He found strength for our people in our darkest hours. He watched over Anduin, raising him as his own.', 12, 0, 100, 378, 0, 16131, 'Jaina - WG_Jaina_HORIntro03'),
(@JAINA, 3, 0, ' I fear that the rage will consume him, Thrall. I remain hopeful that reason will prevail, but we must prepare for the worst... for war.', 12, 0, 100, 378, 0, 16132, 'Jaina - WG_Jaina_HORIntro04'),
(@JAINA, 4, 0, 'Farewell, Warchief. I pray that the next time we meet it will be as allies.', 12, 0, 100, 2, 0, 16133, 'Jaina - WG_Jaina_HORIntro05'),

(@KAJA, 0, 0, 'Why is Thrall allowing this to happen to our city?', 12, 0, 100, 22, 0, 0, 'Kaja'),
(@OLVIA, 0, 0, 'Where is the Warchief?', 12, 0, 100, 22, 0, 0, 'Olvia'),
(@OLVIA, 0, 1, 'What are all these Forsaken doing here?', 12, 0, 100, 22, 0, 0, 'Olvia'),
(@FELIKA, 0, 0, 'What is going on?', 12, 0, 100, 22, 0, 0, 'Felika'),
(@FELIKA, 0, 1, 'This is an outrage!', 12, 0, 100, 22, 0, 0, 'Felika'),
(@SANA, 0, 0, 'We demand answers!', 12, 0, 100, 22, 0, 0, 'Sana'),
(@THATHUNG, 0, 0, 'What is going on?', 12, 0, 100, 22, 0, 0, 'Auctioneer Thathung'),
(@GRYSHKA, 0, 0, 'When can we reopen our shops? I\'m losing gold here!', 12, 0, 100, 22, 0, 0, 'Innkeeper Gryshka'),
(@GRYSHKA, 0, 1, 'This is an outrage!', 12, 0, 100, 22, 0, 0, 'Innkeeper Gryshka'),
(@RUNTHAK, 0, 0, 'SILENCE!', 14, 0, 100, 22, 0, 0, 'Overlord Runthak'),
(@RUNTHAK, 1, 0, 'We are on the brink of all out war with the Alliance!', 12, 0, 100, 22, 0, 0, 'Overlord Runthak'),
(@RUNTHAK, 2, 0, 'Tragic events have unfolded in Northrend. The Warchief is doing all that he can to keep us safe.', 12, 0, 100, 22, 0, 0, 'Overlord Runthak'),
(@RUNTHAK, 3, 0, 'All services and shops are to remain closed until further notice! That is all!.', 12, 0, 100, 22, 0, 0, 'Overlord Runthak');
