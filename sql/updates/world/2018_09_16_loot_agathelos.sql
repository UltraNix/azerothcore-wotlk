DELETE FROM `creature_loot_template` WHERE `entry` = 4422 AND `item` IN (6690, 6691);
INSERT INTO `creature_loot_template` VALUES 
(4422, 6690, 80, 1, 1, 1, 1),
(4422, 6691, 20, 1, 1, 1, 1);
