UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 190777;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 190777 AND `source_type` = 1;
INSERT INTO `smart_scripts` VALUES
(190777, 1, 0, 0, 1, 0, 100, 1, 120000, 120000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
