SET @ENTRY = 14368;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES 
(@ENTRY, 0, 0, 0, 38, 0, 100, 1, 0, 1, 0, 0, 80, @ENTRY*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lorekeeper Lydros - on data set 0 1 - run script');