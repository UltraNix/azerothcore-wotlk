-- Bor'gorok Battleguard SAI
SET @ENTRY := 27073;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Bor'gorok Battleguard - In Combat - Cast 'Shoot'");

-- En'kilah Abomination SAI
SET @ENTRY := 25383;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,50335,0,0,0,0,0,2,1,0,0,0,0,0,0,"En'kilah Abomination - On Aggro - Cast 'Scourge Hook' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3400,4000,11300,12400,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"En'kilah Abomination - In Combat - Cast 'Cleave'");

-- Fizzcrank Airman SAI
SET @ENTRY := 26601;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fizzcrank Airman - In Combat - Cast 'Shoot'");

-- Kvaldir Mist Lord SAI
SET @ENTRY := 25496;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,13000,15600,11,49922,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kvaldir Mist Lord - In Combat - Cast 'Wave Crash'");

-- Kaskala Defender SAI
SET @ENTRY := 25764;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,38556,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kaskala Defender - In Combat - Cast 'Throw'");

-- Grunt Gritch SAI
SET @ENTRY := 31726;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grunt Gritch - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,12000,12000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grunt Gritch - In Combat - Cast 'Net'");

-- Grunt Grikee SAI
SET @ENTRY := 31727;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grunt Grikee - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,12000,12000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grunt Grikee - In Combat - Cast 'Net'");

-- Oil-covered Hawk SAI
SET @ENTRY := 25748;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,9000,11000,11,50280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oil-covered Hawk - In Combat - Cast 'Oily Coat'");

-- Oil-soaked Caribou SAI
SET @ENTRY := 25750;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,9000,11000,11,50280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oil-soaked Caribou - In Combat - Cast 'Oily Coat'");

-- Scourged Flamespitter SAI
SET @ENTRY := 25582;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,32707,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scourged Flamespitter - In Combat - Cast 'Incinerate'");

-- Warsong Battleguard SAI
SET @ENTRY := 25242;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Battleguard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Battleguard - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Battleguard - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Valiance Keep Defender SAI
SET @ENTRY := 29617;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Keep Defender - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,12400,16700,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Valiance Keep Defender - In Combat - Cast 'Shield Block'"),
(@ENTRY,0,2,0,0,0,100,0,5500,5500,13000,16900,11,12170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Keep Defender - In Combat - Cast 'Revenge'");

-- Warsong Honor Guard SAI
SET @ENTRY := 25243;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Honor Guard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Honor Guard - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Honor Guard - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Warsong Scout SAI
SET @ENTRY := 25439;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Scout - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Scout - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Scout - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Crown Sprayer SAI
SET @ENTRY := 38032;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,70074,64,0,0,0,0,2,0,0,0,0,0,0,0,"Crown Sprayer - In Combat - Cast 'Spray Chemical'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crown Sprayer - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crown Sprayer - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,5,12300,16700,11,11978,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crown Sprayer - Within 0-5 Range - Cast 'Kick'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Librarian Belleford SAI
SET @ENTRY := 32374;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Librarian Belleford - Out of Combat - Cast 'Frost Armor'");

-- Rotting Storm Giant SAI
SET @ENTRY := 27270;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,10,70,8000,12000,11,50405,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rotting Storm Giant - Within 10-70 Range - Cast 'Forged Thunder'");

-- Snowplain Zealot SAI
SET @ENTRY := 27278;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Snowplain Zealot - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Snowplain Zealot - Between 0-15% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Conquest Hold Champion SAI
SET @ENTRY := 27550;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Conquest Hold Champion - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,9000,12000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Conquest Hold Champion - Within 0-5 Range - Cast 'Cleave'");

-- Arcturis SAI
SET @ENTRY := 38453;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,61184,0,0,0,0,0,2,0,0,0,0,0,0,0,"Arcturis - On Aggro - Cast 'Pounce' (No Repeat)");

-- Amberpine Footman SAI
SET @ENTRY := 27072;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Amberpine Footman - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Amberpine Footman - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Garg SAI
SET @ENTRY := 23745;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,53824,64,0,0,0,0,2,0,0,0,0,0,0,0,"Garg - In Combat - Cast 'Throw'");

-- Hungry Worg SAI
SET @ENTRY := 26586;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,7000,17000,20000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hungry Worg - In Combat - Cast 'Gore'");

-- Ravenous Worg SAI
SET @ENTRY := 26590;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,7000,17000,20000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravenous Worg - In Combat - Cast 'Gore'");

-- Runic War Golem SAI
SET @ENTRY := 26347;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,15000,16000,11,52702,0,0,0,0,0,2,0,0,0,0,0,0,0,"Runic War Golem - In Combat - Cast 'Rune Punch'");

-- Vladek SAI
SET @ENTRY := 27547;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,32714,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vladek - Between 0-30% Health - Cast 'Enrage' (No Repeat)");

-- Warlord Zim'bo SAI
SET @ENTRY := 26544;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,17000,11,3551,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Zim'bo - In Combat - Cast 'Skull Crack'"),
(@ENTRY,0,1,0,0,0,100,0,12000,12000,120000,130000,11,52283,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warlord Zim'bo - In Combat - Cast 'Warlord Roar'");

-- Westfall Brigade Defender SAI
SET @ENTRY := 27758;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,4500,12000,14000,11,14516,0,0,0,0,0,2,0,0,0,0,0,0,0,"Westfall Brigade Defender - In Combat - Cast 'Strike'");

-- "Scoodles" SAI
SET @ENTRY := 24899;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,12000,13000,11,50169,0,0,0,0,0,2,0,0,0,0,0,0,0,"'Scoodles' - In Combat - Cast 'Flipper Thwack'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,17500,18600,11,48287,0,0,0,0,0,2,0,0,0,0,0,0,0,"'Scoodles' - In Combat - Cast 'Powerful Bite'");

-- Blacksouled Keeper SAI
SET @ENTRY := 23875;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,43619,64,0,0,0,0,2,0,0,0,0,0,0,0,"Blacksouled Keeper - In Combat - Cast 'Wrath'");

-- Bloodthirsty Worg SAI
SET @ENTRY := 24475;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,16000,18000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodthirsty Worg - In Combat - Cast 'Infected Bite'");

-- Bull Lion Seal SAI
SET @ENTRY := 23886;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,11000,12000,11,50169,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bull Lion Seal - In Combat - Cast 'Flipper Thwack'");

-- Caldemere Snapper SAI
SET @ENTRY := 24287;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,10000,10000,11,49978,1,0,0,0,0,2,0,0,0,0,0,0,0,"Caldemere Snapper - In Combat - Cast 'Claw Grasp'");

-- Camp Winterhoof Brave SAI
SET @ENTRY := 24031;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Camp Winterhoof Brave - In Combat - Cast 'Shoot'");

-- Captain Olster SAI
SET @ENTRY := 23962;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,27577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Olster - On Aggro - Cast 'Intercept' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,8000,11000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Olster - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,0,0,100,0,6000,8000,15000,16000,11,32588,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Olster - In Combat - Cast 'Concussion Blow'");

-- Chillmere Coastrunner SAI
SET @ENTRY := 24459;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3900,10000,12000,11,28428,0,0,0,0,0,2,32,0,0,0,0,0,0,"Chillmere Coastrunner - In Combat - Cast 'Instant Poison'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,14000,15000,11,14874,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chillmere Coastrunner - In Combat - Cast 'Rupture'");

-- Chillmere Oracle SAI
SET @ENTRY := 24461;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,49906,64,0,0,0,0,2,0,0,0,0,0,0,0,"Chillmere Oracle - In Combat - Cast 'Ice Lance'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillmere Oracle - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillmere Oracle - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,8,15800,18300,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillmere Oracle - Within 0-8 Range - Cast 'Frost Nova'"),
(@ENTRY,0,4,0,0,0,100,0,5000,5000,14000,16000,11,49935,0,0,0,0,0,5,0,0,0,0,0,0,0,"Chillmere Oracle - In Combat - Cast 'Hex of the Murloc'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Chillmere Tidehunter SAI
SET @ENTRY := 24460;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,38556,64,0,0,0,0,2,0,0,0,0,0,0,0,"Chillmere Tidehunter - In Combat - Cast 'Throw'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillmere Tidehunter - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillmere Tidehunter - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,20,6000,8000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chillmere Tidehunter - Within 0-20 Range - Cast 'Net'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Crazed Northsea Slaver SAI
SET @ENTRY := 24676;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,35,0,0,11,5915,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Northsea Slaver - Between 0-35% Health - Cast 'Crazed' (No Repeat)");

-- Daggercap Hawk SAI
SET @ENTRY := 24172;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,43187,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggercap Hawk - On Aggro - Cast 'Dive' (No Repeat)");

-- Dragonflayer Fleshripper
SET @ENTRY := 24250;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,14000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Rend'),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,18000,21000,11,35948,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Bloodthirst');

