DELETE FROM `conditions` WHERE `sourceEntry` = 27661 AND `SourceTypeOrReferenceId` IN (16, 22);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 18 AND `SourceGroup` = 27661;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(18, 27661, 48365, 0, 0, 9, 0, 12325, 0, 0, 0, 0, 0, '', 'Show spell click if player has quest 12325'),
(18, 27661, 48365, 0, 1, 31, 0, 3, 27662, 0, 0, 0, 0, '', 'OR creatures entry is 27662, vehicle accessory');

DELETE FROM `conditions` WHERE `SourceEntry` = 27661 AND `SourceTypeOrReferenceId` = 22;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(22, 1, 27661, 0, 0, 31, 0, 4, 0, 0, 0, 0, 0, '', 'Run sai Action Invoker is a player');


DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 27661;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(27661, 48365, 1, 0);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 27661;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(27661, 0, 0, 1, 73, 0, 100, 0, 0, 0, 0, 0, 53, 1, 27661, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - On SpellClick - Start WP'),
(27661, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, ''),
(27661, 0, 2, 0, 40, 0, 100, 0, 20, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - On WP Reached - Despawn');

DELETE FROM `vehicle_template_accessory` WHERE `entry` = 27661;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(27661, 27662, 1, 0, 'Wintergarde Gryphon', 6, 30000);
