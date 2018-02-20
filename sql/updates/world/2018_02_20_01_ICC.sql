-- Plague Scientist
DELETE FROM `smart_scripts` WHERE `entryorguid`=37023 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_plague_scientist" WHERE `entry`=37023;
-- Deathspeaker High Priest
UPDATE `creature_onkill_reputation` SET `RewOnKillRepValue1`=50 WHERE `creature_id` IN(36829,38074);
-- Web Wrap
DELETE FROM `smart_scripts` WHERE `entryorguid`=38028 AND `source_type`=0;
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|32, `AIName`="", `ScriptName`="npc_icc_web_wrap" WHERE `entry`=38028;
-- ICC Buff 10%->30%
UPDATE `spell_area` SET `spell`=73822 WHERE `spell`=73818;
UPDATE `spell_area` SET `spell`=73828 WHERE `spell`=73824;
-- Gunship Prenerf
DELETE FROM `creature` WHERE `guid` IN (133974, 133990);
UPDATE `creature` SET `position_x`=14.61, `position_y`=30.60, `position_z`=35.71 WHERE `guid`=133991;
UPDATE `creature` SET `position_x`=-19.81, `position_y`=-24.40, `position_z`=21.62 WHERE `guid`=133989;
UPDATE `creature` SET `spawnMask`=15 WHERE `guid` IN (133991);
-- Dominate Mind
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_deathwhisper_dominate_mind";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71289, "spell_deathwhisper_dominate_mind");
-- Respawning npcs
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_icc_champion" WHERE `entry` IN (37928,37996,37965);
-- Trash corrections --

