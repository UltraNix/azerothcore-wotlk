SET @NPC = 18758;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18396, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telhamat Protector - On Aggro - Cast Dismounting Blast'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 3000, 6000, 5000, 9000, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telhamat Protector - In Combat - Cast Shoot');
