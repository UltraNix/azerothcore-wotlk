-- DB/NPC: Zanzil Hunters should not flee in fear when low hp
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1489 AND `id` = 2;

-- DB/Loot: Saltwater Snapjaws - correct skinning loot table
DELETE FROM `skinning_loot_template` WHERE `entry` = 2505;
INSERT INTO `skinning_loot_template` VALUES 
(2505, 4304, 60, 1, 0, 1, 1),
(2505, 8167, 20, 1, 0, 1, 2),
(2505, 8169, 3, 1, 0, 1, 1),
(2505, 8170, 17, 1, 0, 1, 1);
 
 -- DB/AI: Contagion of Rot - should not stack
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1793,3733,1488) AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1270 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES 
(1270, 0, 1, 0, 0, 0, 100, 0, 2200, 18500, 120200, 125700, 11, 7102, 32, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Fetid Corpse - In Combat - Cast \'Contagion of Rot\''),
(1793, 0, 0, 0, 0, 0, 100, 0, 9000, 16000, 240000, 250000, 11, 7102, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Rotting Ghoul - In Combat - Cast \'Contagion of Rot\' (No Repeat)'),
(3733, 0, 0, 0, 0, 0, 100, 0, 5000, 11000, 120000, 135000, 11, 7102, 32, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Forsaken Herbalist - In Combat - Cast \'Contagion of Rot\' (No Repeat)'),
(1488, 0, 0, 0, 0, 0, 100, 1, 2000, 3000, 0, 0, 11, 7102, 32, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Zanzil Zombie - In Combat - Cast \'Contagion of Rot\' (No Repeat)');

-- DB/NPC: Delete unused Henria Derth spawn
DELETE FROM `creature` WHERE `id` = 2870;

-- Core/NPC: Bragok - summoned wyvern/gryphon should attack player who attacked bragok.
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_bragok" WHERE `entry` = 16227;
