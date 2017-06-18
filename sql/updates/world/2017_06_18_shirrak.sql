DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_inhibit_magic";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(32264, "spell_inhibit_magic");
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|0x00000080 WHERE `entry`=18374;