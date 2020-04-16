-- Ring-Lord Sorceress SAI
SET @ENTRY := 27639;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,1000,1000,0,0,11,51518,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ring-Lord Sorceress - Out of Combat - Cast 'Nexus Energy Cosmetic' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,2,0,40,15000,19000,11,50715,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ring-Lord Sorceress - Within 0-40 Range - Cast 'Blizzard' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,4,0,40,15000,19000,11,59278,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ring-Lord Sorceress - Within 0-40 Range - Cast 'Blizzard' (Heroic Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,9000,12000,15000,18000,11,16102,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ring-Lord Sorceress - In Combat - Cast 'Flamestrike' (Normal Dungeon)"),
(@ENTRY,0,4,0,0,0,100,4,9000,12000,15000,18000,11,61402,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ring-Lord Sorceress - In Combat - Cast 'Flamestrike' (Heroic Dungeon)");
