DELETE FROM `smart_scripts` WHERE `entryorguid` = 30160 AND `source_type` = 0 AND `id` = 2;
INSERT INTO `smart_scripts` (`entryorguid`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (30160, 2, 6, 41, 180000, 1, 'On Death - Despawn after 180s');