-- Ancient Skeletal Soldier SAI
SET @ENTRY := 37012;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,10000,7000,12000,11,70964,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ancient Skeletal Soldier - In Combat - Cast 'Shield Bash'");
-- Servant of the Throne SAI
SET @ENTRY := 36724;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,1000,3000,4500,11,71029,64,0,0,0,0,2,0,0,0,0,0,0,0,"Servant of the Throne - In Combat - Cast 'Glacial Blast'");
-- The Damned SAI
SET @ENTRY := 37011;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,11,70961,3,0,0,0,0,1,0,0,0,0,0,0,0,"The Damned - On Just Died - Cast 'Shattered Bones' (No Repeat)"),
(@ENTRY,0,1,0,2,0,100,0,1,30,15000,20000,11,70960,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Damned - Between 1-30% Health - Cast 'Bone Flurry'"),
(@ENTRY,0,2,0,1,0,100,0,1000,1000,60000,60000,49,0,0,0,0,0,0,25,8,0,0,0,0,0,0,"The Damned - Out of Combat - Start Attacking");

-- Before Marrowgar:
DELETE FROM `creature` WHERE `guid` IN (201107, 247113, 247114, 247115, 201146, 201090);
SET @CGUID = 200800;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND  @CGUID + 7;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@CGUID + 0, 37012, 631, 15, 1, 0, 1, -300.816803, 2200.999268, 41.981998, 6.248071, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 1, 37012, 631, 15, 1, 0, 1, -299.571411, 2223.170166, 41.978565, 6.160891, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 2, 36724, 631, 15, 1, 0, 1, -241.973160, 2215.202393, 42.564507, 6.215871, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 3, 36724, 631, 15, 1, 0, 1, -242.466614, 2207.968506, 42.564507, 6.223723, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 4, 37012, 631, 15, 1, 0, 1, -200.403839, 2214.431152, 35.233513, 0.029989, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 5, 37012, 631, 15, 1, 0, 1, -201.366531, 2206.084717, 35.233513, 0.029989, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 6, 36724, 631, 15, 1, 0, 1, -213.672729, 2196.816406, 35.233513, 0.029989, 86400, 0, 0, 315000, 0, 0, 0, 0, 0),
(@CGUID + 7, 36724, 631, 15, 1, 0, 1, -214.241837, 2224.958740, 35.233513, 0.029989, 86400, 0, 0, 315000, 0, 0, 0, 0, 0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200966,201066);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200966,200966,0,0,3,0,0),
(200966,201066,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200878,200805,200804,200995,200806,200939,201080,201106,200807);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200878,200878,0,0,3,0,0),
(200878,200805,0,0,3,0,0),
(200878,200804,0,0,3,0,0),
(200878,200995,0,0,3,0,0),
(200878,200806,0,0,3,0,0),
(200878,200939,0,0,3,0,0),
(200878,201080,0,0,3,0,0),
(200878,201106,0,0,3,0,0),
(200878,200807,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200892,201170,200803,201090,200802,201127,201119);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200892,200892,0,0,3,0,0),
(200892,201170,0,0,3,0,0),
(200892,200803,0,0,3,0,0),
(200892,201090,0,0,3,0,0),
(200892,200802,0,0,3,0,0),
(200892,201127,0,0,3,0,0),
(200892,201119,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200936,200800,200934,201160,201011,200912,200801,200996);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200936,200936,0,0,3,0,0),
(200936,200800,0,0,3,0,0),
(200936,200934,0,0,3,0,0),
(200936,201160,0,0,3,0,0),
(200936,201011,0,0,3,0,0),
(200936,200912,0,0,3,0,0),
(200936,200801,0,0,3,0,0),
(200936,200996,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201097,201029,201087,201186);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201097,201097,0,0,3,0,0),
(201097,201029,0,0,3,0,0),
(201097,201087,0,0,3,0,0),
(201097,201186,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201177,200969,200913,200965);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201177,201177,0,0,3,0,0),
(201177,200969,0,0,3,0,0),
(201177,200913,0,0,3,0,0),
(201177,200965,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200956,201145,201124,201037,200919);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200956,200956,0,0,3,0,0),
(200956,201145,0,0,3,0,0),
(200956,201124,0,0,3,0,0),
(200956,201037,0,0,3,0,0),
(200956,200919,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (200949,201065,201036,200883,201093);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(200949,200949,0,0,3,0,0),
(200949,201065,0,0,3,0,0),
(200949,201036,0,0,3,0,0),
(200949,200883,0,0,3,0,0),
(200949,201093,0,0,3,0,0);

UPDATE `creature` SET `MovementType`=1, `spawndist`=4 WHERE `guid` IN (201029, 201087, 201186, 201093, 200883, 201036, 201065, 201145, 200919, 201037, 201124, 200913, 200969, 201177);

UPDATE `creature` SET `position_x`=-142.105408, `position_y`=2205.533691, `position_z`=35.227146 WHERE `guid`=200966;
UPDATE `creature` SET `position_x`=-142.105408, `position_y`=2217.462402, `position_z`=35.227146 WHERE `guid`=201066;

DELETE FROM `areatrigger_scripts` WHERE `entry`=5611;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5611, "at_icc_lights_hammer_disable_spawn");

UPDATE `creature` SET `position_x`=-107.308174, `position_y`=2233.338867, `position_z`=30.564341 WHERE `guid`=247110;
UPDATE `creature` SET `position_x`=-106.886055, `position_y`=2188.241943, `position_z`=30.654263 WHERE `guid`=247111;
UPDATE `creature` SET `position_x`=-89.493370, `position_y`=2214.156250, `position_z`=27.902536 WHERE `guid`=247112;

SET @CGUID = 247113;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 2;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID + 0, 37011, 631, 15, 1, 0, 0, -175.0, 2215.0, 35.23, 0.0, 86400, 0, 0, 478800, 0, 2, 0, 0, 0),
(@CGUID + 1, 37011, 631, 15, 1, 0, 0, -175.0, 2215.0, 35.23, 0.0, 86400, 0, 0, 478800, 0, 2, 0, 0, 0),
(@CGUID + 2, 37011, 631, 15, 1, 0, 0, -175.0, 2215.0, 35.23, 0.0, 86400, 0, 0, 478800, 0, 2, 0, 0, 0);
DELETE FROM `creature_addon` WHERE `guid`=@CGUID + 0;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(@CGUID + 0, 3701100, 0, 0, 1, 0, "");
DELETE FROM `creature_formations` WHERE `leaderGUID`=@CGUID + 0;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@CGUID + 0, @CGUID + 0, 0, 0, 1, 0, 0),
(@CGUID + 0, @CGUID + 1, 4, 90, 1, 1, 2),
(@CGUID + 0, @CGUID + 2, 4, 270, 1, 1, 2);
DELETE FROM `waypoint_data` WHERE `id`=3701100;
INSERT INTO `waypoint_data` VALUES 
(3701100, 1, -175.0, 2190.0, 35.5, 0, 0, 1, 0, 100, 0),
(3701100, 2, -175.0, 2240.0, 35.5, 0, 0, 1, 0, 100, 0);

