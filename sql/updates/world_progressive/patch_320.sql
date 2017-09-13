### CONFIG CHANGES REQUIRED
# AllowTwoSide.Accounts = 1
# AllowTwoSide.Interaction.Mail = 1
# TalentsInspecting = 1
#

#
# === Content 3.2.0 (Argent Tournament) ===
#
SET @EmblemHighPREV := 45624; # Emblem of Conquest
SET @EmblemLowPREV  := 40753; # Emblem of Valor
SET @EmblemLowPREV2 := 40752; # Emblem of Heroism

SET @EmblemHighCURR := 47241; # Emblem of Triumph
SET @EmblemLowCURR  := 45624; # Emblem of Conquest

# Update loot tables
UPDATE `creature_loot_template` SET `item`=@EmblemLowCURR WHERE `item` IN (@EmblemLowPREV2, @EmblemLowPREV);
UPDATE `gameobject_loot_template` SET `item`=@EmblemLowCURR WHERE `item` IN (@EmblemLowPREV2, @EmblemLowPREV);
UPDATE `item_loot_template` SET `item`=@EmblemLowCURR WHERE `item` IN (@EmblemLowPREV2, @EmblemLowPREV);
UPDATE `reference_loot_template` SET `item`=@EmblemLowCURR WHERE `item` IN (@EmblemLowPREV2, @EmblemLowPREV);
UPDATE `spell_loot_template` SET `item`=@EmblemLowCURR WHERE `item` IN (@EmblemLowPREV2, @EmblemLowPREV);

