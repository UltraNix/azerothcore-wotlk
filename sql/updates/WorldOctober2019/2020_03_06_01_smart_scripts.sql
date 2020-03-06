DELETE FROM `smart_scripts` WHERE `entryorguid` = 33429 AND `source_type` = 0 AND `id` = 2;
INSERT INTO `smart_scripts` (`entryorguid`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (33429, 2, 6, 41, 60000, 1, 'On Death - Despawn after 60s');
