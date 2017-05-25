UPDATE `spell_proc_event` SET `CustomChance` = '0' WHERE `spell_proc_event`.`entry` = -51940;

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_sha_earthliving_weapon';

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(-51940, 'spell_sha_earthliving_weapon');