DELETE FROM `conditions` WHERE `SourceEntry` = 33924 AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 33924, 0, 0, 31, 0, 4, 0, 0, 0, 0, 0, '', 'Bleeding Hollow Tormentor\'s Fear should target player');
