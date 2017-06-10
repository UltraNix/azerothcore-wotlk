UPDATE `gameobject_template` SET `ScriptName`= 'go_blackened_urn' WHERE `entry`=194092;
UPDATE `gameobject_template` SET `flags`=`flags`|0x00000010 WHERE `entry` IN (184280, 184274);
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_rain_of_bones';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`)VALUES
(37098,'spell_rain_of_bones');
