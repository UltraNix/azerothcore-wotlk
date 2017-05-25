UPDATE `creature_template` SET `InhabitType` = '4' WHERE `creature_template`.`entry` = 33779;

DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = -136525;
DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = -136528;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-136525, 0, 0, 0, 1, 0, 100, 0, 1000, 1000, 0, 0, 11, 48310, 2, 0, 0, 0, 0, 10, 137507, 33779, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Out of Combat - Cast ''Transitus Shield Beam'' (Phase 8)'),
(-136528, 0, 0, 0, 1, 0, 100, 0, 1000, 1000, 0, 0, 11, 48310, 2, 0, 0, 0, 0, 10, 137508, 33779, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Out of Combat - Cast ''Transitus Shield Beam'' (Phase 8)');

DELETE FROM `conditions` WHERE `conditions`.`SourceTypeOrReferenceId` = 13 AND `conditions`.`SourceGroup` = 1 AND `conditions`.`SourceEntry` = 48310;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 48310, 0, 0, 31, 0, 3, 33779, 0, 0, 0, 0, '', 'Spell 48310 targets Ulduar Shield Bunny');