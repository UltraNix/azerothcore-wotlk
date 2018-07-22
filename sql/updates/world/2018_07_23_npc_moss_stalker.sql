UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 1780;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1780;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(1780, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 30000, 35000, 11, 7276, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Moss Stalker - In Combat - Cast \'Poison Proc\''),
(1780, 0, 1, 0, 0, 0, 100, 0, 2000, 6000, 30000, 35000, 11, 744, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Moss Stalker - In Combat - Cast \'Poison\'');
