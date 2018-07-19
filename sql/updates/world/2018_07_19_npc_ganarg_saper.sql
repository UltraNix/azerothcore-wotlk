SET @NPC = 18827;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 33974, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Gan\'arg Sapper - In Combat - Cast Power Burn');
