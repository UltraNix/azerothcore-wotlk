-- Wooly Mammoth Bull
UPDATE `creature_template` SET `RegenHealth`=1 WHERE `entry`=25743;

-- Gundrak Raptor skinning
DELETE FROM `skinning_loot_template` WHERE `entry`=70216;
INSERT INTO `skinning_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(70216, 33568, 0, 1, 1, 1, 8),
(70216, 44128, 1, 1, 1, 1, 2);
UPDATE `creature_template` SET `skinloot`=70216 WHERE `entry`=29334;

-- Disable pathfinding for some creatures
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|0x20000000 WHERE `entry` IN 
(
	26536, -- Mindless Servant
	30791, -- Mindless Servant (Heroic)
	26674, -- Darkweb Hatchling
	31335  -- Darkweb Hatchling (Heroic)
);
