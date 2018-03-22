DELETE FROM `smart_scripts` WHERE `entryorguid` = 19991 AND `id` IN (7,8);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (19952,21238) AND `id` IN (6,7);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (21294,19956,20116) AND `id` IN (1,2);
INSERT INTO `smart_scripts` VALUES
(19991, 0, 7, 8, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodmaul Brute - On WP Reached - Set React State'),
(19952, 0, 6, 7, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodmaul Geomancer - On WP Reached - Set React State'),
(21238, 0, 6, 7, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodmaul Drudger - On WP Reached - Set React State'),
(21294, 0, 1, 2, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodmaul Goon - On WP Reached - Set React Statet'),
(19956, 0, 1, 2, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodmaul Lookout - On WP Reached - Set React State'),
(20116, 0, 1, 2, 40, 0, 100, 0, 7, 19991, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gurn Grubnosh - On WP Reached - Set React State'),

(19991, 0, 8, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Bloodmaul Brute - On WP Reached - Attack Start'),
(19952, 0, 7, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Bloodmaul Geomancer - On WP Reached - Attack Start'),
(21238, 0, 7, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Bloodmaul Drudger - On WP Reached - Attack Start'),
(21294, 0, 2, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Bloodmaul Goon - On WP Reached - Attack Start'),
(19956, 0, 2, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Bloodmaul Lookout - On WP Reached - Attack Start'),
(20116, 0, 2, 0, 61, 0, 100, 0, 7, 19991, 0, 0, 49, 02, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0, 'Gurn Grubnosh - On WP Reached - Attack Start');

UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 19952 AND id = 5;
UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 19956 AND id = 0;
UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 19991 AND id = 6;
UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 20116 AND id = 0;
UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 21238 AND id = 5;
UPDATE `smart_scripts` SET `action_param5` = 0 WHERE `entryorguid` = 21294 AND id = 0;
