SET @NPC = 28034;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 4, 0, 80, 0, 0, 0, 0, 0, 11, 54482, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakkari Snake Handler- On Aggro - Cast Blood of Sseratur'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakkari Snake Handler- In Combat - Cast Shoot'),
(@NPC, 0, 2, 0, 0, 0, 100, 0, 10000, 15000, 15000, 25000, 11, 54484, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakkari Snake Handler- In Combat - Cast Summon Snake');
