DELETE FROM `creature` WHERE `guid` IN (200165, 200166, 200167, 200168);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(200165, 34994, 650, 3, 1, 0, 0, 686.6632, 614.5608, 435.4849, 6.26194, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200166, 34995, 650, 3, 1, 0, 0, 686.9358, 622.0295, 435.4867, 6.230825, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200167, 34990, 650, 3, 1, 0, 0, 806.3246, 617.9948, 435.4912, 3.128137, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(200168, 34992, 650, 3, 1, 0, 0, 806.2239, 614.9393, 435.4874, 3.006140, 120, 0, 0, 1, 0, 0, 0, 0, 0);