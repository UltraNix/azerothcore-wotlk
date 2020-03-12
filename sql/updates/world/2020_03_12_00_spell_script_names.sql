-- Consume Shadows
DELETE FROM `spell_script_names` WHERE `spell_id`=-17767;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(-17767, "spell_warl_consume_shadows");
