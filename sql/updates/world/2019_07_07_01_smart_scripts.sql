-- Anger Guard SAI
SET @ENTRY := 16952;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,22911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anger Guard - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,12000,16000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Anger Guard - In Combat - Cast 'Cleave'");

-- Arakkoa Egg SAI
SET @ENTRY := 20214;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,11,35788,3,0,0,0,0,7,0,0,0,0,0,0,0,"Arakkoa Egg - On Just Died - Cast 'Arakkoa Egg Debuff' (No Repeat)");

-- Bash'ir Spell-Thief SAI
SET @ENTRY := 22242;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,38860,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bash'ir Spell-Thief - On Aggro - Cast 'Damage Reduction: Magic' (No Repeat)");

-- Bladespire Raptor SAI
SET @ENTRY := 20728;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,19000,27000,11,35321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladespire Raptor - In Combat - Cast 'Gushing Wound'");

-- Bladespire Ravager SAI
SET @ENTRY := 20729;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,22911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladespire Ravager - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,19000,20000,11,16128,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladespire Ravager - In Combat - Cast 'Infected Bite'");

-- Bladespire Sober Defender SAI
SET @ENTRY := 21975;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladespire Sober Defender - Within 0-5 Range - Cast 'Cleave'");

-- Bladewing Bloodletter SAI
SET @ENTRY := 21033;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,9000,12000,11,37839,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladewing Bloodletter - Within 0-30 Range - Cast 'Poison Spit'"),
(@ENTRY,0,1,0,2,0,100,0,0,40,15000,18000,11,37838,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bladewing Bloodletter - Between 0-40% Health - Cast 'Blood Leech'");

-- Boulder'mok Brute SAI
SET @ENTRY := 21046;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Brute - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Brute - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,13600,14500,11,37577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Boulder'mok Brute - Within 0-5 Range - Cast 'Debilitating Strike'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage');

-- Boulder'mok Chieftain SAI
SET @ENTRY := 21048;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,18000,24000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Chieftain - Within 0-8 Range - Cast 'Thunderclap'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,22000,36000,11,35492,0,0,0,0,0,2,0,0,0,0,0,0,0,"Boulder'mok Chieftain - In Combat - Cast 'Exhaustion'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,35491,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Chieftain - Between 0-30% Health - Cast 'Furious Rage' (No Repeat)");

