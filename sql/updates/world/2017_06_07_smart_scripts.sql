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
