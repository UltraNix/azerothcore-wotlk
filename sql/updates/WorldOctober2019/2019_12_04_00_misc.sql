-- [Quest] Water Terror - Water Terror's spells should not target players #2617 https://github.com/SunwellTracker/issues/issues/2617
DELETE FROM `conditions` WHERE `SourceEntry` = 57652;
INSERT INTO `conditions` VALUES 
(13, 2, 57652, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Water Terrors spells should not target players'),
(13, 4, 57652, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Water Terrors spells should not target players');
DELETE FROM `conditions` WHERE `SourceEntry` = 57668;
INSERT INTO `conditions` VALUES 
(13, 2, 57668, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Water Terrors spells should not target players'),
(13, 1, 57668, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Water Terrors spells should not target players');
DELETE FROM `conditions` WHERE `SourceEntry` = 57665;
INSERT INTO `conditions` VALUES 
(17, 0, 57665, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '', 'Water Terrors spells should not target players');
