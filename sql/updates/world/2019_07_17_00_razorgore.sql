UPDATE `spell_script_names` SET `ScriptName`="spell_razorgore_destroy_egg" WHERE `spell_id`=19873;
-- Adds
DELETE FROM `creature` WHERE `id` IN (12557, 14456);
DELETE FROM `creature_summon_groups` WHERE `summonerId`=12435 AND `groupId`=1;
INSERT INTO `creature_summon_groups` (`summonerId`, `entry`, `groupId`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`) VALUES
(12435, 12557, 1, -7615.981, -1024.859, 413.56, 5.28, 8),
(12435, 14456, 1, -7618.984, -1026.357, 413.56, 3.73, 8),
(12435, 14456, 1, -7613.647, -1022.539, 413.56, 0.60, 8);
DELETE FROM `smart_scripts` WHERE `entryorguid`=12557 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_grethok_the_controller" WHERE `entry`=12557;
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_razorgore_possess";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(19832, "spell_razorgore_possess");
SET @ENTRY := 14456;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,12000,14000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Guardsman - In Combat - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,19000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Guardsman - In Combat - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,2,0,4,0,100,0,0,0,0,0,39,15,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Guardsman - On Aggro - Call For Help");
SET @ENTRY := 12422;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,12000,14000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Talon Dragonspawn - In Combat - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,19000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Talon Dragonspawn - In Combat - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,2,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Death Talon Dragonspawn - On Reached Point 1 - Despawn Instant");
SET @ENTRY := 12458;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,17289,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Taskmaster - In Combat - Cast 'Shadow Shock' (Normal Dungeon)"),
(@ENTRY,0,1,0,1,0,100,2,500,1000,120000,120000,11,22458,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Taskmaster - Out of Combat - Cast 'Healing Circle' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,10000,10000,30000,35000,11,22458,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Taskmaster - In Combat - Cast 'Healing Circle' (Normal Dungeon)"),
(@ENTRY,0,3,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Taskmaster - On Reached Point 1 - Despawn Instant");
SET @ENTRY := 12416;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,12000,14000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Legionnaire - In Combat - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,8000,8000,15000,19000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Legionnaire - In Combat - Cast 'Strike' (Normal Dungeon)"),
(@ENTRY,0,2,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Legionnaire - On Reached Point 1 - Despawn Instant");
SET @ENTRY := 12420;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,17290,64,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Mage - In Combat - Cast 'Fireball' (Normal Dungeon)"),
(@ENTRY,0,1,0,9,0,100,2,0,10,15000,25000,11,22271,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Mage - Within 0-10 Range - Cast 'Arcane Explosion' (Normal Dungeon)"),
(@ENTRY,0,2,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Mage- On Reached Point 1 - Despawn Instant");
SET @ENTRY := 12459;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,0,0,3400,4700,11,22336,64,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Warlock - In Combat - Cast 'Shadow Bolt' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,5000,8000,18000,22000,11,19717,0,0,0,0,0,4,0,0,0,0,0,0,0,"Blackwing Warlock - In Combat - Cast 'Rain of Fire' (Normal Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,10000,10000,35000,35000,11,22372,2,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Warlock - In Combat - Cast 'Demon Portal' (Normal Dungeon)"),
(@ENTRY,0,3,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Warlock - On Reached Point 1 - Despawn Instant");
-- Door corrections
UPDATE `gameobject_template` SET `flags`=`flags`|16 WHERE `entry`=176964;
DELETE FROM `gameobject` WHERE `guid`=75160;
-- Conditions
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (19832, 23014, 19873);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 19832, 0, 0, 31, 0, 3, 12435, 0, 0, 0, 0, "", "Razorgore the Untamed - Possess"),
(13, 1, 23014, 0, 0, 31, 0, 3, 12435, 0, 0, 0, 0, "", "Razorgore the Untamed - Possess"),
(13, 1, 19873, 0, 0, 31, 0, 5, 177807, 0, 0, 0, 0, "", "Razorgore the Untamed - Destroy Egg"),
(13, 2, 19873, 0, 0, 31, 0, 3, 12435, 0, 0, 0, 0, "", "Razorgore the Untamed - Destroy Egg");
-- Eggs
UPDATE `gameobject_template` SET `faction`=14 WHERE  `entry`=177807;
-- Texts
DELETE FROM `creature_text` WHERE `entry`=12435;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(12435, 0, 0, 'You\'ll pay for forcing me to do this.', 14, 0, 100, 0, 0, 8275, 0, 'razorgore SAY_EGGS_BROKEN1'),
(12435, 0, 1, 'Fools! These eggs are more precious than you know.', 14, 0, 100, 0, 0, 8276, 0, 'razorgore SAY_EGGS_BROKEN2'),
(12435, 0, 2, 'No! Not another one! I\'ll have your heads for this atrocity.', 14, 0, 100, 0, 0, 8277, 0, 'razorgore SAY_EGGS_BROKEN3'),
(12435, 1, 0, 'If I fall into the abyss I\'ll take all of you mortals with me...', 14, 0, 100, 0, 0, 8278, 0, 'razorgore SAY_WIPE'),
(12435, 2, 0, 'Orb of Domination loses power and shuts off!', 16, 0, 100, 0, 0, 0, 0, 'razorgore EMOTE_ORB_DEACTIVATE'),
(12435, 3, 0, 'Nefarian\'s troops flee as the controlling power of the orb is drained.', 16, 0, 100, 0, 0, 0, 0, 'razorgore EMOTE_RUN_OFF');
