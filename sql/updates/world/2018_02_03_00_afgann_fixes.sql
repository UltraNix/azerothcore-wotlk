-- Ahn'kahar Watcher normal mode level correction
UPDATE `creature_template` SET `minlevel`=73, `maxlevel`=73 WHERE `entry`=31104;

-- Ahn'kahar Web Winder
DELETE FROM `smart_scripts` WHERE `entryorguid`=30276 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_ahnkahar_web_winder" WHERE `entry`=30276;
DELETE FROM `spelldifficulty_dbc` WHERE `id`=56640;
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(56640, 56640, 59106);

-- Trained Rock Falcon
DELETE FROM `creature_template_addon` WHERE `entry`= 24783;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`auras`) VALUES
(24783, 1, 54422);

-- Nass SAI
UPDATE `smart_scripts` SET `action_type`=0 WHERE `entryorguid`=28521 AND `source_type`=0 AND `id`=3;

-- Basic Campfire
UPDATE `gameobject_template` SET `data1`=5 WHERE `entry`=29784;

-- If Valgarde Falls
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_valgarde_event_attacker" WHERE `entry` IN (24051, 24063);
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_valgarde_event_defender" WHERE `entry`=23739;
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|0x00020000, `flags_extra`=`flags_extra`|0x00000002 WHERE `entry`=23821;

DELETE FROM `creature_text` WHERE `entry` IN (23739,24051);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(24051, 0, 0, "YAAARRRGH!", 12, "Dragonflayer Invader aggro"),
(23739, 0, 0, "Don't let those monsters through the gate! Stand firm, soldiers!", 12, "Valgarde Defender fight");

DELETE FROM `creature` WHERE `guid` IN (112719, 112720);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(112719, 23739, 571, 1, 1, 21754, 1, 706.422974, -4934.177734, 6.570681, 2.68534, 300, 0, 0, 38440, 0, 0, 0, 0, 0),
(112720, 23739, 571, 1, 1, 21754, 1, 708.427551, -4950.030273, 4.549574, 2.68534, 300, 0, 0, 38440, 0, 0, 0, 0, 0);

SET @GUID = 118770;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 734.072876, -4871.065430, 6.417796, 1, 0),
(@GUID*10, 2, 725.214233, -4898.923340, 6.360070, 1, 0),
(@GUID*10, 3, 710.450439, -4905.583008, 7.977669, 1, 0),
(@GUID*10, 4, 706.199219, -4927.996094, 6.910131, 1, 90000000);

SET @GUID = 118771;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 714.598694, -4943.068359, 5.065039, 1, 90000000);

SET @GUID = 120560;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 744.392395, -4880.510254, 2.192117, 1, 0),
(@GUID*10, 2, 737.298584, -4923.297363, 5.823121, 1, 0),
(@GUID*10, 3, 714.745667, -4938.609863, 6.091618, 1, 90000000);

SET @GUID = 118773;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 741.265747, -4921.530273, 5.336173, 1, 0),
(@GUID*10, 2, 719.388550, -4936.403809, 6.697114, 1, 90000000);

SET @GUID = 120561;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 741.265747, -4921.530273, 5.336173, 1, 0),
(@GUID*10, 2, 719.388550, -4936.403809, 6.697114, 1, 90000000);

SET @GUID = 120558;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 720.532043, -4939.865234, 6.106517, 1, 90000000);

SET @GUID = 118772;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(@GUID, @GUID*10);
UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `waypoint_data` WHERE `id`=@GUID*10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `move_type`, `delay`) VALUES
(@GUID*10, 1, 773.114014, -4973.180176, 1.379400, 1, 0),
(@GUID*10, 2, 738.953491, -4979.407715, 3.195509, 1, 0),
(@GUID*10, 3, 724.995483, -4984.345215, 5.996824, 1, 0);
