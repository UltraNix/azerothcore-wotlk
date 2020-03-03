DELETE FROM `creature` WHERE `guid` = 303341 AND `id` = 33993;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(303341, 33993, 624, 3, 1, 0, 0, -218.726, -288.57, 91.5494, 1.58825, 604800, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_loot_template` WHERE `entry` = 33993 AND `item` = 40752;
DELETE FROM `creature_loot_template` WHERE `entry` = 33993 AND `item` = 40753;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(33993, 40753, 100, 1, 0, 2, 2);
DELETE FROM `creature_loot_template` WHERE `entry` = 33994 AND `item` = 40752;
DELETE FROM `creature_loot_template` WHERE `entry` = 33994 AND `item` = 45624;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(33994, 45624, 100, 1, 0, 2, 2);
