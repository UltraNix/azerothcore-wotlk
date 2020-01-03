-- DB/NPC: Remove duplicate Yulda the Stormspeaker spawn https://github.com/SunwellTracker/issues/issues/2769
-- DB/NPC: Remove duplicate Snowblind Digger spawns https://github.com/SunwellTracker/issues/issues/2768
-- Core/Quest: A Delicate Touch https://github.com/SunwellTracker/issues/issues/2765
-- DB/GO: Arthas Tears - fix floating spawn https://github.com/SunwellTracker/issues/issues/2749
-- DB/Quest: The Scarlet Crusade - Scarlet Armbands should drop only while on quest https://github.com/SunwellTracker/issues/issues/2733
-- DB/Loot: Adjust gold drops from Karazhan mobs https://github.com/SunwellTracker/issues/issues/2717
-- DB/NPC: Add Dark Iron Ambassador rare spawn to Gnomeregan https://github.com/SunwellTracker/issues/issues/2708
DELETE FROM `creature` WHERE `guid` = 104495 AND `id` = 30046;
DELETE FROM `creature` WHERE `guid` IN (209173,209176,209177,209174,209171) AND `id` = 29413;
UPDATE `creature_template` SET `ScriptName` = "npc_improved_land_mine", `AIName` = "" WHERE `entry` = 29475;
UPDATE `gameobject` SET `position_z` = 59.66 WHERE `guid` = 15968;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 3266;
UPDATE `creature_template` SET `mingold` = 1519,  `maxgold` = 1988 WHERE `entry` = 15551;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 15687;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 15688;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 15689;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 15690;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 15691;
UPDATE `creature_template` SET `mingold` = 1901,  `maxgold` = 2487 WHERE `entry` = 16389;
UPDATE `creature_template` SET `mingold` = 1605,  `maxgold` = 2101 WHERE `entry` = 16406;
UPDATE `creature_template` SET `mingold` = 1942,  `maxgold` = 2541 WHERE `entry` = 16407;
UPDATE `creature_template` SET `mingold` = 2967,  `maxgold` = 3879 WHERE `entry` = 16408;
UPDATE `creature_template` SET `mingold` = 290,  `maxgold` = 384 WHERE `entry` = 16409;
UPDATE `creature_template` SET `mingold` = 2669,  `maxgold` = 3491 WHERE `entry` = 16410;
UPDATE `creature_template` SET `mingold` = 1945,  `maxgold` = 2545 WHERE `entry` = 16411;
UPDATE `creature_template` SET `mingold` = 1988,  `maxgold` = 2601 WHERE `entry` = 16412;
UPDATE `creature_template` SET `mingold` = 2540,  `maxgold` = 3322 WHERE `entry` = 16414;
UPDATE `creature_template` SET `mingold` = 1945,  `maxgold` = 2545 WHERE `entry` = 16415;
UPDATE `creature_template` SET `mingold` = 1945,  `maxgold` = 2545 WHERE `entry` = 16424;
UPDATE `creature_template` SET `mingold` = 1945,  `maxgold` = 2545 WHERE `entry` = 16425;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 16457;
UPDATE `creature_template` SET `mingold` = 2540,  `maxgold` = 3322 WHERE `entry` = 16459;
UPDATE `creature_template` SET `mingold` = 2115,  `maxgold` = 2767 WHERE `entry` = 16460;
UPDATE `creature_template` SET `mingold` = 2583,  `maxgold` = 3378 WHERE `entry` = 16461;
UPDATE `creature_template` SET `mingold` = 354,  `maxgold` = 467 WHERE `entry` = 16468;
UPDATE `creature_template` SET `mingold` = 100000,  `maxgold` = 120000 WHERE `entry` = 16470;
UPDATE `creature_template` SET `mingold` = 3137,  `maxgold` = 4101 WHERE `entry` = 16471;
UPDATE `creature_template` SET `mingold` = 2880,  `maxgold` = 3766 WHERE `entry` = 16472;
UPDATE `creature_template` SET `mingold` = 2540,  `maxgold` = 3322 WHERE `entry` = 16473;
UPDATE `creature_template` SET `mingold` = 3264,  `maxgold` = 4268 WHERE `entry` = 16481;
UPDATE `creature_template` SET `mingold` = 2627,  `maxgold` = 3435 WHERE `entry` = 16482;
UPDATE `creature_template` SET `mingold` = 3859,  `maxgold` = 5045 WHERE `entry` = 16485;
UPDATE `creature_template` SET `mingold` = 5219,  `maxgold` = 6821 WHERE `entry` = 16504;
UPDATE `creature_template` SET `mingold` = 240000,  `maxgold` = 260000 WHERE `entry` = 16524;
UPDATE `creature_template` SET `mingold` = 1945,  `maxgold` = 2545 WHERE `entry` = 16525;
UPDATE `creature_template` SET `mingold` = 2117,  `maxgold` = 2769 WHERE `entry` = 16526;
UPDATE `creature_template` SET `mingold` = 839,  `maxgold` = 1100 WHERE `entry` = 16539;
UPDATE `creature_template` SET `mingold` = 1607,  `maxgold` = 2103 WHERE `entry` = 16540;
UPDATE `creature_template` SET `mingold` = 3264,  `maxgold` = 4268 WHERE `entry` = 16544;
UPDATE `creature_template` SET `mingold` = 2627,  `maxgold` = 3435 WHERE `entry` = 16545;
UPDATE `creature_template` SET `mingold` = 3264,  `maxgold` = 4268 WHERE `entry` = 16595;
UPDATE `creature_template` SET `mingold` = 5219,  `maxgold` = 6821 WHERE `entry` = 16596;

DELETE FROM `creature` WHERE `guid` = 183608;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`) VALUES
(183608, 6228, 90, 1, 0, -1, -698.351, 559.918, -282.06, 6.03311, 36000, 0, 0, 4924, 2457, 2);

DELETE FROM `creature_addon` WHERE `guid` = 183608;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(183608, 1836080, 0, 0, 0, 0, '');

DELETE FROM `waypoint_data` WHERE `id` = 1836080;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
(1836080, 1, -698.351, 559.918, -282.06, 0, 0, 0, 100, 0),
(1836080, 2, -736.867, 569.914, -291.06, 0, 0, 0, 100, 0),
(1836080, 3, -743.754, 581.403, -291.06, 0, 0, 0, 100, 0),
(1836080, 4, -734.431, 619.357, -300.06, 0, 0, 0, 100, 0),
(1836080, 5, -726.929, 649.513, -309.06, 0, 0, 0, 100, 0),
(1836080, 6, -717.134, 687.832, -318.06, 0, 0, 0, 100, 0),
(1836080, 7, -705.253, 694.829, -318.06, 0, 0, 0, 100, 0),
(1836080, 8, -717.059, 687.506, -318.06, 0, 0, 0, 100, 0),
(1836080, 9, -726.776, 650.171, -309.06, 0, 0, 0, 100, 0),
(1836080, 10, -734.225, 619.203, -300.06, 0, 0, 0, 100, 0),
(1836080, 11, -743.649, 581.74, -291.06, 0, 0, 0, 100, 0),
(1836080, 12, -736.919, 569.825, -291.06, 0, 0, 0, 100, 0);
