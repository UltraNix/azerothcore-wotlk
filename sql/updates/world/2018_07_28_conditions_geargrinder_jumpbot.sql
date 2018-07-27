DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 18 AND `SourceGroup` = 31784;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 16 AND `SourceEntry` = 31784;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 16 AND `SourceEntry` = 31736;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(16, 0, 31784, 0, 0, 23, 0, 4513, 0, 0, 0, 0, 0, '', 'Vehicle must be in area 4513'),
(18, 31784, 59593, 0, 0, 9, 0, 13283, 0, 0, 0, 0, 0,'', 'Allow spellclick if player has quest 13283'),
(16, 0, 31736, 0, 0, 23, 0, 4513, 0, 0, 0, 0, 0, '', 'Vehicle must be in area 4513');
