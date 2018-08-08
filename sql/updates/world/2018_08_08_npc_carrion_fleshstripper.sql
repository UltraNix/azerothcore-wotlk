SET @NPC = 30206;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 6000, 9000, 20000, 25000, 11, 35201, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Carrion Fleshstripper - In Combat - Cast Paralytic Poison');
