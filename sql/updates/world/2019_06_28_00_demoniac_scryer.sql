UPDATE `creature_template` SET `faction`=113, `unit_flags`=0, `ScriptName`="npc_demoniac_scryer" WHERE `entry`=22258;
UPDATE `creature_template` SET `ScriptName`="" WHERE `entry`=22260;

-- Hellfire Wardling SAI
SET @ENTRY := 22259;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,54,0,100,0,0,0,0,0,11,38683,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hellfire Wardling - On Just Summoned - Cast 'Magic Sucker Device Despawner, Mob'"),
(@ENTRY,0,1,2,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hellfire Wardling - On Just Summoned - Say Line 0"),
(@ENTRY,0,2,4,6,0,100,0,0,0,0,0,11,38891,2,0,0,0,0,1,0,0,0,0,0,0,0,"Hellfire Wardling - On Just Died - Cast 'Magic Sucker Device (Despawn Visual)'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(@ENTRY, 0, 0, 'Your end has come!', 12, 0, 100, 0, 0, 0, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 1, 'An intruder!  Begone!', 12, 0, 100, 0, 0, 0, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 2, 'An intruder!  Begone!', 12, 0, 100, 0, 0, 8152, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 3, 'You will burn!', 12, 0, 100, 0, 0, 0, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 4, 'Die!', 12, 0, 100, 0, 0, 0, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 5, 'Your end has come!', 12, 0, 100, 0, 0, 8152, 0, 'Hellfire Wardling'),
(@ENTRY, 0, 6, 'Die!', 12, 0, 100, 0, 0, 8152, 0, 'Hellfire Wardling');

-- Fel Warden SAI
SET @ENTRY := 22273;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,2,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Warden - On Just Summoned - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,0,0,3200,3800,11,14034,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Warden - In Combat - Cast 'Fireball'"),
(@ENTRY,0,2,0,0,0,100,0,6000,12000,20000,30000,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Warden - In Combat - Cast 'Frost Nova'");
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(@ENTRY, 0, 0, 'Die, interloper!  Your puny device cannot pierce the dark magics of Hellfire Citadel!', 12, 0, 100, 397, 0, 0, 0, 'Fel Warden');

-- Demonaic Visitation
DELETE FROM `spell_script_names` WHERE `spell_id`=38708;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(38708, "spell_demonaic_visitation");
