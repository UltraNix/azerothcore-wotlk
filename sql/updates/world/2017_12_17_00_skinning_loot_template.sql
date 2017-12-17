DELETE FROM `skinning_loot_template` WHERE `entry` = 100008 AND `item` IN (783, 4232, 7287, 2934, 2318);
INSERT INTO `skinning_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(100008, 2318, 37, 1, 1, 1, 2),
(100008, 2934, 63, 1, 1, 1, 2);
