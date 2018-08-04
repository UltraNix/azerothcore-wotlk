SET @NPC = 28255;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 58579, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Malas the Corrupter- In Combat - Cast Burning Blaze'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 15000, 25000, 15000, 25000, 11, 57854, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Malas the Corrupter- In Combat - Cast Raging Shadows');
