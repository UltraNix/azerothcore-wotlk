UPDATE `item_template` SET `stat_value1` = 621, `stat_value2` = 55, `stat_value3` = 57, `stat_value4` = 50, `stat_value5` = 49 WHERE `entry` = 46017;

DELETE FROM `creature` WHERE `guid` IN (85217, 86928);
INSERT INTO `creature` VALUES 
(85217, 35494, 571, 1, 150, 29832, 1, 5766.38, 738.24, 653.748, 2.94961, 180, 0, 0, 1, 0, 0, 0, 0, 0),
(86928, 35495, 571, 1, 150, 29831, 1, 5939.31, 513.155, 650.263, 2.56563, 180, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `npc_vendor` WHERE `entry` = 40160 AND `item` = 45087;
INSERT INTO `npc_vendor` VALUES
(40160, 0, 45087, 0, 0, 2987);

SET @COST40 = 2579;
SET @COST15 = 2577;
SET @ENTRY = 32294;
DELETE FROM `npc_vendor` WHERE `entry` = @ENTRY AND `item` IN (49000,
48999,
48982,
48981,
48980,
48979,
48978,
48977,
48976,
48975,
48974,
48998,
48997,
48994,
48993,
48992,
48991,
48990,
48988,
48987,
48983);
INSERT INTO `npc_vendor` VALUES
(@ENTRY, 0, 49000, 0, 0, @COST15),
(@ENTRY, 0, 48999, 0, 0, @COST15),
(@ENTRY, 0, 48982, 0, 0, @COST15),
(@ENTRY, 0, 48981, 0, 0, @COST15),
(@ENTRY, 0, 48980, 0, 0, @COST15),
(@ENTRY, 0, 48979, 0, 0, @COST15),
(@ENTRY, 0, 48978, 0, 0, @COST15),
(@ENTRY, 0, 48977, 0, 0, @COST15),
(@ENTRY, 0, 48976, 0, 0, @COST15),
(@ENTRY, 0, 48975, 0, 0, @COST15),
(@ENTRY, 0, 48974, 0, 0, @COST15),
(@ENTRY, 0, 48998, 0, 0, @COST40),
(@ENTRY, 0, 48997, 0, 0, @COST40),
(@ENTRY, 0, 48994, 0, 0, @COST40),
(@ENTRY, 0, 48993, 0, 0, @COST40),
(@ENTRY, 0, 48992, 0, 0, @COST40),
(@ENTRY, 0, 48991, 0, 0, @COST40),
(@ENTRY, 0, 48990, 0, 0, @COST40),
(@ENTRY, 0, 48988, 0, 0, @COST40),
(@ENTRY, 0, 48987, 0, 0, @COST40),
(@ENTRY, 0, 48983, 0, 0, @COST40);

SET @ENTRY = 32296;
DELETE FROM `npc_vendor` WHERE `entry` = @ENTRY AND `item` IN (49000,
48999,
48982,
48981,
48980,
48979,
48978,
48977,
48976,
48975,
48974,
48998,
48997,
48994,
48993,
48992,
48991,
48990,
48988,
48987,
48983);
INSERT INTO `npc_vendor` VALUES
(@ENTRY, 0, 49000, 0, 0, @COST15),
(@ENTRY, 0, 48999, 0, 0, @COST15),
(@ENTRY, 0, 48982, 0, 0, @COST15),
(@ENTRY, 0, 48981, 0, 0, @COST15),
(@ENTRY, 0, 48980, 0, 0, @COST15),
(@ENTRY, 0, 48979, 0, 0, @COST15),
(@ENTRY, 0, 48978, 0, 0, @COST15),
(@ENTRY, 0, 48977, 0, 0, @COST15),
(@ENTRY, 0, 48976, 0, 0, @COST15),
(@ENTRY, 0, 48975, 0, 0, @COST15),
(@ENTRY, 0, 48974, 0, 0, @COST15),
(@ENTRY, 0, 48998, 0, 0, @COST40),
(@ENTRY, 0, 48997, 0, 0, @COST40),
(@ENTRY, 0, 48994, 0, 0, @COST40),
(@ENTRY, 0, 48993, 0, 0, @COST40),
(@ENTRY, 0, 48992, 0, 0, @COST40),
(@ENTRY, 0, 48991, 0, 0, @COST40),
(@ENTRY, 0, 48990, 0, 0, @COST40),
(@ENTRY, 0, 48988, 0, 0, @COST40),
(@ENTRY, 0, 48987, 0, 0, @COST40),
(@ENTRY, 0, 48983, 0, 0, @COST40);

DELETE FROM `disables` WHERE `entry` IN (66663, 66660, 66664, 66658, 66662, 66659);

DELETE FROM `item_loot_template` WHERE `entry` = 44943 AND `item` = 1;
INSERT INTO `item_loot_template` VALUES (44943, 1, 7, 1, 0, -10008, 1);

DELETE FROM `disables` WHERE `entry` = 14151;

DELETE FROM `npc_trainer` WHERE `entry` = 201003 AND `spell` IN (66658, 66660,66662,66663,66664);
INSERT INTO `npc_trainer` VALUES 
(201003, 66658, 150000, 171, 450, 0),
(201003, 66660, 150000, 171, 450, 0),
(201003, 66662, 150000, 171, 450, 0),
(201003, 66663, 150000, 171, 450, 0),
(201003, 66664, 150000, 171, 450, 0);

DELETE FROM `npc_vendor` WHERE `entry` IN (31582, 31580, 32172) AND `item` IN (36919, 36922, 36925, 36928, 36931, 36934);
INSERT INTO `npc_vendor` VALUES
(31582, 0, 36919, 0, 0, 2706),
(31582, 0, 36922, 0, 0, 2706),
(31582, 0, 36925, 0, 0, 2706),
(31582, 0, 36928, 0, 0, 2484),
(31582, 0, 36931, 0, 0, 2484),
(31582, 0, 36934, 0, 0, 2484),
(31580, 0, 36919, 0, 0, 2706),
(31580, 0, 36922, 0, 0, 2706),
(31580, 0, 36925, 0, 0, 2706),
(31580, 0, 36928, 0, 0, 2484),
(31580, 0, 36931, 0, 0, 2484),
(31580, 0, 36934, 0, 0, 2484),
(32172, 0, 36919, 0, 0, 2706),
(32172, 0, 36922, 0, 0, 2706),
(32172, 0, 36925, 0, 0, 2706),
(32172, 0, 36928, 0, 0, 2484),
(32172, 0, 36931, 0, 0, 2484),
(32172, 0, 36934, 0, 0, 2484);

DELETE FROM `npc_vendor` WHERE `entry` IN (33637, 33680, 28701) AND `item` IN (46897,
46898,
46899,
46900,
46901,
46902,
46903,
46904,
46905,
46906,
46907,
46908,
46909,
46910,
46911,
46912,
46913,
46914,
46915,
46916,
46917,
46918,
46919,
46920,
46921,
46922,
46923,
46924,
46925,
46926,
46927,
46928,
46929,
46930,
46931,
46932,
46933,
46934,
46935,
46936,
46937,
46938,
46939,
46940,
46941,
46942,
46943,
46944,
46945,
46946,
46947,
46948,
46949,
46950,
46951,
46952,
46953,
46956,
47007,
47008,
47010,
47011,
47012,
47015,
47016,
47017,
47018,
47019,
47020,
47021,
47022,
47023,
49112);
INSERT INTO `npc_vendor` VALUES
(28701, 0, 46897, 0, 0, 2436),
(28701, 0, 46898, 0, 0, 2436),
(28701, 0, 46899, 0, 0, 2436),
(28701, 0, 46900, 0, 0, 2436),
(28701, 0, 46901, 0, 0, 2436),
(28701, 0, 46902, 0, 0, 2436),
(28701, 0, 46903, 0, 0, 2436),
(28701, 0, 46904, 0, 0, 2436),
(28701, 0, 46905, 0, 0, 2436),
(28701, 0, 46906, 0, 0, 2436),
(28701, 0, 46907, 0, 0, 2436),
(28701, 0, 46908, 0, 0, 2436),
(28701, 0, 46909, 0, 0, 2436),
(28701, 0, 46910, 0, 0, 2436),
(28701, 0, 46911, 0, 0, 2436),
(28701, 0, 46912, 0, 0, 2436),
(28701, 0, 46913, 0, 0, 2436),
(28701, 0, 46914, 0, 0, 2436),
(28701, 0, 46915, 0, 0, 2436),
(28701, 0, 46916, 0, 0, 2436),
(28701, 0, 46917, 0, 0, 2436),
(28701, 0, 46918, 0, 0, 2436),
(28701, 0, 46919, 0, 0, 2436),
(28701, 0, 46920, 0, 0, 2436),
(28701, 0, 46921, 0, 0, 2436),
(28701, 0, 46922, 0, 0, 2436),
(28701, 0, 46923, 0, 0, 2436),
(28701, 0, 46924, 0, 0, 2436),
(28701, 0, 46925, 0, 0, 2436),
(28701, 0, 46926, 0, 0, 2436),
(28701, 0, 46927, 0, 0, 2436),
(28701, 0, 46928, 0, 0, 2436),
(28701, 0, 46929, 0, 0, 2436),
(28701, 0, 46930, 0, 0, 2436),
(28701, 0, 46931, 0, 0, 2436),
(28701, 0, 46932, 0, 0, 2436),
(28701, 0, 46933, 0, 0, 2436),
(28701, 0, 46934, 0, 0, 2436),
(28701, 0, 46935, 0, 0, 2436),
(28701, 0, 46936, 0, 0, 2436),
(28701, 0, 46937, 0, 0, 2436),
(28701, 0, 46938, 0, 0, 2436),
(28701, 0, 46939, 0, 0, 2436),
(28701, 0, 46940, 0, 0, 2436),
(28701, 0, 46941, 0, 0, 2436),
(28701, 0, 46942, 0, 0, 2436),
(28701, 0, 46943, 0, 0, 2436),
(28701, 0, 46944, 0, 0, 2436),
(28701, 0, 46945, 0, 0, 2436),
(28701, 0, 46946, 0, 0, 2436),
(28701, 0, 46947, 0, 0, 2436),
(28701, 0, 46948, 0, 0, 2436),
(28701, 0, 46949, 0, 0, 2436),
(28701, 0, 46950, 0, 0, 2436),
(28701, 0, 46951, 0, 0, 2436),
(28701, 0, 46952, 0, 0, 2436),
(28701, 0, 46953, 0, 0, 2436),
(28701, 0, 46956, 0, 0, 2436),
(28701, 0, 47007, 0, 0, 2436),
(28701, 0, 47008, 0, 0, 2436),
(28701, 0, 47010, 0, 0, 2436),
(28701, 0, 47011, 0, 0, 2436),
(28701, 0, 47012, 0, 0, 2436),
(28701, 0, 47015, 0, 0, 2436),
(28701, 0, 47016, 0, 0, 2436),
(28701, 0, 47017, 0, 0, 2436),
(28701, 0, 47018, 0, 0, 2436),
(28701, 0, 47019, 0, 0, 2436),
(28701, 0, 47020, 0, 0, 2436),
(28701, 0, 47021, 0, 0, 2436),
(28701, 0, 47022, 0, 0, 2436),
(28701, 0, 47023, 0, 0, 2436),
(28701, 0, 49112, 0, 0, 2436),
(33637, 0, 46897, 0, 0, 2436),
(33637, 0, 46898, 0, 0, 2436),
(33637, 0, 46899, 0, 0, 2436),
(33637, 0, 46900, 0, 0, 2436),
(33637, 0, 46901, 0, 0, 2436),
(33637, 0, 46902, 0, 0, 2436),
(33637, 0, 46903, 0, 0, 2436),
(33637, 0, 46904, 0, 0, 2436),
(33637, 0, 46905, 0, 0, 2436),
(33637, 0, 46906, 0, 0, 2436),
(33637, 0, 46907, 0, 0, 2436),
(33637, 0, 46908, 0, 0, 2436),
(33637, 0, 46909, 0, 0, 2436),
(33637, 0, 46910, 0, 0, 2436),
(33637, 0, 46911, 0, 0, 2436),
(33637, 0, 46912, 0, 0, 2436),
(33637, 0, 46913, 0, 0, 2436),
(33637, 0, 46914, 0, 0, 2436),
(33637, 0, 46915, 0, 0, 2436),
(33637, 0, 46916, 0, 0, 2436),
(33637, 0, 46917, 0, 0, 2436),
(33637, 0, 46918, 0, 0, 2436),
(33637, 0, 46919, 0, 0, 2436),
(33637, 0, 46920, 0, 0, 2436),
(33637, 0, 46921, 0, 0, 2436),
(33637, 0, 46922, 0, 0, 2436),
(33637, 0, 46923, 0, 0, 2436),
(33637, 0, 46924, 0, 0, 2436),
(33637, 0, 46925, 0, 0, 2436),
(33637, 0, 46926, 0, 0, 2436),
(33637, 0, 46927, 0, 0, 2436),
(33637, 0, 46928, 0, 0, 2436),
(33637, 0, 46929, 0, 0, 2436),
(33637, 0, 46930, 0, 0, 2436),
(33637, 0, 46931, 0, 0, 2436),
(33637, 0, 46932, 0, 0, 2436),
(33637, 0, 46933, 0, 0, 2436),
(33637, 0, 46934, 0, 0, 2436),
(33637, 0, 46935, 0, 0, 2436),
(33637, 0, 46936, 0, 0, 2436),
(33637, 0, 46937, 0, 0, 2436),
(33637, 0, 46938, 0, 0, 2436),
(33637, 0, 46939, 0, 0, 2436),
(33637, 0, 46940, 0, 0, 2436),
(33637, 0, 46941, 0, 0, 2436),
(33637, 0, 46942, 0, 0, 2436),
(33637, 0, 46943, 0, 0, 2436),
(33637, 0, 46944, 0, 0, 2436),
(33637, 0, 46945, 0, 0, 2436),
(33637, 0, 46946, 0, 0, 2436),
(33637, 0, 46947, 0, 0, 2436),
(33637, 0, 46948, 0, 0, 2436),
(33637, 0, 46949, 0, 0, 2436),
(33637, 0, 46950, 0, 0, 2436),
(33637, 0, 46951, 0, 0, 2436),
(33637, 0, 46952, 0, 0, 2436),
(33637, 0, 46953, 0, 0, 2436),
(33637, 0, 46956, 0, 0, 2436),
(33637, 0, 47007, 0, 0, 2436),
(33637, 0, 47008, 0, 0, 2436),
(33637, 0, 47010, 0, 0, 2436),
(33637, 0, 47011, 0, 0, 2436),
(33637, 0, 47012, 0, 0, 2436),
(33637, 0, 47015, 0, 0, 2436),
(33637, 0, 47016, 0, 0, 2436),
(33637, 0, 47017, 0, 0, 2436),
(33637, 0, 47018, 0, 0, 2436),
(33637, 0, 47019, 0, 0, 2436),
(33637, 0, 47020, 0, 0, 2436),
(33637, 0, 47021, 0, 0, 2436),
(33637, 0, 47022, 0, 0, 2436),
(33637, 0, 47023, 0, 0, 2436),
(33637, 0, 49112, 0, 0, 2436),
(33680, 0, 46897, 0, 0, 2436),
(33680, 0, 46898, 0, 0, 2436),
(33680, 0, 46899, 0, 0, 2436),
(33680, 0, 46900, 0, 0, 2436),
(33680, 0, 46901, 0, 0, 2436),
(33680, 0, 46902, 0, 0, 2436),
(33680, 0, 46903, 0, 0, 2436),
(33680, 0, 46904, 0, 0, 2436),
(33680, 0, 46905, 0, 0, 2436),
(33680, 0, 46906, 0, 0, 2436),
(33680, 0, 46907, 0, 0, 2436),
(33680, 0, 46908, 0, 0, 2436),
(33680, 0, 46909, 0, 0, 2436),
(33680, 0, 46910, 0, 0, 2436),
(33680, 0, 46911, 0, 0, 2436),
(33680, 0, 46912, 0, 0, 2436),
(33680, 0, 46913, 0, 0, 2436),
(33680, 0, 46914, 0, 0, 2436),
(33680, 0, 46915, 0, 0, 2436),
(33680, 0, 46916, 0, 0, 2436),
(33680, 0, 46917, 0, 0, 2436),
(33680, 0, 46918, 0, 0, 2436),
(33680, 0, 46919, 0, 0, 2436),
(33680, 0, 46920, 0, 0, 2436),
(33680, 0, 46921, 0, 0, 2436),
(33680, 0, 46922, 0, 0, 2436),
(33680, 0, 46923, 0, 0, 2436),
(33680, 0, 46924, 0, 0, 2436),
(33680, 0, 46925, 0, 0, 2436),
(33680, 0, 46926, 0, 0, 2436),
(33680, 0, 46927, 0, 0, 2436),
(33680, 0, 46928, 0, 0, 2436),
(33680, 0, 46929, 0, 0, 2436),
(33680, 0, 46930, 0, 0, 2436),
(33680, 0, 46931, 0, 0, 2436),
(33680, 0, 46932, 0, 0, 2436),
(33680, 0, 46933, 0, 0, 2436),
(33680, 0, 46934, 0, 0, 2436),
(33680, 0, 46935, 0, 0, 2436),
(33680, 0, 46936, 0, 0, 2436),
(33680, 0, 46937, 0, 0, 2436),
(33680, 0, 46938, 0, 0, 2436),
(33680, 0, 46939, 0, 0, 2436),
(33680, 0, 46940, 0, 0, 2436),
(33680, 0, 46941, 0, 0, 2436),
(33680, 0, 46942, 0, 0, 2436),
(33680, 0, 46943, 0, 0, 2436),
(33680, 0, 46944, 0, 0, 2436),
(33680, 0, 46945, 0, 0, 2436),
(33680, 0, 46946, 0, 0, 2436),
(33680, 0, 46947, 0, 0, 2436),
(33680, 0, 46948, 0, 0, 2436),
(33680, 0, 46949, 0, 0, 2436),
(33680, 0, 46950, 0, 0, 2436),
(33680, 0, 46951, 0, 0, 2436),
(33680, 0, 46952, 0, 0, 2436),
(33680, 0, 46953, 0, 0, 2436),
(33680, 0, 46956, 0, 0, 2436),
(33680, 0, 47007, 0, 0, 2436),
(33680, 0, 47008, 0, 0, 2436),
(33680, 0, 47010, 0, 0, 2436),
(33680, 0, 47011, 0, 0, 2436),
(33680, 0, 47012, 0, 0, 2436),
(33680, 0, 47015, 0, 0, 2436),
(33680, 0, 47016, 0, 0, 2436),
(33680, 0, 47017, 0, 0, 2436),
(33680, 0, 47018, 0, 0, 2436),
(33680, 0, 47019, 0, 0, 2436),
(33680, 0, 47020, 0, 0, 2436),
(33680, 0, 47021, 0, 0, 2436),
(33680, 0, 47022, 0, 0, 2436),
(33680, 0, 47023, 0, 0, 2436),
(33680, 0, 49112, 0, 0, 2436);

UPDATE `quest_template` SET `RewardItemId1` = 47241 WHERE `id` IN (13245,
13246,
13247,
13248,
13249,
13250,
13251,
13252,
13253,
13254,
13255,
13256,
14199,
24712,
24802,
24511,
24499,
24500,
24710);

UPDATE `quest_template` SET `RewardItemId1` = 45624 WHERE `Id` IN (13240, 13241, 13243, 13244);


SET @COST = 2588;
DELETE FROM `npc_vendor` WHERE `entry` = 34040 AND `item` IN (36933, 36930, 36927, 36924, 36921, 36918);
DELETE FROM `npc_vendor` WHERE `entry` = 34040 AND `item` IN (36919, 36922, 36925, 36928, 36931, 36934);
INSERT INTO `npc_vendor` VALUES
(34040, 0, 36919, 0, 0, @COST),
(34040, 0, 36922, 0, 0, @COST),
(34040, 0, 36925, 0, 0, @COST),
(34040, 0, 36928, 0, 0, @COST),
(34040, 0, 36931, 0, 0, @COST),
(34040, 0, 36934, 0, 0, @COST);

DELETE FROM `creature_queststarter` WHERE `id` = 20735 AND `quest` = 14199;
INSERT INTO `creature_queststarter` VALUES
(20735, 14199);
DELETE FROM `creature_questender` WHERE `id` = 20735 AND `quest` = 14199;
INSERT INTO `creature_questender` VALUES
(20735, 14199);

DELETE FROM `disables` WHERE `sourcetype` = 1 AND `entry` IN (13820,
14016,
14017,
14074,
14076,
14077,
14080,
14090,
14092,
14096,
14101,
14102,
14104,
14105,
14108,
14112,
14136,
14140,
14141,
14142,
14143,
14144,
14145,
14152);

UPDATE `creature` SET `phaseMask` = 1 WHERE `guid` = 200816;


DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=3;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 3, 75, 1, 1, -1003, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=2;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 2, 100, 1, 1, -1002, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=1;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 1, 20, 1, 0, -13005, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=46849;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 46849, 75, 1, 0, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36919;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36919, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36922;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36922, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36925;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36925, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36928;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36928, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36931;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36931, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36934;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36934, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36917;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36917, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36932;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36932, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36929;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36929, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36926;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36926, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36923;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36923, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36920;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36920, 0, 1, 1, 1, 2);

DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36929;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36929, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36917;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36917, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36933;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36933, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36932;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36932, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36930;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36930, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36927;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36927, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36926;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36926, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36924;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36924, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36923;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36923, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36921;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36921, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36920;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36920, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36918;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36918, 5, 1, 1, 1, 2);


DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=3;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 3, 50, 1, 0, -45010, 1);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=1;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 1, 7, 1, 0, -10008, 1);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=2;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 2, 100, 1, 0, -45010, 2);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=42225;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 42225, 10, 1, 7, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36918;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36918, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36921;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36921, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36924;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36924, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36927;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36927, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36930;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36930, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36933;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36933, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36919;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36919, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36922;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36922, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36925;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36925, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36928;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36928, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36931;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36931, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36934;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36934, 0, 1, 1, 1, 1);

-- Dalaran Rings
DELETE FROM `npc_vendor` WHERE item IN(48954, 48955, 48956, 48957, 47729, 47730, 47731, 47732, 47733);
INSERT INTO `npc_vendor` VALUES 
(35495,0,47733,0,0,2685),
(35495,0,47730,0,0,2685),
(35495,0,47731,0,0,2685),
(35495,0,47729,0,0,2685),
(35495,0,47732,0,0,2685),
(35574,0,47733,0,0,2685),
(35574,0,47730,0,0,2685),
(35574,0,47731,0,0,2685),
(35574,0,47729,0,0,2685),
(35574,0,47732,0,0,2685),
(35494,0,47733,0,0,2685),
(35494,0,47730,0,0,2685),
(35494,0,47731,0,0,2685),
(35494,0,47729,0,0,2685),
(35494,0,47732,0,0,2685),
(35573,0,47733,0,0,2685),
(35573,0,47730,0,0,2685),
(35573,0,47731,0,0,2685),
(35573,0,47729,0,0,2685),
(35573,0,47732,0,0,2685),
(32172,0,47732,0,0,2685),
(32172,0,47729,0,0,2685),
(32172,0,47731,0,0,2685),
(32172,0,47730,0,0,2685),
(32172,0,47733,0,0,2685),
(32172,0,48954,0,0,2702),
(32172,0,48955,0,0,2703),
(32172,0,48956,0,0,2704),
(32172,0,48957,0,0,2705);

