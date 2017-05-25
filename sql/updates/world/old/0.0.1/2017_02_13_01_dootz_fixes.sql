DELETE FROM `smart_scripts` WHERE `entryorguid` = 2821700 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(2821700, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Script End - Add Aura Feign Death');

UPDATE `gameobject` SET `position_x` = -8426.16, `position_y` = 607.4, `position_z` = 94.55 WHERE `guid` = 13813;
UPDATE `quest_template` SET `RequiredSkillId` = 393, `RequiredSkillPoints` = 1 WHERE `id` = 768;
UPDATE `smart_scripts` SET `target_type` = 18 WHERE `entryorguid` IN(32577,32578,32579,32580)  AND `id` = 2;
UPDATE `smart_scripts` SET `target_type` = 18 WHERE `entryorguid` = 32576 AND `id` = 11; 

SET @WMEAT:= 43010;
SET @CMEAT:= 43013;
SET @RELIC:= 42780;
SET @CLOTH:= 33470;
DELETE FROM `creature_loot_template` WHERE `entry` IN(30291,30422) AND `item` IN(@CMEAT, @WMEAT);
DELETE FROM `creature_loot_template` WHERE `entry` IN(30222, 29974) AND `item` IN(@RELIC, @CLOTH);
DELETE FROM `creature_loot_template` WHERE `entry` = 30260 AND `item` IN(34736, @CMEAT);
DELETE FROM `creature_loot_template` WHERE `entry` = 30160 AND `item` IN(37701, @RELIC);
DELETE FROM `creature_loot_template` WHERE `entry` = 30387 AND `item` IN(37702, @RELIC);
INSERT INTO `creature_loot_template` VALUES
(30291, @WMEAT, 52, 1, 0, 1, 1),
(30291, @CMEAT, 14, 1, 0, 1, 1),
(30222, @RELIC, 42, 1, 0, 1, 1),
(30222, @CLOTH, 30, 1, 0, 1, 4),
(30260, 34736, 52, 1, 0, 1, 1),
(30260, @CMEAT, 14, 1, 0, 1, 1),
(30422, @WMEAT, 52, 1, 0, 1, 1),
(30422, @CMEAT, 14, 1, 0, 1, 1),
(29974, @RELIC, 42, 1, 0, 1, 1),
(29974, @CLOTH, 30, 1, 0, 1, 4),
(30160, 37701, 26, 1, 0, 1, 2),
(30160, @RELIC, 34, 1, 0, 1, 1),
(30387, 37702, 25, 1, 0, 1, 2),
(30387, @RELIC, 33, 1, 0, 1, 1);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (32682, 27932);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (32682, 27932) AND `source_type`=0;
UPDATE `creature_template` SET `InhabitType`=4, `speed_run`=2.5 WHERE `entry` IN (32682, 27932);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(32682, 0, 0, 0, 27, 0, 100, 1, 0, 0, 0, 0, 53, 1, 32682, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'Harry''s Bomber- On passeger rided - Start wp'),
(27932, 0, 0, 0, 27, 0, 100, 1, 0, 0, 0, 0, 53, 1, 27932, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'Harry''s Bomber- On passeger rided - Start wp'),
(32682, 0, 1, 0, 58, 0, 100, 1, 9, 32682, 0, 0, 11, 50630, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'Harry''s Bomber- On waypoint ended - Eject passengers'),
(27932, 0, 1, 0, 58, 0, 100, 1, 9, 27932, 0, 0, 11, 50630, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'Harry''s Bomber- On passeger ended - Eject passengers');

UPDATE `smart_scripts` SET `action_type`=85 WHERE `entryorguid`=28277 AND `source_type`=0 AND `id`=0;
DELETE FROM `waypoints` WHERE `entry` IN (32682, 27932);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(32682, 1, 61.83957, -6228.992, 19.07242, 'Harry''s Bomber'),
(32682, 2, -64.6518, -5908.95, 29.8502, 'Harry''s Bomber'),
(32682, 3, -158.0859, -5631.193, 29.8502, 'Harry''s Bomber'),
(32682, 4, -436.5865, -5223.862, 32.1002, 'Harry''s Bomber'),
(32682, 5, -412.989, -5012.779, 45.7391, 'Harry''s Bomber'),
(32682, 6, -75.09814, -4341.288, 64.29379, 'Harry''s Bomber'),
(32682, 7, -51.86116, -4023.003, 70.12712, 'Harry''s Bomber'),
(32682, 8, -136.1673, -3716.832, 59.96046, 'Harry''s Bomber'),
(32682, 9, -170.8945, -3578.378, 4.988236, 'Harry''s Bomber'),
(27932, 1, -136.1673, -3716.832, 59.96046, 'Harry''s Bomber'),
(27932, 2, -51.86116, -4023.003, 70.12712, 'Harry''s Bomber'),
(27932, 3, -75.09814, -4341.288, 64.29379, 'Harry''s Bomber'),
(27932, 4, -412.989, -5012.779, 45.7391, 'Harry''s Bomber'),
(27932, 5, -436.5865, -5223.862, 32.1002, 'Harry''s Bomber'),
(27932, 6, -158.0859, -5631.193, 29.8502, 'Harry''s Bomber'),
(27932, 7, -64.6518, -5908.95, 29.8502, 'Harry''s Bomber'),
(27932, 8, 61.83957, -6228.992, 19.07242, 'Harry''s Bomber'),
(27932, 9, 89.63259, -6287.430, -0.739605, 'Harry''s Bomber');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=10218;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`Scriptname`,`Comment`) VALUES
(15,10218,0,0,0,23,0,495,0,0,0,0 ,'' , 'Harry''s Bomber - Show gossip option if the npc is in the area 495'),
(15,10218,0,0,0,9,0,11567,0,0,0,0 ,'' , 'Harry''s Bomber - Show gossip option if player has taken quest 11567'),
(15,10218,0,0,1,28,0,11567,0,0,0,0 ,'' , 'Harry''s Bomber - Show gossip option if player has quest 11567 completed');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN(46316, 46317);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 17 AND `SourceEntry` = 46315;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 46317, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0,'' ,'mammoth spell cannot attack player'),
(13, 1, 46316, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0,'' ,'mammoth spell cannot attack player'),
(17, 0, 46315, 0, 0, 31, 1, 4, 0, 0, 1, 0, 0, '','mammoth spell cannot attack player');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 27131;
INSERT INTO `smart_scripts` VALUES 
(27131, 0, 0, 0, 1, 0, 100, 0, 10000, 15000, 10000, 15000, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Grizzly Bear - Out of Combat - Play Emote 7');

SET @CGUID = NULL;

DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` VALUES
(@CGUID, 15351, 571, 1,1, 0, 0, 5647.18, 805.28, 653.69, 5.69, 300, 0, 0, 30520, 0, 0, 0, 0, 0);

UPDATE `creature` SET `equipment_id` = 1 WHERE `id` = 16904;
UPDATE `creature` SET `equipment_id` = 1 WHERE `id` = 16906;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=58151;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(17, 0, 58151, 0, 0, 31, 1, 3, 30894, 0, 0, 12, 0, '', 'Subdued Lithe Stalker - only for Lithe Stalker'),
(17, 0, 58151, 0, 0, 38, 1, 30, 4, 0, 0, 0, 0, '', 'Subdued Lithe Stalker - only if target HP >=30');

SET @GUID := (SELECT MAX(guid) from creature) +100; 

UPDATE `creature_template` SET  `AIName`='SmartAI' WHERE `entry`=6492;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (6492, 649200);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6492, 0, 1, 2, 8, 0, 100, 0, 9095, 0, 0, 0, 28, 34426, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Spellhit - Remove Aura'),
(6492, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 28, 9095, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Spellhit - Remove Aura'),
(6492, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 11, 9096, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Spellhit - Cast Rift Spawn Manifestation'),
(6492, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Spellhit - Attack ActionInvoker'),
(6492, 0, 5, 6, 11, 0, 100, 0, 0, 0, 0, 0, 11, 34426, 19, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on spawn - add aura'),
(6492, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 19, 33685508, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On spawn - remove Flag'),
(6492, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 42, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on Spawn - Set Invincible HP'),
(6492, 0, 8, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 34426, 19, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on reset - add aura'),
(6492, 0, 9, 10, 2, 0, 100, 1, 0, 1, 0, 0, 18, 33685508, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on 1% HP - add flag'),
(6492, 0, 10, 11, 61, 0, 100, 0, 0, 0, 0, 0, 11, 9032, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On On 1% HP - Cast Self Stun - 30 seconds'),
(6492, 0, 11, 12, 61, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On 1% HP - Set Phase 2'),
(6492, 0, 12, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 31000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On 1% HP - despawn'),
(6492, 0, 13, 14, 38, 0, 100, 0, 1, 1, 0, 0, 12, 23837, 1, 15000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on data 1|1 - Spawn ELM General Purpose Bunny'),
(6492, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 32, 32, 0, 0, 0, 0, 19, 23837, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On 1% HP - Set Data ELM General Purpose Bunny'),
(6492, 0, 15, 0, 38, 0, 100, 0, 2, 2, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on data 2|2 - Set Invisible'),
(6492, 0, 16, 0, 25, 0, 100, 0, 0, 0, 0, 0, 19, 33685508, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - on reset - remove aura'),
(6492, 0, 17, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Aggro - Say Line 0'),
(6492, 0, 18, 0, 7, 2, 100, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rift Spawn - On Evade (Phase 2)  - Say line 1');

DELETE FROM `creature_text` WHERE `entry`=6492;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(6492, 0, 0, '%s is angered and attacks!', 16, 0, 100, 0, 0, 0, 'Rift Spawn'),
(6492, 1, 0, '%s escapes into the void!', 16, 0, 100, 0, 0, 0, 'Rift Spawn');

UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry`=122088;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (122088, 12208800);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(122088, 1, 0, 0, 1, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 6492, 1, 0, 0, 0, 0, 0, 'Containment Coffer - On reset - Set data to Rift Spawn'),
(122088, 1, 1, 0, 1, 0, 100, 1, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 6492, 1, 0, 0, 0, 0, 0, 'Containment Coffer - On reset - Set data to Rift Spawn'),
(122088, 1, 2, 0, 1, 0, 100, 1, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Containment Coffer - On reset - activate self'),
(122088, 1, 3, 0, 1, 0, 100, 1, 4000, 4000, 4000, 4000, 44, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Containment Coffer - On reset - set phasemask');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=6492;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(22, 14, 6492, 0, 0, 38, 1, 1, 4, 0, 0, 0, 0, '', 'Rift Spawn - Only run SAI if Rift Spawn hp at 1% or lower'),
(22, 13, 6492, 0, 0, 38, 1, 1, 4, 0, 0, 0, 0, '', 'Rift Spawn - Only run SAI if Rift Spawn hp at 1% or lower'),
(22, 14, 6492, 0, 0, 1, 1, 9032, 0, 0, 0, 0, 0, '', 'Rift Spawn - Only run SAI if Rift Spawn is stuned'),
(22, 13, 6492, 0, 0, 1, 1, 9032, 0, 0, 0, 0, 0, '', 'Rift Spawn - Only run SAI if Rift Spawn is stuned');

DELETE FROM `smart_scripts` WHERE `entryorguid`=23837 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(23837, 0, 2, 0, 38, 0, 100, 1, 32, 32, 0, 0, 11, 9010, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'ELM General Purpose Bunny - On Data Set - Cast Create Filled Containment Coffer');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=9082;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 9082, 0, 0, 29, 0, 6492, 10, 0, 0, 0, 0, '', 'Create Containment Coffer can only be cast if there is rift spawn near');

DELETE FROM `creature` WHERE `id`=6492 AND `guid` BETWEEN @GUID AND @GUID+7;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- Undercity
(@GUID, 6492, 0, 1, 1, 0, 0, 1414.51, 365.095, -66.0066, 4.99293, 300, 0, 0, 386, 0, 0, 0, 0, 0),
(@GUID+1, 6492, 0, 1, 1, 0, 0, 1406.47, 369.853, -66.0231, 5.29334, 300, 0, 0, 356, 0, 0, 0, 0, 0),
(@GUID+2, 6492, 0, 1, 1, 0, 0, 1400.28, 366.915, -66.0388, 5.57844, 300, 0, 0, 386, 0, 0, 0, 0, 0),
(@GUID+3, 6492, 0, 1, 1, 0, 0, 1399.22, 362.385, -66.0382, 5.77244, 300, 0, 0, 386, 0, 0, 0, 0, 0),
-- Stormwind
(@GUID+4, 6492, 0, 1, 1, 0, 0, -9090.34, 834.40, 115.667, 0.221248, 300, 0, 0, 356, 0, 0, 0, 0, 0),
(@GUID+5, 6492, 0, 1, 1, 0, 0, -9082.4, 817.728, 115.667, 5.614612, 300, 0, 0, 386, 0, 0, 0, 0, 0),
(@GUID+6, 6492, 0, 1, 1, 0, 0, -9108.138, 828.56, 97.6289, 0.656658, 300, 0, 0, 386, 0, 0, 0, 0, 0),
(@GUID+7, 6492, 0, 1, 1, 0, 0, -9096.921, 839.302, 97.6289, 4.270519, 300, 0, 0, 386, 0, 0, 0, 0, 0);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 19294 AND `id` = 4;
INSERT INTO `smart_scripts` VALUES
(19294, 0, 4, 0, 25, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Earthbinder Galandria Nightbreeze - On Reset - Set NPC Flags');

SET @ENTRY := 3430;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 20, 0, 100, 0, 5043, 0, 0, 0, 11, 17013, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell'),
(@ENTRY, 0, 1, 0, 20, 0, 100, 0, 5042, 0, 0, 0, 11, 16612, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell'),
(@ENTRY, 0, 2, 0, 20, 0, 100, 0, 5046, 0, 0, 0, 11, 16610, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell'),
(@ENTRY, 0, 3, 0, 20, 0, 100, 0, 5045, 0, 0, 0, 11, 10767, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell'),
(@ENTRY, 0, 4, 0, 20, 0, 100, 0, 889, 0, 0, 0, 11, 16618, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell'),
(@ENTRY, 0, 5, 0, 20, 0, 100, 0, 5044, 0, 0, 0, 11, 7764, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Agamaggan - On Quest Reward - Cast Spell');

DELETE FROM `creature_formations` WHERE `leaderGUID` IN(125886,125889,125891,126029,125995);
INSERT INTO `creature_formations` VALUES
(125886, 125886, 0, 0, 2, 0, 0),
(125886, 126051, 0, 0, 2, 0, 0),
(125886, 125994, 0, 0, 2, 0, 0),
(125886, 125993, 0, 0, 2, 0, 0),

(125889, 125892, 0, 0, 2, 0, 0),
(125889, 125997, 0, 0, 2, 0, 0),
(125889, 125996, 0, 0, 2, 0, 0),
(125889, 125889, 0, 0, 2, 0, 0),

(125891, 125891, 0, 0, 2, 0, 0),
(125891, 125887, 0, 0, 2, 0, 0),
(125891, 126038, 0, 0, 2, 0, 0),
(125891, 125888, 0, 0, 2, 0, 0),

(126029, 126036, 0, 0, 2, 0, 0),
(126029, 126037, 0, 0, 2, 0, 0),
(126029, 126045, 0, 0, 2, 0, 0),
(126029, 126029, 0, 0, 2, 0, 0),

(125995, 125995, 0, 0, 2, 0, 0),
(125995, 126028, 0, 0, 2, 0, 0),
(125995, 126035, 0, 0, 2, 0, 0),
(125995, 126044, 0, 0, 2, 0, 0);