DELETE FROM `conditions` WHERE `conditions`.`SourceEntry` = 44213;
UPDATE `conditions` SET `SourceGroup` = '3' WHERE `conditions`.`SourceEntry` = 44214;

DELETE FROM `world`.`creature` WHERE `creature`.`id` = 24648;
INSERT INTO `world`.`creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(NULL, '24648', '571', '1', '1', '17188', '0', '1074.34', '-5043.678', '53.421', '5.007', '300', '5', '0', '92910', '0', '1', '0', '0', '0');