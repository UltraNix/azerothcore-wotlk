SET @NPC = 32488;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 59130, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ebon Blade Vindicator- In Combat - Cast Blood Strike');
