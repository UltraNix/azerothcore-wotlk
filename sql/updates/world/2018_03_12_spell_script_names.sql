DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_pal_seal_of_vengeance", "spell_pal_seal_of_corruption");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(31801, "spell_pal_seal_of_vengeance"),
(53736, "spell_pal_seal_of_corruption");
