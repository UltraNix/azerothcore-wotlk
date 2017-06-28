-- Bannok Grimaxe SAI
SET @ENTRY := 9596;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,33000,34000,11,15128,0,0,0,0,0,5,0,0,0,0,0,0,0,"Bannok Grimaxe - In Combat - Cast 'Mark of Flames' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,3000,4000,11000,12000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bannok Grimaxe - In Combat - Cast 'Mortal Strike' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,0,8,15800,18300,11,41057,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bannok Grimaxe - Within 0-8 Range - Cast 'Whirlwind' (Normal Dungeon)");

-- Ghok Bashguud SAI
SET @ENTRY := 9718;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,4000,12000,13000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ghok Bashguud - In Combat - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,13,0,100,2,12000,18000,0,0,11,11972,0,0,0,0,0,7,0,0,0,0,0,0,0,"Ghok Bashguud - On Victim Casting - Cast 'Shield Bash' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,30,0,0,11,8269,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghok Bashguud - Between 0-30% Health - Cast 'Frenzy' (No Repeat) (Normal Dungeon)");

-- Gizrul the Slavener SAI
SET @ENTRY := 10268;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,2,0,20,30000,30000,11,8269,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gizrul the Slavener - Between 0-20% Health - Cast 'Frenzy' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,10000,10000,10000,10000,11,16495,0,0,0,0,0,2,1,0,0,0,0,0,0,"Gizrul the Slavener - In Combat - Cast 'Fatal Bite' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,15000,20000,10000,20000,11,16128,0,0,0,0,0,2,32,0,0,0,0,0,0,"Gizrul the Slavener - In Combat - Cast 'Infected Bite' (Normal Dungeon)");

-- Solakar Flamewreath SAI
SET @ENTRY := 10264;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,12000,16000,11,16727,0,0,0,0,0,1,0,0,0,0,0,0,0,"Solakar Flamewreath - Within 0-5 Range - Cast 'War Stomp' (Normal Dungeon)");

-- Blackhand Dragon Handler SAI
SET @ENTRY := 10742;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,14,0,100,2,3000,10,20000,30000,11,16637,0,0,0,0,0,7,0,0,0,0,0,0,0,"Blackhand Dragon Handler - Friendly At 3000 Health - Cast 'Mend Dragon' (Normal Dungeon)");

-- Blackhand Iron Guard SAI
SET @ENTRY := 10319;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,22800,6600,18200,11,15655,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackhand Iron Guard - In Combat - Cast 'Shield Slam' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,50,0,0,11,15062,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackhand Iron Guard - Between 0-50% Health - Cast 'Shield Wall' (No Repeat) (Normal Dungeon)");

-- Firebrand Pyromancer SAI
SET @ENTRY := 9264;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,25000,29000,11,15128,0,0,0,0,0,5,0,0,0,0,0,0,0,"Firebrand Pyromancer - In Combat - Cast 'Mark of Flames' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,4000,4000,8000,12000,11,15096,0,0,0,0,0,2,0,0,0,0,0,0,0,"Firebrand Pyromancer - In Combat - Cast 'Flame Shock' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4000,9000,16000,18000,11,15732,0,0,0,0,0,5,0,0,0,0,0,0,0,"Firebrand Pyromancer - In Combat - Cast 'Immolate' (Normal Dungeon)");

-- Firebrand Dreadweaver SAI
SET @ENTRY := 9263;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,33000,38000,11,15128,0,0,0,0,0,5,0,0,0,0,0,0,0,"Firebrand Dreadweaver - In Combat - Cast 'Mark of Flames' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,1000,4000,12000,15000,11,16071,0,0,0,0,0,5,32,0,0,0,0,0,0,"Firebrand Dreadweaver - In Combat - Cast 'Curse of the Firebrand' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,10000,15000,10000,20000,11,15728,0,0,0,0,0,5,0,0,0,0,0,0,0,"Firebrand Dreadweaver - In Combat - Cast 'Plague Cloud' (Normal Dungeon)"),
(@ENTRY,0,3,0,16,0,100,2,15729,30,15000,22000,11,15729,0,0,0,0,0,7,0,0,0,0,0,0,0,"Firebrand Dreadweaver - On Friendly Unit Missing Buff 'Remove Curse' - Cast 'Remove Curse' (Normal Dungeon)");

-- Scarshield Spellbinder SAI
SET @ENTRY := 9098;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,13748,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarshield Spellbinder - In Combat - Cast 'Arcane Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarshield Spellbinder - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,16,0,100,2,15123,30,3000,6000,11,15123,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarshield Spellbinder - On Friendly Unit Missing Buff 'Resist Fire' - Cast 'Resist Fire' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,8000,8000,12000,15000,11,14033,1,0,0,0,0,5,0,0,0,0,0,0,0,"Scarshield Spellbinder - In Combat - Cast 'Mana Burn' (Normal Dungeon)"),
(@ENTRY,0,4,0,13,0,100,2,12000,18000,0,0,11,15122,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarshield Spellbinder - On Victim Casting - Cast 'Counterspell' (Normal Dungeon)");

-- Smolderthorn Shadow Hunter SAI
SET @ENTRY := 9265;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,67,0,100,2,3900,6900,0,0,11,15582,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smolderthorn Shadow Hunter - On Behind Target - Cast 'Backstab' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,5000,12000,13000,11,12540,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smolderthorn Shadow Hunter - In Combat - Cast 'Gouge' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,7000,11000,10000,17000,11,15614,0,0,0,0,0,2,0,0,0,0,0,0,0,"Smolderthorn Shadow Hunter - In Combat - Cast 'Kick' (Normal Dungeon)");

-- Spectral Assassin SAI
SET @ENTRY := 16066;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,15000,25000,36000,11,27177,0,0,0,0,0,5,0,0,0,0,0,0,0,"Spectral Assassin - In Combat - Cast 'Defile' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,4000,4000,9000,11000,11,18663,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spectral Assassin - In Combat - Cast 'Shadow Shock' (Normal Dungeon)");

-- Smolderthorn Witch Doctor SAI
SET @ENTRY := 9266;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,20000,20000,20000,20000,11,15867,0,0,0,0,0,1,0,0,0,0,0,0,0,"Smolderthorn Witch Doctor - In Combat - Cast 'Flame Buffet Totem' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,12000,10000,15000,11,15869,0,0,0,0,0,1,0,0,0,0,0,0,0,"Smolderthorn Witch Doctor - In Combat - Cast 'Superior Healing Ward' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4000,5000,25000,32000,11,8262,0,0,0,0,0,1,0,0,0,0,0,0,0,"Smolderthorn Witch Doctor - In Combat - Cast 'Elemental Protection Totem' (Normal Dungeon)");

-- Spirestone Enforcer SAI
SET @ENTRY := 9199;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,5000,3000,6000,11,14516,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spirestone Enforcer - In Combat - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,12000,17000,11,15976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spirestone Enforcer - In Combat - Cast 'Puncture' (Normal Dungeon)");
