UPDATE `creature_template` SET AIName = 'SmartAI' WHERE `entry` = 31099;
UPDATE `creature` SET `spawntimesecs` = 60 WHERE `id` = 31099;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 31099 AND `source_type` = 0;