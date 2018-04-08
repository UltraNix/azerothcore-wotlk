SET @UROM = 27655;
DELETE FROM `smart_scripts` WHERE `id` = 1 AND `entryorguid` IN (27649, 27651);
DELETE FROM `smart_scripts` WHERE `id` = 2 AND `entryorguid` IN (27642, 27647, 27650);
DELETE FROM `smart_scripts` WHERE `id` = 4 AND `entryorguid` IN (27644, 27645, 27648, 27653);
INSERT INTO `smart_scripts` VALUES
(27642, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27644, 0, 4, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27645, 0, 4, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27647, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27648, 0, 4, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27649, 0, 1, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27651, 0, 1, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27650, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom'),
(27653, 0, 4, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 27655, 0, 300, 0, 0, 0, 0, 'Urom Summon - On Death - Set Data On Urom');
