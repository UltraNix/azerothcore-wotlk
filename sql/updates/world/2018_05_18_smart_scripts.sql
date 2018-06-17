-- https://db.darkwizard.pl/?npc=1259
-- Gobbler SAI
SET @ENTRY := 1259;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,7000,20000,30000,11,12097,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gobbler - In Combat - Cast 'Pierce Armor'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gobbler - Between 0-15% Health - Flee For Assist (No Repeat)");

-- https://db.darkwizard.pl/?npc=15407
-- Chieftain Zul'Marosh SAI
SET @ENTRY := 15407;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,8000,8000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chieftain Zul'Marosh - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,8000,10000,11,11971,1,0,0,0,0,2,0,0,0,0,0,0,0,"Chieftain Zul'Marosh - In Combat - Cast 'Sunder Armor'");

-- https://db.darkwizard.pl/?npc=15649
-- Feral Dragonhawk Hatchling SAI
SET @ENTRY := 15649;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,12000,15000,11,29117,0,0,0,0,0,2,0,0,0,0,0,0,0,"Feral Dragonhawk Hatchling - In Combat - Cast 'Feather Burst'");

-- https://db.darkwizard.pl/?npc=15650
-- Crazed Dragonhawk SAI
SET @ENTRY := 15650;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,12000,15000,11,29117,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crazed Dragonhawk - In Combat - Cast 'Feather Burst'");


-- https://db.darkwizard.pl/?npc=15937
-- Mmmrrrggglll SAI
SET @ENTRY := 15937;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,8000,4000,8000,11,12058,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mmmrrrggglll - In Combat - Cast 'Chain Lightning'"),
(@ENTRY,0,1,0,0,0,100,0,7000,14000,8000,14000,11,21030,1,0,0,0,0,2,0,0,0,0,0,0,0,"Mmmrrrggglll - In Combat - Cast 'Frost Shock'"),
(@ENTRY,0,2,0,2,0,100,0,0,70,15000,25000,11,12491,1,0,0,0,0,1,0,0,0,0,0,0,0,"Mmmrrrggglll - Between 0-70% Health - Cast 'Healing Wave'");

-- https://db.darkwizard.pl/?npc=16343
-- Shadowpine Oracle SAI
SET @ENTRY := 16343;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,74,0,100,0,0,50,20000,30000,11,7154,0,0,0,0,0,9,0,0,0,0,0,0,0,"Shadowpine Oracle - On Friendly Between 0-50% Health - Cast 'Dark Offering'"),
(@ENTRY,0,1,0,2,0,100,1,0,25,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Shadowpine Oracle - Between 0-25% Health - Flee For Assist (No Repeat)");

-- https://db.darkwizard.pl/?npc=3249
-- Greater Thunderhawk SAI
SET @ENTRY := 3249;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,80,0,4000,12000,10000,12000,11,8078,0,0,0,0,0,2,0,0,0,0,0,0,0,"Greater Thunderhawk - In Combat - Cast 'Thunderclap'");

-- https://db.darkwizard.pl/?npc=712
-- Redridge Thrasher SAI
SET @ENTRY := 712;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Redridge Thrasher - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,1,0,25,0,100,0,0,0,0,0,11,8876,2,0,0,0,0,1,0,0,0,0,0,0,0,"Redridge Thrasher - On Reset - Cast 'Thrash'");

-- https://db.darkwizard.pl/?npc=1038
-- Dragonmaw Shadowwarder SAI
SET @ENTRY := 1038;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3500,6400,11,20807,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Shadowwarder - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,2000,6000,18000,22000,11,6223,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Shadowwarder - In Combat - Cast 'Corruption'"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Shadowwarder - Between 0-15% Health - Flee For Assist (No Repeat)");

