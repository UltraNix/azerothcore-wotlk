UPDATE `creature_addon` SET `path_id` = 770840 WHERE `guid` = 77084;
UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = 77084;
UPDATE `creature_template` SET `flags_extra` = 0 WHERE `entry` = 22061;
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "" WHERE `entry` = 22006;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 22061;
INSERT INTO `smart_scripts` VALUES 
(22061, 0, 0, 0, 6, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 77084, 22006, 0, 0, 0, 0, 0, 'Shadowmoon SoulStealer - on just died - Set data 1 1 - On Deathwail');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 22006;
INSERT INTO `smart_scripts` VALUES 
(22006, 0, 0, 0, 0, 0, 100, 0, 0, 0, 3400, 4700, 11, 12471, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Shadowlord Deathwail - In Combat - Cast \'Shadow Bolt\''),
(22006, 0, 1, 0, 0, 0, 100, 0, 8000, 8000, 20000, 22000, 11, 32709, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 'Shadowlord Deathwail - In Combat - Cast \'Death Coil\''),
(22006, 0, 2, 0, 0, 0, 100, 0, 5000, 7000, 15000, 15000, 11, 15245, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Shadowlord Deathwail - In Combat - Cast \'Shadow Bolt Volley\''),
(22006, 0, 3, 0, 38, 0, 100, 0, 1, 1, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Deathwail - on Data set 1 1 - increase phase'),
(22006, 0, 4, 0, 60, 4, 100, 1, 0, 0, 0, 0, 80, 2200600, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Deathwail - on 3 soulstealer killed - Run script');
