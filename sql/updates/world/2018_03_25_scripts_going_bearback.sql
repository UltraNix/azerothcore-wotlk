UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 29351;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29351 AND `id` = 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29358 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(29351, 0, 1, 0, 8, 0, 100, 1, 54897, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frost Giant - On Spell Hit - Despawn in 10 secs'),
(29358, 0, 2, 0, 8, 0, 100, 1, 54897, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frostworg - On Spell Hit - Despawn in 10 secs');

UPDATE `creature` SET `spawntimesecs` = 60 WHERE `id` IN (29351, 29358);
