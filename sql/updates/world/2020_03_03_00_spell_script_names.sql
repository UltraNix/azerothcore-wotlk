-- Glyph of Holy Light
DELETE FROM `spell_script_names` WHERE `spell_id` IN (54937, 54968);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(54937, "spell_pal_glyph_of_holy_light"),
(54968, "spell_pal_glyph_of_holy_light_trigger");