-- Boulder'mok Shaman SAI
SET @ENTRY := 21047;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,0,0,40,22000,28000,11,28902,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Shaman - Between 0-40% Health - Cast 'Bloodlust'"),
(@ENTRY,0,1,0,2,0,100,0,0,25,15000,20000,11,11986,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Shaman - Between 0-25% Health - Cast 'Healing Wave'"),
(@ENTRY,0,2,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Shaman - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,3,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulder'mok Shaman - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'");

-- Cavern Crawler SAI
SET @ENTRY := 22044;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,20000,11,744,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cavern Crawler - In Combat - Cast 'Poison'");

-- Crystalfused Miner SAI
SET @ENTRY := 23174;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,8000,17000,18000,11,32614,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crystalfused Miner - In Combat - Cast 'Arcane Explosion'");

-- Daggermaw Blackhide SAI
SET @ENTRY := 22052;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,19000,22000,11,35321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggermaw Blackhide - Within 0-5 Range - Cast 'Gushing Wound'");

-- Daggermaw Lashtail SAI
SET @ENTRY := 20751;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggermaw Lashtail - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,19000,20000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggermaw Lashtail - In Combat - Cast 'Infected Bite'");

-- Daggertail Lizard SAI
SET @ENTRY := 22255;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,0,0,50,10000,17000,11,32920,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggertail Lizard - Between 0-50% Health - Cast 'Warp'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,32939,0,0,0,0,0,1,0,0,0,0,0,0,0,"Daggertail Lizard - On Aggro - Cast 'Phase Burst' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,16000,11,31279,0,0,0,0,0,2,0,0,0,0,0,0,0,"Daggertail Lizard - In Combat - Cast 'Swipe'"),
(@ENTRY,0,3,0,1,0,100,0,500,1000,60000,60000,11,32942,0,0,0,0,0,1,0,0,0,0,0,0,0,"Daggertail Lizard - Out of Combat - Cast 'Phasing Invisibility'");

-- Death's Might SAI
SET @ENTRY := 21519;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,14000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death's Might - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,4500,4500,12000,13000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death's Might - In Combat - Cast 'Mortal Strike'");

-- Death's Watch SAI
SET @ENTRY := 21516;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,18000,25000,11,37621,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death's Watch - In Combat - Cast 'Mind Flay'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,13000,15000,11,36398,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death's Watch - In Combat - Cast 'Tongue Lash'");

-- Dire Raven SAI
SET @ENTRY := 21042;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,14000,15000,11,31273,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dire Raven - In Combat - Cast 'Screech'");

-- Doomforge Attendant SAI
SET @ENTRY := 19961;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,12000,15000,11,36208,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Attendant - In Combat - Cast 'Steal Weapon'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,19000,20000,11,36846,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Attendant - In Combat - Cast 'Mana Bomb'");

-- Doomforge Engineer SAI
SET @ENTRY := 19960;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,17000,20000,11,36253,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomforge Engineer - In Combat - Cast 'Chemical Flames'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,15000,15000,11,36251,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomforge Engineer - Within 0-8 Range - Cast 'Hammer Slam'");

-- Dorgok SAI
SET @ENTRY := 20753;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,19000,20000,11,11980,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dorgok - In Combat - Cast 'Curse of Weakness'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,25000,28000,11,39119,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dorgok - In Combat - Cast 'Fear'"),
(@ENTRY,0,2,0,0,0,100,0,4000,4000,12000,13000,11,11962,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dorgok - In Combat - Cast 'Immolate'");

-- Droggam SAI
SET @ENTRY := 20731;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Droggam - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,1800000,1800000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Droggam - Out of Combat - Cast 'Frost Armor'"),
(@ENTRY,0,2,0,0,0,100,0,5000,9000,30000,38000,11,35240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Droggam - In Combat - Cast 'Bloodmaul Intoxication'");

-- Dullgrom Dredger SAI
SET @ENTRY := 21254;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dullgrom Dredger - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dullgrom Dredger - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,13000,11,34802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dullgrom Dredger - In Combat - Cast 'Kick'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage');

-- Evergrove Ancient SAI
SET @ENTRY := 22478;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,15000,16000,11,39274,0,0,0,0,0,1,0,0,0,0,0,0,0,"Evergrove Ancient - Within 0-8 Range - Cast 'Trample'");

-- Expedition Druid SAI
SET @ENTRY := 22206;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Expedition Druid - On Respawn - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,1,0,7,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Expedition Druid - On Evade - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,4000,4500,12000,13000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Expedition Druid - In Combat - Cast 'Rend'");

-- Fel Corrupter SAI
SET @ENTRY := 21300;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Corrupter - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,22000,24000,11,32063,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Corrupter - In Combat - Cast 'Corruption'");

-- Felsworn Daggermaw SAI
SET @ENTRY := 21124;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsworn Daggermaw - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,19000,20000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsworn Daggermaw - In Combat - Cast 'Infected Bite'");

-- Felsworn Scalewing SAI
SET @ENTRY := 21123;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,32093,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsworn Scalewing - In Combat - Cast 'Poison Spit'");

-- Fingrom SAI
SET @ENTRY := 20757;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,14034,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fingrom - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,17145,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fingrom - Within 0-8 Range - Cast 'Blast Wave'"),
(@ENTRY,0,2,0,2,0,100,1,0,10,0,0,11,33245,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fingrom - Between 0-10% Health - Cast 'Ice Barrier' (No Repeat)");

-- Glumdor SAI
SET @ENTRY := 20730;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glumdor - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glumdor - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,13000,11,32009,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glumdor - In Combat - Cast 'Cutdown'"),
(@ENTRY,0,3,0,0,0,100,0,5000,9000,30000,38000,11,35240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glumdor - In Combat - Cast 'Bloodmaul Intoxication'"),
(@ENTRY,0,4,0,0,0,100,0,10000,10000,35000,44000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glumdor - In Combat - Cast 'Demoralizing Shout'"),
(@ENTRY,0,5,0,0,0,100,0,14000,15000,25000,30000,11,36208,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glumdor - In Combat - Cast 'Steal Weapon'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage');

-- Gore-Scythe Ravager SAI
SET @ENTRY := 21423;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,17000,18000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gore-Scythe Ravager - Within 0-5 Range - Cast 'Rend'");

-- Gorr'Dim SAI
SET @ENTRY := 20732;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gorr'Dim - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,30000,38000,11,35240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorr'Dim - In Combat - Cast 'Bloodmaul Intoxication'"),
(@ENTRY,0,2,0,9,0,100,0,0,8,13600,14500,11,15091,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorr'Dim - Within 0-8 Range - Cast 'Blast Wave'"),
(@ENTRY,0,3,0,1,0,100,0,500,1000,600000,600000,11,35917,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorr'Dim - Out of Combat - Cast 'Fiery Intellect'");

-- Grishna Matriarch SAI
SET @ENTRY := 20329;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grishna Matriarch - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,37473,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grishna Matriarch - On Respawn - Cast 'Detect Whispers' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,33000,39000,11,37579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grishna Matriarch - In Combat - Cast 'Impending Doom'"),
(@ENTRY,0,3,0,2,0,100,0,0,40,19000,25000,11,34110,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grishna Matriarch - Between 0-40% Health - Cast 'Shadow Mend'");

-- Korgaah SAI
SET @ENTRY := 20723;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Korgaah - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Korgaah - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,10,25000,28000,11,23600,0,0,0,0,0,1,0,0,0,0,0,0,0,"Korgaah - Within 0-10 Range - Cast 'Piercing Howl'"),
(@ENTRY,0,3,0,0,0,100,0,2000,4500,12000,13000,11,34802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Korgaah - In Combat - Cast 'Kick'"),
(@ENTRY,0,4,0,0,0,100,0,5000,9000,30000,38000,11,35240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Korgaah - In Combat - Cast 'Bloodmaul Intoxication'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage');

-- Lashh'an Matriarch SAI
SET @ENTRY := 20113;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lashh'an Matriarch - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,33000,39000,11,37579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lashh'an Matriarch - In Combat - Cast 'Impending Doom'"),
(@ENTRY,0,2,0,2,0,100,0,0,40,19000,25000,11,34110,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Matriarch - Between 0-40% Health - Cast 'Shadow Mend'");

-- Lashh'an Talonite SAI
SET @ENTRY := 19943;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,67,0,100,0,9000,12000,0,0,11,37685,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lashh'an Talonite - On Behind Target - Cast 'Backstab'"),
(@ENTRY,0,1,0,1,0,100,1,3000,5000,0,0,11,34854,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Talonite - Out of Combat - Cast 'Lashh'an Kaliri' (No Repeat)");

-- Lashh'an Windwalker SAI
SET @ENTRY := 19945;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lashh'an Windwalker - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Windwalker - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Windwalker - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Windwalker - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,4,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Windwalker - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Lashh'an Wing Guard SAI
SET @ENTRY := 19944;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,13600,14500,11,37577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lashh'an Wing Guard - Within 0-5 Range - Cast 'Debilitating Strike'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,36888,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lashh'an Wing Guard - On Aggro - Cast 'Angry Arakkoa Ghost' (No Repeat)");

-- Living Grove Defender SAI
SET @ENTRY := 21072;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,8000,12000,11,12747,0,0,0,0,0,2,0,0,0,0,0,0,0,"Living Grove Defender - Within 0-30 Range - Cast 'Entangling Roots'");

-- Mana-debt Slave SAI
SET @ENTRY := 23154;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,1000,1000,1000,1000,11,39550,2,0,0,0,0,1,0,0,0,0,0,0,0,"Mana-debt Slave - Out of Combat - Cast 'Arcane Channeling' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,9000,10000,11,12555,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mana-debt Slave - Within 0-5 Range - Cast 'Pummel'");

-- Mature Cavern Crawler SAI
SET @ENTRY := 22132;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,10000,15000,11,7951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mature Cavern Crawler - In Combat - Cast 'Toxic Spit'");

-- Mature Silkwing SAI
SET @ENTRY := 21839;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,4500,12000,13000,11,32914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mature Silkwing - In Combat - Cast 'Wing Buffet'");

-- Misha SAI
SET @ENTRY := 10204;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,17156,0,0,0,0,0,2,0,0,0,0,0,0,0,"Misha - In Combat - Cast 'Maul'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,19000,23000,11,6749,0,0,0,0,0,2,0,0,0,0,0,0,0,"Misha - In Combat - Cast 'Wide Swipe'");

-- Mo'arg Extractor SAI
SET @ENTRY := 22304;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,22000,26000,11,40818,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mo'arg Extractor - In Combat - Cast 'Toxic Slime'"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,15000,15000,11,40839,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mo'arg Extractor - In Combat - Cast 'Drill'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,40454,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Extractor - Between 0-30% Health - Cast 'Frighten' (No Repeat)");

-- Morcrush SAI
SET @ENTRY := 18690;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,16000,11,35238,0,0,0,0,0,1,0,0,0,0,0,0,0,"Morcrush - Within 0-5 Range - Cast 'War Stomp'");

-- Morcrush Shardling SAI
SET @ENTRY := 22344;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,34970,0,0,0,0,0,1,0,0,0,0,0,0,0,"Morcrush Shardling - Between 0-30% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Morcrush Shardling - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,9000,9000,18000,20000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"Morcrush Shardling - In Combat - Cast 'Thunderclap'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s goes into a frenzy!',16,0,100,0,0,0, 'combat Frenzy');

-- Mugdorg SAI
SET @ENTRY := 20726;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3500,6400,11,12058,64,0,0,0,0,2,0,0,0,0,0,0,0,"Mugdorg - In Combat - Cast 'Chain Lightning'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mugdorg - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mugdorg - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'"),
(@ENTRY,0,3,0,0,0,100,0,5000,9000,30000,38000,11,35240,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mugdorg - In Combat - Cast 'Bloodmaul Intoxication'"),
(@ENTRY,0,4,0,2,0,100,1,0,40,0,0,11,11986,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mugdorg - Between 0-40% Health - Cast 'Healing Wave' (No Repeat)");

-- Ogri'la Peacekeeper SAI
SET @ENTRY := 23115;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ogri'la Peacekeeper - Within 0-20 Range - Cast 'Net'"),
(@ENTRY,0,1,0,0,0,100,0,6000,7000,18000,22500,11,42691,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ogri'la Peacekeeper - In Combat - Cast 'Peace of Ogri'la'");

-- Raven's Wood Stonebark SAI
SET @ENTRY := 21325;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,15000,17000,11,37823,0,0,0,0,0,2,0,0,0,0,0,0,0,"Raven's Wood Stonebark - Within 0-30 Range - Cast 'Entangling Roots'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,18000,24000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Raven's Wood Stonebark - Within 0-10 Range - Cast 'Stomp'"),
(@ENTRY,0,2,0,2,0,100,0,0,55,20000,21000,11,37709,0,0,0,0,0,1,0,0,0,0,0,0,0,"Raven's Wood Stonebark - Between 0-55% Health - Cast 'Wild Regeneration'");

-- Razak Ironsides SAI
SET @ENTRY := 21118;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,36246,64,0,0,0,0,2,0,0,0,0,0,0,0,"Razak Ironsides - In Combat - Cast 'Shoot Tech Gun'");

-- Rema SAI
SET @ENTRY := 21956;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rema - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rema - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,13000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rema - In Combat - Cast 'Rend'"),
(@ENTRY,0,3,0,0,0,100,0,6000,9000,20000,22000,11,5781,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rema - In Combat - Cast 'Threatening Growl'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Rexxar SAI
SET @ENTRY := 21984;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,14500,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rexxar - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4500,16000,19000,11,18813,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rexxar - In Combat - Cast 'Knock Away'"),
(@ENTRY,0,4,0,4,0,100,1,0,0,0,0,11,3391,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rexxar - On Aggro - Cast 'Thrash' (No Repeat)");

-- Ridgespine Horror SAI
SET @ENTRY := 20998;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ridgespine Horror - On Respawn - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,1,0,7,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ridgespine Horror - On Evade - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,30,8000,9000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ridgespine Horror - Within 0-30 Range - Cast 'Web'"),
(@ENTRY,0,3,0,0,0,100,0,2000,4500,12000,16000,11,7951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ridgespine Horror - In Combat - Cast 'Toxic Spit'");

-- Ridgespine Stalker SAI
SET @ENTRY := 20714;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ridgespine Stalker - On Respawn - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,1,0,7,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ridgespine Stalker - On Evade - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,15000,11,744,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ridgespine Stalker - In Combat - Cast 'Poison'");

-- Rip-Blade Ravager SAI
SET @ENTRY := 22123;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,16000,17000,11,3242,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rip-Blade Ravager - In Combat - Cast 'Ravage'");

-- Ruuan Weald Basilisk SAI
SET @ENTRY := 20987;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,35382,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan Weald Basilisk - On Aggro - Cast 'Rushing Charge' (No Repeat)");

-- Ruuan Weald Sister SAI
SET @ENTRY := 22151;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan Weald Sister - Within 0-20 Range - Cast 'Net'");

-- Ruuan'ok Cloudgazer SAI
SET @ENTRY := 19985;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan'ok Cloudgazer - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Cloudgazer - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Cloudgazer - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'");

-- Ruuan'ok Matriarch SAI
SET @ENTRY := 20211;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan'ok Matriarch - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,37473,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Matriarch - On Respawn - Cast 'Detect Whispers' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,33000,39000,11,37579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan'ok Matriarch - In Combat - Cast 'Impending Doom'"),
(@ENTRY,0,3,0,2,0,100,0,0,40,19000,25000,11,34110,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Matriarch - Between 0-40% Health - Cast 'Shadow Mend'"),
(@ENTRY,0,4,0,11,0,100,1,0,0,0,0,11,35784,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Matriarch - On Respawn - Cast 'Arakkoa Egg' (No Repeat)");

-- Ruuan'ok Ravenguard SAI
SET @ENTRY := 19987;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,13000,11,37581,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan'ok Ravenguard - Within 0-5 Range - Cast 'Thundercleave'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,36888,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ruuan'ok Ravenguard - On Aggro - Cast 'Angry Arakkoa Ghost' (No Repeat)");

-- Ruuan'ok Skyfury SAI
SET @ENTRY := 19986;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,10000,12000,11,37681,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ruuan'ok Skyfury - In Combat - Cast 'Lightning Fury'");

-- Scorch Imp SAI
SET @ENTRY := 21021;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scorch Imp - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,30000,35000,11,37844,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scorch Imp - In Combat - Cast 'Fire Ward'");

-- Silkwing SAI
SET @ENTRY := 21373;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,16000,19000,11,32914,0,0,0,0,0,1,0,0,0,0,0,0,0,"Silkwing - In Combat - Cast 'Wing Buffet'");

-- Silkwing Larva SAI
SET @ENTRY := 20747;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,70,1,0,0,0,0,11,36948,0,0,0,0,0,1,0,0,0,0,0,0,0,"Silkwing Larva - On Aggro - Cast 'Silkwing' (No Repeat)");

-- Simon Unit SAI
SET @ENTRY := 23385;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,34447,64,0,0,0,0,2,0,0,0,0,0,0,0,"Simon Unit - In Combat - Cast 'Arcane Missiles'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,13600,14500,11,32614,0,0,0,0,0,1,0,0,0,0,0,0,0,"Simon Unit - Within 0-10 Range - Cast 'Arcane Explosion'"),
(@ENTRY,0,2,0,0,0,100,0,9000,12000,16000,22000,11,36508,0,0,0,0,0,2,0,0,0,0,0,0,0,"Simon Unit - In Combat - Cast 'Energy Surge'");

-- Slavering Slave SAI
SET @ENTRY := 23246;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,7000,15000,19000,11,40976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slavering Slave - In Combat - Cast 'Slimy Spittle'");

-- Speaker Mar'grom SAI
SET @ENTRY := 18693;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,12466,64,0,0,0,0,2,0,0,0,0,0,0,0,"Speaker Mar'grom - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,16000,18000,11,15241,0,0,0,0,0,2,0,0,0,0,0,0,0,"Speaker Mar'grom - In Combat - Cast 'Scorch'"),
(@ENTRY,0,2,0,0,0,100,0,5000,10000,33000,35000,11,37844,0,0,0,0,0,1,0,0,0,0,0,0,0,"Speaker Mar'grom - In Combat - Cast 'Fire Ward'");

-- Station Bot-Jock SAI
SET @ENTRY := 21152;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,36246,64,0,0,0,0,2,0,0,0,0,0,0,0,"Station Bot-Jock - In Combat - Cast 'Shoot Tech Gun'");

-- Strider Jock SAI
SET @ENTRY := 21427;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,36246,64,0,0,0,0,2,0,0,0,0,0,0,0,"Strider Jock - In Combat - Cast 'Shoot Tech Gun'");

-- Stronglimb Deeproot SAI
SET @ENTRY := 21023;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,12000,15000,11,11922,0,0,0,0,0,4,0,0,0,0,0,0,0,"Stronglimb Deeproot - Within 0-30 Range - Cast 'Entangling Roots'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,18000,22000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stronglimb Deeproot - Within 0-10 Range - Cast 'Stomp'");

-- Sylvanaar Ancient Protector SAI
SET @ENTRY := 20126;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,12000,15000,11,11922,0,0,0,0,0,4,0,0,0,0,0,0,0,"Sylvanaar Ancient Protector - Within 0-30 Range - Cast 'Entangling Roots'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,18000,22000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sylvanaar Ancient Protector - Within 0-10 Range - Cast 'Stomp'");

-- Sylvanaar Sentinel SAI
SET @ENTRY := 19500;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Sylvanaar Sentinel - In Combat - Cast 'Shoot'");

-- Thunderlord Grunt SAI
SET @ENTRY := 19449;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Thunderlord Grunt - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,2,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thunderlord Grunt - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thunderlord Grunt - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,5,8000,9000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thunderlord Grunt - Within 0-5 Range - Cast 'Cleave'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Trogma SAI
SET @ENTRY := 21640;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Trogma - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Trogma - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,9000,11000,11,34802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Trogma - Within 0-5 Range - Cast 'Kick'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Unbound Ethereal SAI
SET @ENTRY := 22244;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,15000,20000,11,38932,0,0,0,0,0,2,0,0,0,0,0,0,0,"Unbound Ethereal - In Combat - Cast 'Blink'");

-- Vekh'nir Dreadhawk SAI
SET @ENTRY := 19984;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,11642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Dreadhawk - Between 0-30% Health - Cast 'Heal' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,16000,11,37582,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Dreadhawk - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,36888,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Dreadhawk - On Aggro - Cast 'Angry Arakkoa Ghost' (No Repeat)");

-- Vekh'nir Keeneye SAI
SET @ENTRY := 19982;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,17000,20000,11,35321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vekh'nir Keeneye - Within 0-5 Range - Cast 'Gushing Wound'"),
(@ENTRY,0,1,0,2,0,100,0,0,40,14000,21000,11,38541,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Keeneye - Between 0-40% Health - Cast 'Evasion'");

-- Vekh'nir Matriarch SAI
SET @ENTRY := 20161;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vekh'nir Matriarch - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,37473,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Matriarch - On Respawn - Cast 'Detect Whispers' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,33000,39000,11,37579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vekh'nir Matriarch - In Combat - Cast 'Impending Doom'"),
(@ENTRY,0,3,0,2,0,100,0,0,40,19000,25000,11,34110,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Matriarch - Between 0-40% Health - Cast 'Shadow Mend'"),
(@ENTRY,0,4,0,11,0,100,1,0,0,0,0,11,35784,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vekh'nir Matriarch - On Respawn - Cast 'Arakkoa Egg' (No Repeat)");

-- Vekh'nir Stormcaller SAI
SET @ENTRY := 19983;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,9000,20000,22000,11,32717,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vekh'nir Stormcaller - In Combat - Cast 'Hurricane'"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,12000,15000,11,37654,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vekh'nir Stormcaller - In Combat - Cast 'Lightning Tether'");

-- Vile Fire-Soul SAI
SET @ENTRY := 22298;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,40,8000,9000,11,9053,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Fire-Soul - Within 0-40 Range - Cast 'Fireball'");

-- Void Hound SAI
SET @ENTRY := 22500;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,20000,25000,11,36406,0,0,0,0,0,2,0,0,0,0,0,0,0,"Void Hound - In Combat - Cast 'Double Breath'");

-- Void Terror SAI
SET @ENTRY := 19980;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,20000,25000,11,36406,0,0,0,0,0,2,0,0,0,0,0,0,0,"Void Terror - In Combat - Cast 'Double Breath'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,15000,17000,11,36405,0,0,0,0,0,2,0,0,0,0,0,0,0,"Void Terror - Within 0-10 Range - Cast 'Stomp'");

-- Wyrm from Beyond SAI
SET @ENTRY := 21796;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,8000,14000,17000,11,13321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrm from Beyond - In Combat - Cast 'Mana Burn'"),
(@ENTRY,0,1,0,0,0,100,0,10000,10000,20000,20000,11,36574,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrm from Beyond - In Combat - Cast 'Phase Slip'");

-- Wyrmcult Acolyte SAI
SET @ENTRY := 21383;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Acolyte - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Acolyte - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Acolyte - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,9,0,100,0,0,8,13600,14500,11,11969,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Acolyte - Within 0-8 Range - Cast 'Fire Nova'"),
(@ENTRY,0,4,0,0,0,100,0,8000,9000,22000,24000,11,32707,0,0,0,0,0,4,0,0,0,0,0,0,0,"Wyrmcult Acolyte - In Combat - Cast 'Incinerate'"),
(@ENTRY,0,5,0,11,0,100,1,0,0,0,0,11,37635,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Acolyte - On Respawn - Cast 'Blessing of the Black' (No Repeat)"),
(@ENTRY,0,6,0,2,0,100,1,0,30,0,0,11,17139,1,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Acolyte - Between 0-30% Health - Cast 'Power Word: Shield' (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Wyrmcult Blessed SAI
SET @ENTRY := 21492;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Blessed - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,11969,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Blessed - Within 0-8 Range - Cast 'Fire Nova'");

-- Wyrmcult Hewer
SET @ENTRY := 21810;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Enrage at 30% HP'),
(@ENTRY,0,1,0,61,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Say Text at 30% HP'),
(@ENTRY,0,2,0,9,0,100,0,0,5,15000,18000,11,37704,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Whirlwind on Close');
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Wyrmcult Hunter SAI
SET @ENTRY := 22308;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Hunter - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,22000,27000,11,39182,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Hunter - In Combat - Cast 'Serpent Sting'");

-- Wyrmcult Provisioner SAI
SET @ENTRY := 22099;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,12500,11,35857,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Provisioner - Within 0-5 Range - Cast 'Torch'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,15000,18000,11,34802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Provisioner - In Combat - Cast 'Kick'");

-- Wyrmcult Scout SAI
SET @ENTRY := 21637;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmcult Scout - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,11969,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Scout - Within 0-8 Range - Cast 'Fire Nova'"),
(@ENTRY,0,2,0,1,0,100,1,3000,5000,0,0,11,37547,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Scout - Out of Combat - Cast 'Wyrmcult BroodlingCall' (No Repeat)");

-- Wyrmcult Zealot SAI
SET @ENTRY := 21382;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Zealot - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Zealot - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,8,13600,14500,11,11969,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Zealot - Within 0-8 Range - Cast 'Fire Nova'"),
(@ENTRY,0,3,0,1,0,100,1,3000,5000,0,0,11,37547,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmcult Zealot - Out of Combat - Cast 'Wyrmcult BroodlingCall' (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Young Crust Burster SAI
SET @ENTRY := 21381;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,11500,13000,11,21067,0,0,0,0,0,2,0,0,0,0,0,0,0,"Young Crust Burster - In Combat - Cast 'Poison Bolt'"),
(@ENTRY,0,1,0,9,0,100,0,8,25,13600,14500,11,37359,0,0,0,0,0,2,0,0,0,0,0,0,0,"Young Crust Burster - Within 8-25 Range - Cast 'Rush'");

-- Area 52 Big Bruiser SAI
SET @ENTRY := 20484;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Area 52 Big Bruiser - Within 0-20 Range - Cast 'Net'");

-- Area 52 Bruiser SAI
SET @ENTRY := 20485;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Area 52 Bruiser - Within 0-20 Range - Cast 'Net'");

-- Avatar of Sathal SAI
SET @ENTRY := 21925;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Avatar of Sathal - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,7000,9000,22000,27000,11,34017,0,0,0,0,0,4,0,0,0,0,0,0,0,"Avatar of Sathal - In Combat - Cast 'Rain of Chaos'");

-- Barbscale Crocolisk SAI
SET @ENTRY := 20773;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4500,12000,14000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Barbscale Crocolisk - In Combat - Cast 'Tendon Rip'");

-- Cosmowrench Bruiser SAI
SET @ENTRY := 22494;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cosmowrench Bruiser - Within 0-20 Range - Cast 'Net'");

-- Ethereum Archon SAI
SET @ENTRY := 20458;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,8000,20000,27000,11,35924,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Archon - In Combat - Cast 'Energy Flux'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3500,18000,19000,11,36513,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Archon - In Combat - Cast 'Intangible Presence'"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,36515,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Archon - On Aggro - Cast 'Shadowtouched' (No Repeat)");

-- Ethereum Assassin SAI
SET @ENTRY := 20452;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,67,0,100,0,9000,12000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Assassin - On Behind Target - Cast 'Backstab'"),
(@ENTRY,0,1,0,13,0,100,0,2000,4500,0,0,11,34802,0,0,0,0,0,7,0,0,0,0,0,0,0,"Ethereum Assassin - On Victim Casting - Cast 'Kick'"),
(@ENTRY,0,2,0,0,0,100,0,7000,9000,18000,20000,11,32920,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Assassin - In Combat - Cast 'Warp'");

-- Ethereum Avenger SAI
SET @ENTRY := 22821;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,33000,35000,11,39489,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Avenger - In Combat - Cast 'Enchanted Weapons'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4000,120000,120000,11,32064,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Avenger - In Combat - Cast 'Battle Shout'"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,36509,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Avenger - On Aggro - Cast 'Charge' (No Repeat)");

-- Ethereum Gladiator SAI
SET @ENTRY := 20854;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,16000,17000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Gladiator - In Combat - Cast 'Hamstring'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,14000,15000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Gladiator - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,2,0,9,0,100,0,0,5,8000,9000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Gladiator - Within 0-5 Range - Cast 'Cleave'");

-- Ethereum Jailor SAI
SET @ENTRY := 23008;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3500,18000,19000,11,36513,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Jailor - In Combat - Cast 'Intangible Presence'");

-- Ethereum Nexus-Stalker SAI
SET @ENTRY := 20474;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,500,1000,600000,600000,11,36515,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Nexus-Stalker - Out of Combat - Cast 'Shadowtouched'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,25000,28000,11,36516,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Nexus-Stalker - In Combat - Cast 'Power Siphon'"),
(@ENTRY,0,2,0,9,0,100,0,0,5,9000,11000,11,36517,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Nexus-Stalker - Within 0-5 Range - Cast 'Shadowsurge'");

-- Ethereum Nullifier SAI
SET @ENTRY := 22822;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3500,18000,19000,11,36513,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Nullifier - In Combat - Cast 'Intangible Presence'");

-- Ethereum Overlord SAI
SET @ENTRY := 20459;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,33000,35000,11,36510,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Overlord - In Combat - Cast 'Enchanted Weapons'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4000,120000,120000,11,32064,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Overlord - In Combat - Cast 'Battle Shout'"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,36509,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Overlord - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,3,0,1,0,40,0,500,1000,600000,600000,11,36515,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Overlord - Out of Combat - Cast 'Shadowtouched'");

-- Ethereum Researcher SAI
SET @ENTRY := 20456;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Researcher - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,2,0,100,0,0,40,14000,21000,11,36506,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereum Researcher - Between 0-40% Health - Cast 'Energy Charge'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,19000,20000,11,36508,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Researcher - In Combat - Cast 'Energy Surge'");

-- Ethereum Shocktrooper SAI
SET @ENTRY := 20453;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,36500,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Shocktrooper - In Combat - Cast 'Glaive'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,16000,18000,11,31553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereum Shocktrooper - Within 0-5 Range - Cast 'Hamstring'");

-- Fel Imp SAI
SET @ENTRY := 21135;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,36227,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Imp - In Combat - Cast 'Firebolt'");

-- Hatecryer SAI
SET @ENTRY := 20930;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,18000,22000,11,34017,0,0,0,0,0,4,0,0,0,0,0,0,0,"Hatecryer - In Combat - Cast 'Rain of Chaos'"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,55000,60000,11,36541,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hatecryer - In Combat - Cast 'Curse of Burning Shadows'");

-- Ironspine Forgelord SAI
SET @ENTRY := 20928;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,16000,19000,11,37179,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ironspine Forgelord - Within 0-10 Range - Cast 'Hammer Slam'"),
(@ENTRY,0,1,0,11,0,100,1,0,0,0,0,11,33962,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ironspine Forgelord - On Respawn - Cast 'Toughen' (No Repeat)");

-- Legion Destroyer SAI
SET @ENTRY := 20403;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,7000,16000,18000,11,11428,0,0,0,0,0,2,0,0,0,0,0,0,0,"Legion Destroyer - In Combat - Cast 'Knockdown'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,16000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Legion Destroyer - Within 0-5 Range - Cast 'Mortal Strike'");

-- Legion Shocktrooper SAI
SET @ENTRY := 20402;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,15000,11,35144,0,0,0,0,0,2,0,0,0,0,0,0,0,"Legion Shocktrooper - Within 0-5 Range - Cast 'Vicious Rend'");

-- Mana Beast SAI
SET @ENTRY := 21267;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,15000,18000,11,36484,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mana Beast - In Combat - Cast 'Mana Burn'");

-- Nuramoc SAI
SET @ENTRY := 20932;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,12000,13000,11,15797,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nuramoc - Within 0-30 Range - Cast 'Lightning Breath'"),
(@ENTRY,0,1,0,9,0,100,0,0,25,19000,22000,11,21971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nuramoc - Within 0-25 Range - Cast 'Poison Bolt'"),
(@ENTRY,0,2,0,11,0,100,1,0,0,0,0,11,38905,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nuramoc - On Respawn - Cast 'Prismatic Shield' (No Repeat)");

-- Overseer Azarad SAI
SET @ENTRY := 20685;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,18000,20000,11,35492,0,0,0,0,0,2,0,0,0,0,0,0,0,"Overseer Azarad - In Combat - Cast 'Exhaustion'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,35491,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overseer Azarad - Between 0-30% Health - Cast 'Furious Rage' (No Repeat)");

-- Protectorate Regenerator SAI
SET @ENTRY := 21783;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,34232,64,0,0,0,0,2,0,0,0,0,0,0,0,"Protectorate Regenerator - In Combat - Cast 'Holy Bolt'");

-- Scythetooth Raptor SAI
SET @ENTRY := 20634;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scythetooth Raptor - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scythetooth Raptor - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,37359,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scythetooth Raptor - On Aggro - Cast 'Rush' (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Shimmerwing Moth SAI
SET @ENTRY := 20611;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,12000,14000,11,36592,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shimmerwing Moth - In Combat - Cast 'Shimmerwing Dust'"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,17000,18500,11,32914,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shimmerwing Moth - In Combat - Cast 'Wing Buffet'");

-- Sunfury Blood Knight SAI
SET @ENTRY := 21089;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Blood Knight - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Blood Knight - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,8000,10000,12000,27000,11,35871,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunfury Blood Knight - In Combat - Cast 'Spellbreaker'"),
(@ENTRY,0,3,0,2,0,100,1,0,20,0,0,11,36476,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunfury Blood Knight - Between 0-20% Health - Cast 'Blood Heal' (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Terrorguard Protector SAI
SET @ENTRY := 21923;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,8000,9000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Terrorguard Protector - Within 0-5 Range - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,15000,15500,11,37488,0,0,0,0,0,2,0,0,0,0,0,0,0,"Terrorguard Protector - In Combat - Cast 'Fel Flames'");

-- Tormented Citizen SAI
SET @ENTRY := 21065;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Tormented Citizen - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,18000,20000,11,11980,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tormented Citizen - In Combat - Cast 'Curse of Weakness'"),
(@ENTRY,0,2,0,0,0,100,1,8000,9000,0,0,11,36153,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tormented Citizen - In Combat - Cast 'Soulbind' (No Repeat)");

-- Tormented Soul SAI
SET @ENTRY := 20512;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,36153,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tormented Soul - On Aggro - Cast 'Soulbind' (No Repeat)");

-- Tyrantus SAI
SET @ENTRY := 20931;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,18000,20000,11,35321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tyrantus - In Combat - Cast 'Gushing Wound'"),
(@ENTRY,0,1,0,2,0,100,1,0,40,0,0,11,36629,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tyrantus - Between 0-40% Health - Cast 'Terrifying Roar' (No Repeat)");

-- Warp Monstrosity SAI
SET @ENTRY := 20516;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,13901,64,0,0,0,0,2,0,0,0,0,0,0,0,"Warp Monstrosity - In Combat - Cast 'Arcane Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,3000,5000,20000,25000,11,36577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warp Monstrosity - In Combat - Cast 'Warp Storm'");

-- Warp-Gate Engineer SAI
SET @ENTRY := 20404;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,15000,17000,11,35147,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warp-Gate Engineer - In Combat - Cast 'Sundering Swipe'");

-- Wrath Lord SAI
SET @ENTRY := 20929;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrath Lord - Within 0-5 Range - Cast 'Cleave'");
