UPDATE `smart_scripts` SET `event_flags` = 0, `event_param3` = 0, `event_param4` = 0 WHERE `entryorguid` = 80001 AND `id` = 0;

DELETE FROM `creature_summon_groups` WHERE `summonerId` = 80001 AND `groupId` = 2;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`, `summonTime`) VALUES 
(80001, 0, 2, 25451, 2684.60, 6066.46, 94.36, 0.67, 3, 300000),
(80001, 0, 2, 25451, 2689.22, 6060.77, 94.36, 0.68, 3, 300000),
(80001, 0, 2, 25451, 2685.22, 6072.97, 92.74, 0.19, 3, 300000),
(80001, 0, 2, 25451, 2681.29, 6072.06, 93.90, 0.23, 3, 300000),
(80001, 0, 2, 25451, 2681.29, 6055.12, 94.80, 0.57, 3, 300000),
(80001, 0, 2, 25451, 2696.28, 6051.02, 93.72, 0.92, 3, 300000),
(80001, 0, 2, 25451, 2687.93, 6047.86, 93.17, 0.95, 3, 300000);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 8000100 AND `id` = 12;
INSERT INTO `smart_scripts` VALUES
(800100, 9, 12, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Script - Despawn');
