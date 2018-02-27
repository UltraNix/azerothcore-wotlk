DELETE FROM `spell_proc_event` WHERE entry IN (58835, 57935, 57988, 57948, 58853);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (58835, 57935);
INSERT INTO `spell_script_names` VALUES
(58835, "spell_twilight_torment_proc_damage"),
(57935, "spell_twilight_torment_proc_damage");
