DELETE FROM `item_loot_template` WHERE `entry` = 43575 AND `item` IN (43611, 43612, 43613);
INSERT INTO `item_loot_template` VALUES
(43575, 43611, 0.02, 1, 0, 1, 1),
(43575, 43612, 0.01, 1, 0, 1, 1),
(43575, 43613, 0.02, 1, 0, 1, 1);