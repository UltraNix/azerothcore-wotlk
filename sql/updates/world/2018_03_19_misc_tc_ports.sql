-- Somnus Rare NPC Movement 
UPDATE `creature` SET `position_x` = -10666, `position_y` = -3923, `position_z` = 18.438, `orientation` = 6.218313 WHERE `guid` = 42880;
SET @NPC := 42880;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`) VALUES
(@PATH,1,-10666,-3923,18.438),
(@PATH,2,-10674.5,-3909.81,17.3732),
(@PATH,3,-10703.7,-3916.17,17.3732),
(@PATH,4,-10770,-4007.98,17.9099),
(@PATH,5,-10722.1,-4038.75,17.6482),
(@PATH,6,-10654.9,-4061.03,17.3742),
(@PATH,7,-10591.6,-4027.09,17.3742),
(@PATH,8,-10568.6,-4002.12,17.3853),
(@PATH,9,-10575.8,-3978.89,17.4333),
(@PATH,10,-10624.2,-3924.85,17.5842);


-- DB/Creature: Anathemus - Movement
SET @NPC := 27567;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`) VALUES
(@PATH, 1, -7095.56, -2718.91, 241.823),
(@PATH, 2, -7067.39, -2756.06, 242.343),
(@PATH, 3, -7037.44, -2790.59, 241.668),
(@PATH, 4, -7018.55, -2835.34, 244.453),
(@PATH, 5, -6984.54, -2869.52, 243.404),
(@PATH, 6, -6938.39, -2890.16, 241.667),
(@PATH, 7, -6905.93, -2928.64, 245.614),
(@PATH, 8, -6854.77, -2984.54, 244.127),
(@PATH, 9, -6836.56, -3004.44, 242.001),
(@PATH, 10, -6807.97, -3077.38, 241.258),
(@PATH, 11, -6787.47, -3129.66, 240.549),
(@PATH, 12, -6764.01, -3175.88, 240.743),
(@PATH, 13, -6745.73, -3211.91, 240.743),
(@PATH, 14, -6708.56, -3249.22, 240.743),
(@PATH, 15, -6693.82, -3306.64, 240.985),
(@PATH, 16, -6720.17, -3363.87, 241.645),
(@PATH, 17, -6774.04, -3394.9, 241.667),
(@PATH, 18, -6846.93, -3401.71, 241.762),
(@PATH, 19, -6905.98, -3407.23, 243.235),
(@PATH, 20, -6961.35, -3397.87, 241.796),
(@PATH, 21, -6999.34, -3391.44, 241.667),
(@PATH, 22, -7039.67, -3397.01, 243.935),
(@PATH, 23, -7064.13, -3400.84, 245.275),
(@PATH, 24, -7110.78, -3375.07, 242.97),
(@PATH, 25, -7113.36, -3322.06, 242.365),
(@PATH, 26, -7098.28, -3284.59, 242.883),
(@PATH, 27, -7095.63, -3246.03, 242.983),
(@PATH, 28, -7085.7, -3202.78, 241.97),
(@PATH, 29, -7072.35, -3144.63, 241.67),
(@PATH, 30, -7061.88, -3098.99, 242.684),
(@PATH, 31, -7015.89, -3040.38, 242.25),
(@PATH, 32, -6970.5, -2981.02, 241.666),
(@PATH, 33, -6934.33, -2905.91, 241.816),
(@PATH, 34, -6913.11, -2861.83, 241.894),
(@PATH, 35, -6874.86, -2825.65, 241.667),
(@PATH, 36, -6859.87, -2776.27, 241.975),
(@PATH, 37, -6842.13, -2717.85, 241.729),
(@PATH, 38, -6846.45, -2667.72, 241.51),
(@PATH, 39, -6851.46, -2607.44, 240.745),
(@PATH, 40, -6852.08, -2566.73, 240.743),
(@PATH, 41, -6880.82, -2550.47, 240.743),
(@PATH, 42, -6920.74, -2512.13, 240.743),
(@PATH, 43, -6957.01, -2459.73, 240.743),
(@PATH, 44, -6968.86, -2436.17, 240.743),
(@PATH, 45, -6985.18, -2427.13, 242.407),
(@PATH, 46, -7032.28, -2403.95, 240.308),
(@PATH, 47, -7070.29, -2406.17, 243.718),
(@PATH, 48, -7132.2, -2394.94, 241.667),
(@PATH, 49, -7165.06, -2398.26, 240.663),
(@PATH, 50, -7188.31, -2426.48, 242.147),
(@PATH, 51, -7194.06, -2475.31, 245.94),
(@PATH, 52, -7197.13, -2523.31, 248.631),
(@PATH, 53, -7185.88, -2555.67, 245.846),
(@PATH, 54, -7191.35, -2594.02, 246.023),
(@PATH, 55, -7175.23, -2639.84, 244.411),
(@PATH, 56, -7164.76, -2655.17, 243.481),
(@PATH, 57, -7143.76, -2663.97, 241.977),
(@PATH, 58, -7120.74, -2667.13, 241.845);

-- Oronok Torn-heart SAI - Add 'Chain Lightning'
SET @ENTRY := 21183;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,2,0,0,0,100,0,6700,11200,18100,24900,11,16006,64,0,0,0,0,2,0,0,0,0,0,0,0,"Oronok Torn-heart - In Combat - Cast 'Chain Lightning'");

-- RFK fixes and improvements
-- Update NPC For Proper Type and Add Waypoint Movement
UPDATE `creature` SET `id` = 4436, `SpawnDist` = 0, `MovementType` = 2 WHERE `guid` = 87296;
SET @NPC := 87296;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`, `delay`) VALUES
(@PATH,1,1984.9,1601.33,79.6094, 0),
(@PATH,2,1976.46,1601.48,80.0231,0),
(@PATH,3,1967.94,1601.07,80.4888,0),
(@PATH,4,1961.14,1599.4,81.1372, 0),
(@PATH,5,1955.46,1595.81,81.9168,0),
(@PATH,6,1951.26,1583.76,81.8884,0),
(@PATH,7,1955.19,1594.79,82.0734,0),
(@PATH,8,1963.58,1599.38,80.8979,0),
(@PATH,9,1968.28,1601.08,80.4596,0),
(@PATH,10,1986.78,1601.08,79.783,0);

-- Move NPC into Proper Position
UPDATE `creature` SET `position_x` = 2008.055786, `position_y` = 1569.062988, `position_z` = 81.737740, `orientation` = 2.060939 WHERE `guid` = 87292;

-- NPC NPC Into Position and Change to Correct Type
UPDATE `creature` SET `id` = 4530, `spawndist` = 0, `MovementType` = 0, `position_x` = 2000.325195, `position_y` = 1558.828735, `position_z` = 82.008972, `orientation` = 0.571824 WHERE `guid` = 87293;

-- Fix Hogger Movement (Random)
UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE  `guid`=80531;