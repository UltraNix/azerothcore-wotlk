-- DB/NPC: Natasha - add text out of combat
-- DB/Quest: Test of Endurance - Reward Text should depend on player's race
-- DB/NPC: Son of Hakkar's Poisonus Blood should apply debuff
-- DB/NPC: Hellfire Training Dummy - add missing spawns
-- DB/NPC: Wyrmcaller Vile - add on aggro text
-- DB/Quest: Unleash the Raptors - unleashed raptors should not attack players
-- DB/NPC: Brote - add spawn point ( event not scripted)
-- Core/AI: Dead creature's AI should not process CallForHelp hook after death
-- DB/NPC: Unu'pe - add equipment
-- DB/NPC: Grizzlesnout - add missing spawn
-- DB/NPC: Sorely Twitchblade - add out-of combat event
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` IN (22465);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (22465) AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(22465, 0, 0, 0, 1, 0, 100, 0, 60000, 120000, 60000, 120000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Natasha - OOC - Say text');

DELETE FROM `creature_text` WHERE `entry` IN (22465);
INSERT INTO `creature_text` (`entry`, `GroupId`, `ID`, `Text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(22465, 0, 0, "I'm only 4 years old.", 12, 0, 100, 0, 0, 0, 'Natasha'),
(22465, 0, 1, "Have you seen my mommy and daddy?", 12, 0, 100, 0, 0, 0, 'Natasha'),
(22465, 0, 2, "Antelarion, is it safe to play in the for-est yet?", 12, 0, 100, 6, 0, 0, 'Natasha'),
(22465, 0, 3, "I think I came from Eng-land, do you know where that is?", 12, 0, 100, 5, 0, 0, 'Natasha'),
(22465, 0, 4, "Antelarion says I fell off a big bird, as I fell he caught me... He is so pretty!", 12, 0, 100, 0, 0, 0, 'Natasha');

UPDATE `quest_template` SET `OfferRewardText` = "Grenka was powerful, even by $r standards. You should be proud of your accomplishment this day.$b$bDuring your test of faith you displayed strength of spirit, and now you have shown endurance in battle by taking on the Roguefeather harpies, but the time has come for a new test." WHERE `id` = 1150;

DELETE FROM `spell_scripts` WHERE `id`=24320;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(24320,0,0,15,24321,2,0,0,0,0,0);

UPDATE `creature_template` SET `unit_flags`=131328  WHERE `entry` = 17578;
DELETE FROM `creature` WHERE `id`=17578 AND `guid` IN (86753, 113595, 113605, 113607, 113609, 113635);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(86753, 17578, 540, 3, 1, 0, 0, 512.1739, 205.3514, 2.007787, 0.6981317, 7200, 0, 0, 0, 0, 0, 0, 0, 0), -- 17578 (Area: 0 - Difficulty: 0) (Auras: )
(113595, 17578, 540, 3, 1, 0, 0, 512.9296, 186.9605, 2.00013, 0.7679449, 7200, 0, 0, 0, 0, 0, 0, 0, 0), -- 17578 (Area: 0 - Difficulty: 0) (Auras: )
(113605, 17578, 540, 3, 1, 0, 0, 525.0672, 176.6558, 2.016024, 2.356194, 7200, 0, 0, 0, 0, 0, 0, 0, 0), -- 17578 (Area: 0 - Difficulty: 0) (Auras: )
(113607, 17578, 540, 3, 1, 0, 0, 508.1696, 131.2284, 2.018857, 1.22173, 7200, 0, 0, 0, 0, 0, 0, 0, 0), -- 17578 (Area: 0 - Difficulty: 0) (Auras: )
(113609, 17578, 540, 3, 1, 0, 0, 512.5972, 119.7658, 1.994586, 0.6632251, 7200, 0, 0, 0, 0, 0, 0, 0, 0), -- 17578 (Area: 0 - Difficulty: 0) (Auras: )
(113635, 17578, 540, 3, 1, 0, 0, 523.4672, 119.2777, 1.946144, 2.042035, 7200, 0, 0, 0, 0, 0, 0, 0, 0); -- 17578 (Area: 0 - Difficulty: 0) (Auras: )

