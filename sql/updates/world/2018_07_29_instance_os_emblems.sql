DELETE FROM `creature_loot_template` WHERE `entry` = 28860 AND `item` = 40752;
INSERT INTO `creature_loot_template` VALUES
(28860, 40752, 100, 1, 0, 1, 1),
(28860, 40752, 100, 2, 0, 1, 1),
(28860, 40752, 100, 4, 0, 1, 1),
(28860, 40752, 100, 8, 0, 1, 1);
UPDATE `creature_template` SET `lootid` = 30452 WHERE `entry` IN (30452, 30449, 30451);
UPDATE `creature_template` SET `lootid` = 31520 WHERE `entry` IN (31520, 31534, 31535);

DELETE FROM `creature_loot_template` WHERE `entry` = 30452 AND `item` = 40752;
DELETE FROM `creature_loot_template` WHERE `entry` = 31520 AND `item` = 40753;
INSERT INTO `creature_loot_template` VALUES
(30452, 40752, 100, 1, 0, 1, 1),
(31520, 40753, 100, 1, 0, 1, 1);
