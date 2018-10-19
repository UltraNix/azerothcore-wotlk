DELETE FROM `creature_loot_template` WHERE `entry` = 23682 AND `item` IN (38175, 33808);
DELETE FROM `creature_loot_template` WHERE `entry` = 23682 AND `item` IN (49126, 49128);
INSERT INTO `creature_loot_template` VALUES 
(23682, 49126, 3, 1, 3, 1, 1),
(23682, 49128, 3, 1, 3, 1, 1);
