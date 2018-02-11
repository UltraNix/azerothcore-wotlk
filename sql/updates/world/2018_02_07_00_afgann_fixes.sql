-- Sunhawk Pyromancer SAI
SET @ENTRY := 17608;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,-1,0,0,0,100,0,0,0,3500,4000,11,9053,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunhawk Pyromancer - In Combat - Cast 'Fireball'"),
(@ENTRY,0,-1,0,0,0,100,0,5000,10000,15000,20000,11,11962,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunhawk Pyromancer - In Combat - Cast 'Immolate'");
-- Void Dance achievement
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=7587;
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(7587,11,0,0,"achievement_void_dance");
-- Drakkari Skullcrusher
DELETE FROM `smart_scripts` WHERE `entryorguid`=28844 AND `source_type`=0;
UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=28844;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_drakkari_skullcrusher" WHERE `entry`=28844;
