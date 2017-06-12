-- Anub'ar Slayer SAI
SET @ENTRY := 26606;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,7800,19800,22300,11,32739,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anub'ar Slayer - In Combat - Cast 'Venomous Bite'");

-- Battered Drakkari Berserker SAI
SET @ENTRY := 26943;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,7000,14000,11,37592,0,0,0,0,0,2,0,0,0,0,0,0,0,"Battered Drakkari Berserker - In Combat - Cast 'Knockdown'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Battered Drakkari Berserker - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Battered Drakkari Berserker - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Duke Vallenhal SAI
SET @ENTRY := 26926;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,51873,0,0,0,0,0,1,1,0,0,0,0,0,0,"Duke Vallenhal - Between 0-50% Health - Cast 'Bloodworm' (No Repeat)"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,50689,0,0,0,0,0,1,0,0,0,0,0,0,0,"Duke Vallenhal - On Aggro - Cast 'Blood Presence' (No Repeat)");

-- Infinite Timerender SAI
SET @ENTRY := 32352;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,12000,17000,11,51020,0,0,0,0,0,2,0,0,0,0,0,0,0,"Infinite Timerender - In Combat - Cast 'Time Lapse'");

-- Fordragon High Priest SAI
SET @ENTRY := 27677;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,25054,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fordragon High Priest - In Combat - Cast 'Holy Smite'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon High Priest - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,9000,9000,35000,45000,11,49306,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon High Priest - In Combat - Cast 'Circle of Healing'"),
(@ENTRY,0,3,0,2,0,100,1,0,50,0,0,11,49348,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon High Priest - Between 0-50% Health - Cast 'Greater Heal' (No Repeat)"),
(@ENTRY,0,4,0,14,0,100,0,4000,10,12000,17000,11,25058,0,0,0,0,0,7,0,0,0,0,0,0,0,"Fordragon High Priest - Friendly At 4000 Health - Cast 'Renew'"),
(@ENTRY,0,5,0,2,0,100,1,0,30,0,0,11,32595,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon High Priest - Between 0-30% Health - Cast 'Power Word: Shield' (No Repeat)");

-- Fordragon Marksman SAI
SET @ENTRY := 27540;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32103,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fordragon Marksman - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon Marksman - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,8000,16000,18000,11,7896,0,0,0,0,0,5,0,0,0,0,0,0,0,"Fordragon Marksman - In Combat - Cast 'Exploding Shot'"),
(@ENTRY,0,3,0,0,0,100,0,3000,9000,11000,12000,11,49474,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fordragon Marksman - In Combat - Cast 'Rapid Shot'");

-- Commander Jordan SAI
SET @ENTRY := 27237;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,48714,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - On Spellhit 'Compelled' - Set Event Phase 2"),
(@ENTRY,0,1,0,6,2,100,0,0,0,0,0,85,48724,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - On Just Died - Invoker Cast 'The Denouncement: Commander Jordan On Death'"),
(@ENTRY,0,2,0,25,0,100,0,0,0,0,0,28,48714,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - On Reset - Remove Aura 'Compelled'"),
(@ENTRY,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - On Reset - Set Event Phase 0"),
(@ENTRY,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - On Just Died - Say Line 0"),
(@ENTRY,0,6,0,0,0,100,0,1000,3000,25000,30000,11,50837,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - In Combat - Cast 'Avenging Wrath'"),
(@ENTRY,0,7,0,9,0,100,0,0,10,18000,23000,11,32773,0,0,0,0,0,1,0,0,0,0,0,0,0,"Commander Jordan - Within 0-10 Range - Cast 'Consecration'");

-- Blighted Elk SAI
SET @ENTRY := 26616;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,1,46770,0,0,0,33,27111,0,0,0,0,0,7,0,0,0,0,0,0,0,"Blighted Elk - On Spellhit 'Liquid Fire of Elune' - Quest Credit 'The Liquid Fire of Elune' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,46770,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blighted Elk - On Spellhit 'Liquid Fire of Elune' - Despawn In 5000 ms (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,5000,6000,9000,11,43506,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blighted Elk - In Combat - Cast 'Plague Blight'");

-- Blacksmith Goodman SAI
SET @ENTRY := 27234;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,48714,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blacksmith Goodman - On Spellhit 'Compelled' - Set Event Phase 2"),
(@ENTRY,0,1,0,6,2,100,0,0,0,0,0,85,48728,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blacksmith Goodman - On Just Died - Invoker Cast 'The Denouncement: Blacksmith Goodman On Death' (Phase 2)"),
(@ENTRY,0,2,0,25,0,100,0,0,0,0,0,28,48714,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blacksmith Goodman - On Reset - Remove Aura 'Compelled'"),
(@ENTRY,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blacksmith Goodman - On Reset - Set Event Phase 0"),
(@ENTRY,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blacksmith Goodman - On Just Died - Say Line 0 (Phase 2)"),
(@ENTRY,0,5,0,0,0,100,0,2000,5000,5000,7000,11,33661,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blacksmith Goodman - In Combat - Cast 'Crush Armor'"),
(@ENTRY,0,6,0,0,0,100,0,6000,9000,10000,14000,11,15621,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blacksmith Goodman - In Combat - Cast 'Skull Crack'");

-- Dregmar Runebrand SAI
SET @ENTRY := 27003;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dregmar Runebrand - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,3,2,0,100,1,0,50,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dregmar Runebrand - Between 0-50% Health - Say Line 1 (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,0,0,20,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Dregmar Runebrand - Between 0-20% Health - Run Script"),
(@ENTRY,0,3,0,61,0,100,0,0,50,0,0,11,48325,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dregmar Runebrand - Between 0-50% Health - Cast 'Rune Shield' (No Repeat)");

-- Rabid Grizzly SAI
SET @ENTRY := 26643;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,2,0,0,0,100,0,2000,5000,9000,12000,11,51951,0,0,0,0,0,2,32,0,0,0,0,0,0,"Rabid Grizzly - In Combat - Cast 'Rabies'");