UPDATE `creature` SET `position_x`=-218.248, `position_y`=2181.06, `position_z`=37.9852 WHERE `guid`=200806;
UPDATE `creature` SET `position_x`=-210.888, `position_y`=2180.11, `position_z`=37.985 WHERE `guid`=200878;
UPDATE `creature` SET `position_x`=-214.409363, `position_y`= 2180.516357, `position_z`=37.984989 WHERE `guid`=200805;
UPDATE `creature` SET `position_x`=-236.411423, `position_y`=2211.396484, `position_z`=42.154911 WHERE `guid`=201080;
UPDATE `creature` SET `position_x`=-216.789795, `position_y`=2242.590576, `position_z`=37.985176 WHERE `guid`=200804;
UPDATE `creature` SET `position_x`=-212.368439, `position_y`=2237.508301, `position_z`=36.326073 WHERE `guid`=200995;
UPDATE `creature` SET `position_x`=-224.459259, `position_y`=2239.782227, `position_z`=37.985332 WHERE `guid`=200807;

DELETE FROM `smart_scripts` WHERE `entryorguid`=37007 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_deathbound_ward" WHERE `entry`=37007;

-- First room (left ward)
SET @GUID = 200987;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@GUID*10, 1, -193.471802, 2165.252930, 37.985104),
(@GUID*10, 2, -173.338287, 2178.899658, 37.985104),
(@GUID*10, 3, -175.232864, 2244.533203, 37.985283),
(@GUID*10, 4, -193.436111, 2258.234863, 37.985283),
(@GUID*10, 5, -214.251709, 2242.914551, 37.985283),
(@GUID*10, 6, -214.629257, 2178.479736, 37.985176),
(@GUID*10, 7, -193.471802, 2165.252930, 37.985104);

-- First room (right ward)
SET @GUID = 201043;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@GUID*10, 1, -193.436111, 2258.234863, 37.985283),
(@GUID*10, 2, -214.251709, 2242.914551, 37.985283),
(@GUID*10, 3, -214.629257, 2178.479736, 37.985176),
(@GUID*10, 4, -193.471802, 2165.252930, 37.985104),
(@GUID*10, 5, -173.338287, 2178.899658, 37.985104),
(@GUID*10, 6, -175.232864, 2244.533203, 37.985283),
(@GUID*10, 7, -193.436111, 2258.234863, 37.985283);

-- Second room (left ward)
SET @GUID = 201108;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@GUID*10, 1, -269.783661, 2211.531494, 42.564575),
(@GUID*10, 2, -238.439240, 2211.536621, 42.564537),
(@GUID*10, 3, -215.574402, 2211.696533, 35.233490),
(@GUID*10, 4, -192.182373, 2210.857178, 35.234684),
(@GUID*10, 5, -215.574402, 2211.696533, 35.233490),
(@GUID*10, 6, -238.439240, 2211.536621, 42.564537),
(@GUID*10, 7, -337.642487, 2211.516113, 42.564522);

-- Second room (right ward)
SET @GUID = 201130;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@GUID*10, 1, -300.544312, 2211.772949, 42.012756),
(@GUID*10, 2, -337.642487, 2211.516113, 42.564522),
(@GUID*10, 3, -238.439240, 2211.536621, 42.564537),
(@GUID*10, 4, -215.574402, 2211.696533, 35.233490),
(@GUID*10, 5, -192.182373, 2210.857178, 35.234684),
(@GUID*10, 6, -215.574402, 2211.696533, 35.233490),
(@GUID*10, 7, -238.439240, 2211.536621, 42.564537);

