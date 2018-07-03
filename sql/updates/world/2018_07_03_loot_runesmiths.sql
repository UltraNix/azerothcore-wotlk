DELETE FROM `creature_loot_template` WHERE `entry` IN (30921,31321,30922) AND `item` = 43291;
INSERT INTO `creature_loot_template` VALUES
(30921, 43291, -70, 1, 0, 1, 2),
(31321, 43291, -40, 1, 0, 1, 1),
(30922, 43291, -0.11, 1, 0, 1, 1);
