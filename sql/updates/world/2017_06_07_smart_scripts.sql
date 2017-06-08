-- Roanauk Icemist SAI
SET @ENTRY := 26654;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,11,0,100,0,0,0,0,0,45,1,1,0,0,0,0,11,26656,10,0,0,0,0,0,"Roanauk Icemist - On Respawn - Set Data 1 1"),
(@ENTRY,0,1,2,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Respawn - Set Event Phase 1"),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,11,47273,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Respawn - Cast 'Icemist's Prison'"),
(@ENTRY,0,3,8,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Respawn - Set Reactstate Passive"),
(@ENTRY,0,4,0,1,1,100,0,5000,30000,120000,150000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - Out of Combat - Say Line 0 (Phase 1)"),
(@ENTRY,0,5,9,38,0,100,1,1,1,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Data Set 1 1 - Run Script (No Repeat)"),
(@ENTRY,0,6,0,40,0,100,0,1,0,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Waypoint 1 Reached - Run Script"),
(@ENTRY,0,7,0,38,0,100,0,2,2,0,0,80,@ENTRY*100+02,2,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Data Set 2 2 - Run Script"),
(@ENTRY,0,8,0,61,0,100,0,0,0,0,0,18,512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Respawn - Set Flag Immune To NPC's"),
(@ENTRY,0,9,0,61,0,100,0,1,1,0,0,19,512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Roanauk Icemist - On Data Set 1 1 - Remove Flag Immune To NPC's");

-- Aspatha the Broodmother SAI
SET @ENTRY := 25498;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,12000,18000,11,45610,0,0,0,0,0,1,0,0,0,0,0,0,0,"Aspatha the Broodmother - In Combat - Cast 'Pollen'"),
(@ENTRY,0,1,0,0,0,100,0,7000,12000,9000,14000,11,32914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aspatha the Broodmother - In Combat - Cast 'Wing Buffet'");

-- Coldarra Scalesworn SAI
SET @ENTRY := 25717;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11200,12400,11,25717,0,0,0,0,0,2,0,0,0,0,0,0,0,"Coldarra Scalesworn - In Combat - Cast 'Spell Penetration'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,15800,18300,11,12748,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coldarra Scalesworn - Within 0-8 Range - Cast 'Frost Nova'");

-- Claximus SAI
SET @ENTRY := 25209;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,5000,9000,12000,11,50273,0,0,0,0,0,2,0,0,0,0,0,0,0,"Claximus - In Combat - Cast 'Arcane Barrage'"),
(@ENTRY,0,1,0,9,0,100,1,0,8,14500,19800,11,50275,0,0,0,0,0,1,0,0,0,0,0,0,0,"Claximus - Within 0-8 Range - Cast 'Stabilized Magic' (No Repeat)");

-- Clam Master K SAI
SET @ENTRY := 25800;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,54431,64,0,0,0,0,2,0,0,0,0,0,0,0,"Clam Master K - In Combat - Cast 'Throw Spear'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,12300,13500,11,49711,0,0,0,0,0,2,0,0,0,0,0,0,0,"Clam Master K - Within 0-8 Range - Cast 'Hooked Net'");

-- Bloodspore Harvester SAI
SET @ENTRY := 25467;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,25,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Harvester - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,1,0,100,0,500,1000,600000,600000,11,45987,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Harvester - Out of Combat - Cast 'Bloodspore Malaise'"),
(@ENTRY,0,2,0,0,0,100,0,5000,9000,12000,15000,11,50380,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodspore Harvester - In Combat - Cast 'Bloodspore Haze'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'Protect the lifegiver!',14,0,100,0,0,0, 'yell');

-- Bloodspore Firestarter SAI
SET @ENTRY := 25470;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodspore Firestarter - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Firestarter - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,8000,8000,120000,120000,11,45985,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodspore Firestarter - In Combat - Cast 'Flaming Touch'"),
(@ENTRY,0,3,0,1,0,100,0,500,1000,600000,600000,11,35916,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Firestarter - Out of Combat - Cast 'Molten Armor'"),
(@ENTRY,0,4,0,4,0,25,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Firestarter - On Aggro - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'Protect the lifegiver!',14,0,100,0,0,0, 'yell');

-- Bane SAI
SET @ENTRY := 25655;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,50,0,0,11,50332,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bane - Between 0-50% Health - Cast 'Fool's Bane' (No Repeat)");

-- Beryl Sorcerer SAI
SET @ENTRY := 25316;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Beryl Sorcerer - In Combat - Cast 'Frostbolt'"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,11,50648,0,0,0,0,0,1,0,0,0,0,0,0,0,"Beryl Sorcerer - Between 0-50% Health - Cast 'Blink' (No Repeat)");

-- Bloodspore Moth SAI
SET @ENTRY := 25464;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,9000,12000,18000,11,45610,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Moth - In Combat - Cast 'Pollen'"),
(@ENTRY,0,1,0,0,0,100,0,7000,12000,9000,14000,11,32914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodspore Moth - In Combat - Cast 'Wing Buffet'");

-- Bloodspore Roaster SAI
SET @ENTRY := 25468;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,25,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodspore Roaster - On Aggro - Say Line 0 (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,17000,19000,11,50402,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodspore Roaster - In Combat - Cast 'Roast'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'Protect the lifegiver!',14,0,100,0,0,0, 'yell');

-- Boiling Spirit SAI
SET @ENTRY := 25419;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,16800,18900,11,50206,0,0,0,0,0,2,0,0,0,0,0,0,0,"Boiling Spirit - In Combat - Cast 'Scalding Steam'");

-- Chieftain Gurgleboggle SAI
SET @ENTRY := 25725;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,13000,11,50533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chieftain Gurgleboggle - In Combat - Cast 'Flip Attack'");

-- Enraged Tempest SAI
SET @ENTRY := 25415;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,50420,0,0,0,0,0,1,0,0,0,0,0,0,0,"Enraged Tempest - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Enraged Tempest - Between 0-30% Health - Say Line 0 (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,0,5000,6000,19000,21000,11,50215,0,0,0,0,0,2,0,0,0,0,0,0,0,"Enraged Tempest - In Combat - Cast 'Zephyr'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, '%s becomes enraged!',16,0,100,0,0,0, 'combat Enrage');

-- En'kilah Necrolord SAI
SET @ENTRY := 25609;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,50324,0,0,0,0,0,1,0,0,0,0,0,0,0,"En'kilah Necrolord - On Aggro - Cast 'Bone Armor' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3400,4500,11300,14500,11,50323,0,0,0,0,0,2,0,0,0,0,0,0,0,"En'kilah Necrolord - In Combat - Cast 'Sharpened Bone'");

-- En'kilah Gargoyle SAI
SET @ENTRY := 25387;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,12000,12000,11,16564,0,0,0,0,0,2,0,0,0,0,0,0,0,"En'kilah Gargoyle - In Combat - Cast 'Gargoyle Strike'");

-- Den Vermin SAI
SET @ENTRY := 24567;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,7000,12000,11,3391,0,0,0,0,0,1,0,0,0,0,0,0,0,"Den Vermin - In Combat - Cast 'Thrash'");

-- Darkfallen Deathblade SAI
SET @ENTRY := 26103;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,17000,22000,11,50668,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Deathblade - In Combat - Cast 'Death Coil'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,11000,11500,11,50349,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Deathblade - In Combat - Cast 'Icy Touch'");

-- En'kilah Crypt Fiend SAI
SET @ENTRY := 25386;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,16000,21000,11,31600,0,0,0,0,0,2,0,0,0,0,0,0,0,"En'kilah Crypt Fiend - In Combat - Cast 'Crypt Scarabs'");

-- En'kilah Ghoul SAI
SET @ENTRY := 25393;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,17000,21000,11,38056,0,0,0,0,0,2,0,0,0,0,0,0,0,"En'kilah Ghoul - In Combat - Cast 'Flesh Rip'");

-- Festering Ghoul SAI
SET @ENTRY := 25660;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,15000,19000,11,50361,0,0,0,0,0,2,0,0,0,0,0,0,0,"Festering Ghoul - In Combat - Cast 'Rot Armor'");

