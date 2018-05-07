UPDATE `creature_template` SET `unit_flags` = 32832 WHERE `entry` = 20132;
UPDATE `creature` SET `spawntimesecs` = 60 WHERE `guid` = 71631;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 20132 AND `id` IN (13,14);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19466 AND `id` = 8;
INSERT INTO `smart_scripts` VALUES
(20132, 0, 13, 0, 38, 0, 100, 0, 4, 4, 0, 0, 18, 33600, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Socrethar - on data set - set unit_flag'),
(20132, 0, 14, 0, 25, 0, 100, 0, 0, 0, 0, 0, 18, 32832, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Socrethar - on reset - set unit flag'),
(19466, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 19, 20132, 50, 0, 0, 0, 0, 0, 'Exarch - On data set - Socrethar');
UPDATE `smart_scripts` SET `link` = 8 WHERE `entryorguid` = 19466 AND `id` = 3;