-- Dragonflayer Guardian SAI
SET @ENTRY := 27927;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,12000,15000,11,48280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Guardian - Within 0-8 Range - Cast 'Whirlwind'");

-- Dragonflayer Harpooner SAI
SET @ENTRY := 24635;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,43325,64,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Harpooner - In Combat - Cast 'Oluf's Harpoon'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,48193,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Harpooner - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Harpooner - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Dragonflayer Hunting Hound SAI
SET @ENTRY := 23994;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,14000,11,48287,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Hunting Hound - In Combat - Cast 'Powerful Bite'");

-- Dragonflayer Lieutenant SAI
SET @ENTRY := 24169;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,13000,11,48245,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Lieutenant - In Combat - Cast 'Head Slash'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,15000,16000,11,48250,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Lieutenant - In Combat - Cast 'Risky Feint'");

-- Dragonflayer Rune-Seer SAI
SET @ENTRY := 23656;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,12000,13000,11,48262,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Rune-Seer - In Combat - Cast 'Rune of Asvior'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,48264,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Rune-Seer - Between 0-30% Health - Cast 'Rune of Ubbi' (No Repeat)");

-- Dragonflayer Soulreaver SAI
SET @ENTRY := 24249;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,8000,13000,14000,11,43512,1,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Soulreaver - In Combat - Cast 'Mind Flay'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4000,18000,19000,11,11639,1,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Soulreaver - In Combat - Cast 'Shadow Word: Pain'");

-- Dragonflayer Thane SAI
SET @ENTRY := 23660;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,13000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Thane - In Combat - Cast 'Sunder Armor'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,18000,21000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Thane - In Combat - Cast 'Hamstring'");

-- Dragonflayer Tribesman SAI
SET @ENTRY := 23651;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Tribesman - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,90000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Tribesman - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,48193,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Tribesman - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Tribesman - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Dragonflayer Warrior SAI
SET @ENTRY := 23654;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,12000,15000,11,48280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Warrior - Within 0-8 Range - Cast 'Whirlwind'");

-- Ember Clutch Ancient SAI
SET @ENTRY := 23870;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,17000,11,12612,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ember Clutch Ancient - In Combat - Cast 'Stomp'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,42544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ember Clutch Ancient - Between 0-30% Health - Cast 'Rejuvenation' (No Repeat)");

-- Expedition Deathguard SAI
SET @ENTRY := 24317;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,16100,64,0,0,0,0,2,0,0,0,0,0,0,0,"Expedition Deathguard - In Combat - Cast 'Shoot'");

-- Fanggore Worg SAI
SET @ENTRY := 24026;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,13000,16000,11,50075,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fanggore Worg - In Combat - Cast 'Maim Flesh'");

-- Fearsome Horror SAI
SET @ENTRY := 24073;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,16000,18000,11,49861,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fearsome Horror - In Combat - Cast 'Infected Bite'");

-- Fjord Crawler SAI
SET @ENTRY := 24478;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,8000,11000,11,49978,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fjord Crawler - In Combat - Cast 'Claw Grasp'");

-- Fjord Crow SAI
SET @ENTRY := 23945;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,9000,12000,11,49865,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fjord Crow - In Combat - Cast 'Eye Peck'");

-- Forlorn Soul SAI
SET @ENTRY := 24789;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,14000,11,16583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forlorn Soul - In Combat - Cast 'Shadow Shock'");

-- Forsaken Deckhand SAI
SET @ENTRY := 23982;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,6000,9000,14000,11,49616,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forsaken Deckhand - In Combat - Cast 'Kidney Shot'");

-- Frostgore SAI
SET @ENTRY := 24173;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,14000,16000,11,52058,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frostgore - In Combat - Cast 'Ground Slam'");

-- Frosthorn Ram SAI
SET @ENTRY := 23740;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,11000,13000,11,29577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frosthorn Ram - In Combat - Cast 'Hoof Strike'");

-- Frostwing Chimaera SAI
SET @ENTRY := 24673;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,13000,11,16552,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostwing Chimaera - In Combat - Cast 'Venom Spit'");

-- Gjalerbron Gargoyle SAI
SET @ENTRY := 24440;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,43804,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gjalerbron Gargoyle - In Combat - Cast 'Gargoyle Strike'");

-- Harpoon Master Yavus SAI
SET @ENTRY := 24644;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,48283,64,0,0,0,0,2,0,0,0,0,0,0,0,"Harpoon Master Yavus - In Combat - Cast 'Harpoon Throw'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,12000,16000,11,48286,0,0,0,0,0,2,0,0,0,0,0,0,0,"Harpoon Master Yavus - Within 0-5 Range - Cast 'Grievous Slash'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,48193,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harpoon Master Yavus - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harpoon Master Yavus - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Howling Wolvar Lookout SAI
SET @ENTRY := 26827;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,43413,64,0,0,0,0,2,0,0,0,0,0,0,0,"Howling Wolvar Lookout - In Combat - Cast 'Throw Spear'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Howling Wolvar Lookout - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Howling Wolvar Lookout - Between 0-15% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Howling Wolvar Shaman SAI
SET @ENTRY := 26825;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,26098,64,0,0,0,0,2,0,0,0,0,0,0,0,"Howling Wolvar Shaman - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Howling Wolvar Shaman - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Howling Wolvar Shaman - Between 0-15% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Howling Wolvar Trainer SAI
SET @ENTRY := 26823;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,12000,11,49453,0,0,0,0,0,2,0,0,0,0,0,0,0,"Howling Wolvar Trainer - Within 0-20 Range - Cast 'Wolvar Net'"),
(@ENTRY,0,1,0,2,0,100,0,0,30,8000,9000,11,50054,0,0,0,0,0,1,0,0,0,0,0,0,0,"Howling Wolvar Trainer - Between 0-30% Health - Cast 'Quick Feet'"),
(@ENTRY,0,2,0,13,0,100,0,12000,18000,0,0,11,12555,0,0,0,0,0,6,1,0,0,0,0,0,0,"Howling Wolvar Trainer - On Victim Casting - Cast 'Pummel'");

-- Ice Elemental SAI
SET @ENTRY := 23919;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,5,30,8000,9000,11,43543,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Elemental - Within 5-30 Range - Cast 'Throw Ice'");

-- Icehollow Behemoth SAI
SET @ENTRY := 23744;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,14000,17000,11,12734,0,0,0,0,0,1,0,0,0,0,0,0,0,"Icehollow Behemoth - In Combat - Cast 'Ground Smash'");

-- Hozzer SAI
SET @ENTRY := 24547;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,14000,15600,11,64319,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hozzer - In Combat - Cast 'Knockback'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,9000,11000,11,34298,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hozzer - In Combat - Cast 'Maul'");

-- Iron Rune Sentinel SAI
SET @ENTRY := 24316;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,13600,16800,11,48416,0,0,0,0,0,1,0,0,0,0,0,0,0,"Iron Rune Sentinel - In Combat - Cast 'Rune Detonation'");

-- Island Shoveltusk SAI
SET @ENTRY := 24681;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,18000,21000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Island Shoveltusk - In Combat - Cast 'Gore'");

-- Iron Rune Sage SAI
SET @ENTRY := 23674;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Sage - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,14000,15000,11,20828,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Sage - Within 0-10 Range - Cast 'Cone of Cold'");

-- Iron Rune Laborer SAI
SET @ENTRY := 23711;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,10000,17000,11,48374,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Laborer - In Combat - Cast 'Puncture Wound'");

-- Iron Rune Guardian SAI
SET @ENTRY := 24212;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,49643,0,0,0,0,0,1,0,0,0,0,0,0,0,"Iron Rune Guardian - On Aggro - Cast 'Guardian Rune' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3000,4000,9000,12000,11,49644,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Guardian - In Combat - Cast 'Guardian Strike'");

-- Iron Rune Destroyer SAI
SET @ENTRY := 23676;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,13000,14000,11,48376,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Destroyer - In Combat - Cast 'Hammer Blow'");

-- Iron Rune Binder SAI
SET @ENTRY := 23796;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,15000,17000,11,15039,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Binder - In Combat - Cast 'Flame Shock'"),
(@ENTRY,0,1,0,0,0,100,0,6000,7000,11000,19000,11,48599,0,0,0,0,0,2,0,0,0,0,0,0,0,"Iron Rune Binder - In Combat - Cast 'Rune of Binding'");

