SET @NPC = 30544;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 6000, 9000, 30000, 35000, 11, 50284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgotten Depths Underking - In Combat - Cast Blinding Swarm'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 15000, 19000, 20000, 25000, 11, 60802, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgotten Depths Underking - In Combat - Cast Mandible Crush');
