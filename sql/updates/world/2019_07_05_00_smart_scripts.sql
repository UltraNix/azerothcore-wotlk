-- Bog Lurker SAI
SET @ENTRY := 18682;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,16000,11,35238,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bog Lurker - Within 0-5 Range - Cast 'War Stomp'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,34163,1,0,0,0,0,1,0,0,0,0,0,0,0,"Bog Lurker - Between 0-30% Health - Cast 'Fungal Regrowth' (No Repeat)");

-- Captain Bo'kar SAI
SET @ENTRY := 20442;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,0,0,40,20000,22000,11,35491,1,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Bo'kar - Between 0-40% Health - Cast 'Furious Rage'");

-- Captain Krosh SAI
SET @ENTRY := 18992;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,0,0,40,20000,22000,11,35491,1,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Krosh - Between 0-40% Health - Cast 'Furious Rage'");

-- Coilfang Emissary SAI
SET @ENTRY := 18681;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20297,64,0,0,0,0,2,0,0,0,0,0,0,0,"Coilfang Emissary - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilfang Emissary - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilfang Emissary - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,10,13600,14500,11,11831,1,0,0,0,0,1,0,0,0,0,0,0,0,"Coilfang Emissary - Within 0-10 Range - Cast 'Frost Nova'"),
(@ENTRY,0,4,0,9,0,100,0,0,5,18000,20000,11,33860,1,0,0,0,0,1,0,0,0,0,0,0,0,"Coilfang Emissary - Within 0-5 Range - Cast 'Arcane Explosion'"),
(@ENTRY,0,5,0,0,0,100,0,6000,9000,10000,25000,11,39207,0,0,0,0,0,2,0,0,0,0,0,0,0,"Coilfang Emissary - In Combat - Cast 'Water Spout'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Dreghood Drudge SAI
SET @ENTRY := 18122;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,34789,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreghood Drudge - On Aggro - Cast 'Shared Bonds' (No Repeat)");

-- Elder Kuruti SAI
SET @ENTRY := 18197;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Kuruti - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,1,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Kuruti - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,2,0,100,0,0,40,20000,28000,11,11986,1,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Kuruti - Between 0-40% Health - Cast 'Healing Wave'"),
(@ENTRY,0,3,0,0,0,100,0,5000,7000,12000,15000,11,12058,0,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Kuruti - In Combat - Cast 'Chain Lightning'");

-- Lagoon Walker SAI
SET @ENTRY := 20291;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,17000,20000,11,6870,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lagoon Walker - In Combat - Cast 'Moss Covered Feet'");

-- Marshrock Stomper SAI
SET @ENTRY := 20283;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35385,0,0,0,0,0,2,0,0,0,0,0,0,0,"Marshrock Stomper - On Aggro - Cast 'Threshalisk Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,7000,15000,15500,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Marshrock Stomper - In Combat - Cast 'Stomp'");

-- Marticar SAI
SET @ENTRY := 18680;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,2000,10000,12000,11,35493,0,0,0,0,0,2,0,0,0,0,0,0,0,"Marticar - In Combat - Cast 'Forked Lightning Tether'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,32039,0,0,0,0,0,2,0,0,0,0,0,0,0,"Marticar - On Aggro - Cast 'Magnetic Pull' (No Repeat)");

-- Overlord Gorefist SAI
SET @ENTRY := 18160;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,9000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Overlord Gorefist - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,2,0,100,1,0,60,0,0,11,33962,1,0,0,0,0,1,0,0,0,0,0,0,0,"Overlord Gorefist - Between 0-60% Health - Cast 'Toughen' (No Repeat)");

-- Rajah Haghazed SAI
SET @ENTRY := 18046;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35472,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rajah Haghazed - On Aggro - Cast 'Shield Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3000,4000,9000,10000,11,35473,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rajah Haghazed - In Combat - Cast 'Forceful Cleave'"),
(@ENTRY,0,2,0,0,0,100,0,7000,9000,15000,16000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rajah Haghazed - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,3,0,2,0,100,0,0,40,16000,21000,11,15062,1,0,0,0,0,1,0,0,0,0,0,0,0,"Rajah Haghazed - Between 0-40% Health - Cast 'Shield Wall'");

-- Sporeggar Preserver SAI
SET @ENTRY := 18139;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,15000,16000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sporeggar Preserver - In Combat - Cast 'Faerie Fire'");

-- Ssslith SAI
SET @ENTRY := 18154;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,13600,14500,11,12674,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ssslith - Within 0-8 Range - Cast 'Frost Nova'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,17741,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ssslith - On Aggro - Cast 'Mana Shield' (No Repeat)");

-- Steam Pump Overseer SAI
SET @ENTRY := 18340;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,19000,11,5164,0,0,0,0,0,2,0,0,0,0,0,0,0,"Steam Pump Overseer - Within 0-5 Range - Cast 'Knockdown'"),
(@ENTRY,0,1,0,2,0,100,1,0,60,0,0,11,33962,1,0,0,0,0,1,0,0,0,0,0,0,0,"Steam Pump Overseer - Between 0-60% Health - Cast 'Toughen' (No Repeat)");

-- Telredor Guard SAI
SET @ENTRY := 18922;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Telredor Guard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,19000,20000,11,12170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Telredor Guard - In Combat - Cast 'Revenge'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,12000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Telredor Guard - In Combat - Cast 'Shield Block'");

