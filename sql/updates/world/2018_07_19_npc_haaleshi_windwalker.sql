SET @NPC = 16966;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 3000, 6000, 5000, 9000, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Haal\'eshi Windwalker - In Combat - Cast Lightning Bolt'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 20000, 25000, 15000, 20000, 11, 32717, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Haal\'eshi Windwalker - In Combat - Cast Hurricane');
