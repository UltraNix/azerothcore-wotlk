UPDATE `creature_loot_template` SET `mincountOrRef` = -34143, `maxcount` = 2 WHERE `entry` = 29448 AND `item` = 1;
UPDATE `creature_loot_template` SET `maxcount` = 2 WHERE `entry` = 29718 AND `item` = 1;

DELETE FROM `gameobject_loot_template` WHERE `entry` = 25193;
INSERT INTO `gameobject_loot_template` VALUES
(25193, 34146, 100, 1, 0, -34146, 2),
(25193, 30001, 100, 1, 0, -30001, 2),
(25193, 40753, 100, 1, 0, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry` = 30001;
INSERT INTO `reference_loot_template` VALUES
(30001, 40625, 0, 1, 1, 1, 1),
(30001, 40626, 0, 1, 1, 1, 1),
(30001, 40627, 0, 1, 1, 1, 1);