-- Xeleth SAI
SET @ENTRY := 21894;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,36414,0,0,0,0,0,2,0,0,0,0,0,0,0,"Xeleth - In Combat - Cast 'Focused Bursts'"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,16000,22000,11,36398,0,0,0,0,0,2,0,0,0,0,0,0,0,"Xeleth - In Combat - Cast 'Tongue Lash'");

-- Zabra'jin Guard SAI
SET @ENTRY := 18909;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Zabra'jin Guard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,19000,20000,11,12170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zabra'jin Guard - In Combat - Cast 'Revenge'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,12000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zabra'jin Guard - In Combat - Cast 'Shield Block'");

-- Bonechewer Marauder SAI
SET @ENTRY := 21245;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,7000,6000,9000,11,8646,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bonechewer Marauder - In Combat - Cast 'Snap Kick'");

-- Caravan Defender SAI
SET @ENTRY := 22407;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Caravan Defender - In Combat - Cast 'Shoot'");

-- Crippler SAI
SET @ENTRY := 18689;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,12500,11,38621,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crippler - Within 0-5 Range - Cast 'Debilitating Strike'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,38882,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crippler - On Aggro - Cast 'Bone Armor' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,15000,20000,11,39214,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crippler - In Combat - Cast 'Pierce Armor'");

-- Empoor's Bodyguard SAI
SET @ENTRY := 18483;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,10000,14500,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Empoor's Bodyguard - Within 0-5 Range - Cast 'Rend'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,15000,20000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Empoor's Bodyguard - In Combat - Cast 'Demoralizing Shout'");

-- Enslaved Doomguard SAI
SET @ENTRY := 21963;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,14000,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Enslaved Doomguard - In Combat - Cast 'Cripple'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,17000,18000,11,31598,0,0,0,0,0,4,0,0,0,0,0,0,0,"Enslaved Doomguard - In Combat - Cast 'Rain of Fire'"),
(@ENTRY,0,2,0,9,0,100,0,0,5,14000,14500,11,11876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Enslaved Doomguard - Within 0-5 Range - Cast 'War Stomp'");

-- Floon SAI
SET @ENTRY := 18588;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Floon - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Floon - Within 0-8 Range - Cast 'Frost Nova'"),
(@ENTRY,0,2,0,0,0,100,0,5000,8000,18000,20000,11,6726,0,0,0,0,0,4,0,0,0,0,0,0,0,"Floon - In Combat - Cast 'Silence'");

-- Gardok Ripjaw SAI
SET @ENTRY := 19002;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gardok Ripjaw - In Combat - Cast 'Shoot'");

-- Hawkbane SAI
SET @ENTRY := 21724;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,16000,19000,11,33912,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hawkbane - In Combat - Cast 'Rip'");

-- High Elf Ranger SAI
SET @ENTRY := 19000;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"High Elf Ranger - In Combat - Cast 'Shoot'");

-- Infested Root-Walker SAI
SET @ENTRY := 22095;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,40,0,0,11,39000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Infested Root-Walker - Between 0-40% Health - Cast 'Regrowth' (No Repeat)"),
(@ENTRY,0,1,0,6,0,100,1,0,0,0,0,11,39130,3,0,0,0,0,1,0,0,0,0,0,0,0,"Infested Root-Walker - On Just Died - Cast 'Summon Wood Mites' (No Repeat)");

-- Razorthorn Flayer SAI
SET @ENTRY := 24920;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,33896,0,0,0,0,0,1,0,0,0,0,0,0,0,"Razorthorn Flayer - Between 0-30% Health - Cast 'Desperate Defense' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,4500,12000,13000,11,46202,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razorthorn Flayer - In Combat - Cast 'Pierce Armor'"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,18000,20000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razorthorn Flayer - In Combat - Cast 'Rend'");

-- Stonebreaker Grunt SAI
SET @ENTRY := 18973;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Stonebreaker Grunt - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonebreaker Grunt - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonebreaker Grunt - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,5,9000,11000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonebreaker Grunt - Within 0-5 Range - Cast 'Cleave'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Stonebreaker Guard SAI
SET @ENTRY := 18989;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Stonebreaker Guard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonebreaker Guard - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonebreaker Guard - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Time-Lost Skettis High Priest SAI
SET @ENTRY := 21787;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,16592,0,0,0,0,0,1,0,0,0,0,0,0,0,"Time-Lost Skettis High Priest - On Respawn - Cast 'Shadowform' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,4500,16000,20000,11,15654,0,0,0,0,0,2,0,0,0,0,0,0,0,"Time-Lost Skettis High Priest - In Combat - Cast 'Shadow Word: Pain'"),
(@ENTRY,0,2,0,14,0,100,0,3000,40,18000,22000,11,42420,1,0,0,0,0,7,0,0,0,0,0,0,0,"Time-Lost Skettis High Priest - Friendly At 3000 Health - Cast 'Flash Heal'"),
(@ENTRY,0,3,0,0,0,100,0,0,0,3400,4700,11,9734,64,0,0,0,0,2,0,0,0,0,0,0,0,"Time-Lost Skettis High Priest - In Combat - Cast 'Holy Smite'");

-- Time-Lost Skettis Reaver SAI
SET @ENTRY := 21651;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,3019,0,0,0,0,0,1,0,0,0,0,0,0,0,"Time-Lost Skettis Reaver - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Time-Lost Skettis Reaver - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,8000,9000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Time-Lost Skettis Reaver - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,3,0,0,0,100,0,5000,5000,120000,125000,11,42247,0,0,0,0,0,1,0,0,0,0,0,0,0,"Time-Lost Skettis Reaver - In Combat - Cast 'Battle Shout'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Time-Lost Skettis Worshipper SAI
SET @ENTRY := 21763;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,22000,24000,11,38167,0,0,0,0,0,2,0,0,0,0,0,0,0,"Time-Lost Skettis Worshipper - In Combat - Cast 'Curse of Blood'");

