DELETE FROM `spell_area` WHERE `spell` IN (73818, 73824);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(73818, 4812, 0, 0, 0, 690, 2, 1, 64, 11),
(73824, 4812, 0, 0, 0, 1101, 2, 1, 64, 11);
