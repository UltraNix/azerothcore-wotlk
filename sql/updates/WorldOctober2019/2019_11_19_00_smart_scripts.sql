UPDATE `smart_scripts` SET `action_param2`='10' WHERE  `entryorguid`=2572900 AND `source_type`=9 AND `id`=4 AND `link`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25729 AND `source_type` = 0 AND `id` = 11;
INSERT INTO `smart_scripts` VALUES (25729, 0, 11, 0, 11, 0, 100, 0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 19, 25618, 100, 1, 0, 0, 0, 0, 'On Respawn - Respawn Varidus the Flenser')