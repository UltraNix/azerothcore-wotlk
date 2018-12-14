DELETE FROM `creature_loot_template` WHERE `entry` IN (38603, 38599, 38112, 38113);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(38603, 1, 100, 1, 1, -35056, 2),
(38603, 43228, 100, 1, 0, 4, 4),
(38603, 47241, 100, 1, 0, 1, 1),
(38599, 1, 100, 1, 1, -35055, 2),
(38599, 43228, 100, 1, 0, 4, 4),
(38599, 47241, 100, 1, 0, 1, 1),
(38112, 1, 100, 1, 1, -35053, 2),
(38112, 43228, 100, 1, 0, 3, 3),
(38112, 47241, 100, 1, 0, 1, 1),
(38113, 1, 100, 1, 1, -35054, 2),
(38113, 43228, 100, 1, 0, 3, 3),
(38113, 47241, 100, 1, 0, 1, 1);


DELETE FROM `gameobject_loot_template` WHERE `entry` IN (27985, 27993);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27985, 1, 100, 1, 0, -35091, 2),
(27985, 47241, 100, 1, 0, 1, 1),
(27993, 1, 100, 1, 0, -35092, 2),
(27993, 43102, 85, 1, 0, 1, 1),
(27993, 47241, 100, 1, 0, 1, 1);

