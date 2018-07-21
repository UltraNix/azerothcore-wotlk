UPDATE `smart_scripts` SET `action_param2` = 3, `event_flags` = 1 WHERE `entryorguid` = 30169 AND `id` = 1;
UPDATE `smart_scripts` SET `target_param2` = 2 WHERE `entryorguid` = 30169 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30169 AND `id` = 4;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30169, 0, 4, 0, 11, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 20, 192127, 2, 0, 0, 0, 0, 0, 'Respawn - Despawn GO');
