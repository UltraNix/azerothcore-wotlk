DELETE FROM `smart_scripts` WHERE `entryorguid` = 31701 AND `id` = 9;
INSERT INTO `smart_scripts` VALUES 
(31701, 0, 9, 0, 1, 0, 100, 0, 30000, 30000, 10000, 10000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'OOC - Despawn');

DELETE FROM `conditions` WHERE `SourceEntry` = 31701;
INSERT INTO `conditions` VALUES
(22, 10, 31701, 0, 0, 29, 1, 31737, 30, 0, 1, 0, 0, '', 'Despawn Skybreaker Infantry only if Squad Leader is not near');
