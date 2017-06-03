-- Eviscerator SAI
SET @ENTRY := 9029;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,4000,16000,18000,11,14331,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast 'Vicious Rend' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,9000,12000,13000,11,15245,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast 'Shadow Bolt Volley' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,7000,12000,18000,24000,11,7121,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast 'Anti-Magic Shield' (Normal Dungeon)");

-- Houndmaster Grebmar SAI
SET @ENTRY := 9319;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,10,22000,24000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Houndmaster Grebmar - Within 0-10 Range - Cast 'Demoralizing Shout' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,30,0,0,11,21049,0,0,0,0,0,1,0,0,0,0,0,0,0,"Houndmaster Grebmar - Between 0-30% Health - Cast 'Bloodlust' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,5000,5000,12000,14000,11,15615,0,0,0,0,0,2,0,0,0,0,0,0,0,"Houndmaster Grebmar - In Combat - Cast 'Pummel' (Normal Dungeon)");

-- Lord Roccor SAI
SET @ENTRY := 9025;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,7000,11000,9000,14000,11,13728,0,0,0,0,0,5,0,0,0,0,0,0,0,"Lord Roccor - In Combat - Cast 'Earth Shock' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,15,9000,14000,11,6524,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Roccor - Within 0-15 Range - Cast 'Ground Tremor' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,5000,8000,13000,18000,11,13729,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Roccor - In Combat - Cast 'Flame Shock' (Normal Dungeon)");

-- Hedrum the Creeper SAI
SET @ENTRY := 9032;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,25000,28000,11,15475,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hedrum the Creeper - In Combat - Cast 'Baneful Poison' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,3000,3000,12000,13000,11,3609,0,0,0,0,0,5,0,0,0,0,0,0,0,"Hedrum the Creeper - In Combat - Cast 'Paralyzing Poison' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,30,10000,13000,11,15474,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hedrum the Creeper - Within 0-30 Range - Cast 'Web Explosion' (Normal Dungeon)");

-- Ok'thor the Breaker SAI
SET @ENTRY := 9030;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,15254,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ok'thor the Breaker - In Combat - Cast 'Arcane Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,12000,17000,11,13323,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ok'thor the Breaker - In Combat - Cast 'Polymorph' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,25,11000,12000,11,15453,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ok'thor the Breaker - Within 0-25 Range - Cast 'Arcane Explosion' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,3000,4000,9000,14000,11,13747,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ok'thor the Breaker - In Combat - Cast 'Slow' (Normal Dungeon)");

-- Panzor the Invincible SAI
SET @ENTRY := 8923;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,3,0,0,0,0,11,9941,0,0,0,0,0,1,0,0,0,0,0,0,0,"Panzor the Invincible - On Respawn - Cast 'Spell Reflection' (No Repeat) (Normal Dungeon)");

-- Anvilrage Footman SAI
SET @ENTRY := 8892;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,14000,14000,11,15614,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Footman - In Combat - Cast 'Kick' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,5,8000,9000,11,11998,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Footman - Within 0-5 Range - Cast 'Strike' (Normal Dungeon)");

-- Anvilrage Guardsman SAI
SET @ENTRY := 8891;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,6000,12000,13000,11,6713,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Guardsman - In Combat - Cast 'Disarm' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,5,15000,17000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Guardsman - Within 0-5 Range - Cast 'Sunder Armor' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,2000,3000,11000,12000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Guardsman - In Combat - Cast 'Shield Block' (Normal Dungeon)");

-- Anvilrage Marshal SAI
SET @ENTRY := 8898;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,8258,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Marshal - On Aggro - Cast 'Devotion Aura' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,5,8000,9000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Marshal - Within 0-5 Range - Cast 'Holy Strike' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,30,0,0,11,15493,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Marshal - Between 0-30% Health - Cast 'Holy Light' (No Repeat) (Normal Dungeon)");

