-- Aged Clefthoof SAI
SET @ENTRY := 17133;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32021,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aged Clefthoof - On Aggro - Cast 'Rushing Charge' (No Repeat)");

-- Alliance Halaani Guard SAI
SET @ENTRY := 18256;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,23337,64,0,0,0,0,2,0,0,0,0,0,0,0,"Alliance Halaani Guard - In Combat - Cast 'Shoot'");

-- Bleeding Hollow Refugee
UPDATE `smart_scripts` SET `event_param1`=2000, `event_param2`=4500, `event_param3`=18000, `event_param4`=20000 WHERE `entryorguid`=18292 AND `source_type`=0 AND `id`=0;

-- Boulderfist Crusher
UPDATE `smart_scripts` SET `event_param1`=2000, `event_param2`=4500, `event_param3`=18000, `event_param4`=20000 WHERE `entryorguid`=17134 AND `source_type`=0 AND `id`=0;

-- Boulderfist Hunter SAI
SET @ENTRY := 18352;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32248,64,0,0,0,0,2,0,0,0,0,0,0,0,"Boulderfist Hunter - In Combat - Cast 'Spear Throw'"),
(@ENTRY,0,1,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulderfist Hunter - On Aggro - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Boulderfist Mage SAI
SET @ENTRY := 17137;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Boulderfist Mage - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,6742,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulderfist Mage - Between 0-30% Health - Cast 'Bloodlust' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,7000,12000,15000,11,20795,0,0,0,0,0,2,0,0,0,0,0,0,0,"Boulderfist Mage - In Combat - Cast 'Fire Blast'"),
(@ENTRY,0,3,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulderfist Mage - On Aggro - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Boulderfist Saboteur SAI
SET @ENTRY := 18396;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32248,64,0,0,0,0,2,0,0,0,0,0,0,0,"Boulderfist Saboteur - In Combat - Cast 'Spear Throw'"),
(@ENTRY,0,1,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulderfist Saboteur - On Aggro - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Boulderfist Warrior SAI
SET @ENTRY := 17136;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Boulderfist Warrior - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,31994,0,0,0,0,0,2,0,0,0,0,0,0,0,"Boulderfist Warrior - On Aggro - Cast 'Shoulder Charge' (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Bro'Gaz the Clanless SAI
SET @ENTRY := 18684;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bro'Gaz the Clanless - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,12000,18000,11,12468,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bro'Gaz the Clanless - In Combat - Cast 'Flamestrike'"),
(@ENTRY,0,2,0,2,0,100,0,0,30,35000,45000,11,15586,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bro'Gaz the Clanless - Between 0-30% Health - Cast 'Heal'"),
(@ENTRY,0,3,0,9,0,100,0,0,5,14000,19000,11,38313,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bro'Gaz the Clanless - Within 0-5 Range - Cast 'Pummel'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Bull Elekk SAI
SET @ENTRY := 18289;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,14000,15000,11,15550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bull Elekk - Within 0-10 Range - Cast 'Trample'");

-- Cho'war the Pillager SAI
SET @ENTRY := 18423;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32323,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cho'war the Pillager - On Aggro - Cast 'Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,120000,120000,11,31403,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cho'war the Pillager - In Combat - Cast 'Battle Shout'"),
(@ENTRY,0,2,0,0,0,100,0,4000,5000,15000,15500,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cho'war the Pillager - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,3,0,0,0,100,0,8000,8500,22000,25000,11,17963,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cho'war the Pillager - In Combat - Cast 'Sundering Cleave'");

-- Clefthoof SAI
SET @ENTRY := 18205;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,18000,11,32023,0,0,0,0,0,1,0,0,0,0,0,0,0,"Clefthoof - In Combat - Cast 'Hoof Stomp'");

-- Clefthoof Bull SAI
SET @ENTRY := 17132;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,18000,11,32023,0,0,0,0,0,1,0,0,0,0,0,0,0,"Clefthoof Bull - In Combat - Cast 'Hoof Stomp'");

-- Clefthoof Calf SAI
SET @ENTRY := 19183;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,15000,18000,11,32023,0,0,0,0,0,1,0,0,0,0,0,0,0,"Clefthoof Calf - In Combat - Cast 'Hoof Stomp'");

-- Crashing Wave-Spirit SAI
SET @ENTRY := 22309;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,34425,64,0,0,0,0,2,0,0,0,0,0,0,0,"Crashing Wave-Spirit - In Combat - Cast 'Water Bolt'");

-- Dark Worg SAI
SET @ENTRY := 18033;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,15000,16000,11,30639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Worg - In Combat - Cast 'Carnivorous Bite'");