-- Vengeful Husk SAI
SET @ENTRY := 22045;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,38621,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vengeful Husk - In Combat - Cast 'Debilitating Strike'");

-- Adyen the Lightwarden SAI
SET @ENTRY := 18537;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,25000,28000,11,13005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Adyen the Lightwarden - In Combat - Cast 'Hammer of Justice'"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,30000,32000,11,33127,0,0,0,0,0,1,0,0,0,0,0,0,0,"Adyen the Lightwarden - In Combat - Cast 'Seal of Command'"),
(@ENTRY,0,2,0,2,0,100,1,0,10,0,0,11,13874,0,0,0,0,0,1,0,0,0,0,0,0,0,"Adyen the Lightwarden - Between 0-10% Health - Cast 'Divine Shield' (No Repeat)");

-- Nicole Bartlett SAI
SET @ENTRY := 19033;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nicole Bartlett - Out of Combat - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, 'Hello, what business brings you here? This is an orphanage for the children of Outland who have lost their parents and have no one else to look after them. Perhaps you are here because you are considering adoption?',12,0,100,1,0,0, 'say Text');

-- Alandien SAI
SET @ENTRY := 21171;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,14000,11,39262,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alandien - In Combat - Cast 'Mana Burn'"),
(@ENTRY,0,1,0,2,0,100,1,0,40,0,0,11,36298,0,0,0,0,0,1,0,0,0,0,0,0,0,"Alandien - Between 0-40% Health - Cast 'Metamorphosis' (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,30,15000,16000,11,39082,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alandien - Within 0-30 Range - Cast 'Shadowfury'");

-- Aldor Gryphon Guard SAI
SET @ENTRY := 22077;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,100,8000,9000,11,38279,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aldor Gryphon Guard - Within 0-100 Range - Cast 'Stormhammer'");

-- Altar of Sha'tar Vindicator SAI
SET @ENTRY := 21986;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,41440,64,0,0,0,0,2,0,0,0,0,0,0,0,"Altar of Sha'tar Vindicator - In Combat - Cast 'Shoot'");

