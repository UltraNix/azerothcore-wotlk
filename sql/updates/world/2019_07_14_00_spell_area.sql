/* ALLIANCE */
DELETE FROM `spell_area` WHERE `spell`=60815;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_status`, `quest_end`, `quest_end_status`, `racemask`, `gender`, `autocast`) VALUES
-- Fate, Up Against Your Will quest
(60815, 1637, 13369, 66, 13370, 3, 1101, 2, 1), -- orgrimmar
(60815, 14, 13369, 66, 13370, 3, 1101, 2, 1), -- durotar
(60815, 1519, 13369, 2, 0, 0, 1101, 2, 1), -- stormwind
-- A Royal Coup quest
(60815, 1519, 13370, 2, 0, 0, 1101, 2, 1), -- stormwind
-- The Killing Time quest
(60815, 1519, 13371, 2, 0, 0, 1101, 2, 1), -- stormwind
(60815, 1497, 13371, 2, 13377, 11, 1101, 2, 1), -- undercity
(60815, 85, 13371, 66, 13377, 11, 1101, 2, 1), -- tirisfal glades
-- The Battle For Undercity quest
(60815, 1519, 13377, 10, 0, 0, 1101, 2, 1), -- stormwind
(60815, 1497, 13377, 10, 0, 0, 1101, 2, 1), -- undercity
(60815, 85, 13377, 10, 0, 0, 1101, 2, 1); -- tirisfal glades

/* HORDE */
DELETE FROM `spell_area` WHERE `spell`=59062;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_status`, `quest_end`, `quest_end_status`, `racemask`, `gender`, `autocast`) VALUES
-- Herald of War quest
(59062, 1637, 13257, 66, 13266, 3, 690, 2, 1), -- orgrimmar
(59062, 14, 13257, 2, 0, 0, 690, 2, 1), -- durotar
-- A Life Without Regret quest
(59062, 1497, 13266, 2, 0, 0, 690, 2, 1), -- undercity
(59062, 85, 13266, 66, 13267, 11, 690, 2, 1), -- tirisfal glades
-- The Battle For Undercity quest
(59062, 1519, 13267, 10, 0, 0, 690, 2, 1), -- stormwind
(59062, 1497, 13267, 10, 0, 0, 690, 2, 1), -- undercity
(59062, 85, 13267, 10, 0, 0, 690, 2, 1); -- tirisfal glades
