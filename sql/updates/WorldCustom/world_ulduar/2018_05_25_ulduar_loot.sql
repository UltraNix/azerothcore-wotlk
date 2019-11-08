-- Flame leviathan 25 loot
SET @CONQUEST:= 45624;
SET @VALOR:= 40753;
SET @REFERENCE_EMBLEM_10:= 34380;
SET @EMBLEM_TO_REPLACE:= 47241;

-- reference loot template for emblems 25
UPDATE `reference_loot_template` SET `item` = @CONQUEST WHERE `entry` = 34349;

-- reference loot template for emblems 10
DELETE FROM `reference_loot_template` WHERE `entry` = @REFERENCE_EMBLEM_10;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@REFERENCE_EMBLEM_10, @VALOR, 100, 1, 0, 1, 1);

-- Flame leviathan 25
DELETE FROM `creature_loot_template` WHERE `entry` = 34003;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(34003, 1, 100, 1, 0, -34352, 3),
(34003, 2, 5, 1, 0, -34154, 1), -- patterny
(34003, 3, 100, 8, 0, -34154, 1), -- patterny

(34003, 45038, 8.5, 1, 0, 1, 1), -- fragment

(34003, 45132, 0, 16, 1, 1, 1), -- hard mode items
(34003, 45133, 0, 16, 1, 1, 1), -- hard mode items
(34003, 45134, 0, 16, 1, 1, 1), -- hard mode items
(34003, 45135, 0, 16, 1, 1, 1), -- hard mode items
(34003, 45136, 0, 16, 1, 1, 1), -- hard mode items

-- emblem group
(34003, @CONQUEST, 100, 1, 3, 1, 1),

(34003, @CONQUEST, 100, 4, 2, 1, 1),
(34003, @CONQUEST, 100, 8, 2, 1, 1),
(34003, @CONQUEST, 100, 16, 2, 2, 2),

-- runed orbs
(34003, 45087, 15, 1, 4, 1, 1),
(34003, 45087, 40, 12, 5, 1, 1),
(34003, 45087, 40, 16, 5, 1, 2);

-- flame leviathan 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33113;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33113, 2, 100, 1, 0, -34351, 2),
(33113, 5, 5, 8, 0, -34154, 1), -- patterns
(33113, 45293, 0, 16, 1, 1, 1),
(33113, 45295, 0, 16, 1, 1, 1),
(33113, 45296, 0, 16, 1, 1, 1),
(33113, 45297, 0, 16, 1, 1, 1),
(33113, 45300, 0, 16, 1, 1, 1),
(33113, 45087, 40, 12, 6, 1, 1),
(33113, 45087, 40, 16, 7, 1, 1),

-- emblems
(33113, @VALOR, 100, 1, 3, 1, 1),
(33113, @VALOR, 100, 4, 2, 1, 1),
(33113, @VALOR, 100, 8, 2, 1, 1),
(33113, @CONQUEST, 100, 16, 4, 1, 1),
(33113, @VALOR, 100, 16, 5, 1, 1);

-- Razorscale 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33186;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33186, 1, 100, 1, 0, -34355, 2),
(33186, 40753, 100, 1, 0, 1, 1);

-- Razorscale 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33724;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33724, 1, 100, 1, 0, -34356, 3),
(33724, 2, 10, 1, 0, -34154, 1),
(33724, 45038, 8.5, 1, 0, 1, 1),
(33724, 45087, 40, 1, 0, 1, 1),
(33724, 45624, 100, 1, 0, 1, 2);

-- Ignis 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33118;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33118, 1, 100, 1, 0, -34353, 2),
(33118, 40753, 100, 1, 0, 1, 1);

-- ignis 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33190;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33190, 1, 100, 1, 0, -34354, 3),
(33190, 3, 10, 1, 0, -34154, 1),
(33190, 45038, 8.5, 1, 0, 1, 1),
(33190, 45087, 40, 1, 0, 1, 1),
(33190, 45624, 100, 1, 0, 1, 1);

-- xt-002 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33293;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33293, 1, 100, 1, 0, -34357, 2),
(33293, 45867, 0, 2, 1, 1, 1),
(33293, 45868, 0, 2, 1, 1, 1),
(33293, 45869, 0, 2, 1, 1, 1),
(33293, 45870, 0, 2, 1, 1, 1),
(33293, 45871, 0, 2, 1, 1, 1),
(33293, @VALOR, 100, 1, 2, 1, 1),
(33293, @CONQUEST, 100, 2, 2, 1, 1);

