-- Anub'ar Necromancer SAI
SET @ENTRY := 28925;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,0,0,3400,4700,11,53333,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Shadow Bolt' (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,6,8000,8000,29900,32300,11,53334,1,0,0,0,0,1,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Animate Bones' (Dungeon)");

-- Anub'ar Necromancer SAI
SET @ENTRY := 29119;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,0,0,3400,4700,11,53333,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Shadow Bolt' (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,6,8000,8000,29900,32300,11,53334,1,0,0,0,0,1,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Animate Bones' (Dungeon)");

-- Anub'ar Necromancer SAI
SET @ENTRY := 29064;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,0,0,3400,4700,11,53333,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Shadow Bolt' (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,6,8000,8000,29900,32300,11,53334,1,0,0,0,0,1,0,0,0,0,0,0,0,"Anub'ar Necromancer - In Combat - Cast 'Animate Bones' (Dungeon)");

-- Anub'ar Champion SAI
SET @ENTRY := 28924;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,13,0,100,2,14000,17000,0,0,11,53394,0,0,0,0,0,6,1,0,0,0,0,0,0,"Anub'ar Champion - On Victim Casting - Cast 'Pummel' (Normal Dungeon)"),
(@ENTRY,0,1,0,13,0,100,4,14000,17000,0,0,11,59344,0,0,0,0,0,6,1,0,0,0,0,0,0,"Anub'ar Champion - On Victim Casting - Cast 'Pummel' (Heroic Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,6000,9000,17000,32000,11,53317,0,0,0,0,0,5,32,0,0,0,0,0,0,"Anub'ar Champion - In Combat - Cast 'Rend' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,6000,9000,17000,32000,11,59343,0,0,0,0,0,5,32,0,0,0,0,0,0,"Anub'ar Champion - In Combat - Cast 'Rend' (Heroic Dungeon)");
