select * from creature_template where entry = 33953;
UPDATE `creature_template` SET `AIName` = "SmartAI", `flags_extra` = `flags_extra` | 2 WHERE `entry` = 33953;
UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 194461;
UPDATE `gameobject_template` SET `data1` = 194463 WHERE `entry` = 194463; 
DELETE FROM `gameobject_loot_template` WHERE `entry` = 194463;
INSERT INTO `gameobject_loot_template` VALUES
(194463, 45278, -100, 1, 0, 1, 4);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (194461,33953);
INSERT INTO `smart_scripts` VALUES
(194461, 1, 0, 0, 70, 0, 100, 0, 2, 0, 0, 0, 11, 63385, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
( 33953, 0, 0, 0, 1, 0, 100, 0, 2000, 4000, 1000, 2000, 11, 63386, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
( 33953, 0, 1, 0, 1, 0, 100, 0, 10000, 10000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

