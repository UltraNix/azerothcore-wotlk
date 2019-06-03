-- DB/Creature: Forgus - add missing spawn
-- DB/Quest: Slain by the Wrentched - breadcrumb no longer required

DELETE FROM `creature` WHERE `id`  = 21455 AND `guid` = 160828;
DELETE FROM `creature` WHERE `id`  = 23148 AND `guid` = 160829;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`,  `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(160828, 21455, 530, 1, 1, 1, -3422.27, 1122.06, 46.7247, 0.86922, 180, 0, 0),
(160829, 23148, 530, 1, 1, 0, -5137.82, 561.520, 84.3600, 4.74700, 180, 0, 0);

UPDATE `quest_template` SET `PrevQuestID`=0 WHERE `ID`=9704;
