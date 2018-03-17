-- Quest "Elixir of Suffering (Part 2)"
DELETE FROM `smart_scripts` WHERE `entryorguid`=2230 AND `source_type`=0; -- Umpi
DELETE FROM `smart_scripts` WHERE `entryorguid`=223000 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2230,0,0,0,20,0,100,1,499,0,0,0,80,223000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Umpi - On Quest 'Elixir of Agony (Part 2)' Rewarded - Run Script"),
(2230,0,1,0,20,0,100,1,499,0,0,0,45,1,1,0,0,0,0,19,2216,0,0,0,0,0,0,"Umpi - On Quest 'Elixir of Agony (Part 2)' Rewarded - Set Data to Apothecary Lydon"),
(223000,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Umpi - On Script - Say Line 0"),
(223000,9,1,0,0,0,100,0,0,0,0,0,11,3240,0,0,0,0,0,1,0,0,0,0,0,0,0,"Umpi - On Script - Cast 'Bloody Explosion'");

DELETE FROM `creature_text` WHERE `entry`=2230;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2230,0,0,"Croak!",12,0,100,0,0,0,0,"Umpi");
DELETE FROM `smart_scripts` WHERE `entryorguid`=2216 AND `source_type`=0 AND `id`=1; -- Apothecary Lydon
DELETE FROM `smart_scripts` WHERE `entryorguid`=221601 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2216,0,1,0,38,0,100,1,1,1,0,0,80,221601,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Lydon - On Data Set - Run Script"),
(221601,9,0,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.15964,"Apothecary Lydon - On Script - Set Orientation"),
(221601,9,1,0,0,0,100,0,2000,2000,0,0,5,11,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Lydon - On Script - Play Emote 'Laugh'"),
(221601,9,2,0,0,0,100,0,5000,5000,0,0,66,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Lydon - On Script - Set Orientation");
