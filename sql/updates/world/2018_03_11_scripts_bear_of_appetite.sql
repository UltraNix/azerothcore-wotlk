UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 189290;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 189290;
INSERT INTO `smart_scripts` VALUES
(189290, 1, 0, 0, 8, 0, 100, 0, 48794, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,  'School of Northern Salmon - On Fishing Net Spell Hit - Despawn');
