DELETE FROM `creature_loot_template` WHERE `entry` = 32482 AND `item` = 44009; 
INSERT INTO `creature_loot_template` VALUES (32482, 44009, -0.5, 1, 0, 1, 1);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -7 WHERE `entry` = 31139 AND `item` = 44009;