-- DB/NPC: Remove duplicate Goblin Commoner spawn - https://github.com/SunwellTracker/issues/issues/2848
-- DB/Quest: The Warm Up - make sure player receive credit even if killed without bear - https://github.com/SunwellTracker/issues/issues/2847
DELETE FROM `creature` WHERE `guid` = 91581;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 29352 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(29352, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 42, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kirgaraak - On Respawn - Set Invincibilty hp level');