UPDATE `creature_loot_template` SET `item` = 45624 WHERE `item` IN (40753,40752) AND `entry` NOT IN( 33113);
UPDATE `gameobject_loot_template` SET `item` = 45624 WHERE `item` IN (40753,40752) AND `entry` NOT IN (27078);
 
UPDATE `gameobject_loot_template` SET `item` = 47241 WHERE `item` IN (40753,40752, 45624) AND `entry` IN 
(27327, 27417, 27325, 27416, 27321, 27414);

UPDATE `creature_loot_template` SET `item` = 47241 WHERE `item` IN (40753,40752,45624) AND `entry` IN (34796,
34799,
35144,
34797,
34780,
34497,
34496,
34564,35512,35513,
35347,35438,35439,35440,35447,35448,35449,35514,35515,35516,35511,
35348,35349,35350,35351,35352,34566,35615,35616,35216,35268,35269);

UPDATE `gameobject_loot_template` SET `item` = 47241 WHERE `item` IN (40753,40752, 45624) AND `entry` IN (27498, 27503, 27335, 27356);

DELETE FROM `npc_vendor` WHERE `entry` = 32172;
INSERT INTO `npc_vendor` VALUES (32172, 0, 36919, 0, 0, 2706);
INSERT INTO `npc_vendor` VALUES (32172, 0, 36922, 0, 0, 2706);
INSERT INTO `npc_vendor` VALUES (32172, 0, 36925, 0, 0, 2706);
INSERT INTO `npc_vendor` VALUES (32172, 0, 36928, 0, 0, 2484);
INSERT INTO `npc_vendor` VALUES (32172, 0, 36931, 0, 0, 2484);
INSERT INTO `npc_vendor` VALUES (32172, 0, 36934, 0, 0, 2484);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40585, 0, 0, 0);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40586, 0, 0, 0);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40678, 0, 0, 2523);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40679, 0, 0, 2523);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40680, 0, 0, 2523);
INSERT INTO `npc_vendor` VALUES (32172, 0, 40681, 0, 0, 2523);
INSERT INTO `npc_vendor` VALUES (32172, 0, 44934, 0, 0, 0);
INSERT INTO `npc_vendor` VALUES (32172, 0, 44935, 0, 0, 0);
INSERT INTO `npc_vendor` VALUES (32172, 0, 45688, 0, 0, 2592);
INSERT INTO `npc_vendor` VALUES (32172, 0, 45689, 0, 0, 2593);
INSERT INTO `npc_vendor` VALUES (32172, 0, 45690, 0, 0, 2594);
INSERT INTO `npc_vendor` VALUES (32172, 0, 45691, 0, 0, 2595);
INSERT INTO `npc_vendor` VALUES (32172, 0, 47729, 0, 0, 2685);
INSERT INTO `npc_vendor` VALUES (32172, 0, 47730, 0, 0, 2685);
INSERT INTO `npc_vendor` VALUES (32172, 0, 47731, 0, 0, 2685);
INSERT INTO `npc_vendor` VALUES (32172, 0, 47732, 0, 0, 2685);
INSERT INTO `npc_vendor` VALUES (32172, 0, 47733, 0, 0, 2685);
INSERT INTO `npc_vendor` VALUES (32172, 0, 48954, 0, 0, 2702);
INSERT INTO `npc_vendor` VALUES (32172, 0, 48955, 0, 0, 2703);
INSERT INTO `npc_vendor` VALUES (32172, 0, 48956, 0, 0, 2704);
INSERT INTO `npc_vendor` VALUES (32172, 0, 48957, 0, 0, 2705);

UPDATE `item_loot_template` SET `item` = 45624 WHERE `entry` = 54535 AND `item` = 40753;

SET @EmblemHighCURR = 47241;
SET @EmblemHighPREV = 45624;
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34797, 35447, 35448, 35449); -- Icehowl
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34780, 35216, 35268, 35269); -- Lord Jaraxxus
UPDATE `gameobject_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (27498, 27503, 27335, 27356); -- Faction Champions
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34497, 35350, 35351, 35352, 34496, 35347, 35348, 35349); -- Twin Val'kyr
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34564, 34566, 35615, 35616); -- Anub'arak

UPDATE `gameobject_loot_template` SET `item` = 45624 WHERE `entry` IN (27416,27417) AND `item` = 47241;
