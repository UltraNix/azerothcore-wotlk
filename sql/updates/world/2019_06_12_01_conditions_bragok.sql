DELETE FROM conditions WHERE SourceEntry = 16227 AND SourceTypeOrReferenceId = 22;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
(22, 1, 16227, 0, 1, 29, 0, 9526, 100, 0, 1, 0, 0, '', 'SAI triggers only if gryphon or wyvern is not nearby'),
(22, 1, 16227, 0, 1, 29, 0, 9297, 100, 0, 1, 0, 0, '', 'SAI triggers only if gryphon or wyvern is not nearby');