-- https://db.darkwizard.pl/?npc=1057
-- Dragonmaw Bonewarder SAI
SET @ENTRY := 1057;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,15000,20000,40000,60000,11,6205,32,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Bonewarder - In Combat - Cast 'Curse of Weakness'"),
(@ENTRY,0,0,1,0,0,100,0,8000,15000,40000,60000,11,10651,32,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Bonewarder - In Combat - Cast 'Curse of the Eye'"),
(@ENTRY,0,1,0,60,0,100,0,0,0,5000,5000,11,13787,32,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Bonewarder - On Update - Cast 'Demon Armor'"),
(@ENTRY,0,2,0,0,0,100,0,4000,8000,10000,12000,11,707,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Bonewarder - In Combat - Cast 'Immolate'");

-- https://db.darkwizard.pl/?npc=2434
-- Shadowy Assassin SAI
SET @ENTRY := 2434;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,11,1786,34,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowy Assassin - On Reset - Cast 'Stealth'");

-- https://db.darkwizard.pl/?npc=1037
-- Dragonmaw Battlemaster SAI
SET @ENTRY := 1037;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,6000,8000,11,11839,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Battlemaster - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,8599,34,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Battlemaster - Between 0-30% Health - Cast 'Enrage' (No Repeat)");

-- https://db.darkwizard.pl/?npc=937
-- Kurzen Jungle Fighter SAI
SET @ENTRY := 937;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Kurzen Jungle Fighter - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,1,0,25,0,100,0,0,0,0,0,11,3637,34,0,0,0,0,1,0,0,0,0,0,0,0,"Kurzen Jungle Fighter - On Reset - Cast 'Improved Blocking III'");

-- https://db.darkwizard.pl/?npc=3974
-- Houndmaster Loksey SAI
SET @ENTRY := 3974;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Houndmaster Loksey - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,20000,20000,11,6742,32,1,0,0,0,11,4304,20,0,0,0,0,0,"Houndmaster Loksey - In Combat - Cast 'Bloodlust'"),
(@ENTRY,0,2,0,60,0,100,0,0,0,5000,5000,11,6192,34,0,0,0,0,1,0,0,0,0,0,0,0,"Houndmaster Loksey - On Update - Cast 'Battle Shout'");

-- https://db.darkwizard.pl/?npc=9176
-- Gor'tesh SAI
SET @ENTRY := 9176;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,10000,10000,12000,11,12734,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gor'tesh - In Combat - Cast 'Ground Smash'"),
(@ENTRY,0,1,0,0,0,100,0,17000,20000,20000,22000,11,10101,1,0,0,0,0,2,0,0,0,0,0,0,0,"Gor'tesh - In Combat - Cast 'Knock Away'"),
(@ENTRY,0,2,0,25,0,100,0,0,0,0,0,11,8876,34,0,0,0,0,1,0,0,0,0,0,0,0,"Gor'tesh - On Reset - Cast 'Thrash'"),
(@ENTRY,0,3,0,0,0,100,0,12000,14000,12000,15000,11,15652,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gor'tesh - In Combat - Cast 'Head Smash'");

-- https://db.darkwizard.pl/?npc=12476
-- Emeraldon Oracle SAI
SET @ENTRY := 12476;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,74,0,100,0,0,60,14000,16000,11,20664,0,0,0,0,0,9,0,0,0,0,0,0,0,"Emeraldon Oracle - On Friendly Between 0-60% Health - Cast 'Rejuvenation'"),
(@ENTRY,0,1,0,0,0,100,0,4000,6000,30000,35000,11,20656,1,0,0,0,0,2,0,0,0,0,0,0,0,"Emeraldon Oracle - In Combat - Cast 'Faerie Fire'");

-- https://db.darkwizard.pl/?npc=12475
-- Emeraldon Tree Warder SAI
SET @ENTRY := 12475;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,19000,23000,11,20654,0,0,0,0,0,5,0,0,0,0,0,0,0,"Emeraldon Tree Warder - In Combat - Cast 'Entangling Roots'"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,30000,34000,11,20656,1,0,0,0,0,5,0,0,0,0,0,0,0,"Emeraldon Tree Warder - In Combat - Cast 'Faerie Fire'");

-- https://db.darkwizard.pl/?npc=4024
-- Bloodfury Slayer SAI
SET @ENTRY := 4024;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,12,0,100,0,0,20,4000,6000,11,38959,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfury Slayer - Target Between 0-20% Health - Cast 'Execute'"),
(@ENTRY,0,1,0,0,0,75,0,4000,7000,15000,20000,11,16231,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfury Slayer - In Combat - Cast 'Curse of Recklessness'");

-- https://db.darkwizard.pl/?npc=4026
-- Bloodfury Windcaller SAI
SET @ENTRY := 4026;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,10000,15000,20000,11,6728,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfury Windcaller - In Combat - Cast 'Enveloping Winds'");

-- https://db.darkwizard.pl/?npc=4339
-- Brimgore SAI
SET @ENTRY := 4339;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,8000,12000,14000,11,8873,0,0,0,0,0,2,0,0,0,0,0,0,0,"Brimgore - In Combat - Cast 'Flame Breath'");

-- http://www.wowhead.com/npc=23714
-- Grimtotem Elder SAI
SET @ENTRY := 23714;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,0,0,75,15000,20000,11,11986,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Elder - Between 0-75% Health - Cast 'Healing Wave'"),
(@ENTRY,0,1,0,0,0,100,0,4000,6000,6000,10000,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Elder - In Combat - Cast 'Lightning Bolt'");

-- http://www.wowhead.com/npc=23592
-- Grimtotem Breaker SAI
SET @ENTRY := 23592;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,10000,14000,11,43108,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Breaker - In Combat - Cast 'Bone Breaker'");

-- http://www.wowhead.com/npc=23594
-- Grimtotem Destroyer SAI
SET @ENTRY := 23594;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,10000,14000,11,11876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Destroyer - In Combat - Cast 'War Stomp'");

-- http://www.wowhead.com/npc=23881
-- Apothecary Cylla SAI
SET @ENTRY := 23881;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,45000,60000,11,35204,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Cylla - In Combat - Cast 'Toxic Fumes'"),
(@ENTRY,0,1,0,0,0,100,0,8000,12000,60000,70000,11,3583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Apothecary Cylla - In Combat - Cast 'Deadly Poison'");
