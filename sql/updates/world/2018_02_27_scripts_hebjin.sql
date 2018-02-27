UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE `entry` IN (28636,28639);

DELETE FROM `creature` WHERE `id` = 28636;

DELETE FROM `creature_template_addon` WHERE `entry` = 28636;
INSERT INTO `creature_template_addon` VALUES
(28636, 0, 0, 0, 1, 0, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (28636,2863600);
INSERT INTO `smart_scripts` VALUES
(28636, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 80, 2863600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Just Summoned - Run Script'),
(28636, 0, 1, 2, 38, 0, 100, 0, 0, 1, 0, 0, 11, 52354, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Data Set 0 1 - Cast \'Script Effect - Creature Attack GUID from Dot Variable\''),
(28636, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 5937.22, -3820.87, 366.556, 0, 'Heb\'Jin - On Data Set 0 1 - Move To Position'),
(28636, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Data Set 0 1 - Say Line 2'),
(28636, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 19, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Data Set 0 1 - Remove Flag Immune To Players'),
(28636, 0, 5, 10, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Data Set 0 1 - Start Attacking'),
(28636, 0, 6, 0, 0, 0, 100, 0, 1000, 1000, 7000, 8000, 11, 12734, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - In Combat - Cast \'Ground Smash\''),
(28636, 0, 7, 0, 0, 0, 100, 0, 5000, 5000, 10000, 12000, 11, 15548, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - In Combat - Cast \'Thunderclap\''),
(28636, 0, 8, 0, 13, 0, 100, 0, 12000, 15000, 0, 0, 11, 12555, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - Target Casting - Cast \'Pummel\''),
(28636, 0, 9, 0, 7, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb Jin - On Evade - Despawn'),
(28636, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb Jin - On Link (Landed) - Set Home Position'),
(2863600, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 52353, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Cast \'Script Effect - Creature Capture GUID to Dot Variable\''),
(2863600, 9, 1, 0, 0, 0, 100, 0, 3200, 3200, 0, 0, 11, 52154, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Cast \'Taunt\''),
(2863600, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Say Line 0'),
(2863600, 9, 3, 0, 0, 0, 100, 0, 300, 300, 0, 0, 12, 28639, 2, 300000, 0, 0, 0, 8, 0, 0, 0, 5984.55, -3882.62, 417.438, 1.91986, 'Heb\'Jin - On Script - Summon Creature \'Heb\'Jin\'s Bat\''),
(2863600, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 28639, 10, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Send Target 1'),
(2863600, 9, 5, 0, 0, 0, 100, 0, 5700, 5700, 0, 0, 1, 1, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Say Line 1'),
(2863600, 9, 6, 0, 0, 0, 100, 0, 2400, 2400, 0, 0, 11, 43671, 0, 0, 0, 0, 0, 19, 28639, 10, 0, 0, 0, 0, 0, 'Heb\'Jin - On Script - Cast \'Ride Vehicle\'');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (190695, 19069500, -98562, 28639, 2863900);
INSERT INTO `smart_scripts` VALUES
(190695, 1, 0, 1, 70, 0, 100, 0, 2, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Drum - On state changed - Store targetlist'),
(190695, 1, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 19069500, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Drum - Linked with Previous Event - Run Script'),
(19069500, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 98562, 23837, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Drum - Script - Set Data ELM General Purpose Bunny'),
(19069500, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 100, 1, 0, 0, 0, 0, 0, 19, 28636, 100, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Drum - Script - Send Target list to heb jin'),
(-98562, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 45, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'ELM General Purpose Bunny - On Data Set - Set Data'),
(-98562, 0, 1, 0, 61, 0, 100, 0, 1, 1, 0, 0, 12, 28636, 2, 300000, 0, 0, 0, 8, 0, 0, 0, 5988.71, -3878.04, 417.15, 2.35619, 'ELM General Purpose Bunny - Linked with Previous Event - Spawn Heb Jin'),
(28639, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 91, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Respawn - Remove Flag Standstate Dead'),
(28639, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 52353, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Respawn - Cast \'Script Effect - Creature Capture GUID to Dot Variable\''),
(28639, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 4, 10892, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Respawn - Play Sound 10892'),
(28639, 0, 3, 0, 27, 0, 100, 1, 0, 0, 0, 0, 53, 1, 28639, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Passenger Boarded - Start Waypoint'),
(28639, 0, 4, 5, 40, 0, 100, 0, 4, 28639, 0, 0, 28, 43671, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Waypoint 4 Reached - Remove Aura \'Ride Vehicle\''),
(28639, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, 28636, 10, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Waypoint 4 Reached - Set Data 0 1'),
(28639, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2863900, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Waypoint 4 Reached - Run Script'),
(28639, 0, 7, 8, 8, 0, 100, 0, 52151, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Spellhit \'Bat Net\' - Set Flag Immune To Players'),
(28639, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 90, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Spellhit \'Bat Net\' - Set Flag Standstate Dead'),
(28639, 0, 9, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Spellhit \'Bat Net\' - Despawn In 5000 ms'),
(28639, 0, 10, 0, 7, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb Jins Bat - On Evade - Despawn'),
(2863900, 9, 0, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 19, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Script - Remove Flag Immune To Players'),
(2863900, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 20, 0, 0, 0, 0, 0, 0, 'Heb\'Jin\'s Bat - On Script - Start Attacking');
