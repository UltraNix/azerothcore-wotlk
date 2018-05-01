UPDATE `creature` SET `spawntimesecs` = 180 WHERE `id` = 818;
UPDATE `smart_scripts` SET `event_param2` = 10000, `event_param3` = 15000, `event_param4` = 20000 WHERE `entryorguid` = 818 AND `id` = 1;
UPDATE `smart_scripts` SET `event_param2` = 3000, `event_param3` = 15000, `event_param4` = 25000 WHERE `entryorguid` = 818 AND `id` = 0;
