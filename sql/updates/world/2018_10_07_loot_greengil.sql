UPDATE `creature_template` SET `pickpocketloot` = 25084 WHERE `entry` = 25084;
DELETE FROM `creature_loot_template` WHERE `entry` = 25084 AND `item` = 4;
INSERT INTO `creature_loot_template` VALUES
(25084, 4, 40, 1, 1, -24023, 1);
