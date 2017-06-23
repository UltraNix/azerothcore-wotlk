-- Allows achievement Torch Juggler
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=6937;
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES
(6937, 16, 341, 0, '');
-- Spell link for Throw Torch with on hit trigger Juggle Torch for the target
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=45276;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(45819, 45276, 0, 'Throw Torch with on hit trigger Juggle Torch for the target');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry` IN (45276);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,45276,0,0,31,0,4,0,0,0,0,'','Torch juggler target can be only player');