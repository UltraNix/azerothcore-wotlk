DELETE FROM `spelldifficulty_dbc` WHERE `id`=72370;
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`, `spellid2`, `spellid3`) VALUES
(72370, 72370, 72370, 72371, 72371);
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_deathbringer_blood_power";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72370, "spell_deathbringer_blood_power"),
(72371, "spell_deathbringer_blood_power");
