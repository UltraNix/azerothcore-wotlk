DELETE FROM `smart_scripts` WHERE `entryorguid` = 27254 AND `id` = 6;
INSERT INTO `smart_scripts` VALUES
(27254, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 91, 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Emerald Lasher - On Aggro - Remove Flag Submerge');
UPDATE `smart_scripts` SET `link` = 6 WHERE `entryorguid` = 27254 AND `id` = 4;
