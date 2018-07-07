SET @NPC = 19257;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC AND `id` IN (1,2);
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 1, 0, 0, 0, 100, 0, 6000, 9000, 20000, 25000, 11, 19643, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Wolf Rider - In Combat - Cast Mortal Strike'),
(@NPC, 0, 2, 0, 0, 0, 100, 0, 15000, 20000, 15000, 20000, 11, 15618, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Wolf Rider - In Combat - Cast Snap Kick');
