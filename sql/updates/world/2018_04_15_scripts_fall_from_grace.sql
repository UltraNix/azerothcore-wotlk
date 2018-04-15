UPDATE `smart_scripts` SET `link` = 3 WHERE `entryorguid` = 188713 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 188713 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(188713, 1, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48762, 7, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On Just Deactivated - Cast');
