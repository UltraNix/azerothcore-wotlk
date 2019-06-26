DELETE FROM `creature_text` WHERE `entry` = 18947;
INSERT INTO `creature_text` VALUES 
(18947,0,0,'Gah! Every time I load something into the wagon, it reappears here within moments!',12,0,100,6,0,0,0,'Solanin'),
(18947,1,0,'I should have better than to have given Silanna that tome of cantrips.',12,0,100,1,0,0,0,'Solanin');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 18947 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1894700, 1894701) AND `source_type` = 9;

INSERT INTO `smart_scripts` VALUES 
(18947,0,0,0,25,0,100,0,0,0,0,0,53,0,18947,1,0,0,2,1,0,0,0,0,0,0,0,'Solanin - On Reset - Start Waypoint'),
(18947,0,1,0,40,0,100,0,1,18947,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 1 Reached - Pause Waypoint'),
(18947,0,2,3,40,0,100,0,4,18947,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 4 Reached - Pause Waypoint'),
(18947,0,3,0,61,0,100,0,4,18947,0,0,80,1894700,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 4 Reached - Run Script'),
(18947,0,4,5,40,0,100,0,7,18947,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 7 Reached - Pause Waypoint'),
(18947,0,5,0,61,0,100,0,7,18947,0,0,80,1894700,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 7 Reached - Run Script'),
(18947,0,6,0,40,0,100,0,8,18947,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 8 Reached - Pause Waypoint'),
(18947,0,7,8,40,0,100,0,11,18947,0,0,54,14000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 11 Reached - Pause Waypoint'),
(18947,0,8,0,61,0,100,0,11,18947,0,0,80,1894701,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 11 Reached - Run Script'),
(18947,0,9,0,40,0,100,0,13,18947,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Solanin - On Waypoint 13 Reached - Pause Waypoint'),
(1894700,9,0,0,0,0,100,0,3000,3000,0,0,5,16,0,0,0,0,0,1,0,0,0,0,0,0,0,'On Script - Play Emote 16'),
(1894701,9,0,0,0,0,100,0,1000,1000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.19456,'On Script - Set Orientation 3,19456'),
(1894701,9,1,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'On Script - Say Line 0'),
(1894701,9,2,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'On Script - Say Line 1');

DELETE FROM `waypoints` WHERE `entry` = 18947;
INSERT INTO `waypoints` VALUES 
(18947,1,9308.56,-6554.44,34.6806,'Solanin'),
(18947,2,9308.9,-6549.6,34.6871,'Solanin'),
(18947,3,9310.42,-6547.2,34.6966,'Solanin'),
(18947,4,9312.12,-6546.47,35.6365,'Solanin'),
(18947,5,9309.84,-6546.45,34.6963,'Solanin'),
(18947,6,9306.75,-6544.39,34.6448,'Solanin'),
(18947,7,9304.57,-6542.03,34.7358,'Solanin'),
(18947,8,9300.32,-6553.67,34.604,'Solanin'),
(18947,9,9302.13,-6550.81,34.623,'Solanin'),
(18947,10,9305.58,-6548.93,34.6424,'Solanin'),
(18947,11,9311.03,-6549.56,34.7268,'Solanin'),
(18947,12,9308.56,-6554.44,34.6806,'Solanin'),
(18947,13,9308.56,-6554.44,34.6806,'Solanin');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 18947;
