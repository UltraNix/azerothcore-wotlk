-- Aeranas SAI
SET @ENTRY := 17085;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,12500,11,12553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aeranas - In Combat - Cast 'Shock'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,18000,22000,11,15535,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aeranas - In Combat - Cast 'Enveloping Winds'");

-- Aggonis SAI
SET @ENTRY := 17000;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,15000,17000,11,21068,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aggonis - In Combat - Cast 'Corruption'"),
(@ENTRY,0,1,0,0,0,100,0,10000,10000,26000,30000,11,22678,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aggonis - In Combat - Cast 'Fear'");

-- Arcanist Torseldori SAI
SET @ENTRY := 19257;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,15530,64,0,0,0,0,2,0,0,0,0,0,0,0,"Arcanist Torseldori - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,13600,14500,11,12674,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arcanist Torseldori - Within 0-10 Range - Cast 'Frost Nova'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,19000,24000,11,33634,0,0,0,0,0,4,0,0,0,0,0,0,0,"Arcanist Torseldori - In Combat - Cast 'Blizzard'"),
(@ENTRY,0,3,0,0,0,100,0,10000,12000,15000,22000,11,22273,0,0,0,0,0,4,0,0,0,0,0,0,0,"Arcanist Torseldori - In Combat - Cast 'Arcane Missiles'");

-- Bat Rider Guard SAI
SET @ENTRY := 15242;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,100,8000,9000,11,38066,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bat Rider Guard - Within 0-100 Range - Cast 'Unstable Concoction'");

-- Bloodmage SAI
SET @ENTRY := 19258;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,15530,64,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodmage - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,9,0,100,0,0,10,13600,14500,11,12674,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodmage - Within 0-10 Range - Cast 'Frost Nova'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,19000,24000,11,33634,0,0,0,0,0,4,0,0,0,0,0,0,0,"Bloodmage - In Combat - Cast 'Blizzard'"),
(@ENTRY,0,3,0,0,0,100,0,10000,12000,15000,22000,11,22273,0,0,0,0,0,4,0,0,0,0,0,0,0,"Bloodmage - In Combat - Cast 'Arcane Missiles'");

-- Deathwhisperer SAI
SET @ENTRY := 19299;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,12000,16000,11,32417,0,0,0,0,0,2,0,0,0,0,0,0,0,"Deathwhisperer - In Combat - Cast 'Mind Flay'"),
(@ENTRY,0,1,0,2,0,100,0,0,40,20000,21000,11,17687,0,0,0,0,0,1,0,0,0,0,0,0,0,"Deathwhisperer - Between 0-40% Health - Cast 'Flurry'");

-- Draenei Vindicator SAI
SET @ENTRY := 16996;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,25000,28000,11,13005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Draenei Vindicator - In Combat - Cast 'Hammer of Justice'"),
(@ENTRY,0,1,0,0,0,100,0,2000,3000,30000,32000,11,33127,0,0,0,0,0,1,0,0,0,0,0,0,0,"Draenei Vindicator - In Combat - Cast 'Seal of Command'"),
(@ENTRY,0,2,0,2,0,100,1,0,10,0,0,11,13874,0,0,0,0,0,1,0,0,0,0,0,0,0,"Draenei Vindicator - Between 0-10% Health - Cast 'Divine Shield' (No Repeat)");

-- Dread Tactician SAI
SET @ENTRY := 16959;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,15000,20000,11,33678,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dread Tactician - In Combat - Cast 'Carrion Swarm'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,26000,30000,11,12098,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dread Tactician - In Combat - Cast 'Sleep'"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,11,33679,0,0,0,0,0,4,0,0,0,0,0,0,0,"Dread Tactician - Between 0-30% Health - Cast 'Inferno' (No Repeat)");

-- Falcon Watch Ranger SAI
SET @ENTRY := 17282;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Falcon Watch Ranger - In Combat - Cast 'Shoot'");

-- Falcon Watch Sentinel SAI
SET @ENTRY := 16579;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,22121,64,0,0,0,0,2,0,0,0,0,0,0,0,"Falcon Watch Sentinel - In Combat - Cast 'Shoot'");

-- Far Seer Regulkut SAI
SET @ENTRY := 16574;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,15234,64,0,0,0,0,2,0,0,0,0,0,0,0,"Far Seer Regulkut - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,18000,22000,11,16006,0,0,0,0,0,4,0,0,0,0,0,0,0,"Far Seer Regulkut - In Combat - Cast 'Chain Lightning'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,28000,32000,11,15786,0,0,0,0,0,1,0,0,0,0,0,0,0,"Far Seer Regulkut - In Combat - Cast 'Earthbind Totem'");

