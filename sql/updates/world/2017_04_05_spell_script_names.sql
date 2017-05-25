-- Rogue Vanish
DELETE FROM spell_script_names WHERE spell_id IN(1856);
INSERT INTO `spell_script_names` (`spell_id` , `ScriptName` ) VALUES ('1856', 'spell_rog_vanish')