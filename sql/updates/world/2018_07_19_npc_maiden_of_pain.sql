SET @NPC = 19408;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 15968, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maiden of Pain - In Combat - Cast Lash of Pain'),
(@NPC, 0, 1, 0, 2, 0, 100, 0, 0, 30, 0, 0, 11, 34086, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Maiden of Pain - On Health Below 30% - Cast Whipped Frenzy');
