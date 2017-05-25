UPDATE `gameobject_template` SET `ScriptName` = 'go_lard_picnic_basket' WHERE `gameobject_template`.`entry` = 179910;
UPDATE `gameobject_template` SET `data2` = '0' WHERE `gameobject_template`.`entry` = 179910;

DELETE FROM `event_scripts` WHERE `event_scripts`.`id` = 8605; 