DELETE FROM `smart_scripts` WHERE `entryorguid` = 498300 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 498301 AND `id` = 14;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4983 AND `id` IN (9,10,11,12,13);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 498302;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 498001 AND `id` IN (3,4,5,6,7);

INSERT INTO `smart_scripts` VALUES
(498300, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Script - Remove NPC Flag'),
(498301, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Script - Remove Unit flag'),
(4983, 0, 9, 0, 38, 0, 100, 0, 4, 4, 0, 0, 80, 498302, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Data Set 4 4 - Start Script'),
(498302, 9, 0, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Script - Say Line 6'),
(498302, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Script - Say Line 7'),
(498302, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 3000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Script - Despawn'),
(4983, 0, 10, 11, 11, 0, 100, 0, 0, 0, 0, 0, 81, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Respawn - Set NPC Flag'),
(4983, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 18, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ogron - On Respawn - Set NPC Flag'),
(498001, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, 4983, 0, 15, 0, 0, 0, 0, 'Paval Reethe - On Script - Set Data 4 4'),
(498001, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Paval Reethe - On Script - Kill Self'),
(498001, 9, 5, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Paval Reethe - On Script - Despawn Instant');

UPDATE `creature` SET `spawntimesecs` = 60 WHERE `guid` = 33840;
