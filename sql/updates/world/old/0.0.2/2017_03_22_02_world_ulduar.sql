DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 34003 AND `creature_loot_template`.`item` = 45086;
DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 34003 AND `creature_loot_template`.`item` = 45110;

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34352 AND `reference_loot_template`.`item` = 45086;
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34352 AND `reference_loot_template`.`item` = 45110;
INSERT INTO `reference_loot_template` (`entry` , `item` , `ChanceOrQuestChance` , `lootmode` , `groupid` , `mincountOrRef` , `maxcount`) VALUES 
('34352', '45086', '0', '1', '1', '1', '1'),
('34352', '45110', '0', '1', '1', '1', '1');

DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 33449 AND `creature_loot_template`.`item` = 45498;
DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 33449 AND `creature_loot_template`.`item` = 45511;

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34374 AND `reference_loot_template`.`item` = 45086;
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34374 AND `reference_loot_template`.`item` = 45110;
INSERT INTO `reference_loot_template` (`entry` , `item` , `ChanceOrQuestChance` , `lootmode` , `groupid` , `mincountOrRef` , `maxcount`) VALUES 
('34374', '45498', '0', '1', '1', '1', '1'),
('34374', '45511', '0', '1', '1', '1', '1');