DELETE FROM `creature_equip_template` WHERE `creature_equip_template`.`entry` = 31651;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(31651, 1, 2179, 0, 42775, 18019);

DELETE FROM `creature_equip_template` WHERE `creature_equip_template`.`entry` = 31650;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(31650, 1, 12183, 0, 0, 18019);

UPDATE `creature_template` SET `InhabitType` = '8' WHERE `creature_template`.`entry` =31526;