-- Anchorite Caalen SAI
SET @ENTRY := 22862;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,36176,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anchorite Caalen - In Combat - Cast 'Holy Smite'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,35096,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Caalen - Between 0-30% Health - Cast 'Greater Heal' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,17000,22000,11,17142,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anchorite Caalen - In Combat - Cast 'Holy Fire'"),
(@ENTRY,0,3,0,2,0,100,0,0,55,20000,21000,11,35943,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Caalen - Between 0-55% Health - Cast 'Prayer of Healing'");

-- Arcane Burst SAI
SET @ENTRY := 22022;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,16000,11,34517,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arcane Burst - Within 0-10 Range - Cast 'Arcane Explosion'");

-- Arvoar the Rapacious SAI
SET @ENTRY := 23267;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,16000,17000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Arvoar the Rapacious - Within 0-5 Range - Cast 'Rend'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,33811,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arvoar the Rapacious - Between 0-30% Health - Cast 'Broken Rage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,11,33810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arvoar the Rapacious - Between 0-50% Health - Cast 'Rock Shell' (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,8000,9000,20000,25000,11,40636,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arvoar the Rapacious - In Combat - Cast 'Bellowing Roar'");

-- Ashtongue Shaman SAI
SET @ENTRY := 21453;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,19000,22000,11,32062,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashtongue Shaman - In Combat - Cast 'Fire Nova Totem'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,6742,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashtongue Shaman - Between 0-30% Health - Cast 'Bloodlust' (No Repeat)"),
(@ENTRY,0,2,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashtongue Shaman - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,3,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashtongue Shaman - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'");

-- Ashtongue Worker SAI
SET @ENTRY := 21455;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,11000,11000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ashtongue Worker - Within 0-5 Range - Cast 'Pierce Armor'");

-- Azaloth SAI
SET @ENTRY := 21506;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,13000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Azaloth - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,14000,16000,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Azaloth - In Combat - Cast 'Cripple'"),
(@ENTRY,0,2,0,0,0,100,0,7000,9000,22000,25000,11,38741,0,0,0,0,0,4,0,0,0,0,0,0,0,"Azaloth - In Combat - Cast 'Rain of Fire'"),
(@ENTRY,0,3,0,9,0,100,0,0,10,22000,28000,11,38750,0,0,0,0,0,1,0,0,0,0,0,0,0,"Azaloth - Within 0-10 Range - Cast 'War Stomp'");

-- Barash the Den Mother SAI
SET @ENTRY := 23269;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,16000,17000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Barash the Den Mother - Within 0-5 Range - Cast 'Rend'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,33811,0,0,0,0,0,1,0,0,0,0,0,0,0,"Barash the Den Mother - Between 0-30% Health - Cast 'Broken Rage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,11,33810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Barash the Den Mother - Between 0-50% Health - Cast 'Rock Shell' (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,8000,9000,20000,25000,11,40636,0,0,0,0,0,1,0,0,0,0,0,0,0,"Barash the Den Mother - In Combat - Cast 'Bellowing Roar'");

-- Black Blood of Draenor SAI
SET @ENTRY := 23286;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,16000,18000,11,40818,0,0,0,0,0,1,0,0,0,0,0,0,0,"Black Blood of Draenor - In Combat - Cast 'Toxic Slime'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,11000,12000,11,7279,0,0,0,0,0,2,0,0,0,0,0,0,0,"Black Blood of Draenor - Within 0-5 Range - Cast 'Black Sludge'");

-- Bonechewer Messenger SAI
SET @ENTRY := 21244;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bonechewer Messenger - On Aggro - Cast 'Charge' (No Repeat)");

-- Chancellor Bloodleaf SAI
SET @ENTRY := 22012;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,15791,64,0,0,0,0,2,0,0,0,0,0,0,0,"Chancellor Bloodleaf - In Combat - Cast 'Arcane Missiles'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,14000,15000,11,34517,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chancellor Bloodleaf - Within 0-8 Range - Cast 'Arcane Explosion'");

-- Coilskar Cobra SAI
SET @ENTRY := 19784;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,5,30,12000,13000,11,38030,0,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Cobra - Within 5-30 Range - Cast 'Poison Spit'");

-- Coilskar Defender SAI
SET @ENTRY := 19762;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,13,0,100,0,2000,4500,0,0,11,38233,0,0,0,0,0,7,0,0,0,0,0,0,0,"Coilskar Defender - On Victim Casting - Cast 'Shield Bash'"),
(@ENTRY,0,1,0,2,0,100,0,0,55,15000,21000,11,38031,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Defender - Between 0-55% Health - Cast 'Shield Block'");

-- Coilskar Muckwatcher SAI
SET @ENTRY := 19788;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,38232,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Muckwatcher - On Aggro - Cast 'Battle Shout' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,13000,14500,11,38029,0,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Muckwatcher - Within 0-5 Range - Cast 'Stab'");

-- Coilskar Myrmidon SAI
SET @ENTRY := 19765;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,38027,0,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Myrmidon - Between 0-30% Health - Cast 'Boiling Blood' (No Repeat)");

-- Coilskar Siren SAI
SET @ENTRY := 19768;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Siren - In Combat - Cast 'Water Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Siren - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Siren - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,0,0,40,25000,28000,11,38026,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Siren - Between 0-40% Health - Cast 'Viscous Shield'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Coilskar Sorceress SAI
SET @ENTRY := 19767;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Sorceress - In Combat - Cast 'Water Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Sorceress - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Sorceress - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,0,0,40,25000,28000,11,38026,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Sorceress - Between 0-40% Health - Cast 'Viscous Shield'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Coilskar Waterkeeper SAI
SET @ENTRY := 19789;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Coilskar Waterkeeper - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,38033,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coilskar Waterkeeper - Within 0-8 Range - Cast 'Frost Nova'");

-- Collidus the Warp-Watcher SAI
SET @ENTRY := 18694;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,16000,18000,11,36414,0,0,0,0,0,2,0,0,0,0,0,0,0,"Collidus the Warp-Watcher - In Combat - Cast 'Focused Bursts'"),
(@ENTRY,0,1,0,0,0,100,0,9000,12000,25000,28000,11,38932,0,0,0,0,0,2,0,0,0,0,0,0,0,"Collidus the Warp-Watcher - In Combat - Cast 'Blink'"),
(@ENTRY,0,2,0,2,0,100,0,0,40,28000,32000,11,34322,0,0,0,0,0,1,0,0,0,0,0,0,0,"Collidus the Warp-Watcher - Between 0-40% Health - Cast 'Psychic Scream'");

-- Corok the Mighty SAI
SET @ENTRY := 22011;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,14000,16000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Corok the Mighty - In Combat - Cast 'Stomp'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,18000,20000,11,15550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Corok the Mighty - Within 0-10 Range - Cast 'Trample'");

-- Corrupted Air Elemental SAI
SET @ENTRY := 21707;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Corrupted Air Elemental - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,35194,0,0,0,0,0,1,0,0,0,0,0,0,0,"Corrupted Air Elemental - On Respawn - Cast 'Shadowform' (No Repeat)");

-- Corrupted Fire Elemental SAI
SET @ENTRY := 21706;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Corrupted Fire Elemental - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,35194,0,0,0,0,0,1,0,0,0,0,0,0,0,"Corrupted Fire Elemental - On Respawn - Cast 'Shadowform' (No Repeat)");

-- Corrupted Water Elemental SAI
SET @ENTRY := 21428;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Corrupted Water Elemental - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,35194,0,0,0,0,0,1,0,0,0,0,0,0,0,"Corrupted Water Elemental - On Respawn - Cast 'Shadowform' (No Repeat)");

-- Crazed Murkblood Foreman SAI
SET @ENTRY := 23305;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,40743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Murkblood Foreman - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Murkblood Foreman - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Crazed Murkblood Miner SAI
SET @ENTRY := 23324;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,40743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Murkblood Miner - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Murkblood Miner - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Crazed Shardling SAI
SET @ENTRY := 21936;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,34970,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Shardling - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Shardling - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Demon Hunter Initiate SAI
SET @ENTRY := 21180;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,12000,15000,11,38009,0,0,0,0,0,2,0,0,0,0,0,0,0,"Demon Hunter Initiate - In Combat - Cast 'Banish'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,12000,27000,11,35871,0,0,0,0,0,2,0,0,0,0,0,0,0,"Demon Hunter Initiate - In Combat - Cast 'Spellbreaker'");

