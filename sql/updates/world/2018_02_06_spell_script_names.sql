DELETE FROM `smart_scripts` WHERE `entryorguid` = 32154;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(32154, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourgewagon - on reset - set react state'),
(32154, 0, 2, 0, 6, 0, 100, 1, 0, 1, 0, 0, 11, 52324, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourgewagon - on death - cast 52324');

DELETE FROM `spell_script_names` WHERE `spell_id` = 52324;
INSERT INTO `spell_script_names` VALUES
(52324, "spell_scourgewagon_explosion");

UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 33554432 WHERE `entry` = 32154;
