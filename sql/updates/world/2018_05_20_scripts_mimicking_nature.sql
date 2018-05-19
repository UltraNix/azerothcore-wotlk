UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24173;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (24173,2417300);
INSERT INTO `smart_scripts` VALUES
(24173, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 10000, 20000, 11, 52058, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - In Combat - Cast \'Ground Slam\''),
(24173, 0, 1, 2, 11, 0, 100, 0, 0, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Spawn - Add UNIT_FLAG_IMMUNE_TO_PC'),
(24173, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 24173, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Spawn - Start Waypoint'),
(24173, 0, 3, 0, 40, 0, 100, 0, 4, 0, 0, 0, 80, 2417300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On WP 4 Reached - Start Script'),
(2417300, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Set home position to summoner\'s position'),
(2417300, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0,  66, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Turn to summoner'),
(2417300, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Say Text 0'),
(2417300, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Say Text 1'),
(2417300, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 19, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Remove UNIT_FLAG_IMMUNE_TO_PC'),
(2417300, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Frostgore - On Script - Attack summoner');
DELETE FROM `creature_text` WHERE `entry` = 24173;
INSERT INTO `creature_text` VALUES
(24173, 0, 0, 'Are YOU the one who interrupted my dinner? Well, are you?', 12, 0, 100, 1, 0, 0, 0, 'Frostgore'),
(24173, 1, 0, 'You\'re too ugly and scrawny to be a female yeti! And now you\'re making me mad...', 12, 0, 100, 25, 0, 0, 0, 'Frostgore');

DELETE FROM `event_scripts` WHERE `id` = 15726;
INSERT INTO `event_scripts` VALUES (15726, 0, 10, 24173, 300000, 0, 2932.63, -4488.1, 285.688, 3.29867);

DELETE FROM `waypoints` WHERE `entry` = 24173;
INSERT INTO `waypoints` VALUES 
(24173, 1, 2918.37, -4505.42, 280.042, ''),
(24173, 2, 2920.94, -4521.92, 276.003, ''),
(24173, 3, 2923.96, -4535.5, 274.453, ''),
(24173, 4, 2944.43, -4555.3, 273.69, '');

DELETE FROM `conditions` WHERE `SourceEntry` = 43189;
INSERT INTO `conditions` VALUES
(17, 0, 43189, 0, 0, 29,0, 24173 ,50, 0,1, 0, 0, '', 'Test Horn can be used only if event not started');
