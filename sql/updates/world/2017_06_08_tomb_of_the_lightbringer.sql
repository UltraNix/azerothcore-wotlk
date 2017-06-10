-- Creature text
DELETE FROM `creature_text` WHERE `entry`=17238;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(17238, 0, 0, "Shall we begin, my friend?", 12, 7, 100, 6, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 1, 0, "This area is known to be full of foul Scourge.  You may want to take a moment to prepare any defenses at your disposal.", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 2, 0, "Beware!  We are attacked!", 12, 7, 100, 5, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 3, 0, "It must be the purity of the Mark of the Lightbringer that is drawing forth the Scourge to us.  We must proceed with caution lest we be overwhelmed!", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 4, 0, "We are beset upon again! Defend yourself!", 12, 7, 100, 5, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 5, 0, "This land truly needs to be cleansed by the Light!  Let us continue on to the tomb.  It isn't far now.", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 6, 0, "Very well, let us continue.", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17238, 7, 0, "Thank you my friend for making this possible.  This is a day that I shall never forget!  I think I will stay a while.  Please return to High Priestess MacDonnell at the camp.  I know that she'll be keenly interested to know of what has transpired here.", 12, 7, 100, 2, 0, 0, 0, "Q Tomb of the Lightbringer");
DELETE FROM `creature_text` WHERE `entry`=17233 AND `groupid` IN (4, 5);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(17233, 4, 0, "Thank you for coming here in remembrance of me. Your efforts in recovering that symbol while unnecessary, are certainly touching to an old man's heart.", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer"),
(17233, 5, 0, "Please, rise my friend. Keep the Blessing as a symbol of the strength of the Light and how heroes long gone might once again rise in each of us to inspire.", 12, 7, 100, 1, 0, 0, 0, "Q Tomb of the Lightbringer");

-- Anchorite Truuen SAI
SET @ENTRY := 17238;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,19,0,100,0,9446,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Quest 'Tomb of the Lightbringer' Taken - Say Line 0"),
(@ENTRY,0,1,2,61,0,100,0,9446,0,0,0,53,0,17238,0,9446,45000,1,17,0,30,0,0,0,0,0,"Anchorite Truuen - On Quest 'Tomb of the Lightbringer' Taken - Start Waypoint"),
(@ENTRY,0,2,3,61,0,100,0,9446,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Quest 'Tomb of the Lightbringer' Taken - Pause Waypoint"),
(@ENTRY,0,3,18,61,0,100,0,9446,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Quest 'Tomb of the Lightbringer' Taken - Set Npc Flag "),
(@ENTRY,0,4,5,40,0,100,0,3,0,0,0,54,15000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 3 Reached - Pause Waypoint"),
(@ENTRY,0,5,0,61,0,100,0,3,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 3 Reached - Say Line 1"),
(@ENTRY,0,6,7,40,0,100,0,5,0,0,0,12,4472,3,60000,1,0,0,8,0,0,0,1039.98,-1577.66,61.437,1.75395,"Anchorite Truuen - On Waypoint 5 Reached - Summon Creature 'Haunting Vision'"),
(@ENTRY,0,7,8,61,0,100,0,5,0,0,0,12,1802,3,60000,1,0,0,8,0,0,0,1031.03,-1576.28,62.436,0.265621,"Anchorite Truuen - On Waypoint 5 Reached - Summon Creature 'Hungering Wraith'"),
(@ENTRY,0,8,0,61,0,100,0,5,0,0,0,1,2,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 5 Reached - Say Line 2"),
(@ENTRY,0,9,0,40,0,100,0,7,0,0,0,1,3,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 7 Reached - Say Line 3"),
(@ENTRY,0,10,11,40,0,100,0,11,0,0,0,1,4,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 11 Reached - Say Line 4"),
(@ENTRY,0,11,12,61,0,100,0,11,0,0,0,12,4475,3,60000,1,0,0,8,0,0,0,1110.66,-1742.14,61.019,2.41369,"Anchorite Truuen - On Waypoint 11 Reached - Summon Creature 'Blighted Zombie'"),
(@ENTRY,0,12,13,61,0,100,0,11,0,0,0,12,4475,3,60000,1,0,0,8,0,0,0,1106.84,-1750.59,61.174,2.40976,"Anchorite Truuen - On Waypoint 11 Reached - Summon Creature 'Blighted Zombie'"),
(@ENTRY,0,13,14,61,0,100,0,11,0,0,0,12,4475,3,60000,1,0,0,8,0,0,0,1111.72,-1753.4,61.459,2.75534,"Anchorite Truuen - On Waypoint 11 Reached - Summon Creature 'Blighted Zombie'"),
(@ENTRY,0,14,0,61,0,100,0,11,0,0,0,12,4475,3,60000,1,0,0,8,0,0,0,1117.46,-1743.33,61,2.85351,"Anchorite Truuen - On Waypoint 11 Reached - Summon Creature 'Blighted Zombie'"),
(@ENTRY,0,15,0,40,0,100,0,12,0,0,0,1,5,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 12 Reached - Say Line 5"),
(@ENTRY,0,16,17,40,0,100,0,17,0,0,0,12,17233,3,60000,0,0,0,8,0,0,0,971.86,-1825.42,84,0,"Anchorite Truuen - On Waypoint 17 Reached - Summon Creature 'Ghost of Uther Lightbringer'"),
(@ENTRY,0,17,0,61,0,100,0,17,0,0,0,90,8,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 17 Reached - Set Flag Standstate Kneel"),
(@ENTRY,0,18,0,61,0,100,0,9446,0,0,0,2,250,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Quest 'Tomb of the Lightbringer' Taken - Set Faction 250"),
(@ENTRY,0,19,0,40,0,100,0,3,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Waypoint 3 Reached - Run Script"),
(@ENTRY,0,20,0,38,0,100,0,0,1,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Data Set 0 1 - Run Script");
-- Actionlist SAI
SET @ENTRY := 1723800;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,15000,15000,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Script - Say Line 6");
-- Actionlist SAI
SET @ENTRY := 1723801;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Script - Remove Flag Standstate Kneel"),
(@ENTRY,9,1,0,0,0,100,0,10000,10000,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Script - Say Line 7"),
(@ENTRY,9,2,0,0,0,100,0,12000,12000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anchorite Truuen - On Script - Despawn Instant");
-- Ghost of Uther Lightbringer SAI
SET @ENTRY := 17233;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Just Summoned - Run Script");
-- Actionlist SAI
SET @ENTRY := 1723300;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,4000,4000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Script - Say Line 4"),
(@ENTRY,9,1,0,0,0,100,0,9000,9000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Script - Say Line 5"),
(@ENTRY,9,2,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,17238,20,0,0,0,0,0,"Ghost of Uther Lightbringer - On Script - Set Data 0 1"),
(@ENTRY,9,3,0,0,0,100,0,8000,8000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Script - Despawn Instant");

-- Waypoints
DELETE FROM `waypoints` WHERE `entry`=17238;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(17238, 1, 946, -1430, 64, "quest9446"),
(17238, 2, 974, -1439, 66, "quest9446"),
(17238, 3,  1031, -1474, 64, "quest9446"),
(17238, 4,  1039, -1503, 66, "quest9446"),
(17238, 5,  1036, -1566, 62, "quest9446"),
(17238, 6,  1036, -1568, 62, "quest9446"),
(17238, 7,  1038, -1662, 61, "quest9446"),
(17238, 8,  1047, -1683, 61, "quest9446"),
(17238, 9,  1064, -1710, 61, "quest9446"),
(17238, 10,  1099, -1738, 61, "quest9446"),
(17238, 11,  1113, -1746, 61, "quest9446"),
(17238, 12,  1118, -1750, 61, "quest9446"),
(17238, 13,  1156, -1761, 61, "quest9446"),
(17238, 14,  1152, -1773, 61, "quest9446"),
(17238, 15,  1080, -1802, 65, "quest9446"),
(17238, 16,  1019, -1810, 78, "quest9446"),
(17238, 17,  976, -1823, 81, "quest9446");
