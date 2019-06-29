-- Molten Elemental: melee damage has to be slightly increased, should be also immune to nature school damage.
UPDATE `creature_template` SET `mindmg`=15, `maxdmg`=30, `resistance3`=-1 WHERE `entry`=11321;

-- Remove random movement from Bazzalan and Taragaman
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `id` IN (11519, 11520);

-- Searing Blade Cultist SAI
SET @ENTRY := 11322;
DELETE FROM `smart_ai_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_ai_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,6000,16000,18000,11,18266,32,0,0,0,0,5,0,0,0,0,0,0,0,"Searing Blade Cultist - In Combat - Cast 'Curse of Agony' (Normal Dungeon)");

-- Ragefire Shaman SAI
SET @ENTRY := 11319;
DELETE FROM `smart_ai_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_ai_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3000,4000,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ragefire Shaman - In Combat - Cast 'Lightning Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,14,0,100,2,400,40,18000,22000,11,11986,1,0,0,0,0,7,0,0,0,0,0,0,0,"Ragefire Shaman - Friendly At 400 Health - Cast 'Healing Wave' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ragefire Shaman - Between 0-15% Health - Flee For Assist (No Repeat) (Normal Dungeon)");

-- Taragaman the Hungerer SAI
SET @ENTRY := 11520;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,6000,4000,8000,11,18072,0,0,0,0,0,2,0,0,0,0,0,0,0,"Taragaman the Hungerer - In Combat - Cast 'Uppercut' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,8,9000,12000,11,11970,0,0,0,0,0,2,0,0,0,0,0,0,0,"Taragaman the Hungerer - Within 0-8 Range - Cast 'Fire Nova' (Normal Dungeon)");
