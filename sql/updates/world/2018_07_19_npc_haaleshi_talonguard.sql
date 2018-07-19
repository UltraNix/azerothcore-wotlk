SET @NPC = 16967;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 20000, 25000, 15000, 20000, 11, 32720, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Haal\'eshi Talonguard - In Combat - Cast Sprint');
