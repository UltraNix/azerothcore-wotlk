-- Spawn of Fankriss SAI
SET @ENTRY := 15630;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,1,20000,20000,0,0,11,26662,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spawn of Fankriss - In Combat - Cast 'Berserk' (No Repeat)");
-- Entangle
DELETE FROM `spell_target_position` WHERE `id` IN (720, 731, 1121);
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(720, 0, 531, -8106.0142, 1289.2900, -74.419533, 5.112),
(731, 0, 531, -7990.135354, 1155.1907, -78.849319, 2.608),
(1121, 0, 531, -8159.7753, 1127.9064, -76.868660, 0.675);
