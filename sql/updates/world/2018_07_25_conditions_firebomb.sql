DELETE FROM `conditions` WHERE `SourceEntry` = 59234;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 59234, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Fire Bomb should not target players'),
(13, 2, 59234, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Fire Bomb should not target players');
