DELETE FROM `creature_loot_template` WHERE `entry` = 33113 AND `item` = 40753 AND `lootmode` in (1,4,8);
DELETE FROM `creature_loot_template` WHERE `entry` = 33113 AND `item` = 45624 AND `lootmode` in (1,4,8);
INSERT INTO `creature_loot_template` VALUES
(33113, 45624, 100, 1, 3, 1, 1),
(33113, 45624, 100, 4, 2, 1, 1),
(33113, 45624, 100, 8, 2, 1, 1);
