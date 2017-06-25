-- Firewalker 
DELETE FROM `spell_script_names` WHERE ScriptName="spell_firewalker_fireblossom";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(19636, "spell_firewalker_fireblossom");
-- Firewalker SAI
SET @ENTRY := 11666;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,12000,12000,8000,15000,11,19635,0,0,0,0,0,0,0,0,0,0,0,0,0,"Firewalker - In Combat - Cast 'Incite Flames' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,6000,6000,12000,12000,11,19636,0,0,0,0,0,1,0,0,0,0,0,0,0,"Firewalker - In Combat - Cast 'Fire Blossom' (Normal Dungeon)"),
(@ENTRY,0,2,0,4,0,100,0,0,0,0,0,11,19396,0,0,0,0,0,1,0,0,0,0,0,0,0,"Firewalker - On Aggro - Cast 'Incinerate (SERVERSIDE)'");
-- Firelord 
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_firelord" WHERE `entry` = 11668;
-- Lava Surger SAI
SET @ENTRY := 12101;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,40,15000,25000,11,19196,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lava Surger - Within 0-40 Range - Cast 'Surge' (Normal Dungeon)");
-- Core Hound
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_core_hound" WHERE `entry` = 11671;
DELETE FROM `creature_text` WHERE `entry`=11671;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(11671, 0, 0, "%s collapses and begins to smolder.", 16, 0, 100, 0, 0, 0, 0, "core hound EMOTE_FEIGN_DEATH"),
(11671, 1, 0, "%s reignites from the heat of another Core Hound!", 16, 0, 100, 0, 0, 0, 0, "core hound EMOTE_RESSURRECT");
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_ancient_core_hound" WHERE `entry` = 11673;
-- Flame Imp SAI
SET @ENTRY := 11669;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,10,15000,25000,11,20602,0,0,0,0,0,1,0,0,0,0,0,0,0,"Flame Imp - Within 0-10 Range - Cast 'Fire Nova' (Normal Dungeon)");
-- Lava Annihilator SAI
SET @ENTRY := 11665;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,16168,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lava Annihilator - In Combat - Cast 'Flame Buffet' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,0,0,3400,4700,11,22088,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lava Annihilator - In Combat - Cast 'Fireball' (Normal Dungeon)");
-- Lava Elemental SAI
SET @ENTRY := 12076;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,18000,22000,11,19641,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lava Elemental - In Combat - Cast 'Pyroclast Barrage' (Normal Dungeon)");
-- Lava Reaver SAI
SET @ENTRY := 12100;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,8000,12000,15000,11,19642,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lava Reaver - In Combat - Cast 'Cleave' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,10000,10000,10000,25000,11,19644,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lava Reaver - In Combat - Cast 'Strike' (Normal Dungeon)");
