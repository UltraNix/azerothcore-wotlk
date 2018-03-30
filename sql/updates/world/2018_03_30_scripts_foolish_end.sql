DELETE FROM `smart_scripts` WHERE `entryorguid` = 25729 AND `id` = 7 AND `event_param1` = 45923;
UPDATE `smart_scripts` SET `id` = 7 WHERE `entryorguid` = 25729 AND `id` = 8 AND `event_type` = 61;
UPDATE `smart_scripts` SET `id` = 8 WHERE `entryorguid` = 25729 AND `id` = 9 AND `event_type` = 38;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25729 AND `id` in (9,10);
INSERT INTO `smart_scripts` VALUES
(25729, 0, 9, 0, 58, 0, 100, 0, 16, 25729, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On WP Ended - Remove flag'),
(25729, 0, 10, 0, 38, 0, 100, 0, 2, 2, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 25618, 30, 0, 0, 0, 0, 0, 'On Data Set - Attack Start');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 2561800 AND `id` IN (23,24,25,26,27);
INSERT INTO `smart_scripts` VALUES
(2561800, 9, 23, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 25729, 30, 0, 0, 0, 0, 0, 'Script9 - Set Data'),
(2561800, 9, 24, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 25751, 30, 0, 0, 0, 0, 0, 'Script9 - Attack Start'),
(2561800, 9, 25, 0, 0, 0, 100, 0, 100000, 100000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 19, 25729, 100, 0, 0, 0, 0, 0, 'Script9 - Fail Check'),
(2561800, 9, 26, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 19, 25751, 100, 0, 0, 0, 0, 0, 'Script9 - Fail Check'),
(2561800, 9, 27, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Script9 - Fail Check');
