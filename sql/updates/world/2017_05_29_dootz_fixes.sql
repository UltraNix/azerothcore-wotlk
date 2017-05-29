-- Bug: #936  Gameobject: The Holy Spring | Author: Shonsu - poprawienie dropu
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `entry` = 938;

-- Bug: #922  NPC: Gorzeeki Wildeyes | Author: Shonsu - poprawiono vendora
DELETE FROM `conditions` WHERE `SourceGroup` = 14437;
INSERT INTO `conditions` VALUES
(23, 14437, 18629, 0, 0, 15, 0, 256, 0, 0, 0, 0, 0, '', 'Show vendor item if player is a warlock'),
(23, 14437, 18663, 0, 0, 15, 0, 256, 0, 0, 0, 0, 0, '', 'Show vendor item if player is a warlock'),
(23, 14437, 18670, 0, 0, 15, 0, 256, 0, 0, 0, 0, 0, '', 'Show vendor item if player is a warlock'),
(23, 14437, 18802, 0, 0, 15, 0, 256, 0, 0, 0, 0, 0, '', 'Show vendor item if player is a warlock');

-- Bug: #921  NPC: Anathemus | Author: Shonsu - poprawienie frakcji
UPDATE `creature_template` SET `faction` = 778 WHERE `entry` = 2754;

-- Bug: #946  Gameobject: Statue of Queen Azshara | Author: Shonsu - poprawienie interakcji
UPDATE `gameobject_template` SET `data3` = 10000 WHERE `entry` = 181964;

-- Bug: #935  Quest: Crimson Crystal Clue | Author: Shonsu - poprawiono drop start itemu(Close Issue: #935)
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` = 29476;
DELETE FROM `conditions` WHERE `SourceEntry` = 29476;
INSERT INTO `conditions` VALUES
(1, 19188, 29476, 0, 0, 14, 0, 10134, 0, 0, 1, 0, 0, '', 'Drop Crimson Crystal Shard only if player has not completed Crimson Crystal Clue');

-- Bug: #956  NPC: Winterskorn Raider | Author: Shonsu - poprawiono zachowania npc(Close Issue: #956)
UPDATE `creature_template` SET `InhabitType` = 1 WHERE `entry` = 23665;

-- Bug: #957  Quest: Gruesome, But Necessary | Author: Shonsu - poprawiono zachowanie Quest itemu(Close Issue: #957)
DELETE FROM `conditions` WHERE `SourceEntry` = 43036 AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` VALUES
(13, 1, 43036, 0, 1, 36, 0, 0, 0, 0, 1, 0, 0, '', 'Amulet can target only dead Iskalder');
UPDATE `conditions` SET `ElseGroup` = 1 WHERE `SourceEntry` = 43036 AND `SourceTypeOrReferenceId` = 17;

-- Bug: #949  NPC: Thorim | Author: Shonsu - poprawienie pozycji NPC(Close Issue: #949)
UPDATE `creature` SET `position_z` = 1897.53 WHERE `guid` = 97128;

-- Bug: #950  NPC: Frost Giant Stormherald | Author: Shonsu - poprawienie frakcji NPC(Close Issue: #950)
UPDATE `creature_template` SET `faction` = 2107 WHERE `entry` = 30121;

-- Bug: #162 NPC: Dzieci w Goldshire | Author: Rushor - dodanie eventu(Close Issue: #162) 
DELETE FROM `game_event` WHERE  `eventEntry`=73;
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES
(73, '2010-07-04 07:00:00', '2020-07-04 07:00:00', 660, 780, 0, 'Children of Goldshire', 0);

DELETE FROM `game_event_creature` WHERE `guid` IN (79638, 79639, 79640, 79641, 79642, 79643);
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(73, 79638),
(73, 79639),
(73, 79640),
(73, 79641),
(73, 79642),
(73, 79643);

