UPDATE `smart_scripts` SET `link` = 5 WHERE `entryorguid` = 29880 AND `id` = 4;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29880 AND `id` = 5;
INSERT INTO `smart_scripts` VALUES
(29880, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jotunheim Warrion - On SpellHit - Despawn');

UPDATE `smart_scripts` SET `link` = 7 WHERE `entryorguid` = 30037 AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30037 AND `id` = 7;
INSERT INTO `smart_scripts` VALUES
(30037, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mjordin Combatant - On SpellHit - Despawn');

UPDATE `smart_scripts` SET `link` = 4 WHERE `entryorguid` = 30243 AND `id` = 3;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30243 AND `id` = 4;
INSERT INTO `smart_scripts` VALUES
(30243, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Njorndar Spear Sister - On SpellHit - Despawn');

UPDATE `smart_scripts` SET `link` = 6 WHERE `entryorguid` = 30632 AND `id` = 5;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30632 AND `id` = 6;
INSERT INTO `smart_scripts` VALUES
(30632, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mjordin Water Magus - On SpellHit - Despawn');
