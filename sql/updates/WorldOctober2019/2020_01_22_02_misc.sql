-- DB/Quest: Escape Through Force - add post-quest event with Sentinel Selarin - based on Rushor\'s work https://github.com/SunwellTracker/issues/issues/2797
UPDATE `creature_template` SET `speed_walk`=1 WHERE  `entry`=3694;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `Id`=990;
-- Terenthis SAI
SET @ENTRY := 3693;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,995,0,0,0,12,3694,6,180000,0,0,0,8,0,0,0,6339.14,341.764,24.3387,0.498114,"Terenthis - On Quest 'Escape Through Stealth' Finished - Summon Creature 'Sentinel Selarin'"),
(@ENTRY,0,1,0,20,0,100,0,994,0,0,0,12,3694,6,180000,0,0,0,8,0,0,0,6339.14,341.764,24.3387,0.498114,"Terenthis - On Quest 'Escape Through Force' Finished - Summon Creature 'Sentinel Selarin'");

-- Sentinel Selarin SAI
DELETE FROM `waypoints` WHERE `entry`=3694;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(3694, 1, 6339.14,341.764,24.3387, 'Sentinel Selarin'),
(3694, 2, 6353.39,354.557,22.3779, 'Sentinel Selarin'),
(3694, 3, 6368.99,357.894,21.5712, 'Sentinel Selarin'),
(3694, 4, 6387.81,359.455,18.9899, 'Sentinel Selarin'),
(3694, 5, 6398.12,363.588,17.366, 'Sentinel Selarin'),
(3694, 6, 6403.68,370.92,15.6815, 'Sentinel Selarin'),
(3694, 7, 6416.57,392.998,12.0215, 'Sentinel Selarin'),
(3694, 8, 6424.95,399.193,10.9586, 'Sentinel Selarin'),
(3694, 9, 6428.93,396.971,11.1736, 'Sentinel Selarin'),
(3694, 10, 6432,388.708,13.7662, 'Sentinel Selarin'),
(3694, 11, 6436.71,375.264,13.9403, 'Sentinel Selarin'),
(3694, 12, 6434.92,367.203,13.9403, 'Sentinel Selarin'), 
(3694, 13, 6436.9,374.833,13.9403, 'Sentinel Selarin'),
(3694, 14, 6431.63,389.723,13.5875, 'Sentinel Selarin'),
(3694, 15, 6428.84,397.45,11.0941, 'Sentinel Selarin'),
(3694, 16, 6424,400.084,10.9784, 'Sentinel Selarin'),
(3694, 17, 6413.76,392.804,12.2825, 'Sentinel Selarin'),
(3694, 18, 6401.4,368.195,16.4249, 'Sentinel Selarin'),
(3694, 19, 6393.69,360.887,18.1549, 'Sentinel Selarin'),
(3694, 20, 6377.21,357.731,20.6589, 'Sentinel Selarin'),
(3694, 21, 6358.35,357.353,22.2106, 'Sentinel Selarin'),
(3694, 22, 6348.45,352.662,22.6056, 'Sentinel Selarin'),
(3694, 23, 6322.42,326.649,25.3338, 'Sentinel Selarin');

SET @ENTRY := 3694;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,2,54,0,100,0,0,0,0,0,53,1,3694,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Just Summoned - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,23,3694,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Waypoint 23 Reached - Despawn Instant"),
(@ENTRY,0,2,5,61,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Just Summoned - Set Active On"),
(@ENTRY,0,3,0,40,0,100,0,1,3694,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Waypoint 1 Reached - Run Script"),
(@ENTRY,0,4,6,40,0,100,0,12,3694,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Waypoint 12 Reached - Run Script"),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Just Summoned - Remove Npc Flags Gossip & Questgiver");

-- Actionlist SAI
SET @ENTRY := 369400;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Script - Pause Waypoint"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Script - Set Run On");

-- Actionlist SAI 
SET @ENTRY := 369401;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,54,60000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - On Script - Pause Waypoint"),
(@ENTRY,9,1,0,0,0,100,0,1000,1000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.6089,"Sentinel Selarin - Set Orientation 4,6089"),
(@ENTRY,9,2,0,0,0,100,0,3000,3000,0,0,1,0,4000,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - Say Line 0"),
(@ENTRY,9,3,0,0,0,100,0,5000,5000,0,0,1,15,5000,0,0,0,0,19,3693,30,0,0,0,0,0,"Sentinel Selarin - Say Line 15"),
(@ENTRY,9,4,0,0,0,100,0,5000,500,0,0,1,1,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - Say Line 1"),
(@ENTRY,9,5,0,0,0,100,0,5000,5000,0,0,1,2,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - Say Line 2"),
(@ENTRY,9,6,0,0,0,100,0,0,0,0,0,82,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sentinel Selarin - Add Npc Flags Gossip & Questgiver");

DELETE FROM `creature_text` WHERE `entry`=3694;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(3694, 0, 0, 'Terenthis, Raene sent me to find you. The Sentinels are in need of help in Ashenvale.', 12, 7, 100, 0, 0, 0, 'Sentinel Selarin'),
(3694, 1, 0, 'Thank you, Terenthis. I shall remain here for as long as I can.', 12, 7, 100, 0, 0, 0, 'Sentinel Selarin'),
(3694, 2, 0, 'Hopefully I can send a worthy few to help Ashenvale and the Sentinels.', 12, 7, 100, 0, 0, 0, 'Sentinel Selarin'),
(3694, 3, 0, 'Thank you again, Terenthis. I shall return again if more help is needed. Until then, please send more adventurers to Ashenvale', 12, 7, 100, 0, 0, 0, 'Sentinel Selarin');


DELETE FROM `creature_text` WHERE `entry`=3693 AND `groupid`=15;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(3693, 15, 0, 'I understand, my friend. I shall find someone to help your master. Go back to him now, or at least stay close.', 12, 0, 0, 0, 0, 0, 0, 'Terenthis');
