UPDATE `item_template` SET `Quality` = '4' WHERE `item_template`.`entry` =23162;
UPDATE `item_template` SET `Quality` = '4' WHERE `item_template`.`entry` =46779;
UPDATE `item_template` SET `Quality` = '4' WHERE `item_template`.`entry` =38233;

UPDATE `creature_template` SET `minlevel` = '83', `maxlevel` = '83', `dmg_multiplier` = '400', `Health_mod` = '3500', `lootid` = '18338',  `ScriptName` = 'boss_highlord_kruul' WHERE `creature_template`.`entry` = 18338;

DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 18338;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(18338, 40753, 100, 0, 0, 2, 2),
(18338, 23162, 100, 0, 0, 1, 1),
(18338, 43346, 100, 0, 0, 1, 1),
(18338, 43347, 100, 0, 0, 1, 1),
(18338, 54847, 30,  0, 0, 1, 1),
(18338, 49693, 30,  0, 0, 1, 1),
(18338, 13584, 30,  0, 0, 1, 1),
(18338, 37719, 30,  0, 0, 1, 1),
(18338, 46779, 100, 0, 0, 10, 10),
(18338, 38233, 100, 0, 0, 10, 10),
(18338, 54452, 50,  0, 0, 1, 1),
(18338, 35227, 20,  0, 0, 1, 1),
(18338, 23709, 100, 0, 1, 1, 1),
(18338, 38310, 100, 0, 1, 1, 1),
(18338, 23705, 100, 0, 1, 1, 1),
(18338, 38309, 100, 0, 1, 1, 1),
(18338, 38311, 100, 0, 1, 1, 1),
(18338, 38576, 5, 0, 3, 1, 1),
(18338, 23720, 5, 0, 3, 1, 1),
(18338, 33809, 5, 0, 3, 1, 1),
(18338, 33225, 1, 0, 3, 1, 1);

DELETE FROM `creature` WHERE `creature`.`id` = 18338;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- Stonetalon Mountains
(NULL, 18338, 1, 1, 300, 0, 0, 21.372627, -664.018127, -26.755596, 2.082048, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Feralas
(NULL, 18338, 1, 1, 300, 0, 0, -4281.869141, -804.157837, -54.787910, 2.085063, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Winterspring
(NULL, 18338, 1, 1, 300, 0, 0, 7891.474609, -4130.862793, 687.960632, 0.566674, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Desolace 
(NULL, 18338, 1, 1, 300, 0, 0, -551.035889, 2333.394775, 88.941414, 0.350288, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Redridge Mountains
(NULL, 18338, 0, 1, 300, 0, 0, -9059.951172, -2550.071533, 123.718903, 0.350288, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Badlands
(NULL, 18338, 0, 1, 300, 0, 0, -6431.359863, -3299.984863, 241.667023, 2.740570, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Wetlands
(NULL, 18338, 0, 1, 300, 0, 0, -2913.379639, -1302.009277, 9.146076, 3.594296, 28800, 10, 0, 0, 0, 0, 0, 0, 0), 
-- Lochmodan
(NULL, 18338, 0, 1, 300, 0, 0, -4974.830078, -2777.049316, 325.741730, 0.721297, 28800, 10, 0, 0, 0, 0, 0, 0, 0),
-- Durotar
(NULL, 18338, 1, 1, 300, 0, 0, 1375.238892, -4370.548828, 26.024982, 0.123965, 28800, 10, 0, 0, 0, 0, 0, 0, 0),
-- Elwynn Forest
(NULL, 18338, 0, 1, 300, 0, 0, -9071.675781, 427.454132, 93.056282, 0.652231, 28800, 10, 0, 0, 0, 0, 0, 0, 0); 