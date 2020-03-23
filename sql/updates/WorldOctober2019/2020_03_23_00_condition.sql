DELETE FROM `conditions` WHERE `SourceGroup` = 1 AND `SourceEntry` = 33447;
INSERT INTO `conditions` VALUES
(22, 1, 33447, 0, 0, 29, 0, 33448, 30, 0, 1, 0, 0, '', 'Do not summon Argent Valiant if one already summoned');

DELETE FROM `conditions` WHERE `SourceGroup` = 1 AND `SourceEntry` = 33518;
INSERT INTO `conditions` VALUES
(22, 1, 33518, 0, 0, 29, 0, 33707, 30, 0, 1, 0, 0, '', 'Do not summon Argent Champion if one already summoned');
