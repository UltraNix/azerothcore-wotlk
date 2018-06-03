-- Chip off ulduar block
SET @OGUID = 269386;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID AND @OGUID+11;
INSERT INTO `gameobject` VALUES
(@OGUID, 194461, 571, 1, 7, 7475.51, -1383.12, 930.56, 3.58, -0.5, 0, 0, 0, 60, 100, 1, 0),
(@OGUID+1, 194461, 571, 1, 7, 7223.35, -1407.62, 911.70, 0.00, 1, 1, 1, 1, 60, 100, 1, 0),
(@OGUID+2, 194461, 571, 1, 7, 7308.74, -930.99, 916.47, 3.86, 1, 1, 1, 1, 60, 100, 1, 0),
(@OGUID+3, 194461, 571, 1, 7, 7631.98, -1170.15, 923.63, 3.32, 0, 0.087156, 0, 0, 60, 100, 1, 0),
(@OGUID+4, 194461, 571, 1, 7, 7714.21, -1062.28, 918.65, 4.08, 0, -0.139, 0, 0.0871, 60, 100, 1, 0),
(@OGUID+5, 194461, 571, 1, 7, 7395.14, -868.96, 915.63, 3.82, 0.988, 0, 0.6156, 0, 60, 100, 1, 0),
(@OGUID+6, 194461, 571, 1, 7, 8125.11, -1088.86, 926.66, 3.21, 0, 0.988, 0.494, 0, 60, 100, 1, 0),
(@OGUID+7, 194461, 571, 1, 7, 8323.84, -1095.45, 923.8, 1.79, 0.08, -0.05, 0.5, 0.8, 60, 100, 1, 0),
(@OGUID+8, 194461, 571, 1, 7, 8090.09, -882.47, 955.85, 3.73, 0, 0.84, 0.49, 0, 60, 100, 1, 0),
(@OGUID+9, 194461, 571, 1, 7, 7342.08, -829.80, 933.30, 2.81, 0, 0.84, 0.49, 0, 60, 100, 1, 0),
(@OGUID+10, 194461, 571, 1, 7, 7707.21, -1044.61, 916.86, 1.00, 0, 0.84, 0.49, 0, 60, 100, 1, 0),
(@OGUID+11, 194461, 571, 1, 7, 8070.63, -1042.43, 941.29, 3.58, 0, 0.84, 0.49, 0, 60, 100, 1, 0);

