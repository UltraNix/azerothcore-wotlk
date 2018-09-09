UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 25383;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25383;
INSERT INTO `smart_scripts` VALUES 
(25383, 0, 0, 0, 0, 0, 100, 0, 5, 5000, 8000, 12000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'En\'kilah Abomination - Cast Cleave'),
(25383, 0, 1, 0, 0, 0, 100, 0, 2000, 6000, 10000, 16000, 11, 50335, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'En\'kilah Abomination - Cast Scourge Hook');
