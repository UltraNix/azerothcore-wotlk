DELETE FROM `creature` WHERE `creature`.`guid` = 208515;
DELETE FROM `creature` WHERE `creature`.`guid` = 208516;
DELETE FROM `creature` WHERE `creature`.`guid` = 208517;
DELETE FROM `creature` WHERE `creature`.`guid` = 208518;
DELETE FROM `creature` WHERE `creature`.`guid` = 208519;
DELETE FROM `creature` WHERE `creature`.`guid` = 208520;

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(208515, 34083, 0, 1, 1, 0, 1, -8775.85, 423.96, 105.233, 5.73298, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208516, 34077, 0, 1, 1, 0, 1, -8773.78, 425.804, 105.233, 4.80621, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208517, 34074, 0, 1, 1, 0, 1, -8781.18, 419.883, 105.233, 6.18459, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208518, 34037, 1, 1, 1, 0, 1, 1669.09, -4196.78, 56.3827, 4.10416, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208519, 34062, 1, 1, 1, 0, 1, 1670.17, -4199.26, 56.3827, 3.98664, 25, 0, 0, 0, 0, 0, 0, 0, 0),
(208520, 34059, 1, 1, 1, 0, 0, 1673.07, -4201.89, 56.3826, 3.62927, 25, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208515;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208516;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208517;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208518;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208519;
DELETE FROM `game_event_creature` WHERE `game_event_creature`.`eventEntry` = 59 AND `game_event_creature`.`guid` = 208520;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES 
('59', '208515'),
('59', '208516'),
('59', '208517'),
('59', '208518'),
('59', '208519'),
('59', '208520');