SET @CHISEL = 33660;
SET @STONE_SUMMONER = 33953;
UPDATE `creature_template` SET `AIName` = "SmartAI", `flags_extra` = 2 WHERE `entry` IN (@CHISEL,@STONE_SUMMONER,@CHISEL*100);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@CHISEL,@CHISEL*100, @STONE_SUMMONER);
INSERT INTO `smart_scripts` VALUES
(@CHISEL, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 80, @CHISEL*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Goblin Chisel - On Just Summoned - Start Script'),
(@CHISEL*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 64068, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Goblin--  Chisel - Script - Cast Ticking Bomb'),
(@CHISEL*100, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 11, 64079, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Goblin Chisel - Script - Cast Cosmetic Explosion'),
(@CHISEL*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 64061, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Goblin Chisel - Script - Cast Explosion'),
(@CHISEL*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 63392, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Goblin Chisel - On Script - Cast Throw Stone Chunks'),
(@CHISEL*100, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 3, 0, 0, 0, 0, 0, 20, 194461, 20, 0, 0, 0, 0, 0, 'Goblin Chisel - Script - Set Go state just deactivated'),
(@STONE_SUMMONER, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 11, 63386, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Small Stone Summoner - On Just Summoned - Cast Summon Small Stone Block');

UPDATE `gameobject_template` SET  `AIName` = "", `ScriptName` = "" WHERE `entry` = 194461;
DELETE FROM `spell_script_names` WHERE `spell_id` = 63392;
INSERT INTO `spell_script_names` VALUES
(63392, 'spell_q13681_throw_stone_chunk');

DELETE FROM `creature_queststarter` WHERE `quest` = 13681;
INSERT INTO `creature_queststarter` VALUES
(33434, 13681);
DELETE FROM `creature_questender` WHERE `quest` = 13681;
INSERT INTO `creature_questender` VALUES
(33434, 13681);

UPDATE `gameobject_template` SET `data1` = 194463 WHERE `entry` = 194463;
DELETE FROM `gameobject_loot_template` WHERE `entry` = 194463;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(194463, 45278, -100, 1, 0, 1, 4);

-- jack me some lumber
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` = 33434;
DELETE FROM `creature_queststarter` WHERE `quest` = 13627;
DELETE FROM `creature_queststarter` WHERE `quest` = 13820;
INSERT INTO `creature_queststarter` VALUES
(33817, 13820), -- opcjonalny prequest
(33434, 13627); -- daily 
DELETE FROM `creature_questender` WHERE `quest` IN (13820,13627);
INSERT INTO `creature_questender` VALUES
(33434, 13820),
(33434, 13627);
UPDATE `creature_template` SET `faction` = 16 WHERE `entry` = 33947;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 33308;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN ( 33308, 3330800);
INSERT INTO `smart_scripts` VALUES
(33308, 0, 0, 1, 8, 0, 100, 1, 62990, 0, 0, 0, 11, 62855, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell hit - Cast LumberJackin'),
(33308, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell hit - Despawn');

DELETE FROM `conditions` WHERE  `sourceentry` = 62990;
INSERT INTO `conditions` VALUES
(13, 1, 62990, 0, 0, 31, 0, 3, 33308, 0, 0, 0, 0, '', 'Chop tree should target Crystalong Oak');

SET @CGUID = 142300;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID AND @CGUID+25;
INSERT INTO `creature` VALUES 
(@CGUID, 33308, 571, 1, 1, 0, 0, 5717.31, 482.338, 162.46, 5.48766, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 33308, 571, 1, 1, 0, 0, 5776.08, 416.478, 174.631, 3.11576, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2, 33308, 571, 1, 1, 0, 0, 5723.9, 349.74, 163.849, 0.904862, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3, 33308, 571, 1, 1, 0, 0, 5792.99, 557.175, 166.058, 4.56482, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4, 33308, 571, 1, 1, 0, 0, 5859, 590.191, 180.452, 4.30564, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5, 33308, 571, 1, 1, 0, 0, 5832.23, 534.432, 179.86, 3.9797, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6, 33308, 571, 1, 1, 0, 0, 5866.76, 721.829, 163.244, 0.900943, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7, 33308, 571, 1, 1, 0, 0, 5898.76, 701.853, 165.949, 4.46666, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8, 33308, 571, 1, 1, 0, 0, 5940.31, 703.013, 168.287, 5.46411, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9, 33308, 571, 1, 1, 0, 0, 5996.23, 719.235, 172.01, 4.4156, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10, 33308, 571, 1, 1, 0, 0, 6042.86, 761.038, 174.169, 0.57892, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11, 33308, 571, 1, 1, 0, 0, 6040.47, 864.374, 157.292, 1.29364, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12, 33308, 571, 1, 1, 0, 0, 5974.01, 953.197, 153.545, 2.36178, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13, 33308, 571, 1, 1, 0, 0, 5939.87, 923.505, 154.164, 3.75193, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14, 33308, 571, 1, 1, 0, 0, 5899.98, 903.793, 159.729, 3.43777, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+15, 33308, 571, 1, 1, 0, 0, 5832.25, 851.849, 156.836, 4.19961, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+16, 33308, 571, 1, 1, 0, 0, 5789.69, 826.294, 153.101, 3.88938, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+17, 33308, 571, 1, 1, 0, 0, 5742.53, 810.186, 153.424, 3.34745, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+18, 33308, 571, 1, 1, 0, 0, 5670.18, 761.991, 152.578, 2.70735, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+19, 33308, 571, 1, 1, 0, 0, 5632.1, 726.091, 155.277, 1.92195, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+20, 33308, 571, 1, 1, 0, 0, 5613.79, 707.102, 156.75, 3.20608, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+21, 33308, 571, 1, 1, 0, 0, 5653.73, 601.442, 152.685, 3.59092, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+22, 33308, 571, 1, 1, 0, 0, 5637.72, 574.879, 154.792, 4.73367, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+23, 33308, 571, 1, 1, 0, 0, 5619.24, 518.643, 150.913, 4.07001, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+24, 33308, 571, 1, 1, 0, 0, 5792.69, 363.301, 182.29, 5.88427, 60, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+25, 33308, 571, 1, 1, 0, 0, 5836.4, 408.158, 192.881, 1.23864, 60, 0, 0, 1, 0, 0, 0, 0, 0);