-- Keeper Witherleaf SAI
SET @ENTRY := 24638;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,43619,64,0,0,0,0,2,0,0,0,0,0,0,0,"Keeper Witherleaf - In Combat - Cast 'Wrath'");

-- Lieutenant Celeyne SAI
SET @ENTRY := 23964;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,27577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Celeyne - On Aggro - Cast 'Intercept' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,8000,11000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Celeyne - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,0,0,100,0,6000,8000,15000,16000,11,32588,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Celeyne - In Combat - Cast 'Concussion Blow'");

-- Lion Seal SAI
SET @ENTRY := 23887;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,12000,13000,11,50169,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lion Seal - In Combat - Cast 'Flipper Thwack'");

-- Mur'ghoul Corrupter
SET @ENTRY := 23645;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,4900,16500,18900,11,32063,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Corruption');

-- Mur'ghoul Corrupter SAI
SET @ENTRY := 23645;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,4900,16500,18900,11,32063,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mur'ghoul Corrupter - In Combat - Cast 'Corruption'");

-- Megalith SAI
SET @ENTRY := 24371;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,5,30,8000,11000,11,50086,0,0,0,0,0,2,0,0,0,0,0,0,0,"Megalith - Within 5-30 Range - Cast 'Boulder'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,18000,11,50084,0,0,0,0,0,2,0,0,0,0,0,0,0,"Megalith - Within 0-5 Range - Cast 'Hulking Uppercut'");

-- Necrotech SAI
SET @ENTRY := 24540;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Necrotech - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Necrotech - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Necrotech - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,0,0,50,8000,14000,11,17173,0,0,0,0,0,2,1,0,0,0,0,0,0,"Necrotech - Between 0-50% Health - Cast 'Drain Life'"),
(@ENTRY,0,4,0,0,0,100,0,5000,5000,32000,35000,11,18267,0,0,0,0,0,2,0,0,0,0,0,0,0,"Necrotech - In Combat - Cast 'Curse of Weakness'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Mutinous Sea Dog SAI
SET @ENTRY := 25026;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,17000,19000,11,33912,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mutinous Sea Dog - In Combat - Cast 'Rip'");

-- North Fleet Marine SAI
SET @ENTRY := 23983;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Marine - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Marine - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Marine - Between 0-15% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- North Fleet Medic SAI
SET @ENTRY := 23794;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9734,64,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Medic - In Combat - Cast 'Holy Smite'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Medic - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Medic - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,14,0,100,0,3000,40,15000,18000,11,11640,0,0,0,0,0,7,0,0,0,0,0,0,0,"North Fleet Medic - Friendly At 3000 Health - Cast 'Renew'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- North Fleet Soldier SAI
SET @ENTRY := 23793;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,12000,13000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Soldier - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,17000,18000,11,12054,0,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Soldier - In Combat - Cast 'Rend'");

-- North Fleet Marksman SAI
SET @ENTRY := 23946;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Marksman - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Marksman - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"North Fleet Marksman - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,5000,5000,17000,18000,11,30933,0,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Marksman - In Combat - Cast 'Volley'"),
(@ENTRY,0,4,0,0,0,100,0,8500,9500,14600,19600,11,20902,0,0,0,0,0,2,0,0,0,0,0,0,0,"North Fleet Marksman - In Combat - Cast 'Aimed Shot'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Proto-Whelp SAI
SET @ENTRY := 23688;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,14000,11,51218,0,0,0,0,0,2,0,0,0,0,0,0,0,"Proto-Whelp - In Combat - Cast 'Flame Breath'");

-- Proto-Whelp Hatchling SAI
SET @ENTRY := 23750;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,14000,11,51218,0,0,0,0,0,2,0,0,0,0,0,0,0,"Proto-Whelp Hatchling - In Combat - Cast 'Flame Breath'");

-- Putrid Wight SAI
SET @ENTRY := 23992;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,23,0,100,0,21862,0,2000,2000,11,21862,0,0,0,0,0,1,0,0,0,0,0,0,0,"Putrid Wight - On Has Aura 'Radiation' - Cast 'Radiation'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,43506,0,0,0,0,0,1,0,0,0,0,0,0,0,"Putrid Wight - On Aggro - Cast 'Plague Blight' (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,10,15000,18000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"Putrid Wight - Within 0-10 Range - Cast 'Thunderclap'");

-- Rabid Brown Bear SAI
SET @ENTRY := 24633;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,9000,11000,11,34298,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rabid Brown Bear - In Combat - Cast 'Maul'");

-- Reef Cow SAI
SET @ENTRY := 24797;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,12000,13000,11,50169,0,0,0,0,0,2,0,0,0,0,0,0,0,"Reef Cow - In Combat - Cast 'Flipper Thwack'");

-- Risen Vrykul Ancestor SAI
SET @ENTRY := 24871;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,16000,18000,11,49841,0,0,0,0,0,2,0,0,0,0,0,0,0,"Risen Vrykul Ancestor - In Combat - Cast 'Perturbing Strike'");

-- Rotgill SAI
SET @ENTRY := 24546;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,11000,14000,11,49956,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rotgill - In Combat - Cast 'Searing Wound'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rotgill - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rotgill - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Sepulchral Overseer SAI
SET @ENTRY := 23993;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,12737,64,0,0,0,0,2,0,0,0,0,0,0,0,"Sepulchral Overseer - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,120000,120000,11,43556,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sepulchral Overseer - In Combat - Cast 'Curse of the Sepulcher'"),
(@ENTRY,0,2,0,9,0,100,0,0,35,7000,9000,11,22744,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sepulchral Overseer - Within 0-35 Range - Cast 'Chains of Ice'");

-- Sergeant Gorth SAI
SET @ENTRY := 24027;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,10000,12000,11,22427,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sergeant Gorth - In Combat - Cast 'Concussion Blow'");

-- Servitor Shade SAI
SET @ENTRY := 24485;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,11000,13000,11,16583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Servitor Shade - In Combat - Cast 'Shadow Shock'"),
(@ENTRY,0,1,0,9,0,100,0,8,40,9000,11000,11,49961,0,0,0,0,0,2,0,0,0,0,0,0,0,"Servitor Shade - Within 8-40 Range - Cast 'Blink Strike'");

-- Shoveltusk SAI
SET @ENTRY := 23690;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,10500,14500,11,42320,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shoveltusk - In Combat - Cast 'Head Butt'");

-- Shoveltusk Calf SAI
SET @ENTRY := 24791;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,10500,14500,11,42320,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shoveltusk Calf - In Combat - Cast 'Head Butt'");

-- Shoveltusk Forager SAI
SET @ENTRY := 29479;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,3000,17000,19000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shoveltusk Forager - In Combat - Cast 'Gore'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,55860,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shoveltusk Forager - On Aggro - Cast 'Shoveltusk Charge' (No Repeat)");

-- Shoveltusk Stag SAI
SET @ENTRY := 23691;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,3000,17000,19000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shoveltusk Stag - In Combat - Cast 'Gore'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,55860,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shoveltusk Stag - On Aggro - Cast 'Shoveltusk Charge' (No Repeat)");

-- Skeld Drakeson SAI
SET @ENTRY := 23940;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,19471,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skeld Drakeson - On Aggro - Cast 'Berserker Charge' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,10,22000,24500,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skeld Drakeson - Within 0-10 Range - Cast 'Demoralizing Shout'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skeld Drakeson - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skeld Drakeson - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Sergeant Lorric SAI
SET @ENTRY := 23963;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,18545,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sergeant Lorric - On Aggro - Cast 'Scorpid Sting' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,10,8000,12000,11,23601,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sergeant Lorric - Within 0-10 Range - Cast 'Scatter Shot'");

-- Spearfang Worg SAI
SET @ENTRY := 24677;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,14500,16800,11,50075,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spearfang Worg - In Combat - Cast 'Maim Flesh'");

-- Spotted Hippogryph SAI
SET @ENTRY := 23772;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,49865,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spotted Hippogryph - On Aggro - Cast 'Eye Peck' (No Repeat)");

-- Tamed Proto-Whelp SAI
SET @ENTRY := 23882;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,11000,14000,11,11021,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tamed Proto-Whelp - In Combat - Cast 'Flamespit'");

-- Storm Giant SAI
SET @ENTRY := 24812;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,16000,18000,11,50084,0,0,0,0,0,2,0,0,0,0,0,0,0,"Storm Giant - In Combat - Cast 'Hulking Uppercut'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4000,12000,15000,11,50100,0,0,0,0,0,2,0,0,0,0,0,0,0,"Storm Giant - In Combat - Cast 'Stormbolt'"),
(@ENTRY,0,2,0,0,0,100,0,7000,11000,25000,28000,11,50105,0,0,0,0,0,5,0,0,0,0,0,0,0,"Storm Giant - In Combat - Cast 'Violent Hurricane'");

-- Thornvine Creeper SAI
SET @ENTRY := 23874;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,11,33907,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thornvine Creeper - Out of Combat - Cast 'Thorns'"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,8000,9000,11,31287,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thornvine Creeper - In Combat - Cast 'Entangling Roots'");

