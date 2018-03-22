DELETE FROM `areatrigger_scripts` WHERE `entry` = 168;
INSERT INTO `areatrigger_scripts` VALUES
(168, 'SmartTrigger');

DELETE FROM `smart_scripts` WHERE `source_type` = 2 AND `entryorguid` = 168;
INSERT INTO `smart_scripts` VALUES
(168, 2, 0, 0, 46, 0, 100, 0, 0, 0, 0, 0, 15, 287, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'areatrigger - on trigger - areaexplored frostmane hold');
