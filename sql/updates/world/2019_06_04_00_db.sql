DELETE FROM `waypoints` WHERE `entry` IN (17238,20129,28061) AND `pointid` = 0;
DELETE FROM `creature_formations` WHERE `memberguid` IN (123111,123113, 123149, 123151, 123148, 123134, 201090);
DELETE FROM `script_waypoint` WHERE `entry` IN (20129, 23348, 32491);
DELETE FROM `smart_scripts` WHERE `entryorguid` = -96556;
UPDATE `smart_scripts` SET `event_flags` = 0 WHERE `entryorguid` = 15402 AND `id` = 8;
UPDATE `smart_scripts` SET `event_flags` = 0 WHERE `entryorguid` = 16014 AND `id` = 1;
UPDATE `smart_scripts` SET `event_flags` = 0 WHERE `entryorguid` = 29358 AND `id` IN (0,1);
