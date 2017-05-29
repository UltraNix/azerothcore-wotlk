UPDATE `creature_template` SET `minlevel` = '83', `maxlevel` = '83' WHERE `creature_template`.`entry` = 33576;
UPDATE `creature_template` SET `speed_walk` = '1', `speed_run` = '1.14' WHERE `creature_template`.`entry` =34148;

DELETE FROM `spell_script_names` WHERE `spell_script_names`.`ScriptName` = 'spell_rapid_burst_targeting';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('64532', 'spell_rapid_burst_targeting'),
('64531', 'spell_rapid_burst_targeting'),
('63387', 'spell_rapid_burst_targeting'),
('64019', 'spell_rapid_burst_targeting');