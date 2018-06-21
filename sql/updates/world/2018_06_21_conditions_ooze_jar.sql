DELETE FROM `conditions` WHERE `SourceEntry` IN (15698,15699);
INSERT INTO `conditions` VALUES
(17, 0, 15698, 0, 0, 36, 1, 0, 0, 0, 1, 0, 0, '', 'Empty Ooze Jar should target dead mob'),
(17, 0, 15698, 0, 0, 31, 1, 3, 7086, 0, 0, 0, 0, '', 'Empty Ooze Jar should target Tainted Ooze'),
(17, 0, 15699, 0, 0, 31, 1, 3, 7092, 0, 0, 0, 0, '', 'Empty Ooze Jar should target Cursed Ooze'),
(17, 0, 15699, 0, 0, 36, 1, 0, 0, 0, 1, 0, 0, '', 'Empty Ooze Jar should target dead mob');
