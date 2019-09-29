-- Instill Lord Valthalar should target dead lord valthalar
DELETE FROM `conditions` WHERE `SourceEntry` = 27360;
INSERT INTO `conditions` VALUES
(17, 0, 27360, 0, 0, 29, 0, 16042, 20, 1, 0, 0, 0, '', 'Instill Lord Valthalar should target dead lord valthalar');
-- Enraged Feral Scar - incorrect behaviour 
UPDATE `smart_scripts` SET `action_param2` = 0 WHERE `entryorguid` = 5295 AND `id` = 1;
-- [Cosmetic] Trapped Animal
DELETE FROM `creature_template_addon` WHERE `entry` = 24196;
INSERT INTO `creature_template_addon` VALUES
(24196, 0, 0, 0, 0, 0, '74490');
-- Dalaran - Wonderworks
UPDATE creature_template SET InhabitType = 7, HoverHeight = 3 WHERE entry IN (29780, 29784, 29782, 29777, 29785, 29781); 
DELETE FROM `creature` WHERE `guid` = 103951;