DELETE FROM `smart_scripts` WHERE `entryorguid`=24029 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(24029, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Wyrmcaller Vile - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `entry`=24029;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(24029, 0, 0, "Did you really think that by facing me, you have any hope of saving your friends?", 12, 0, 100, 0, 0, 0, 0, "Wyrmcaller Vile");

UPDATE `creature_template` SET `unit_flags`=`unit_flags`|256  WHERE `entry` =23741;

UPDATE `creature` SET `MovementType` =0, `spawndist`=0 WHERE `id`=27191;
DELETE FROM `creature` WHERE `id`=27198 AND `guid`=113636; 
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(113636, 27198, 571, 1, 1, 0, 0, 3240.79, -724.326, 174.892, 4.15388, 300, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `creature_template_addon` WHERE `entry` IN (27198);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `path_id`, `bytes1`, `bytes2`, `auras`) VALUES
(27198,0,0,1,0,"");

DELETE FROM `creature_template_addon` WHERE `entry` IN (27610);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `emote`, `bytes1`, `bytes2`, `auras`) VALUES
(27610,0,0,0,0,"29266");

DELETE FROM `creature_equip_template` WHERE `entry`=27566 AND `ID` IN (2,3);
INSERT INTO `creature_equip_template` (`entry`, `ID`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES
(27566, 2, 2827, 0, 0), -- 27566
(27566, 3, 12856, 0, 0); -- 27566

UPDATE `creature` SET `equipment_id`=3 WHERE `id`=27566 AND `guid` IN (112384);
UPDATE `creature` SET `equipment_id`=2 WHERE `id`=27566 AND `guid` IN (112379,112378);

UPDATE `creature_addon` SET `emote`=28 WHERE `guid` IN (112378);
UPDATE `creature` SET `MovementType` =0, `spawndist`=0 WHERE `id`=27529;

DELETE FROM `creature` WHERE `id`=27523 AND `guid`=113637; 
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(113637, 27523, 571, 1, 1, 0, 0, 3691.77, -5411, 32.8266, 5.96903, 60, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=23732;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23732 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (2373200, 2373201) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(23732, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Reset - Set Event Phase 1"),
(23732, 0, 1, 0, 1, 1, 100, 0, 3000, 3000, 3000, 3000, 87, 2373200, 2373201, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - OOC - Run Random Actionlist (Phase 1)"),
(2373200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set Event Phase 2"),
(2373200, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Play Emote 'Eat'"),
(2373200, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Say Line 0"),
(2373200, 9, 3, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Play Emote 'Talk'"),
(2373200, 9, 4, 0, 0, 0, 100, 0, 18000, 27000, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set Event Phase 1"),
(2373201, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set Event Phase 2"),
(2373201, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 5, 11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Play Emote 'Laugh'"),
(2373201, 9, 2, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Say Line 1"),
(2373201, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 5, 273, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Play Emote 'Yes'"),
(2373201, 9, 4, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Say Line 2"),
(2373201, 9, 5, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 17, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set EmoteState 'Dance'"),
(2373201, 9, 6, 0, 0, 0, 100, 0, 40000, 81000, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set EmoteState 'None'"),
(2373201, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sorely Twitchblade - On Script - Set Event Phase 1");

DELETE FROM `creature_text` WHERE `entry`=23732;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(23732, 0, 0, "That hit the shpot! Gimmie anudder one, Coot! *hic*", 12, 7, 100, 5, 0, 0, 0, "Sorely Twitchblade"),
(23732, 1, 0, "You're shayin' you wan... you wan... *hic* you wan' me to dansh on dis bar? *hic*", 12, 7, 100, 6, 0, 0, 0, "Sorely Twitchblade"),
(23732, 2, 0, "Maeshtro! Cue da mushic!", 12, 7, 100, 5, 0, 0, 0, "Sorely Twitchblade");
