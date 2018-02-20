SET @NPC = 3386;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 0, 0, 3400, 4700, 11, 9734, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Theramore Preserver - In Combat - Cast \'Holy Smite\''),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 0, 0, 20000, 30000, 11, 8362, 64, 0, 0, 0, 0, 26, 0, 10, 0, 0, 0, 0, 0, 'Theramore Preserver - In Combat - Cast \'Renew\''),
(@NPC, 0, 2, 0, 0, 0, 100, 0, 0, 0, 10000, 20000, 11, 11642, 64, 0, 0, 0, 0, 1, 0, 10, 0, 0, 0, 0, 0, 'Theramore Preserver - In Combat - Cast \'Heal\''),
(@NPC, 0, 3, 0, 0, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Theramore Preserver - Between 0-15% Health - Flee For Assist (No Repeat)');
