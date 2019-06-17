-- DB/Quest: Outro event for "On Brann's Trail" and fix prevquest for "Sniffing Out the Perpetrator"
-- DB/SAI: Add scripts for some Howling Fjord mobs
-- Loot/Item: fix drop chance for Moonrest Gardens Plans
-- DB/Gossip: add Death Knight-only gossip text for NPC The Ebon Watcher
--  DB/SAI: out of combat dialog for NPCs Crusade Engineer Spitzpatrick and Crusade Architect Silas
-- DB/Item: Add gold loot to item Chest of Spoils 
-- DB/Creature: Seer Nakha  - add spawn
UPDATE `quest_template` SET `PrevQuestID`=12854 WHERE `id`=12855;

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=29650;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2965000 AND `source_type` =9;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29650 AND `id` = 2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(29650, 0, 2, 0, 20, 0, 100, 0, 12854, 0, 0, 0, 80, 2965000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Quest 'On Brann's Trail' Rewarded - Run Script"),
(2965000, 9, 0, 0, 0, 0, 100, 0, 500, 500, 0, 0, 66, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Face Invoker"),
(2965000, 9, 1, 0, 0, 0, 100, 0, 500, 500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Talk 0"),
(2965000, 9, 2, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Talk 1"),
(2965000, 9, 3, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Talk 2"),
(2965000, 9, 4, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Talk 3"),
(2965000, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Archaeologist Andorin - On Script - Restore Orientation");

DELETE FROM `creature_text` WHERE `entry`=29650;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(29650, 0, 0, "It's those blasted iron dwarves again! Somehow, they found him before we did.", 12, 7, 100, 1, 0, 0, 0, "Archaeologist Andorin"),
(29650, 1, 0, "They're not going to give up until they find him. We can't allow that to happen, $n, and Brann knows it.", 12, 7, 100, 1, 0, 0, 0, "Archaeologist Andorin"),
(29650, 2, 0, "There are some rather cryptic instructions in this note. Brann must've had some kind of backup plan, but he can't keep evading capture forever...", 12, 7, 100, 1, 0, 0, 0, "Archaeologist Andorin"),
(29650, 3, 0, "It's up to you to find him before the irons do!", 12, 7, 100, 397, 0, 0, 0, "Archaeologist Andorin");

-- Lieutenant Celeyne
UPDATE creature_template SET `AIName`='SmartAI' WHERE `entry`=23964;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23964 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(23964,0,0,0,9,0,100,0,8,25,5000,5000,11,27577,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Celeyne - In Range - Cast 'Intercept'"),
(23964,0,1,0,0,0,100,0,0,5,9000,14000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Celeyne - In Range - Cast 'Mortal Strike'");

-- Dragonflayer Guardian
UPDATE creature_template SET `AIName`='SmartAI' WHERE `entry`=27927;
DELETE FROM `smart_scripts` WHERE `entryorguid`=27927 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27927,0,0,0,0,0,100,0,4000,4000,15000,21000,11,48280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonflayer Guardian - In Combat - Cast 'Whirlwind'");

-- Dragonflayer Hunting Hound
UPDATE creature_template SET `AIName`='SmartAI' WHERE `entry`=23994;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23994 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(23994,0,0,0,0,0,100,0,2000,6000,10000,15000,11,48287,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Hunting Hound - In Combat - Cast 'Powerful Bite'");

-- Ember Clutch Ancient
UPDATE creature_template SET `AIName`='SmartAI' WHERE `entry`=23870;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23870 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(23870,0,0,0,0,0,100,0,3000,8000,9000,13000,11,12612,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ember Clutch Ancient - In Combat - Cast 'Stomp'"),
(23870,0,1,0,2,0,100,1,0,30,0,0,11,42544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ember Clutch Ancient - At 30% HP - Cast 'Rejuvenation'");

-- Dragonflayer Handler
UPDATE creature_template SET `AIName`='SmartAI' WHERE `entry`=23871;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23871 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(23871,0,0,0,9,0,100,0,0,5,5000,7000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Handler - In Range - Cast 'Cleave'"),
(23871,0,1,0,9,0,100,0,0,20,9000,13000,11,6533,1,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonflayer Handler - In Range - Cast 'Net'");

UPDATE `item_loot_template` SET `ChanceOrQuestChance`=10 WHERE `Item`=35783;

DELETE FROM `gossip_menu` WHERE `entry`=9999 AND `text_id`=13857;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(9999, 13857);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=14 AND `SourceGroup`=9999;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(14, 9999, 13856, 0, 0, 15, 0, 32, 0, 0, 1, 0, 0, "", "Show gossip text 13856 if player is NOT a Death Knight"),
(14, 9999, 13857, 0, 0, 15, 0, 32, 0, 0, 0, 0, 0, "", "Show gossip text 13857 if player is a Death Knight");
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` = 30596;

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=30714;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (30714, 3071400) AND `source_type` IN (0, 9);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(30714, 0, 0, 0, 1, 0, 100, 0, 10000, 40000, 120000, 240000, 80, 3071400, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusade Engineer Spitzpatrick - Out Of Combat - Run Script"),
(3071400, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusade Engineer Spitzpatrick - On Script - Talk 0"),
(3071400, 9, 1, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 30686, 0, 0, 0, 0, 0, 0, "Crusade Engineer Spitzpatrick - On Script - Talk 0 (Crusade Architect Silas)");

DELETE FROM `creature_text` WHERE `entry` IN (30714, 30686);
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(30714, 0, 0, "Dying must have completely destroyed your ability to perform simple arithmetic. Can't you see that there is no way you're going to make that structure's layout work? It'll collapse!", 12, 0, 100, 1, 0, 0, 0, "Crusade Engineer Spitzpatrick"),
(30686, 0, 0, "How dare you! I am the chief architect here and I make the final call on layouts! If you have a problem with my plans, feel free to file a grievance with Highlord Fordring. Now if you don't mind, I have work to attend!", 12, 0, 100, 1, 0, 0, 0, "Crusade Architect Silas");

UPDATE `item_template` SET `minMoneyLoot`=600000, `maxMoneyLoot`=1000000 WHERE `entry`=20602;

DELETE FROM `creature` WHERE `id`  IN (23265) AND `guid` IN (109724);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`,  `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(109724, 23265, 530, 1, 1, 1, -1333.53, 7221.96, 33.583, 2.26893, 300, 0, 0);

