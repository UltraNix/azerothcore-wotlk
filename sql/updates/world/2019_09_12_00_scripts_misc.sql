DELETE FROM `smart_scripts` WHERE `entryorguid` IN (68, 1756);
INSERT INTO `smart_scripts` VALUES
(68, 0, 0, 0, 10, 0, 100, 0, 1, 10, 10000, 10000, 87, 6800, 6801, 6802, 6803, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - Within 1-10 Range Out of Combat LoS - Run Random Script'),
(1756, 0, 0, 0, 10, 0, 100, 0, 1, 10, 10000, 10000, 87, 6800, 6801, 6802, 6803, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind Royal Guard - Within 1-10 Range Out of Combat LoS - Run Random Script');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (6800, 6801,6802,6803);
INSERT INTO `smart_scripts` VALUES 
(6800, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 58509, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Cast \'\'Rotten Apple Toss\''),
(6800, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Say Line 2'),
(6801, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 58513, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Cast \'Rotten Banana Toss\''),
(6801, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Say Line 3'),
(6802, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 58520, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Cast \'Spit\''),
(6802, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Say Line 4'),
(6803, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Script - Say Line 5');
