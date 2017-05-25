-- 750
DELETE FROM `creature_loot_template` WHERE `entry` = 20197 AND `item` = 24401;
INSERT INTO `creature_loot_template` VALUES
(20197, 24401, 25, 1, 0, 1, 1);

-- 749
UPDATE `creature` SET `spawntimesecs` = 28800 WHERE `guid` = 66945;
UPDATE `creature` SET `spawntimesecs` = 28800 WHERE `id` = 18685;

-- 454
UPDATE `gameobject` SET `position_x` = -11764.45, `position_y` = -3313.96, `position_z` = 6.76 WHERE `guid` = 16527;

-- 409
DELETE FROM `smart_scripts` WHERE `entryorguid` = 27292 AND `id` = 6;
INSERT INTO `smart_scripts` VALUES
(27292, 0, 6, 0, 1, 0, 100, 0, 300000, 300000, 300000, 300000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Flamebringer - OOC 5mins- Despawn');

-- 287
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_onslaught_warhorse" WHERE `entry` = 27213;

-- 242
UPDATE `quest_template` SET `RequiredRaces` = 690 WHERE `id` = 9820;

-- 209
UPDATE `smart_scripts` SET `action_param1` = 0 WHERE `entryorguid` = 25814 AND `id` = 1; -- 25773;

-- 761
UPDATE `gameobject` SET `position_x` = 796.36, `position_y` = -5150.45, `position_z` = -83.69 WHERE `guid` = 56732;

-- 186
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30422;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30423;

UPDATE `creature_template` SET `AIName` = '', `ScriptName` = "npc_roaming_jormungar" WHERE `entry` = 30422;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = "npc_roaming_jormungar" WHERE `entry` = 30423;

-- 208
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28565 AND `id` = 2;
UPDATE `smart_scripts` SET `id` = 2, `link` = 3 WHERE `entryorguid` = 28565 AND`id` = 3;
INSERT INTO `smart_scripts` VALUES
(28565, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Decaying Ghoul - On Follow Complete - Despawn');  

-- 245
DELETE FROM `conditions` WHERE `SourceEntry` = 25596 AND `ElseGroup` IN (3,4);
INSERT INTO `conditions` VALUES 
(16, 0, 25596, 0, 3, 23, 0, 4027, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 25596, 0, 4, 23, 0, 4143, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone');

-- 762

SET @GUID := (SELECT MAX(guid) from creature) +100; 
DELETE FROM `creature` WHERE `id` IN (25090, 25091, 25092);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`,  `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@GUID   , 25090, 530,   1,  0, 0, 13199.25, -7050.695, 14.45722, 3.700098, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+1 , 25090, 530,   1,  0, 0, 13196.12, -7049.336, 16.22812, 0.8552113, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+2 , 25090, 530,   1,  0, 0, 13274.6, -7057.694, 24.88402, 0.2443461, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+3 , 25090, 530,   1,  0, 0, 13207.01, -7053.201, 15.47437, 2.740167, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+4 , 25090, 530,   1,  0, 0, 13202.56, -7051.397, 16.39847, 4.18879, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+5 , 25090, 530,   1,  0, 0, 13235.61, -7053.926, 15.1975, 5.934119, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+6 , 25090, 530,   1,  0, 0, 13240.7, -7053.23, 14.11119, 4.974188, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+7 , 25090, 530,   1,  0, 0, 13242.16, -7054.788, 17.20347, 4.764749, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+8 , 25091, 530,   1,  0, 0, 13321.43, -6992.023, 15.16358, 1.850049, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+9 , 25091, 530,   1, 0, 0, 13330.63, -6993.74, 18.55262, 0.4537856, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+10, 25091, 530,   1,  0, 0, 13312.74, -6989.042, 16.80069, 3.036873, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+11, 25092, 530,   1,  0, 0, 13332.46, -7149.989, 25.6237, 3.455752, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+12, 25092, 530,   1,  0, 0, 13308.78, -7147.535, 14.74447, 2.6529, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+13, 25092, 530,   1,  0, 0, 13276.29, -7148.312, 18.78717, 5.253441, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+14, 25092, 530,   1,  0, 0, 13323.89, -7149.331, 23.59076, 0.3316126, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+15, 25092, 530,   1,  0, 0, 13315.08, -7149.389, 15.7673, 4.066617, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+16, 25092, 530,   1,  0, 0, 13306.4, -7148.456, 19.44827, 6.126106, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+17, 25092, 530,   1,  0, 0, 13273.84, -7146.333, 11.37591, 0.3141593, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+18, 25092, 530,   1,  0, 0, 13285.6, -7150.727, 20.10993, 5.113815, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@GUID+19, 25092, 530,   1,  0, 0, 13323.48, -7150.049, 19.51648, 2.251475, 300, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (25090, 25091, 25092);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25090, 25091, 25092);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(25090, 0, 0, 1, 8, 0, 100, 0, 45115, 0, 0, 0, 33, 25090, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Sin'Loren Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Give Kill Credit"),
(25090, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 25090, 0, 200, 0, 0, 0, 0, "Sin'Loren Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Set Data to nearby creatures"),
(25090, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 11, 73119, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sin'Loren Credit - On Data Set - Cast spell '[DND] Fire Visual'"),
(25091, 0, 0, 1, 8, 0, 100, 0, 45115, 0, 0, 0, 33, 25091, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Bloodoath Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Give Kill Credit"),
(25091, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 25091, 0, 200, 0, 0, 0, 0, "Bloodoath Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Set Data to nearby creatures"),
(25091, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 11, 73119, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bloodoath Credit - On Data Set - Cast spell '[DND] Fire Visual'"),
(25092, 0, 0, 1, 8, 0, 100, 0, 45115, 0, 0, 0, 33, 25092, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Dawnchaser Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Give Kill Credit"),
(25092, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 9, 25092, 0, 200, 0, 0, 0, 0, "Dawnchaser Credit - On Spellhit 'Quest - Sunwell Daily - Ship Bombing Run Bomb' - Set Data to nearby creatures"),
(25092, 0, 2, 0, 38, 0, 100, 0, 0, 1, 0, 0, 11, 73119, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Dawnchaser Credit - On Data Set - Cast spell '[DND] Fire Visual'");

-- 699
UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI', scriptname='' WHERE `entry` IN (177243, 177365, 177366, 177367, 177368, 177369, 177397, 177398, 177399, 177400);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (177243, 177365, 177366, 177367, 177368, 177369, 177397, 177398, 177399, 177400) AND `source_type`=1;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (17724300, 17736500, 17736600, 17736700, 17736800, 17736900, 17739700, 17739800, 17739900, 17740000) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES

(177243,1,0,0,70,0,100,0,2,0,0,0,80,17724300,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17724300, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17724300, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17724300, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17724300, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177365,1,0,0,70,0,100,0,2,0,0,0,80,17736500,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17736500, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17736500, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736500, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736500, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177366,1,0,0,70,0,100,0,2,0,0,0,80,17736600,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17736600, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17736600, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736600, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736600, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177367,1,0,0,70,0,100,0,2,0,0,0,80,17736700,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17736700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17736700, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736700, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736700, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177368,1,0,0,70,0,100,0,2,0,0,0,80,17736800,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17736800, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17736800, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736800, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736800, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177369,1,0,0,70,0,100,0,2,0,0,0,80,17736900,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17736900, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17736900, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736900, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17736900, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177397,1,0,0,70,0,100,0,2,0,0,0,80,17739700,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17739700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17739700, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739700, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739700, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177398,1,0,0,70,0,100,0,2,0,0,0,80,17739800,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17739800, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17739800, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739800, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739800, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177399,1,0,0,70,0,100,0,2,0,0,0,80,17739900,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17739900, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17739900, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739900, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17739900, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset'),

(177400,1,0,0,70,0,100,0,2,0,0,0,80,17740000,2,0,0,0,0,1,0,0,0,0,0,0,0,'demon portal - on state change - Call Timed ActionList'),
(17740000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 11937, 3, 60000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - summon'),
(17740000, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 99, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17740000, 9, 2, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 70, 300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - despawn'),
(17740000, 9, 3, 0, 0, 0, 100, 0, 30000, 30000, 0, 0, 99, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,'demon portal - ActionList - Reset');

-- 462
UPDATE `creature_template` SET `faction` = 105 WHERE `entry` = 10638;

-- ?? 
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(28217,2821700,2821701);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(28217, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 11, 51329, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Spawn - Cast Feign Death'), 
(28217, 0, 1, 14, 61, 0, 100, 0, 0, 0, 0, 0, 81, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Spawn - Set NPC Flags (Gossip Only)'), 
(28217, 0, 2, 3, 62, 0, 100, 0, 9677, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Say Line 1'), 
(28217, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 28, 51329, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Remove Aura - Feign Death'), 
(28217, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Remove Aura - Set NPC Flags - Quest + Gossip'), 
(28217, 0, 5, 15, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Close Gossip'), 
(28217, 0, 6, 0, 62, 0, 100, 0, 9677, 0, 0, 0, 85, 51382, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Invoker Cast Forcecast Summon Huge Crocolisk'), 
(28217, 0, 7, 0, 64, 0, 100, 0, 0, 0, 0, 0, 98, 9684, 13124, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Hello - Send Gossip Menu'), 
(28217, 0, 8, 10, 62, 0, 100, 0, 9684, 0, 0, 0, 2, 774, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Set Faction (Alliance)'), 
(28217, 0, 9, 10, 62, 0, 100, 0, 9684, 0, 0, 0, 2, 775, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Set Faction (Horde)'), 
(28217, 0, 10, 11, 61, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Store Targetlist'), 
(28217, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2821700, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Option Select - Run Script'), 
(28217, 0, 12, 0, 19, 0, 100, 0, 12570, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On On Quest Accept - Fortunate Misunderstandings - Say Line 2'), 
(28217, 0, 13, 0, 40, 0, 100, 0, 64, 28217, 0, 0, 80, 2821701, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Reached WP80 - Run Script'), 
(28217, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Spawn - Add Aura Permanent Feign Death'), 
(28217, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 28, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Gossip Select - Remove Aura Permanent Feign Death'), 
(2821700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Set NPC Flags'),
(2821700, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Say Line 3'),
(2821700, 9, 2, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 53, 1, 28217, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Start WP'),
(2821701, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script 2 - Say Line 4'),
(2821701, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 51448, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script 2 - Cast Oracle Intro Quest Complete'),
(2821701, 9, 2, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script 2 - Say Line 5'),
(2821701, 9, 3, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 11, 52100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script 2 - Cast Summon Frenyheart Tracker'),
(2821701, 9, 4, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script 2 - Despawn');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9677;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=28217;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 9677, 0, 0, 0, 1, 1, 51329, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if injured rainspeaker oracle has aura Feign Death'),
(15, 9677, 0, 0, 0, 9, 0, 12540, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Just following orders taken'),
(15, 9677, 0, 0, 0, 8, 0, 12570, 0, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Player does not have Fortunate Misunderstandings rewarded'),
(15, 9677, 0, 0, 0,28, 0, 12570, 0, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Player does not have Fortunate Misunderstandings complete'),
(15, 9677, 0, 0, 1, 1, 1, 51329, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if injured rainspeaker oracle has aura Feign Death'),
(15, 9677, 0, 0, 1, 8, 0, 12540, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Just following orders rewarded'),
(15, 9677, 0, 0, 1, 8, 0, 12570, 0, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Player does not have Fortunate Misunderstandings rewarded'),
(15, 9677, 0, 0, 1,28, 0, 12570, 0, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Player does not have Fortunate Misunderstandings complete'),
(22, 7, 28217, 0, 0, 9, 0, 12540, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle - Only run SAI if player has Just Following Orders taken'),
(22, 8, 28217, 0, 0, 9, 0, 12570, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle - Only run SAI if player has Fortunate Misunderstandings Taken'),
(22, 8, 28217, 0, 0, 1, 1, 51329, 0, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle - Only run SAI if Injured rainspeaker oracle does have aura - feign death'),
(22, 9, 28217, 0, 0, 16, 0, 1101, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle - Only run SAI if player is Alliance'),
(22, 10, 28217, 0, 0, 16, 0, 690, 0, 0, 0, 0, 0, '', 'Injured Rainspeaker Oracle - Only run SAI if player is Horde');

-- 775
DELETE FROM `smart_scripts` WHERE `entryorguid` = 7272 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 7269 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(7272, 0, 2, 0, 0, 0, 100, 0, 2000, 2000, 2000, 2000, 45, 1, 1, 0, 0, 0, 0, 11, 7269, 20, 0, 0, 0, 0, 0, 'Theka the Martyr - In Combat - Set Data 1 1 On Nearby Scarab'),
(7269, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 30, 0, 0, 0, 0, 0, 0, 'Scarab - On Data Set 1 1 - Attack Start');

-- 777
UPDATE `creature` SET `position_x` = 1594.438599, `position_y` = -4421.250977, `position_z` = 9.499698 WHERE `guid` = 54742;
UPDATE `smart_scripts` SET `action_type` = 80, `action_param1` = 1484300, `action_param2` = 2 WHERE `entryorguid` = 14843 AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1484300;
INSERT INTO `smart_scripts` VALUES
(1484300, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 5, 94, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Play emote'),
(1484300, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 5, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Play emote');

-- 782
UPDATE `gameobject` SET `position_x` = 830.79, `position_y` = 2228.74, `position_z` = -130.19 WHERE `guid` = 27813;

-- AT Quests p1
-- kuń czasem się buguje
DELETE FROM `conditions` WHERE `SourceEntry` = 63215 AND `ConditionValue1` = 62853;
-- kuń za szybko się rusza
UPDATE `creature_template` SET `speed_run` = 1.14286 WHERE `entry` = 34127;
-- black knight behavior cleanup
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 768 WHERE `entry` = 33785;
UPDATE `smart_scripts` SET `action_param1` = 768  WHERE `entryorguid` = 3378501 AND `id` = 1;
-- black knight combat cleanup
UPDATE `smart_scripts` SET `link` = 4, `event_param1` = 5, `event_param3` = 5000, `event_param4` = 7000 WHERE `entryorguid` = 33785 AND `id` = 5;
UPDATE `smart_scripts` SET `event_type` = 61, `event_param1` = 0,  `event_param2` = 0, `event_param3` = 0, `event_param4` = 0 WHERE `entryorguid` = 33785 AND `id` = 4;

-- AT Quests p2
DELETE FROM `event_scripts` WHERE `id` IN (21077, 21076, 21075);
INSERT INTO `event_scripts` VALUES
(21077, 0, 10, 33439, 20000, 0, 8461.75, 468.926, 596.072, 4.6392),
(21076, 0, 10, 33457, 20000, 0, 8471.46, 452.336, 596.071, 4.71),
(21076, 0, 9, 67923, 20, 0, 0, 0, 0, 0),
(21075, 0, 10, 33455, 20000, 0, 8441.06, 452.919, 596.07, 1.643);

DELETE FROM `creature_template_addon` WHERE `entry` IN (33439, 33455, 33457);
INSERT INTO `creature_template_addon` VALUES 
(33439, 0, 0, 3, 0, 0, '59216'),
(33455, 0, 0, 3, 0, 0, '41290'),
(33457, 0, 0, 3, 0, 0, '');