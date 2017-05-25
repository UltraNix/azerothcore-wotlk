-- Freezing trap effect
DELETE FROM `spell_script_names` WHERE  `spell_id`=14309;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('14309', 'spell_hun_freezing_trap_aura');