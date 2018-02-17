UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.2 WHERE `entry` = 29834 AND `item` = 26001;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.2 WHERE `entry` = 29834 AND `item` = 26002;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.2 WHERE `entry` = 29834 AND `item` = 26010;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.2 WHERE `entry` = 29834 AND `item` = 26011;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.2 WHERE `entry` = 29834 AND `item` = 26012;

DELETE FROM `creature_loot_template` WHERE `entry` = 29834 AND `item` IN (SELECT `item` FROM `reference_loot_template` WHERE `entry` IN (26001,26002,26010,26011,26012,26040));
