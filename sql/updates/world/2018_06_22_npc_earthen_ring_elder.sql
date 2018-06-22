DELETE FROM `creature` WHERE `guid` IN (138258,138259,138260);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(138258, 26221, 530, 1, 1, 23687, 1, -3795.06, -11492.92, -134.71, 2.2101, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(138259, 26221, 0, 1, 1, 23131, 1, -8832.81, 861.687, 98.8931, 0.880735, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(138260, 26221, 530, 1, 1, 23129, 1, 9803.67, -7241.96, 26.05, 5.04, 300, 0, 0, 8982, 3155, 0, 0, 0, 0);

DELETE FROM `game_event_creature` WHERE `guid` IN (138258, 138259, 138260);
INSERT INTO `game_event_creature` VALUES
(1, 138258),
(1, 138259),
(1, 138260);
