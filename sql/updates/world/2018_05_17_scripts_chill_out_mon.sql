UPDATE `smart_scripts` SET `link` = 7 WHERE `entryorguid` IN (26812,26811) AND `id` = 6;
UPDATE `smart_scripts` SET `event_type` = 61 WHERE `entryorguid` IN (26812,26811) AND `id` = 7;
UPDATE `smart_scripts` SET `event_param1` = 5000, `event_param2` = 5000 WHERE `entryorguid` = 2681200 AND `id` = 0;
UPDATE `smart_scripts` SET `link` = 10 WHERE `entryorguid` IN (26811, 26812) AND `id` = 8;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (26811, 26812) AND `id` = 10;
INSERT INTO `smart_scripts` VALUES
(26811, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 33555200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ancient Drakkari Warmonger - On Respawn - Remove Immune Flags & Not Selectable'),
(26812, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 33555200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ancient Drakkari Warmonger - On Respawn - Remove Immune Flags & Not Selectable');
