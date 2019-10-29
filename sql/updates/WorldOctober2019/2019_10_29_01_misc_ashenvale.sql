UPDATE creature_addon SET bytes1 = 3, auras = '42648 0' WHERE guid = 34228;
UPDATE creature_addon SET bytes1 = 3, auras = '42648 0' WHERE guid = 32599;
UPDATE creature_addon SET bytes1 = 3, auras = '42648 0' WHERE guid = 32600;
DELETE FROM `creature_addon` WHERE `guid` = 34225;
INSERT INTO `creature_addon` VALUES
(34225, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 1820.19, position_y = -2611.46, position_z = 60.7361, orientation = 6.12588 WHERE guid = 34226;
DELETE FROM `creature_addon` WHERE `guid` = 34226;
INSERT INTO `creature_addon` VALUES (34226, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature_addon SET bytes1 = 3, auras = '42648 0' WHERE guid = 32649;
UPDATE creature SET position_x = 2204.18, position_y = -1422.82, position_z = 90.7302, orientation = 0.65005 WHERE guid = 33087;
DELETE FROM `creature_addon` WHERE `guid` = 33087;
INSERT INTO `creature_addon` VALUES (33087, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 2314.2, position_y = -1425.68, position_z = 86.7688, orientation = 3.2998 WHERE guid = 33035;
DELETE FROM `creature_addon` WHERE `guid` = 33035;
INSERT INTO `creature_addon` VALUES (33035, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 2370.66, position_y = -1181.04, position_z = 90.8939, orientation = 4.43775 WHERE guid = 33034;
DELETE FROM `creature_addon` WHERE `guid` = 33034;
INSERT INTO `creature_addon` VALUES (33034, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 2379.65, position_y = -1195.1, position_z = 89.3769, orientation = 2.97333 WHERE guid = 33082;
DELETE FROM `creature_addon` WHERE `guid` = 33082;
INSERT INTO `creature_addon` VALUES (33082, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 2365.41, position_y = -1197.17, position_z = 89.0061, orientation = 0.622459 WHERE guid = 33081;
DELETE FROM `creature_addon` WHERE `guid` = 33081;
INSERT INTO `creature_addon` VALUES (33081, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = -1498.21, position_y = -3812.88, position_z = 24.285, orientation = 4.36949 WHERE guid = 13808;
DELETE FROM `creature_addon` WHERE `guid` = 13808;
INSERT INTO `creature_addon` VALUES (13808, 0, 0, 3, 0, 0, '42648 0');
UPDATE creature SET position_x = 1589.26, position_y = -2536.65, position_z = 102.131, orientation = 3.9547 WHERE guid = 34832;
UPDATE creature SET MovementType = 1, spawndist = 5 WHERE guid = 34832;
UPDATE creature SET position_x = 1711.3, position_y = -3459.53, position_z = 144.087, orientation = 2.09165 WHERE guid = 32896;
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE guid = 32896;
UPDATE creature SET position_x = 1777.18, position_y = -2006.78, position_z = 111.49, orientation = 4.69821 WHERE guid = 32589;
DELETE FROM creature_addon WHERE guid = 32589;
INSERT INTO creature_addon VALUES (32589,0,0,0,4097,16,'');

UPDATE creature SET position_x = 1570.8, position_y = -2509.23, position_z = 97.9949, orientation = 1.51761 WHERE guid = 33048;
DELETE FROM creature_addon WHERE guid = 33048;
INSERT INTO creature_addon VALUES (33048,0,0,1,4097,0,'');
UPDATE creature_addon SET bytes1 = 1 WHERE guid = 33028;
UPDATE creature_addon SET bytes1 = 1 WHERE guid = 33037;
UPDATE creature SET position_x = 2433.5, position_y = -3424.5, position_z = 99.1643, orientation = 6.04849 WHERE guid = 33061;
DELETE FROM creature_addon WHERE guid = 33061;
INSERT INTO creature_addon VALUES (33061,0,0,1,4097,0,'');
UPDATE creature SET position_x = -1096.84, position_y = -5580.96, position_z = 11.1797, orientation = 2.11735 WHERE guid = 13030;
DELETE FROM creature_addon WHERE guid = 13030;
INSERT INTO creature_addon VALUES (13030,0,0,1,4097,0,'');
UPDATE creature SET position_x = 881.191, position_y = -4198.7, position_z = -14.1639, orientation = 1.68093 WHERE guid = 6432;
UPDATE creature_addon SET bytes1 = 1 WHERE guid = 6432;
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32821);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32821;
INSERT INTO `smart_scripts` VALUES
(-32821, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32821, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 33010);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -33010;
INSERT INTO `smart_scripts` VALUES (-33010, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-33010, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 33026);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -33026;
INSERT INTO `smart_scripts` VALUES (-33026, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-33026, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32810);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32810;
INSERT INTO `smart_scripts` VALUES (-32810, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32810, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 33015);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -33015;
INSERT INTO `smart_scripts` VALUES (-33015, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-33015, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32817);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32817;
INSERT INTO `smart_scripts` VALUES (-32817, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32817, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32813);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32813;
INSERT INTO `smart_scripts` VALUES (-32813, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32813, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32829);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32829;
INSERT INTO `smart_scripts` VALUES (-32829, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32829, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 33022);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -33022;
INSERT INTO `smart_scripts` VALUES (-33022, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-33022, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32814);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32814;
INSERT INTO `smart_scripts` VALUES (-32814, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32814, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32845);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32845;
INSERT INTO `smart_scripts` VALUES (-32845, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32845, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE entry = (SELECT id FROM creature WHERE guid = 32841);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -32841;
INSERT INTO `smart_scripts` VALUES (-32841, 0, 0, 0, 1, 0, 100, 0, 2000, 3000, 4000, 5000, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(-32841, 0, 1, 0, 1, 0, 100, 0, 4000, 5000, 6000, 8000, 5, 54, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
