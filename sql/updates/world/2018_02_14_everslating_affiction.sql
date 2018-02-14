UPDATE `spell_proc_event` SET `procFlags`=262144 + 65536 WHERE  `entry`=-47201;
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_warl_everlasting_affliction_aura";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(-47201, "spell_warl_everlasting_affliction_aura");
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_warl_everlasting_affliction";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(47422, "spell_warl_everlasting_affliction");