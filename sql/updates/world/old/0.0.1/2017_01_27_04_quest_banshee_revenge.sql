UPDATE `gameobject_template` SET `ScriptName` = 'go_war_horn_of_jotunheim' WHERE `gameobject_template`.`entry` = 193028;
UPDATE `gameobject_template` SET `data2` = '0' WHERE `gameobject_template`.`entry` = 193028;

DELETE FROM `event_scripts` WHERE `event_scripts`.`id` = 20108; 