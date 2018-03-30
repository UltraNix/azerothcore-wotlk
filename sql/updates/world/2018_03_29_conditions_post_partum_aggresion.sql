DELETE FROM `conditions` WHERE `SourceEntry` = 51752 AND `SourceTypeOrReferenceId` = 13;
DELETE FROM `conditions` WHERE `SourceEntry` IN (51751,51756) AND `SourceTypeOrReferenceId` = 17;
INSERT INTO `conditions` VALUES
(17, 0, 51756, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '', 'mammoth spell cannot attack player'),
(17, 0, 51751, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '', 'mammoth spell cannot attack player'),
(13, 1, 51752, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'mammoth spell cannot attack player'),
(13, 4, 51752, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'mammoth spell cannot attack player');
