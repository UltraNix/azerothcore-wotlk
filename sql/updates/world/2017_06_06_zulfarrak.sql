-- Dustwraith SAI
SET @ENTRY := 10081;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,3600,7300,11,15667,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dustwraith - Within 0-5 Range - Cast 'Sinister Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,17000,18000,11,12251,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dustwraith - In Combat - Cast 'Virulent Poison' (Normal Dungeon)");

-- Hydromancer Velratha SAI
SET @ENTRY := 7795;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Hydromancer Velratha - In Combat - Cast 'Water Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,50,0,0,11,12491,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hydromancer Velratha - Between 0-50% Health - Cast 'Healing Wave' (No Repeat) (Normal Dungeon)");

-- Zerillis SAI
SET @ENTRY := 10082;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Zerillis - In Combat - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,20,12000,25000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zerillis - Within 0-20 Range - Cast 'Net' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,6000,11000,5800,16000,11,12551,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zerillis - In Combat - Cast 'Frost Shot' (Normal Dungeon)");

-- Sandarr Dunereaver SAI
SET @ENTRY := 10080;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,16000,26000,11,14516,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sandarr Dunereaver - Within 0-5 Range - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,6000,12000,25000,34000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sandarr Dunereaver - In Combat - Cast 'Demoralizing Shout' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,10000,20000,15000,24000,11,15615,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sandarr Dunereaver - In Combat - Cast 'Pummel' (Normal Dungeon)");

-- Sandfury Guardian SAI
SET @ENTRY := 7268;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,2000,3000,8000,11000,11,3391,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sandfury Guardian - In Combat - Cast 'Thrash' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,16000,17000,11,744,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sandfury Guardian - In Combat - Cast 'Poison' (Normal Dungeon)");

