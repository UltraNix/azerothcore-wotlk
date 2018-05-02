SET @Dragon = 8480;
SET @Squire = 8509;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (@Dragon,@Squire);
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 256 WHERE `entry` = @Dragon;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@Dragon, @Squire, @Dragon*100);
INSERT INTO `smart_scripts` VALUES
(@Squire, 0, 0, 0, 20, 0, 100, 0, 3463, 0, 0, 0, 12, @Dragon, 4, 30000, 0, 0, 0, 8, 0, 0, 0, -6674.44, -1193.39, 240.81, 3.35, ''),
(@Dragon, 0, 0, 1, 54, 0, 100, 1, 0, 0, 0, 0, 80, @Dragon*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@Dragon*100, 9, 0, 0, 0, 0, 100, 1, 2000, 2000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@Dragon*100, 9, 1, 0, 0, 0, 100, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@Dragon*100, 9, 2, 0, 0, 0, 100, 1, 10000, 10000, 0, 0, 53, 1, @Dragon, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `creature_text` WHERE `entry` = @Dragon;
INSERT INTO `creature_text` VALUES
(@Dragon, 0, 0, 'Kalaran the Deceiver lets loose a reptilian laugh... at least you think it\'s a laugh.', 16, 0, 100, 0, 0, 0, 0, ''),
(@Dragon, 1, 0, 'You would not have helped the legion of Blackrock had we just asked for your assistance, now would you?', 12, 0, 100, 0, 0, 0, 0, '');
DELETE FROM `waypoints` WHERE `entry` = @Dragon;
INSERT INTO `waypoints` VALUES
(@Dragon, 1, -6674.742, -1193.413, 248.05959, ''),
(@Dragon, 2, -6667.960, -1175.038, 255.63031, ''),
(@Dragon, 3, -6656.083, -1133.035, 272.19885, ''),
(@Dragon, 4, -6648.262, -1090.345, 281.20718, ''),
(@Dragon, 5, -6637.382, -1037.938, 306.96140, '');
