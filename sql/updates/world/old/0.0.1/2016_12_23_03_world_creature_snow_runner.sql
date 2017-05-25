UPDATE `creature` SET `npcflag` = 0,`unit_flags` = 0, `MovementType` = 0, `dynamicflags` = 32 WHERE `guid` = 105491;
UPDATE `creature_template` SET `npcflag` = 0,`unit_flags` = 0, `dynamicflags` = 0, `MovementType` = 0 WHERE `entry` = 29546;
DELETE FROM `creature_addon` WHERE `guid` = 105491;

DELETE FROM `creature_template_addon` WHERE `entry` = 29546;
INSERT INTO `creature_template_addon` VALUES
(29546, 0, 0, 7, 0, 0, '');