# ToC & VoA (Koralon) & Daily Quest Proof of Demise should grant EoTs.
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34797, 35447, 35448, 35449); -- Icehowl
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34780, 35216, 35268, 35269); -- Lord Jaraxxus
UPDATE `gameobject_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (27498, 27503, 27335, 27356); -- Faction Champions
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34497, 35350, 35351, 35352, 34496, 35347, 35348, 35349); -- Twin Val'kyr
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (34564, 34566, 35615, 35616); -- Anub'arak
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV AND `entry` IN (35013, 35360); -- Koralon the Flame Watcher
UPDATE `quest_template` SET `RewardItemId1`=47241 WHERE `Id` IN (13246, 13248, 13250, 13252, 13254, 13256, 13245, 13247, 13249, 13251, 13253, 13255, 14199); -- Proof of Demise quests

# Update quest emblems
UPDATE `quest_template` SET `RewardItemId1`=@EmblemLowCURR WHERE `RewardItemId1` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardItemId2`=@EmblemLowCURR WHERE `RewardItemId2` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardItemId3`=@EmblemLowCURR WHERE `RewardItemId3` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardItemId4`=@EmblemLowCURR WHERE `RewardItemId4` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardChoiceItemId1`=@EmblemLowCURR WHERE `RewardChoiceItemId1` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardChoiceItemId2`=@EmblemLowCURR WHERE `RewardChoiceItemId2` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardChoiceItemId3`=@EmblemLowCURR WHERE `RewardChoiceItemId3` IN (@EmblemLowPREV, @EmblemLowPREV2);
UPDATE `quest_template` SET `RewardChoiceItemId4`=@EmblemLowCURR WHERE `RewardChoiceItemId4` IN (@EmblemLowPREV, @EmblemLowPREV2);
# Remove disables for raids and instances for current content
DELETE FROM `disables` WHERE `sourceType` = 2 AND `entry` IN (649, 650);

# =============================================================================================

-- Ulduar 3.2 nerfs
UPDATE `creature_template` SET `health_mod`=1648.089171974522 WHERE `entry`=33449; -- General Vezax
UPDATE `creature_template` SET `health_mod`=672.03125 WHERE `entry`=34152; -- Saronite Animus
UPDATE `creature_template` SET `health_mod`=3155.2 WHERE `entry`=33955; -- Yogg-Saron
UPDATE `creature_template` SET `health_mod`=516.316 WHERE `entry`=33995; -- Heart of the Deconstructor (25n)

-- EoT Vendors
DELETE FROM `creature` WHERE `guid` IN (86928, 85217);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(86928, 35495, 571, 1, 1, 29831, 1, 5939.31, 513.155, 650.263, 2.56563, 180, 0, 0, 1, 0, 0, 0, 0, 0),
(85217, 35494, 571, 1, 1, 29832, 1, 5766.38, 738.24, 653.748, 2.94961, 180, 0, 0, 1, 0, 0, 0, 0, 0);

-- Val'anyr buff
UPDATE `item_template` SET `stat_value1`=621, `stat_value2`=55, `stat_value3`=57, `stat_value4`=50, `stat_value5`=49 WHERE `entry`=46017;

-- Crusader orb for vendors
SET @ORB_ENTRY := 47556;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = @ORB_ENTRY;
INSERT INTO `npc_vendor` (`entry`, `item`, `ExtendedCost`) VALUES
(35573, @ORB_ENTRY, 2723),
(35494, @ORB_ENTRY, 2723),
(35574, @ORB_ENTRY, 2723),
(35495, @ORB_ENTRY, 2723);

-- Flame Warder damage
UPDATE `creature_template` SET `mindmg`=500 , `maxdmg`=1000, `dmg_multiplier`=10 WHERE `entry`=35143;
UPDATE `creature_template` SET `mindmg`=1000 , `maxdmg`=2000, `dmg_multiplier`=10 WHERE `entry`=35359;

-- Wintergrasp Mark of Honor vendors
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48983;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48988;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48990;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48991;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48992;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48993;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48994;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48997;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48998;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48987;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48974;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48975;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48976;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48977;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48978;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48979;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48980;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48981;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48982;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48999;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 49000;
INSERT INTO `npc_vendor` (`entry`, `item`, `ExtendedCost`) VALUES
(32294, 48983, 2579),
(32294, 48988, 2579),
(32294, 48990, 2579),
(32294, 48991, 2579),
(32294, 48992, 2579),
(32294, 48993, 2579),
(32294, 48994, 2579),
(32294, 48997, 2579),
(32294, 48987, 2579),
(32294, 48998, 2579),
(32294, 48974, 2577),
(32294, 48975, 2577),
(32294, 48976, 2577),
(32294, 48977, 2577),
(32294, 48978, 2577),
(32294, 48979, 2577),
(32294, 48980, 2577),
(32294, 48981, 2577),
(32294, 48982, 2577),
(32294, 48999, 2577),
(32294, 49000, 2577),
(32296, 48983, 2579),
(32296, 48988, 2579),
(32296, 48990, 2579),
(32296, 48991, 2579),
(32296, 48992, 2579),
(32296, 48993, 2579),
(32296, 48994, 2579),
(32296, 48997, 2579),
(32296, 48987, 2579),
(32296, 48998, 2579),
(32296, 48974, 2577),
(32296, 48975, 2577),
(32296, 48976, 2577),
(32296, 48977, 2577),
(32296, 48978, 2577),
(32296, 48979, 2577),
(32296, 48980, 2577),
(32296, 48981, 2577),
(32296, 48982, 2577),
(32296, 48999, 2577),
(32296, 49000, 2577);

-- Honor: Epic Gems
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 34040;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 34043;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 34081;
INSERT INTO `npc_vendor` (`entry`, `item`, `ExtendedCost`) VALUES
(34043, -34040, 0),
(34081, -34040, 0),
(34040, 36919, 2588),
(34040, 36925, 2588),
(34040, 36928, 2588),
(34040, 36931, 2588),
(34040, 36934, 2588),
(34040, 36922, 2588),
(34040, 28118, 95),
(34040, 28119, 95),
(34040, 28120, 95),
(34040, 28362, 95),
(34040, 28123, 99),
(34040, 28363, 99),
(34040, 41559, 2426),
(34040, 41560, 2426),
(34040, 41563, 2426),
(34040, 41564, 2426),
(34040, 41565, 2426),
(34040, 41566, 2426),
(34040, 41569, 2426),
(34040, 41570, 2426),
(34040, 41571, 2426),
(34040, 41572, 2426),
(34040, 41573, 2426),
(34040, 41575, 2426);



-- Emblems: Epic Gems
DELETE FROM `npc_vendor` WHERE 
(`npc_vendor`.`entry` = 32172 OR `npc_vendor`.`entry` = 31582 OR `npc_vendor`.`entry` = 31580) 
AND (`npc_vendor`.`item` = 36919 OR `npc_vendor`.`item` = 36925 OR `npc_vendor`.`item` = 36922 OR `npc_vendor`.`item` = 36931 OR `npc_vendor`.`item` = 36928 OR `npc_vendor`.`item` = 36934 OR 
`npc_vendor`.`item` = 36930 OR `npc_vendor`.`item` = 36933 OR `npc_vendor`.`item` = 36918 OR `npc_vendor`.`item` = 36921 OR `npc_vendor`.`item` = 36924 OR `npc_vendor`.`item` = 36927);
INSERT INTO `npc_vendor` (`entry`, `item`, `ExtendedCost`) VALUES
(32172, 36919, 2706),
(32172, 36925, 2706),
(32172, 36922, 2706),
(32172, 36931, 2484),
(32172, 36928, 2484),
(32172, 36934, 2484),
(31582, 36919, 2706),
(31582, 36925, 2706),
(31582, 36922, 2706),
(31582, 36931, 2484),
(31582, 36928, 2484),
(31582, 36934, 2484),
(31580, 36919, 2706),
(31580, 36925, 2706),
(31580, 36922, 2706),
(31580, 36931, 2484),
(31580, 36928, 2484),
(31580, 36934, 2484);

-- Prospecting Titanium Ore

DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=3;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 3, 75, 1, 1, -1003, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=2;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 2, 100, 1, 1, -1002, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=1;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 1, 20, 1, 0, -13005, 1);
DELETE FROM `prospecting_loot_template` WHERE `entry`=36910 AND `item`=46849;
INSERT INTO `prospecting_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (36910, 46849, 75, 1, 0, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36919;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36919, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36922;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36922, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36925;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36925, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36928;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36928, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36931;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36931, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=13005 AND `item`=36934;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (13005, 36934, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36917;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36917, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36932;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36932, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36929;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36929, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36926;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36926, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36923;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36923, 0, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1003 AND `item`=36920;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1003, 36920, 0, 1, 1, 1, 2);

DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36929;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36929, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36917;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36917, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36933;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36933, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36932;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36932, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36930;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36930, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36927;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36927, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36926;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36926, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36924;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36924, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36923;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36923, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36921;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36921, 4, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36920;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36920, 12.5, 1, 1, 1, 2);
DELETE FROM `reference_loot_template` WHERE `entry`=1002 AND `item`=36918;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (1002, 36918, 5, 1, 1, 1, 2);