-- Demon Hunter Supplicant SAI
SET @ENTRY := 21179;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32720,0,0,0,0,0,1,0,0,0,0,0,0,0,"Demon Hunter Supplicant - On Aggro - Cast 'Sprint' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,37683,0,0,0,0,0,1,0,0,0,0,0,0,0,"Demon Hunter Supplicant - Between 0-30% Health - Cast 'Evasion' (No Repeat)");

-- Dragonmaw Nether Drake SAI
SET @ENTRY := 22000;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,38344,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Nether Drake - In Combat - Cast 'Arcane Blast'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,9000,9000,11,36513,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Nether Drake - In Combat - Cast 'Intangible Presence'");

-- Dragonmaw Skybreaker SAI
SET @ENTRY := 22274;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,38858,64,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Skybreaker - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,18000,18000,11,38859,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Skybreaker - In Combat - Cast 'Serpent Sting'"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,15000,15000,11,38861,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Skybreaker - In Combat - Cast 'Aimed Shot'");

-- Dreadwarden SAI
SET @ENTRY := 19744;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,11000,11500,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadwarden - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,15000,16000,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadwarden - In Combat - Cast 'Cripple'");

-- Elekk Demolisher SAI
SET @ENTRY := 21802;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,18000,11,38045,0,0,0,0,0,2,0,0,0,0,0,0,0,"Elekk Demolisher - Within 0-10 Range - Cast 'Rampaging Stomp'");

-- Enslaved Netherwing Whelp SAI
SET @ENTRY := 21721;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,38340,64,0,0,0,0,2,0,0,0,0,0,0,0,"Enslaved Netherwing Whelp - In Combat - Cast 'Arcane Bolt'");

-- Eykenen SAI
SET @ENTRY := 21709;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,1000,1000,1000,1000,11,39550,2,0,0,0,0,1,0,0,0,0,0,0,0,"Eykenen - Out of Combat - Cast 'Arcane Channeling' (No Repeat)"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,120000,120000,11,32734,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eykenen - Out of Combat - Cast 'Earth Shield'"),
(@ENTRY,0,2,0,16,0,100,0,32734,1,15000,30000,11,32734,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eykenen - On Friendly Unit Missing Buff 'Earth Shield' - Cast 'Earth Shield'"),
(@ENTRY,0,3,0,9,0,100,0,0,20,11000,12000,11,13281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eykenen - Within 0-20 Range - Cast 'Earth Shock'");

-- Felfire Diemetradon SAI
SET @ENTRY := 21408;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,3000,16000,16500,11,37941,0,0,0,0,0,1,0,0,0,0,0,0,0,"Felfire Diemetradon - In Combat - Cast 'Flaming Wound'");

-- Haalum SAI
SET @ENTRY := 21711;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Haalum - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,15000,18000,11,12058,0,0,0,0,0,2,0,0,0,0,0,0,0,"Haalum - In Combat - Cast 'Chain Lightning'");

-- Illidari Agonizer SAI
SET @ENTRY := 19801;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,36227,64,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Agonizer - In Combat - Cast 'Firebolt'");

-- Illidari Dreadbringer SAI
SET @ENTRY := 19799;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,38166,0,0,0,0,0,1,0,0,0,0,0,0,0,"Illidari Dreadbringer - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Illidari Dreadbringer - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,20,21000,22000,11,38167,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Dreadbringer - Within 0-20 Range - Cast 'Curse of Blood'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Illidari Dreadlord SAI
SET @ENTRY := 21166;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,8000,18000,20000,11,17287,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Dreadlord - In Combat - Cast 'Mind Blast'"),
(@ENTRY,0,1,0,0,0,100,0,12000,14000,25000,26000,11,13704,0,0,0,0,0,1,0,0,0,0,0,0,0,"Illidari Dreadlord - In Combat - Cast 'Psychic Scream'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,17000,17000,11,12098,0,0,0,0,0,5,0,0,0,0,0,0,0,"Illidari Dreadlord - In Combat - Cast 'Sleep'");

-- Illidari Jailor SAI
SET @ENTRY := 21520;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,14000,14500,11,38051,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Jailor - Within 0-30 Range - Cast 'Fel Shackles'");

-- Illidari Overseer SAI
SET @ENTRY := 21808;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,11000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Overseer - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,16000,18000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Overseer - In Combat - Cast 'Rend'");

-- Illidari Painlasher SAI
SET @ENTRY := 19800;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,11000,12000,11,15968,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Painlasher - Within 0-5 Range - Cast 'Lash of Pain'");

-- Illidari Satyr SAI
SET @ENTRY := 21656;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,15500,16000,11,38048,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Satyr - Within 0-30 Range - Cast 'Curse of Pain'");

-- Illidari Shadowstalker SAI
SET @ENTRY := 21337;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,5916,0,0,0,0,0,1,0,0,0,0,0,0,0,"Illidari Shadowstalker - On Respawn - Cast 'Shadowstalker Stealth' (No Repeat)"),
(@ENTRY,0,1,0,7,0,100,1,0,0,0,0,11,5916,0,0,0,0,0,1,0,0,0,0,0,0,0,"Illidari Shadowstalker - On Evade - Cast 'Shadowstalker Stealth' (No Repeat)"),
(@ENTRY,0,2,0,67,0,100,0,9000,12000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Shadowstalker - On Behind Target - Cast 'Backstab'"),
(@ENTRY,0,3,0,0,0,100,0,4000,4500,12000,20000,11,30981,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Shadowstalker - In Combat - Cast 'Crippling Poison'");

-- Illidari Shocktrooper SAI
SET @ENTRY := 19802;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,22120,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Shocktrooper - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,9000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Shocktrooper - In Combat - Cast 'Cleave'");

-- Illidari Slayer SAI
SET @ENTRY := 21639;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Slayer - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,9000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Slayer - In Combat - Cast 'Cleave'");

-- Illidari Succubus SAI
SET @ENTRY := 22860;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,11000,12000,11,32202,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Succubus - Within 0-5 Range - Cast 'Lash of Pain'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,15000,18000,11,31865,0,0,0,0,0,4,0,0,0,0,0,0,0,"Illidari Succubus - In Combat - Cast 'Seduction'");

-- Illidari Watcher SAI
SET @ENTRY := 22093;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,8000,10500,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Illidari Watcher - Within 0-5 Range - Cast 'Mortal Strike'");

-- Infernal Soul SAI
SET @ENTRY := 19757;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,16000,11,11969,0,0,0,0,0,1,0,0,0,0,0,0,0,"Infernal Soul - Within 0-10 Range - Cast 'Fire Nova'");

