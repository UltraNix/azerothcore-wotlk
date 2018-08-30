UPDATE `creature_template` SET `lootid` = 33773 WHERE `entry` = 33773;
DELETE FROM `creature_loot_template` WHERE `entry` = 33772 AND `item` = 200036;
DELETE FROM `creature_loot_template` WHERE `entry` = 33773;
INSERT INTO `creature_loot_template` VALUES
(33773, 45912, 0.1, 1, 0, 1, 1),
(33773, 200036, 3, 1, 0, -34155, 1);