-- Anvilrage Medic SAI
SET @ENTRY := 8894;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,2,500,1000,600000,600000,11,13864,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Medic - Out of Combat - Cast 'Power Word: Fortitude' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,6000,10000,12000,11,15587,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Medic - In Combat - Cast 'Mind Blast' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,12000,15000,28000,32000,11,15585,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Medic - In Combat - Cast 'Prayer of Healing' (Normal Dungeon)"),
(@ENTRY,0,3,0,14,0,100,2,3000,40,15000,17000,11,15586,0,0,0,0,0,7,0,0,0,0,0,0,0,"Anvilrage Medic - Friendly At 3000 Health - Cast 'Heal' (Normal Dungeon)"),
(@ENTRY,0,4,0,2,0,100,3,0,30,0,0,11,15586,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Medic - Between 0-30% Health - Cast 'Heal' (No Repeat) (Normal Dungeon)");

-- Anvilrage Officer SAI
SET @ENTRY := 8895;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Officer - In Combat - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Officer - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,4,2,0,100,3,0,30,0,0,11,13874,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Officer - Between 0-30% Health - Cast 'Divine Shield' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,3000,3000,120000,120000,11,9128,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Officer - In Combat - Cast 'Battle Shout' (Normal Dungeon)"),
(@ENTRY,0,4,0,61,0,100,3,0,30,0,0,11,13952,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Officer - Between 0-30% Health - Cast 'Holy Light' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,5,0,9,0,100,2,0,5,9000,13000,11,6253,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Officer - Within 0-5 Range - Cast 'Backhand' (Normal Dungeon)");

-- Anvilrage Overseer SAI
SET @ENTRY := 8889;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,8000,9000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Overseer - Within 0-5 Range - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,4,0,100,3,0,0,0,0,11,13589,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Overseer - On Aggro - Cast 'Haste Aura' (No Repeat) (Normal Dungeon)");

-- Anvilrage Soldier SAI
SET @ENTRY := 8893;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,8,8000,9000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Soldier - Within 0-8 Range - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,13000,15000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Soldier - In Combat - Cast 'Hamstring' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,30,0,0,11,13847,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Soldier - Between 0-30% Health - Cast 'Recklessness' (No Repeat) (Normal Dungeon)");

-- Anvilrage Warden SAI
SET @ENTRY := 8890;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,30,8000,8500,11,14030,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Warden - Within 0-30 Range - Cast 'Hooked Net' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,4000,4000,11000,12000,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Warden - In Combat - Cast 'Shield Bash' (Normal Dungeon)");

-- Anvilrage Captain SAI
SET @ENTRY := 8903;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,10,22000,24000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Captain - Within 0-10 Range - Cast 'Demoralizing Shout' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,4000,4000,15000,16000,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Captain - In Combat - Cast 'Shield Bash' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,2000,2000,9000,11000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anvilrage Captain - In Combat - Cast 'Mortal Strike' (Normal Dungeon)"),
(@ENTRY,0,3,0,2,0,100,2,0,40,6000,6000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anvilrage Captain - Between 0-40% Health - Cast 'Shield Block' (Normal Dungeon)");

-- Blazing Fireguard SAI
SET @ENTRY := 8910;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,4000,8000,9000,11,13341,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blazing Fireguard - In Combat - Cast 'Fire Blast' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,6000,8000,16000,17000,11,20787,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blazing Fireguard - In Combat - Cast 'Immolate' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,8,2500,3500,11,15241,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blazing Fireguard - Within 0-8 Range - Cast 'Scorch' (Normal Dungeon)");

-- Bloodhound Mastiff SAI
SET @ENTRY := 8922;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,5000,12000,13000,11,7140,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodhound Mastiff - In Combat - Cast 'Expose Weakness' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,9000,9000,20000,22000,11,15608,0,0,0,0,0,2,1,0,0,0,0,0,0,"Bloodhound Mastiff - In Combat - Cast 'Ravenous Claw' (Normal Dungeon)");

-- Burning Spirit SAI
SET @ENTRY := 9178;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,11,13489,3,0,0,0,0,1,0,0,0,0,0,0,0,"Burning Spirit - On Just Died - Cast 'Burning Spirit' (No Repeat)");

-- Arena Spectator SAI
SET @ENTRY := 8916;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,120000,120000,11,9128,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arena Spectator - In Combat - Cast 'Battle Shout' (Normal Dungeon)");

-- Cave Creeper SAI
SET @ENTRY := 8933;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,14532,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cave Creeper - On Aggro - Cast 'Creeper Venom' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,30,9000,13000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cave Creeper - Within 0-30 Range - Cast 'Web' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4000,5000,17000,18000,11,13298,0,0,0,0,0,2,32,0,0,0,0,0,0,"Cave Creeper - In Combat - Cast 'Poison' (Normal Dungeon)");

