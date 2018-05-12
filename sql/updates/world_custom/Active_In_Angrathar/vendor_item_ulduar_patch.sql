-- Stormjewel
DELETE FROM `item_loot_template` WHERE `entry` = 46007 AND `item` = 4;
INSERT INTO `item_loot_template` VALUES (46007, 4, 1, 1, 0, -10019, 1);
DELETE FROM `reference_loot_template` WHERE `entry` = 10019;
INSERT INTO `reference_loot_template` VALUES
(10019, 45862, 0, 1, 1, 1, 1),
(10019, 45879, 0, 1, 1, 1, 1),
(10019, 45880, 0, 1, 1, 1, 1),
(10019, 45881, 0, 1, 1, 1, 1),
(10019, 45882, 0, 1, 1, 1, 1),
(10019, 45883, 0, 1, 1, 1, 1),
(10019, 45987, 0, 1, 1, 1, 1);

UPDATE `item_template` SET `Flags` = `Flags` | 524288 WHERE `entry` IN (45862, 45879,45880,45881,45882,45883,45987);
-- Vendorzy w dalaranie z itemami EoC
DELETE FROM `creature` WHERE `guid` IN (86929, 85224);
INSERT INTO `creature` VALUES
(86929, 33963, 571, 1, 1, 28986, 1, 5931.55, 507.388, 650.263, 1.67552, 180, 0, 0, 1, 0, 0, 0, 0, 0),
(85224, 33964, 571, 1, 1, 28987, 1, 5762.13, 731.637, 653.748, 2.47837, 180, 0, 0, 1, 0, 0, 0, 0, 0);
-- Ringi
DELETE FROM `npc_vendor` WHERE `entry` = 32172 AND `item` IN (45691,45690,45689,45688);
INSERT INTO `npc_vendor` VALUES
(32172, 0, 45691, 0, 0, 2595),
(32172, 0, 45690, 0, 0, 2594),
(32172, 0, 45689, 0, 0, 2593),
(32172, 0, 45688, 0, 0, 2592);
