-- DB/Quest: Raising Hodir's Spear - update Stoic Mammoth Hide drop chance https://github.com/SunwellTracker/issues/issues/2787
-- DB/Loot: Firemane Flamecaller - correct loottable https://github.com/SunwellTracker/issues/issues/2734
-- DB/Quest: I Sense A Disturbance - small adjustment's to Kitten's path https://github.com/SunwellTracker/issues/issues/2775
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -29 WHERE `item` = 42542;

DELETE FROM `skinning_loot_template` WHERE `entry` = 4334;
INSERT INTO `skinning_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(4334, 1, 100, 1, 0, -4107, 1);

DELETE FROM `reference_loot_template` WHERE `entry` = 4107;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(4107, 4234, 0, 1, 0, 1, 2),
(4107, 4235, 0, 1, 0, 1, 1),
(4107, 4304, 0, 1, 0, 1, 2),
(4107, 8165, 0, 1, 0, 1, 2),
(4107, 8169, 0, 1, 0, 1, 1);

UPDATE `smart_scripts` SET `event_param1` = 3000, `event_param2` = 3000 WHERE `entryorguid` = 2866500 AND `id` = 0;
UPDATE `smart_scripts` SET `event_param1` = 1000, `event_param2` = 1000 WHERE `entryorguid` = 2866500 AND `id` = 1;
