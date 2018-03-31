UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 188712;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 27435;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (27435,2743500,188712,18871200);
INSERT INTO `smart_scripts` VALUES
(27435, 0, 0, 0, 1, 0, 100, 1, 1000, 1000, 0, 0, 80, 2743500, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - Out of Combat - run script'),
(27435, 0, 1, 2, 1, 0, 100, 1, 14000, 14000, 0, 0, 11, 48742, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - Out of Combat - Cast \'Wintergarde Mine Explosion\' (No Repeat)'),
(27435, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - Out of Combat - Despawn In 3000 ms (No Repeat)'),
(27435, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 3, 3, 0, 0, 0, 0, 15, 188712, 10, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - Out of Combat - Set Data 3 3'),
(2743500, 9, 0, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 0'),
(2743500, 9, 1, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 1'),
(2743500, 9, 2, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 2'),
(2743500, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 3'),
(2743500, 9, 4, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 4'),
(2743500, 9, 5, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Bomb - On Script - Say Line 5'),
(188712, 1, 0, 0, 38, 0, 100, 0, 3, 3, 0, 0, 80, 18871200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Cave In - On Data Set 3 3 - run script'),
(18871200, 9, 0, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Mine Cave In  - on script - despawn');

DELETE FROM `creature_text` WHERE `entry` = 27435;
INSERT INTO `creature_text` VALUES
(27435, 0, 0, 'Wintergarde Mine Bomb armed', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine'),
(27435, 1, 0, 'Detonation 5...', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine'),
(27435, 2, 0, '4...', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine'),
(27435, 3, 0, '3...', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine'),
(27435, 4, 0, '2...', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine'),
(27435, 5, 0, '1...', 16, 7, 100, 0, 0, 0, 0, 'Wintergarde Mine');