UPDATE `creature` SET `position_x`=-9350.654, `position_y`=-90.29861, `position_z`=65.15973, `orientation`=0 WHERE `guid`=79642;
UPDATE `creature` SET `position_x`=-9354.359, `position_y`=-91.97743, `position_z`=64.87327, `orientation`=0 WHERE `guid`=79643;
UPDATE `creature` SET `position_x`=-9356.938, `position_y`=-87.10703, `position_z`=64.92709, `orientation`=0 WHERE `guid`=79641;
UPDATE `creature` SET `position_x`=-9355.375, `position_y`=-87.10703, `position_z`=65.69692, `orientation`=0 WHERE `guid`=79638;
UPDATE `creature` SET `position_x`=-9353.279, `position_y`=-89.96702, `position_z`=65.22049, `orientation`=0 WHERE `guid`=79640;
UPDATE `creature` SET `position_x`=-9352.859, `position_y`=-93.96007, `position_z`=64.4566, `orientation`=0 WHERE `guid`=79639;

DELETE FROM `creature_formations` WHERE `leaderGUID`=79638;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(79638, 79638, 0, 0, 0), -- Cameron
(79638, 79639, 3, 230, 0), -- John
(79638, 79640, 3, 180, 0), -- Dana
(79638, 79641, 3, 130, 0), -- Jose
(79638, 79642, 3, 310, 0), -- Lisa
(79638, 79643, 3, 50, 0); -- Aaron

