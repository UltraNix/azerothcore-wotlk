-- DB/Spell: Warlock's Shadow Trance shouldn't be consumed instantly but only on next cast of Shadow Bolt
DELETE FROM `spell_proc` WHERE `spellId` = 17941;
INSERT INTO `spell_proc` VALUES
(17941, 0, 5, 1, 0, 0, 65536, 1, 1, 0, 8, 0, 0, 0, 1);