-- xt-002 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33885;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33885, 1, 100, 1, 0, -34358, 3),
(33885, 2, 10, 1, 0, -34154, 1),
(33885, 45038, 8.5, 1, 0, 1, 1),
(33885, 45087, 40, 1, 0, 1, 1),
(33885, 45442, 0, 2, 1, 1, 1),
(33885, 45443, 0, 2, 1, 1, 1),
(33885, 45444, 0, 2, 1, 1, 1),
(33885, 45445, 0, 2, 1, 1, 1),
(33885, 45446, 0, 2, 1, 1, 1),
(33885, @CONQUEST, 100, 1, 2, 1, 1),
(33885, @CONQUEST, 100, 2, 3, 1, 1);


-- Assembly of iron
-- molgeim 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33692;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33692, 1, 100, 1, 0, -34360, 3),
(33692, 2, 10, 1, 0, -34154, 1),
(33692, 45038, 8.5, 1, 0, 1, 1),
(33692, 45087, 40, 1, 0, 1, 2),
(33692, 45624, 100, 1, 0, 2, 2),
(33692, 45857, 100, 1, 0, 1, 1);

-- steelbreaker 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33693;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33693, 1, 100, 1, 0, -34360, 3),
(33693, 2, 10, 1, 0, -34154, 1),
(33693, 45038, 19.5, 1, 0, 1, 1),
(33693, 45087, 40, 1, 0, 1, 3),
(33693, 45241, 0, 1, 1, 1, 1),
(33693, 45242, 0, 1, 1, 1, 1),
(33693, 45243, 0, 1, 1, 1, 1),
(33693, 45244, 0, 1, 1, 1, 1),
(33693, 45245, 0, 1, 1, 1, 1),
(33693, 45607, 0, 1, 1, 1, 1),
(33693, 45624, 100, 1, 0, 2, 2),
(33693, 45857, 100, 1, 0, 1, 1);

-- brundir 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33694;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33694, 1, 100, 1, 0, -34360, 3),
(33694, 2, 10, 1, 0, -34154, 1),
(33694, 45038, 8.5, 1, 0, 1, 1),
(33694, 45087, 40, 1, 0, 1, 1),
(33694, 45624, 100, 1, 0, 1, 1);

-- brundir 10
DELETE FROM `creature_loot_template` WHERE `entry` = 32857;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(32857, 1, 100, 1, 0, -34359, 2),
(32857, 40753, 100, 1, 0, 1, 1);

-- molgeim 10
DELETE FROM `creature_loot_template` WHERE `entry` = 32927;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(32927, 1, 100, 1, 0, -34359, 2),
(32927, 45087, 40, 1, 0, 1, 2),
(32927, 45506, 100, 1, 0, 1, 1),
(32927, 45624, 100, 1, 0, 1, 1);

-- steelbreaker 10
DELETE FROM `creature_loot_template` WHERE `entry` = 32867;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(32867, 1, 100, 1, 0, -34359, 2),
(32867, 45087, 40, 1, 0, 1, 2),
(32867, 45447, 0, 1, 1, 1, 1),
(32867, 45448, 0, 1, 1, 1, 1),
(32867, 45449, 0, 1, 1, 1, 1),
(32867, 45455, 0, 1, 1, 1, 1),
(32867, 45456, 0, 1, 1, 1, 1),
(32867, 45506, 100, 1, 0, 1, 1),
(32867, 45624, 100, 1, 0, 1, 1);


-- Kologarn
-- 10
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27061;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(27061, 1, 100, 1, 0, -34361, 2),
(27061, 40753, 100, 1, 0, 1, 1);

-- 25
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26929;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26929, 1, 100, 1, 0, -34362, 3),
(26929, 2, 10, 1, 0, -34154, 1),
(26929, 45038, 8.5, 1, 0, 1, 1),
(26929, 45087, 40, 1, 0, 1, 1),
(26929, 45624, 100, 1, 0, 1, 1);

-- Auriaya
-- 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33515;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33515, 1, 100, 1, 0, -34363, 2),
(33515, 40753, 100, 1, 0, 1, 1);