-- Ja'y Nosliw SAI
SET @ENTRY := 22433;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ja'y Nosliw - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,18000,18000,11,31975,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ja'y Nosliw - In Combat - Cast 'Serpent Sting'");

-- Keeper of the Cistern SAI
SET @ENTRY := 20795;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Keeper of the Cistern - In Combat - Cast 'Water Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Keeper of the Cistern - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Keeper of the Cistern - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,8,13600,14500,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Keeper of the Cistern - Within 0-8 Range - Cast 'Frost Nova'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Kor'kron Rider SAI
SET @ENTRY := 19364;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,12000,12500,11,18396,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Rider - Within 0-30 Range - Cast 'Dismounting Blast'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,11000,11500,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Rider - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,18000,20000,11,15618,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Rider - In Combat - Cast 'Snap Kick'");

-- Lady Shav'rar SAI
SET @ENTRY := 20684;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,13901,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lady Shav'rar - In Combat - Cast 'Arcane Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lady Shav'rar - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lady Shav'rar - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,25,15000,18000,11,38035,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lady Shav'rar - Within 0-25 Range - Cast 'Freeze'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Lakaan SAI
SET @ENTRY := 21416;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lakaan - In Combat - Cast 'Water Bolt'");

-- Lothros SAI
SET @ENTRY := 21928;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,38166,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lothros - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lothros - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,20,21000,22000,11,38167,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lothros - Within 0-20 Range - Cast 'Curse of Blood'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Mordenai SAI
SET @ENTRY := 22113;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,41440,64,0,0,0,0,2,0,0,0,0,0,0,0,"Mordenai - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,27000,28000,11,41448,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mordenai - In Combat - Cast 'Multi-Shot'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,18000,18000,11,38370,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mordenai - In Combat - Cast 'Aimed Shot'");

-- Netharel SAI
SET @ENTRY := 21164;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,12000,13000,11,39262,0,0,0,0,0,4,0,0,0,0,0,0,0,"Netharel - In Combat - Cast 'Mana Burn'"),
(@ENTRY,0,1,0,2,0,100,0,0,60,22000,28000,11,37683,0,0,0,0,0,1,0,0,0,0,0,0,0,"Netharel - Between 0-60% Health - Cast 'Evasion'"),
(@ENTRY,0,2,0,9,0,100,0,0,5,9000,11000,11,39135,0,0,0,0,0,2,0,0,0,0,0,0,0,"Netharel - Within 0-5 Range - Cast 'Debilitating Strike'"),
(@ENTRY,0,3,0,2,0,100,1,0,20,0,0,11,36298,0,0,0,0,0,1,0,0,0,0,0,0,0,"Netharel - Between 0-20% Health - Cast 'Metamorphosis' (No Repeat)");

-- Nethermine Flayer SAI
SET @ENTRY := 23169;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,14500,11,40770,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nethermine Flayer - Within 0-5 Range - Cast 'Shred Armor'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,10000,20000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nethermine Flayer - In Combat - Cast 'Rend'");

-- Nethermine Ravager SAI
SET @ENTRY := 23326;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,16000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nethermine Ravager - In Combat - Cast 'Rend'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,33810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nethermine Ravager - Between 0-30% Health - Cast 'Rock Shell' (No Repeat)");

-- Netherskate SAI
SET @ENTRY := 21901;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,15,10000,14500,11,36659,0,0,0,0,0,2,0,0,0,0,0,0,0,"Netherskate - Within 0-15 Range - Cast 'Tail Sting'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,18000,20000,11,17008,0,0,0,0,0,4,0,0,0,0,0,0,0,"Netherskate - In Combat - Cast 'Drain Mana'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,15000,15000,11,35334,0,0,0,0,0,2,0,0,0,0,0,0,0,"Netherskate - In Combat - Cast 'Nether Shock'");

-- Netherwing Ray SAI
SET @ENTRY := 23501;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,15,10000,14500,11,36659,0,0,0,0,0,2,0,0,0,0,0,0,0,"Netherwing Ray - Within 0-15 Range - Cast 'Tail Sting'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,18000,20000,11,17008,0,0,0,0,0,4,0,0,0,0,0,0,0,"Netherwing Ray - In Combat - Cast 'Drain Mana'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,15000,15000,11,35334,0,0,0,0,0,2,0,0,0,0,0,0,0,"Netherwing Ray - In Combat - Cast 'Nether Shock'");

