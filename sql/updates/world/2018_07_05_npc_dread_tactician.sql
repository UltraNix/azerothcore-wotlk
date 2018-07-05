UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 16959;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 16959;
INSERT INTO `smart_scripts` VALUES
(16959, 0, 0, 0, 0, 0, 100, 0, 10000, 20000, 20000, 25000, 11, 12098, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Dread Tactician - In Combat - Cast Sleep'),
(16959, 0, 1, 0, 0, 0, 100, 0, 20000, 30000, 25000, 40000, 11, 33679, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dread Tactician - In Combat - Cast Inferno'),
(16959, 0, 2, 0, 0, 0, 100, 0, 3000, 7000, 10000, 15000, 11, 33678, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dread Tactician - In Combat - Cast Carrion Swarm');
