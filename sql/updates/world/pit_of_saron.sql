-- Forgemaster Garfrost
UPDATE `gameobject_template` SET `AIName`="", `ScriptName`="go_saronite_rock" WHERE `entry`=196485;
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=12993 AND `type` IN (11, 12, 18);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(12993,11,0,0,"achievement_garfrost_doesnt_go_to_eleven");