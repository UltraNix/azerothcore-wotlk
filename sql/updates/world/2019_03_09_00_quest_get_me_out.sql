UPDATE `smart_scripts` SET `link` = 14 WHERE `entryorguid` = 12277 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 12277 AND `id` = 14;
INSERT INTO `smart_scripts` VALUES 
(12277, 0, 14, 0, 61, 0, 100, 0, 58, 1227700, 0, 0, 15, 6132, 0, 0, 0, 0, 0, 17, 0, 30, 0, 0, 0, 0, 0, 'Melizza Brimbuzzle - On Waypoint 3 Reached - Quest Credit \'Get Me Out of Here!\'');
