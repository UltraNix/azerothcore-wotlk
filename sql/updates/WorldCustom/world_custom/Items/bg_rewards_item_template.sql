DELETE FROM `item_template` WHERE `item_template`.`entry` = 71999;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(71999, 15, 0, -1, 'Misty Satchel of Sunwell Gifts', 56915, 3, 4, 0, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, '', 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 12340);

DELETE FROM `item_loot_template` WHERE `item_loot_template`.`entry` = 71999;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71999, 1, 100, 1, 0, -71990, 1),
(71999, 2, 20, 1, 0, -71991, 1),
(71999, 3, 2, 1, 0, -71992, 1),
(71999, 4, 1, 1, 0, -71993, 1),
(71999, 5, 0.5, 1, 0, -71994, 1),
(71999, 6, 0.1, 1, 0, -71995, 1),
(71999, 7, 0.01, 1, 0, -71996, 1),
(71999, 45706, 10, 1, 0, 1, 1);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71990;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71990, 34822, 0, 1, 1, 1, 1),
(71990, 45980, 0, 1, 1, 1, 1),
(71990, 45981, 0, 1, 1, 1, 1),
(71990, 34823, 0, 1, 1, 1, 1),
(71990, 34825, 0, 1, 1, 1, 1),
(71990, 34824, 0, 1, 1, 1, 1),
(71990, 43522, 0, 1, 1, 1, 1),
(71990, 45979, 0, 1, 1, 1, 1),
(71990, 43521, 0, 1, 1, 1, 1),
(71990, 27442, 0, 1, 1, 1, 1),
(71990, 54470, 0, 1, 1, 1, 1),
(71990, 34476, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71991;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71991, 38233, 0, 1, 1, 3, 3),
(71991, 46779, 0, 1, 1, 3, 3),
(71991, 41427, 0, 1, 1, 5, 5),
(71991, 9317, 0, 1, 1, 5, 5),
(71991, 19026, 0, 1, 1, 5, 5);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71992;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71992, 38311, 0, 1, 1, 1, 1),
(71992, 45037, 0, 1, 1, 1, 1),
(71992, 45063, 0, 1, 1, 1, 1),
(71992, 46780, 0, 1, 1, 1, 1),
(71992, 34499, 0, 1, 1, 1, 1);


DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71993;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71993, 38050, 0, 1, 1, 1, 1),
(71993, 39656, 0, 1, 1, 1, 1),
(71993, 49287, 0, 1, 1, 1, 1),
(71993, 49646, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71994;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71994, 54068, 0, 1, 1, 1, 1),
(71994, 54069, 0, 1, 1, 1, 1),
(71994, 35226, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71995;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71995, 8628, 0, 1, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 71996;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(71996, 13317, 0, 1, 1, 1, 1),
(71996, 12302, 0, 1, 1, 1, 1);