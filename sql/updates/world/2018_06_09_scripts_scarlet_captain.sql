DELETE FROM `creature_text` WHERE `entry` = 28611 AND `id` = 6;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 28611 AND `id` = 4;
INSERT INTO `smart_scripts` VALUES
(28611, 0, 4, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Captain - On Aggro - Say Line 0 (No Repeat)');
UPDATE `smart_scripts` SET `comment` = "Scarlet Captain - Update - Cast Shoot" WHERE `entryorguid` = 28611 AND `id` = 0;
