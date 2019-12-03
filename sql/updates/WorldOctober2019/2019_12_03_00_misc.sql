-- DB/NPC: Stoic Mammoth - update loottable https://github.com/SunwellTracker/issues/issues/2614
DELETE FROM `creature_loot_template` WHERE `entry` = 30260 AND `item` = 1;
INSERT INTO `creature_loot_template` VALUES
(30260, 1, 33.9, 1, 0, -26011, 1);
