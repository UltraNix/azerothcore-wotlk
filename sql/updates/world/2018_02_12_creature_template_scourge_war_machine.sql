UPDATE `creature_template` SET `flags_extra` = 0, `unit_flags` = 0 WHERE `entry` = 32154;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 32154 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(32154, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''); 