DELETE FROM `smart_scripts` WHERE `entryorguid` = 19493 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(19493, 0, 3, 0, 1, 0, 100, 0, 300000,300000,300000,300000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ekkorash the Inquisitor');

DELETE FROM `conditions` WHERE `SourceEntry` = 34992;
INSERT INTO `conditions` VALUES
(17, 0, 34992, 0, 0, 29,0, 19493 ,30, 0,1, 0, 0, '', 'Conjuring Powder useable only when Ekkorash the Inquisitor not near');
