-- DB/NPC: Farseer Faedris - remove additional spawn https://github.com/SunwellTracker/issues/issues/2551
-- DB/Loot: Uncured Caribou Hide - slightly increase drop chance https://github.com/SunwellTracker/issues/issues/2547
-- DB/Quest: Battling the Elements - add additional spawns of Seething Revenants
-- DB/Quest: Boiling blood - slightly increase drop chance https://github.com/SunwellTracker/issues/issues/2557
-- DB/NPC: Heb'Drakkar Striker - should not fly dismounted https://github.com/SunwellTracker/issues/issues/2531
-- DB/Quest: The Last Line Of Defense - turret's spells should not target players https://github.com/SunwellTracker/issues/issues/2558
DELETE FROM `creature` WHERE `guid` = 125031 AND `id` = 32250;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -37 WHERE `entry` = 25680 AND `item` = 35288;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -30 WHERE `entry` = 25750 AND `item` = 35288;
DELETE FROM `creature` WHERE `id` = 30120 AND `guid` IN (303308, 303309, 303310, 303311,303312);
INSERT INTO `creature` VALUES 
(303308, 30120, 571, 1, 4, 0, 0, 7238.28, -3617.2, 823.124, 4.48637, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(303309, 30120, 571, 1, 4, 0, 0, 7199.95, -3644.77, 823.605, 0.681117, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(303310, 30120, 571, 1, 4, 0, 0, 7238.47, -3694.46, 824.055, 0.300193, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(303311, 30120, 571, 1, 4, 0, 0, 7249.85, -3669.73, 823.013, 3.30042, 300, 0, 0, 12600, 0, 0, 0, 0, 0),
(303312, 30120, 571, 1, 4, 0, 0, 7219.73, -3689.90, 822.369, 2.01, 300, 0, 0, 12600, 0, 0, 0, 0, 0);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -30 WHERE `entry` = 19442 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -22 WHERE `entry` = 19424 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -22 WHERE `entry` = 16907 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -22 WHERE `entry` = 16871 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -22 WHERE `entry` = 16873 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -22 WHERE `entry` = 19422 AND `item` = 30425;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -15 WHERE `entry` = 19457 AND `item` = 30425;

UPDATE `creature_template` SET `InhabitType` = 3 WHERE `entry` = 28465;

DELETE FROM `conditions` WHERE `SourceEntry` = 57542;
INSERT INTO `conditions` VALUES 
(13, 1, 57542, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Argent Cannon Assault should not target players');

DELETE FROM `conditions` WHERE `SourceEntry` = 57415;
INSERT INTO `conditions` VALUES 
(13, 1, 57415, 0, 0, 31, 0, 4, 0, 0, 1, 0, 0, '', 'The Reckoning should not target players');
