UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 2 WHERE `entry` = 28137;
UPDATE `smart_scripts` SET `action_param2` = 7 WHERE `entryorguid` IN (28142, 28136, 28148) AND `id` IN (11, 12);
