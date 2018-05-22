DELETE FROM `conditions` WHERE `SourceEntry` = 62834;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 62834, 0, 0, 32, 0, 144, 0, 0, 0, 0, 0, '', 'Boombot Boom - Player target'),
(13, 1, 62834, 0, 3, 31, 0, 3, 33343, 0, 0, 0, 0, '', 'Boombot Boom - Scrapbot target'),
(13, 1, 62834, 0, 4, 31, 0, 3, 33344, 0, 0, 0, 0, '', 'Boombot Boom - Pummeler target'),
(13, 1, 62834, 0, 5, 31, 0, 3, 33346, 0, 0, 0, 0, '', 'Boombot Boom - Boombot target'),
(13, 1, 62834, 0, 2, 31, 0, 3, 33329, 0, 0, 0, 0, '', 'Boombot Boom - Heart of the Deconstructor target'),
(13, 1, 62834, 0, 1, 31, 0, 3, 33293, 0, 0, 0, 0, '', 'Boombot Boom - XT-002 target');
