DELETE FROM `smart_scripts` WHERE `entryorguid` = 26369;
INSERT INTO `smart_scripts` VALUES
(26369, 0, 0, 0, 0, 0, 100, 0, 3000, 7000, 5000, 9000, 11, 55079, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Imperial Eagle - In Combat - Cast \'Swoop\' (Phase 1)'),
(26369,0,1,2,8,0,100,0,49546,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0,0,0,0,"Imperial Eagle - On Spellhit 'Eagle Eyes' - Move random"),
(26369,0,2,0,61,0,100,0,0,0,0,0,41,3000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Imperial Eagle - On Spellhit 'Eagle Eyes' - Despawn In 4000 ms");

UPDATE `creature_addon` SET `auras` = "34873" WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 26369);
