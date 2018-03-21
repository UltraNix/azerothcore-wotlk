DELETE FROM `spell_script_names` WHERE `spell_id` = 48794;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(48794,'spell_q12279_cast_net');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 189290;
UPDATE `gameobject_template` SET `AIName` = "" WHERE `entry` = 189290;
