-- Shadowlord Deathwail
UPDATE `creature_addon` SET `mount` = 20684 WHERE `guid` = 77084;
UPDATE `creature_template` SET `InhabitType` = 7, `HoverHeight` = 0, `MovementType` = 2 WHERE `entry` = 22006;
UPDATE `creature` SET `MovementType` = 0 WHERE `guid` =  77084;
UPDATE `creature_addon` SET `path_id` = 0 WHERE `guid` =  77084; -- 770840
