DELETE FROM `creature_text` WHERE `entry`=14509;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(14509, 0, 0, '%s dies.', 16, 0, 100, 0, 0, 0, 0, 'Thekal EMOTE_DEATH_THEKAL_P1'),
(14509, 1, 0, 'Shirvallah, fill me with your RAGE!', 14, 0, 100, 0, 0, 8419, 0, 'Thekal SAY_TRANSFORM'),
(14509, 2, 0, 'Hakkar binds me no more! Peace at last!', 14, 0, 100, 0, 0, 8424, 0, 'Thekal SAY_DEATH');
