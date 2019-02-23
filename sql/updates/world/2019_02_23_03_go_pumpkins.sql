-- DB/GO: Remove leftover Halloween decorations from Silvermoon
DELETE FROM `game_event_gameobject` WHERE `guid` IN (78033, 78066, 78105, 78106, 78109, 78117, 78111);
INSERT INTO `game_event_gameobject` VALUES
(12, 78033),
(12, 78066),
(12, 78105),
(12, 78106),
(12, 78109),
(12, 78111),
(12, 78117);
