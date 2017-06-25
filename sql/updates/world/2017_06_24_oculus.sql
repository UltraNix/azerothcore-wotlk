-- Drakos
DELETE FROM `creature_text` WHERE `entry`=27654 AND `groupid`=5 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(27654, 5, 0, '%s begins to cast Magic Pull!', 41, 0, 100, 0, 0, 0, 0, 'drakos EMOTE_MAGIC_PULL');

