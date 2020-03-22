DELETE FROM `smart_scripts` WHERE `entryorguid` = 34196;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(34196, 0, 0, 0, 0, 0, 100, 2, 10000, 15000, 15000, 25000, 11, 64847, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Runed Flame Jets 10'),
(34196, 0, 1, 0, 0, 0, 100, 4, 10000, 15000, 15000, 25000, 11, 64988, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Runed Flame Jets 25'),
(34196, 0, 2, 0, 0, 0, 100, 2, 5000, 10000, 5000, 10000, 11, 64870, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Lava Burst 10'),
(34196, 0, 3, 0, 0, 0, 100, 4, 5000, 10000, 5000, 10000, 11, 64991, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Lava Burst 25'),
(34196, 0, 4, 0, 0, 0, 100, 2, 5000, 10000, 5000, 10000, 11, 64852, 0, 0, 0, 0, 0, 6, 60, 1, 0, 0, 0, 0, 0, 'Flaming Rune 10'),
(34196, 0, 5, 0, 0, 0, 100, 4, 5000, 10000, 5000, 10000, 11, 64990, 0, 0, 0, 0, 0, 6, 60, 1, 0, 0, 0, 0, 0, 'Flaming Rune 25');

DELETE FROM creature_template_addon WHERE entry IN (33754, 33757, 33755, 33758);
UPDATE `creature_template` SET `ScriptName` = "npc_dark_rune_ravager_thunderer" WHERE `entry` IN (33754, 33755);
