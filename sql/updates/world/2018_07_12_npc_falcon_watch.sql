SET @NPC = 17282;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 11, 18950, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Falcon Watch Ranger - On Reset - Cast Invisibility and Stealth Detection'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 3000, 6000, 8000, 10000, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Falcon Watch Ranger  - In Combat - Cast Shoot');
