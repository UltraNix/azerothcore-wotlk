SET @NPC = 18046;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 3000, 7000, 10000, 15000, 11, 16856, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Rajah Haghazed - In Combat - Cast Mortal Strike'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 15000, 20000, 15000, 20000, 11, 35473, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Rajah Haghazed - In Combat - Cast Forceful Cleave');
