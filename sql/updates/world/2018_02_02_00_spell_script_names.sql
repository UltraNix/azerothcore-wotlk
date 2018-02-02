DELETE FROM `spell_script_names` WHERE `spell_id` = 11504;
INSERT INTO `spell_script_names` VALUES
(11504, "spell_walking_bomb_effect");

UPDATE `smart_scripts` SET `event_param2` = 3 WHERE `entryorguid` = 7915 AND `id` = 3;