-- 25
DELETE FROM `creature_loot_template` WHERE `entry` = 34175;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(34175, 1, 100, 1, 0, -34364, 3),
(34175, 2, 10, 1, 0, -34154, 1),
(34175, 45038, 8.5, 1, 0, 1, 1),
(34175, 45087, 40, 1, 0, 1, 1),
(34175, 45624, 100, 1, 0, 1, 1);

-- Hodir
-- chest 10 normal
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27068;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27068, 1, 100, 1, 0, -34367, 1),
(27068, 2, 100, 1, 0, -12028, 1),
(27068, 40753, 100, 1, 0, 1, 1);

-- chest 10 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27069;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27069, 45624, 100, 1, 2, 1, 1),
(27069, 45786, -100, 1, 0, 1, 1),
(27069, 45876, 0, 1, 1, 1, 1),
(27069, 45877, 0, 1, 1, 1, 1),
(27069, 45886, 0, 1, 1, 1, 1),
(27069, 45887, 0, 1, 1, 1, 1),
(27069, 45888, 0, 1, 1, 1, 1);

-- chest 25 normal
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26946;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26946, 1, 100, 1, 0, -34368, 1),
(26946, 2, 100, 1, 0, -12029, 1),
(26946, 3, 10, 1, 0, -34154, 1),
(26946, 45038, 8.5, 1, 0, 1, 1),
(26946, 45087, 40, 1, 0, 1, 1),
(26946, 45624, 100, 1, 0, 1, 1);

-- chest 25 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26950;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26950, 45038, 19.5, 1, 0, 1, 1),
(26950, 45457, 0, 1, 1, 1, 1),
(26950, 45459, 0, 1, 1, 1, 1),
(26950, 45460, 0, 1, 1, 1, 1),
(26950, 45461, 0, 1, 1, 1, 1),
(26950, 45462, 0, 1, 1, 1, 1),
(26950, 45612, 0, 1, 1, 1, 1),
(26950, 45624, 100, 1, 2, 1, 1),
(26950, 45815, -100, 1, 0, 1, 1);

-- Thorim
-- chest 10 normal
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27073;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27073, 1, 100, 1, 0, -34371, 1),
(27073, 2, 100, 1, 0, -12032, 1),
(27073, 40753, 100, 1, 0, 1, 1);

-- chest 10 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27074;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27074, 1, 100, 1, 0, -34371, 1),
(27074, 2, 100, 1, 0, -12032, 1),
(27074, 45624, 100, 1, 0, 1, 1),
(27074, 45784, -100, 1, 0, 1, 1),
(27074, 45928, 0, 1, 1, 1, 1),
(27074, 45929, 0, 1, 1, 1, 1),
(27074, 45930, 0, 1, 1, 1, 1),
(27074, 45931, 0, 1, 1, 1, 1),
(27074, 45933, 0, 1, 1, 1, 1);

-- chest 25 normal
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26955;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26955, 1, 100, 1, 0, -34372, 1),
(26955, 2, 100, 1, 0, -12033, 2),
(26955, 3, 10, 1, 0, -34154, 1),
(26955, 45038, 8.5, 1, 0, 1, 1),
(26955, 45087, 40, 1, 0, 1, 1),
(26955, 45624, 100, 1, 0, 1, 1);

-- chest 25 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26956;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26956, 1, 100, 1, 0, -34372, 1),
(26956, 2, 100, 1, 0, -12033, 2),
(26956, 3, 10, 1, 0, -34154, 1),
(26956, 45038, 19.5, 1, 0, 1, 1),
(26956, 45087, 40, 1, 0, 1, 1),
(26956, 45470, 0, 1, 1, 1, 1),
(26956, 45471, 0, 1, 1, 1, 1),
(26956, 45472, 0, 1, 1, 1, 1),
(26956, 45473, 0, 1, 1, 1, 1),
(26956, 45474, 0, 1, 1, 1, 1),
(26956, 45570, 0, 1, 1, 1, 1),
(26956, 45624, 100, 1, 0, 2, 2),
(26956, 45817, -100, 1, 0, 1, 1);