-- Or'kaos the Insane SAI
SET @ENTRY := 23168;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Or'kaos the Insane - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,15000,15000,11,17547,0,0,0,0,0,2,0,0,0,0,0,0,0,"Or'kaos the Insane - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,0,0,100,0,8000,8500,18000,22000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Or'kaos the Insane - In Combat - Cast 'Uppercut'");

-- Oronu the Elder SAI
SET @ENTRY := 21663;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,45000,46000,11,34079,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oronu the Elder - In Combat - Cast 'Grounding Totem'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oronu the Elder - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oronu the Elder - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'"),
(@ENTRY,0,3,0,2,0,100,0,0,40,14000,21000,11,11986,0,0,0,0,0,1,0,0,0,0,0,0,0,"Oronu the Elder - Between 0-40% Health - Cast 'Healing Wave'");

-- Overmine Flayer SAI
SET @ENTRY := 23264;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,16000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Overmine Flayer - In Combat - Cast 'Rend'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,33810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overmine Flayer - Between 0-30% Health - Cast 'Rock Shell' (No Repeat)");

-- Ravenous Flayer SAI
SET @ENTRY := 21196;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,17000,11,37933,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravenous Flayer - Within 0-5 Range - Cast 'Consume Flesh'");

-- Ravenous Flayer Matriarch SAI
SET @ENTRY := 21205;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,1,0,40,0,0,11,36464,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravenous Flayer Matriarch - Within 0-40 Range - Cast 'The Den Mother's Mark' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,14000,16000,11,38363,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravenous Flayer Matriarch - Within 0-5 Range - Cast 'Gushing Wound'");

-- Rocknail Flayer SAI
SET @ENTRY := 21477;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,16500,17000,11,37937,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rocknail Flayer - Within 0-20 Range - Cast 'Flayed Flesh'");

-- Rocknail Ripper SAI
SET @ENTRY := 21478;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,13500,11,33912,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rocknail Ripper - Within 0-5 Range - Cast 'Rip'");