-- Dust Howler SAI
SET @ENTRY := 17158;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,18000,20000,11,32017,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dust Howler - In Combat - Cast 'Howling Dust'");

-- Elder Ungriz SAI
SET @ENTRY := 18415;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Ungriz - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,11431,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Ungriz - Between 0-30% Health - Cast 'Healing Touch' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,8000,8000,14000,14500,11,13281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Ungriz - In Combat - Cast 'Earth Shock'");

-- Elder Yorley SAI
SET @ENTRY := 18414;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Yorley - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,11431,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Yorley - Between 0-30% Health - Cast 'Healing Touch' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,8000,8000,14000,14500,11,13281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Yorley - In Combat - Cast 'Earth Shock'");

-- Felguard Legionnaire SAI
SET @ENTRY := 17152;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,15000,19000,11,32009,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felguard Legionnaire - In Combat - Cast 'Cutdown'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,10000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felguard Legionnaire - Within 0-5 Range - Cast 'Cleave'");

-- Gan'arg Tinkerer SAI
SET @ENTRY := 17151;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,32003,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gan'arg Tinkerer - In Combat - Cast 'Power Burn'");

-- Garadar Defender SAI
SET @ENTRY := 18489;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Garadar Defender - In Combat - Cast 'Shoot'");

-- Garadar Guard Captain SAI
SET @ENTRY := 19158;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Garadar Guard Captain - In Combat - Cast 'Shoot'");

-- Garadar Wolf Rider SAI
SET @ENTRY := 19068;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,37770,64,0,0,0,0,2,0,0,0,0,0,0,0,"Garadar Wolf Rider - In Combat - Cast 'Shoot'");

-- Gava'xi SAI
SET @ENTRY := 18298;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,14873,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gava'xi - In Combat - Cast 'Sinister Strike'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,18000,20000,11,15691,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gava'xi - In Combat - Cast 'Eviscerate'"),
(@ENTRY,0,2,0,0,0,100,0,10000,11000,25000,28000,11,12540,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gava'xi - In Combat - Cast 'Gouge'");

-- Giselda the Crone SAI
SET @ENTRY := 18391;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,15000,18000,11,32000,0,0,0,0,0,2,0,0,0,0,0,0,0,"Giselda the Crone - In Combat - Cast 'Mind Sear'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,16592,0,0,0,0,0,1,0,0,0,0,0,0,0,"Giselda the Crone - On Aggro - Cast 'Shadowform' (No Repeat)");

-- Goretooth SAI
SET @ENTRY := 17144;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,20000,20000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Goretooth - In Combat - Cast 'Tendon Rip'"),
(@ENTRY,0,1,0,0,0,100,0,6000,6000,17000,18000,11,39215,0,0,0,0,0,2,0,0,0,0,0,0,0,"Goretooth - In Combat - Cast 'Gushing Wound'"),
(@ENTRY,0,2,0,2,0,100,0,0,40,14000,21000,11,38887,0,0,0,0,0,2,0,0,0,0,0,0,0,"Goretooth - Between 0-40% Health - Cast 'Blood Leech'");

-- Gutripper SAI
SET @ENTRY := 18257;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,20000,25000,11,32022,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gutripper - Within 0-5 Range - Cast 'Gut Rip'");

-- Hemet Nesingwary SAI
SET @ENTRY := 18180;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32190,64,0,0,0,0,2,0,0,0,0,0,0,0,"Hemet Nesingwary - In Combat - Cast 'Shoot'");

-- Kil'sorrow Cultist SAI
SET @ENTRY := 17147;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,15000,18000,11,32000,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kil'sorrow Cultist - In Combat - Cast 'Mind Sear'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,16592,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kil'sorrow Cultist - On Aggro - Cast 'Shadowform' (No Repeat)");

-- Kil'sorrow Ritualist SAI
SET @ENTRY := 18658;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kil'sorrow Ritualist - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,6000,7000,18000,20000,11,32063,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kil'sorrow Ritualist - In Combat - Cast 'Corruption'");

-- Lake Spirit SAI
SET @ENTRY := 17153;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,34425,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lake Spirit - In Combat - Cast 'Water Bolt'");

-- Lake Surger SAI
SET @ENTRY := 17155;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32012,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lake Surger - On Aggro - Cast 'Surge' (No Repeat)");

