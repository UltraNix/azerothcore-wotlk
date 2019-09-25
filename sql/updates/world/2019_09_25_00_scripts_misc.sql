-- DB/NPC: Zanzil Hunters should not flee in fear when low hp
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1489 AND `id` = 1;
-- DB/Loot: Saltwater Snapjaws - correct skinning loot table
DELETE FROM `skinning_loot_template` WHERE `entry` = 2505;
INSERT INTO `skinning_loot_template` VALUES 
(2505, 1, 100, 1, 0, -39600, 1);

DELETE FROM `reference_loot_template` WHERE `entry` = 39600;
INSERT INTO `reference_loot_template` VALUES
(39600, 4304, 60, 1, 0, 1, 1),
(39600, 8167, 20, 1, 0, 1, 2),
(39600, 8169, 3, 1, 0, 1, 1),
(39600, 8170, 17, 1, 0, 1, 1);
