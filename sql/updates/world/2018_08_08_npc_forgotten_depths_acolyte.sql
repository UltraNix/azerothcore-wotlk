SET @NPC = 30205;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 6000, 9000, 60000, 80000, 11, 60781, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgotten Depths Acolyte - In Combat - Cast Curse of Mending'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 3000, 4000, 10000, 15000, 11, 16583, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgotten Depths Acolyte - In Combat - Cast Shadow Shock');