-- freya elders
UPDATE `creature_template` SET `lootId` = 32914 WHERE `entry` = 32914;
UPDATE `creature_template` SET `lootId` = 33393 WHERE `entry` = 33393;
UPDATE `creature_template` SET `lootId` = 32913 WHERE `entry` = 32913;
UPDATE `creature_template` SET `lootId` = 33392 WHERE `entry` = 33392;
UPDATE `creature_template` SET `lootId` = 32915 WHERE `entry` = 32915;
UPDATE `creature_template` SET `lootId` = 33391 WHERE `entry` = 33391;
DELETE FROM `creature_loot_template` WHERE `entry` IN (32914, 33393, 32913, 33392, 32915, 33391);
INSERT INTO `creature_loot_template` VALUES
-- stonebark
(32914, @VALOR, 100, 1, 0, 1, 1),
(33393, @CONQUEST, 100, 1, 0, 1, 1),
-- ironbranch
(32913, @VALOR, 100, 1, 0, 1, 1),
(33392, @CONQUEST, 100, 1, 0, 1, 1),
-- brightleaf
(32915, @VALOR, 100, 1, 0, 1, 1),
(33391, @CONQUEST, 100, 1, 0, 1, 1);

-- freya
-- 10 0 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26961;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26961, 1, 100, 1, 0, -34365, 1),
(26961, 2, 100, 1, 0, -12026, 1),
(26961, 40753, 100, 1, 0, 1, 1),
(26961, 46110, 100, 1, 0, 1, 1);

-- 10 1 elder
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26959;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26959, 1, 100, 1, 0, -34365, 1),
(26959, 2, 100, 1, 0, -12026, 1),
(26959, 40753, 100, 1, 0, 2, 2),
(26959, 45087, 40, 1, 0, 1, 1),
(26959, 46110, 100, 1, 0, 1, 1);

-- 10 2 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27080;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27080, 1, 100, 1, 0, -34365, 1),
(27080, 2, 100, 1, 0, -12026, 1),
(27080, 3, 100, 1, 0, -34154, 1),
(27080, 40753, 100, 1, 0, 3, 3),
(27080, 45087, 40, 1, 0, 1, 1),
(27080, 46110, 100, 1, 0, 1, 1);

-- 10 3 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27078;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27078, 1, 100, 1, 0, -34365, 1),
(27078, 2, 100, 1, 0, -12026, 1),
(27078, 3, 100, 1, 0, -34154, 1),
(27078, 40753, 100, 1, 0, 4, 4),
(27078, 45087, 40, 1, 0, 1, 2),
(27078, 45294, 0, 1, 1, 1, 1),
(27078, 45788, -100, 1, 0, 1, 1),
(27078, 45943, 0, 1, 1, 1, 1),
(27078, 45945, 0, 1, 1, 1, 1),
(27078, 45946, 0, 1, 1, 1, 1),
(27078, 45947, 0, 1, 1, 1, 1),
(27078, 46110, 100, 1, 0, 1, 1),
(27078, 45624, 100, 1, 0, 1, 1);

-- 25 0 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26962;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26962, 1, 100, 1, 0, -34366, 1),
(26962, 2, 100, 1, 0, -12027, 2),
(26962, 3, 10, 1, 0, -34154, 1),
(26962, 45038, 19.5, 1, 0, 1, 1),
(26962, 45087, 20, 1, 0, 1, 1),
(26962, 45624, 100, 1, 0, 1, 1),
(26962, 46110, 100, 1, 0, 1, 1);

-- 25 1 elder
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26960;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26960, 1, 100, 1, 0, -34366, 1),
(26960, 2, 100, 1, 0, -12027, 2),
(26960, 3, 10, 1, 0, -34154, 1),
(26960, 4, 10, 1, 0, -34350, 1),
(26960, 45038, 19.5, 1, 0, 1, 1),
(26960, 45087, 40, 1, 0, 2, 2),
(26960, 45624, 100, 1, 0, 2, 2),
(26960, 46110, 100, 1, 0, 1, 1);

-- 25 2 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27081;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27081, 1, 100, 1, 0, -34366, 1),
(27081, 2, 100, 1, 0, -12027, 2),
(27081, 3, 10, 1, 0, -34350, 1),
(27081, 4, 100, 1, 0, -34154, 1),
(27081, 5, 10, 1, 0, -34154, 1),
(27081, 45038, 19.5, 1, 0, 1, 1),
(27081, 45087, 40, 1, 0, 2, 2),
(27081, 46110, 100, 1, 0, 1, 1),
(27081, @CONQUEST, 100, 1, 0, 3, 3);

