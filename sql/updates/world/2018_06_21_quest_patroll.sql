UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 28039;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 28039;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(28039, 0, 0, 1, 19, 0, 100, 0, 12596, 0, 0, 0, 85, 51506, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - reset quest'),
(28039, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 85, 51509, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - reset quest'),
(28039, 0, 4, 5, 19, 0, 100, 0, 12501, 0, 0, 0, 85, 53712, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53713, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53715, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53716, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 51573, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - cast On Patrol'),
(28039, 0, 10, 11, 19, 0, 100, 0, 12563, 0, 0, 0, 85, 53713, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 11, 12, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53712, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 12, 13, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53715, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 13, 14, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53716, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 51573, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - cast On Patrol'),
(28039, 0, 16, 17, 19, 0, 100, 0, 12587, 0, 0, 0, 85, 53715, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 17, 18, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53712, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 18, 19, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53713, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 19, 20, 61, 0, 100, 0, 0, 0, 0, 0, 85, 53716, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Troll Patrol - reset quest'),
(28039, 0, 20, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 51573, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - cast On Patrol'),
(28039, 0, 21, 22, 20, 0, 100, 0, 12604, 0, 0, 0, 28, 51573, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - remove aura On Patrol'),
(28039, 0, 22, 0, 61, 0, 100, 0, 0, 0, 0, 0, 28, 53707, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Commander Kunz - on quest accept Patrol - remove aura On Patrol dummy');

UPDATE `quest_template` SET `RewardSpellCast` = 53707 WHERE `id` IN (12501,12596,12563,12587,12604);

DELETE FROM `conditions` WHERE `SourceEntry` = 53707;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 53707, 0, 0, 31, 1, 4, 0, 0, 0, 0, 0, '', 'Patroll dummy should target players');

DELETE FROM `conditions` WHERE `SourceEntry` = 12604;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19, 0, 12604, 0, 0, 1, 0, 51573, 0, 0, 0, 0, 0, '', 'Show quest Congratulations! if player has aura On Patrol'),
(20, 0, 12604, 0, 0, 1, 0, 51573, 0, 0, 0, 0, 0, '', 'Show quest mark for Congratulations! if player has aura On Patrol'),
(19, 0, 12604, 0, 0, 1, 0, 53707, 0, 0, 0, 0, 0, '', 'Show quest Congratulations! if player has aura On Patrol'),
(20, 0, 12604, 0, 0, 1, 0, 53707, 0, 0, 0, 0, 0, '', 'Show quest mark for Congratulations! if player has aura On Patrol');
