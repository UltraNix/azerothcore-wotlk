UPDATE `creature_template` SET `unit_flags`= 4, `AIName`="", `flags_extra`=0 WHERE `entry`=2667;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryorguid`= 2667 AND `source_type`=0;
DELETE FROM `creature_template_addon` WHERE `entry`=2667;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(2667, "3825");

UPDATE `smart_scripts` SET `action_param2` = '0' WHERE `smart_scripts`.`entryorguid` =1144 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =0 AND `smart_scripts`.`link` =0;
UPDATE `smart_scripts` SET `action_param2` = '0' WHERE `smart_scripts`.`entryorguid` =1144 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =1 AND `smart_scripts`.`link` =0;