SET @EmblemHighPREV := 47241; # Emblem of Triumph
SET @EmblemLowPREV  := 45624; # Emblem of Conquest

SET @EmblemHighCURR := 49426; # Emblem of Frost
SET @EmblemLowCURR  := 47241; # Emblem of Triumph

-- Crusader Orb & Carpet 
DELETE FROM `npc_vendor` WHERE `entry` = 40160 AND `item` IN (47556, 54798);
INSERT INTO `npc_vendor` VALUES 
(40160, 0, 47556, 0, 0, 2986),
(40160, 0, 54798, 0, 0, 2986);
-- JC Rings
DELETE FROM `npc_vendor` WHERE `entry` = 32172 AND `item` IN (51557, 51558, 51559, 51560);
INSERT INTO `npc_vendor` VALUES
(32172, 0, 51557, 0, 0, 2735),
(32172, 0, 51558, 0, 0, 2737),
(32172, 0, 51559, 0, 0, 2736),
(32172, 0, 51560, 0, 0, 2738);

-- WG PVP Alliance
DELETE FROM `npc_vendor` WHERE `entry` = 39172 AND `item` IN (51568,51569,51570,51571, 51572, 51573,51574, 51575, 51576, 51577, 51578, 51579, 51580, 51581);
INSERT INTO `npc_vendor` VALUES
(39172, 0, 51568, 0, 0, 2578),
(39172, 0, 51569, 0, 0, 2578),
(39172, 0, 51570, 0, 0, 2578),
(39172, 0, 51571, 0, 0, 2578),
(39172, 0, 51572, 0, 0, 2579),
(39172, 0, 51573, 0, 0, 2579),
(39172, 0, 51574, 0, 0, 2579),
(39172, 0, 51575, 0, 0, 2579),
(39172, 0, 51576, 0, 0, 2579),
(39172, 0, 51577, 0, 0, 2579),
(39172, 0, 51578, 0, 0, 2579),
(39172, 0, 51579, 0, 0, 2579),
(39172, 0, 51580, 0, 0, 2579),
(39172, 0, 51581, 0, 0, 2579);
-- PvP WG Horde
DELETE FROM `npc_vendor` WHERE `entry` = 39173 AND `item` IN (51568,51569,51570,51571,51572,51573,51574,51575,51576,51577,51578,51579,51580,51581);
INSERT INTO `npc_vendor` VALUES
(39173, 0, 51568, 0, 0, 2578),
(39173, 0, 51569, 0, 0, 2578),
(39173, 0, 51570, 0, 0, 2578),
(39173, 0, 51571, 0, 0, 2578),
(39173, 0, 51572, 0, 0, 2579),
(39173, 0, 51573, 0, 0, 2579),
(39173, 0, 51574, 0, 0, 2579),
(39173, 0, 51575, 0, 0, 2579),
(39173, 0, 51576, 0, 0, 2579),
(39173, 0, 51577, 0, 0, 2579),
(39173, 0, 51578, 0, 0, 2579),
(39173, 0, 51579, 0, 0, 2579),
(39173, 0, 51580, 0, 0, 2579),
(39173, 0, 51581, 0, 0, 2579);

-- RDF rewards
UPDATE `quest_template` SET `RewardItemId1`=@EmblemHighCURR, `RewardItemCount1`=2 WHERE `Id`=24788; -- 1st daily heroic random
UPDATE `quest_template` SET `RewardItemId1`=@EmblemLowCURR, `RewardItemCount1`=2 WHERE `Id`=24789; -- nth daily heroic random
UPDATE `quest_template` SET `RewardItemId1`=@EmblemLowCURR, `RewardItemCount1`=2 WHERE `Id`=24790; -- 1st daily normal random

-- Toravon the Ice Watcher
DELETE FROM `creature` WHERE `guid`=202600;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(202600, 38433, 624, 3, 1, 0, 1, -43.3316, -288.708, 91.2511, 1.58825, 604800, 0, 0, 1, 0, 0, 0, 0, 0);

-- ICC heroic (disable heroic for now)
UPDATE `access_requirement` SET `completed_achievement`=0, `level_min`=90, `level_max`=255 WHERE `mapId`=631 AND `difficulty`=2;
UPDATE `access_requirement` SET `completed_achievement`=0, `level_min`=90, `level_max`=255 WHERE `mapId`=631 AND `difficulty`=3;

-- Archmage Lan'dalock
DELETE FROM `creature_queststarter` WHERE `id`=20735;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES 
(20735, 24579),
(20735, 24580),
(20735, 24581),
(20735, 24582),
(20735, 24583),
(20735, 24584),
(20735, 24585),
(20735, 24586),
(20735, 24587),
(20735, 24588),
(20735, 24589),
(20735, 24590);
DELETE FROM `creature_questender` WHERE `id`=20735;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES 
(20735, 24579),
(20735, 24580),
(20735, 24581),
(20735, 24582),
(20735, 24583),
(20735, 24584),
(20735, 24585),
(20735, 24586),
(20735, 24587),
(20735, 24588),
(20735, 24589),
(20735, 24590);
-- Update Archmage Landalock quest rewards
UPDATE `quest_template` SET `RewardItemId1` = @EmblemHighCURR, `RewardItemId2` = @EmblemLowCURR WHERE `id` IN (SELECT `quest` FROM `creature_queststarter` WHERE `id` = 20735);

-- Archmage Timear
DELETE FROM `creature_queststarter` WHERE `id`=31439;
DELETE FROM `creature_questender` WHERE `id`=31439;
