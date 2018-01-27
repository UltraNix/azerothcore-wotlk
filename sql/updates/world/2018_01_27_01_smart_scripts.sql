-- Kam Deepfury SAI
SET @ENTRY := 1666;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,1,1000,1000,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kam Deepfury - In Combat - Cast 'Defensive Stance' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,8000,10000,16000,11,8242,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kam Deepfury - In Combat - Cast 'Shield Slam'"),
(@ENTRY,0,2,0,0,0,100,0,5000,12000,15000,25000,11,3419,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kam Deepfury - In Combat - Cast 'Improved Blocking'"),
(@ENTRY,0,3,0,0,0,100,0,1000,5000,35000,45000,11,871,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kam Deepfury - In Combat - Cast 'Shield Wall'");
-- Old Serra'kis SAI
SET @ENTRY := 4830;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,11,8434,0,0,0,0,0,1,0,0,0,0,0,0,0,"Old Serra'kis - On Reset - Cast 'Leech Pulse'");
-- Interrogator Vishas SAI
SET @ENTRY := 3983;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Interrogator Vishas - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,5,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Interrogator Vishas - On Killed Unit - Say Line 3"),
(@ENTRY,0,2,0,2,0,100,1,50,70,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Interrogator Vishas - Between 50-70% Health - Say Line 1 (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Interrogator Vishas - Between 0-30% Health - Say Line 2 (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,3000,7000,8000,14000,11,2767,0,0,0,0,0,5,30,0,0,0,0,0,0,"Interrogator Vishas - In Combat - Cast 'Shadow Word: Pain'"),
(@ENTRY,0,5,0,6,0,100,0,0,0,0,0,1,0,0,0,0,0,0,19,3981,100,0,0,0,0,0,"Interrogator Vishas - On Just Died - Say Line 0"),
(@ENTRY,0,6,0,0,0,100,0,2000,5000,15000,21000,11,9034,0,0,0,0,0,5,0,0,0,0,0,0,0,"Interrogator Vishas - In Combat - Cast 'Immolate'");
-- Azshir the Sleepless SAI
SET @ENTRY := 6490;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,37,0,90,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0,0,0,0,"Azshir the Sleepless - On Initialize - Despawn In 500 ms"),
(@ENTRY,0,1,0,0,0,100,0,7000,11000,70000,70000,11,5137,0,0,0,0,0,2,0,0,0,0,0,0,0,"Azshir the Sleepless - In Combat - Cast Call of the Grave"),
(@ENTRY,0,2,0,0,0,100,0,6000,8000,20000,20000,11,7399,0,0,0,0,0,5,0,0,0,0,0,0,0,"Azshir the Sleepless - In Combat - Cast 'Terrify'"),
(@ENTRY,0,3,0,0,0,100,0,14000,14000,20000,20000,11,9373,0,0,0,0,0,2,0,0,0,0,0,0,0,"Azshir the Sleepless - In Combat - Cast Soul Siphon");
-- Herod SAI
SET @ENTRY := 3975;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,3000,7000,6000,10000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Herod - In Combat - Cast 'Cleave'"),
(@ENTRY,0,2,3,0,0,100,0,15000,15000,30000,40000,11,8989,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - In Combat - Cast 'Whirlwind'"),
(@ENTRY,0,3,0,61,0,100,0,15000,15000,30000,40000,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - In Combat - Say Line 1"),
(@ENTRY,0,4,5,2,0,100,1,0,50,0,0,11,8269,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - Between 0-50% Health - Cast 'Frenzy' (No Repeat)"),
(@ENTRY,0,5,6,61,0,100,0,0,50,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - Between 0-50% Health - Say Line 4 (No Repeat)"),
(@ENTRY,0,6,0,61,0,100,0,0,50,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - Between 0-50% Health - Say Line 2 (No Repeat)"),
(@ENTRY,0,7,0,5,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - On Killed Unit - Say Line 3"),
(@ENTRY,0,8,9,6,0,100,0,0,0,0,0,107,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - On Just Died - Summon Creature Group 1"),
(@ENTRY,0,9,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,19,6575,100,0,0,0,0,0,"Herod - On Just Died - Say Line 0"),
(@ENTRY,0,10,0,4,0,100,0,0,0,0,0,11,8260,0,0,0,0,0,1,0,0,0,0,0,0,0,"Herod - On Aggro - Cast 'Rushing Charge'");

-- Glassweb Spider SAI
SET @ENTRY := 5856;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,11,13299,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glassweb Spider - On Reset - Cast 'Poison Proc'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,8000,11000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glassweb Spider - Within 0-20 Range - Cast 'Web'");
-- Shleipnarr SAI
SET @ENTRY := 8280;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,12000,15000,11,13321,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shleipnarr - In Combat - Cast 'Mana Burn'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,25000,32000,11,7399,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shleipnarr - In Combat - Cast 'Terrify'");
-- Dark Iron Geologist SAI
SET @ENTRY := 5839;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Iron Geologist - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Iron Geologist - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,5,30,12000,14000,11,8858,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Iron Geologist - Within 5-30 Range - Cast 'Bomb'");
-- Magma Elemental SAI
SET @ENTRY := 5855;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,12000,16000,11,11970,2,0,0,0,0,2,0,0,0,0,0,0,0,"Magma Elemental - In Combat - Cast 'Fire Nova'");
-- Heavy War Golem SAI
SET @ENTRY := 5854;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,13000,19000,11,12612,0,0,0,0,0,1,0,0,0,0,0,0,0,"Heavy War Golem - Within 0-5 Range - Cast 'Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,5000,8000,11000,17000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Heavy War Golem - In Combat - Cast 'Trample'");
-- Inferno Elemental SAI
SET @ENTRY := 5852;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,11000,14000,11,10733,0,0,0,0,0,2,0,0,0,0,0,0,0,"Inferno Elemental - In Combat - Cast 'Flame Spray'");
-- Margol the Rager SAI
SET @ENTRY := 5833;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,8000,14000,11,15549,0,0,0,0,0,2,0,0,0,0,0,0,0,"Margol the Rager - In Combat - Cast 'Chained Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,8000,12000,16000,20000,11,8147,0,0,0,0,0,1,0,0,0,0,0,0,0,"Margol the Rager - In Combat - Cast 'Thunderclap'");
-- Rekk'tilac SAI
SET @ENTRY := 8277;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,9000,16000,18000,11,3583,2,0,0,0,0,2,0,0,0,0,0,0,0,"Rekk'tilac - In Combat - Cast 'Deadly Poison'");
-- Scald SAI
SET @ENTRY := 8281;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,14000,16000,11,11962,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scald - In Combat - Cast 'Immolate'");
-- Greater Lava Spider SAI
SET @ENTRY := 5858;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,5000,7000,13000,11,11985,0,0,0,0,0,2,0,0,0,0,0,0,0,"Greater Lava Spider - In Combat - Cast 'Fireball'");
-- Slave Worker SAI
SET @ENTRY := 5843;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,12000,15000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slave Worker - In Combat - Cast 'Sunder Armor'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slave Worker - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Smoldar SAI
SET @ENTRY := 8278;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,9000,17000,19000,11,5213,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smoldar - In Combat - Cast 'Molten Metal'");
-- Twilight Fire Guard SAI
SET @ENTRY := 5861;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,12000,18000,22000,11,11988,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Fire Guard - In Combat - Cast 'Fireball Volley'"),
(@ENTRY,0,1,0,4,0,100,0,0,0,0,0,11,18968,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Fire Guard - On Aggro - Cast 'Fire Shield'");
-- Twilight Dark Shaman SAI
SET @ENTRY := 5860;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,10000,14000,11,11824,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Dark Shaman - In Combat - Cast 'Shock'"),
(@ENTRY,0,1,0,0,0,100,0,7000,9000,15000,25000,11,7289,32,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Dark Shaman - In Combat - Cast 'Shrink'"),
(@ENTRY,0,2,0,14,0,100,0,700,40,16000,20000,11,11986,0,0,0,0,0,7,0,0,0,0,0,0,0,"Twilight Dark Shaman - Friendly At 700 Health - Cast 'Healing Wave'");
-- Twilight Geomancer SAI
SET @ENTRY := 5862;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Geomancer - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,7000,11000,18000,24000,11,11990,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Geomancer - In Combat - Cast 'Rain of Fire'"),
(@ENTRY,0,2,0,0,0,100,0,9000,13000,15000,19000,11,11436,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Geomancer - In Combat - Cast 'Slow'");
-- Twilight Idolater SAI
SET @ENTRY := 8419;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Idolater - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,18000,22000,11,11962,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Idolater - In Combat - Cast 'Immolate'");
-- Highlord Mastrogonde SAI
SET @ENTRY := 8282;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Highlord Mastrogonde - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,8000,14000,21000,25000,11,11639,0,0,0,0,0,5,0,0,0,0,0,0,0,"Highlord Mastrogonde - In Combat - Cast 'Shadow Word: Pain'"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,15000,18000,11,13323,0,0,0,0,0,6,0,0,0,0,0,0,0,"Highlord Mastrogonde - In Combat - Cast 'Polymorph'"),
(@ENTRY,0,3,0,2,0,100,0,0,50,50000,70000,11,11974,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highlord Mastrogonde - Between 0-50% Health - Cast 'Power Word: Shield'");
-- Slave Master Blackheart SAI
SET @ENTRY := 8283;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2000,3000,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Slave Master Blackheart - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,8000,9000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slave Master Blackheart - Within 0-20 Range - Cast 'Net'");
-- Incendosaur SAI
SET @ENTRY := 9318;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,12000,16000,11,11985,0,0,0,0,0,2,0,0,0,0,0,0,0,"Incendosaur - In Combat - Cast 'Fireball'");
-- Overseer Maltorius SAI
SET @ENTRY := 14621;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Overseer Maltorius - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,4000,12000,16000,22000,11,11639,0,0,0,0,0,5,0,0,0,0,0,0,0,"Overseer Maltorius - In Combat - Cast 'Shadow Word: Pain'"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,13000,16000,11,13323,0,0,0,0,0,6,0,0,0,0,0,0,0,"Overseer Maltorius - In Combat - Cast 'Polymorph'"),
(@ENTRY,0,3,0,2,0,100,0,0,50,40000,60000,11,11974,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overseer Maltorius - Between 0-50% Health - Cast 'Power Word: Shield'");
-- Zukk'ash Stinger SAI
SET @ENTRY := 5244;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,15,0,0,11,17170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zukk'ash Stinger - Between 0-15% Health - Cast 'Fatal Sting' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zukk'ash Stinger - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,1000,4000,15000,20000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zukk'ash Stinger - In Combat - Cast 'Venom Sting'");
DELETE FROM `creature_text` WHERE `entry`=5244;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(5244,0,0,"%s prepares to sting its victim as a last desperate move!",16,0,100,0,0,0,0,"Zukk'ash Stinger");
-- Silvermane Howler SAI
SET @ENTRY := 2925;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,32919,0,0,0,0,0,2,0,0,0,0,0,0,0,"Silvermane Howler - In Combat - Cast 'Snarl'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,18000,22000,11,3149,0,0,0,0,0,1,0,0,0,0,0,0,0,"Silvermane Howler - In Combat - Cast 'Furious Howl'"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,39,30,1,0,0,0,0,1,0,0,0,0,0,0,0,"Silvermane Howler - Between 0-50% Health - Call For Help (No Repeat)");
-- Savage Owlbeast SAI
SET @ENTRY := 2929;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,12,0,100,0,0,20,14000,18000,11,7938,0,0,0,0,0,2,0,0,0,0,0,0,0,"Savage Owlbeast - Target Between 0-20% Health - Cast 'Fatal Bite'");
-- Jalinde Summerdrake
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8214;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8214 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8214,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jalinde Summerdrake - In Combat CMC - Cast Shoot"),
(8214,0,1,0,9,0,100,0,5,30,9000,13000,11,15495,0,0,0,0,0,5,0,0,0,0,0,0,0,"Jalinde Summerdrake - Within 5-30 Range - Cast Explosive Shot"),
(8214,0,2,0,0,0,100,0,3000,5000,15000,21000,11,8806,32,0,0,0,0,5,0,0,0,0,0,0,0,"Jalinde Summerdrake - In Combat - Cast Poisoned Shot");
-- Highvale Ranger SAI
SET @ENTRY := 2694;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,30,30000,35000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Highvale Ranger - Within 0-30 Range - Cast 'Faerie Fire'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highvale Ranger - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Zealot SAI
SET @ENTRY := 2650;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Zealot - Between 0-50% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Zealot - Between 0-50% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=2650;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2650,0,0,"%s becomes enraged!",16,0,100,0,0,0,0,"Witherbark Zealot");
-- Razorbeak Skylord SAI
SET @ENTRY := 2659;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,12000,12000,16000,11,11019,0,0,0,0,0,1,0,0,0,0,0,0,0,"Razorbeak Skylord - In Combat - Cast 'Wing Flap'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,19000,11,3147,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razorbeak Skylord - Within 0-5 Range - Cast 'Rend Flesh'");
-- Grimungous SAI
SET @ENTRY := 8215;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,9000,13000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimungous - In Combat - Cast 'Trample'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,14000,20000,11,11876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimungous - Within 0-5 Range - Cast 'War Stomp'");
-- Shadra SAI
SET @ENTRY := 2707;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,11,13299,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadra - On Reset - Cast 'Poison Proc'"),
(@ENTRY,0,1,0,25,0,100,0,0,0,0,0,11,8601,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadra - On Reset - Cast 'Slowing Poison'"),
(@ENTRY,0,2,0,9,0,100,0,0,10,9000,10000,11,28991,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shadra - Within 0-10 Range - Cast 'Web'");
-- Add random movement for some creatures
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `guid` IN (69119,69117);
-- Pathing for Witherheart the Stalker
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=85478;
DELETE FROM `creature_addon` WHERE `guid`=85478;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(85478,854780,0,0,1,0,"");
DELETE FROM `waypoint_data` WHERE `id`=854780;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
(854780,1,-336.731,-2833.29,77.0363,0,0,0,0,100,0),
(854780,2,-334.463,-2814.89,80.383,0,0,0,0,100,0),
(854780,3,-348.051,-2805.34,80.0625,0,0,0,0,100,0),
(854780,4,-364.007,-2805.31,76.9893,0,0,0,0,100,0),
(854780,5,-376.958,-2796.97,77.4724,0,0,0,0,100,0),
(854780,6,-394.72,-2805.83,77.8546,0,0,0,0,100,0),
(854780,7,-390.019,-2822.94,74.1284,0,0,0,0,100,0),
(854780,8,-389.906,-2837.06,74.2824,0,0,0,0,100,0),
(854780,9,-402.354,-2843.73,76.9459,0,0,0,0,100,0),
(854780,10,-416.467,-2844.41,79.3868,0,0,0,0,100,0),
(854780,11,-421.565,-2852.64,79.3284,0,0,0,0,100,0),
(854780,12,-421.623,-2874.12,83.6468,0,0,0,0,100,0),
(854780,13,-428.279,-2885.91,84.8522,0,0,0,0,100,0),
(854780,14,-417.871,-2899.71,83.2011,0,0,0,0,100,0),
(854780,15,-421.714,-2912.49,82.035,0,0,0,0,100,0),
(854780,16,-409.008,-2915.46,80.4308,0,0,0,0,100,0),
(854780,17,-398.058,-2912.56,79.2019,0,0,0,0,100,0),
(854780,18,-388.929,-2926.26,77.9069,0,0,0,0,100,0),
(854780,19,-376.519,-2927.69,75.9121,0,0,0,0,100,0),
(854780,20,-372.09,-2931.3,75.3061,0,0,0,0,100,0),
(854780,21,-354.46,-2929.29,75.2535,0,0,0,0,100,0),
(854780,22,-339.972,-2930.95,76.0707,0,0,0,0,100,0),
(854780,23,-326.085,-2943.36,78.7858,0,0,0,0,100,0),
(854780,24,-313.89,-2944.59,80.8206,0,0,0,0,100,0),
(854780,25,-305.916,-2935.44,82.1426,0,0,0,0,100,0),
(854780,26,-307.534,-2917.76,80.3467,0,0,0,0,100,0),
(854780,27,-298.165,-2903.94,81.5407,0,0,0,0,100,0),
(854780,28,-301.296,-2890.28,81.1735,0,0,0,0,100,0),
(854780,29,-310.921,-2881.96,79.6081,0,0,0,0,100,0),
(854780,30,-313.692,-2872.43,80.082,0,0,0,0,100,0),
(854780,31,-312.576,-2859.04,80.4389,0,0,0,0,100,0),
(854780,32,-320.584,-2852.24,78.3489,0,0,0,0,100,0),
(854780,33,-336.88,-2851.17,77.2118,0,0,0,0,100,0);
