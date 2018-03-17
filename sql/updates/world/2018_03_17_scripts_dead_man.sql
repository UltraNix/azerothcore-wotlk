UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI', scriptname='' WHERE `entry` =186944;
DELETE FROM `smart_scripts` WHERE `entryorguid` =186944 AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(186944, 1, 0, 1, 70, 0, 100, 0, 2, 0, 0, 0, 105, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dirt Mound - On State Changed - Add Go Flag '),
(186944, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 12, 24790, 1, 120000, 1, 0, 0, 8, 0, 0, 0, 688.9122, -3377.737, 67.87585, 1.291544, 'Dirt Mound - On State Changed - Summon Black Conrads Ghost'),
(186944, 1, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 12, 24796, 1, 120000, 1, 0, 0, 8, 0, 0, 0, 691.5706, -3375.863, 68.09953, 1.308997, 'Dirt Mound - On State Changed - Summon Spectral Sailor'),
(186944, 1, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 24796, 1, 120000, 1, 0, 0, 8, 0, 0, 0, 687.27, -3374.881, 67.92136, 1.047198, 'Dirt Mound - On State Changed - Summon Spectral Sailor');

DELETE FROM `creature` WHERE  `guid`=116177;
DELETE FROM `gameobject` WHERE `guid` = 5842;
INSERT INTO `gameobject` VALUES
(5842, 186944, 571, 1, 1, 686.76, -3369.37, 67.96, 0, 0, 0, 0, 0, 120, 100, 1, 0);