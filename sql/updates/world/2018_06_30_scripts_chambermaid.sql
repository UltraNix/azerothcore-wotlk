DELETE FROM `creature_text` WHERE `entry` = 14636;
INSERT INTO `creature_text` VALUES
(14636, 0, 0, "Thieves! Scallywags! Rapscallions! Come face me gigantic pillas!", 14, 0, 100, 0, 0, 0, 0, 'Chambermaid');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14636;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14636;
INSERT INTO `smart_scripts` VALUES
(14636, 0, 0, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 1, 2, 0, 0, 0, 0, 9, 70101, 0, 100, 0, 0, 0, 0, 'Chambermaid - On Death - Set Data 1 2 On Event Trigger'),
(14636, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chambermaid - On Aggro - Say Line 0'),
(14636, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 50, 0, 0, 0, 0, 0, 0, 'Chambermaid - On Just Summoned - Attack Closest Player'),
(14636, 0, 3, 0, 0, 0, 100, 0, 8000, 12000, 30000, 40000, 11, 23417, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Chambermaid - In Combat - Cast Smother'),
(14636, 0, 4, 0, 0, 0, 100, 0, 4000, 6000, 20000, 30000, 11, 23416, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Chambermaid - In Combat - Cast Pillow Fight');

UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 179828;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 179828;
INSERT INTO `smart_scripts` VALUES
(179828, 1, 0, 0, 70, 0, 10, 0, 2, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 70101, 0, 100, 0, 0, 0, 0, 'Dark Iron Pillow - On State Change - Set Data 1 1 On Event Trigger');
UPDATE `gameobject` SET `spawntimesecs` = 180 WHERE `id` = 179828;
DELETE FROM `creature_template` WHERE `entry` = 70101;
INSERT INTO `creature_template` VALUES
(70101, 0, 0, 0, 0, 0, 16480, 13069, 0, 0, 'Chambermaid Pillaclencher Event Trigger', NULL, NULL, 0, 70, 70, 1, 35, 0, 1.125, 1.14286, 1, 0, 252, 357, 0, 304, 1, 2000, 2000, 1, 33555200, 2048, 0, 0, 0, 0, 0, 0, 215, 320, 44, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 265, 1, 0, 130, 'npc_chambermaid_pillaclencher_trigger', 0);

UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `entry` = 16841 AND `item` = 18950;
