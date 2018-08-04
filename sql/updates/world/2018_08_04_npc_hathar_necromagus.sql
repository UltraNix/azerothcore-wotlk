SET @NPC = 28257;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 10000, 15000, 11, 54491, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Hathar Necromagus- In Combat - Cast Conversion Beam'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 15000, 25000, 15000, 25000, 11, 50661, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Hathar Necromagus- In Combat - Cast Weakened Resolve');
