-- Bronjahm
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=12752 AND `type` IN (11, 12, 18);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(12752,11,0,0,"achievement_bronjahm_soul_power");
-- Devourer of Souls
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=12976 AND `type` IN (11, 12, 18);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(12976,11,0,0,'achievement_three_faced');
-- Spiteful Apparition SAI
SET @ENTRY := 36551;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,25,0,100,1,0,0,0,0,11,69105,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Reset - Cast 'Soul Horror Visual' (No Repeat)"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,11,69136,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Reset - Cast 'Spiteful Apparition Visual' (No Repeat)"),
(@ENTRY,0,2,3,34,0,100,1,5,0,0,0,11,68895,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Reached Point 0 - Cast 'Spite' (No Repeat)"),
(@ENTRY,0,3,4,61,0,100,0,5,0,0,0,41,4000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Reached Point 0 - Despawn In 4000 ms (No Repeat)"),
(@ENTRY,0,4,0,61,0,100,0,5,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Reached Point 0 - Disable Combat Movement (No Repeat)"),
(@ENTRY,0,5,0,11,0,100,0,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spiteful Apparition - On Respawn - Enable Combat Movement");
DELETE FROM `instance_trash_map_data` WHERE `InstanceId`=632;
INSERT INTO `instance_trash_map_data` (`InstanceId`, `BossDataId`, `TrashGUID`) VALUES
(632, 0, 201792),
(632, 0, 201677),
(632, 0, 201725),
(632, 0, 201766),
(632, 0, 201726),
(632, 0, 201712),
(632, 0, 201676),
(632, 0, 201697),
(632, 0, 201705),
(632, 0, 201688),
(632, 0, 201786),
(632, 0, 201751),
(632, 0, 201733),
(632, 0, 201713),
(632, 0, 201735),
(632, 0, 201783),
(632, 0, 201749),
(632, 0, 201719),
(632, 0, 201753),
(632, 0, 201763),
(632, 0, 201693),
(632, 0, 201711),
(632, 0, 201678),
(632, 0, 201699),
(632, 0, 201742),
(632, 0, 201734),
(632, 0, 201776),
(632, 0, 201686),
(632, 0, 201758),
(632, 0, 201791),
(632, 0, 201764),
(632, 0, 201706),
(632, 0, 201762),
(632, 0, 201695),
(632, 0, 201698),
(632, 1, 201790),
(632, 1, 201732),
(632, 1, 201748),
(632, 1, 201714),
(632, 1, 201700),
(632, 1, 201757),
(632, 1, 201796),
(632, 1, 201737),
(632, 1, 201687);
