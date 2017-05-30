DELETE FROM `conditions` WHERE `sourceEntry` IN (63414,63274);
INSERT INTO `conditions` VALUES 
(13, 1, 63414, 0, 0, 31, 0, 3, 33651, 0, 0, 0, 0, '', 'Spinning Up EFFECT_0 can only hit vx001'),
(13, 2, 63414, 0, 0, 31, 0, 3, 33432, 0, 0, 0, 0, '', 'Spinning Up EFFECT_1 can only hit Leviathan'),
(13, 1, 63274, 0, 0, 31, 0, 3, 33651, 0, 0, 0, 0, '', 'P3Wx2 Laser Barrage EFFECT_0 can only hit vx001');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (63274,63293);
INSERT INTO spell_script_names VALUES 
(63274,'spell_lasser_barrage_aura'),
(63293,'spell_lasser_barrage_targeting');
