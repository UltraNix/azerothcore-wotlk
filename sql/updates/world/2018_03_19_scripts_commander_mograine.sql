UPDATE `smart_scripts` SET `link` = 13 WHERE `entryorguid` = 3976 AND `id` = 3;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 3976 AND `id` IN (13,14);
INSERT INTO `smart_scripts` VALUES
(3976, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 131, 1, 0, 0, 0, 0, 0, 14, 11875, 104591, 0, 0, 0, 0, 0, 'Scarlet Commander Mograine - On Aggro - Set GO State'),
(3976, 0, 14, 0, 25, 0, 100, 0, 0, 0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 14, 11875, 104591, 0, 0, 0, 0, 0, 'Scarlet Commander Mograine - On Reset - Set GO State');
