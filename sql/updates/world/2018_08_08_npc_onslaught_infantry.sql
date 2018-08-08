SET @NPC = 27330;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 50713, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Onslaught Infantry - In Combat - Cast Unrelenting Onslaugh');
