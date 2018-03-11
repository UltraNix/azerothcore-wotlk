UPDATE `creature_loot_template` SET `item` = 0 WHERE `entry` = 17308 AND `mincountOrRef` = -24073;

DELETE FROM `creature_loot_template` WHERE `entry` = 17308 AND `item` = 24073 AND `mincountOrRef` = 1;
INSERT INTO `creature_loot_template` VALUES
(17308, 24073, 12, 1, 1, 1, 1);