-- Crypt Crawler SAI
SET @ENTRY := 25227;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,16000,21000,11,31600,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crypt Crawler - In Combat - Cast 'Crypt Scarabs'");

-- Fumblub Gearwind SAI
SET @ENTRY := 32358;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,49987,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fumblub Gearwind - In Combat - Cast 'Shoot'"),
(@ENTRY,0,1,0,0,0,100,0,5000,7000,15800,19500,11,49981,0,0,0,0,0,2,1,0,0,0,0,0,0,"Fumblub Gearwind - In Combat - Cast 'Machine Gun'");

-- Gamel the Cruel SAI
SET @ENTRY := 26449;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,14000,17000,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gamel the Cruel - In Combat - Cast 'Mortal Strike'");

-- Gammothra the Tormentor SAI
SET @ENTRY := 25789;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,46012,0,0,0,36,25790,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gammothra the Tormentor - On Spellhit 'Bloodspore Poison' - Update Template To 'Weakened Gammothra'"),
(@ENTRY,0,1,0,0,0,100,0,8000,12000,9000,15000,11,50410,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gammothra the Tormentor - In Combat - Cast 'Tusk Strike'"),
(@ENTRY,0,2,0,0,0,100,0,1000,3000,18000,26000,11,50413,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gammothra the Tormentor - In Combat - Cast 'Magnataur Charge'");

-- Leviroth SAI
SET @ENTRY := 26452;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6500,12000,13500,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Leviroth - In Combat - Cast 'Mortal Strike'");

-- Landing Crawler SAI
SET @ENTRY := 25481;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,11000,13000,11,49978,0,0,0,0,0,2,0,0,0,0,0,0,0,"Landing Crawler - In Combat - Cast 'Claw Grasp'");

-- Kvaldir Mistweaver SAI
SET @ENTRY := 25479;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7700,9900,17800,24300,11,49816,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kvaldir Mistweaver - In Combat - Cast 'Mist of Strangulation'");

-- Kaganishu SAI
SET @ENTRY := 25427;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,19816,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kaganishu - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,9,0,100,0,0,8,14500,16800,11,15744,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kaganishu - Within 0-8 Range - Cast 'Blast Wave'"),
(@ENTRY,0,2,0,0,0,100,0,9000,15000,15000,21000,11,44257,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kaganishu - In Combat - Cast 'Fire Nova Totem'");

-- Justicar Julia Celeste SAI
SET @ENTRY := 25264;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,11500,16700,11,13005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Justicar Julia Celeste - In Combat - Cast 'Hammer of Justice'"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,11,29427,0,0,0,0,0,1,0,0,0,0,0,0,0,"Justicar Julia Celeste - Between 0-50% Health - Cast 'Holy Light' (No Repeat)");

-- Gorloc Waddler SAI
SET @ENTRY := 25685;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,15800,18300,11,50522,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorloc Waddler - Within 0-8 Range - Cast 'Gorloc Stomp'");

-- Gorloc Steam Belcher SAI
SET @ENTRY := 25687;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,6000,11000,16000,11,50538,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorloc Steam Belcher - In Combat - Cast 'Belch Blast'");

-- Gorloc Mud Splasher SAI
SET @ENTRY := 25699;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,15800,18300,11,50522,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorloc Mud Splasher - Within 0-8 Range - Cast 'Gorloc Stomp'");

-- Gorloc Gibberer SAI
SET @ENTRY := 25686;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,12000,13000,11,50520,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorloc Gibberer - Within 0-8 Range - Cast 'Deep Dredge'");

-- Gorloc Dredger SAI
SET @ENTRY := 25701;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,8,12000,13000,11,50520,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorloc Dredger - Within 0-8 Range - Cast 'Deep Dredge'");

-- Glacial Ancient SAI
SET @ENTRY := 25709;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17000,20500,11,50505,0,0,0,0,0,2,0,0,0,0,0,0,0,"Glacial Ancient - In Combat - Cast 'Frost Breath'");

-- Ghostly Sage SAI
SET @ENTRY := 25351;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Sage - In Combat - Cast 'Wrath'"),
(@ENTRY,0,1,0,0,0,100,0,8900,9700,14500,19900,11,15798,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Sage - In Combat - Cast 'Moonfire'");

-- Gerald Green SAI
SET @ENTRY := 26083;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5500,11400,13400,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gerald Green - In Combat - Cast 'Cleave'");

-- Harvest Collector SAI
SET @ENTRY := 25623;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,47166,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Harvest Collector - On Spellhit 'Converting Harvest Collector' - Despawn In 1000 ms"),
(@ENTRY,0,1,0,0,0,100,0,3000,3500,14500,16700,11,54185,0,0,0,0,0,2,0,0,0,0,0,0,0,"Harvest Collector - In Combat - Cast 'Claw Slash'");

-- Heigarr the Horrible SAI
SET @ENTRY := 26266;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,13000,13000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Heigarr the Horrible - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,18000,22000,11,32588,0,0,0,0,0,2,0,0,0,0,0,0,0,"Heigarr the Horrible - In Combat - Cast 'Concussion Blow'");

-- Ith'rix the Harvester SAI
SET @ENTRY := 25453;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,4000,11000,13000,11,25748,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ith'rix the Harvester - In Combat - Cast 'Poison Stinger'"),
(@ENTRY,0,1,0,0,0,100,0,7000,7000,16000,19000,11,45592,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ith'rix the Harvester - In Combat - Cast 'Venom Spit'"),
(@ENTRY,0,2,0,2,0,100,1,0,50,0,0,11,34392,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ith'rix the Harvester - Between 0-50% Health - Cast 'Stinger Rage' (No Repeat)");

-- Nerub'ar Sky Darkener SAI
SET @ENTRY := 25451;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5500,12000,17300,11,45577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nerub'ar Sky Darkener - In Combat - Cast 'Venom Spit'"),
(@ENTRY,0,1,0,0,0,100,0,9900,9900,19900,21300,11,45587,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nerub'ar Sky Darkener - In Combat - Cast 'Web Bolt'");

-- Nerub'ar Warrior SAI
SET @ENTRY := 25619;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,1,0,0,0,0,11,50347,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nerub'ar Warrior - On Aggro - Cast 'Rush' (No Repeat)"),
(@ENTRY,0,1,0,9,0,100,0,8,25,15800,17600,11,50347,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nerub'ar Warrior - Within 8-25 Range - Cast 'Rush'");

-- Nerub'ar Web Lord SAI
SET @ENTRY := 25294;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17800,22400,11,50284,0,0,0,0,0,2,1,0,0,0,0,0,0,"Nerub'ar Web Lord - In Combat - Cast 'Blinding Swarm'");

-- Nerub'ar Tunneler SAI
SET @ENTRY := 25622;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,30,0,0,11,50364,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nerub'ar Tunneler - Between 0-30% Health - Cast 'Rock Shield' (No Repeat)");

-- Nerub'ar Corpse Harvester SAI
SET @ENTRY := 25445;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5500,6500,12400,15600,11,6917,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nerub'ar Corpse Harvester - In Combat - Cast 'Venom Spit'");

-- Magmoth Crusher SAI
SET @ENTRY := 25434;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,33,25505,0,0,0,0,0,7,0,0,0,0,0,0,0,"Magmoth Crusher - On Just Died - Quest Credit 'Hah... You're Not So Big Now!' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,9000,9000,15900,21400,11,50410,0,0,0,0,0,2,0,0,0,0,0,0,0,"Magmoth Crusher - In Combat - Cast 'Tusk Strike'"),
(@ENTRY,0,2,0,4,0,100,1,0,0,0,0,11,50413,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magmoth Crusher - On Aggro - Cast 'Magnataur Charge' (No Repeat)");

-- Scalesworn Elite SAI
SET @ENTRY := 32534;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,8000,17000,19000,11,61272,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scalesworn Elite - In Combat - Cast 'Arcane Surge'"),
(@ENTRY,0,1,0,0,0,100,0,3000,5000,11000,12000,11,61269,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scalesworn Elite - In Combat - Cast 'Ice Shard'");

-- Scourged Footman SAI
SET @ENTRY := 25981;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,16000,23000,29000,11,33735,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scourged Footman - In Combat - Cast 'Blade Flurry'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,11000,14000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scourged Footman - In Combat - Cast 'Mortal Strike'");

-- Risen Longrunner SAI
SET @ENTRY := 25350;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1500,5700,9600,12900,11,36093,0,0,0,0,0,2,0,0,0,0,0,0,0,"Risen Longrunner - In Combat - Cast 'Ghost Strike'"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,32720,0,0,0,0,0,1,0,0,0,0,0,0,0,"Risen Longrunner - On Aggro - Cast 'Sprint' (No Repeat)");

-- Rockfang SAI
SET @ENTRY := 25774;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,15000,21000,11,32918,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rockfang - In Combat - Cast 'Chilling Howl'");

-- Rocknar SAI
SET @ENTRY := 25514;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,8000,7000,13000,11,50094,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rocknar - In Combat - Cast 'Ice Spike'"),
(@ENTRY,0,1,0,2,0,100,1,0,50,0,0,11,22693,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rocknar - Between 0-50% Health - Cast 'Harden Skin' (No Repeat)");

-- Ragnar Drakkarlund SAI
SET @ENTRY := 26451;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,12500,15900,11,41056,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ragnar Drakkarlund - Within 0-5 Range - Cast 'Whirlwind'");

-- Raging Boiler SAI
SET @ENTRY := 25417;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,0,0,5,7000,12000,11,50207,0,0,0,0,0,5,32,0,0,0,0,0,0,"Raging Boiler - Within 0-5 Range - Cast 'Boiling Blood'");

-- Skadir Raider SAI
SET @ENTRY := 25522;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2300,3900,11,43413,64,0,0,0,0,2,0,0,0,0,0,0,0,"Skadir Raider - In Combat - Cast 'Throw Spear'"),
(@ENTRY,0,1,0,9,0,100,0,0,3,5000,17000,11,43414,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skadir Raider - Within 0-3 Range - Cast 'Freezing Trap'");

-- Skadir Mariner SAI
SET @ENTRY := 25523;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,9000,13000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skadir Mariner - In Combat - Cast 'Uppercut'"),
(@ENTRY,0,1,0,0,0,100,0,2000,5000,18000,24000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skadir Mariner - In Combat - Cast 'Demoralizing Shout'");

-- Skadir Runecaster SAI
SET @ENTRY := 25520;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Skadir Runecaster - In Combat - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,4000,9000,120000,120000,11,49871,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skadir Runecaster - In Combat - Cast 'Rune of Retribution'");

-- Unliving Swine SAI
SET @ENTRY := 25600;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,35700,39800,11,50303,0,0,0,0,0,2,0,0,0,0,0,0,0,"Unliving Swine - In Combat - Cast 'Swine Flu'");

-- Tundra Crawler SAI
SET @ENTRY := 25454;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3500,3900,17800,19200,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tundra Crawler - In Combat - Cast 'Infected Bite'"),
(@ENTRY,0,1,0,0,0,100,0,5000,12000,10000,18000,11,50293,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tundra Crawler - In Combat - Cast 'Corrosive Poison'");

-- Warsong Captain SAI
SET @ENTRY := 25446;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,7000,9000,12000,11,12058,0,0,0,0,0,5,0,0,0,0,0,0,0,"Warsong Captain - In Combat - Cast 'Chain Lightning'"),
(@ENTRY,0,1,0,14,0,100,0,4000,25,14000,17000,11,44256,0,0,0,0,0,7,0,0,0,0,0,0,0,"Warsong Captain - Friendly At 4000 Health - Cast 'Lesser Healing Wave'"),
(@ENTRY,0,2,0,14,0,100,0,3000,25,18000,23000,11,15799,0,0,0,0,0,7,0,0,0,0,0,0,0,"Warsong Captain - Friendly At 3000 Health - Cast 'Chain Heal'"),
(@ENTRY,0,3,0,16,0,100,0,45584,20,9000,16000,11,45584,0,0,0,0,0,7,0,0,0,0,0,0,0,"Warsong Captain - On Friendly Unit Missing Buff 'Bloodlust' - Cast 'Bloodlust'");

-- Ziggurat Defender SAI
SET @ENTRY := 26202;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,12000,14000,11,50306,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ziggurat Defender - In Combat - Cast 'Thrash Kick'");
