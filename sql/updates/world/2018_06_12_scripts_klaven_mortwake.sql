DELETE FROM `smart_scripts` WHERE `entryorguid` IN (705300, 7053);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(705300, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 24000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Pause Waypoint'),
(705300, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Say Line 0'),
(705300, 9, 2, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Say Line 1'),
(705300, 9, 3, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 2, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Say Line 2'),
(705300, 9, 4, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 3, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Say Line 3'),
(705300, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 4, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Script - Say Line 4'),
(7053, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 54, 20000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Klaven Mortwake - On Gossip Hello - Pause Waypoint'),
(7053, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 53, 0, 7053, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Klaven Mortwake - On Reset - Start Waypoint'),
(7053, 0, 2, 0, 40, 0, 100, 0, 1, 7053, 0, 0, 80, 705300, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Klaven Mortwake - On Waypoint 1 Reached - Run Script');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 7053;

DELETE FROM `waypoints` WHERE `entry` = 7053;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(7053, 1, -11124.1, 545.44, 70.4323, 'Klaven Mortwake'),
(7053, 2, -11128.9, 544.692, 70.4022, 'Klaven Mortwake'),
(7053, 3, -11133.4, 550.86, 70.3957, 'Klaven Mortwake'),
(7053, 4, -11132.2, 539.132, 70.3766, 'Klaven Mortwake'),
(7053, 5, -11133.4, 550.86, 70.3957, 'Klaven Mortwake'),
(7053, 6, -11132.2, 539.132, 70.3766, 'Klaven Mortwake'),
(7053, 7, -11128.9, 544.692, 70.4022, 'Klaven Mortwake');

DELETE FROM `creature_text` WHERE `entry` = 7053;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(7053, 0, 0, '%s wildly flips through the pages of a large tome.', 16, 0, 100, 0, 1000, 0, 0, 'Klaven Mortwake'),
(7053, 1, 0, 'The sweet irony -- Stormwind forces cut down in defense of their city, only to rise and fight alongside the Brotherhood as instruments of destruction.', 12, 0, 100, 0, 0, 0, 0, 'Klaven Mortwake'),
(7053, 2, 0, 'And should one die, two shall rise!', 12, 0, 100, 0, 1000, 0, 0, 'Klaven Mortwake'),
(7053, 3, 0, '%s shuffles through the books.', 16, 0, 100, 0, 1000, 0, 0, 'Klaven Mortwake'),
(7053, 4, 0, 'Now where did I put the Venture Company formulations?', 12, 0, 100, 0, 1000, 0, 0, 'Klaven Mortwake');
