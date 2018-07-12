SET @NPC = 16580;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 11, 18950, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Grunt - On Reset - Cast Invisibility and Stealth Detection'),
(@NPC, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18396, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Grunt - On Aggro - Cast Dismounting Blast'),
(@NPC, 0, 2, 0, 0, 0, 100, 0, 3000, 6000, 5000, 9000, 11, 6660, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Grunt - In Combat - Cast Shoot'),
(@NPC, 0, 3, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 19643, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Grunt - In Combat - Cast Mortal Strike'),
(@NPC, 0, 4, 0, 0, 0, 100, 0, 13000, 20000, 15000, 20000, 11, 15618, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrallmar Grunt - In Combat - Cast Snap Kick');