-- Thorvald SAI
SET @ENTRY := 27926;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,16000,11,52719,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thorvald - In Combat - Cast 'Concussion Blow'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,8000,11000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thorvald - In Combat - Cast 'Sunder Armor'");

-- Unstable Mur'ghoul SAI
SET @ENTRY := 23643;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,11,49948,3,0,0,0,0,1,0,0,0,0,0,0,0,"Unstable Mur'ghoul - On Just Died - Cast 'Unstable Explosion' (No Repeat)");

-- Varg SAI
SET @ENTRY := 24517;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,52071,0,0,0,0,0,1,0,0,0,0,0,0,0,"Varg - Between 0-30% Health - Cast 'Killing Rage' (No Repeat)");

-- Vengeance Landing Deathguard SAI
SET @ENTRY := 23779;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vengeance Landing Deathguard - In Combat - Cast 'Shoot'");

-- Vengeful Kvaldir Spirit SAI
SET @ENTRY := 25224;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,50106,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeful Kvaldir Spirit - On Respawn - Cast 'Disease Cloud' (No Repeat)");

-- Vengeance Bringer SAI
SET @ENTRY := 23865;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,120000,120000,11,32064,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeance Bringer - In Combat - Cast 'Battle Shout'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,9000,12000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vengeance Bringer - In Combat - Cast 'Mortal Strike'");

-- Vrykul Soul SAI
SET @ENTRY := 24262;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,50027,0,0,0,0,0,2,1,0,0,0,0,0,0,"Vrykul Soul - Between 0-50% Health - Cast 'Tug Soul' (No Repeat)");

-- Westguard Defender SAI
SET @ENTRY := 23842;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Westguard Defender - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,1,0,5,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Westguard Defender - Within 0-5 Range - Cast 'Defensive Stance' (No Repeat)");

-- Westguard Officer SAI
SET @ENTRY := 23844;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Westguard Officer - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,1,0,5,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Westguard Officer - Within 0-5 Range - Cast 'Defensive Stance' (No Repeat)");

-- Westguard Rifleman SAI
SET @ENTRY := 24197;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Westguard Rifleman - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,1,0,5,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Westguard Rifleman - Within 0-5 Range - Cast 'Defensive Stance' (No Repeat)");

-- Wild Worg SAI
SET @ENTRY := 24128;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,12000,13000,11,48287,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wild Worg - In Combat - Cast 'Powerful Bite'");

-- Wildervar Sentry SAI
SET @ENTRY := 24050;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wildervar Sentry - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,13000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wildervar Sentry - Within 0-5 Range - Cast 'Shield Block'"),
(@ENTRY,0,2,0,0,0,100,0,8000,8000,12000,16000,11,12170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wildervar Sentry - In Combat - Cast 'Revenge'");

-- Winterhoof Longrunner SAI
SET @ENTRY := 24195;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterhoof Longrunner - In Combat - Cast 'Shoot'");

-- Winterskorn Bonegrinder SAI
SET @ENTRY := 23655;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,12000,13000,11,43951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Bonegrinder - In Combat - Cast 'Bonegrinder'");

-- Winterskorn Hunter SAI
SET @ENTRY := 26663;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Hunter - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,19000,22000,11,18651,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Hunter - In Combat - Cast 'Multi-Shot'"),
(@ENTRY,0,2,0,2,0,100,1,0,35,0,0,11,36828,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterskorn Hunter - Between 0-35% Health - Cast 'Rapid Fire' (No Repeat)");

-- Winterskorn Skald SAI
SET @ENTRY := 23657;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Skald - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,13000,15000,11,11829,0,0,0,0,0,5,0,0,0,0,0,0,0,"Winterskorn Skald - In Combat - Cast 'Flamestrike'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4000,35000,36000,11,37844,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterskorn Skald - In Combat - Cast 'Fire Ward'");

-- Winterskorn Scout SAI
SET @ENTRY := 24116;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,13000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Scout - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,22000,25000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterskorn Scout - Within 0-10 Range - Cast 'Demoralizing Shout'"),
(@ENTRY,0,2,0,0,0,100,0,8000,8000,15000,17000,11,18812,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Scout - In Combat - Cast 'Knockdown'");

-- Yanis the Mystic SAI
SET @ENTRY := 23932;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,42870,64,0,0,0,0,2,0,0,0,0,0,0,0,"Yanis the Mystic - In Combat - Cast 'Throw Dragonflayer Harpoon'");

-- Winterskorn Spearman SAI
SET @ENTRY := 23653;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,55217,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Spearman - In Combat - Cast 'Throw Spear'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,60000,60000,11,43414,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterskorn Spearman - Within 0-5 Range - Cast 'Freezing Trap'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,12000,13000,11,32908,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterskorn Spearman - In Combat - Cast 'Wing Clip'");

-- Wyrmcaller Vile SAI
SET @ENTRY := 24029;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcaller Vile - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcaller Vile - Out of Combat - Cast 'Frost Armor'"),
(@ENTRY,0,2,0,9,0,100,0,0,10,14000,18000,11,15532,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcaller Vile - Within 0-10 Range - Cast 'Frost Nova'");

-- Aldur'thar Sentry SAI
SET @ENTRY := 32323;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8800,11300,16800,11,16564,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aldur'thar Sentry - In Combat - Cast 'Gargoyle Strike'");

-- Animated Laborer SAI
SET @ENTRY := 32267;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3400,9900,11500,17800,11,48374,0,0,0,0,0,2,0,0,0,0,0,0,0,"Animated Laborer - In Combat - Cast 'Puncture Wound'");

-- Argent Paladin SAI
SET @ENTRY := 30704;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6700,8900,15600,21300,11,58127,0,0,0,0,0,2,0,0,0,0,0,0,0,"Argent Paladin - In Combat - Cast 'Divine Storm'");

-- Argent Peacekeeper SAI
SET @ENTRY := 34179;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,5100,11500,19800,11,63861,0,0,0,0,0,5,0,0,0,0,0,0,0,"Argent Peacekeeper - In Combat - Cast 'Chains of Law'");

-- Bone Giant SAI
SET @ENTRY := 31815;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,11200,12300,16700,27900,11,36405,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Giant - In Combat - Cast 'Stomp'");

-- Bone Guard SAI
SET @ENTRY := 32479;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4900,11200,10800,18500,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Guard - In Combat - Cast 'Mortal Strike'");

-- Bone Sentinel SAI
SET @ENTRY := 32299;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,10700,12300,16500,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Sentinel - In Combat - Cast 'Mortal Strike'");

-- Carrion Fleshstripper SAI
SET @ENTRY := 30206;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,25600,29700,11,35201,0,0,0,0,0,2,0,0,0,0,0,0,0,"Carrion Fleshstripper - In Combat - Cast 'Paralytic Poison'");

-- Carrion Hunter SAI
SET @ENTRY := 31263;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,6700,11300,15600,11,24187,0,0,0,0,0,2,0,0,0,0,0,0,0,"Carrion Hunter - In Combat - Cast 'Claw'");

-- Chained Abomination SAI
SET @ENTRY := 30689;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,50335,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chained Abomination - On Aggro - Cast 'Scourge Hook' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5600,8900,12000,13400,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chained Abomination - In Combat - Cast 'Cleave'");

-- Corp'rethar Guardian SAI
SET @ENTRY := 32280;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3300,4900,14700,16800,11,60927,0,0,0,0,0,2,0,0,0,0,0,0,0,"Corp'rethar Guardian - In Combat - Cast 'Infected Bite'"),
(@ENTRY,0,1,0,0,0,100,0,7800,9700,19300,25600,11,54378,0,0,0,0,0,2,0,0,0,0,0,0,0,"Corp'rethar Guardian - In Combat - Cast 'Mortal Wound'");

