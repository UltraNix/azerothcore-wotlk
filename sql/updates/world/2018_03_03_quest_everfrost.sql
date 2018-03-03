SET @OGUID = 279388;
DELETE FROM `gameobject` WHERE `id` = 193997;
INSERT INTO `gameobject` VALUES
(@OGUID, 193997, 571, 1, 1, 7155.12, -2096.03, 764.428, 2.53072, 0, 0, 0.953716, 0.300709, 1200, 100, 1, 0),
(@OGUID+1, 193997, 571, 1, 1, 7218.2, -2139.83, 863.085, -1.09956, 0, 0, -0.5225, 0.852639, 1200, 100, 1, 0),
(@OGUID+2, 193997, 571, 1, 1, 7330.44, -2212.68, 800.483, 4.25861, 0, 0, 0.848046, -0.529922, 1200, 255, 1, 0),
(@OGUID+3, 193997, 571, 1, 1, 7211.5, -2373.86, 781.449, 4.38078, 0, 0, 0.814114, -0.580705, 1200, 255, 1, 0),
(@OGUID+4, 193997, 571, 1, 1, 6973.8, -2096.83, 777.638, 3.26377, 0, 0, 0.998135, -0.0610507, 1200, 255, 1, 0),
(@OGUID+5, 193997, 571, 1, 1, 7310.71, -2812.07, 798.081, 1.5708, 0, 0, 0.707108, 0.707106, 1200, 255, 1, 0),
(@OGUID+6, 193997, 571, 1, 1, 7301.01, -2746.12, 749.508, 0.157079, 0, 0, 0.0784588, 0.996917, 1200, 255, 1, 0),
(@OGUID+7, 193997, 571, 1, 1, 7550.37, -3154.98, 840.146, 4.41568, 0, 0, 0.803858, -0.594822, 1200, 255, 1, 0),
(@OGUID+8, 193997, 571, 1, 1, 7177.29, -3071.11, 862.298, 0.680677, 0, 0, 0.333806, 0.942642, 1200, 255, 1, 0),
(@OGUID+9, 193997, 571, 1, 1, 7694.28, -3154.72, 869.769, 3.76991, 0, 0, 0.951057, -0.309016, 1200, 255, 1, 0);

DELETE FROM `pool_gameobject` WHERE `pool_entry` = 383;
INSERT INTO `pool_gameobject` VALUES
(@OGUID,   383, 0, 'Everfrost Chip'),
(@OGUID+1, 383, 0, 'Everfrost Chip'),
(@OGUID+2, 383, 0, 'Everfrost Chip'),
(@OGUID+3, 383, 0, 'Everfrost Chip'),
(@OGUID+4, 383, 0, 'Everfrost Chip'),
(@OGUID+5, 383, 0, 'Everfrost Chip'),
(@OGUID+6, 383, 0, 'Everfrost Chip'),
(@OGUID+7, 383, 0, 'Everfrost Chip'),
(@OGUID+8, 383, 0, 'Everfrost Chip'),
(@OGUID+9, 383, 0, 'Everfrost Chip');

UPDATE `pool_template` SET `max_limit` = 5 WHERE `entry` = 383;

UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` = 44724;
DELETE FROM `conditions` WHERE `SourceEntry` = 44724 AND `SourceTypeOrReferenceId` = 4;
INSERT INTO `conditions` VALUES
(4, 26782, 44724, 0, 0, 8, 0, 13420, 0, 0, 0, 0, 0, '', 'Show Everfrost chip if player has rewarded quest Everfrost');
UPDATE `quest_template` SET `Flags` = 8320, `specialflags` = 1 WHERE `id` = 13421; -- 128
