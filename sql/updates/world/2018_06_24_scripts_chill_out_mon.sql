UPDATE `smart_scripts` SET `link` = 10 WHERE `entryorguid` = 26812 AND `id` = 8;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26812 AND `id` = 10;
INSERT INTO `smart_scripts` VALUES
(26812, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 33555200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ancient Drakkari Soothsayer - On Respawn Remove - Flags Immune to Players & NPC & Not Selectable');
