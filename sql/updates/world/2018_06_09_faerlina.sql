UPDATE `creature_template` SET `spell2`=0 WHERE `entry`=16506;
UPDATE `creature_template` SET `spell3`=0 WHERE `entry`=29274;

-- Naxxramas Worshipper SAI
SET @ENTRY := 16506;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,5000,7000,9000,11,54095,0,0,0,0,0,2,0,0,0,0,0,0,0,"Naxxramas Worshipper - In Combat - Cast 'Fireball' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,4,4000,5000,7000,9000,11,54096,0,0,0,0,0,2,0,0,0,0,0,0,0,"Naxxramas Worshipper - In Combat - Cast 'Fireball' (Heroic Dungeon)"),
(@ENTRY,0,2,0,6,0,100,4,0,0,0,0,11,28732,0,0,0,0,0,1,0,0,0,0,0,0,0,"Naxxramas Worshipper - On Just Died - Cast 'Widow's Embrace' (Heroic Dungeon)"),
(@ENTRY,0,3,0,5,0,100,0,0,0,1,0,34,119,0,0,0,0,0,1,0,0,0,0,0,0,0,"Naxxramas Worshipper - On Killed Unit - Set Instance Data 119 to 0");
