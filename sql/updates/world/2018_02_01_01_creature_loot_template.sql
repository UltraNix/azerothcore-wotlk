DELETE FROM `creature_loot_template` WHERE `Entry`=118;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(118, 777, 25, 1, 1, 1, 3), -- Prowler teeth
(118, 2672, 85, 1, 0, 1, 3), -- Stringy wolf meat
(118, 3299, 15, 1, 1, 1, 3), -- Fractured canine
(118, 3300, 25, 1, 1, 1, 3), -- Rabbit's foot
(118, 24073, 2, 1, 2, -24073, 1), -- Junk
(118, 24074, 1, 1, 2, -24074, 1), -- Greens ilvl 10-11
(118, 24075, 0.5, 1, 2, -24075, 1), -- Greens ilvl 12-13
(118, 11111, 0.1, 1, 0, -11111, 1); -- Bags