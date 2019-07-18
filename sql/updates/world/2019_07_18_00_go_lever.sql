-- DB/Gameobject: Fix lever near Violet Hold entrance
UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI", `ScriptName` = "" WHERE `entry` = 193020;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 193020 AND `source_type` = 1;
INSERT INTO `smart_scripts` VALUES (193020, 1, 0, 0, 70, 0, 100, 0, 2, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 61606, 193019, 0, 0, 0, 0, 0, 'Lever - On Gameobject State Changed - Activate Gameobject');
