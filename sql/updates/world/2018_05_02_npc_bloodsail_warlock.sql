UPDATE `creature_template` SET `dmg_multiplier` = 0.3 WHERE `entry` IN (10928,12922);
UPDATE `smart_scripts` SET `event_param3` = 4000, `event_param4` = 8000 WHERE `entryorguid` = 1564 AND `id` = 3;
