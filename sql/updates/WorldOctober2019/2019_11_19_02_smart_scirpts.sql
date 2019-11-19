-- Brokentoe
UPDATE `smart_scripts` SET `link`=3 WHERE  `entryorguid`=18398 AND `source_type`=0 AND `id`=2 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18398 AND `source_type` = 0 AND `id` = 3;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (18398, 0, 3, 61, 41, 10000, 1, 'Brokentoe - On Just Died - Despawn after 10s');

-- The Blue Brothers
UPDATE `smart_scripts` SET `link`=6 WHERE  `entryorguid`=18399 AND `source_type`=0 AND `id`=5 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18399 AND `source_type` = 0 AND `id` = 6;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (18399, 0, 6, 61, 41, 10000, 1, 'Murkblood Twin - On Just Died - Despawn after 10s');

-- Rokdar
UPDATE `smart_scripts` SET `link`=7 WHERE  `entryorguid`=18400 AND `source_type`=0 AND `id`=6 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18400 AND `source_type` = 0 AND `id` = 7;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (18400, 0, 7, 61, 41, 10000, 1, 'Rokdar the Sundered Lord - On Just Died - Despawn after 10s');

-- Skra'gath
UPDATE `smart_scripts` SET `link`=5 WHERE  `entryorguid`=18401 AND `source_type`=0 AND `id`=4 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18401 AND `source_type` = 0 AND `id` = 5;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (18401, 0, 5, 61, 41, 10000, 1, 'Skra\'gath - On Just Died - Despawn after 10s');

-- The Warmaul Champion
UPDATE `smart_scripts` SET `link`=7 WHERE  `entryorguid`=18402 AND `source_type`=0 AND `id`=6 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 18402 AND `source_type` = 0 AND `id` = 7;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (18402, 0, 7, 61, 41, 10000, 1, 'The Warmaul Champion - On Just Died - Despawn after 10s');