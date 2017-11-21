DELETE FROM `smart_scripts` WHERE `entryorguid` = 23335 AND `id` IN (1, 2);
INSERT INTO `smart_scripts` VALUES
(23335, 0, 1, 0, 20, 0, 100, 0, 11065, 0, 0, 0, 28, 40926, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard kathie - on quest reward - remove auras'),
(23335, 0, 2, 0, 20, 0, 100, 0, 11066, 0, 0, 0, 28, 40926, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard kathie - on quest reward - remove auras');

DELETE FROM `spell_script_names` WHERE `spell_id` = 40926;
INSERT INTO `spell_script_names` VALUES
(40926, "spell_aura_wrangling_rope_channel_despawner");
