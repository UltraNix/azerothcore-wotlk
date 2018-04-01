UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 191458;
UPDATE `smart_scripts` SET `link` = 13 WHERE `entryorguid` = 28998 AND `id` = 11;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28998 AND `id` = 13;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 191458 AND `source_type` = 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 202357 AND `source_type` = 1 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(28998, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, 28931, 0, 100, 0, 0, 0, 0, 'Overlord Drakuru - OOC - Set Data On Trolls'),
(191458, 1, 0, 0, 1, 0, 100, 0, 120000, 120000, 120000, 120000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Skull - OOC -Despawn'),
(202357, 1, 1, 0, 1, 0, 100, 0, 120000, 120000, 120000, 120000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakurus Last Wish - OOC -Despawn');