-- Mo'arg Engineer SAI
SET @ENTRY := 16945;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,8,40,18000,25000,11,31705,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Engineer - Within 8-40 Range - Cast 'Magnetic Pull'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,11000,11,32005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Engineer - Within 0-5 Range - Cast 'Thorium Drill'"),
(@ENTRY,0,2,0,0,0,100,0,7000,8000,15000,20000,11,15976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Engineer - In Combat - Cast 'Puncture'");

-- Mo'arg Master Planner SAI
SET @ENTRY := 18567;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,8,40,18000,25000,11,31705,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Master Planner - Within 8-40 Range - Cast 'Magnetic Pull'");

-- Muck Spawn SAI
SET @ENTRY := 17154;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,21067,64,0,0,0,0,2,0,0,0,0,0,0,0,"Muck Spawn - In Combat - Cast 'Poison Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,15000,20000,11,32013,0,0,0,0,0,2,0,0,0,0,0,0,0,"Muck Spawn - In Combat - Cast 'Mucky Sludge'");

-- Murkblood Brute SAI
SET @ENTRY := 18211;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,13000,11,32104,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Brute - In Combat - Cast 'Backhand'");

-- Murkblood Invader SAI
SET @ENTRY := 18238;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,15000,17000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Invader - In Combat - Cast 'Sunder Armor'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Invader - Within 0-5 Range - Cast 'Cleave'");

-- Murkblood Putrifier SAI
SET @ENTRY := 18202;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,20,15500,17500,11,32133,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Putrifier - Within 0-20 Range - Cast 'Corrupted Earth'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,18000,20000,11,32132,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Putrifier - In Combat - Cast 'Tainted Chain Lightning'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,25000,30000,11,32717,0,0,0,0,0,4,0,0,0,0,0,0,0,"Murkblood Putrifier - In Combat - Cast 'Hurricane'");

-- Murkblood Raider SAI
SET @ENTRY := 18203;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,15000,17000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Raider - In Combat - Cast 'Sunder Armor'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,8000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murkblood Raider - Within 0-5 Range - Cast 'Cleave'");

