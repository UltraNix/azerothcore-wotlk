UPDATE `creature_template` SET `ScriptName` = "", `AIName` = "SmartAI" WHERE `entry` = 27258;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 27258;
INSERT INTO `smart_scripts` VALUES
(27258, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - on just summon - follow summoner'),
(27258, 0, 1, 0, 28, 0, 100, 1, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Wintergarde Gryphon - on passenenger removed -despawn');

DELETE FROM `conditions` WHERE `SourceEntry` IN (30228,27258);
INSERT INTO `conditions` VALUES
(16, 0, 30228, 0, 0, 23, 0, 4501, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 30228, 0, 1, 23, 0, 4504, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 30228, 0, 2, 23, 0, 4505, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 30228, 0, 3, 23, 0, 4506, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 27258, 0, 0, 23, 0, 4177, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 27258, 0, 1, 23, 0, 4178, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 27258, 0, 2, 23, 0, 4188, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone');