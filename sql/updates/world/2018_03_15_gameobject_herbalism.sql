UPDATE `pool_template` SET `max_limit` = 50 WHERE `entry` = 958;

SET @POOL = 9909;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 30, 'Goldthorn Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(8621, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8622, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8624, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8625, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8630, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8631, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8633, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8634, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8635, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8638, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8639, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8649, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8654, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8655, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8680, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8684, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8685, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8715, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8716, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8747, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8749, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8752, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8753, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8769, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8771, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8792, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8798, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8819, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8851, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8855, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8867, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8873, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8878, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8885, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8892, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8926, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8927, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8939, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8946, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8974, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8984, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8987, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8988, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8989, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8990, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(8991, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9002, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9004, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9008, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9009, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9010, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9031, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9046, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9048, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9049, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9050, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9051, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9057, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9102, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9105, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9141, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9142, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9143, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9162, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9165, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9171, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9172, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9173, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9190, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9191, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9211, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(9213, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(33141, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(33140, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(32643, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(32201, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(32199, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(32194, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(35388, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(35390, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(32114, @POOL, 0, 'Goldthorn - Eastern Kingdoms'),
(64094, @POOL, 0, 'Goldthorn - Eastern Kingdoms');


SET @POOL = 9910;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 10, 'Wintersbite Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
 (8190, @POOL, 0, 'Wintersbite'),
 (8191, @POOL, 0, 'Wintersbite'),
 (8192, @POOL, 0, 'Wintersbite'),
 (8193, @POOL, 0, 'Wintersbite'),
 (8194, @POOL, 0, 'Wintersbite'),
 (8195, @POOL, 0, 'Wintersbite'),
 (8196, @POOL, 0, 'Wintersbite'),
 (8197, @POOL, 0, 'Wintersbite'),
 (8198, @POOL, 0, 'Wintersbite'),
 (8199, @POOL, 0, 'Wintersbite'),
 (8200, @POOL, 0, 'Wintersbite'),
 (8201, @POOL, 0, 'Wintersbite'),
 (8202, @POOL, 0, 'Wintersbite'),
 (8203, @POOL, 0, 'Wintersbite'),
 (8204, @POOL, 0, 'Wintersbite'),
 (8205, @POOL, 0, 'Wintersbite'),
 (8206, @POOL, 0, 'Wintersbite'),
 (8207, @POOL, 0, 'Wintersbite'),
 (8208, @POOL, 0, 'Wintersbite'),
 (8209, @POOL, 0, 'Wintersbite'),
 (8210, @POOL, 0, 'Wintersbite'),
 (8211, @POOL, 0, 'Wintersbite'),
 (8212, @POOL, 0, 'Wintersbite'),
 (8213, @POOL, 0, 'Wintersbite'),
 (8214, @POOL, 0, 'Wintersbite'),
 (8215, @POOL, 0, 'Wintersbite'),
(33310, @POOL, 0, 'Wintersbite'),
(33137, @POOL, 0, 'Wintersbite'),
(33135, @POOL, 0, 'Wintersbite'),
(32217, @POOL, 0, 'Wintersbite'),
(32203, @POOL, 0, 'Wintersbite'),
(35389, @POOL, 0, 'Wintersbite'),
(35397, @POOL, 0, 'Wintersbite'),
(35404, @POOL, 0, 'Wintersbite');


SET @POOL = 9911;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 10, 'Bruiseweed Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
 (3030, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3031, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3034, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3038, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3111, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3112, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3176, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3332, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3362, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3435, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3545, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3564, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3607, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3608, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3609, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3610, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3671, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3676, @POOL, 0, 'Bruiseweed - Eastern K'),
 (3853, @POOL, 0, 'Bruiseweed - Eastern K'),
(33168, @POOL, 0, 'Bruiseweed - Eastern K'),
(32284, @POOL, 0, 'Bruiseweed - Eastern K'),
(35394, @POOL, 0, 'Bruiseweed - Eastern K'),
(87249, @POOL, 0, 'Bruiseweed - Eastern K');

SET @POOL = 9912;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 15, 'Khadgar Whisker Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(29997, @POOL, 0, 'Khadgar Whisker - EK'),
 (7831, @POOL, 0, 'Khadgar Whisker - EK'),
 (7832, @POOL, 0, 'Khadgar Whisker - EK'),
 (7841, @POOL, 0, 'Khadgar Whisker - EK'),
 (7843, @POOL, 0, 'Khadgar Whisker - EK'),
 (7902, @POOL, 0, 'Khadgar Whisker - EK'),
 (7906, @POOL, 0, 'Khadgar Whisker - EK'),
 (7919, @POOL, 0, 'Khadgar Whisker - EK'),
 (7959, @POOL, 0, 'Khadgar Whisker - EK'),
 (7981, @POOL, 0, 'Khadgar Whisker - EK'),
 (7982, @POOL, 0, 'Khadgar Whisker - EK'),
 (7989, @POOL, 0, 'Khadgar Whisker - EK'),
 (8015, @POOL, 0, 'Khadgar Whisker - EK'),
 (8026, @POOL, 0, 'Khadgar Whisker - EK'),
 (8030, @POOL, 0, 'Khadgar Whisker - EK'),
 (8051, @POOL, 0, 'Khadgar Whisker - EK'),
 (8055, @POOL, 0, 'Khadgar Whisker - EK'),
 (8062, @POOL, 0, 'Khadgar Whisker - EK'),
 (8063, @POOL, 0, 'Khadgar Whisker - EK'),
 (8064, @POOL, 0, 'Khadgar Whisker - EK'),
 (8071, @POOL, 0, 'Khadgar Whisker - EK'),
 (8092, @POOL, 0, 'Khadgar Whisker - EK'),
 (8102, @POOL, 0, 'Khadgar Whisker - EK'),
 (8120, @POOL, 0, 'Khadgar Whisker - EK'),
 (8128, @POOL, 0, 'Khadgar Whisker - EK'),
 (8130, @POOL, 0, 'Khadgar Whisker - EK'),
 (8132, @POOL, 0, 'Khadgar Whisker - EK'),
 (8133, @POOL, 0, 'Khadgar Whisker - EK'),
 (8162, @POOL, 0, 'Khadgar Whisker - EK'),
 (8164, @POOL, 0, 'Khadgar Whisker - EK'),
 (8172, @POOL, 0, 'Khadgar Whisker - EK'),
 (8174, @POOL, 0, 'Khadgar Whisker - EK'),
(32211, @POOL, 0, 'Khadgar Whisker - EK'),
(32210, @POOL, 0, 'Khadgar Whisker - EK'),
(32200, @POOL, 0, 'Khadgar Whisker - EK'),
(32198, @POOL, 0, 'Khadgar Whisker - EK'),
(35375, @POOL, 0, 'Khadgar Whisker - EK'),
(87554, @POOL, 0, 'Khadgar Whisker - EK'),
(87555, @POOL, 0, 'Khadgar Whisker - EK'),
(87556, @POOL, 0, 'Khadgar Whisker - EK'),
(87558, @POOL, 0, 'Khadgar Whisker - EK');


SET @POOL = 9913;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 20, 'Dreamfoil Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(19259, @POOL, 0, 'Dreamfoil EK'),
(19285, @POOL, 0, 'Dreamfoil EK'),
(19286, @POOL, 0, 'Dreamfoil EK'),
(19296, @POOL, 0, 'Dreamfoil EK'),
(19299, @POOL, 0, 'Dreamfoil EK'),
(19315, @POOL, 0, 'Dreamfoil EK'),
(19316, @POOL, 0, 'Dreamfoil EK'),
(19321, @POOL, 0, 'Dreamfoil EK'),
(19324, @POOL, 0, 'Dreamfoil EK'),
(19339, @POOL, 0, 'Dreamfoil EK'),
(19340, @POOL, 0, 'Dreamfoil EK'),
(19346, @POOL, 0, 'Dreamfoil EK'),
(19361, @POOL, 0, 'Dreamfoil EK'),
(19362, @POOL, 0, 'Dreamfoil EK'),
(19366, @POOL, 0, 'Dreamfoil EK'),
(19367, @POOL, 0, 'Dreamfoil EK'),
(19387, @POOL, 0, 'Dreamfoil EK'),
(19388, @POOL, 0, 'Dreamfoil EK'),
(19395, @POOL, 0, 'Dreamfoil EK'),
(19407, @POOL, 0, 'Dreamfoil EK'),
(19408, @POOL, 0, 'Dreamfoil EK'),
(19426, @POOL, 0, 'Dreamfoil EK'),
(19430, @POOL, 0, 'Dreamfoil EK'),
(19433, @POOL, 0, 'Dreamfoil EK'),
(19470, @POOL, 0, 'Dreamfoil EK'),
(19475, @POOL, 0, 'Dreamfoil EK'),
(19484, @POOL, 0, 'Dreamfoil EK'),
(19493, @POOL, 0, 'Dreamfoil EK'),
(19494, @POOL, 0, 'Dreamfoil EK'),
(19510, @POOL, 0, 'Dreamfoil EK'),
(19516, @POOL, 0, 'Dreamfoil EK'),
(19520, @POOL, 0, 'Dreamfoil EK'),
(19554, @POOL, 0, 'Dreamfoil EK'),
(19566, @POOL, 0, 'Dreamfoil EK'),
(19577, @POOL, 0, 'Dreamfoil EK'),
(19596, @POOL, 0, 'Dreamfoil EK'),
(19597, @POOL, 0, 'Dreamfoil EK'),
(19624, @POOL, 0, 'Dreamfoil EK'),
(19625, @POOL, 0, 'Dreamfoil EK'),
(19634, @POOL, 0, 'Dreamfoil EK'),
(19640, @POOL, 0, 'Dreamfoil EK'),
(19641, @POOL, 0, 'Dreamfoil EK'),
(19642, @POOL, 0, 'Dreamfoil EK'),
(19643, @POOL, 0, 'Dreamfoil EK'),
(19652, @POOL, 0, 'Dreamfoil EK'),
(19653, @POOL, 0, 'Dreamfoil EK'),
(29585, @POOL, 0, 'Dreamfoil EK'),
(33419, @POOL, 0, 'Dreamfoil EK'),
 (6830, @POOL, 0, 'Dreamfoil EK'),
 (6829, @POOL, 0, 'Dreamfoil EK'),
 (6810, @POOL, 0, 'Dreamfoil EK'),
 (4527, @POOL, 0, 'Dreamfoil EK'),
(39952, @POOL, 0, 'Dreamfoil EK'),
(39954, @POOL, 0, 'Dreamfoil EK'),
(63632, @POOL, 0, 'Dreamfoil EK'),
(86416, @POOL, 0, 'Dreamfoil EK'),
(87305, @POOL, 0, 'Dreamfoil EK');

SET @POOL = 9914;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 5, 'Sungrass Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(16028, @POOL, 0, 'Sungras EK'),
(16042, @POOL, 0, 'Sungras EK'),
(16052, @POOL, 0, 'Sungras EK'),
(16054, @POOL, 0, 'Sungras EK'),
(16058, @POOL, 0, 'Sungras EK'),
(16059, @POOL, 0, 'Sungras EK'),
(16068, @POOL, 0, 'Sungras EK'),
(16069, @POOL, 0, 'Sungras EK'),
(16082, @POOL, 0, 'Sungras EK'),
(16106, @POOL, 0, 'Sungras EK'),
(16131, @POOL, 0, 'Sungras EK'),
(16155, @POOL, 0, 'Sungras EK'),
(16192, @POOL, 0, 'Sungras EK'),
(16225, @POOL, 0, 'Sungras EK'),
(16226, @POOL, 0, 'Sungras EK'),
(16227, @POOL, 0, 'Sungras EK'),
(39957, @POOL, 0, 'Sungras EK'),
(39958, @POOL, 0, 'Sungras EK'),
(87177, @POOL, 0, 'Sungras EK');


SET @POOL = 9915;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 5, 'Golden Sansan Master Pool');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(18944, @POOL, 0, 'Golden Sansan'),
(18954, @POOL, 0, 'Golden Sansan'),
(18955, @POOL, 0, 'Golden Sansan'),
(18958, @POOL, 0, 'Golden Sansan'),
(18961, @POOL, 0, 'Golden Sansan'),
(18962, @POOL, 0, 'Golden Sansan'),
(18963, @POOL, 0, 'Golden Sansan'),
(18970, @POOL, 0, 'Golden Sansan'),
(18979, @POOL, 0, 'Golden Sansan'),
(19018, @POOL, 0, 'Golden Sansan'),
(19020, @POOL, 0, 'Golden Sansan'),
(19024, @POOL, 0, 'Golden Sansan'),
(19025, @POOL, 0, 'Golden Sansan'),
(19034, @POOL, 0, 'Golden Sansan'),
(19039, @POOL, 0, 'Golden Sansan'),
(19042, @POOL, 0, 'Golden Sansan'),
(19049, @POOL, 0, 'Golden Sansan'),
(19051, @POOL, 0, 'Golden Sansan'),
(19096, @POOL, 0, 'Golden Sansan'),
(19109, @POOL, 0, 'Golden Sansan'),
(19114, @POOL, 0, 'Golden Sansan'),
(19150, @POOL, 0, 'Golden Sansan'),
(19180, @POOL, 0, 'Golden Sansan'),
(19194, @POOL, 0, 'Golden Sansan'),
(19217, @POOL, 0, 'Golden Sansan'),
(19226, @POOL, 0, 'Golden Sansan'),
 (6873, @POOL, 0, 'Golden Sansan'),
 (6857, @POOL, 0, 'Golden Sansan'),
 (6823, @POOL, 0, 'Golden Sansan'),
 (4525, @POOL, 0, 'Golden Sansan');
  
UPDATE `pool_template` SET `max_limit` = 20 WHERE `entry` = 950;
UPDATE `pool_template` SET `max_limit` = 50 WHERE `entry` = 951;
UPDATE `pool_template` SET `max_limit` = 50 WHERE `entry` = 995;
UPDATE `pool_template` SET `max_limit` = 30 WHERE `entry` = 996;
