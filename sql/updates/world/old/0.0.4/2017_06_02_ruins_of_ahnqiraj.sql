-- Anubisath Swarmguard SAI
SET @ENTRY := 15538;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,15000,25000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anubisath Swarmguard - Within 0-5 Range - Cast 'Cleave' (Normal Dungeon)");

-- Canal Frenzy SAI
SET @ENTRY := 15505;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,12097,0,0,0,0,0,2,0,0,0,0,0,0,0,"Canal Frenzy - In Combat - Cast 'Pierce Armor' (Normal Dungeon)");

-- Flesh Hunter SAI
SET @ENTRY := 15335;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,2000,3200,9000,9100,11,3391,0,0,0,0,0,1,0,0,0,0,0,0,0,"Flesh Hunter - In Combat - Cast 'Thrash' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,0,0,3400,4700,11,25424,64,0,0,0,0,2,0,0,0,0,0,0,0,"Flesh Hunter - In Combat - Cast 'Poison Bolt' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,2,0,65,22000,25000,11,25371,2,0,0,0,0,1,0,0,0,0,0,0,0,"Flesh Hunter - Between 0-65% Health - Cast 'Consume' (Normal Dungeon)");

-- Hive'Zara Collector SAI
SET @ENTRY := 15319;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,30,15000,25000,11,12252,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Collector - Within 0-30 Range - Cast 'Web Spray' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,19000,11,3589,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Collector - In Combat - Cast 'Deafening Screech' (Normal Dungeon)");

-- Hive'Zara Drone SAI
SET @ENTRY := 15318;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,25605,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Drone - In Combat - Cast 'Poison' (Normal Dungeon)");

-- Hive'Zara Larva SAI
SET @ENTRY := 15555;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,24685,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Larva - In Combat - Cast 'Earth Shock' (Normal Dungeon)");

-- Hive'Zara Soldier SAI
SET @ENTRY := 15320;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,15000,19000,11,25497,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Soldier - In Combat - Cast 'Venom Spit' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,5,15000,25000,11,22857,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hive'Zara Soldier - Within 0-5 Range - Cast 'Retaliation' (Normal Dungeon)");

-- Hive'Zara Tail Lasher SAI
SET @ENTRY := 15336;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,25645,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Tail Lasher - In Combat - Cast 'Poison' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,30,7000,10000,11,25654,0,0,0,0,0,4,0,0,0,0,0,0,0,"Hive'Zara Tail Lasher - Within 0-30 Range - Cast 'Tail Lash' (Normal Dungeon)");

-- Hive'Zara Wasp SAI
SET @ENTRY := 15325;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,40,10000,12000,11,25185,0,0,0,0,0,4,0,0,0,0,0,0,0,"Hive'Zara Wasp - Within 0-40 Range - Cast 'Itch' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,8000,15000,19000,11,25187,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zara Wasp - In Combat - Cast 'Hive'Zara Catalyst' (Normal Dungeon)");

-- Mana Fiend SAI
SET @ENTRY := 15527;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,8,15000,25000,11,25679,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mana Fiend - Within 0-8 Range - Cast 'Arcane Explosion' (Normal Dungeon)"),
(@ENTRY,0,1,0,13,0,100,2,5000,8000,0,30000,11,15122,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mana Fiend - On Victim Casting - Cast 'Counterspell' (Normal Dungeon)");

-- Obsidian Destroyer SAI
SET @ENTRY := 15338;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,25756,0,0,0,0,0,1,0,0,0,0,0,0,0,"Obsidian Destroyer - In Combat - Cast 'Purge' (Normal Dungeon)");

-- Qiraji Swarmguard SAI
SET @ENTRY := 15343;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,25174,0,0,0,0,0,2,0,0,0,0,0,0,0,"Qiraji Swarmguard - In Combat - Cast 'Sundering Cleave' (Normal Dungeon)");

-- Qiraji Warrior SAI
SET @ENTRY := 15387;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,3,0,25,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Qiraji Warrior - Between 0-25% Health - Cast 'Enrage' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,61,0,100,0,0,25,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Qiraji Warrior - Between 0-25% Health - Say Line 0 (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,0,15000,25000,15000,25000,11,15588,0,0,0,0,0,2,0,0,0,0,0,0,0,"Qiraji Warrior - In Combat - Cast 'Thunderclap'");

-- Shrieker Scarab SAI
SET @ENTRY := 15461;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,22886,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shrieker Scarab - On Aggro - Cast 'Berserker Charge' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,18000,11,26379,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shrieker Scarab - In Combat - Cast 'Piercing Shriek' (Normal Dungeon)");

-- Spitting Scarab SAI
SET @ENTRY := 15462;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,22886,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spitting Scarab - On Aggro - Cast 'Berserker Charge' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,18000,11,24334,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spitting Scarab - In Combat - Cast 'Acid Spit' (Normal Dungeon)");

-- Swarmguard Needler SAI
SET @ENTRY := 15344;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Swarmguard Needler - In Combat - Cast 'Cleave' (Normal Dungeon)");

