SET @ENTRY := 12396;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,8000,18000,24000,11,16005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomguard Commander - IC -  spell cast"),
(@ENTRY,0,1,0,0,0,100,0,12000,15000,20000,25000,11,16727,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomguard Commander - IC -  spell cast"),
(@ENTRY,0,2,0,0,0,100,0,2000,4000,25000,32000,11,20812,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomguard Commander - IC -  spell cast"),
(@ENTRY,0,3,0,0,0,100,0,7000,14000,17000,22000,11,15090,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomguard Commander - IC -  spell cast"),
(@ENTRY,0,4,5,8,0,100,0,23019,0,0,0,50,179644,180,1,0,0,0,7,0,0,0,0,0,0,0,"Doomguard Commander - on spell hit - summon GO"),
(@ENTRY,0,5,6,61,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomguard Commander - linked - turn invisible"),
(@ENTRY,0,6,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Doomguard Commander - linked - Die");
