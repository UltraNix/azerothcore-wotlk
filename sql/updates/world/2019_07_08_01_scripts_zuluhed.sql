DELETE FROM `smart_scripts` WHERE `entryorguid` = 1198000;
INSERT INTO `smart_scripts` VALUES
(1198000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 24240, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zuluhed the Whacked - action list - cast red lightning'),
(1198000, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zuluhed the Whacked - action list - text'),
(1198000, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zuluhed the Whacked - action list - text'),
(1198000, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zuluhed the Whacked - action list - text'),
(1198000, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22251, 4, 20000, 0, 0, 0, 8, 0, 0, 0, -4204.4, 308.2, 136.9, 1.45, 'Zuluhed the Whacked - action list - summon archer'),
(1198000, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 22251, 4, 20000, 0, 0, 0, 8, 0, 0, 0, -414.89, 316.7, 135.0, 2.19, 'Zuluhed the Whacked - action list - summon archer');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 22251;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 22251;
INSERT INTO `smart_scripts` VALUES
(22251, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 11, 6660, 2, 0, 0, 0, 0, 21, 50, 0, 0, 0, 0, 0, 0, '');