-- Fel Cannon MKI SAI
SET @ENTRY := 22461;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Cannon MKI - On Aggro - Set Event Phase 1 (No Repeat)"),
(@ENTRY,0,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Cannon MKI - On Aggro - Disable Combat Movement (Phase 1) (No Repeat)"),
(@ENTRY,0,2,0,4,1,100,1,0,0,0,0,11,36238,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Cannon MKI - On Aggro - Cast 'Fel Cannon Blast' (Phase 1) (No Repeat)"),
(@ENTRY,0,3,0,9,1,100,0,0,40,2500,3000,11,36238,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Cannon MKI - Within 0-40 Range - Cast 'Fel Cannon Blast' (Phase 1)");

-- Fel Reaver SAI
SET @ENTRY := 18733;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,15,18000,25000,11,41534,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Reaver - Within 0-15 Range - Cast 'War Stomp'");

-- Felguard Destroyer SAI
SET @ENTRY := 18977;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,33971,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felguard Destroyer - On Aggro - Cast 'Sweeping Charge' (No Repeat)");

-- Gan'arg Sapper SAI
SET @ENTRY := 18827;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,33974,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gan'arg Sapper - In Combat - Cast 'Power Burn'"),
(@ENTRY,0,1,0,6,0,100,1,0,0,0,0,11,33895,3,0,0,0,0,1,0,0,0,0,0,0,0,"Gan'arg Sapper - On Just Died - Cast 'Set Charge' (No Repeat)");

-- Gan'arg Servant SAI
SET @ENTRY := 16947;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,32003,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gan'arg Servant - In Combat - Cast 'Power Burn'");

-- Glacial Templar SAI
SET @ENTRY := 26216;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,13600,14500,11,14907,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glacial Templar - Within 0-8 Range - Cast 'Frost Nova'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,8000,12000,11,15089,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glacial Templar - Within 0-20 Range - Cast 'Frost Shock'"),
(@ENTRY,0,2,0,0,0,100,0,8000,9000,18000,22000,11,5164,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glacial Templar - In Combat - Cast 'Knockdown'");

-- Gryphon Rider Guard SAI
SET @ENTRY := 15241;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,100,8000,9000,11,38182,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gryphon Rider Guard - Within 0-100 Range - Cast 'Stormhammer'");

-- Haal'eshi Talonguard SAI
SET @ENTRY := 16967;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,32720,0,0,0,0,0,1,0,0,0,0,0,0,0,"Haal'eshi Talonguard - On Aggro - Cast 'Sprint' (No Repeat)");

-- Haal'eshi Windwalker SAI
SET @ENTRY := 16966;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Haal'eshi Windwalker - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,2,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Haal'eshi Windwalker - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Haal'eshi Windwalker - Between 0-15% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,0,8000,9000,22000,26000,11,32717,0,0,0,0,0,4,0,0,0,0,0,0,0,"Haal'eshi Windwalker - In Combat - Cast 'Hurricane'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s attempts to run away in fear!',16,0,100,0,0,0, 'combat Flee');

-- Honor Hold Defender SAI
SET @ENTRY := 16842;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,1,0,30,0,0,11,18396,0,0,0,0,0,2,0,0,0,0,0,0,0,"Honor Hold Defender - Within 0-30 Range - Cast 'Dismounting Blast' (No Repeat)");

-- Mag'har Escort SAI
SET @ENTRY := 17417;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,9000,12000,11,30460,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mag'har Escort - Within 0-5 Range - Cast 'Kick'");

-- Magister Aledis SAI
SET @ENTRY := 20159;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Magister Aledis - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,13600,14500,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magister Aledis - Within 0-8 Range - Cast 'Frost Nova'"),
(@ENTRY,0,2,0,0,0,100,0,8000,10000,22000,23000,11,33975,0,0,0,0,0,2,0,0,0,0,0,0,0,"Magister Aledis - In Combat - Cast 'Pyroblast'");

-- Maiden of Pain SAI
SET @ENTRY := 19408;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12000,14500,11,15968,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maiden of Pain - Within 0-5 Range - Cast 'Lash of Pain'"),
(@ENTRY,0,1,0,2,0,100,0,0,30,15000,15000,11,34086,0,0,0,0,0,1,0,0,0,0,0,0,0,"Maiden of Pain - Between 0-30% Health - Cast 'Whipped Frenzy'");

-- Megzeg Nukklebust SAI
SET @ENTRY := 21283;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,18000,11,15588,0,0,0,0,0,1,0,0,0,0,0,0,0,"Megzeg Nukklebust - Within 0-10 Range - Cast 'Thunderclap'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,22000,25000,11,13736,0,0,0,0,0,1,0,0,0,0,0,0,0,"Megzeg Nukklebust - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,2,0,9,0,50,0,0,5,8000,9000,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Megzeg Nukklebust - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,3,0,9,0,50,0,0,5,8000,9000,11,16044,0,0,0,0,0,2,0,0,0,0,0,0,0,"Megzeg Nukklebust - Within 0-5 Range - Cast 'Cleave'");

-- Mekthorg the Wild SAI
SET @ENTRY := 18677;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mekthorg the Wild - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mekthorg the Wild - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,9,0,100,0,0,5,22000,25000,11,37704,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mekthorg the Wild - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,3,0,0,0,100,0,4000,4500,12000,16000,11,38875,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mekthorg the Wild - In Combat - Cast 'Pike Vault'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Mo'arg Forgefiend SAI
SET @ENTRY := 16946;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,10,40,8000,12000,11,32735,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Forgefiend - Within 10-40 Range - Cast 'Saw Blade'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,19000,11,36486,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mo'arg Forgefiend - Within 0-5 Range - Cast 'Slime Spray'");

-- Nazgrel SAI
SET @ENTRY := 3230;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,18000,11,15588,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nazgrel - Within 0-10 Range - Cast 'Thunderclap'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,22000,25000,11,13736,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nazgrel - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,2,0,9,0,50,0,0,5,8000,9000,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nazgrel - Within 0-5 Range - Cast 'Mortal Strike'"),
(@ENTRY,0,3,0,9,0,50,0,0,5,8000,9000,11,16044,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nazgrel - Within 0-5 Range - Cast 'Cleave'");

-- Overlord Hun Maimfist SAI
SET @ENTRY := 16576;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,10,15000,18000,11,15588,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overlord Hun Maimfist - Within 0-10 Range - Cast 'Thunderclap'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,22000,25000,11,13736,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overlord Hun Maimfist - Within 0-5 Range - Cast 'Whirlwind'"),
(@ENTRY,0,2,0,9,0,50,0,0,5,8000,9000,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Overlord Hun Maimfist - Within 0-5 Range - Cast 'Mortal Strike'");

-- Shadow Hunter Ty'jin SAI
SET @ENTRY := 16575;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,20000,20000,11,22566,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shadow Hunter Ty'jin - In Combat - Cast 'Hex'"),
(@ENTRY,0,1,0,9,0,100,0,0,20,11000,11500,11,17439,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Hunter Ty'jin - Within 0-20 Range - Cast 'Shadow Shock'"),
(@ENTRY,0,2,0,0,0,100,0,5000,5000,30000,32000,11,15802,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Hunter Ty'jin - In Combat - Cast 'Shrink'");

-- Stonescythe Ambusher SAI
SET @ENTRY := 16928;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,14000,16000,11,31819,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonescythe Ambusher - In Combat - Cast 'Cheap Shot'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,33898,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Ambusher - Between 0-30% Health - Cast 'Desperate Rage' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,11,33896,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Ambusher - Between 0-15% Health - Cast 'Desperate Defense' (No Repeat)"),
(@ENTRY,0,3,0,11,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Ambusher - On Respawn - Cast 'Sneak' (No Repeat)"),
(@ENTRY,0,4,0,7,0,100,1,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Ambusher - On Evade - Cast 'Sneak' (No Repeat)");

-- Stonescythe Whelp SAI
SET @ENTRY := 16927;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,33898,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Whelp - Between 0-30% Health - Cast 'Desperate Rage' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,11,33896,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonescythe Whelp - Between 0-15% Health - Cast 'Desperate Defense' (No Repeat)");

-- Subjugator Shi'aziv SAI
SET @ENTRY := 19282;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,32000,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Shi'aziv - In Combat - Cast 'Mind Sear'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,18000,20000,11,32026,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Shi'aziv - In Combat - Cast 'Pain Spike'");

-- Subjugator Yalqiz SAI
SET @ENTRY := 19335;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,32000,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Yalqiz - In Combat - Cast 'Mind Sear'"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,18000,20000,11,32026,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Yalqiz - In Combat - Cast 'Pain Spike'");

-- Tagar Spinebreaker SAI
SET @ENTRY := 19443;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4500,15000,16000,11,34108,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tagar Spinebreaker - In Combat - Cast 'Spine Break'"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,20000,25000,11,34109,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tagar Spinebreaker - In Combat - Cast 'Whirlwind Knockback'");

-- Telhamat Protector SAI
SET @ENTRY := 18758;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Telhamat Protector - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,1,5000,5000,0,0,11,18396,0,0,0,0,0,2,0,0,0,0,0,0,0,"Telhamat Protector - In Combat - Cast 'Dismounting Blast' (No Repeat)");

-- Thrallmar Marksman SAI
SET @ENTRY := 16582;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,22121,64,0,0,0,0,2,0,0,0,0,0,0,0,"Thrallmar Marksman - In Combat - Cast 'Shoot'");

-- Vorakem Doomspeaker SAI
SET @ENTRY := 18679;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vorakem Doomspeaker - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vorakem Doomspeaker - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,15000,25000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vorakem Doomspeaker - In Combat - Cast 'Hamstring'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- Warboss Nekrogg SAI
SET @ENTRY := 19263;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,16000,11,34113,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warboss Nekrogg - In Combat - Cast 'Bonechewer Bite'"),
(@ENTRY,0,1,0,0,0,100,0,8000,8000,30000,35000,11,33951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warboss Nekrogg - In Combat - Cast 'Bonechewer Rot'");

-- Z'kral SAI
SET @ENTRY := 18974;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,16500,11,32003,0,0,0,0,0,2,0,0,0,0,0,0,0,"Z'kral - In Combat - Cast 'Power Burn'");