-- Scryer Cavalier SAI
SET @ENTRY := 22967;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,10000,12000,27000,11,35871,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer Cavalier - In Combat - Cast 'Spellbreaker'"),
(@ENTRY,0,3,0,4,0,100,1,0,0,0,0,11,30931,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scryer Cavalier - On Aggro - Cast 'Battle Shout' (No Repeat)");

-- Scryer Guardian SAI
SET @ENTRY := 19504;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,15228,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer Guardian - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,30,9000,10500,11,11436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer Guardian - Within 0-30 Range - Cast 'Slow'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,20000,11,17195,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer Guardian - In Combat - Cast 'Scorch'");

-- Shadowhoof Assassin SAI
SET @ENTRY := 22858;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,11000,11,14873,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowhoof Assassin - Within 0-5 Range - Cast 'Sinister Strike'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,17000,20000,11,37577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowhoof Assassin - In Combat - Cast 'Debilitating Strike'");

-- Shadowhoof Summoner SAI
SET @ENTRY := 22859;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowhoof Summoner - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,18000,22000,11,13338,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowhoof Summoner - In Combat - Cast 'Curse of Tongues'"),
(@ENTRY,0,2,0,1,0,100,1,1000,1000,1000,1000,11,45846,2,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowhoof Summoner - Out of Combat - Cast 'Frost Channelling' (No Repeat)");

-- Shadowlord Deathwail SAI
SET @ENTRY := 22006;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowlord Deathwail - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,20000,22000,11,32709,0,0,0,0,0,4,0,0,0,0,0,0,0,"Shadowlord Deathwail - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,15000,15000,11,15245,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowlord Deathwail - In Combat - Cast 'Shadow Bolt Volley'");

-- Shadowmoon Chosen SAI
SET @ENTRY := 22084;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,17000,11,38618,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Chosen - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8500,18000,22000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Chosen - In Combat - Cast 'Uppercut'");

-- Shadowmoon Darkweaver SAI
SET @ENTRY := 22081;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Darkweaver - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,25,15000,18000,11,11962,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Darkweaver - Within 0-25 Range - Cast 'Immolate'"),
(@ENTRY,0,2,0,9,0,100,0,0,10,8000,11000,11,35373,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Darkweaver - Within 0-10 Range - Cast 'Shadowfury'");

-- Shadowmoon Peon SAI
SET @ENTRY := 19355;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,11000,11500,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Peon - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,18000,20000,11,15618,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Peon - In Combat - Cast 'Snap Kick'");

-- Shadowmoon Retainer SAI
SET @ENTRY := 22102;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Retainer - In Combat - Cast 'Shoot'");

-- Shadowmoon Slayer SAI
SET @ENTRY := 22082;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,3019,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Slayer - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Slayer - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,4000,4500,17000,20000,11,37577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Slayer - In Combat - Cast 'Debilitating Strike'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Shadowsworn Drakonid SAI
SET @ENTRY := 22072;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowsworn Drakonid - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,15000,15000,11,17547,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowsworn Drakonid - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,0,0,100,0,8000,8500,18000,22000,11,16145,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowsworn Drakonid - In Combat - Cast 'Sunder Armor'");

-- Skethyl Owl SAI
SET @ENTRY := 21450;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,15000,15500,11,38254,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skethyl Owl - In Combat - Cast 'Festering Wound'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,25000,26000,11,38021,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skethyl Owl - In Combat - Cast 'Terrifying Screech'");

-- Smith Gorlunk SAI
SET @ENTRY := 22037;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,16000,17000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smith Gorlunk - Within 0-5 Range - Cast 'Rend'"),
(@ENTRY,0,1,0,0,0,100,0,2000,4500,12000,13000,11,13444,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smith Gorlunk - In Combat - Cast 'Sunder Armor'");

-- Son of Corok SAI
SET @ENTRY := 19824;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,15000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Son of Corok - Within 0-10 Range - Cast 'Stomp'");

-- Spawn of Uvuros SAI
SET @ENTRY := 21108;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,15000,11,36405,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spawn of Uvuros - Within 0-10 Range - Cast 'Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,18000,20000,11,36406,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spawn of Uvuros - In Combat - Cast 'Double Breath'");

-- Spellbound Terrorguard SAI
SET @ENTRY := 21908;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,15000,11,31553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spellbound Terrorguard - Within 0-5 Range - Cast 'Hamstring'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,15000,19000,11,37488,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spellbound Terrorguard - In Combat - Cast 'Fel Flames'");

-- Sunfury Blood Lord SAI
SET @ENTRY := 21743;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,15000,16000,11,36104,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Blood Lord - Within 0-8 Range - Cast 'Torrent of Flames'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,17000,20000,11,37577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunfury Blood Lord - In Combat - Cast 'Debilitating Strike'");

-- Sunfury Eradicator SAI
SET @ENTRY := 21742;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,17137,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Eradicator - Between 0-30% Health - Cast 'Flash Heal' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,31000,31500,11,38008,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Eradicator - In Combat - Cast 'Seal of Blood'");

-- Sunfury Summoner SAI
SET @ENTRY := 21505;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,13901,64,0,0,0,0,2,0,0,0,0,0,0,0,"Sunfury Summoner - In Combat - Cast 'Arcane Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,9000,9000,20000,20000,11,36994,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Summoner - In Combat - Cast 'Blink'");

-- Sunfury Warlock SAI
SET @ENTRY := 21503;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Sunfury Warlock - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,18000,20000,11,32707,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunfury Warlock - In Combat - Cast 'Incinerate'");

-- Theras SAI
SET @ENTRY := 21168;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,14000,11,39262,0,0,0,0,0,2,0,0,0,0,0,0,0,"Theras - In Combat - Cast 'Mana Burn'"),
(@ENTRY,0,1,0,2,0,100,1,0,40,0,0,11,36298,0,0,0,0,0,1,0,0,0,0,0,0,0,"Theras - Between 0-40% Health - Cast 'Metamorphosis' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,8000,10000,12000,27000,11,35871,0,0,0,0,0,2,0,0,0,0,0,0,0,"Theras - In Combat - Cast 'Spellbreaker'");

-- Umberhowl SAI
SET @ENTRY := 21255;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,16000,11,32918,0,0,0,0,0,1,0,0,0,0,0,0,0,"Umberhowl - Within 0-5 Range - Cast 'Chilling Howl'"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,12000,13000,11,32919,0,0,0,0,0,2,0,0,0,0,0,0,0,"Umberhowl - In Combat - Cast 'Snarl'");

-- Uylaru SAI
SET @ENTRY := 21710;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,25000,26000,11,38581,0,0,0,0,0,1,0,0,0,0,0,0,0,"Uylaru - In Combat - Cast 'Corrupted Searing Totem'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,9000,11000,11,15039,0,0,0,0,0,2,0,0,0,0,0,0,0,"Uylaru - Within 0-20 Range - Cast 'Flame Shock'"),
(@ENTRY,0,2,0,1,0,100,1,1000,1000,1000,1000,11,45846,2,0,0,0,0,1,0,0,0,0,0,0,0,"Uylaru - Out of Combat - Cast 'Frost Channelling' (No Repeat)");

-- Val'zareq the Conqueror SAI
SET @ENTRY := 21979;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,38094,64,0,0,0,0,2,0,0,0,0,0,0,0,"Val'zareq the Conqueror - In Combat - Cast 'Shoot'");

-- Varedis SAI
SET @ENTRY := 21178;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,25000,26000,11,38010,0,0,0,0,0,2,0,0,0,0,0,0,0,"Varedis - In Combat - Cast 'Curse of Flames'"),
(@ENTRY,0,1,0,2,0,100,0,0,40,14000,21000,11,37683,0,0,0,0,0,1,0,0,0,0,0,0,0,"Varedis - Between 0-40% Health - Cast 'Evasion'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,20000,11,39262,0,0,0,0,0,2,0,0,0,0,0,0,0,"Varedis - In Combat - Cast 'Mana Burn'");

-- Warbringer Razuun SAI
SET @ENTRY := 21287;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,35913,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warbringer Razuun - In Combat - Cast 'Fel Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,18000,25000,11,38047,0,0,0,0,0,4,0,0,0,0,0,0,0,"Warbringer Razuun - In Combat - Cast 'Mind Warp'");

-- Wildhammer Guard SAI
SET @ENTRY := 19353;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wildhammer Guard - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,9000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wildhammer Guard - Within 0-5 Range - Cast 'Cleave'");

-- Wrathstalker SAI
SET @ENTRY := 21249;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wrathstalker - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wrathstalker - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,12000,12500,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrathstalker - Within 0-5 Range - Cast 'Cleave'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Zandras SAI
SET @ENTRY := 21827;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,14000,14500,11,38051,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zandras - Within 0-30 Range - Cast 'Fel Shackles'");
