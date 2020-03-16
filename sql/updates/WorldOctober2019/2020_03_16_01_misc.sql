-- DB/NPC: Zerillis - fix spawning in textures - https://github.com/SunwellTracker/issues/issues/2954
UPDATE `creature_addon` SET `path_id` = 0 WHERE `guid` = 138256;
UPDATE `creature` SET `MovementType` = 0 WHERE `guid` = 138256;