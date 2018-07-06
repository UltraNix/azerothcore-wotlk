UPDATE `creature` SET `unit_flags` = 536870912 | 768 WHERE `guid` = 117222;
DELETE FROM `creature_addon` WHERE `guid` = 117222;
INSERT INTO `creature_addon` VALUES
(117222, 0, 0, 0, 0, 0, '58951');
