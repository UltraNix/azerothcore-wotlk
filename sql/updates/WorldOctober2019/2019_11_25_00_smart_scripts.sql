UPDATE `creature_template` SET AIName = 'SmartAI' WHERE `entry` = 31099;
UPDATE `creature` SET `spawntimesecs` = 60 WHERE `id` = 31099;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 31099 AND `source_type` = 0;
INSERT INTO `smart_scripts`(`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES
(31099, 0, 1, 6, 41, 30000, 1, 'Patchwerk - Just Died - Despawn after 30s');