-- 25 elders 3 elders
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27079;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27079, 1, 100, 1, 0, -34366, 1),
(27079, 2, 100, 1, 0, -12027, 2),
(27079, 3, 10, 1, 0, -34350, 1),
(27079, 4, 100, 1, 0, -34154, 1),
(27079, 5, 10, 1, 0, -34154, 1),
(27079, 45038, 19.5, 1, 0, 1, 1),
(27079, 45087, 40, 1, 0, 1, 3),
(27079, 45484, 0, 1, 1, 1, 1),
(27079, 45485, 0, 1, 1, 1, 1),
(27079, 45486, 0, 1, 1, 1, 1),
(27079, 45487, 0, 1, 1, 1, 1),
(27079, 45488, 0, 1, 1, 1, 1),
(27079, 45613, 0, 1, 1, 1, 1),
(27079, 45814, -100, 1, 0, 1, 1),
(27079, 46110, 100, 1, 0, 1, 1),
(27079, @CONQUEST, 100, 1, 0, 5, 5);

-- mimiron
-- 10 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27086;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27086, 1, 100, 1, 0, -34369, 1),
(27086, 2, 100, 1, 0, -12030, 1),
(27086, 45787, -100, 1, 0, 1, 1),
(27086, 45982, 0, 1, 1, 1, 1),
(27086, 45988, 0, 1, 1, 1, 1),
(27086, 45989, 0, 1, 1, 1, 1),
(27086, 45990, 0, 1, 1, 1, 1),
(27086, 45993, 0, 1, 1, 1, 1),
(27086, @CONQUEST, 100, 1, 0, 1, 1);

-- 10 normal
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27085;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(27085, 1, 100, 1, 0, -34369, 1),
(27085, 2, 100, 1, 0, -12030, 1),
(27085, @VALOR, 100, 1, 0, 1, 1);

-- 25 hard mode
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26967;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26967, 1, 100, 1, 0, -34370, 1),
(26967, 2, 100, 1, 0, -12031, 2),
(26967, 3, 10, 1, 0, -34154, 1),
(26967, 45038, 19.5, 1, 0, 1, 1),
(26967, 45087, 40, 1, 0, 1, 2),
(26967, 45494, 0, 1, 1, 1, 1),
(26967, 45495, 0, 1, 1, 1, 1),
(26967, 45496, 0, 1, 1, 1, 1),
(26967, 45497, 0, 1, 1, 1, 1),
(26967, 45620, 0, 1, 1, 1, 1),
(26967, 45663, 0, 1, 1, 1, 1),
(26967, 45816, -100, 1, 0, 1, 1),
(26967, @CONQUEST, 100, 1, 0, 2, 2);

-- General Vezax
-- 10 man
DELETE FROM `creature_loot_template` WHERE `entry` = 33271;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33271, 1, 100, 1, 0, -34373, 2),
(33271, 46032, 0, 2, 1, 1, 1),
(33271, 46033, 0, 2, 1, 1, 1),
(33271, 46034, 0, 2, 1, 1, 1),
(33271, 46035, 0, 2, 1, 1, 1),
(33271, 46036, 0, 2, 1, 1, 1),
(33271, @VALOR, 100, 4, 2, 1, 1),
(33271, @CONQUEST, 100, 2, 2, 1, 1);

-- 25 man
DELETE FROM `creature_loot_template` WHERE `entry` = 33449;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33449, 1, 100, 1, 0, -34374, 3),
(33449, 2, 10, 1, 0, -34154, 1),
(33449, 3, 10, 1, 0, -34350, 1),
(33449, 45038, 8.5, 1, 0, 1, 1),
(33449, 45516, 0, 2, 1, 1, 1),
(33449, 45517, 0, 2, 1, 1, 1),
(33449, 45518, 0, 2, 1, 1, 1),
(33449, 45519, 0, 2, 1, 1, 1),
(33449, 45520, 0, 2, 1, 1, 1),
(33449, @CONQUEST, 100, 1, 2, 1, 1);

