DELETE FROM `smart_scripts` WHERE `entryorguid` = 19455 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1945500 AND `source_type` = 9;

INSERT INTO `smart_scripts` VALUES 
(19455,0,0,0,25,0,100,0,0,0,0,0,53,0,19455,1,0,0,1,0,0,0,0,0,0,0,0,'Nurse Judith - On Reset - Start Waypoint'),
(19455,0,1,0,64,0,100,0,0,0,0,0,54,180000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Gossip Hello - Pause Waypoint'),
(19455,0,2,3,40,0,100,0,2,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 2 Reached - Run Script'),
(19455,0,3,0,61,0,100,0,2,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.76273,'Nurse Judith - On Waypoint 2 Reached - Set Orientation 2,76273'),
(19455,0,4,5,40,0,100,0,5,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 5 Reached - Run Script'),
(19455,0,5,0,61,0,100,0,5,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.1529,'Nurse Judith - On Waypoint 5 Reached - Set Orientation 4,1529'),
(19455,0,5,6,40,0,100,0,7,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 7 Reached - Run Script'),
(19455,0,6,0,61,0,100,0,7,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.25502,'Nurse Judith - On Waypoint 7 Reached - Set Orientation 4.25502'),
(19455,0,7,8,40,0,100,0,9,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 9 Reached - Run Script'),
(19455,0,8,0,61,0,100,0,9,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.969,'Nurse Judith - On Waypoint 9 Reached - Set Orientation 2.969'),
(19455,0,9,10,40,0,100,0,12,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 12 Reached - Run Script'),
(19455,0,10,0,61,0,100,0,12,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.17224,'Nurse Judith - On Waypoint 12 Reached - Set Orientation 4.17224'),
(19455,0,11,12,40,0,100,0,15,19455,0,0,80,1945500,2,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Waypoint 15 Reached - Run Script'),
(19455,0,12,0,61,0,100,0,15,19455,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.1529,'Nurse Judith - On Waypoint 15 Reached - Set Orientation 2.41624'),
(1945500,9,0,0,0,0,100,0,0,0,0,0,54,12000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Script - Pause Waypoint'),
(1945500,9,1,0,0,0,100,0,4000,4000,0,0,90,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Script - Set Flag Standstate Kneel'),
(1945500,9,2,0,0,0,100,0,6000,6000,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Nurse Judith - On Script - Remove Flag Standstate Kneel');

DELETE FROM `waypoints` WHERE `entry` = 19455;
INSERT INTO `waypoints` VALUES 
(19455,1,-365.789,981.419,54.195,'Nurse Judith'),
(19455,2,-368.858,982.56,54.1727,'Nurse Judith'),
(19455,3,-363.252,980.47,54.2127,'Nurse Judith'),
(19455,4,-357.494,978.322,54.2425,'Nurse Judith'),
(19455,5,-358.948,975.922,54.243,'Nurse Judith'),
(19455,6,-357.512,973.939,54.2493,'Nurse Judith'),
(19455,7,-360.045,968.102,54.2344,'Nurse Judith'),
(19455,8,-358.571,965.26,54.2447,'Nurse Judith'),
(19455,9,-362.99,962.005,54.2135,'Nurse Judith'),
(19455,10,-352.415,973.809,54.2617,'Nurse Judith'),
(19455,11,-349.296,971.591,54.2724,'Nurse Judith'),
(19455,12,-349.964,970.224,54.2733,'Nurse Judith'),
(19455,13,-350.597,974.797,54.2635,'Nurse Judith'),
(19455,14,-362.665,981.665,54.2171,'Nurse Judith'),
(19455,15,-364.29,984.89,54.2066,'Nurse Judith');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 19455;