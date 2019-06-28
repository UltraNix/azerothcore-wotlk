-- DB/Creature: Add missing spawns in Onslaught Harbor 
-- DB/Creature: make Troll Roof Stalker immune to Mind Control 
--  DB/SAI: add spell Blinding Swarm and associated emote to Nerub'ar Web Lord
--  DB/SAI: fix out-of-combat event for Warsong Peon in Warsong Hold (Borean Tundra)
-- DB/SAI: add out-of-combat text for Brother Keltan and Absalan the Pious
--  DB/Creature: NPCs Rork Sharpchin and Olut Alegut can only sell their items if the related quests are rewarded
-- DB/Loot: remove wrong loot from Young Nightsaber 
-- DB/SAI: fix on-accept event for quest Help for Camp Winterhoof
--  DB/SAI: Add spell Hoof Strike to Highland Mustang, Frosthorn Ram and Onslaught Destrier
DELETE FROM `gameobject` WHERE `guid` IN(279413,279414,279415) AND `id` IN (192474,192475,192473);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(279413, 192474, 571, 1, 1, 7370.37, 4879.1, 1.0929, 2.92342, 0, 0, 0.994056, 0.10887, 300, 255, 1),
(279414, 192475, 571, 1, 1, 7362.43, 4853.38, 0.244615, 2.86233, 0, 0, 0.990267, 0.139178, 300, 255, 1),
(279415, 192473, 571, 1, 1, 7816.62, 4705.44, 0.338167, 1.57952, 0, 0, 0.710184, 0.704016, 300, 255, 1);

