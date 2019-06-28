DELETE FROM `smart_scripts` WHERE `entryorguid` = 25258 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (2525800, 2525801, 2525802, 2525803) AND `source_type` = 9;

INSERT INTO `smart_scripts` VALUES 
(25258,0,0,0,34,0,100,1,2,5,0,0,80,2525800,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Reached Point 5 - Run Script (No Repeat)'),
(25258,0,1,0,34,0,100,0,2,9,0,0,80,2525801,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Reached Point 9 - Run Script'),
(25258,0,2,0,34,0,100,0,2,10,0,0,80,2525802,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Reached Point 10 - Run Script'),
(25258,0,3,0,34,0,100,1,2,15,0,0,12,25260,3,180000,0,0,0,8,0,0,0,2255.77,5186.26,11.4391,1.47479,'Footman Rob - On Reached Point 15 - Summon Creature \'Footman Mitch\' (No Repeat)'),
(25258,0,4,0,34,0,100,0,2,17,0,0,80,2525803,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Reached Point 17 - Run Script'),
(25258,0,5,0,17,0,100,0,25260,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'Footman Rob - On Summoned Unit - Store Targetlist'),
(25258,0,6,0,1,0,100,1,100,100,0,0,71,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - Out of Combat - Change Equipment (No Repeat)'),
(25258,0,7,0,1,0,100,1,100,100,0,0,71,0,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - Out of Combat - Change Equipment (No Repeat)'),
(25258,0,8,0,1,0,100,1,100,100,0,0,71,0,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - Out of Combat - Change Equipment (No Repeat)'),
(2525800,9,0,0,0,0,100,0,3000,3000,0,0,1,0,6000,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Say Line 0'),
(2525800,9,1,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Say Line 0'),
(2525801,9,0,0,0,0,100,0,4000,4000,0,0,1,1,6000,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Say Line 1'),
(2525801,9,1,0,0,0,100,0,6000,6000,0,0,1,0,6000,0,0,0,0,10,110613,25245,0,0,0,0,0,'Footman Rob - On Script - Say Line 0'),
(2525801,9,2,0,0,0,100,0,6000,6000,0,0,1,2,6000,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Say Line 2'),
(2525801,9,3,0,0,0,100,0,6000,6000,0,0,1,1,6000,0,0,0,0,10,110613,25245,0,0,0,0,0,'Footman Rob - On Script - Say Line 1'),
(2525801,9,4,0,0,0,100,0,3000,3000,0,0,5,397,0,0,0,0,0,10,110613,25245,0,0,0,0,0,'Footman Rob - On Script - Play Emote 397'),
(2525801,9,5,0,0,0,100,0,7000,7000,0,0,17,423,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 423'),
(2525801,9,6,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,7,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,8,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,9,0,0,0,100,0,5000,5000,0,0,17,423,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 423'),
(2525801,9,10,0,0,0,100,0,0,0,0,0,17,423,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 423'),
(2525801,9,11,0,0,0,100,0,22000,22000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 0'),
(2525801,9,12,0,0,0,100,0,0,0,0,0,17,0,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 0'),
(2525801,9,13,0,0,0,100,0,0,0,0,0,17,0,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Set Emote State 0'),
(2525801,9,14,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,15,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,16,0,0,0,100,0,0,0,0,0,71,1,0,2703,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,17,0,0,0,100,0,0,0,0,0,71,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,18,0,0,0,100,0,0,0,0,0,71,0,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525801,9,19,0,0,0,100,0,0,0,0,0,71,0,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Change Equipment'),
(2525802,9,0,0,0,0,100,0,1000,1000,0,0,1,3,6000,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Say Line 3'),
(2525802,9,1,0,0,0,100,0,3000,3000,0,0,45,1,1,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Set Data 1 1'),
(2525802,9,2,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Set Data 1 1'),
(2525802,9,3,0,0,0,100,0,3000,3000,0,0,1,0,6000,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Say Line 0'),
(2525802,9,4,0,0,0,100,0,6000,6000,0,0,5,11,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Play Emote 11'),
(2525802,9,5,0,0,0,100,0,0,0,0,0,5,11,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Play Emote 11'),
(2525802,9,6,0,0,0,100,0,0,0,0,0,5,11,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Play Emote 11'),
(2525802,9,7,0,0,0,100,0,1000,1000,0,0,5,274,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Play Emote 274'),
(2525802,9,8,0,0,0,100,0,0,0,0,0,5,274,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Play Emote 274'),
(2525802,9,9,0,0,0,100,0,0,0,0,0,5,274,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Play Emote 274'),
(2525803,9,0,0,0,0,100,0,0,0,0,0,41,1,0,0,0,0,0,10,85222,25259,0,0,0,0,0,'Footman Rob - On Script - Despawn Instant'),
(2525803,9,1,0,0,0,100,0,0,0,0,0,41,1,0,0,0,0,0,10,85226,25261,0,0,0,0,0,'Footman Rob - On Script - Despawn Instant'),
(2525803,9,2,0,0,0,100,0,0,0,0,0,41,1,0,0,0,0,0,12,1,0,0,0,0,0,0,'Footman Rob - On Script - Despawn Instant'),
(2525803,9,3,0,0,0,100,0,100,100,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Footman Rob - On Script - Despawn Instant');

DELETE FROM `creature_text` WHERE `entry` IN (25261, 25259, 25258);
INSERT INTO `creature_text` VALUES 
(25258,0,0,'One last drink before we head to the front?',12,7,100,1,0,0,0,'Footman Rob'),
(25258,1,0,'Barkeep!  Bring out your strongest ale.  We\'re off to the front.',12,7,100,1,0,0,0,'Footman Rob'),
(25258,2,0,'You\'ll surely make an exception for us, eh?  We might not come back.',12,7,100,1,0,0,0,'Footman Rob'),
(25258,3,0,'I guess that\'s it then.  Off we go.',12,7,100,1,0,0,0,'Footman Rob'),
(25259,0,0,'Sure, why not?',12,7,100,6,0,0,0,'Footman George'),
(25261,0,0,'That was the worst beer I\'ve ever had.',12,7,100,0,0,0,0,'Footman Chuck');

DELETE FROM `waypoint_data` WHERE `id` = 852210;
INSERT INTO `waypoint_data` VALUES 
(852210,1,2277.23,5177.21,11.34,0,0,0,0,100,0),
(852210,2,2268.97,5175.55,11.1665,0,0,0,0,100,0),
(852210,3,2254.59,5188.89,11.384,0,0,0,0,100,0),
(852210,4,2254.27,5196.42,11.3837,0,0,0,0,100,0),
(852210,5,2260.67,5200.36,11.3711,0,0,0,0,100,0),
(852210,6,2264.38,5199.09,11.3676,0,13000,0,0,100,0),
(852210,7,2270.18,5196.94,12.4959,0,0,0,0,100,0),
(852210,8,2275.23,5194.94,12.49,0,0,0,0,100,0),
(852210,9,2276.23,5197.58,12.4896,0,0,0,0,100,0),
(852210,10,2279.08,5206.5,12.494,0,60000,0,0,100,0),
(852210,11,2278.6,5205.3,12.4926,0,16000,0,0,100,0),
(852210,12,2275.55,5197.84,12.4897,0,0,0,0,100,0),
(852210,13,2275.6,5194.96,12.489,0,0,0,0,100,0),
(852210,14,2265.21,5198.54,11.3533,0,0,0,0,100,0),
(852210,15,2258.23,5201.82,11.3182,0,0,0,0,100,0),
(852210,16,2258.98,5205.83,11.322,0,0,0,0,100,0),
(852210,17,2261,5212.02,11.2373,0,0,0,0,100,0),
(852210,18,2268.17,5226.07,11.2421,0,5000,0,0,100,0);

DELETE FROM `creature_addon` WHERE `guid` = 85221;
INSERT INTO `creature_addon` VALUES (85221,852210,0,0,1,0,'');

UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = 85221;
UPDATE `creature_template` SET `InhabitType` = 1 WHERE `entry` IN (25261, 25259, 25258);

DELETE FROM `creature_formations` WHERE `leaderGUID`= 85221;
INSERT INTO `creature_formations` VALUES (85221,85221,0,0,512,0,0),(85221,85222,2,305,512,0,0),(85221,85226,2,55,512,0,0);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 25258;
