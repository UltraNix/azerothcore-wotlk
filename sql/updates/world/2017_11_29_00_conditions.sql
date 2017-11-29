DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `sourceEntry` IN (24390, 24391) AND `conditionValue2` IN (179697, 180418);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 24391, 0, 151, 31, 0, 5, 179697, 0, 0, 0, 0, '', 'Opening BG visual should target gameobject'),
(13, 2, 24391, 0, 152, 31, 0, 5, 179697, 0, 0, 0, 0, '', 'Opening BG visual should target gameobject'),
(13, 1, 24390, 0, 153, 31, 0, 5, 180418, 0, 0, 0, 0, '', 'Opening BG visual should target gameobject'),
(13, 2, 24390, 0, 154, 31, 0, 5, 180418, 0, 0, 0, 0, '', 'Opening BG visual should target gameobject');