-- Icy Prism

DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=3;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 3, 50, 1, 0, -45010, 1);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=1;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 1, 7, 1, 0, -10008, 1);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=2;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 2, 100, 1, 0, -45010, 2);
DELETE FROM `item_loot_template` WHERE `entry`=44943 AND `item`=42225;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (44943, 42225, 10, 1, 7, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36918;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36918, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36921;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36921, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36924;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36924, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36927;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36927, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36930;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36930, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=45010 AND `item`=36933;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (45010, 36933, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36919;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36919, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36922;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36922, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36925;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36925, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36928;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36928, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36931;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36931, 0, 1, 1, 1, 1);
DELETE FROM `reference_loot_template` WHERE `entry`=10008 AND `item`=36934;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (10008, 36934, 0, 1, 1, 1, 1);

-- Recipes Epic Gem 

DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46897 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46897, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46898 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46898, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46899 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46899, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46900 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46900, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46901 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46901, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46902 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46902, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46903 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46903, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46904 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46904, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46905 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46905, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46906 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46906, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46907 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46907, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46908 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46908, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46909 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46909, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46910 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46910, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46911 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46911, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46912 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46912, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46913 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46913, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46914 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46914, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46915 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46915, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46916 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46916, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46917 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46917, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46918 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46918, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46919 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46919, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46920 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46920, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46921 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46921, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46922 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46922, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46923 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46923, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46924 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46924, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46925 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46925, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46926 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46926, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46927 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46927, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46928 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46928, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46929 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46929, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46930 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46930, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46931 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46931, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46932 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46932, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46933 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46933, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46934 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46934, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46935 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46935, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46936 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46936, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46937 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46937, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46938 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46938, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46939 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46939, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46940 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46940, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46941 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46941, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46942 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46942, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46943 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46943, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46944 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46944, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46945 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46945, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46946 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46946, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46947 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46947, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46948 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46948, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46949 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46949, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46950 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46950, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46951 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46951, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46952 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46952, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46953 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46953, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=46956 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 46956, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47007 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47007, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47008 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47008, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47010 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47010, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47011 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47011, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47012 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47012, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47015 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47015, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47016 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47016, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47017 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47017, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47018 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47018, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47019 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47019, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47020 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47020, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47021 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47021, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47022 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47022, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=47023 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 47023, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=28701 AND `item`=49112 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (28701, 0, 49112, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=20815 AND `ExtendedCost`=0;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 20815, 0, 0, 0);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=20824 AND `ExtendedCost`=0;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 20824, 0, 0, 0);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46897 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46897, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46898 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46898, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46899 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46899, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46900 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46900, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46901 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46901, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46902 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46902, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46903 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46903, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46904 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46904, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46905 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46905, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46906 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46906, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46907 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46907, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46908 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46908, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46909 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46909, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46910 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46910, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46911 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46911, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46912 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46912, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46913 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46913, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46914 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46914, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46915 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46915, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46916 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46916, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46917 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46917, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46918 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46918, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46919 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46919, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46920 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46920, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46921 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46921, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46922 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46922, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46923 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46923, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46924 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46924, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46925 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46925, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46926 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46926, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46927 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46927, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46928 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46928, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46929 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46929, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46930 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46930, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46931 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46931, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46932 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46932, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46933 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46933, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46934 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46934, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46935 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46935, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46936 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46936, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46937 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46937, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46938 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46938, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46939 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46939, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46940 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46940, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46941 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46941, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46942 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46942, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46943 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46943, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46944 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46944, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46945 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46945, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46946 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46946, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46947 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46947, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46948 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46948, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46949 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46949, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46950 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46950, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46951 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46951, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46952 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46952, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46953 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46953, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=46956 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 46956, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47007 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47007, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47008 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47008, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47010 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47010, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47011 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47011, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47012 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47012, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47015 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47015, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47016 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47016, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47017 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47017, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47018 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47018, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47019 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47019, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47020 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47020, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47021 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47021, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47022 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47022, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=47023 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 47023, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33637 AND `item`=49112 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33637, 0, 49112, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=20815 AND `ExtendedCost`=0;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 20815, 0, 0, 0);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=20824 AND `ExtendedCost`=0;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 20824, 0, 0, 0);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46897 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46897, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46898 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46898, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46899 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46899, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46900 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46900, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46901 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46901, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46902 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46902, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46903 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46903, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46904 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46904, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46905 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46905, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46906 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46906, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46907 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46907, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46908 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46908, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46909 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46909, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46910 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46910, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46911 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46911, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46912 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46912, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46913 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46913, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46914 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46914, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46915 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46915, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46916 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46916, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46917 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46917, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46918 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46918, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46919 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46919, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46920 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46920, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46921 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46921, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46922 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46922, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46923 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46923, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46924 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46924, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46925 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46925, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46926 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46926, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46927 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46927, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46928 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46928, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46929 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46929, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46930 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46930, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46931 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46931, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46932 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46932, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46933 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46933, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46934 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46934, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46935 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46935, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46936 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46936, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46937 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46937, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46938 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46938, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46939 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46939, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46940 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46940, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46941 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46941, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46942 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46942, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46943 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46943, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46944 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46944, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46945 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46945, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46946 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46946, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46947 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46947, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46948 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46948, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46949 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46949, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46950 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46950, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46951 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46951, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46952 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46952, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46953 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46953, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=46956 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 46956, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47007 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47007, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47008 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47008, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47010 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47010, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47011 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47011, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47012 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47012, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47015 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47015, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47016 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47016, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47017 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47017, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47018 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47018, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47019 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47019, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47020 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47020, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47021 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47021, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47022 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47022, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=47023 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 47023, 0, 0, 2436);
DELETE FROM `npc_vendor` WHERE `entry`=33680 AND `item`=49112 AND `ExtendedCost`=2436;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (33680, 0, 49112, 0, 0, 2436);

