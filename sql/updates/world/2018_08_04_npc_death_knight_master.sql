SET @NPC = 29738;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 50689, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Death Knight Master - On Aggro - Cast Blood Presence'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 50688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Death Knight Master - In Combat - Cast Plague Strike');
