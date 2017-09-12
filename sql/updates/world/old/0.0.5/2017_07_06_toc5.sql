-- Night Elfs
DELETE FROM `creature` WHERE `guid` IN (200146, 200147);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200146, 34871, 650, 3, 1, 0, 0, 806.273376, 655.308655, 440.160919, 3.375838, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200147, 34871, 650, 3, 1, 0, 0, 798.808411, 654.133240, 436.912567, 3.265882, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Gnomes
DELETE FROM `creature` WHERE `guid` IN (200148, 200149);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200148, 34869, 650, 3, 1, 0, 0, 812.238281, 637.895813, 438.686035, 3.171645, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200149, 34869, 650, 3, 1, 0, 0, 806.769104, 641.530640, 436.906403, 3.387629, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Humans
DELETE FROM `creature` WHERE `guid` IN (200150, 200151, 200152, 200153);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200150, 34870, 650, 3, 1, 0, 0, 805.243164, 632.398926, 435.418213, 3.226631, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200151, 34870, 650, 3, 1, 0, 0, 811.914246, 632.715088, 438.740265, 3.218777, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200152, 34870, 650, 3, 1, 0, 0, 808.875427, 604.240051, 436.886414, 3.024165, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200153, 34870, 650, 3, 1, 0, 0, 811.891418, 601.672424, 438.730377, 2.819967, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Dwarves
DELETE FROM `creature` WHERE `guid` IN (200154, 200155);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200154, 34856, 650, 3, 1, 0, 0, 804.593506, 590.583008, 436.911133, 2.777457, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200155, 34856, 650, 3, 1, 0, 0, 807.295288, 595.484863, 436.895416, 2.722480, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Draenei
DELETE FROM `creature` WHERE `guid` IN (200156, 200157, 200158);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200156, 34868, 650, 3, 1, 0, 0, 811.111816, 580.102356, 441.995148, 2.910975, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200157, 34868, 650, 3, 1, 0, 0, 796.939514, 585.111755, 435.421326, 2.600742, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200158, 34868, 650, 3, 1, 0, 0, 804.073303, 582.106018, 438.707031, 2.608597, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Argent Crusade Spectators (alliance side)
DELETE FROM `creature` WHERE `guid` IN (200159, 200160, 200161, 200162, 200163, 200164);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200159, 34970, 650, 3, 1, 0, 0, 758.450928, 558.978699, 435.411774, 1.798862, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200160, 34975, 650, 3, 1, 0, 0, 776.789856, 561.516296, 436.902161, 2.012488, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200161, 34975, 650, 3, 1, 0, 0, 778.616699, 559.002197, 438.743683, 2.067461, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200162, 34974, 650, 3, 1, 0, 0, 784.224304, 570.678345, 435.420715, 2.208839, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200163, 34974, 650, 3, 1, 0, 0, 781.669128, 564.459167, 436.895050, 2.122443, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200164, 34974, 650, 3, 1, 0, 0, 784.738525, 562.048279, 438.705658, 2.196272, 120, 0, 0, 1, 0, 0, 0, 0, 0);
