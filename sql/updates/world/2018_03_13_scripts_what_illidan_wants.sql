DELETE FROM `creature` WHERE `guid` IN (86102, 86101);

SET @SLAYER = 21639;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @SLAYER;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 20563 AND `id` IN (2,3,4);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SLAYER, @SLAYER*100);
INSERT INTO `smart_scripts` VALUES
(@SLAYER, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, @SLAYER*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@SLAYER*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, -4579.70, 1668.31, 175.79, 2.88, ''),
(@SLAYER*100, 9, 1, 0, 0, 0, 100, 0, 500, 500, 500, 500, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 2.88, ''),
(@SLAYER*100, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 30000, 30000, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@SLAYER, 0, 1, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(20563, 0, 2, 3, 62, 0, 100, 0, 8341, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, @SLAYER, 0, 10, 0, 0, 0, 0, ''),
(20563, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 18, 5, 0, 0, 0, 0, 0, 0, ''),
(20563, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 9, @SLAYER, 0, 10, 0, 0, 0, 0, '');

UPDATE `smart_scripts` SET `link` = 4 WHERE `entryorguid` = 20563 AND `id` = 1;

DELETE FROM `creature_text` WHERE `entry` = 20563;
INSERT INTO `creature_text` VALUES
(20563, 0, 0, 'Illidari Slayer moves in behind you with his axe at ready.', 16, 0, 100, 0, 0, 0, 0, 'Commander Ruusk');
