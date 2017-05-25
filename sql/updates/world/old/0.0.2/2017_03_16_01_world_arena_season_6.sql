DELETE FROM `creature` WHERE `creature`.`guid` = 208509;
DELETE FROM `creature` WHERE `creature`.`guid` = 208510;
DELETE FROM `creature` WHERE `creature`.`guid` = 208511;
DELETE FROM `creature` WHERE `creature`.`guid` = 208512;
DELETE FROM `creature` WHERE `creature`.`guid` = 208513;
DELETE FROM `creature` WHERE `creature`.`guid` = 208514;

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(208509, 34061, 1, 1, 1, 0, 1, 1670.17, -4199.26, 56.3827, 3.98664, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208510, 34058, 1, 1, 1, 0, 0, 1673.07, -4201.89, 56.3826, 3.62927, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208511, 34036, 1, 1, 1, 0, 1, 1669.09, -4196.78, 56.3827, 4.10416, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208512, 34076, 0, 1, 1, 0, 1, -8773.78, 425.804, 105.233, 4.80621, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208513, 34082, 0, 1, 1, 0, 1, -8775.85, 423.96, 105.233, 5.73298, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208514, 34073, 0, 1, 1, 0, 1, -8781.18, 419.883, 105.233, 6.18459, 25, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208509;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208510;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208511;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208512;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208513;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`guid` = 208514;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
('58', '208509'),
('58', '208510'),
('58', '208511'),
('58', '208512'),
('58', '208513'),
('58', '208514');