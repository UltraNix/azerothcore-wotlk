DELETE FROM `event_scripts` WHERE `id`= 10362;

DELETE FROM `spell_script_names` WHERE `spell_id`= 29297;
INSERT INTO `spell_script_names` (`spell_id` , `ScriptName` ) VALUES
('29297', 'spell_gen_cleansing_vial');

UPDATE `creature_template` SET `ScriptName` = 'npc_aggonis' WHERE `creature_template`.`entry` = 17000;