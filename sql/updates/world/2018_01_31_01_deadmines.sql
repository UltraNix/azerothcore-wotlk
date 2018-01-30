-- Rhahk'zor
DELETE FROM `smart_scripts` WHERE `entryorguid`=644 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_rhahkzor" WHERE `entry`=644;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 101831;
UPDATE `gameobject_template` SET `AIName`="", `ScriptName`="go_deadmines_lever_first_boss" WHERE `entry`=101831;
-- Sneed
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (642, 643) AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_sneed" WHERE `entry`=643;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_sneed_shredder" WHERE `entry`=642;
-- Gilnid
DELETE FROM `smart_scripts` WHERE `entryorguid`=1763 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_gilnid" WHERE `entry`=1763;
-- Mr Smite
DELETE FROM `creature_template_addon` WHERE `entry`=646;
UPDATE `creature_text` SET `type`=12 WHERE `entry`=646 AND `groupid` IN (2, 3);
-- Captain Greenskin
DELETE FROM `smart_scripts` WHERE `entryorguid`=647 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_captain_greenskin" WHERE `entry`=647;
-- Cookie
DELETE FROM `smart_scripts` WHERE `entryorguid`=645 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_cookie" WHERE `entry`=645;
-- Edwin Valcleef
DELETE FROM `smart_scripts` WHERE `entryorguid`=639 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_edwin_vancleef" WHERE `entry`=639;
-- Cannon Event
UPDATE `gameobject_template` SET `AIName`="", `ScriptName`="go_deadmines_defias_cannon" WHERE `entry`=16398;
DELETE FROM `creature_summon_groups` WHERE `summonerId`=16398 AND `summonerType`=1;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`) VALUES
(16398, 1, 1, 1732, -90.2, -708.74, 8.88, 1.74, 8),
(16398, 1, 1, 1732, -100.73, -709.36, 8.96, 1.58, 8);
-- Defias Blackguard (Aggro Smite)
SET @GUID := -79346;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,0,0,1,0,100,1,0,0,0,0,11,6408,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - Out of Combat - Cast 'Faded' (No Repeat)"),
(@GUID,0,1,2,4,0,100,0,0,0,0,0,11,1833,0,0,0,0,0,7,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Cast 'Cheap Shot'"),
(@GUID,0,2,3,61,0,100,0,0,0,0,0,28,6408,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Remove Aura 'Faded'"),
(@GUID,0,3,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Say Line 0"),
(@GUID,0,4,0,0,0,100,0,3000,10000,10000,15000,11,14903,1,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - In Combat - Cast 'Rupture'"),
(@GUID,0,5,0,4,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,79337,646,0,0,0,0,0,"Defias Blackguard - On Aggro - Set Data 1 1");
SET @GUID := -79345;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,0,0,1,0,100,1,0,0,0,0,11,6408,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - Out of Combat - Cast 'Faded' (No Repeat)"),
(@GUID,0,1,2,4,0,100,0,0,0,0,0,11,1833,0,0,0,0,0,7,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Cast 'Cheap Shot'"),
(@GUID,0,2,3,61,0,100,0,0,0,0,0,28,6408,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Remove Aura 'Faded'"),
(@GUID,0,3,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - On Aggro - Say Line 0"),
(@GUID,0,4,0,0,0,100,0,3000,10000,10000,15000,11,14903,1,0,0,0,0,1,0,0,0,0,0,0,0,"Defias Blackguard - In Combat - Cast 'Rupture'"),
(@GUID,0,5,0,4,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,79337,646,0,0,0,0,0,"Defias Blackguard - On Aggro - Set Data 1 1");
