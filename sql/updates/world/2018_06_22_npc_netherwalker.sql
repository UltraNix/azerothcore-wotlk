UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 64 WHERE `entry` = 14389;
UPDATE `smart_scripts` SET `event_param3` = 20000, `event_param4` = 25000 WHERE `entryorguid` = 14386 AND `id` = 1;