-- Cruel Overseer SAI
SET @ENTRY := 31853;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4600,15400,7800,16200,11,6253,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cruel Overseer - In Combat - Cast 'Backhand'"),
(@ENTRY,0,1,0,0,0,100,0,10000,10000,19000,20000,11,49639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cruel Overseer - In Combat - Cast 'Crush'");

-- Crusader of Virtue SAI
SET @ENTRY := 30189;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,58053,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crusader of Virtue - Between 0-50% Health - Cast 'Holy Light' (No Repeat)");

-- Crusader of Virtue SAI
SET @ENTRY := 30672;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,58053,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crusader of Virtue - Between 0-50% Health - Cast 'Holy Light' (No Repeat)");

-- Dancing Runeblade SAI
SET @ENTRY := 32496;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,4500,11300,13500,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dancing Runeblade - In Combat - Cast 'Blood Strike'");

-- Death Knight Adept SAI
SET @ENTRY := 31325;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,60951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Frost Strike'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,3,0,0,0,100,0,15000,15000,33000,35000,11,60953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death and Decay'");

-- Death Knight Adept SAI
SET @ENTRY := 31318;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,60951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Frost Strike'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,3,0,0,0,100,0,15000,15000,33000,35000,11,60953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death and Decay'");

-- Death Knight Adept SAI
SET @ENTRY := 31042;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,60951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Frost Strike'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,3,0,0,0,100,0,15000,15000,33000,35000,11,60953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Adept - In Combat - Cast 'Death and Decay'");

-- Death Knight Initiate SAI
SET @ENTRY := 30958;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,19000,19000,11,60950,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Blood Plague'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,25000,25000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,2,0,0,0,100,0,3000,3000,11000,13000,11,60952,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Icy Touch'");

-- Death Knight Initiate SAI
SET @ENTRY := 30957;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,19000,19000,11,60950,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Blood Plague'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,25000,25000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,2,0,0,0,100,0,3000,3000,11000,13000,11,60952,0,0,0,0,0,5,0,0,0,0,0,0,0,"Death Knight Initiate - In Combat - Cast 'Icy Touch'");

-- Death Knight Master SAI
SET @ENTRY := 29738;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,7800,15000,18000,11,50688,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Knight Master - In Combat - Cast 'Plague Strike'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,50689,0,0,0,0,0,1,0,0,0,0,0,0,0,"Death Knight Master - Out of Combat - Cast 'Blood Presence'");

-- Decomposed Ghoul SAI
SET @ENTRY := 31812;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Decomposed Ghoul - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Decomposed Ghoul - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,11000,14000,11,12097,0,0,0,0,0,2,0,0,0,0,0,0,0,"Decomposed Ghoul - In Combat - Cast 'Pierce Armor'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Ebon Blade Champion SAI
SET @ENTRY := 30703;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,58130,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ebon Blade Champion - On Aggro - Cast 'Icebound Fortitude' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,18000,18000,11,50688,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Champion - In Combat - Cast 'Plague Strike'");

-- Ebon Blade Defender SAI
SET @ENTRY := 31250;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Defender - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,59131,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Defender - In Combat - Cast 'Icy Touch'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ebon Blade Defender - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,3,0,4,0,100,1,0,0,0,0,11,49576,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ebon Blade Defender - On Aggro - Cast 'Death Grip' (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,5000,8000,25000,25000,11,50688,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Defender - In Combat - Cast 'Plague Strike'");

-- Ebon Blade Vindicator SAI
SET @ENTRY := 32488;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Vindicator - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,59131,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Vindicator - In Combat - Cast 'Icy Touch'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ebon Blade Vindicator - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,3,0,4,0,100,1,0,0,0,0,11,49576,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ebon Blade Vindicator - On Aggro - Cast 'Death Grip' (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,5000,8000,25000,25000,11,50688,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ebon Blade Vindicator - In Combat - Cast 'Plague Strike'");

-- Fallen Spiderlord SAI
SET @ENTRY := 31780;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,16000,11,60802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fallen Spiderlord - In Combat - Cast 'Mandible Crush'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,23000,24500,11,50284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fallen Spiderlord - In Combat - Cast 'Blinding Swarm'");

-- Father Kamaros SAI
SET @ENTRY := 32800;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,25054,64,0,0,0,0,2,0,0,0,0,0,0,0,"Father Kamaros - In Combat - Cast 'Holy Smite'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6200,11700,15600,11,17146,0,0,0,0,0,5,0,0,0,0,0,0,0,"Father Kamaros - In Combat - Cast 'Shadow Word: Pain'"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,11,32595,0,0,0,0,0,1,0,0,0,0,0,0,0,"Father Kamaros - Between 0-50% Health - Cast 'Power Word: Shield' (No Repeat)");

-- Foreman Thaldrin SAI
SET @ENTRY := 31399;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,4300,12300,13300,11,59992,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Thaldrin - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,6000,6000,7000,16000,11,21401,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Thaldrin - In Combat - Cast 'Frost Shock'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,25000,27000,11,16509,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Thaldrin - In Combat - Cast 'Rend'"),
(@ENTRY,0,3,0,0,0,50,0,5000,5000,19000,39000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Thaldrin - In Combat - Cast 'Strike'");

-- Forgotten Depths Acolyte SAI
SET @ENTRY := 30205;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,3500,11500,13500,11,16583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Acolyte - In Combat - Cast 'Shadow Shock'"),
(@ENTRY,0,1,0,0,0,100,0,5500,6500,35000,35000,11,60781,0,0,0,0,0,5,0,0,0,0,0,0,0,"Forgotten Depths Acolyte - In Combat - Cast 'Curse of Mending'");

-- Forgotten Depths Slayer SAI
SET @ENTRY := 30333;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5400,11500,12500,11,54185,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Slayer - In Combat - Cast 'Claw Slash'");

-- Forgotten Depths Underking SAI
SET @ENTRY := 31039;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,16000,11,60802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Mandible Crush'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,23000,24500,11,50284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Blinding Swarm'");

-- Forgotten Depths Underking SAI
SET @ENTRY := 30544;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,16000,11,60802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Mandible Crush'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,23000,24500,11,50284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Blinding Swarm'");

-- Forgotten Depths Underking SAI
SET @ENTRY := 30541;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,16000,11,60802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Mandible Crush'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,23000,24500,11,50284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Forgotten Depths Underking - In Combat - Cast 'Blinding Swarm'");

-- Frostbrood Matriarch SAI
SET @ENTRY := 32492;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,19800,23400,11,60667,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostbrood Matriarch - In Combat - Cast 'Frost Breath'");

-- Frostbrood Sentry SAI
SET @ENTRY := 31721;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,12000,14500,11,60542,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostbrood Sentry - In Combat - Cast 'Bitter Blast'");

-- Frostskull Magus SAI
SET @ENTRY := 31813;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20297,64,0,0,0,0,2,0,0,0,0,0,0,0,"Frostskull Magus - In Combat - Cast 'Frostbolt'");

-- Gargoyle Ambusher SAI
SET @ENTRY := 32188;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,5500,11300,14500,11,60239,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gargoyle Ambusher - In Combat - Cast 'Gargoyle Ambusher Strike'");

-- Harbinger of Horror SAI
SET @ENTRY := 32278;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,61747,64,0,0,0,0,2,0,0,0,0,0,0,0,"Harbinger of Horror - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,18100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harbinger of Horror - Out of Combat - Cast 'Frost Armor'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,17800,19900,11,60924,0,0,0,0,0,2,0,0,0,0,0,0,0,"Harbinger of Horror - In Combat - Cast 'Lich Slap'"),
(@ENTRY,0,3,0,0,0,100,0,7800,9800,60000,60000,11,59663,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harbinger of Horror - In Combat - Cast 'Deathchill Empowerment'"),
(@ENTRY,0,4,0,0,0,100,0,3400,12300,28900,29800,11,18099,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harbinger of Horror - In Combat - Cast 'Chill Nova'");

-- Intrepid Ghoul SAI
SET @ENTRY := 31015;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,4900,17800,19800,11,60873,0,0,0,0,0,2,0,0,0,0,0,0,0,"Intrepid Ghoul - In Combat - Cast 'Festering Bite'"),
(@ENTRY,0,1,0,0,0,100,0,12000,14000,23000,26000,11,60872,0,0,0,0,0,2,1,0,0,0,0,0,0,"Intrepid Ghoul - In Combat - Cast 'Ravenous Claw'"),
(@ENTRY,0,2,0,6,0,100,1,0,0,0,0,11,58137,0,0,0,0,0,1,0,0,0,0,0,0,0,"Intrepid Ghoul - On Just Died - Cast 'Ghoulplosion' (No Repeat)");

-- Kor'kron Reaver SAI
SET @ENTRY := 30755;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Reaver - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Reaver - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Reaver - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,4500,5400,11800,13500,11,12024,0,0,0,0,0,5,0,0,0,0,0,0,0,"Kor'kron Reaver - In Combat - Cast 'Net'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Kul'galar Oracle SAI
SET @ENTRY := 30751;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,45,0,0,11,11642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kul'galar Oracle - Between 0-45% Health - Cast 'Heal' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,13400,15700,11,31516,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kul'galar Oracle - In Combat - Cast 'Mind Blast'"),
(@ENTRY,0,2,0,0,0,100,0,9900,9900,17400,19800,11,16568,0,0,0,0,0,5,1,0,0,0,0,0,0,"Kul'galar Oracle - In Combat - Cast 'Mind Flay'");

-- Lumbering Atrocity SAI
SET @ENTRY := 31226;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,12000,12000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lumbering Atrocity - In Combat - Cast 'Cleave'");

-- Malithus Brightblade SAI
SET @ENTRY := 36120;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17800,19600,11,66004,0,0,0,0,0,1,0,0,0,0,0,0,0,"Malithus Brightblade - In Combat - Cast 'Seal of Command'");

-- Master Summoner Zarod SAI
SET @ENTRY := 30746;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,61747,64,0,0,0,0,2,0,0,0,0,0,0,0,"Master Summoner Zarod - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,18100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Master Summoner Zarod - Out of Combat - Cast 'Frost Armor'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,17800,19900,11,60924,0,0,0,0,0,2,0,0,0,0,0,0,0,"Master Summoner Zarod - In Combat - Cast 'Lich Slap'"),
(@ENTRY,0,3,0,0,0,100,0,7800,9800,15800,25600,11,12096,0,0,0,0,0,5,0,0,0,0,0,0,0,"Master Summoner Zarod - In Combat - Cast 'Fear'"),
(@ENTRY,0,4,0,0,0,100,0,3400,12300,28900,29800,11,18099,0,0,0,0,0,1,0,0,0,0,0,0,0,"Master Summoner Zarod - In Combat - Cast 'Chill Nova'");

-- Morbid Carcass SAI
SET @ENTRY := 29719;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,50335,0,0,0,0,0,2,0,0,0,0,0,0,0,"Morbid Carcass - On Aggro - Cast 'Scourge Hook' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,11000,13000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Morbid Carcass - In Combat - Cast 'Cleave'");

-- Necrotic Webspinner SAI
SET @ENTRY := 31747;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,12000,11,744,0,0,0,0,0,2,32,0,0,0,0,0,0,"Necrotic Webspinner - In Combat - Cast 'Poison'"),
(@ENTRY,0,1,0,0,0,100,0,3000,9000,11000,19000,11,745,0,0,0,0,0,5,0,0,0,0,0,0,0,"Necrotic Webspinner - In Combat - Cast 'Web'");

