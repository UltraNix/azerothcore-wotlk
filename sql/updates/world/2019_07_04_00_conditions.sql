DELETE FROM `conditions` WHERE `SourceGroup` = 24002 AND `SourceEntry` = 33117;
DELETE FROM `conditions` WHERE `SourceGroup` = 25428 AND `SourceEntry` = 33117;
INSERT INTO `conditions` VALUES
(10, 24002, 33117, 0, 0, 12, 0, 12, 0, 0, 0, 0, 0, '', ''),
(1, 25428, 33117, 0, 0, 12, 0, 12, 0, 0, 0, 0, 0, '', '');