SET @ENTRY := 80500;
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(@ENTRY, 1  ,-9351.973,-92.05708,64.95626, 'Cameron'), -- 07:00:21
(@ENTRY, 2  ,-9354.806,-87.93577,65.57292, 'Cameron'), -- 07:00:21
(@ENTRY, 3  ,-9357.639,-83.81445,66.18958, 'Cameron'), -- 07:00:21
(@ENTRY, 4  ,-9360.979,-78.97743,65.9347, 'Cameron'), -- 07:00:21
(@ENTRY, 5  ,-9359.736,-75.17188,65.31458, 'Cameron'), -- 07:00:21
(@ENTRY, 6  ,-9358.805,-72.31836,64.56458, 'Cameron'), -- 07:00:21
(@ENTRY, 7  ,-9357.252,-67.5625,65.31458, 'Cameron'), -- 07:00:21
(@ENTRY, 8  ,-9357.252,-67.5625,65.31458, 'Cameron'), -- 07:00:21
(@ENTRY, 9  ,-9356.818,-59.81693,66.47333, 'Cameron'), -- 07:00:23
(@ENTRY, 10 ,-9359.703,-40.74677,64.90179, 'Cameron'), -- 07:00:24
(@ENTRY, 11 ,-9366.912,-26.63774,63.58042, 'Cameron'), -- 07:00:27
(@ENTRY, 12 ,-9376.815,-16.4907,62.47466, 'Cameron'), -- 07:00:29
(@ENTRY, 13 ,-9390.682,0.2398973,60.84456, 'Cameron'), -- 07:00:30
(@ENTRY, 14 ,-9402.53,14.60529,59.79248, 'Cameron'), -- 07:00:34
(@ENTRY, 15 ,-9419.141,34.55973,57.84264, 'Cameron'), -- 07:00:35
(@ENTRY, 16 ,-9426.896,43.84751,57.06255, 'Cameron'), -- 07:00:40
(@ENTRY, 17 ,-9433.867,53.78213,56.78226, 'Cameron'), -- 07:00:41
(@ENTRY, 18 ,-9438.548,61.02147,56.39376, 'Cameron'), -- 07:00:42
(@ENTRY, 19 ,-9436.482,68.04466,56.42494, 'Cameron'), -- 07:00:44
(@ENTRY, 20 ,-9415.27,87.07191,57.30513, 'Cameron'), -- 07:00:45
(@ENTRY, 21 ,-9396.235,98.29691,59.15154, 'Cameron'), -- 07:00:47
(@ENTRY, 22 ,-9375.271,106.7702,60.70432, 'Cameron'), -- 07:00:51
(@ENTRY, 23 ,-9364.256,110.7547,61.50436, 'Cameron'), -- 07:00:53
(@ENTRY, 24 ,-9344.307,120.2394,63.43427, 'Cameron'), -- 07:00:55
(@ENTRY, 25 ,-9332.738,126.8489,63.9777, 'Cameron'), -- 07:00:57
(@ENTRY, 26 ,-9308.697,137.7139,65.57498, 'Cameron'), -- 07:00:59
(@ENTRY, 27 ,-9292.605,144.2936,66.53963, 'Cameron'), -- 07:01:03
(@ENTRY, 28 ,-9271.355,152.9366,67.37766, 'Cameron'), -- 07:01:04
(@ENTRY, 29 ,-9258.908,158.3268,67.75345, 'Cameron'), -- 07:01:07
(@ENTRY, 30 ,-9258.107,158.9872,67.80977, 'Cameron'), -- 07:01:08
(@ENTRY, 31 ,-9245.959,170.1512,68.25052, 'Cameron'), -- 07:01:10
(@ENTRY, 32 ,-9219.314,201.358,69.06726, 'Cameron'), -- 07:01:13
(@ENTRY, 33 ,-9208.215,212.5414,70.81392, 'Cameron'), -- 07:01:17
(@ENTRY, 34 ,-9198.92,222.5978,71.63802, 'Cameron'), -- 07:01:18
(@ENTRY, 35 , -9194.827, 227.36, 71.91199, 'Cameron'), -- 07:01:20
(@ENTRY, 36 ,-9187.375,241.8835,72.91473, 'Cameron'), -- 07:01:21
(@ENTRY, 37 ,-9184.045,254.7417,73.77821, 'Cameron'), -- 07:01:23
(@ENTRY, 38 ,-9182.289,274.1739,75.36765, 'Cameron'), -- 07:01:25
(@ENTRY, 39 ,-9181.092,289.6617,77.20319, 'Cameron'), -- 07:01:26
(@ENTRY, 40 ,-9180.633,300.7958,78.49542, 'Cameron'), -- 07:01:29
(@ENTRY, 41 ,-9178.008,326.7234,81.67275, 'Cameron'), -- 07:01:31
(@ENTRY, 42 ,-9174.055,336.8582,84.08626, 'Cameron'), -- 07:01:34
(@ENTRY, 43 ,-9163.633,351.4775,87.70863, 'Cameron'), -- 07:01:35
(@ENTRY, 44 ,-9153.682,362.516,90.23949, 'Cameron'), -- 07:01:37
(@ENTRY, 45 ,-9148.218,368.3586,90.66177, 'Cameron'), -- 07:01:40
(@ENTRY, 46 ,-9125.46,390.1248,91.81776, 'Cameron'), -- 07:01:43
(@ENTRY, 47 ,-9115.926,397.5776,92.71513, 'Cameron'), -- 07:01:45
(@ENTRY, 48 ,-9095.435,413.1418,92.21481, 'Cameron'), -- 07:01:46
(@ENTRY, 49 ,-9088.044,418.7169,92.44129, 'Cameron'), -- 07:01:49
(@ENTRY, 50 ,-9058.086,439.64,93.14257, 'Cameron'), -- 07:01:52
(@ENTRY, 51 ,-9045.07,450.092,93.28775, 'Cameron'), -- 07:01:54
(@ENTRY, 52 ,-9040.674,453.6961,93.05584, 'Cameron'),
(@ENTRY, 53 ,-9057.086,442.696,93.05582, 'Cameron'), -- 07:13:02
(@ENTRY, 54 ,-9074.805,431.4119,93.05582, 'Cameron'), -- 07:13:03
(@ENTRY, 55 ,-9077.455,426.727,92.54478, 'Cameron'), -- 07:13:05
(@ENTRY, 56 ,-9130.008,384.1526,91.08342, 'Cameron'), -- 07:13:11
(@ENTRY, 57 ,-9138.167,378.1005,90.83872, 'Cameron'), -- 07:13:14
(@ENTRY, 58 ,-9170.719,340.1506,85.00079, 'Cameron'), -- 07:13:17
(@ENTRY, 59 ,-9177.553,324.4485,81.63397, 'Cameron'), -- 07:13:22
(@ENTRY, 60 ,-9179.79,302.5313,78.90688, 'Cameron'), -- 07:13:24
(@ENTRY, 61 ,-9180.076,284.7124,76.62807, 'Cameron'), -- 07:13:26
(@ENTRY, 62 ,-9180.527,273.4619,75.51992, 'Cameron'), -- 07:13:29
(@ENTRY, 63 ,-9181.712,261.4136,74.55137, 'Cameron'), -- 07:13:30
(@ENTRY, 64 ,-9187.871,242.3035,72.95731, 'Cameron'), -- 07:13:32
(@ENTRY, 65 ,-9199.146,222.4604,71.7192, 'Cameron'), -- 07:13:35
(@ENTRY, 66 ,-9217.201,203.2024,69.32413, 'Cameron'), -- 07:13:37
(@ENTRY, 67 ,-9230.155,189.5526,68.19696, 'Cameron'), -- 07:13:41
(@ENTRY, 68 ,-9241.491,176.5851,67.95673, 'Cameron'), -- 07:13:45
(@ENTRY, 69 ,-9263.844,156.9561,67.57113, 'Cameron'), -- 07:13:46
(@ENTRY, 70 ,-9267.183,155.5535,67.38669, 'Cameron'), -- 07:13:48
(@ENTRY, 71 ,-9276.685,152.7653,67.1469, 'Cameron'), -- 07:13:50
(@ENTRY, 72 ,-9299.891,144.6541,66.28534, 'Cameron'), -- 07:13:52
(@ENTRY, 73 ,-9319.277,135.1606,65.03548, 'Cameron'), -- 07:13:53
(@ENTRY, 74 ,-9332.896,126.1193,63.87636, 'Cameron'), -- 07:13:57
(@ENTRY, 75 ,-9352.381,116.5327,62.6504, 'Cameron'), -- 07:13:58
(@ENTRY, 76 ,-9372.848,108.2433,60.93748, 'Cameron'), -- 07:14:02
(@ENTRY, 77 ,-9390.894,102.341,59.62895, 'Cameron'), -- 07:14:04
(@ENTRY, 78 ,-9395.941,100.5215,59.13963, 'Cameron'), -- 07:14:07
(@ENTRY, 79 ,-9409.482,92.83659,58.09391, 'Cameron'), -- 07:14:08
(@ENTRY, 80 ,-9417.838,86.17823,57.23439, 'Cameron'), -- 07:14:09
(@ENTRY, 81 ,-9433.703,74.28316,56.51966, 'Cameron'), -- 07:14:10
(@ENTRY, 82 ,-9435.221,73.19769,56.34148, 'Cameron'), -- 07:14:13
(@ENTRY, 83 ,-9448.541,67.65511,56.51829, 'Cameron'), -- 07:14:14
(@ENTRY, 84 ,-9460.035,63.37641,55.895, 'Cameron'),
(@ENTRY, 85 ,-9445.364,58.4987,55.97727, 'Cameron'), -- 07:31:27
(@ENTRY, 86 ,-9445.032,58.55785,56.2136, 'Cameron'), -- 07:31:28
(@ENTRY, 87 ,-9427.596,41.84236,57.21891, 'Cameron'), -- 07:31:30
(@ENTRY, 88 ,-9410.779,22.67539,58.65345, 'Cameron'), -- 07:31:32
(@ENTRY, 89 ,-9391.792,0.02795124,60.67725, 'Cameron'), -- 07:31:34
(@ENTRY, 90 ,-9377.568,-14.63209,62.37714, 'Cameron'), -- 07:31:38
(@ENTRY, 91 ,-9363.139,-29.04746,63.92186, 'Cameron'), -- 07:31:41
(@ENTRY, 92 ,-9348.428,-41.40288,65.24854, 'Cameron'), -- 07:31:43
(@ENTRY, 93 ,-9333.074,-51.61682,66.22433, 'Cameron'), -- 07:31:46
(@ENTRY, 94 ,-9324.543,-55.41918,66.51912, 'Cameron'), -- 07:31:49
(@ENTRY, 95 ,-9306.514,-57.01295,66.98401, 'Cameron'), -- 07:31:51
(@ENTRY, 96 ,-9288.65,-65.67791,67.9245, 'Cameron'), -- 07:31:53
(@ENTRY, 97 ,-9266.111,-81.1689,69.09925, 'Cameron'), -- 07:31:55
(@ENTRY, 98 ,-9246.279,-94.43002,70.69906, 'Cameron'), -- 07:31:57
(@ENTRY, 99 ,-9241.527,-97.61461,70.86122, 'Cameron'), -- 07:32:01
(@ENTRY, 100,-9228.587,-103.1802,71.24693, 'Cameron'), -- 07:32:02
(@ENTRY, 101,-9202.936,-110.5503,71.32005, 'Cameron'), -- 07:32:06
(@ENTRY, 102,-9189.19,-111.8865,71.32235, 'Cameron'), -- 07:32:07
(@ENTRY, 103,-9164.87,-117.8934,73.10243, 'Cameron'), -- 07:32:10
(@ENTRY, 104,-9164.276,-118.5964,73.10841, 'Cameron'), -- 07:32:11
(@ENTRY, 105,-9157.389,-130.045,74.83447, 'Cameron'), -- 07:32:12
(@ENTRY, 106,-9155.88,-137.6466,74.73592, 'Cameron');

SET @ENTRY := 80501;
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(@ENTRY, 1 ,-9158.411,-126.9952,74.33096, 'Cameron'), -- 07:38:14
(@ENTRY, 2 ,-9161.936,-122.2632,73.48005, 'Cameron'), -- 07:38:18
(@ENTRY, 3 ,-9171.188,-116.403,72.13133, 'Cameron'), -- 07:38:23
(@ENTRY, 4 ,-9175.792,-115.2302,71.66595, 'Cameron'), -- 07:38:26
(@ENTRY, 5 ,-9188.126,-113.6762,71.1235, 'Cameron'), -- 07:38:31
(@ENTRY, 6 ,-9198.314,-111.6536,71.19713, 'Cameron'), -- 07:38:36
(@ENTRY, 7 ,-9212.777,-108.1362,71.49892, 'Cameron'), -- 07:38:41
(@ENTRY, 8 ,-9221.962,-106.0956,71.29646, 'Cameron'), -- 07:38:46
(@ENTRY, 9 ,-9238.102,-98.25057,71.02353, 'Cameron'), -- 07:38:52
(@ENTRY, 10,-9255.748,-87.4807,70.21791, 'Cameron'), -- 07:38:55
(@ENTRY, 11,-9262.821,-82.41038,69.39944, 'Cameron'), -- 07:39:01
(@ENTRY, 12,-9267.083,-79.06253,68.88945, 'Cameron'), -- 07:39:06
(@ENTRY, 13,-9277.369,-71.58946,68.45795, 'Cameron'), -- 07:39:11
(@ENTRY, 14,-9294.043,-62.51098,67.73149, 'Cameron'), -- 07:39:15
(@ENTRY, 15,-9296.369,-61.36803,67.39666, 'Cameron'), -- 07:39:20
(@ENTRY, 16,-9306.391,-58.70887,67.12717, 'Cameron'), -- 07:39:23
(@ENTRY, 17,-9314.822,-57.41774,66.82509, 'Cameron'), -- 07:39:27
(@ENTRY, 18,-9336.649,-53.8809,66.1555, 'Cameron'), -- 07:39:31
(@ENTRY, 19,-9337.359,-53.52038,65.92425, 'Cameron'), -- 07:39:37
(@ENTRY, 20,-9350.479,-55.02436,66.34923, 'Cameron'), -- 07:39:40
(@ENTRY, 21,-9351.158,-55.39683,66.35679, 'Cameron'), -- 07:39:43
(@ENTRY, 22,-9359.373,-69.76035,64.45229, 'Cameron'), -- 07:39:44
(@ENTRY, 23,-9360.618,-71.72406,64.24545, 'Cameron'), -- 07:39:50
(@ENTRY, 24,-9366.256,-80.96321,64.52115, 'Cameron'), -- 07:39:54
(@ENTRY, 25,-9364.25,-85.4796,65.50365, 'Cameron'), -- 07:39:56
(@ENTRY, 26,-9354.806,-87.93577,65.47449, 'Cameron'); -- 07:40:01