-- Onslaught Destrier SAI
SET @ENTRY := 29710;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,12000,14300,11,29577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Onslaught Destrier - In Combat - Cast 'Hoof Strike'");

-- Reanimated Miner SAI
SET @ENTRY := 31843;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11300,13400,11,48374,0,0,0,0,0,2,0,0,0,0,0,0,0,"Reanimated Miner - In Combat - Cast 'Puncture Wound'");

-- Rabid Cannibal SAI
SET @ENTRY := 29722;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17000,21000,11,30639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rabid Cannibal - In Combat - Cast 'Carnivorous Bite'");

-- Reanimated Crusader SAI
SET @ENTRY := 31043;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32674,0,0,0,0,0,2,0,0,0,0,0,0,0,"Reanimated Crusader - On Aggro - Cast 'Avenger's Shield' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,17800,19800,11,58154,0,0,0,0,0,2,0,0,0,0,0,0,0,"Reanimated Crusader - In Combat - Cast 'Hammer of Injustice'"),
(@ENTRY,0,2,0,2,0,100,1,0,45,0,0,11,58153,0,0,0,0,0,1,0,0,0,0,0,0,0,"Reanimated Crusader - Between 0-45% Health - Cast 'Unholy Light' (No Repeat)"),
(@ENTRY,0,3,0,14,0,100,0,4000,10,20000,30000,11,58153,0,0,0,0,0,7,0,0,0,0,0,0,0,"Reanimated Crusader - Friendly At 4000 Health - Cast 'Unholy Light'");

-- Ravaged Ghoul SAI
SET @ENTRY := 32502;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,4900,17800,19800,11,60873,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravaged Ghoul - In Combat - Cast 'Festering Bite'"),
(@ENTRY,0,1,0,0,0,100,0,12000,14000,23000,26000,11,60872,0,0,0,0,0,2,1,0,0,0,0,0,0,"Ravaged Ghoul - In Combat - Cast 'Ravenous Claw'");

-- Restless Lookout SAI
SET @ENTRY := 31554;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,59208,0,0,0,0,0,1,0,0,0,0,0,0,0,"Restless Lookout - Between 0-30% Health - Cast 'Enraged' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Restless Lookout - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,13400,15600,11,46202,0,0,0,0,0,2,0,0,0,0,0,0,0,"Restless Lookout - In Combat - Cast 'Pierce Armor'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Pustulent Colossus SAI
SET @ENTRY := 32482;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,11200,12300,16700,27900,11,63546,0,0,0,0,0,1,0,0,0,0,0,0,0,"Pustulent Colossus - In Combat - Cast 'Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,23000,25000,11,28405,0,0,0,0,0,2,0,0,0,0,0,0,0,"Pustulent Colossus - In Combat - Cast 'Knockback'");

-- Putrid Colossus SAI
SET @ENTRY := 30697;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,11200,12300,16700,27900,11,63546,0,0,0,0,0,1,0,0,0,0,0,0,0,"Putrid Colossus - In Combat - Cast 'Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,23000,25000,11,28405,0,0,0,0,0,2,0,0,0,0,0,0,0,"Putrid Colossus - In Combat - Cast 'Knockback'");

-- Scourge Death Knight SAI
SET @ENTRY := 32486;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,12000,11,60945,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scourge Death Knight - In Combat - Cast 'Blood Strike'"),
(@ENTRY,0,1,0,0,0,70,0,3300,3300,16000,16000,11,60951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scourge Death Knight - In Combat - Cast 'Frost Strike'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0,0,0,0,"Scourge Death Knight - In Combat - Cast 'Death Coil'");

-- Scourge Deathcharger SAI
SET @ENTRY := 32490;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,12000,14300,11,29577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scourge Deathcharger - In Combat - Cast 'Hoof Strike'"),
(@ENTRY,0,1,0,0,0,100,0,10000,10000,33000,34000,11,29323,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scourge Deathcharger - In Combat - Cast 'Absorb Vitality'");

-- Scourge Soulbinder SAI
SET @ENTRY := 32284;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,60814,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scourge Soulbinder - In Combat - Cast 'Frost Blast'"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,11,17620,0,0,0,0,0,2,1,0,0,0,0,0,0,"Scourge Soulbinder - Between 0-50% Health - Cast 'Drain Life' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,15700,17800,11,22744,0,0,0,0,0,5,0,0,0,0,0,0,0,"Scourge Soulbinder - In Combat - Cast 'Chains of Ice'");

-- Scourgebeak Fleshripper SAI
SET @ENTRY := 30988;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11200,14500,11,55079,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scourgebeak Fleshripper - In Combat - Cast 'Swoop'");

-- Saronite Shaper SAI
SET @ENTRY := 31255;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7900,9800,23400,27800,11,60960,0,0,0,0,0,1,0,0,0,0,0,0,0,"Saronite Shaper - In Combat - Cast 'War Stomp'");

-- Savage Proto-Drake SAI
SET @ENTRY := 31265;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,16700,18900,11,51219,0,0,0,0,0,2,0,0,0,0,0,0,0,"Savage Proto-Drake - In Combat - Cast 'Flame Breath'"),
(@ENTRY,0,1,0,0,0,100,0,9900,11200,23400,27800,11,41572,0,0,0,0,0,2,0,0,0,0,0,0,0,"Savage Proto-Drake - In Combat - Cast 'Wing Buffet'");

-- Shadow Vault Abomination SAI
SET @ENTRY := 31438;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17800,18600,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadow Vault Abomination - In Combat - Cast 'Trample'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,25600,27600,11,16790,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadow Vault Abomination - In Combat - Cast 'Knockdown'");

-- Shadow Vault Boneguard SAI
SET @ENTRY := 30312;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,12300,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Vault Boneguard - In Combat - Cast 'Net'");

-- Shambling Zombie SAI
SET @ENTRY := 32503;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,16800,18900,11,61095,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shambling Zombie - In Combat - Cast 'Plague Blast'");

-- Shambling Zombie SAI
SET @ENTRY := 32499;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,16800,18900,11,61095,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shambling Zombie - In Combat - Cast 'Plague Blast'");

-- Shambling Zombie SAI
SET @ENTRY := 32503;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,16800,18900,11,61095,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shambling Zombie - In Combat - Cast 'Plague Blast'");

