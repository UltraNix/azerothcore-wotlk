UPDATE `smart_scripts` SET `link` = 7 WHERE `entryorguid` = 25584 AND `source_type` = 0 AND `id` = 4;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25584 AND `source_type` = 0 AND `id` = 7;
INSERT INTO `smart_scripts`(`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES
(25584, 0, 7, 61, 41, 30000, 1, 'Inquisitor Salrand - Just Died - Despawn after 30s');
UPDATE `creature` SET `spawntimesecs` = 30 WHERE `id` = 25584;