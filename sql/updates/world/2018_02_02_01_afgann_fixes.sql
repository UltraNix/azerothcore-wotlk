-- Bonechewer Blood drop rate
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-90 WHERE `item`=30327;

-- Demon Blood drop rate
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-70 WHERE `item`=29113;

-- Amani Berserker SAI
SET @ENTRY := 15643;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,2,0,100,1,0,30,0,0,11,8599,1,0,0,0,0,1,0,0,0,0,0,0,0,"Amani Berserker - Between 0-30% Health - Cast 'Enrage' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,0,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Amani Berserker - Between 0-30% Health - Say Line 0 (No Repeat)");

-- Tormenting the Softknuckles
UPDATE `creature` SET `position_x`=5108.243164, `position_y`=3969.263916, `position_z`=-56.001804, `orientation`=0.692766 WHERE `guid`=100797; -- Hardknuckle Matriarch correction
SET @GUID = 100797;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 5117.972168, 3978.340332, -61.207340, 1),
(@GUID*10, 2, 5135.378906, 3983.859863, -61.911339, 1);
DELETE FROM `smart_scripts` WHERE `entryorguid`=28213 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_hardknuckle_matriarch" WHERE `entry`=28213;
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_scared_softknuckle";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(50979, "spell_scared_softknuckle");

-- Cyanigosa
UPDATE `creature_model_info` SET `bounding_radius`=3.0, `combat_reach`=10.0 WHERE `modelid`=27340;
