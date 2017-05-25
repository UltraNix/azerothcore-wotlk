DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 19424 AND `smart_scripts`.`source_type` = 0 AND `smart_scripts`.`id` = 1 AND `smart_scripts`.`link` = 0;

UPDATE `smart_scripts` SET `id` = '1', `link` = '2' WHERE `smart_scripts`.`entryorguid` = 19424 AND `smart_scripts`.`source_type` = 0 AND `smart_scripts`.`id` =2 AND `smart_scripts`.`link` = 3;
UPDATE `smart_scripts` SET `id` = '2' WHERE `smart_scripts`.`entryorguid` = 19424 AND `smart_scripts`.`source_type` = 0 AND `smart_scripts`.`id` = 3 AND `smart_scripts`.`link` = 0;

DELETE FROM `disables` WHERE `disables`.`entry` = 34368;
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES ('0', '34368', '1', '', '', 'Summon Riding Worg prevent cheat');