-- Allow enter to Trial of the Crusader

UPDATE `access_requirement` SET completed_achievement = 0 WHERE `mapId`=649 AND `difficulty` IN (2, 3);

-- Alchemy: transmutating trainers 

DELETE FROM `npc_trainer` WHERE `entry`=201003 AND `spell`=66658;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (201003, 66658, 150000, 171, 450, 0);
DELETE FROM `npc_trainer` WHERE `entry`=201003 AND `spell`=66660;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (201003, 66660, 150000, 171, 450, 0);
DELETE FROM `npc_trainer` WHERE `entry`=201003 AND `spell`=66662;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (201003, 66662, 150000, 171, 450, 0);
DELETE FROM `npc_trainer` WHERE `entry`=201003 AND `spell`=66663;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (201003, 66663, 150000, 171, 450, 0);
DELETE FROM `npc_trainer` WHERE `entry`=201003 AND `spell`=66664;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (201003, 66664, 150000, 171, 450, 0);

-- Vendor: Runed Orb
DELETE FROM `npc_vendor` WHERE `entry` = 40160 AND `item` = 45087;
INSERT INTO `npc_vendor` (`entry`, `item`, `ExtendedCost`) VALUES (40160, 45087, 2987);

-- Koralon the Flame Watcher
DELETE FROM `creature` WHERE `guid`= 202596;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(202596, 35013, 624, 3, 1, 0, 0, -218.521, 104.391, 91.8297, 4.69494, 604800, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `health_mod`= 1058.285714285714 WHERE `entry`= 35440; -- Gormok the Impaler
UPDATE `creature_template` SET `health_mod`= 74.9814585908529 WHERE `entry` = 35443; -- Snobold Vassal
UPDATE `creature_template` SET `health_mod`= 600.2689376961004 WHERE `entry` IN (35513, 35516); -- Acidmaw & Dreadscale
UPDATE `creature_template` SET `health_mod`= 1625 WHERE `entry` = 35449; -- Icehowl
UPDATE `creature_template` SET `health_mod`= 2375 WHERE `entry` = 35269; -- Lord Jaraxxus
UPDATE `creature_template` SET `health_mod`= 87.51855779427359 WHERE `entry` = 35272; -- Mistress of Pain
UPDATE `creature_template` SET `health_mod`= 28.75 WHERE `entry` = 35264; -- Felflame Infernal
UPDATE `creature_template` SET `health_mod`= 79.96029776674938 WHERE `entry` IN (35280, 35267); -- Nether Portal & Infernal Volcano
UPDATE `creature_template` SET `health_mod`= 3500 WHERE `entry` IN (35352, 35349); -- Fjola Lightbane & Eydis Darkbane
UPDATE `creature_template` SET `health_mod`= 14.625 WHERE `entry` = 35659; -- Swarm Scarab
UPDATE `creature_template` SET `health_mod`= 67.5 WHERE `entry` = 35656; -- Nerubian Burrower
UPDATE `creature_template` SET `health_mod`= 2437.5 WHERE `entry` = 35616; -- Anub'arak
UPDATE `creature_template` SET `health_mod`= 68.73015873015873 WHERE `entry` IN (35776, 36303); -- Cat & Zhaagrym
UPDATE `creature_template` SET `health_mod`= 294.4358543417367 WHERE `entry` IN (35664, 35726, 35682, 35730, 35736, 35742, 35745, 35694, 35739, 35720, 35673, 35688, 35704, 35716, 35670, 35707, 35710, 35748, 35713, 35701); -- Hunter, Shaman, Death Knight, Warrior, Druid, Paladin, Rogue
UPDATE `creature_template` SET `health_mod`= 294.4 WHERE `entry` IN (35697, 35733, 35667, 35676, 35685, 35749, 35691, 35723); -- Warlock, Priest, Mage