-- Festergut Gastric Bloat
DELETE FROM `spell_proc_event` WHERE `entry`=72214;
INSERT INTO `spell_proc_event` (`entry`, `Cooldown`) VALUES
(72214, 14000);
