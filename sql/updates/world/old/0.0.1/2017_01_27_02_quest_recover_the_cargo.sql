UPDATE `gameobject` SET `position_z` = '0' WHERE `gameobject`.`id` = 186283;

DELETE FROM `spell_script_names` WHERE `spell_script_names`.`ScriptName` = 'spell_q11140_salvage_wreckage';
INSERT INTO `spell_script_names` (`spell_id` ,`ScriptName`)
VALUES ('42287', 'spell_q11140_salvage_wreckage');