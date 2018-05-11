UPDATE `smart_scripts` SET `action_param2` = 2 WHERE `entryorguid` = 25401 AND `id` = 1;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 25401;
UPDATE `smart_scripts` SET `action_param2` = 2 WHERE `entryorguid` = 25401 AND `id` IN (2,3,4,5);
