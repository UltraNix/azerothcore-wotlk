UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23206;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 23161 AND `id` IN (4,5);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (2316100,23206);
INSERT INTO `smart_scripts` VALUES
(23161, 0, 4, 5, 0, 0, 100, 1, 8000, 10000, 0, 0, 11, 40427, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Darkscreecher Akkarai - In Combat - Cast Flock Call'),
(23161, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2316100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Darkscreecher Akkarai - In Combat - Start script'),
(2316100, 9, 0, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 12, 23206, 3, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Darkscreecher Akkarai - on script - summon hatchling'),
(2316100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 23206, 3, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Darkscreecher Akkarai - on script - summon hatchling'),
(2316100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 11, 23206, 10, 0, 0, 0, 0, 0, 'Darkscreecher Akkarai - on script - set data 5 5'),
(23206, 0, 0, 0, 38, 0, 100, 0, 5, 5, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Akkarai hatchling - on data set 5 5 - attack start');