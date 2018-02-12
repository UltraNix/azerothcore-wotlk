
UPDATE `creature_text` SET `sound` = 14211 WHERE `entry` = 28189 AND `groupid` = 0 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14756 WHERE `entry` = 26203 AND `groupid` = 0 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14212 WHERE `entry` = 28189 AND `groupid` = 1 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14664 WHERE `entry` = 26170 AND `groupid` = 0 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14665 WHERE `entry` = 26170 AND `groupid` = 1 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14757 WHERE `entry` = 26203 AND `groupid` = 1 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14666 WHERE `entry` = 26170 AND `groupid` = 2 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14213 WHERE `entry` = 28189 AND `groupid` = 2 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14758 WHERE `entry` = 26203 AND `groupid` = 2 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14214 WHERE `entry` = 28189 AND `groupid` = 3 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14196 WHERE `entry` = 25250 AND `groupid` = 0 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14197 WHERE `entry` = 25250 AND `groupid` = 1 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14489 WHERE `entry` = 25251 AND `groupid` = 0 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14667 WHERE `entry` = 26170 AND `groupid` = 3 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14490 WHERE `entry` = 25251 AND `groupid` = 1 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14668 WHERE `entry` = 26170 AND `groupid` = 4 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14491 WHERE `entry` = 25251 AND `groupid` = 2 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14669 WHERE `entry` = 26170 AND `groupid` = 5 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14492 WHERE `entry` = 25251 AND `groupid` = 3 AND `id` = 0;
UPDATE `creature_text` SET `sound` = 14670 WHERE `entry` = 26170 AND `groupid` = 6 AND `id` = 0;


UPDATE `smart_scripts` SET `event_param1` = 8000, `event_param2` = 8000 WHERE `entryorguid` = 2617000 AND `id` IN (8,9, 10, 11); -- 5000


DELETE FROM `smart_scripts` WHERE `entryorguid` = 26203 AND `id` = 3;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2617001;
INSERT INTO `smart_scripts` VALUES
(2617001, 9, 0, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk'),
(2617001, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 91, 255, 0, 0, 0, 0, 0, 12, 2, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Remove Bytes1'),
(2617001, 9, 2, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 45, 3, 3, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Set Data'),
(2617001, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk Target 1'),
(2617001, 9, 4, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk'),
(2617001, 9, 5, 0, 0, 0, 100, 0, 12000, 12000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 12, 2, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk Target 2'),
(2617001, 9, 6, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk Target 1'),
(2617001, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 4000, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Despawn'),
(2617001, 9, 8, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 12, 2, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Talk Target 2'),
(2617001, 9, 9, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 45, 5, 5, 0, 0, 0, 0, 12, 2, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Set Data'),
(2617001, 9, 10, 0, 0, 0, 100, 0, 500, 500, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 2, 0, 0, 0, 0, 0, 0, 'Thassarian - On Script - Attack Start');