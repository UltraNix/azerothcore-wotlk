-- fix to something else, already added to sunwell DB and reloaded
DELETE FROM `spell_proc_event` WHERE `entry` = 66073;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(66073, 0, 0, 0, 0, 0, 4, 51, 0, 100, 0);

UPDATE `smart_scripts` SET `action_type` = 99, `action_param1` = 2 WHERE `entryorguid` = 2407700 AND `id` = 0;