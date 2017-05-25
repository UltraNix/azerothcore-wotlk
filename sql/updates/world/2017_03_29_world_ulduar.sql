UPDATE `reference_loot_template` SET `item` = '45464' WHERE `reference_loot_template`.`entry` =34367 AND `reference_loot_template`.`item` =45454;
UPDATE `creature_loot_template` SET `item` = '9', `mincountOrRef` = '-34350' WHERE `creature_loot_template`.`entry` =33955 AND `creature_loot_template`.`item` =45624;
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` =33955 AND `creature_loot_template`.`item` =40753;

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 33963 AND `npc_vendor`.`item` = 45087;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 33964 AND `npc_vendor`.`item` = 45087;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES 

('33963', '0', '45087', '0', '0', '2604'),
('33964', '0', '45087', '0', '0', '2604');

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34156 AND `reference_loot_template`.`item` = 7