-- Lisa waypoints
DELETE FROM `waypoints` WHERE `entry`=807;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(807, 1,-9154.618,-134.9246,75.17611, 'Lisa'), -- 07:32:15
(807, 2,-9155.719,-132.458,75.17039, 'Lisa'), -- 07:32:15
(807, 3,-9340.689,-89.09771,66.49249, 'Lisa'), -- 07:32:27
(807, 4,-9353.076,-86.58789,65.68958, 'Lisa'); -- 07:33:47 Random movement

-- Cameron SAI
SET @ENTRY := 805;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,512,0,0,0,0,53,1,@ENTRY*100+00,0,0,0,0,1,0,0,0,0,0,0,0,"Cameron - On Reset - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,512,51,@ENTRY*100+00,0,0,54,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cameron - On Waypoint 51 Reached - Pause Waypoint"),
(@ENTRY,0,2,0,40,0,100,512,83,@ENTRY*100+00,0,0,54,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cameron - On Waypoint 83 Reached - Pause Waypoint"),
(@ENTRY,0,4,0,40,0,100,512,105,@ENTRY*100+00,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Cameron - On Waypoint 105 Reached - Run Script"),
(@ENTRY,0,5,0,58,0,100,0,25,@ENTRY*100+01,0,0,69,26,0,0,0,0,0,8,0,0,0,-9354.81,-87.9358,65.4745,5.20108,"Cameron - On Waypoint Finished - Move To Position"),
(@ENTRY,0,6,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,807,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1"),
(@ENTRY,0,7,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,810,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1"),
(@ENTRY,0,8,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,811,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1"),
(@ENTRY,0,9,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,804,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1"),
(@ENTRY,0,10,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,804,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1"),
(@ENTRY,0,11,0,58,0,100,0,25,@ENTRY*100+01,0,0,45,1,1,0,0,0,0,9,806,0,10,0,0,0,0,"Cameron - On Waypoint Finished - Set Data 1 1");

-- Actionlist SAI
SET @ENTRY := 805;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,1,0,0,0,100,0,2000,2000,0,0,45,2,1,0,0,0,0,9,807,0,10,0,0,0,0,"On Script - Set Data 2 1"),
(@ENTRY,9,2,0,0,0,100,0,2000,2000,0,0,55,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Stop Waypoint"),
(@ENTRY,9,3,0,0,0,100,0,100000,100000,0,0,53,0,@ENTRY*100+01,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Start Waypoint");

-- Lisa SAI
SET @ENTRY := 807;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,69,5,0,0,0,0,0,8,0,0,0,-9350.654,-90.29861,65.16615,3.141593,"Lisa - On Data Set 1 1 - Move To Position"),
(@ENTRY,0,1,0,38,0,100,0,2,1,0,0,53,1,807,0,0,0,0,1,0,0,0,0,0,0,0,"Lisa - On Data Set 2 1 - Start Waypoint");

-- Aaron SAI
SET @ENTRY := 810;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,69,1,0,0,0,0,0,8,0,0,0,-9354.359,-91.97743,64.86536,1.117011,"Aaron - On Data Set 1 1 - Move To Position");

-- Jose SAI
SET @ENTRY := 811;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,69,1,0,0,0,0,0,8,0,0,0,-9356.938,-91.69791,64.93226,0.296706,"Jose - On Data Set 1 1 - Move To Position");

-- Dana SAI
SET @ENTRY := 804;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,69,1,0,0,0,0,0,8,0,0,0,-9353.279,-89.96702,65.20618,4.206244,"Dana - On Data Set 1 1 - Move To Position");

-- John SAI
SET @ENTRY := 806;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,69,1,0,0,0,0,0,8,0,0,0,-9352.859,-93.96007,64.3888,1.937315,"John - On Data Set 1 1 - Move To Position");

UPDATE `creature` SET `spawndist`=5, `MovementType`=1  WHERE `guid`=80321;
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `guid`=80317;

-- Bug: #959  Quest: A Warm Welcome | Author: Shonsu - poprawienie dropu Q Itemu(Close Issue: #959)
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 24280;

-- Bug: #958  NPC: Marsh Lurker | Author: Shonsu - poprawienie zachowania NPC(Close Issue: #958)
DELETE FROM `creature` WHERE `guid` = 64845;
INSERT INTO `creature` VALUES
(64845, 18136, 530, 1, 1, 0, 0, -1219.64, 5751.73, 42.99, 5.31, 300, 5, 0, 4126, 2486, 1, 0, 0, 0);

-- Bug: #113 NPC: Grimtotem Naturalist | Author: Shonsu - poprawienie visuala(Close Issue: #113)
UPDATE `creature_template_addon` SET `auras` = 0 WHERE  `entry` = 7726;

-- Bug: #431 Quest: Going Bearback | Author: Shonsu - usunięcie nadmiarowego skilla, dodanie wilków(Close Issue: #431)
UPDATE `creature_template` SET `spell3` = 0 WHERE `entry` = 29602; -- 54788

SET @CGUID := (SELECT MAX(guid) from creature) +100; 

DELETE FROM `creature` WHERE `entry` IN (@CGUID, @CGUID + 1, @CGUID + 2);
INSERT INTO `creature` VALUES
(@CGUID, 29358, 571, 1, 1, 26331, 0, 7071.99, -2185.44, 761.44, 5.63741, 300, 0, 0, 36525, 0, 0, 0, 0, 0),
(@CGUID + 1, 29358, 571, 1, 1, 26331, 0, 7236.0, -2355.71, 753.67, 5.63741, 300, 0, 0, 36525, 0, 0, 0, 0, 0),
(@CGUID + 2, 29358, 571, 1, 1, 26331, 0, 7375.95, -2306.2, 756.79, 5.63741, 300, 0, 0, 36525, 0, 0, 0, 0, 0);


-- Bug: #254  Instance: Violte Hold | Author: Shonsu - dodanie reputacji do mobów i bossów(Close Issue: #254)
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (30695,30663, 30668, 29315, 29395, 29314, 29316, 29312, 29313,31503,31483, 31490,31507,31513,31512,31510,31509,31511,31508,31508, 29266);
INSERT INTO `creature_onkill_reputation` VALUES
-- normal
(30695, 1037, 1052, 7, 0, 5, 7, 0, 25, 1),
(30663, 1037, 1052, 7, 0, 5, 7, 0, 25, 1),
(30668, 1037, 1052, 7, 0, 5, 7, 0, 25, 1),
(29315, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
(29395, 1037, 1052, 7, 0, 5, 7, 0, 25, 1),
(29314, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
(29316, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
(29312, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
(29266, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
(29313, 1037, 1052, 7, 0, 50, 7, 0, 25, 1),
-- heroic
(31503, 1037, 1052, 7, 0, 12, 7, 0, 25, 1),
(31483, 1037, 1052, 7, 0, 12, 7, 0, 25, 1),
(31490, 1037, 1052, 7, 0, 12, 7, 0, 25, 1),
(31507, 1037, 1052, 7, 0, 250, 7, 0, 25, 1),
(31513, 1037, 1052, 7, 0, 12, 7, 0, 25, 1),
(31512, 1037, 1052, 7, 0, 250, 7, 0, 25, 1),
(31510, 1037, 1052, 7, 0, 250, 7, 0, 25, 1),
(31509, 1037, 1052, 7, 0, 250, 7, 0, 25, 1),
(31511, 1037, 1052, 7, 0, 250, 7, 0, 25, 1),
(31508, 1037, 1052, 7, 0, 250, 7, 0, 25, 1);