SET @NPC = 18977;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 33971, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Destroyer - In Combat - Cast Charge'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 40505, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Destroyer - In Combat - Cast Cleave');
(@NPC, 0, 2, 0, 0, 0, 100, 0, 15000, 25000, 10000, 15000, 11, 40220, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Destroyer - In Combat - Cast Mortal Strike');
