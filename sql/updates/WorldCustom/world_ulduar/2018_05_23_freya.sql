SET @STONEBARK:= 65589;
SET @IRONBRANCH:= 65588;
SET @BRIGHTLEAF:= 65587;

DELETE FROM `conditions` WHERE `SourceEntry` IN (@STONEBARK, @IRONBRANCH, @BRIGHTLEAF) AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, @STONEBARK, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Stonebark essence BASE'),
(13, 1, @IRONBRANCH, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Ironbranch essence BASE'),
(13, 1, @BRIGHTLEAF, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Brightleaf essence BASE');

-- stonebark triggered
SET @STONEBARK_TRIGGERED:= 65590;

DELETE FROM `conditions` WHERE `SourceEntry` IN (@STONEBARK_TRIGGERED) AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 5, @STONEBARK_TRIGGERED, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Stonebark essence');

-- ironbranch triggered
SET @IRONBRANCH_TRIGGERED:= 65586;
DELETE FROM `conditions` WHERE `SourceEntry` IN (@IRONBRANCH_TRIGGERED) AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 3, @IRONBRANCH_TRIGGERED, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Ironbranch essence');

-- brightleaf
SET @BRIGHTLEAF_TRIGGERED:= 65585;
DELETE FROM `conditions` WHERE `SourceEntry` IN (@BRIGHTLEAF_TRIGGERED) AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 3, @BRIGHTLEAF_TRIGGERED, 0, 0, 31, 0, 3, 32906, 0, 0, 0, 0, '', 'Brightleaf essence');

DELETE FROM `spell_script_names` WHERE `spell_id` = 64606;
INSERT INTO `spell_script_names` VALUES
(64606, "spell_summon_nature_bomb_freya");