-- Yogg Saron
-- yogg 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33288;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33288, 1, 100, 1, 0, -34375, 1),
(33288, 2, 100, 1, 0, -12034, 1),
(33288, 4, 100, 4, 0, -34350, 1),
(33288, 5, 10, 4, 0, -34154, 1),
(33288, 7, 100, 8, 0, -34154, 1),
(33288, 46067, 0, 8, 1, 1, 1),
(33288, 46068, 0, 8, 1, 1, 1),
(33288, 46095, 0, 8, 1, 1, 1),
(33288, 46096, 0, 8, 1, 1, 1),
(33288, 46097, 0, 8, 1, 1, 1),
(33288, 46312, 100, 16, 0, 1, 1),
-- valors
(33288, @VALOR, 100, 64, 2, 1, 1),
-- conquests
(33288, @CONQUEST, 100, 24, 3, 2, 2);

-- yogg 25
DELETE FROM `creature_loot_template` WHERE `entry` = 33955;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33955, 45038, 100, 1, 0, 1, 1), -- fragment
(33955, 1, 100, 1, 0, -34376, 2),
(33955, 2, 100, 1, 0, -12035, 2),
(33955, 3, 10, 1, 0, -34350, 1),
(33955, 4, 10, 1, 0, -34154, 1),

(33955, 6, 100, 4, 3, -34350, 1), -- runed orb

(33955, 8, 100, 8, 0, -34154, 1),

(33955, 45533, 0, 8, 1, 1, 1),
(33955, 45534, 0, 8, 1, 1, 1),
(33955, 45535, 0, 8, 1, 1, 1),
(33955, 45536, 0, 8, 1, 1, 1),
(33955, 45537, 0, 8, 1, 1, 1),

-- 4 keepers
(33955, 45693, 100, 16, 0, 1, 1),

-- quest
(33955, 45897, 100, 32, 0, 1, 1),

-- emblems
(33955, @CONQUEST, 100, 1, 2, 1, 1),
(33955, @CONQUEST, 100, 24, 3, 1, 1);

-- algalon 10
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27030;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27030, 1, 100, 1, 0, -34134, 3),
(27030, 46052, 100, 1, 0, 1, 1),
(27030, @CONQUEST, 100, 1, 0, 1, 1);

-- algalon 25
DELETE FROM `gameobject_loot_template` WHERE `entry` = 26974;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26974, 1, 100, 1, 0, -12023, 3),
(26974, 2, 10, 1, 0, -34154, 1),
(26974, 45038, 19.5, 1, 0, 1, 1),
(26974, 46053, 100, 1, 0, 1, 1),
(26974, @CONQUEST, 100, 1, 0, 2, 2);

-- sack of ulduar
DELETE FROM `item_loot_template` WHERE `entry` = 45875;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45875, 45087, 100, 1, 0, 1, 1),
(45875, @VALOR, 100, 1, 0, 5, 5);

-- large sack of ulduar
DELETE FROM `item_loot_template` WHERE `entry` = 45878;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45878, 45087, 100, 1, 0, 2, 2),
(45878, 45088, 0, 1, 1, 1, 1),
(45878, 45089, 0, 1, 1, 1, 1),
(45878, 45090, 0, 1, 1, 1, 1),
(45878, 45091, 0, 1, 1, 1, 1),
(45878, 45092, 0, 1, 1, 1, 1),
(45878, 45093, 0, 1, 1, 1, 1),
(45878, 45094, 0, 1, 1, 1, 1),
(45878, 45095, 0, 1, 1, 1, 1),
(45878, 45096, 0, 1, 1, 1, 1),
(45878, 45097, 0, 1, 1, 1, 1),
(45878, 45098, 0, 1, 1, 1, 1),
(45878, 45100, 0, 1, 1, 1, 1),
(45878, 45101, 0, 1, 1, 1, 1),
(45878, 45102, 0, 1, 1, 1, 1),
(45878, 45103, 0, 1, 1, 1, 1),
(45878, 45104, 0, 1, 1, 1, 1),
(45878, 45105, 0, 1, 1, 1, 1),
(45878, @CONQUEST, 100, 1, 0, 10, 10);

-- emalon 10
DELETE FROM `creature_loot_template` WHERE `entry` = 33993;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33993, 1, 100, 1, 0, -34208, 2),
(33993, 2, 1, 1, 0, -34203, 1),
(33993, @VALOR, 100, 1, 0, 2, 2);

DELETE FROM `creature_loot_template` WHERE `entry` = 33994;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33994, 1, 100, 1, 0, -34215, 4),
(33994, 2, 1, 1, 0, -34203, 1),
(33994, 47241, 100, 1, 0, 2, 2);