-- Skeletal Runesmith SAI
SET @ENTRY := 31321;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,4900,11300,14500,11,42724,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skeletal Runesmith - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,3000,9000,19000,19000,11,46202,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skeletal Runesmith - In Combat - Cast 'Pierce Armor'");

-- Sky-Reaver Korm Blackscar SAI
SET @ENTRY := 30824;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,13400,14500,11,42724,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sky-Reaver Korm Blackscar - In Combat - Cast 'Cleave'");

-- Skeletal Craftsman SAI
SET @ENTRY := 32164;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,4900,11300,14500,11,42724,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skeletal Craftsman - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,3000,9000,19000,19000,11,46202,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skeletal Craftsman - In Combat - Cast 'Pierce Armor'");

-- Umbral Brute SAI
SET @ENTRY := 31320;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,13500,16800,11,13446,0,0,0,0,0,2,0,0,0,0,0,0,0,"Umbral Brute - In Combat - Cast 'Strike'"),
(@ENTRY,0,1,0,0,0,100,0,9000,11000,21000,26000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Umbral Brute - In Combat - Cast 'Uppercut'");

-- Vault Geist SAI
SET @ENTRY := 29720;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,16000,17000,11,36590,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vault Geist - In Combat - Cast 'Rip'");

-- Water Terror SAI
SET @ENTRY := 30633;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,60869,64,0,0,0,0,2,0,0,0,0,0,0,0,"Water Terror - In Combat - Cast 'Water Bolt'");

-- Wrathstrike Gargoyle SAI
SET @ENTRY := 30482;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,13400,16700,11,16564,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrathstrike Gargoyle - In Combat - Cast 'Gargoyle Strike'");

-- Wrathstrike Gargoyle SAI
SET @ENTRY := 31040;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,13400,16700,11,16564,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrathstrike Gargoyle - In Combat - Cast 'Gargoyle Strike'");

-- Vindicator Maraad SAI
SET @ENTRY := 30833;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4500,6700,13400,16700,11,17281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vindicator Maraad - In Combat - Cast 'Crusader Strike'"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,11,29427,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vindicator Maraad - Between 0-50% Health - Cast 'Holy Light' (No Repeat)");

-- Valiance Commando SAI
SET @ENTRY := 31414;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Commando - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3500,15600,17800,11,31567,0,0,0,0,0,1,0,0,0,0,0,0,0,"Valiance Commando - In Combat - Cast 'Deterrence'"),
(@ENTRY,0,2,0,0,0,100,0,9000,9000,34500,37800,11,35918,0,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Commando - In Combat - Cast 'Puncture Armor'");

-- Thexal Deathchill SAI
SET @ENTRY := 31775;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,61747,64,0,0,0,0,2,0,0,0,0,0,0,0,"Thexal Deathchill - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,18100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thexal Deathchill - Out of Combat - Cast 'Frost Armor'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,17800,19900,11,60924,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thexal Deathchill - In Combat - Cast 'Lich Slap'"),
(@ENTRY,0,3,0,0,0,100,0,7800,9800,60000,60000,11,59663,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thexal Deathchill - In Combat - Cast 'Deathchill Empowerment'"),
(@ENTRY,0,4,0,0,0,100,0,3400,12300,28900,29800,11,18099,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thexal Deathchill - In Combat - Cast 'Chill Nova'");

-- Warsong Raider SAI
SET @ENTRY := 31435;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,27577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Raider - On Aggro - Cast 'Intercept' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,12000,14000,11,25710,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Raider - In Combat - Cast 'Heroic Strike'"),
(@ENTRY,0,2,0,0,0,100,0,9000,9000,25000,27800,11,25710,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warsong Raider - In Combat - Cast 'Heroic Strike'");

-- Geen SAI
SET @ENTRY := 31910;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,15504,0,0,0,0,0,1,0,0,0,0,0,0,0,"Geen - Between 0-50% Health - Cast 'Drink Healing Potion' (No Repeat)");

-- Foreman Swindlegrin SAI
SET @ENTRY := 28186;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,12000,13000,11,36228,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Swindlegrin - In Combat - Cast 'Chainsaw Blade'");

-- Iron Sentinel SAI
SET @ENTRY := 29984;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,12000,12000,15000,11,56490,0,0,0,0,0,1,0,0,0,0,0,0,0,"Iron Sentinel - In Combat - Cast 'Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,1000,5000,12000,18000,11,55811,0,0,0,0,0,5,0,0,0,0,0,0,0,"Iron Sentinel - In Combat - Cast 'Throw Boulder'");

-- Skoll SAI
SET @ENTRY := 35189;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,61184,0,0,0,0,0,2,1,0,0,0,0,0,0,"Skoll - On Aggro - Cast 'Pounce' (No Repeat)");

-- Valiance Expedition Champion SAI
SET @ENTRY := 30740;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,6800,11700,12800,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Expedition Champion - In Combat - Cast 'Strike'");

-- Valiance Expedition Guard SAI
SET @ENTRY := 32308;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,6800,11700,12800,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Valiance Expedition Guard - In Combat - Cast 'Strike'");

-- Tempest Revenant SAI
SET @ENTRY := 30875;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17800,22400,11,56620,0,0,0,0,0,2,1,0,0,0,0,0,0,"Tempest Revenant - In Combat - Cast 'Seething Flames'");

-- Wandering Shadow SAI
SET @ENTRY := 30842;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,14000,11,38240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wandering Shadow - In Combat - Cast 'Chilling Touch'"),
(@ENTRY,0,1,0,0,0,100,0,3000,9000,29800,35600,11,18267,0,0,0,0,0,5,0,0,0,0,0,0,0,"Wandering Shadow - In Combat - Cast 'Curse of Weakness'");

-- Warsong Champion SAI
SET @ENTRY := 30739;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,6800,11700,12800,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Champion - In Combat - Cast 'Strike'");

-- Warsong Guard SAI
SET @ENTRY := 32307;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4700,6800,11700,12800,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warsong Guard - In Combat - Cast 'Strike'");

-- Chilled Earth Elemental SAI
SET @ENTRY := 30849;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,5,30,4500,5000,11,43543,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chilled Earth Elemental - Within 5-30 Range - Cast 'Throw Ice'");

-- Shadow Revenant SAI
SET @ENTRY := 30872;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,12800,16700,11,51131,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Revenant - In Combat - Cast 'Strangulate'");

-- Alarmed Blightguard SAI
SET @ENTRY := 28745;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,500,1000,0,0,11,52060,0,0,0,0,0,1,0,0,0,0,0,0,0,"Alarmed Blightguard - Out of Combat - Cast 'Invisibility' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,6000,11000,11,33914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alarmed Blightguard - Within 0-5 Range - Cast 'Shadowstrike'");

-- Altar Warden SAI
SET @ENTRY := 28784;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,16000,11,54588,0,0,0,0,0,5,0,0,0,0,0,0,0,"Altar Warden - Within 0-5 Range - Cast 'Gust of Wind'"),
(@ENTRY,0,1,0,0,0,100,0,5000,11000,75000,90000,11,54589,0,0,0,0,0,1,0,0,0,0,0,0,0,"Altar Warden - In Combat - Cast 'Whirling Winds'"),
(@ENTRY,0,2,0,6,0,100,1,0,0,0,0,11,50215,3,0,0,0,0,7,0,0,0,0,0,0,0,"Altar Warden - On Just Died - Cast 'Zephyr' (No Repeat)");

-- Argent Stand Defender SAI
SET @ENTRY := 28801;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Argent Stand Defender - In Combat - Cast 'Shoot'");

-- Alarmed Blightguard SAI
SET @ENTRY := 28745;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,500,1000,0,0,11,52060,0,0,0,0,0,1,0,0,0,0,0,0,0,"Alarmed Blightguard - Out of Combat - Cast 'Invisibility' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,6000,11000,11,33914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alarmed Blightguard - Within 0-5 Range - Cast 'Shadowstrike'");

-- Bloated Abomination SAI
SET @ENTRY := 28843;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,8000,13000,11,52497,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloated Abomination - In Combat - Cast 'Flatulate'");

-- Carrion Eater SAI
SET @ENTRY := 28022;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,5000,9000,11,54387,0,0,0,0,0,2,0,0,0,0,0,0,0,"Carrion Eater - Within 0-5 Range - Cast 'Ravenous Claw'");

-- Drakkari Native SAI
SET @ENTRY := 29211;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,12000,18000,11,51307,0,0,0,0,0,1,32,0,0,0,0,0,0,"Drakkari Native - In Combat - Cast 'Unwavering Will'");

