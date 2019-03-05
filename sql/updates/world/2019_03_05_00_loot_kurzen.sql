-- DB/Quest: Bad medicine - quest item should drop also from Kurzen Jungle Fighters
DELETE FROM `creature_loot_template` WHERE `entry` = 937 AND `item` = 2633;
INSERT INTO `creature_loot_template` VALUES
(937, 2633, 34.54, 1, 0, 1, 1);