-- Before Gunship:
-- Kor'kron Battle Standard SAI
SET @ENTRY := 37044;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,69809,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Battle Standard - On Respawn - Cast 'Kor'kron Battle Standard'"),
(@ENTRY,0,1,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Battle Standard - On Respawn - Set Reactstate Passive"),
(@ENTRY,0,2,0,11,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Battle Standard - On Respawn - Disable Combat Movement");

-- Skybreaker Battle Standard SAI
SET @ENTRY := 37041;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,69808,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Battle Standard - On Respawn - Cast 'Skybreaker Battle Standard'"),
(@ENTRY,0,1,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Battle Standard - On Respawn - Set Reactstate Passive"),
(@ENTRY,0,2,0,11,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Battle Standard - On Respawn - Disable Combat Movement");

-- Before Valithria:
UPDATE `creature_template` SET `ScriptName`="npc_icc_warhawk" WHERE `entry`=38154;
-- Reputation:
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (37501, 37502, 37228, 37229, 38154, 38134, 38137, 38197, 38198);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(37501, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(37502, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(37228, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(37229, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(38154, 1156, 0, 7, 0, 2, 0, 0, 0, 0),
(38134, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(38137, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(38197, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(38198, 1156, 0, 7, 0, 15, 0, 0, 0, 0);

-- Crimson Hall:
SET @CGUID = 210000;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 9;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@CGUID + 0, 37595, 631, 15, 1, 0, 1, 4624.595703, 2778.435303, 361.164734, 2.057239, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 1, 37666, 631, 15, 1, 0, 1, 4626.430176, 2791.383789, 361.164734, 4.162108, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 2, 37595, 631, 15, 1, 0, 1, 4629.443848, 2744.228516, 361.165314, 2.379777, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 3, 37666, 631, 15, 1, 0, 1, 4625.564941, 2756.155273, 361.165771, 4.374685, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 4, 37664, 631, 15, 1, 0, 1, 4582.464844, 2687.033203, 384.684418, 3.575848, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 5, 37595, 631, 15, 1, 0, 1, 4573.750000, 2675.562988, 384.684418, 1.438779, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 6, 37595, 631, 15, 1, 0, 1, 4512.936523, 2769.254395, 403.982422, 0.000720, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 7, 37666, 631, 15, 1, 0, 1, 4532.104492, 2769.261230, 403.982422, 3.142632, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 8, 37664, 631, 15, 1, 0, 1, 4580.873535, 2851.963135, 384.682861, 2.445193, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 9, 37595, 631, 15, 1, 0, 1, 4575.161621, 2863.505127, 384.682861, 4.641165, 86400, 0, 0, 431360, 91600, 0, 0, 0, 0);

UPDATE `creature` SET `position_x`=4629.100098, `position_y`=2753.189941, `position_z`=361.165985, `orientation`=3.624630 WHERE `guid`=201444;

-- Darkfallen Advisor SAI
SET @ENTRY := 37571;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,10000,12000,11,72057,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Advisor - In Combat - Cast 'Lich Slap'"),
(@ENTRY,0,1,0,14,0,100,0,200000,39,8000,8000,11,72065,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkfallen Advisor - Friendly At 200000 Health - Cast 'Shroud of Protection'"),
(@ENTRY,0,2,0,14,0,100,0,200000,39,8000,8000,11,72066,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkfallen Advisor - Friendly At 200000 Health - Cast 'Shroud of Spell Warding'");
-- Darkfallen Blood Knight SAI
SET @ENTRY := 37595;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,5000,5000,11,70437,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Blood Knight - In Combat - Cast 'Unholy Strike'"),
(@ENTRY,0,1,0,0,0,100,0,0,0,20000,20000,11,71736,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Blood Knight - In Combat - Cast 'Vampiric Aura'");
-- Darkfallen Noble SAI
SET @ENTRY := 37663;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,5000,5000,11,72960,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Noble - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,10000,15000,15000,15000,11,70645,0,0,0,0,0,6,0,0,0,0,0,0,0,"Darkfallen Noble - In Combat - Cast 'Chains of Shadow'");
-- Darkfallen Archmage SAI
SET @ENTRY := 37664;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,10000,15000,20000,11,70408,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Amplify Magic'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,12000,15000,11,70407,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Blast Wave'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4000,8000,10000,11,70409,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Fireball'"),
(@ENTRY,0,3,0,0,0,100,0,6000,10000,16000,20000,11,70410,0,0,0,0,0,17,14,29,1,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Polymorph: Spider'"),
(@ENTRY,0,5,0,4,0,100,0,0,0,0,0,11,70299,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Archmage - On Aggro - Cast 'Siphon Essence'"),
(@ENTRY,0,6,0,6,0,100,0,0,0,0,0,104,0,0,0,0,0,0,20,201741,40,0,0,0,0,0,"Darkfallen Archmage - On Just Died - Set Gameobject Flag ");
-- Darkfallen Tactician SAI
SET @ENTRY := 37666;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,15000,10000,20000,11,70432,0,0,0,0,0,3,0,0,0,0,0,0,0,"Darkfallen Tactician - In Combat - Cast 'Blood Sap'"),
(@ENTRY,0,1,0,0,0,100,0,15000,20000,15000,25000,11,70431,0,0,0,0,0,17,11,39,1,0,0,0,0,"Darkfallen Tactician - In Combat - Cast 'Shadowstep'"),
(@ENTRY,0,2,0,0,0,100,0,3000,6000,5000,5000,11,70437,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Tactician - In Combat - Cast 'Unholy Strike'");
-- Darkfallen Lieutenant SAI
SET @ENTRY := 37665;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4000,8000,8000,11,70423,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Lieutenant - In Combat - Cast 'Vampiric Curse'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,5000,5000,11,70435,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Lieutenant - In Combat - Cast 'Rend Flesh'");
-- Darkfallen Commander SAI
SET @ENTRY := 37662;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1000,12000,12000,11,70750,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Commander - In Combat - Cast 'Battle Shout'"),
(@ENTRY,0,1,0,0,0,100,0,4000,4000,20000,20000,11,70449,0,0,0,0,0,6,0,0,0,0,0,0,0,"Darkfallen Commander - In Combat - Cast 'Vampire Rush'");
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201482,201646,201479,201659);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201482,201482,0,0,3,0,0),
(201482,201646,0,0,3,0,0),
(201482,201479,0,0,3,0,0),
(201482,201659,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (210000,201396,201458,201307,210001,201238);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(210000,210000,0,0,3,0,0),
(210000,201396,0,0,3,0,0),
(210000,201458,0,0,3,0,0),
(210000,201307,0,0,3,0,0),
(210000,210001,0,0,3,0,0),
(210000,201238,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201314,201673,210003,201444,210002,201259);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201314,201314,0,0,3,0,0),
(201314,201673,0,0,3,0,0),
(201314,210003,0,0,3,0,0),
(201314,201444,0,0,3,0,0),
(201314,210002,0,0,3,0,0),
(201314,201259,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201218,210008,201604,201275,201595,210009);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201218,201218,0,0,3,0,0),
(201218,210008,0,0,3,0,0),
(201218,201604,0,0,3,0,0),
(201218,201275,0,0,3,0,0),
(201218,201595,0,0,3,0,0),
(201218,210009,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (210006,201385,201335,210007,201306,201296);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(210006,210006,0,0,3,0,0),
(210006,201385,0,0,3,0,0),
(210006,201335,0,0,3,0,0),
(210006,210007,0,0,3,0,0),
(210006,201306,0,0,3,0,0),
(210006,201296,0,0,3,0,0);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (201530,210005,201630,201589,201553,210004);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(201530,201530,0,0,3,0,0),
(201530,210005,0,0,3,0,0),
(201530,201630,0,0,3,0,0),
(201530,201589,0,0,3,0,0),
(201530,201553,0,0,3,0,0),
(201530,210004,0,0,3,0,0);

-- Sindragosa room:
UPDATE `creature` SET `MovementType`=1, `spawndist`=4 WHERE `id`=37532;
UPDATE `creature_onkill_reputation` SET `RewOnKillRepValue1`=2 WHERE `creature_id` IN (37532, 38151);

-- Valithria
UPDATE `creature_template` SET `flags_extra`=(`flags_extra`&~0x00000080) WHERE `entry`=37950;
UPDATE `creature_template` SET `mechanic_immune_mask`=8388624 WHERE `entry` IN (37868, 37863, 37934, 37886, 38171, 38727, 38737, 38167, 38725, 38735, 38166, 38724, 38734, 38170, 38723, 38733);

-- Rampart of Skull Horde NPCs
SET @CGUID = 1980054;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID AND @CGUID+5;
INSERT INTO `creature` VALUES
(@CGUID, 37031, 631, 15, 1, 0, 1, -563.49, 2282.43, 199.96, 0.95, 86400, 0, 0, 324010, 41690, 0, 0, 0, 0),
(@CGUID+1, 37033, 631, 15, 1, 0, 1, -555.20, 2283.03, 199.96, 1.03, 86400, 0, 0, 261715, 91600, 0, 0, 0, 0),
(@CGUID+2, 37035, 631, 15, 1, 0, 1, -546.93, 2285.06, 199.96, 0.73, 86400, 0, 0, 471835, 41690, 0, 0, 0, 0),
(@CGUID+3, 37149, 631, 15, 1, 0, 1, -547.45, 2273.36, 199.96, 0.42, 86400, 0, 0, 261715, 91600, 0, 0, 0, 0),
(@CGUID+4, 37034, 631, 15, 1, 0, 1, -538.90, 2265.76, 199.96, 1.35, 86400, 0, 0, 261715, 91600, 0, 0, 0, 0),
(@CGUID+5, 37029, 631, 15, 1, 0, 1, -519.92, 2317.28, 199.97, 3.73, 86400, 0, 0, 471835, 0, 0, 0, 0, 0);

-- Darkfallen Blood Knight
UPDATE `creature_template` SET `ScriptName` = "npc_darkfallen_blood_knight", `AIName` = "" WHERE `entry` = 37595; 

-- LK valkyrs
UPDATE `creature_template` SET `HoverHeight`=0 WHERE `entry` IN (36609, 39120, 39121, 39122);

-- Frostwing Halls
UPDATE `creature` SET `position_y`=2554.991211, `position_z`=354.717682 WHERE `guid`=137765;
UPDATE `creature` SET `position_y`=2558.303711, `position_z`=353.850403 WHERE `guid`=137769;
UPDATE `creature` SET `position_y`=2558.230713, `position_z`=353.869324 WHERE `guid`=137768;
UPDATE `creature` SET `position_x`=4365.277344, `position_y`=2556.302734, `position_z`=354.374420 WHERE `guid`=137757;
UPDATE `creature` SET `position_x`=4347.931641, `position_y`=2556.314941, `position_z`=354.371399 WHERE `guid`=137756;

-- Left Battle Maiden (1st group)
SET @GUID = 137757;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4365.456055, 2638.538330, 351.100433, 1);

-- Left Huntress (1st group)
SET @GUID = 137769;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4362.18, 2642.97, 351.1, 1);

-- Warlord (1st group)
SET @GUID = 137765;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4356.85, 2636.39, 351.101, 1);

-- Right Huntress (1st group)
SET @GUID = 137768;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4351.66, 2642.95, 351.1, 1);

-- Right Battle Maiden (1st group)
SET @GUID = 137756;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4348.057617, 2638.836914, 351.100433, 1);


UPDATE `creature` SET `position_x`=4349.928223, `position_y`=2535.158447, `position_z`=358.432465 WHERE `guid`=137760;
UPDATE `creature` SET `position_x`=4353.247070, `position_y`=2539.200195, `position_z`=358.432465 WHERE `guid`=137771;
UPDATE `creature` SET `position_x`=4360.323730, `position_y`=2539.200195, `position_z`=358.432465 WHERE `guid`=137770;
UPDATE `creature` SET `position_x`=4363.255859, `position_y`=2535.158447, `position_z`=358.432465 WHERE `guid`=137761;

-- Left Battle Maiden (2nd group)
SET @GUID = 137761;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4363.255859, 2596.497559, 351.101624, 1);

-- Left Huntress (2nd group)
SET @GUID = 137770;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4360.323730, 2599.092041, 351.101624, 1);

-- Right Huntress (2nd group)
SET @GUID = 137771;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4353.247070, 2599.411621, 351.101624, 1);

-- Right Battle Maiden (2nd group)
SET @GUID = 137760;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`) VALUES
(@GUID*10, 1, 4350.106445, 2597.012451, 351.101929, 1);
