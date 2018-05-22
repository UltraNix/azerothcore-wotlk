DELETE FROM `conditions` WHERE `SourceEntry` = 62705;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 7, 62705, 0, 0, 31, 0, 3, 33060, 0, 0, 0, 0, '', 'Auto-repair to Salvaged Siege Engine'),
(13, 7, 62705, 0, 1, 31, 0, 3, 33067, 0, 0, 0, 0, '', 'Auto-repair to Salvaged Siege Turret'),
(13, 7, 62705, 0, 2, 31, 0, 3, 33062, 0, 0, 0, 0, '', 'Auto-repair to Salvaged Chopper'),
(13, 7, 62705, 0, 3, 31, 0, 3, 33109, 0, 0, 0, 0, '', 'Auto-repair to Salvaged Demolisher'),
(13, 7, 62705, 0, 4, 31, 0, 3, 33167, 0, 0, 0, 0, '', 'Auto-repair to Salvaged Demolisher Mechanic Seat');
