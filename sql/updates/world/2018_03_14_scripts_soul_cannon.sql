-- [QUEST] The Soul Cannon of Reth'hedron
SET @NPCTEXT = 11030;
SET @GOSIP = 8725; -- values taken from https://github.com/TrinityCore/TrinityCore/issues/4763
SET @ENTRY  := 23093; -- NPC entry
SET @SPELL1 := 40129; -- Summon Air Elemental
SET @SPELL2 := 40130; -- Summon Water Elemental
SET @SPELL3 := 40132; -- Summon Earth Elemental
SET @SPELL4 := 40133; -- Summon Fire Elemental
SET @SPELL5 := 40134; -- Summon Arcane Elemental
UPDATE `creature_template` SET `gossip_menu_id`=@GOSIP, `AIName`= "SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
UPDATE `creature_template` SET `AIName` = "SmartAI", faction = 16 WHERE `entry` IN (23096,23097,23098,23099,23100);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=8725;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,8725,0,0,9,11089,0,0,0,'','Show gossip option if player has Quest 11089 The Soul Cannon of Reth''hedron');

DELETE FROM `gossip_menu` WHERE `entry`=@GOSIP AND `text_id`=@NPCTEXT;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (@GOSIP,@NPCTEXT);


DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (@GOSIP) AND `id` IN (0,1);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`) VALUES
(@GOSIP,0,0, 'I am an envoy of Balthas. He has sent me to collect a flawless arcane essence.',1,1,0,0,0,0, '');

DELETE FROM `creature_text` WHERE `entry`=23093;
DELETE FROM `creature_text` WHERE `entry`=23100 AND `groupid`=0;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(23093,0,0, 'So my blood was not a sufficient payment, eh? Fine, let us recover your arcane essence. After this, I owe Balthas nothing.',12,0,100,1,0,0, 'Sar''this'),
(23093,1,0, '%s places a fetish at the ritual pile.',16,0,100,16,0,0, 'Sar''this'),
(23093,2,0, 'The process is arduous. We must first summon forth acolytes of the elements. You must then destroy these acolytes so that my minions can make preparations.',12,0,100,0,0,0, 'Sar''this'),
(23093,3,0, 'Prepare yourself! The acolyte of water is soon to come...',12,0,100,0,0,0, 'Sar''this'),
(23093,4,0, 'Come forth, acolyte of earth!',12,0,100,0,0,0, 'Sar''this'),
(23093,5,0, 'Fire, show yourself!',12,0,100,0,0,0, 'Sar''this'),
(23093,6,0, 'Well done!  Let''s continue.',12,0,100,0,0,0, 'Sar''this'),
(23093,7,0, 'Now we call forth the arcane acolyte.',12,0,100,0,0,0, 'Sar''this'),
(23093,8,0, 'It is yours my Lord!',12,0,100,0,0,0, 'Sar''this'),
(23100,0,0, 'I require your life essence to maintain my existence in this realm.',12,0,100,0,0,0, 'Flawless Arcane Elemental');
DELETE FROM `smart_scripts` WHERE `entryorguid`= @ENTRY ;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN (@ENTRY*100,@ENTRY*101,@ENTRY*102,@ENTRY*103,@ENTRY*104,@ENTRY*105,23096,23097,23098,23099,23100);
INSERT INTO `smart_scripts` VALUES
-- Sar'this event
(@ENTRY,0,1,0,62,0,100,0,@GOSIP,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - On gossip Option select - run script 1'),
(@ENTRY*100,9,0,0,0,0,100,0,100,100,100,100,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Sar''this - script 1 - Close Gossip'),
(@ENTRY*100,9,1,0,0,0,100,0,100,100,100,100,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 1 - Say Line 0'),
(@ENTRY*100,9,2,0,0,0,100,0,100,100,100,100,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 1 - Say Line 2'),
(@ENTRY*100,9,3,0,0,0,100,0,1000,1000,1000,1000,83,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 1 - Remove npc flag'),
(@ENTRY*100,9,4,0,0,0,100,0,1000,20000,0,0,53,0,@ENTRY*10,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 1 - load waypoints 1'),

(@ENTRY,0,2,0,58,0,100,1,0,@ENTRY*10,0,0,11,@SPELL1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this -on waypoint 1 end -  cast spell summon Air elemental'),
(@ENTRY,   0,3,0,38,0,100,0,1,1,       0,0,80,@ENTRY*101,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this on data set 1 1 run script 2'),
(@ENTRY*101,9,0,0,0,0,100,0,0,0,0,0, 28, 0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Sar''this script 2 - remove spell aura'),
(@ENTRY*101,9,1,0,0,0,100,0,2000,20000,0,0,53,0,@ENTRY*10+1,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 2 - load waypoints 2'),
(@ENTRY*101,9,2,0,0,0,100,0,100,100,100,100,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 2 - Say line 3'),

(@ENTRY,0,4,0,58,0,100,1,0,@ENTRY*10+1,0,0,11,@SPELL2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this -on waypoint 2 end- cast spell summon Water elemental'),
(@ENTRY,0,5,0,38,0,100,0,2,2,       0,0,80,@ENTRY*102,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this on data set 2 2 run script 3'),
(@ENTRY*102,9,0,0,0,0,100,0,4000,20000,0,0,53,0,@ENTRY*10+2,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 3 - load waypoints 3'),
(@ENTRY*102,9,1,0,0,0,100,0,100,100,100,100,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 3 - Say line 4'),

(@ENTRY,0,6,0,58,0,100,1,0,@ENTRY*10+2,0,0,11,@SPELL3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - on waypoint 3 end - cast summon Earth elemental'),
(@ENTRY,0,7,0,38,0,100,0,3,3,       0,0,80,@ENTRY*103,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this on data set 3 3 run script 4'),
(@ENTRY*103,9,0,0,0,0,100,0,4000,10000,0,0,53,0,@ENTRY*10+3,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 4 - load waypoints 4'),
(@ENTRY*103,9,1,0,0,0,100,0,100,100,100,100,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 4 - Say line 5'),

(@ENTRY,0,8,0,58,0,100,1,0,@ENTRY*10+3,0,0,11,@SPELL4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - on waypoint 4 cast summon Fire elemental'),
(@ENTRY,0,9,0,38,0,100,0,4,4,       0,0,80,@ENTRY*104,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this on data set 4 4 run script 5'),
(@ENTRY*104,9,0,0,0,0,100,0,100,100,100,100,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 5- Say line 5'),
(@ENTRY*104,9,1,0,0,0,100,0,3000,20000,0,0,53,0,@ENTRY*10+4,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 5 - load waypoints 5'),
(@ENTRY*104,9,2,0,0,0,100,0,100,100,100,100,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 5 - Say line 7'),

(@ENTRY,0,10,0,58,0,100,1,0,@ENTRY*10+4,0,0,11,@SPELL5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this -on waypoint 5 end - cast summon Arcane elemental'),
(@ENTRY,0,11,0,38,0,100,0,5,5,       0,0,80,@ENTRY*105,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this on data set 5 5 run script 6'),
(@ENTRY*105,9,0,0,0,0,100,0,100,100,100,100,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 6  - Say line 8'),
(@ENTRY*105,9,1,0,0,0,100,0,3000,20000,0,0,53,0,@ENTRY*10+5,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - script 6 - load waypoints 6'),
(@ENTRY,0,12,14,58,0,100,0,0,@ENTRY*10+5,0,0,98,@GOSIP,@NPCTEXT,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this -on waypoint 6 end - Reset Gossip'),
(@ENTRY,0,13,0,61,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sar''this - on link prev id 13 - Set npcflag 1'),

-- SAI for elementals
(23096,0,0,0,6, 0,100,0,0,0,0,0,45,1,1,0,0,0,0,11, @ENTRY,20,0,0,0,0,0,'On death - Set data on Sarthis'),
(23097,0,0,0,6, 0,100,0,0,0,0,0,45,2,2,0,0,0,0,11, @ENTRY,20,0,0,0,0,0,'On death - Set data on Sarthis'),
(23098,0,0,0,6, 0,100,0,0,0,0,0,45,3,3,0,0,0,0,11, @ENTRY,20,0,0,0,0,0,'On death - Set data on Sarthis'),
(23099,0,0,0,6, 0,100,0,0,0,0,0,45,4,4,0,0,0,0,11, @ENTRY,20,0,0,0,0,0,'On death - Set data on Sarthis'),
(23100,0,0,0,6, 0,100,0,0,0,0,0,45,5,5,0,0,0,0,11, @ENTRY,20,0,0,0,0,0,'On death - Set data on Sarthis'),
(23100,0,1,0,54,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Arcane elemental on spawn say 0');

DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10, @ENTRY*10+1,@ENTRY*10+2, @ENTRY*10+3,@ENTRY*10+4,@ENTRY*10+5);
INSERT INTO `waypoints` VALUES
-- waypoints 1
(@ENTRY*10, 1,-2528.39, 4660.68, 170.49,''),
(@ENTRY*10, 2, -2515.82, 4667.77, 168.55,''),
(@ENTRY*10, 3,-2509.90, 4671.04, 165.74,''),
(@ENTRY*10, 4, -2504.60, 4674.00, 162.71,''),
(@ENTRY*10, 5, -2494.88, 4678.5, 158.56,''),
(@ENTRY*10, 6, -2484.43, 4678.14, 157.19,''),
(@ENTRY*10, 7, -2478.16, 4669.94, 159.28,''),
(@ENTRY*10, 8, -2484.25, 4661.53, 162.08,''),
-- waypoints 2
(@ENTRY*10+1, 1,-2441.07, 4653.56, 160.63,''),
(@ENTRY*10+1, 2,-2442.49, 4635.27, 158.21,''),
-- waypoints 3
(@ENTRY*10+2, 1,-2428.31, 4648.47, 160.48,''),
(@ENTRY*10+2, 2,-2404.47, 4629.48, 160.28,''),
-- waypoints 4
(@ENTRY*10+3, 1,-2419.24, 4588.27, 160.52,''),
-- waypoint 5
(@ENTRY*10+4, 1,-2404.47, 4629.48, 160.28,''),
(@ENTRY*10+4, 2,-2428.31, 4648.47, 160.48,''),
(@ENTRY*10+4, 3,-2482.00, 4674.76, 158.30,''),
(@ENTRY*10+4, 4,-2474.78, 4701.65, 155.23,''),
-- waypoints 6
(@ENTRY*10+5, 1,-2487.16, 4690.43, 154.76,''),
(@ENTRY*10+5, 2,-2494.00, 4684.60, 156.55,''),
(@ENTRY*10+5, 3,-2498.43, 4680.63, 158.77,''),
(@ENTRY*10+5, 4,-2505.03, 4674.71, 162.66,''),
(@ENTRY*10+5, 5,-2509.73, 4671.64, 165.51,''),
(@ENTRY*10+5, 6,-2514.79, 4668.73, 168.07,''),
(@ENTRY*10+5, 7,-2528.39, 4660.68, 170.49,'');

-- event scripts for spells that sar'this cast during event, they summon different elementals in process
DELETE FROM `event_scripts` WHERE `id` IN (14856, 14857, 14858, 14859, 14860);
INSERT INTO `event_scripts` VALUES
(14856, 2, 10, 23096, 300000, 0, -2485.68, 4658.75, 162.68, 1.26),
(14857, 2, 10, 23097, 300000, 0, -2443.66, 4634.44, 158.21, 1.20),
(14858, 2, 10, 23098, 300000, 0, -2400.24, 4629.18, 160.22, 3.32),
(14859, 2, 10, 23099, 300000, 0, -2425.67, 4588.09, 159.79, 0.79),    
(14860, 2, 10, 23100, 300000, 0, -2467.59, 4700.11, 155.74, 3.41);