SET @NPC = 20159;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 3000, 9000, 10000, 15000, 11, 11831, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis - In Combat - Cast Forst Nova'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 2000, 4000, 5000, 8000, 11, 20823, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Magister Aledis  - In Combat - Cast Fireball');
