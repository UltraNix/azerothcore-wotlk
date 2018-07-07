SET @NPC = 19257;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 6000, 9000, 20000, 25000, 11, 33634, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Arcanist Torseldori - In Combat - Cast Blizzard'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 15000, 20000, 15000, 20000, 11, 12674, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Arcanist Torseldori - In Combat - Cast Frost Nova'),
(@NPC, 0, 2, 0, 0, 0, 100, 0, 2000, 3000, 8000, 12000, 11, 15530, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Arcanist Torseldori - In Combat - Cast Frost Bolt');