-- Drakkari Snake SAI
SET @ENTRY := 29444;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,40,7000,12000,11,25809,0,0,0,0,0,2,32,0,0,0,0,0,0,"Drakkari Snake - Within 0-40 Range - Cast 'Crippling Poison'"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,7000,12000,11,25810,0,0,0,0,0,2,32,0,0,0,0,0,0,"Drakkari Snake - In Combat - Cast 'Mind-numbing Poison'");

-- Drakkari Snake Handler SAI
SET @ENTRY := 28034;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Drakkari Snake Handler - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakkari Snake Handler - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakkari Snake Handler - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,11,54482,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakkari Snake Handler - Between 0-30% Health - Cast 'Blood of Sseratus' (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,3000,5000,20000,30000,11,54484,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakkari Snake Handler - In Combat - Cast 'Summon Drakkari Snake'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Drakuru's Guard SAI
SET @ENTRY := 28803;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,5000,8000,11,54345,0,0,0,0,0,5,0,0,0,0,0,0,0,"Drakuru's Guard - Within 0-5 Range - Cast 'Withering Strike'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakuru's Guard - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakuru's Guard - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Drakuru Raptor Rider SAI
SET @ENTRY := 29699;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Drakuru Raptor Rider - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakuru Raptor Rider - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drakuru Raptor Rider - Between 0-15% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Drek'Maz SAI
SET @ENTRY := 28918;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,13000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drek'Maz - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,1,0,0,0,100,0,8000,12000,8000,12000,11,49807,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drek'Maz - In Combat - Cast 'Whirlwind'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drek'Maz - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drek'Maz - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Flying Fiend SAI
SET @ENTRY := 28759;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,11500,13500,11,16564,0,0,0,0,0,2,0,0,0,0,0,0,0,"Flying Fiend - In Combat - Cast 'Gargoyle Strike'");

-- Gondria SAI
SET @ENTRY := 33776;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,40,18000,24000,11,61184,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gondria - Within 0-40 Range - Cast 'Pounce'");

-- Hath'ar Necromagus SAI
SET @ENTRY := 28257;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,16000,24000,30000,40000,11,51139,0,0,0,0,0,5,0,0,0,0,0,0,0,"Hath'ar Necromagus - In Combat - Cast 'Scourging Reanimation'"),
(@ENTRY,0,1,0,9,0,100,0,0,30,11000,17000,11,54491,1,0,0,0,0,2,0,0,0,0,0,0,0,"Hath'ar Necromagus - Within 0-30 Range - Cast 'Conversion Beam'");

-- Hath'ar Skimmer SAI
SET @ENTRY := 28258;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,5,30,16000,24000,11,54487,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hath'ar Skimmer - Within 5-30 Range - Cast 'Jump Attack'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,9000,18000,11,51152,0,0,0,0,0,5,32,0,0,0,0,0,0,"Hath'ar Skimmer - Within 0-5 Range - Cast 'Encasing Webs'");

-- Icetouched Earthrager SAI
SET @ENTRY := 29436;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,6000,11000,11,55216,0,0,0,0,0,5,0,0,0,0,0,0,0,"Icetouched Earthrager - In Combat - Cast 'Avalanche'");

-- Malas the Corrupter SAI
SET @ENTRY := 28255;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,12000,15000,9000,16000,11,57854,0,0,0,0,0,1,0,0,0,0,0,0,0,"Malas the Corrupter - In Combat - Cast 'Raging Shadows'"),
(@ENTRY,0,1,0,0,0,100,0,7000,10000,11000,18000,11,51676,0,0,0,0,0,2,0,0,0,0,0,0,0,"Malas the Corrupter - In Combat - Cast 'Wavering Will'"),
(@ENTRY,0,2,0,0,0,100,0,9000,16000,26000,35000,11,58579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Malas the Corrupter - In Combat - Cast 'Burning Blaze'");

-- Putrid Abomination SAI
SET @ENTRY := 28564;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,13000,18000,11,54340,0,0,0,0,0,2,0,0,0,0,0,0,0,"Putrid Abomination - Within 0-10 Range - Cast 'Vile Vomit'");

-- Prophet of Rhunok SAI
SET @ENTRY := 28442;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,7000,11000,11,16095,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prophet of Rhunok - Within 0-5 Range - Cast 'Vicious Rend'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,49758,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prophet of Rhunok - On Aggro - Cast 'Charge' (No Repeat)");

-- Rageclaw Berserker SAI
SET @ENTRY := 29437;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Berserker - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Berserker - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Rageclaw Hunter SAI
SET @ENTRY := 29439;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Rageclaw Hunter - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Hunter - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Hunter - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,9000,13000,11000,15000,11,18651,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rageclaw Hunter - In Combat - Cast 'Multi-Shot'"),
(@ENTRY,0,4,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Hunter - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,5,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Hunter - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Rageclaw Primalist SAI
SET @ENTRY := 29438;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,3400,4800,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rageclaw Primalist - Within 0-20 Range - Cast 'Frost Shock'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Primalist - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Primalist - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'"),
(@ENTRY,0,3,0,14,0,100,0,2000,40,9000,12000,11,11986,0,0,0,0,0,7,0,0,0,0,0,0,0,"Rageclaw Primalist - Friendly At 2000 Health - Cast 'Healing Wave'"),
(@ENTRY,0,4,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Primalist - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,5,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw Primalist - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Rotting Abomination SAI
SET @ENTRY := 28023;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,8,40,12000,15000,11,50335,0,0,0,0,0,2,1,0,0,0,0,0,0,"Rotting Abomination - Within 8-40 Range - Cast 'Scourge Hook'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,7000,11000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rotting Abomination - Within 0-5 Range - Cast 'Cleave'");

-- Rhunok SAI
SET @ENTRY := 28416;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,5000,40000,45000,11,57861,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rhunok - In Combat - Cast 'Roar of Rhunok'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,6000,9000,11,34298,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rhunok - Within 0-5 Range - Cast 'Maul'");

-- Scion of Quetz'lun SAI
SET @ENTRY := 28477;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,15000,17000,11,38193,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scion of Quetz'lun - In Combat - Cast 'Lightning Breath'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,12000,17000,11,54526,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scion of Quetz'lun - Within 0-5 Range - Cast 'Torment'");

-- Shalewing SAI
SET @ENTRY := 28879;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,33000,35000,11,49980,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shalewing - In Combat - Cast 'Ravenous Pathogen'");

-- Vargul Blighthound SAI
SET @ENTRY := 29452;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,12000,11,50046,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vargul Blighthound - Within 0-5 Range - Cast 'Gnaw Bone'");

-- Trapdoor Ambusher SAI
SET @ENTRY := 28342;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,21067,64,0,0,0,0,2,0,0,0,0,0,0,0,"Trapdoor Ambusher - In Combat - Cast 'Poison Bolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,30,9000,13000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Trapdoor Ambusher - Within 0-30 Range - Cast 'Web'");

-- Tiri SAI
SET @ENTRY := 28916;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,9000,15000,11,52719,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tiri - Within 0-10 Range - Cast 'Concussion Blow'"),
(@ENTRY,0,1,0,14,0,100,0,2000,40,9000,15000,11,25058,0,0,0,0,0,7,0,0,0,0,0,0,0,"Tiri - Friendly At 2000 Health - Cast 'Renew'"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,11,25058,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tiri - Between 0-50% Health - Cast 'Renew' (No Repeat)");

-- Vargul Deathwaker SAI
SET @ENTRY := 29449;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,9000,12000,11,56038,0,0,0,0,0,5,0,0,0,0,0,0,0,"Vargul Deathwaker - In Combat - Cast 'Plaguebolt'");

-- Vargul Plaguetalon SAI
SET @ENTRY := 29453;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,8000,13000,11,55079,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vargul Plaguetalon - Within 0-5 Range - Cast 'Swoop'");

-- Vargul Runelord SAI
SET @ENTRY := 29450;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,11,54512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vargul Runelord - Out of Combat - Cast 'Plague Shield'"),
(@ENTRY,0,1,0,16,0,100,0,54512,1,15000,30000,11,54512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vargul Runelord - On Friendly Unit Missing Buff 'Plague Shield' - Cast 'Plague Shield'"),
(@ENTRY,0,2,0,0,0,100,0,9000,15000,12000,16000,11,56036,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vargul Runelord - In Combat - Cast 'Rune of Destruction'");

-- Watery Lord SAI
SET @ENTRY := 28118;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Watery Lord - In Combat - Cast 'Water Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,6000,11000,9000,14000,11,35735,0,0,0,0,0,5,0,0,0,0,0,0,0,"Watery Lord - In Combat - Cast 'Water Spout'");
