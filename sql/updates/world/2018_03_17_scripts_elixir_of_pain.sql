-- Quest "Elixir of Pain (Part 2)"
DELETE FROM `smart_scripts` WHERE `entryorguid`=2274 AND `source_type`=0 AND `id` IN (0,1,2); -- Stanley
DELETE FROM `smart_scripts` WHERE `entryorguid`=227400 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2274,0,0,0,20,0,100,1,502,0,0,0,80,227400,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stanley - On Quest 'Elixir of Pain (Part 2)' Rewarded - Run Script"),
(227400,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stanley - On Script - Say Line 0"),
(227400,9,1,0,0,0,100,0,2000,2000,0,0,36,2275,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stanley - On Script - Update Template To 'Enraged Stanley'"),
(227400,9,2,0,0,0,100,0,0,0,0,0,3,2275,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stanley - On Script - Morph To Creature 'Enraged Stanley'"),
(227400,9,3,0,0,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Stanley - On Script - Start Attacking");

DELETE FROM `creature_text` WHERE `entry`=2274;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2274,0,0,"%s sniffs the elixir then eagerly digs in!",16,0,100,0,0,0,0,"Stanley");
