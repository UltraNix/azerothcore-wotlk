DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (13,17) AND `SourceEntry` IN (56091,56092);
INSERT INTO `conditions` VALUES
(13, 1, 56091, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '', 'Flame Spike cant be used on players'),
(13, 1, 56092, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '', 'Engulf in Flames cant be used on players'),
(17, 0, 56091, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '','Flame Spike cant be used on players'),
(17, 0, 56092, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '','Engulf in Flames cant be used on players');