DELETE FROM `creature` WHERE `guid` IN (111106, 111111, 111112, 111127, 111128, 111129, 111130, 111131, 111132, 111133, 111134, 111135, 111136, 111138, 111139, 111141, 111142, 111144, 111167) AND `id` IN (29330,29338,29329);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(111106, 29330, 571, 1, 1, 0, 1, 7369.12, 4869.77, 1.72863, 2.74042, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111111, 29330, 571, 1, 1, 0, 1, 7367.12, 4866.47, 1.70856, 2.74042, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111112, 29330, 571, 1, 1, 0, 1, 7366.77, 4862.94, 2.58352, 2.74042, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111127, 29338, 571, 1, 1, 0, 1, 7370.76, 4863.02, 2.46999, 2.58353, 300, 0, 0, 10080, 8814, 0, 0, 0, 0),
(111128, 29338, 571, 1, 1, 0, 1, 7372.27, 4866.47, 1.96164, 2.77233, 300, 0, 0, 10080, 8814, 0, 0, 0, 0),
(111129, 29330, 571, 1, 1, 0, 1, 7333.77, 4832.87, 1.18764, 0.376084, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111130, 29330, 571, 1, 1, 0, 1, 7334.38, 4836.51, 0.922947, 5.90293, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111131, 29338, 571, 1, 1, 0, 1, 7339.65, 4837.68, 1.03617, 4.38083, 300, 0, 0, 9740, 8636, 0, 0, 0, 0),
(111132, 29329, 571, 1, 1, 0, 1, 7338.27, 4829.94, 1.56251, 1.45297, 300, 0, 0, 12175, 3893, 0, 0, 0, 0),
(111133, 29330, 571, 1, 1, 0, 1, 7342.16, 4832.92, 1.49471, 2.96879, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111134, 29330, 571, 1, 1, 0, 1, 7370.51, 4905.15, 2.21898, 3.19985, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111135, 29330, 571, 1, 1, 0, 1, 7369.92, 4898.99, 1.87871, 2.54012, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111136, 29330, 571, 1, 1, 0, 1, 7362.2, 4904.13, 1.56021, 5.90006, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111138, 29329, 571, 1, 1, 0, 1, 7365.78, 4908.53, 1.81832, 4.8382, 300, 0, 0, 12600, 3994, 0, 0, 0, 0),
(111139, 29338, 571, 1, 1, 0, 1, 7364.82, 4898.25, 1.37546, 1.07614, 300, 0, 0, 9740, 8636, 0, 0, 0, 0),
(111141, 29330, 571, 1, 1, 0, 1, 7849.05, 4729.17, 0.183427, 5.5724, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111142, 29330, 571, 1, 1, 0, 1, 7808.31, 4692.79, 0.237622, 1.58257, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(111144, 29330, 571, 1, 1, 0, 1, 7825.13, 4706.11, 0.914293, 3.21699, 300, 0, 0, 12175, 0, 0, 0, 0, 0),
(111167, 29338, 571, 1, 1, 0, 1, 7807.4, 4710.85, 0.495033, 6.09547, 300, 0, 0, 9740, 8636, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (111142,111144,111141);
INSERT INTO `creature_addon` (`guid`,`bytes1`,`bytes2`, `emote`) VALUES
(111142,0,1,69),
(111141,0,1,69),
(111144,1,1,0);

DELETE FROM `creature_template_addon` WHERE `entry`=29338;
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(29338,0,0,1,0, "48154");

UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|1 WHERE `entry`=23090;

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=25294;
DELETE FROM `smart_scripts` WHERE `entryorguid`=25294 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(25294, 0, 0, 1, 0, 0, 100, 0, 3000, 10000, 30000, 40000, 11, 50284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Nerub'ar Web Lord - In Combat - Cast 'Blinding Swarm'"),
(25294, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nerub'ar Web Lord - In Combat - Say Line 0");

DELETE FROM `creature_text` WHERE `entry`=25294;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(25294, 0, 0, "The %s directs the blinding swarm directly in front of it.", 16, 0, 100, 0, 0, 0, 0, "Nerub'ar Web Lord");

UPDATE `creature_addon` SET `auras`="55474" WHERE `guid` IN (125388, 125390, 125385);
DELETE FROM `creature` WHERE `guid`=125391;
DELETE FROM `creature_addon` WHERE `guid`=125391;

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=27432;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-125386, 2743200) AND `source_type` IN (0, 9);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-125386, 0, 0, 0, 1, 0, 100, 0, 5000, 20000, 150000, 210000, 80, 2743200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Warsong Peon - Out Of Combat - Run Script"),
(2743200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 10, 125389, 27432, 0, 0, 0, 0, 0, "Warsong Peon - On Script - Say Line 0 (Warsong Peon)"),
(2743200, 9, 1, 0, 0, 0, 50, 0, 60000, 120000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Warsong Peon - On Script - Say Line 1"),
(2743200, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 5, 36, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Warsong Peon - On Script - Play Emote 'Attack 1H'"),
(2743200, 9, 3, 0, 0, 0, 50, 0, 1000, 1000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 10, 125387, 27432, 0, 0, 0, 0, 0, "Warsong Peon - On Script - Say Line 2 (Warsong Peon)");

DELETE FROM `creature_text` WHERE `entry`=27432;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(27432, 0, 0, "Me hungry.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 1, "Me sleepy.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 2, "Me cold.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 3, "Me scared of bug things.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 4, "Me got stuck in sticky bug rope.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 5, "Me no like rock place full of bugs.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 6, "Me no like new cold place.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 0, 7, "It time for work! Zug zug!", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 1, 0, "Ha ha.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 1, 1, "That funny.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 1, 2, "Your head like rock.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 2, 0, "Ow.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 2, 1, "Stop it!", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 2, 2, "That hurt.", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon"),
(27432, 2, 3, "What that sound?", 12, 1, 100, 1, 0, 0, 0, "Warsong Peon");

DELETE FROM `creature_text` WHERE `entry` IN (31261, 31259);
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(31261, 0, 0, "This is madness! Cease this foolish battle!", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 1, "Brothers and sisters, we must remain united! The Lich King will never fall to a world divided!", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 2, "Can you not see that you play right into the Lich King's hands? He wants you to kill each other!", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 3, "Join the Argent Crusade! United, we shall destroy the Lich King!", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 4, "Judgment day comes, brothers and sisters! Will you be prepared?", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 5, "How much of our efforts are being wasted by attacking the Alliance?", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31261, 0, 6, "We must unite and focus our attention upon the true threat: THE LICH KING!", 12, 1, 100, 0, 0, 0, 0, "Brother Keltan"),
(31259, 0, 0, "This is madness! Cease this foolish battle!", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 1, "Brothers and sisters, we must remain united! The Lich King will never fall to a world divided!", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 2, "Can you not see that you play right into the Lich King's hands? He wants you to kill each other!", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 3, "Join the Argent Crusade! United, we shall destroy the Lich King!", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 4, "Judgment day comes, brothers and sisters! Will you be prepared?", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 5, "How much of our efforts are being wasted by attacking the Horde?", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious"),
(31259, 0, 6, "We must unite and focus our attention upon the true threat: THE LICH KING!", 12, 7, 100, 0, 0, 0, 0, "Absalan the Pious");

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (31261, 31259);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (31261, 31259) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(31261, 0, 0, 0, 1, 0, 100, 0, 15000, 30000, 100000, 140000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Brother Keltan - Out Of Combat - Say Line 0"),
(31259, 0, 0, 0, 1, 0, 100, 0, 15000, 30000, 100000, 140000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Absalan the Pious - Out Of Combat - Say Line 0");

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (10214, 10255);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10214, 0, 1, "I want to browse your goods", 3, 128, 0, 0, 0, 0, ""),
(10255, 0, 1, "I want to browse your goods", 3, 128, 0, 0, 0, 0, "");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN (10214, 10255);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10214, 0, 0, 0, 8, 0, 12870, 0, 0, 0, 0, 0, "", "NPC Rork Sharpchin can sell items only if quest 'Ancient Relics' is rewarded"),
(15, 10255, 0, 0, 0, 8, 0, 12882, 0, 0, 0, 0, 0, "", "NPC Olut Alegut can sell items only if quest 'Ancient Relics' is rewarded");

DELETE FROM `creature_loot_template` WHERE `entry`=2031 AND `item`=44007;

DELETE FROM `smart_scripts` WHERE `entryorguid`=28314 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2831400 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(28314, 0, 0, 0, 19, 0, 100, 0, 12566, 0, 0, 0, 80, 2831400, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,"Longrunner Nanik - On Quest Accept - Run Script"),
(2831400, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 28313, 0, 0, 0, 0, 0, 0, "Longrunner Nanik - On Script - Say Line 0 (Apothecary Scyllis)"),
(2831400, 9, 1, 0, 0, 0, 0, 0, 6000, 6000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 28313, 0, 0, 0, 0, 0, 0, "Longrunner Nanik - On Script - Say Line 1 (Apothecary Scyllis)");

DELETE FROM `creature_text` WHERE `entry`=28313;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(28313, 0, 0, "Yes, yes, we should do whatever we can to help them.", 12, 1, 100, 1, 0, 0, 0, "Apothecary Scyllis"),
(28313, 1, 0, "Longrunner, your fodder... err, people will be a valuable resource against the vrykul. Did I say resource? I meant, 'ally.' \n", 12, 1, 100, 25, 0, 0, 0, "Apothecary Scyllis");

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (23740, 29710);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (23740, 29710) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(23740, 0, 0, 0, 0, 0, 100, 0, 5000, 7000, 8000, 12000, 11, 29577, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Frosthorn Ram - In Combat - Cast 'Hoof Strike'"),
(29710, 0, 0, 0, 0, 0, 100, 0, 5000, 7000, 8000, 12000, 11, 29577, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Onslaught Destrier - In Combat - Cast 'Hoof Strike'");
