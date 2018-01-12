DELETE FROM `smart_scripts` WHERE `entryorguid` = 36551;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(36551, 0, 0, 1, 25, 0, 100, 6, 0, 0, 0, 0, 11, 69105, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - On Reset - Cast \'Soul Horror Visual\' (Dungeon)'),
(36551, 0, 1, 2, 61, 0, 100, 6, 0, 0, 0, 0, 11, 69136, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - On Reset - Cast \'Spiteful Apparition Visual\' (Dungeon)'),
(36551, 0, 2, 0, 61, 0, 100, 6, 0, 0, 0, 0, 11, 41253, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - On Reset - Cast \'Greater Invisibility\' (Dungeon)'),
(36551, 0, 3, 0, 10, 0, 100, 518, 0, 20, 3000, 4000, 28, 41253, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - Within 0-20 Range Out of Combat LoS - Remove Aura \'Greater Invisibility\' (Dungeon)'),
(36551, 0, 4, 0, 0, 0, 100, 2, 7000, 9000, 7000, 9000, 11, 68895, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - In Combat - Cast \'Spite\' (Normal)'),
(36551, 0, 5, 0, 0, 0, 100, 4, 7000, 9000, 7000, 9000, 11, 70212, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spiteful Apparition - In Combat - Cast \'Spite\' (Heroic)');

UPDATE `creature` SET `spawndist` = 8, `MovementType` = 1 WHERE `id` = 36967;
UPDATE `creature_template` SET `flags_extra` = 2, `unit_flags` = `unit_flags` | 33554432, `AIName` = "SmartAI", `MovementType` = 1 WHERE `entry` = 36967;