-- Deep Stinger SAI
SET @ENTRY := 8926;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,7000,11000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Deep Stinger - Within 0-5 Range - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,2000,3000,33000,35000,11,14534,0,0,0,0,0,1,0,0,0,0,0,0,0,"Deep Stinger - In Combat - Cast 'Barbed Sting' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4000,5000,12000,13000,11,7992,0,0,0,0,0,2,32,0,0,0,0,0,0,"Deep Stinger - In Combat - Cast 'Slowing Poison' (Normal Dungeon)");

-- Doomforge Arcanasmith SAI
SET @ENTRY := 8900;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,13748,64,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Arcanasmith - In Combat - Cast 'Arcane Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Arcanasmith - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,10,8000,9000,11,13745,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Arcanasmith - Within 0-10 Range - Cast 'Arcane Explosion' (Normal Dungeon)");

-- Doomforge Craftsman SAI
SET @ENTRY := 8897;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,15619,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Craftsman - On Aggro - Cast 'Throw Wrench' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,5,30,8000,9000,11,9143,0,0,0,0,0,5,0,0,0,0,0,0,0,"Doomforge Craftsman - Within 5-30 Range - Cast 'Bomb' (Normal Dungeon)");

-- Doomforge Dragoon SAI
SET @ENTRY := 8899;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,2300,3900,11,15620,64,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Dragoon - In Combat - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Dragoon - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,4,2,0,100,3,0,30,0,0,11,13874,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Dragoon - Between 0-30% Health - Cast 'Divine Shield' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,3000,3000,120000,120000,11,9128,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Dragoon - In Combat - Cast 'Battle Shout' (Normal Dungeon)"),
(@ENTRY,0,4,0,61,0,100,3,0,30,0,0,11,13952,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Dragoon - Between 0-30% Health - Cast 'Holy Light' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,5,0,9,0,100,2,0,5,7000,9000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Dragoon - Within 0-5 Range - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,6,0,0,0,100,2,8000,8000,12000,13000,11,15495,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Dragoon - In Combat - Cast 'Explosive Shot' (Normal Dungeon)");

-- Fireguard SAI
SET @ENTRY := 8909;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,15242,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fireguard - In Combat - Cast 'Fireball' (Normal Dungeon)");

-- Molten War Golem SAI
SET @ENTRY := 8908;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,3000,16000,17000,11,15570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Molten War Golem - In Combat - Cast 'Immolate' (Normal Dungeon)");

-- Ragereaver Golem SAI
SET @ENTRY := 8906;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,18000,21000,11,17687,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ragereaver Golem - In Combat - Cast 'Flurry' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,3,0,30,0,0,11,12795,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ragereaver Golem - In Combat - Cast 'Frenzy' (No Repeat) (Normal Dungeon)");

-- Ribbly's Crony SAI
SET @ENTRY := 10043;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,2000,2000,11000,12000,11,15581,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ribbly's Crony - In Combat - Cast 'Sinister Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,14000,15000,11,15692,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ribbly's Crony - In Combat - Cast 'Eviscerate' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,8000,8000,18000,19000,11,13298,0,0,0,0,0,2,32,0,0,0,0,0,0,"Ribbly's Crony - In Combat - Cast 'Poison' (Normal Dungeon)");

-- Shadowforge Citizen SAI
SET @ENTRY := 8902;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,2000,3000,8000,9000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Citizen - In Combat - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,6000,12000,13000,11,13339,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Citizen - In Combat - Cast 'Fire Blast' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,8,15800,18300,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Citizen - Within 0-8 Range - Cast 'Frost Nova' (Normal Dungeon)"),
(@ENTRY,0,3,0,2,0,100,3,0,30,0,0,11,11642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Citizen - Between 0-30% Health - Cast 'Heal' (No Repeat) (Normal Dungeon)");

-- Shadowforge Flame Keeper SAI
SET @ENTRY := 9956;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Flame Keeper - In Combat - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Flame Keeper - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,5000,5000,120000,120000,11,9128,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Flame Keeper - In Combat - Cast 'Battle Shout' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,4000,7000,14000,16000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Flame Keeper - In Combat - Cast 'Hamstring' (Normal Dungeon)"),
(@ENTRY,0,4,0,9,0,100,2,0,5,8000,9000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Flame Keeper - Within 0-5 Range - Cast 'Strike' (Normal Dungeon)");

-- Shadowforge Senator SAI
SET @ENTRY := 8904;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Senator - In Combat - Cast 'Shadow Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Senator - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,20,16000,17000,11,14868,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Senator - Within 0-20 Range - Cast 'Curse of Agony' (Normal Dungeon)");

-- Shadowforge Peasant SAI
SET @ENTRY := 8896;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowforge Peasant - In Combat - Cast 'Fireball' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Peasant - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,30,0,0,11,11642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowforge Peasant - Between 0-30% Health - Cast 'Heal' (No Repeat) (Normal Dungeon)");

-- Twilight's Hammer Ambassador SAI
SET @ENTRY := 8915;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,2,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight's Hammer Ambassador - Out of Combat - Cast 'Frost Armor' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,4000,5000,12000,13000,11,15501,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight's Hammer Ambassador - In Combat - Cast 'Earth Shock' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,3000,3000,11000,15000,11,15096,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight's Hammer Ambassador - In Combat - Cast 'Flame Shock' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,6000,8000,10000,13000,11,15499,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight's Hammer Ambassador - In Combat - Cast 'Frost Shock' (Normal Dungeon)"),
(@ENTRY,0,4,0,2,0,100,3,0,50,0,0,11,6742,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight's Hammer Ambassador - Between 0-50% Health - Cast 'Bloodlust' (No Repeat) (Normal Dungeon)");

-- Twilight's Hammer Torturer SAI
SET @ENTRY := 8912;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,3000,14000,16000,11,14032,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight's Hammer Torturer - In Combat - Cast 'Shadow Word: Pain' (Normal Dungeon)");

-- Wrath Hammer Construct SAI
SET @ENTRY := 8907;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,5000,12000,13000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrath Hammer Construct - In Combat - Cast 'Uppercut' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,20,9000,12000,11,15575,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrath Hammer Construct - Within 0-20 Range - Cast 'Flame Cannon' (Normal Dungeon)");

-- Weapon Technician SAI
SET @ENTRY := 8920;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Weapon Technician - In Combat - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Weapon Technician - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,5000,5000,12000,12000,11,12551,0,0,0,0,0,2,0,0,0,0,0,0,0,"Weapon Technician - In Combat - Cast 'Frost Shot' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,8000,8000,25000,26000,11,14443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Weapon Technician - In Combat - Cast 'Multi-Shot' (Normal Dungeon)"),
(@ENTRY,0,4,0,0,0,100,2,3000,3000,10000,15000,11,7896,0,0,0,0,0,2,0,0,0,0,0,0,0,"Weapon Technician - In Combat - Cast 'Exploding Shot' (Normal Dungeon)");

-- Twilight Emissary SAI
SET @ENTRY := 8913;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,15043,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Emissary - In Combat - Cast 'Frostbolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Emissary - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,8,15800,18300,11,15063,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Emissary - Within 0-8 Range - Cast 'Frost Nova' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,5000,5000,14000,17000,11,8364,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Emissary - In Combat - Cast 'Blizzard' (Normal Dungeon)"),
(@ENTRY,0,4,0,1,0,100,2,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Emissary - Out of Combat - Cast 'Frost Armor' (Normal Dungeon)");

-- Twilight Bodyguard SAI
SET @ENTRY := 8914;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,5000,12000,14000,11,13902,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Bodyguard - In Combat - Cast 'Fist of Ragnaros' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,3000,6000,16000,17000,11,15615,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Bodyguard - In Combat - Cast 'Pummel' (Normal Dungeon)"),
(@ENTRY,0,2,0,14,0,100,2,3000,30,32000,33000,11,13903,0,0,0,0,0,7,0,0,0,0,0,0,0,"Twilight Bodyguard - Friendly At 3000 Health - Cast 'Seal of Sacrifice' (Normal Dungeon)");
