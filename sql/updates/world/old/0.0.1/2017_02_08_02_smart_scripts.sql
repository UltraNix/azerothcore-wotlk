DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 18405 AND `smart_scripts`.`source_type` = 0 AND `smart_scripts`.`id` = 0 AND `smart_scripts`.`link` = 0;
DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 18405 AND `smart_scripts`.`source_type` = 0 AND `smart_scripts`.`id` = 1 AND `smart_scripts`.`link` = 0;

UPDATE `smart_scripts` SET `id` = '0' WHERE `smart_scripts`.`entryorguid` =18405 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =2 AND `smart_scripts`.`link` =0;
UPDATE `smart_scripts` SET `id` = '1' WHERE `smart_scripts`.`entryorguid` =18405 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =3 AND `smart_scripts`.`link` =0;