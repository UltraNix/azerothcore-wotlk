UPDATE `smart_scripts` SET `link` = 13 WHERE `entryorguid` = 3977 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 3977 AND `id` IN (13,14,15);
INSERT INTO `smart_scripts` VALUES
(3977, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 131, 1, 0, 0, 0, 0, 0, 14, 11875, 104591, 0, 0, 0, 0, 0, 'High Inquisitor Whitemane - On Aggro - Set GO State'),
(3977, 0, 14, 0, 25, 0, 100, 0, 0, 0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 14, 11875, 104591, 0, 0, 0, 0, 0, 'High Inquisitor Whitemane - On Reset - Set GO State'),
(3977, 0, 15, 0, 6, 0, 100, 0, 0, 0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 14, 11875, 104591, 0, 0, 0, 0, 0, 'High Inquisitor Whitemane - On Death - Set GO State');
