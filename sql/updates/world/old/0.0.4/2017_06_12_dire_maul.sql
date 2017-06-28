-- Tsu'zee SAI
SET @ENTRY := 11467;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,6000,7000,11,15667,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tsu'zee - In Combat - Cast 'Sinister Strike'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,9000,12000,11,12540,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tsu'zee - In Combat - Cast 'Gouge'"),
(@ENTRY,0,2,0,0,0,100,0,7000,11000,16000,21000,11,21060,0,0,0,0,0,5,0,0,0,0,0,0,0,"Tsu'zee - In Combat - Cast 'Blind'"),
(@ENTRY,0,3,0,67,0,100,0,9000,12000,0,0,11,15657,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tsu'zee - On Behind Target - Cast 'Backstab'");

-- Wildspawn Imp SAI
SET @ENTRY := 13276;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,7000,15000,11,13340,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wildspawn Imp - Within 0-20 Range - Cast 'Fire Blast'");

-- Eldreth Seether SAI
SET @ENTRY := 11469;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,20000,20000,30000,11,16843,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eldreth Seether - In Combat - Cast 'Crimson Fury'"),
(@ENTRY,0,1,2,2,0,100,1,0,30,0,0,11,8269,1,0,0,0,0,1,0,0,0,0,0,0,0,"Eldreth Seether - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,0,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eldreth Seether - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,25,0,100,0,0,0,0,0,11,18968,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eldreth Seether - On Reset - Cast 'Fire Shield'");

-- Gordok Bushwacker SAI
SET @ENTRY := 14351;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,60,0,100,257,1500,1500,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gordok Bushwacker - On Update - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,2,61,0,100,0,1500,1500,0,0,69,1,0,0,0,0,0,8,0,0,0,591.51,592.22,-4.75,0,"Gordok Bushwacker - On Update - Move To Position (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,0,1500,1500,0,0,89,7,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gordok Bushwacker - On Update - Start Random Movement (No Repeat)"),
(@ENTRY,0,3,0,4,0,10,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gordok Bushwacker - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,5000,8000,19000,25000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gordok Bushwacker - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,5,0,0,0,100,0,3000,6000,15000,17000,11,15572,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gordok Bushwacker - In Combat - Cast 'Sunder Armor'"),
(@ENTRY,0,6,0,9,0,100,0,0,5,13600,14500,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gordok Bushwacker - Within 0-5 Range - Cast 'Cleave'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid` = 1;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,1,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,1,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,1,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');
