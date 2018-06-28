UPDATE `creature_template` SET `speed_walk` = 3, `speed_run` = 3, `spell3` = 56712 WHERE `entry` = 29736;
UPDATE `smart_scripts` SET `event_flags` = 0 WHERE `entryorguid` = 29732;
UPDATE `quest_template` SET `SourceSpellId` = 56411 WHERE `id` = 12869;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29736;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(29736, 0, 0, 1, 27, 0, 100, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On passenger boarded - set npcflag to 0'),
(29736, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 60, 1, 300, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Linked - set fly'),
(29736, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 59, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Linked - set run');

DELETE FROM `conditions` WHERE `SourceEntry` IN (29736);
INSERT INTO `conditions` VALUES
(16, 0, 29736, 0, 0, 23, 0, 4428, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 1, 23, 0, 67, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 2, 23, 0, 4452, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 3, 23, 0, 4432, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 4, 23, 0, 4476, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 5, 23, 0, 4431, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 6, 23, 0, 4422, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 7, 23, 0, 4423, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 29736, 0, 8, 23, 0, 4420, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone');
