DELETE FROM `smart_scripts` WHERE `entryorguid` IN (68, 1756) AND `id` = 0;
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

DELETE FROM `smart_scripts` WHERE `entryorguid` = 68 AND `id` >= 2;
INSERT INTO `smart_scripts` VALUES 
(68, 0, 2, 0, 0, 0, 100, 0, 3000, 13000, 9000, 15000, 11, 40505, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - In Combat - Cast Cleave'),
(68, 0, 3, 10, 22, 1, 100, 0, 58, 0, 0, 0, 5, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Kiss - Play Emote Bow'),
(68, 0, 4, 10, 22, 1, 100, 0, 101, 0, 0, 0, 5, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Wave - Play Emote Wave'),
(68, 0, 5, 10, 22, 1, 100, 0, 78, 0, 0, 0, 5, 66, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Salute - Play Emote Salute'),
(68, 0, 6, 10, 22, 1, 100, 0, 84, 0, 0, 0, 5, 23, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Shy - Play Emote Flex'),
(68, 0, 7, 10, 22, 1, 100, 0, 77, 0, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Rude - Play Emote Point'),
(68, 0, 8, 10, 22, 1, 100, 0, 22, 0, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received Chicken - Play Emote Point'),
(68, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Emote Received - Set Event Phase'),
(68, 0, 11, 0, 60, 0, 100, 0, 5000, 5000, 5000, 5000, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Update - Set Event Phase'),
(68, 0, 12, 0, 6, 0, 100, 0, 0, 0, 0, 0, 149, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Stormwind City Guard - On Death - Send Zone Under Attack');

DELETE FROM `creature_text` WHERE `entry` IN (68, 1756);
INSERT INTO `creature_text` VALUES 
(68, 2, 0, '%s throws a rotten apple at $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 3, 0, '%s throws rotten banana on $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 4, 0, '%s spits on $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 0, 'Monster!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 1, 'Murderer!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 2, 'GET A ROPE!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 3, 'How dare you set foot in our city!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 4, 'You disgust me.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 5, 'Looks like we\'re going to have ourselves an execution.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 6, 'Traitorous dog.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(68, 5, 7, 'My family was wiped out by the Scourge! MONSTER!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind City Guard'),
(1756, 0, 0, 'Yes, sir!', 12, 0, 100, 0, 0, 0, 0, 'lord gregor lescovar SAY_GUARD_2'),
(1756, 1, 0, 'Of course. He awaits you in the library.', 12, 0, 100, 0, 0, 0, 0, 'tyrion spybot SAY_GUARD_1'),
(1756, 2, 0, '%s throws a rotten apple at $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 3, 0, '%s throws rotten banana on $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 4, 0, '%s spits on $n.', 16, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 0, 'Monster!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 1, 'Murderer!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 2, 'GET A ROPE!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 3, 'How dare you set foot in our city!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 4, 'You disgust me.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 5, 'Looks like we\'re going to have ourselves an execution.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 6, 'Traitorous dog.', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard'),
(1756, 5, 7, 'My family was wiped out by the Scourge! MONSTER!', 12, 0, 100, 0, 0, 0, 0, 'Stormwind Royal Guard');

DELETE FROM `conditions` WHERE `SourceEntry` IN (1756, 68);
INSERT INTO `conditions` VALUES
(22, 1, 1756, 0, 0, 28, 0, 13188, 0, 0, 0, 0, 0, '', 'Only Run script if quest is completed'),
(22, 1, 68, 0, 0, 28, 0, 13188, 0, 0, 0, 0, 0, '', 'Only Run script if quest is completed');
