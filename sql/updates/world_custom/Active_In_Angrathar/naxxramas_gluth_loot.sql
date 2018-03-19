DELETE FROM `creature_loot_template` WHERE `entry` = 29417 AND `item` = 2;
INSERT INTO `creature_loot_template` VALUES
(29417, 2, 100, 1, 0, -50018, 2);
DELETE FROM `creature_loot_template` WHERE `entry` = 29417 AND `item` IN (40639,40638,40637,40636,40635,40634,40627,40626,40625);
DELETE FROM `reference_loot_template` WHERE `entry` = 50018;
INSERT INTO `reference_loot_template` VALUES
(50018, 40639, 0, 1, 1, 1, 1),
(50018, 40638, 0, 1, 1, 1, 1),
(50018, 40637, 0, 1, 1, 1, 1),
(50018, 40636, 0, 1, 1, 1, 1),
(50018, 40635, 0, 1, 1, 1, 1),
(50018, 40634, 0, 1, 1, 1, 1),
(50018, 40627, 0, 1, 1, 1, 1),
(50018, 40626, 0, 1, 1, 1, 1),
(50018, 40625, 0, 1, 1, 1, 1);
