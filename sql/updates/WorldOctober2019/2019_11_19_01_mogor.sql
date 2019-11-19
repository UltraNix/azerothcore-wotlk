UPDATE `smart_scripts` SET `link`='15' WHERE  `entryorguid`=18069 AND `source_type`=0 AND `id`=14 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18069 AND `source_type` = 0 AND `id` = 15;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES ('18069', 0, 15, 61, 41, 5000, 1, 'Mogor - On Just Died - Despawn after 5s');
UPDATE `creature` SET `spawntimesecs`='15' WHERE  `guid`=48191;