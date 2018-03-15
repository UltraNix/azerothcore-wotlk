UPDATE `smart_scripts` SET `action_type` = 49, `action_param1` = 0, `target_type` = 21, `target_param1` = 10, `comment` = "Chancellor Amai - Script - Attack Start" WHERE `entryorguid` = 2738100 AND `id` = 3;
UPDATE `smart_scripts` SET `action_type` = 49, `action_param1` = 0, `target_type` = 21, `target_param1` = 10, `comment` = "Deathguard Schneider - Script - Attack Start" WHERE `entryorguid` = 2737600 AND `id` = 3;
UPDATE `smart_scripts` SET `action_type` = 49, `action_param1` = 0, `target_type` = 21, `target_param1` = 10, `comment` = "Engineer Burke - Script - Attack Start" WHERE `entryorguid` = 2737900 AND `id` = 3;
UPDATE `smart_scripts` SET `action_type` = 49, `action_param1` = 0, `target_type` = 21, `target_param1` = 10, `comment` = "Senior Scrivener Barriga - Script - Attack Start" WHERE `entryorguid` = 2737800 AND `id` = 3;

UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 536870912 WHERE `entry` IN (27381,27376,27379,27378);