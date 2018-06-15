DELETE FROM `smart_scripts` WHERE `entryorguid` = 31279 AND `id` IN (12,13);
INSERT INTO `smart_scripts` VALUES
(31279, 0, 12, 0, 11, 0, 100, 0, 0, 0, 0, 0, 18, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Respawn - Set Immune to NPC'),
(31279, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Quest Accept - Remove Immune to NPC');
UPDATE `smart_scripts` SET `link` = 13 WHERE `entryorguid` = 31279 AND `id` = 2;