-- Ortor of Murkblood SAI
SET @ENTRY := 18204;
SET @ENTRYTOTEM := 18176;
SET @TOTEMSPELL := 31983;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
UPDATE `creature_template` SET `AIName`='' WHERE `entry`=@ENTRYTOTEM;
UPDATE `creature_template` SET `spell1`=@TOTEMSPELL WHERE `entry`=@ENTRYTOTEM;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,19000,22000,11,32137,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ortor of Murkblood - In Combat - Cast 'Corrupted Air Totem'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,31000,33000,11,31981,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ortor of Murkblood - In Combat - Cast 'Tainted Earthgrab Totem'"),
(@ENTRY,0,2,0,9,0,100,0,0,30,9000,11000,11,32132,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ortor of Murkblood - Within 0-30 Range - Cast 'Tainted Chain Lightning'"),
(@ENTRY,0,3,0,2,0,100,1,0,50,0,0,11,32135,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ortor of Murkblood - Between 0-50% Health - Cast 'Corrupted Healing Stream Totem' (No Repeat)");

-- Ravenous Windroc SAI
SET @ENTRY := 18220;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,18000,22000,11,30285,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravenous Windroc - Within 0-5 Range - Cast 'Eagle Claw'");

-- Rumbling Earth-Heart SAI
SET @ENTRY := 22313;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rumbling Earth-Heart - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rumbling Earth-Heart - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,16000,19000,11,33840,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rumbling Earth-Heart - Within 0-5 Range - Cast 'Earth Rumble'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Saurfang the Younger SAI
SET @ENTRY := 18229;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,15749,0,0,0,0,0,2,0,0,0,0,0,0,0,"Saurfang the Younger - On Aggro - Cast 'Shield Charge' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,4500,12000,13000,11,16044,0,0,0,0,0,2,0,0,0,0,0,0,0,"Saurfang the Younger - In Combat - Cast 'Cleave'"),
(@ENTRY,0,2,0,0,0,100,0,6000,6500,16000,17000,11,24573,0,0,0,0,0,2,0,0,0,0,0,0,0,"Saurfang the Younger - In Combat - Cast 'Mortal Strike'"),
(@ENTRY,0,3,0,2,0,100,1,0,30,0,0,11,14100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Saurfang the Younger - Between 0-30% Health - Cast 'Terrifying Roar' (No Repeat)"),
(@ENTRY,0,4,0,2,0,100,0,0,50,18000,21000,11,41097,0,0,0,0,0,1,0,0,0,0,0,0,0,"Saurfang the Younger - Between 0-50% Health - Cast 'Whirlwind'");

-- Shado 'Fitz' Farstrider SAI
SET @ENTRY := 18200;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,32190,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shado 'Fitz' Farstrider - In Combat - Cast 'Shoot'");

-- Storm Rager SAI
SET @ENTRY := 17159;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4500,12000,13000,11,32018,0,0,0,0,0,2,0,0,0,0,0,0,0,"Storm Rager - In Combat - Cast 'Call Lightning'");

-- Storming Wind-Ripper SAI
SET @ENTRY := 22310;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20295,64,0,0,0,0,2,0,0,0,0,0,0,0,"Storming Wind-Ripper - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Storming Wind-Ripper - Out of Combat - Cast 'Lightning Shield'"),
(@ENTRY,0,2,0,16,0,100,0,12550,1,15000,30000,11,12550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Storming Wind-Ripper - On Friendly Unit Missing Buff 'Lightning Shield' - Cast 'Lightning Shield'");

-- Talbuk Stag SAI
SET @ENTRY := 17130;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15500,16000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Talbuk Stag - Within 0-5 Range - Cast 'Gore'");

-- Talbuk Thorngrazer SAI
SET @ENTRY := 17131;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15500,16000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Talbuk Thorngrazer - Within 0-5 Range - Cast 'Gore'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,19000,22000,11,32020,0,0,0,0,0,2,0,0,0,0,0,0,0,"Talbuk Thorngrazer - In Combat - Cast 'Talbuk Strike'");

-- Terrorguard SAI
SET @ENTRY := 18661;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15000,18000,11,11876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Terrorguard - Within 0-5 Range - Cast 'War Stomp'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5500,17000,18500,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Terrorguard - In Combat - Cast 'Cripple'");

-- Tusker SAI
SET @ENTRY := 18290;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,18000,18000,11,15550,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tusker - Within 0-10 Range - Cast 'Trample'"),
(@ENTRY,0,1,0,0,0,100,0,4000,5500,15500,16000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tusker - In Combat - Cast 'Gore'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,22000,26000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tusker - In Combat - Cast 'Stomp'");

-- Warmaul Brute SAI
SET @ENTRY := 18065;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmaul Brute - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,12000,15000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warmaul Brute - In Combat - Cast 'Uppercut'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Warmaul Chef Bufferlo SAI
SET @ENTRY := 18440;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmaul Chef Bufferlo - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,31994,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warmaul Chef Bufferlo - On Aggro - Cast 'Shoulder Charge' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,2000,4500,12000,15000,11,32376,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warmaul Chef Bufferlo - In Combat - Cast 'Tenderize'"),
(@ENTRY,0,3,0,0,0,100,0,7000,9000,23000,35000,11,32378,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warmaul Chef Bufferlo - In Combat - Cast 'Filet'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');

-- Warmaul Reaver SAI
SET @ENTRY := 17138;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,10000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warmaul Reaver - Within 0-5 Range - Cast 'Cleave'");

-- Wild Elekk SAI
SET @ENTRY := 18334;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,15500,16000,11,32019,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wild Elekk - Within 0-5 Range - Cast 'Gore'");

-- Windroc SAI
SET @ENTRY := 17128;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,16000,17000,11,30285,0,0,0,0,0,2,0,0,0,0,0,0,0,"Windroc - Within 0-5 Range - Cast 'Eagle Claw'");

-- Windyreed Scavenger SAI
SET @ENTRY := 17139;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Windyreed Scavenger - In Combat - Cast 'Throw'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Windyreed Scavenger - Within 0-20 Range - Cast 'Net'");

-- Windyreed Wretch SAI
SET @ENTRY := 17141;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,15000,17000,11,6278,0,0,0,0,0,2,0,0,0,0,0,0,0,"Windyreed Wretch - In Combat - Cast 'Creeping Mold'"),
(@ENTRY,0,1,0,0,0,100,0,7000,8000,12000,13000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Windyreed Wretch - In Combat - Cast 'Disease Touch'");

-- Zorbo the Advisor SAI
SET @ENTRY := 18413;
SET @ENTRYTOTEM := 9637;
SET @TOTEMSPELL := 15037;
UPDATE `creature_template` SET `AIName`='' WHERE `entry`=@ENTRYTOTEM;
UPDATE `creature_template` SET `spell1`=@TOTEMSPELL WHERE `entry`=@ENTRYTOTEM;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zorbo the Advisor - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,11000,16000,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zorbo the Advisor - In Combat - Cast 'Frost Shock'"),
(@ENTRY,0,2,0,2,0,100,0,0,30,22000,25000,11,11986,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zorbo the Advisor - Between 0-30% Health - Cast 'Healing Wave'"),
(@ENTRY,0,3,0,0,0,100,0,5000,5000,30000,35000,11,15038,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zorbo the Advisor - In Combat - Cast 'Scorching Totem'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I\'ll crush you!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,1, 'Me smash! You die!',12,0,50,0,0,0, 'on Aggro Text'),
(@ENTRY,0,2, 'Raaar!!! Me smash $r!',12,0,50,0,0,0, 'on Aggro Text');
