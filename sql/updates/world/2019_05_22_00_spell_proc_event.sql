DELETE FROM `spell_proc_event` WHERE `entry`=60485;
INSERT INTO `spell_proc_event` (`entry`, `procFlags`) VALUES
(60485, 0x00004000 | 0x00010000);
