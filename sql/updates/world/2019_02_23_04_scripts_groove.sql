-- DB/Scripts: Grove Walker - shouldn't heal players
UPDATE `smart_scripts` SET `event_type` = 2, `event_param1` = 0, `event_param2` = 40, `target_type` = 1 WHERE `entryorguid` = 31228 AND `id` = 1;
