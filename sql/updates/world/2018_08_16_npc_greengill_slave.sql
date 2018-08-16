DELETE FROM `creature_loot_template` WHERE `entry` = 25084 AND `item` = 24476;
INSERT INTO `creature_loot_template` VALUES
(25084, 24476, 17, 1, 0, 1, 1);
DELETE FROM `pickpocketing_loot_template` WHERE `entry` = 25084;
INSERT INTO `pickpocketing_loot_template` VALUES
(25084, 16885, 37, 1, 0, 1, 1),
(25084, 5435, 37, 1, 0, 1, 1),
(25084, 8959, 27, 1, 0, 1, 1),
(25084, 3928, 5, 1, 0, 1, 1),
(25084, 7910, 3, 1, 0, 1, 1);
