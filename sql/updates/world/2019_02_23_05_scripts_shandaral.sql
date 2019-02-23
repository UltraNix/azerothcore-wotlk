-- DB/Scripts: Lost Shandaral Spirit - shouldnt cast heal on players
UPDATE `smart_scripts` SET `event_type` = 2, `event_param1` = 0, `event_param2` = 40, `target_type` = 1 WHERE `entryorguid` = 31231 AND `id` = 1;
